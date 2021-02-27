// MyMotionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyMotion.h"
#include "MyMotionDlg.h"
#include ".\mymotiondlg.h"
#include "afxdialogex.h"
#include "winsock.h"
#include "matlib.h"
#include "header_rtph263.h"
#include <cstdlib> 
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace jrtplib;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static float32 m_t = 0.0f;//����ʱ��
static float32 ld_basic = 0.0f;//��������λ��
static float32 rd_basic = 0.0f;//��������λ��
const float32 PI = 3.1415926f;
int delaycount;
float CurrentAngel;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
//
ofstream outlv("c:\\Data\\lv.txt");
ofstream outrv("c:\\Data\\rv.txt");
ofstream outld("c:\\Data\\ld.txt");
ofstream outrd("c:\\Data\\rd.txt");
ofstream outla("c:\\Data\\la.txt");
ofstream outra("c:\\Data\\ra.txt");
ofstream out("c:\\trace.txt");
ofstream out1("c:\\trace1.txt");
#define SendPortBase	3000
#define ReceivePortBase	2000
int ByteCount = 0;
unsigned char cdata[20000];
int cbuffer_size = 20000;
unsigned char rgbdata[400000];
int buffersize = 400000;

//����ص�
void OwnWriteFunction(int byte)
{
	if(ByteCount<cbuffer_size)
	{
		cdata[ByteCount]=(unsigned char)byte;
		++ByteCount;
	}
}

void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
		exit(-1);
	}
}

UINT ThreadCmd(LPVOID pParam)
{
	CMyMotionDlg* dlg=(CMyMotionDlg*)pParam;

	//�����׽���
	WORD wVersionRequested;
	WSADATA wsaData;//����winsock��İ汾��
	int err;
	wVersionRequested=MAKEWORD(1,1);//����������汾�ŵ�wordֵ
	err=WSAStartup(wVersionRequested,&wsaData);//�����׽��֣�����䷵��ֵ������0���˳�
	if (err!=0)
	{
		return 0;
	}
	if (LOBYTE (wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();//���������������İ汾����ô����wsacleanup��������ֹ��winsock���ʹ�ã�������
		return 0;

	}
	//�������׽��ֿ�֮�󣬾Ϳ��԰������潲���Ļ���TCP���������ӣ���socket����еķ������˳���������д����
	//�������ڼ������׽���
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);	//����socket���͵ı�����sockSrv����������socket�������ص��׽��֡�
	//socket��������һ������ֻ����AF_INET�����ߣ�PF_INET�������ǻ���TCPЭ������������Ҫ����������ʽ�׽��֣���˽�socket�ĺ����ĵڶ�����������ΪSOCK_STREAM
	//�������������ָ��Ϊ0���ú��������ݵ�ַ��ʽ���׽�������Զ�ѡ��һ�����ʵ�Э��
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//�Ա���sin_addr.S_un.S_addr��Ա���и�ֵ���ó�ԱΪu_long���ͣ��ú�����һ��u_longת��Ϊ�����ֽ�˳��
	addrSrv.sin_family=AF_INET;//������Ա���ǰ������ֽ�˳���ʾ��
	addrSrv.sin_port=htons(6000);//Ϊ����д���������ָ���˿ںš�
	//ע�⣺htons��htonl������������һ��:�������htons��һ��int����long����ֵת��Ϊ�����ֽ�˳�򣬿��ܻᶪʧ����

	//���׽��֣�������׽��ְ󶨵����ص�ĳ����ַ�Ͷ˿���
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//��һ���ֽڣ�Ҫ�󶨵��׽��֣��ڶ����ֽڣ���Ҫһ��ָ�룬������ȡ��ַ����ʵ��
	//addrSrv������SOCKADDR_IN�ṹ�����ͣ�������ҪSOCKADDR*���ͣ���SOCKADDR������˵����Сд��һ����
	//���׽�����Ϊ����ģʽ��׼�����ܿͻ�����
	listen(sockSrv,5);//��һ����������Ҫ���õ��׽��֣��ڶ��������ǵȴ����Ӷ��е���󳤶ȡ��������˲���ֵ����Ϊ5



	SOCKADDR_IN addrClient;//��֮ǰ������һ��SOCKADDR_IN���͵ı���addrSrv,Ȼ��Ըõ�ַ�ṹ������еĳ�Ա���и�ֵ��
	int len=sizeof(SOCKADDR);
	char sendBuf1[100];
	sprintf(sendBuf1,"welcome");
	while(true)
	{
		//�ȴ��ͻ�������
		SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);	//���յ����󣬷���һ���µĶ�Ӧ�ڴ����ӵ��׽���,��������������֮ǰ���븳��ʼֵ����SOCKADDR_IN�ṹ��ĳ���
		//��Ϊ�������ˣ���Ҫ���ϵȴ��ͻ��˵����������������ԣ�������Ž���һ��ѭ������һ������accept�����ȴ������ܿͻ��˵ĵ�ַ��Ϣ��
		//���ͻ���������ʱ���ú������ܸ����󣬽������� ��ͬʱ��������һ������뵱ǰ��������ӵ�һ���׽�����������������sockConn�С�
		//Ȼ����������׽��־Ϳ�����ͻ��˽���ͨ����


		//��ʱ����������send������ͻ��˷������ݣ����ȶ���һ���ַ����飬�����ͻ��˵ĵ�ַ��ʽ�������ŵ���������С�
		//�ڸ�ʽ���ͻ��˽��յ�ַʱ��ʹ��inet_ntoa�������ú�������һ��in_addr�ṹ�����͵Ĳ���������һ���Ե��ʮ���Ƹ�ʽ��ʾ��IP��ַ�ַ���
		//��SOCKADDR_IN�ṹ���е�sin_addr��Ա��in_addr���ͣ����ÿ�����Ϊ��������
		//���÷��͵��ַ���
		//sprintf(sendBuf,"welcome %s to use",inet_ntoa(addrClient.sin_addr));

		//��������
		send(sockConn,sendBuf1,strlen(sendBuf1)+1,0);
		//��ͻ��˷������ݣ���Ҫʹ���Ѿ��������ĸ��׽��֣�sockConn��������ʹ�����ڼ������ĸ��׽��֣�addrSrv
		//���ͳ��̿�����strlen����ã������������ڷ�������ʱ���෢����һ���ֽڣ���Ҫ��Ϊ���ý��ն��ڽ�������֮������һ����\0����Ϊ��β��־

		//��������
		char recvBuf[100];
		//����һ���ַ����飬���ڱ�����ܵ�����
		recv(sockConn,recvBuf,100,0);
		//���ݷ�����ϣ������Դӿͻ��˽������ݣ���recv��������һ�������ǽ�������֮����ĸ��׽��֣�sockConn��
		//��ӡ���ܵ�����

// 		dlg->UpdateData(TRUE);
// 		dlg->m_EdtRe=recvBuf;
// 		dlg->UpdateData(FALSE);
// 		dlg->GetDlgItem(IDC_EdtRe)->SetWindowText(dlg->m_EdtRe);
		if(strcmp(recvBuf, "left")==0)
		{
			g_Commands="left";
			sprintf(sendBuf1,"left");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "right")==0)
		{
			g_Commands="right";
			sprintf(sendBuf1,"right");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "backward")==0)
		{
			g_Commands="backward";
			sprintf(sendBuf1,"backward");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "forward")==0)
		{	
			g_Commands="forward";
		    sprintf(sendBuf1,"forward");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "stop")==0)
		{
			g_Commands="stop";
			sprintf(sendBuf1,"stop");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else 
		{
			dlg->m_EdtRe=recvBuf;
			sprintf(sendBuf1,"Commands not found");
		}
		// 		sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
		// 		send(sockConn,recvBuf,strlen(recvBuf)+1,0);
		closesocket(sockConn);
		//�ر��ѽ������ӵ��׽��֣��ͷ�Ϊ���׽��ַ������Դ��������һ��ѭ�����ȴ���һ���ͻ���������

	}
	/**************************************
	��Ϊ����ʹ����WinSock���еĺ��������ն�̬���ӿ��ʹ�÷�������Ҫ��������Ӧ��.lib�ļ�����ҪΪ���������ws2_32.lib
	***********************************/


	closesocket(sockSrv);
	return 0;

}

UINT ThreadImg(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;
//	dlg->m_string.Format(_T("Begin Sending Image!\n"));
// 	dlg->m_cListInfor.AddString(dlg->m_string);
// 	dlg->m_cListInfor.SetCurSel(dlg->m_cListInfor.GetCount()-1);

	//////////////////////////////
	IplImage * pSendFrame;
	CvCapture * pSendCapture = cvCaptureFromCAM(0);
// 	cvSetCaptureProperty( pSendCapture, CV_CAP_PROP_FRAME_WIDTH,320 );
// 	cvSetCaptureProperty( pSendCapture, CV_CAP_PROP_FRAME_HEIGHT,240 );
//  	cvSetCaptureProperty( pSendCapture, CV_CAP_PROP_FPS ,5 );

	pSendFrame = cvQueryFrame( pSendCapture ) ;
	IplImage * pFrame;
	pFrame=cvRetrieveFrame(pSendCapture);           // retrieve the captured frame
	uchar * pSendBufData = (uchar *)pSendFrame->imageData;
	////////////////////////////////////

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1);

	err = WSAStartup( wVersionRequested, &wsaData);
	if( err != 0 )return -1;
	if( LOBYTE( wsaData.wVersion) != 1 ||
		HIBYTE( wsaData.wVersion) != 1 )
	{
		WSACleanup();
		return -1;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5600);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	listen(sockSrv, 5);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		//CVAPI(IplImage*) cvRetrieveFrame( CvCapture* capture );
		//img=cvRetrieveFrame(pSendCapture);           // retrieve the captured frame

		
		pSendFrame = cvQueryFrame( pSendCapture ) ;
		char c=cvWaitKey(1);
		cvShowImage("Video Server",pSendFrame);
		/*send(sockConn, (const char *)pBufData, 480*1920+640*3+320+3 , 0);*/
		send(sockConn, (const char *)pSendBufData, 480*1920 , 0);
		closesocket(sockConn);		
	}

	WSACleanup();
	return 0;
}
UINT ThreadImgLocalRecv(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;

	//dlg->m_string.Format(_T("Begin receiving Image\n"));
	//dlg->m_cListInfor.AddString(dlg->m_string);
	//dlg->m_cListInfor.SetCurSel(dlg->m_cListInfor.GetCount()-1);

	//////////////////////////////
	IplImage * pColorImg ;
	pColorImg = cvCreateImage( cvSize(640,480), 8, 3 );
	pColorImg->widthStep = 1920;//pFrame->widthStep/(sizeof(uchar));//1920
	pColorImg->origin = 0;//pFrame->origin;//0
	pColorImg->width = 640;//cvGetSize(pFrame).width;//640
	pColorImg->height =480;// cvGetSize(pFrame).height;//480
	pColorImg->nChannels  =3;// pFrame->nChannels;//3
	uchar * pBufData = (uchar *)pColorImg->imageData;
	/*cvNamedWindow("Video Receiving from Server");*/
	//////////////////////////////
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup( wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	if( LOBYTE( wsaData.wVersion) != 1 ||
		HIBYTE( wsaData.wVersion) != 1 )
	{
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN addrSrv;
	CString IPAddr;
	//��ȡ��������

	IPAddr=dlg->cstrClientIP;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//��ַ
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5600);

	while (1)
	{	
		SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
		/*SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);*/
		if(connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
		{
			//	m_string.Format(_T("%s\n","connecting failed!"));
			//dlg->m_string.Format(_T("connecting failed!\n"));
		}
		else
		{
			recv(sockClient, (char *)pBufData, 640*1920,0);
			cvShowImage("Video Receiving from Server",pColorImg);
			//dlg->DrawPicToHDC(pColorImg, IDC_STATIC_PIC);
			char c =cvWaitKey(1);	
			if(c == 27)
				break;

		}
		closesocket(sockClient);
	}

	WSACleanup();
	cvDestroyWindow("ClientGrayImage");
	return 0;
}
UINT ThreadImgRecv(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;

	//dlg->m_string.Format(_T("Begin receiving Image\n"));
	//dlg->m_cListInfor.AddString(dlg->m_string);
	//dlg->m_cListInfor.SetCurSel(dlg->m_cListInfor.GetCount()-1);

	//////////////////////////////
	IplImage * pColorImg ;
	pColorImg = cvCreateImage( cvSize(320,240), 8, 3 );
	pColorImg->widthStep = 960;//pFrame->widthStep/(sizeof(uchar));//1920
	pColorImg->origin = 0;//pFrame->origin;//0
	pColorImg->width = 320;//cvGetSize(pFrame).width;//640
	pColorImg->height =240;// cvGetSize(pFrame).height;//480
	pColorImg->nChannels  =3;// pFrame->nChannels;//3
	uchar * pBufData = (uchar *)pColorImg->imageData;
	/*cvNamedWindow("Video Receiving from Server");*/
	//////////////////////////////
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup( wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	if( LOBYTE( wsaData.wVersion) != 1 ||
		HIBYTE( wsaData.wVersion) != 1 )
	{
		WSACleanup();
		return -1;
	}
	
		SOCKADDR_IN addrSrv;
		CString IPAddr;
		//��ȡ��������

		IPAddr=dlg->cstrClientIP;
		addrSrv.sin_addr.S_un.S_addr=inet_addr(IPAddr);//��ַ
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(5800);

		while (1)
		{	
			SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
			/*SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);*/
			if(connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
			{
				//	m_string.Format(_T("%s\n","connecting failed!"));
				//dlg->m_string.Format(_T("connecting failed!\n"));
			}
			else
			{
				recv(sockClient, (char *)pBufData, 240*960,0);
				//cvShowImage("Video Receiving from Server",pColorImg);
				dlg->DrawPicToHDC(pColorImg, IDC_STATIC_PIC);
				char c =cvWaitKey(1);	
				if(c == 27)
					break;

			}
			closesocket(sockClient);
		}

	WSACleanup();
	cvDestroyWindow("ClientGrayImage");
	return 0;
}

UINT ThreadImgRtpSending(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;
  
	//opencv var
	Mat frame;
	Mat temp[3];
	VideoCapture capture;
	int frameCount = 0;

	//h263 ----------encoder/decoder init
	unsigned int yuv[WIDTH*HEIGHT*3/2];
	CParam h263Param;
	Bits bits;
	InitLookupTable();
	h263Param.format = PARAM_FORM;
	InitH263Encoder(&h263Param);
	WriteByteFunction = OwnWriteFunction;

	//rtp---initialze and creation
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2), &dat);

	const size_t MaxPackSize = 20000;
	RTPSession session;
	RTPSessionParams sessionparams;
	sessionparams.SetOwnTimestampUnit(1.0/90000.0);	//for video ---see RFC2190

	RTPUDPv4TransmissionParams transparams;
	transparams.SetPortbase(SendPortBase);
	int status = session.Create(sessionparams,&transparams);
	checkerror(status);
	CString IPAddr;
	//��ȡ��������
	IPAddr=dlg->cstrClientIP;
	uint32_t data;
	if (IPAddr.Find(_T("0x"))==0)
	{
		_stscanf_s((LPCTSTR)IPAddr,_T("%x"),&data);
	} 
	else
	{
		_stscanf_s((LPCTSTR)IPAddr,_T("%d"),&data);
	}
	/*uint8_t localip[]={127, 0, 0, 1};*/
/*	uint8_t localip[]={192, 168, 0, 179};//�ͻ��˵�ַ*/
		uint8_t localip[]={192, 168, 1, 129};//�ͻ��˵�ַ
	RTPIPv4Address addr(localip, SendPortBase);
	status = session.AddDestination(addr);
	checkerror(status);

	session.SetDefaultPayloadType(34);	//PT for H.263----see RFC2190
	session.SetDefaultMark(true);		//true or false ?? both ok for my test	
	session.SetDefaultTimestampIncrement(3600);	// =90000/25
	session.SetMaximumPacketSize(MaxPackSize);
	capture.open(0);
	if (!capture.isOpened())
	{
		cout<<"open video/camera failed!"<<endl;
		return -1;
	}
	capture>>frame;
	if (frame.empty())
	{
		cout<<"grab frame failed! exit...."<<endl;
		return -1;
	}
	while (waitKey(40) != 27)	//25 fps
	{
		capture>>frame;
		if (frame.empty())
		{
			cout<<"grab frame failed! exit...."<<endl;
			return -1;
		}
		++frameCount;
 		resize(frame, temp[0], cv::Size(WIDTH, HEIGHT));	//resize to CIF
// 		imshow("raw", temp[0]);
	
		dlg->DrawPicToHDC(temp[0], IDC_STATIC_PIC2);
		char c =cvWaitKey(1);	
		if(c == 27)
			break;
		////---------------------------compress image frames-------------------------//	
		ConvertRGB2YUV(WIDTH, HEIGHT, temp[0].data, yuv);
		ByteCount = 0;
		h263Param.format = PARAM_FORM;
		h263Param.inter = CPARAM_INTRA;
		h263Param.Q_intra = 8;
		h263Param.data = yuv;
		CompressFrame(&h263Param, &bits);
		cout<<"compressed byte count is: "<<ByteCount<<endl;
		///-------------------------------------------------------------------------//

		status = session.SendPacket(cdata, ByteCount);
		checkerror(status);

	}
	//release resources
	cvDestroyAllWindows();
	ExitH263Encoder(&h263Param);

	RTPTime delay(5.0);
	session.BYEDestroy(delay, "trans over", 10);
	WSACleanup();
	return 0;
}

UINT ThreadImgRtpReceiving(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;

	//opencv var
	Mat frame;
	Mat temp[3];
	VideoCapture capture;
	int frameCount = 0;

	//h263 ----------encoder/decoder init
	uchar *readData = NULL;
	uchar *imgBuffer = NULL;
	InitLookupTable();
	InitH263Decoder();

	//rtp---initialze and creation
#ifdef WIN32
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
	RTPPacket *packet;
	const size_t MaxPackSize = 20000;
	RTPSession sess;
	RTPSessionParams sessionparams;
	sessionparams.SetOwnTimestampUnit(1.0/90000.0);	//for video ---see RFC2190
	sessionparams.SetAcceptOwnPackets(true);
	/*RTPUDPv4TransmissionParams transparams;*/
	RTPUDPv4TransmissionParams transparams;
	transparams.SetPortbase(ReceivePortBase);
	int status = sess.Create(sessionparams,&transparams);
	checkerror(status);
	/********************************************/
	sess.SetDefaultPayloadType(34);	//PT for H.263----see RFC2190
	sess.SetDefaultMark(true);		//true or false ?? both ok for my test	
	sess.SetDefaultTimestampIncrement(3600);	// =90000/25
	sess.SetMaximumPacketSize(MaxPackSize);
	int packetNum = 0;
	while(waitKey(40) != 27)	//25fps
	{
		sess.BeginDataAccess();
		if (sess.GotoFirstSourceWithData())
		{
			do 
			{

				while( (packet = sess.GetNextPacket()) != NULL)
				{
					cout<<"packet count: "<<++packetNum<<endl;
					size_t dataLen = packet->GetPayloadLength();
					cout<<"payload length: "<<dataLen<<endl;
					readData = packet->GetPayloadData();
					imgBuffer = new uchar[dataLen];
					memcpy(imgBuffer, readData, dataLen);

					///----------------------------decompress--------------------------//
					DecompressFrame(imgBuffer, dataLen, rgbdata, buffersize);
					///----------------------------------------------------------------//

					Mat GotImg(HEIGHT, WIDTH, CV_8UC3, rgbdata);
					if(GotImg.empty())
					{
						cout<<"got image has no data, exiting...."<<endl;
						return -1;
					}
					dlg->DrawPicToHDC(GotImg, IDC_STATIC_PIC);
					//release buffers and packet
					delete []imgBuffer;
					imgBuffer = NULL;
					sess.DeletePacket(packet);
				}

			} while (sess.GotoNextSourceWithData());
		}
		sess.EndDataAccess();

	}

	///////////////////////////////////////////////////////////////////

	//release resources
	ExitH263Decoder();
	RTPTime delay(5.0);
	sess.BYEDestroy(delay, "trans over", 10);
	WSACleanup();


	return 0;
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyMotionDlg �Ի���



CMyMotionDlg::CMyMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMotionDlg::IDD, pParent)
	, m_pDevMotion(NULL)
	, m_pMotion(NULL)
	, m_fLeftSpeed(0.1f)
	, m_fRightSpeed(0.1f)
	, m_lKp(0)
	, m_lKi(0)
	, m_lKd(0)
	, m_la(0.5f)
	, m_ls(1)
	, m_rKp(0)
	, m_rKi(0)
	, m_rKd(0)
	, m_ra(0.5f)
	, m_rs(1)
	, m_ModeSelect(1)
	, m_PidSelect(1)
	, m_ModeSelect1(0)
	, m_ClrState(0)
	, e_la(0.0f)
	, e_ra(10.0f)
	, m_fLv(0.0f)
	, m_fRv(0.0f)
	, m_CurrentTimer(0.0f)
	, m_CurrentLD(0.0f)
	, m_CurrentRD(0.0f)
	, m_pEncoder(NULL)
	, Vrx(0)
	, Vry(0)
	, X(0)
	, Y(0)
	, theta(0)
	, PreXd(0)
	, PreYd(0)
	, Wd(0)
	, Vd(0)
	, Vr(0)
	, Wr(0)
	, V(0)
	, W(0)
	, WaitTime(100)
	, PreVd(0)
	, PreWd(0)
	, thetaR(0)
	, Xr(0)
	, Yr(0)
	, e1(0)
	, e2(0)
	, e3(0)
	, N1(0)
	, N2(0)
	, T1(0)
	, T2(0)
	, I(60)
	, V1(0)
	, V2(0)
	, r(0.1)
	, R(2)
	, m(0)
	, md(0)
	, n(0)
	, nd(0)
	, framecount(0)
	, S1(0)
	, S2(0)
	, EncodeTime(0)
	, alfa1(0)
	, alfa2(0)
	, acc1(0)
	, acc2(0)
	, X1(0)
	, X2(0)
	, Y1(0)
	, px(277)
	, py(178)
	, m_iState(0)
	, cstrClientIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for (int i=0;i<4;i++)
	{
		m_fEncoderDis[i] = 0;
	}
	for (int i=0;i<5;i++)
	{
		m_fEncoder[i] = 0;
	}
	m_Vr = 0.0f;
	m_Wr = 0.0f;
	m_X = 0.0f;
	m_Xr = 0.0f;
	m_Y = 0.0f;
	m_Yr = 0.0f;
	m_theta = 0.0f;
	m_thetaR = 0.0f;
	m_T1 = 0.0f;
	m_T2 = 0.0f;
	//  m_V1 = 0.0f;
	//  m_V1 = 0.0f;
	//  m_V2 = 0.0f;
	m_V21 = 0.0f;
	m_V22 = 0.0f;
	m_e1 = 0.0f;
	m_e2 = 0.0f;
	m_e3 = 0.0f;
	m_EdtImg = _T("");
	m_EdtRe = _T("");
	m_CstrIP = _T("");
	m_UltraSonic_B = _T("");
	m_UltraSonic_F = _T("");
	m_UltraSonic_FL = _T("");
	m_UltraSonic_FR = _T("");
	m_UltraSonic_L = _T("");
	m_UltraSonic_R = _T("");
	m_PSD_B = _T("");
	m_PSD_F = _T("");
	m_PSD_FL = _T("");
	m_PSD_FR = _T("");
	m_PSD_L = _T("");
	m_PSD_R = _T("");
}

void CMyMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LKP, m_lKp);
	DDX_Text(pDX, IDC_LKI, m_lKi);
	DDX_Text(pDX, IDC_LKD, m_lKd);
	DDX_Text(pDX, IDC_LA, m_la);
	DDX_Text(pDX, IDC_LS, m_ls);
	DDX_Text(pDX, IDC_RKP, m_rKp);
	DDX_Text(pDX, IDC_RKI, m_rKi);
	DDX_Text(pDX, IDC_RKD, m_rKd);
	DDX_Text(pDX, IDC_RA, m_ra);
	DDX_Text(pDX, IDC_RS, m_rs);
	DDX_Text(pDX, IDC_LEFTSPEED, m_fLeftSpeed);
	DDX_Text(pDX, IDC_RIGHTSPEED, m_fRightSpeed);
	DDV_MinMaxFloat(pDX, m_fLeftSpeed, -2.5f, 2.5f);
	DDV_MinMaxFloat(pDX, m_fRightSpeed, -2.5f, 2.5f);
	DDX_Text(pDX, IDC_EdtImg, m_EdtImg);
	DDX_Text(pDX, IDC_EdtRe, m_EdtRe);


	DDX_Text(pDX, IDC_EdtIP, m_CstrIP);
	DDX_Text(pDX, IDC_ClientIP, cstrClientIP);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_B, m_UltraSonic_B);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_F, m_UltraSonic_F);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_FL, m_UltraSonic_FL);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_FR, m_UltraSonic_FR);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_L, m_UltraSonic_L);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_R, m_UltraSonic_R);
	DDX_Text(pDX, IDC_EDIT_PSD_B, m_PSD_B);
	DDX_Text(pDX, IDC_EDIT_PSD_F, m_PSD_F);
	DDX_Text(pDX, IDC_EDIT_PSD_FL, m_PSD_FL);
	DDX_Text(pDX, IDC_EDIT_PSD_FR, m_PSD_FR);
	DDX_Text(pDX, IDC_EDIT_PSD_L, m_PSD_L);
	DDX_Text(pDX, IDC_EDIT_PSD_R, m_PSD_R);
}

BEGIN_MESSAGE_MAP(CMyMotionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_FORWARD, OnBnClickedForward)
	ON_BN_CLICKED(IDC_BACKWARD, OnBnClickedBackward)
	ON_BN_CLICKED(IDC_LEFT, OnBnClickedLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnBnClickedRight)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDC_CHECK_VELOCITY, OnBnClickedCheckVelocity)
	ON_BN_CLICKED(IDC_CHECK_POSITION, OnBnClickedCheckPosition)
	ON_BN_CLICKED(IDC_CHECK_CORRESPOND, OnBnClickedCheckCorrespond)
	ON_BN_CLICKED(IDC_CHECK_PID, OnBnClickedCheckPid)
	ON_BN_CLICKED(IDC_CHECK_DEBUGPID, OnBnClickedCheckDebugpid)
	ON_BN_CLICKED(IDC_CHECK_LOADPID, OnBnClickedCheckLoadpid)
	ON_BN_CLICKED(IDC_CHECK_SAVEPID, OnBnClickedCheckSavepid)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPID, OnBnClickedButtonSavepid)
	ON_BN_CLICKED(IDC_BUTTON_LOOK, OnBnClickedButtonLook)
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BtnRC, &CMyMotionDlg::OnBnClickedBtnrc)
	ON_BN_CLICKED(IDC_BtnIP, &CMyMotionDlg::OnBnClickedBtnip)
	ON_MESSAGE(WM_USER_THREAD,OnMyMessage)
END_MESSAGE_MAP()


// CMyMotionDlg ��Ϣ�������

BOOL CMyMotionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	::CreateDirectory("c:\\Data",NULL);//�����ļ���
	ofstream outlv("c:\\Data\\lv.txt");
	ofstream outrv("c:\\Data\\rv.txt");
	ofstream outld("c:\\Data\\ld.txt");
	ofstream outrd("c:\\Data\\rd.txt");
	ofstream outla("c:\\Data\\la.txt");
	ofstream outra("c:\\Data\\ra.txt");
	if(!BuildSystem())//����ϵͳ
	{
		return FALSE;
	}

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CMyMotionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyMotionDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CMyMotionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMyMotionDlg::BuildSystem(void)
{
	for (int i=0;i<16;i++) m_fDis[i] = 100 ;
	try
	{
		CreateDevice("MOTION",m_pDevMotion);// ���ݸ������豸���ƴ�����Ӧ�豸
		//���������ɹ�����������豸�ӿڸ�ֵ����һ����������Ҫ�������豸����
		//�����˶��豸����Ϊ��MOTION���ڶ����������������豸�ӿ�
		//������ӿں�����
		m_pDevMotion->Init(); //��ʼ������
		AddMsgReceiver(m_pDevMotion); // ����ǰ�豸�����û�������豸�б�
		m_pDevMotion->QueryInterface(InterfaceID_MOTION, (LPVOID*)&m_pMotion);//��ѯ����ʵ�ֵĽӿڡ���һ����������Ӧ�ӿڱ�ʶ��
		//�ڶ�����������Ӧ�豸�����ַ�����豸����ʧ�ܣ�����NULL��

		CreateDevice("MTULTRASONIC",sonarDev);//���������������豸
		AddMsgReceiver(sonarDev);
		sonarDev->QueryInterface(InterfaceID_ULTRASONIC, (LPVOID*)&m_pSonar);
		m_pSonar->SetSonarProc(RecvProc,(LPVOID*)this) ;

		CreateDevice("MTPSD",m_PSDDev);//��������������豸
		AddMsgReceiver(m_PSDDev);
		m_PSDDev->QueryInterface(InterfaceID_PSD, (LPVOID*)&m_pPSD);
		m_pPSD->SetPSDProc(PSD_RecvProc,(LPVOID*)this);

		Broadcast(NTY_MSG_DEV_PTR, sonarDev,pGlobalDevLst);
		Broadcast(NTY_MSG_DEV_PTR, m_PSDDev,pGlobalDevLst);

		SetTimer(1,100,0);

		m_proc = PIDFunc;
		m_pMotion->SetMotionProc(m_proc,this);//Set event handling process

		CreateDevice("MTENCODER",m_pDevEncoder);//�����������豸�ӿ�  �������̶�λϵͳ
		m_pDevEncoder->Init();
		AddMsgReceiver(m_pDevEncoder);
		m_pDevEncoder->QueryInterface(InterfaceID_ENCODER,(LPVOID*)&m_pEncoder);

		m_EncoderProc = EncoderProcFun;
		m_pEncoder->SetEncoderProc(m_EncoderProc,this);

		//����һ������EncoderDisProcFunָ�룬�ú������յ��¼��󣬽��ɸ�ָ��ָ��ĺ�������
		m_EncoderDisProc = EncoderDisProcFun;
		m_pEncoder->SetEncoderDisProc(m_EncoderDisProc,this);
		if (m_pEncoder)
		{
			m_pEncoder->EncoderDis();//����������λ��
		}

	}
	catch (IngeniousException& e)
	{
		Cleanup();//����������쳣ʱ��ֹͣ�����ٴ�����ָ��
		String16 str16;
		char strTchar[256];
		str16 = e.GetErrorMessage();
		setlocale(LC_CTYPE,"");
		wcstombs(strTchar, str16.c_str(), 256);
		MessageBox(strTchar, "ERROR", MB_OK);
		return 1;
	}
	UpdateData(TRUE);
// 	/*********************
// 	��ȡ����IP��ַ(CString)
// 	*********************/
// 	char name[255];
// 	PHOSTENT hostinfo;
// 	if( gethostname ( name, sizeof(name)) == 0)
// 	{
// 		if((hostinfo = gethostbyname(name)) != NULL)
// 		{
// 			m_CstrIP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
// 		}
// 	}

	return 0;
}

int CMyMotionDlg::DestroySystem(void)
{
	try
	{
		KillTimer(1);
		if(m_pMotion)
		{
			m_pMotion->End();              //ֹͣʹ���˶��豸
			m_pMotion->Release();          //�ͷŻ����˶����ƽӿ�
			m_pMotion = NULL;
		}
		if (m_pEncoder)
		{
			m_pEncoder->Release();
			m_pEncoder = NULL;
		}
	}
	catch(IngeniousException& e)
	{
		String16 str16;
		char strTchar[256];
		str16 = e.GetErrorMessage();
		setlocale(LC_CTYPE,"");
		wcstombs(strTchar, str16.c_str(), 256);
		MessageBox(strTchar, "ERROR", MB_OK);
		return -1;
	}
	return 0;
}

void CMyMotionDlg::OnDestroy()
{
	CDialog::OnDestroy();
	DestroySystem();
	// TODO: �ڴ˴������Ϣ����������
}

//������ԭ�ȵ��ƶ���ʽ
void CMyMotionDlg::Move(float lSpeed, int lKp,int lKi,int lKd,float la,float ls,float rSpeed,int rKp,int rKi,int rKd,float ra,float rs)
{
	UpdateData(TRUE);
	static CString s1;
	char s[256];	
	if (m_ModeSelect+m_ModeSelect1==4)
	{
		MessageBox("��ѡ���ٶȱջ���λ�ñջ�!");
	}
	if (!IsDlgButtonChecked(IDC_CHECK_PID)&&!IsDlgButtonChecked(IDC_CHECK_DEBUGPID)&&!IsDlgButtonChecked(IDC_CHECK_LOADPID))
	{
		m_PidSelect = 1;
	}
	if (!IsDlgButtonChecked(IDC_CHECK_VELOCITY)&&!IsDlgButtonChecked(IDC_CHECK_POSITION)&&!IsDlgButtonChecked(IDC_CHECK_CORRESPOND)&&!IsDlgButtonChecked(IDC_CHECK_SAVEPID)) 
	{
		m_ModeSelect = 1;
		m_ModeSelect1 = 0;
	}
	sprintf(s,"%d%d%f%f%d%d%d%d%d%d%f%f%f%f",m_ModeSelect+m_ModeSelect1, m_PidSelect,lSpeed,rSpeed,lKp,lKi,lKd,rKp,rKi,rKd,la,ls,ra,rs);
	if (s1!=s)
	{
		m_CurrentTimer = m_t;
		m_CurrentLD = ld_basic;
		m_CurrentRD = rd_basic;
	}
	s1 = s;
	ASSERT(m_pMotion);	
	if (m_pMotion)
	{
		m_pMotion->drive(m_ModeSelect+m_ModeSelect1, m_PidSelect,lSpeed, lKp, lKi, lKd, la, ls,  rSpeed, rKp, rKi, rKd, ra, rs);
		//����1��1Ϊ�ٶȱջ�������2��1ΪĬ��PID������3�������ٶȣ�����4��
		//����Pֵ������5������Iֵ������6������Dֵ������7�����ּ��ٶȣ�
		//����8������λ�ƣ�����9�������ٶȣ�����10������Pֵ��
		//����11������Iֵ������12������Dֵ������13�����ּ��ٶȣ�����14������λ�ƣ�
	}
}

//���еĻ����˵��ƶ���ʽ  �����������
void CMyMotionDlg::robotmove(float lSpeed, float la,float rSpeed,float ra)
{
	ASSERT(m_pMotion);	
	if (m_pMotion)
	{
		m_pMotion->drive(1,1,lSpeed, 0,0,0, la, 0, rSpeed, 0,0,0, ra,0);
		//����1��1Ϊ�ٶȱջ�������2��1ΪĬ��PID������3�������ٶȣ�����4��
		//����Pֵ������5������Iֵ������6������Dֵ������7�����ּ��ٶȣ�
		//����8������λ�ƣ�����9�������ٶȣ�����10������Pֵ��
		//����11������Iֵ������12������Dֵ������13�����ּ��ٶȣ�����14������λ�ƣ�
	}
}


void CMyMotionDlg::Cleanup(void)
{
	if(m_pMotion)
	{
		m_pMotion->End();
		m_pMotion->Release();        
		m_pMotion = NULL;
	}
}

void CMyMotionDlg::OnBnClickedForward()
{
	UpdateData(TRUE);
	m_fLv = m_fLeftSpeed;
	m_fRv = m_fRightSpeed;
	Move(m_fLv, m_lKp,m_lKi,m_lKd,m_la,m_ls,m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs); 

}

void CMyMotionDlg::OnBnClickedBackward()
{
	UpdateData(TRUE);
	m_fLv = -m_fLeftSpeed;
	m_fRv = -m_fRightSpeed;
	Move(m_fLv,  m_lKp,m_lKi,m_lKd,m_la,m_ls, m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs);
}

void CMyMotionDlg::OnBnClickedLeft()
{
	UpdateData(TRUE);
	m_fLv = -m_fLeftSpeed;
	m_fRv = m_fRightSpeed;
	Move(m_fLv, m_lKp,m_lKi,m_lKd,m_la,m_ls, m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs);
}

void CMyMotionDlg::OnBnClickedRight()
{
	UpdateData(TRUE);
	m_fLv = m_fLeftSpeed;
	m_fRv = -m_fRightSpeed;
	Move(m_fLv,  m_lKp,m_lKi,m_lKd,m_la,m_ls, m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs);
}

void CMyMotionDlg::OnBnClickedStop()
{
	m_fLv = 0.0f;
	m_fRv = 0.0f;
	Move(0.0f,m_lKp,m_lKi,m_lKd,m_la,m_ls,0.0f,m_rKp,m_rKi,m_rKd,m_ra,m_rs);


	//KillTimer(1);
}

void CMyMotionDlg::OnBnClickedCheckVelocity()
{
	if (IsDlgButtonChecked(IDC_CHECK_VELOCITY))
	{
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(FALSE);//disable IDC_CHECK_POSITION
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_LS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_ModeSelect = 1;
	}
	else
	{
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LS)->EnableWindow(TRUE);
		GetDlgItem(IDC_RS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
		m_ModeSelect = 0;
	}
}

void CMyMotionDlg::OnBnClickedCheckPosition()
{
	if (IsDlgButtonChecked(IDC_CHECK_POSITION))
	{
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_ModeSelect = 2;
	}
	else
	{
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
		m_ModeSelect = 0;
	}
}

void CMyMotionDlg::OnBnClickedCheckCorrespond()
{
	if (IsDlgButtonChecked(IDC_CHECK_CORRESPOND))
	{
		if (IsDlgButtonChecked(IDC_CHECK_POSITION))
		{
			m_ModeSelect1 = 4;
		}
		else if (IsDlgButtonChecked(IDC_CHECK_VELOCITY))
		{
			m_ModeSelect1 = 4;
		}
		else
		{
			MessageBox("��ѡ���ٶȱջ���λ�ñջ�");
		}
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
	}
	else
	{
		m_ModeSelect1 = 0;
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckPid()
{
	if (IsDlgButtonChecked(IDC_CHECK_PID))
	{
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_LKP)->EnableWindow(FALSE);
		GetDlgItem(IDC_LKI)->EnableWindow(FALSE);
		GetDlgItem(IDC_LKD)->EnableWindow(FALSE);
		GetDlgItem(IDC_RKP)->EnableWindow(FALSE);
		GetDlgItem(IDC_RKI)->EnableWindow(FALSE);
		GetDlgItem(IDC_RKD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);	
		m_PidSelect = 1;
	}
	else
	{
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LKP)->EnableWindow(TRUE);
		GetDlgItem(IDC_LKI)->EnableWindow(TRUE);
		GetDlgItem(IDC_LKD)->EnableWindow(TRUE);
		GetDlgItem(IDC_RKP)->EnableWindow(TRUE);
		GetDlgItem(IDC_RKI)->EnableWindow(TRUE);
		GetDlgItem(IDC_RKD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckDebugpid()
{
	if (IsDlgButtonChecked(IDC_CHECK_DEBUGPID))
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_PidSelect = 2;
	}
	else
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckLoadpid()
{
	if (IsDlgButtonChecked(IDC_CHECK_LOADPID))
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_PidSelect = 4;
	}
	else
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckSavepid()
{
	if (IsDlgButtonChecked(IDC_CHECK_SAVEPID))
	{
		m_ModeSelect = 8;
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CORRESPOND)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_LEFTSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_RIGHTSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_LA)->EnableWindow(FALSE);
		GetDlgItem(IDC_LS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RA)->EnableWindow(FALSE);
		GetDlgItem(IDC_RS)->EnableWindow(FALSE);
		GetDlgItem(IDC_FORWARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BACKWARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_CORRESPOND)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LEFTSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_RIGHTSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_LA)->EnableWindow(TRUE);
		GetDlgItem(IDC_LS)->EnableWindow(TRUE);
		GetDlgItem(IDC_RA)->EnableWindow(TRUE);
		GetDlgItem(IDC_RS)->EnableWindow(TRUE);
		GetDlgItem(IDC_FORWARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BACKWARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_LEFT)->EnableWindow(TRUE);
		GetDlgItem(IDC_RIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
	}
}

void CMyMotionDlg::OnBnClickedButtonSavepid()
{
	UpdateData(TRUE);
	m_pMotion->drive(m_ModeSelect, 0,0.0f, m_lKp, m_lKi, m_lKd, 0.0f, 0.0f, 0.0f, m_rKp, m_rKi, m_rKd, 0.0f, 0.0f);
}

void CMyMotionDlg::OnBnClickedButtonLook()
{
	if (m_pMotion)
	{
		m_pMotion->EnableMotion(1,1);//Check PID Parameters
	}
}

void __stdcall CMyMotionDlg::PIDFunc(void* pParam, UInt8 LP, UInt8 LI,UInt8 LD,UInt8 RP,UInt8 RI,UInt8 RD)
{
	CMyMotionDlg *pThis = (CMyMotionDlg*)pParam;
	CSingleLock sLock(&(pThis->m_Mutex));
	sLock.Lock();
	char s[256];
	sprintf(s,"%s%d","����PֵΪ:",LP);
	pThis->GetDlgItem(IDC_STATIC_LP)->SetWindowText(s);
	sprintf(s,"%s%d","����IֵΪ:",LI);
	pThis->GetDlgItem(IDC_STATIC_LI)->SetWindowText(s);
	sprintf(s,"%s%d","����DֵΪ:",LD);
	pThis->GetDlgItem(IDC_STATIC_LD)->SetWindowText(s);
	sprintf(s,"%s%d","����PֵΪ:",RP);
	pThis->GetDlgItem(IDC_STATIC_RP)->SetWindowText(s);
	sprintf(s,"%s%d","����IֵΪ:",RI);
	pThis->GetDlgItem(IDC_STATIC_RI)->SetWindowText(s);
	sprintf(s,"%s%d","����DֵΪ:",RD);
	pThis->GetDlgItem(IDC_STATIC_RD)->SetWindowText(s);
	pThis->m_lKp=LP;
	pThis->m_lKi=LI;
	pThis->m_lKd=LD;
	pThis->m_rKp=RP;
	pThis->m_rKi=RI;
	pThis->m_rKd=RD;
	sLock.Unlock();
}

//��������ʾ����
void _stdcall CMyMotionDlg::EncoderDisProcFun(void *pParam, float32* value, UInt16 num)
{
	CMyMotionDlg *pThis = (CMyMotionDlg*)pParam;
	CSingleLock sLock(&(pThis->m_Mutex));
	sLock.Lock();
	pThis->m_fEncoderDis[num] = *value;//�������λ�Ʒֱ�Ϊ�������λ�ơ��������λ�ơ�x�����λ�ơ�y�����λ�ƣ�x����ǰ��y������
	if(num==3)
	{
		pThis->on_odo();
	}
	sLock.Unlock();
}

//�����ص�����
void __stdcall CMyMotionDlg::RecvProc(void* pParam,float32* speed, UInt16 num)//�����ص�����
{
	CMyMotionDlg *dlg = (CMyMotionDlg*)pParam;
// 	CString strBuffer="";
// 	CSingleLock sLock(&(dlg->m_Mutex));
// 	sLock.Lock();
// 	strBuffer.Format("channels %d:%f",num,*value);
// 	sLock.Unlock();
//     dlg->AddToListBox(strBuffer);
	dlg->m_fDis[num] = (float)(*speed) ;

}

//����ص�����
void __stdcall CMyMotionDlg::PSD_RecvProc(void* pParam, float32* speed, UInt16 num)//����ص�����

{
	CMyMotionDlg *dlh = (CMyMotionDlg*)pParam;

	dlh->PSD_m_fDis[num] = (float)(*speed);

}

//������������
void _stdcall CMyMotionDlg::EncoderProcFun(void *pParam,float32* lvelocity, float32* rvelocity, float32* ldistance,float32* rdistance,float32 timer)
{
	CMyMotionDlg *pThis = (CMyMotionDlg*)pParam;
	CSingleLock sLock(&(pThis->m_Mutex));
	sLock.Lock();
	static float32 lvelocity0 = 0.0f;//ǰһʱ��������
	static float32 rvelocity0 = 0.0f;//ǰһʱ��������
	static int t=0;//ʱ�䳬��8���ӵ�������ʱ��һ����������洢������

	float32 lv_basic = 0.0f;//���������ٶ�
	float32 rv_basic = 0.0f;//���������ٶ�
	float32 la_basic = 0.0f;//�����������ٶ�
	float32 ra_basic = 0.0f;//�����������ٶ�

	static float32 ld_basic1 = 0.0f;//���ּ��ٻ����ʱ�߹���λ��
	float32 ld_basic2 = 0.0f;//��������ʱ��λ��
	static float32 rd_basic1 = 0.0f;//���ּ��ٻ����ʱ�߹���λ��
	float32 rd_basic2 = 0.0f;//��������ʱ��λ��
	float32 la;//���ּ��ٶ�
	float32 ra;//���ּ��ٶ�
	la = ((*lvelocity)-lvelocity0)/timer;
	ra = ((*rvelocity)-rvelocity0)/timer; 
	if (la>5)//�����˳�ƫ������ֵ
	{
		la =pThis->m_la;
	}
	if (ra>5)
	{
		ra =pThis->m_ra;
	}
	lvelocity0 = *lvelocity;
	rvelocity0 = *rvelocity;
	m_t +=timer;//m_tΪ����ʱ��ֵ��timerΪ��һʱ�̲ɼ�����һʱ�̲ɼ�֮��Ĳ�ֵ
	pThis->m_fEncoder[0] = *lvelocity;
	pThis->m_fEncoder[1] = *rvelocity; 
	pThis->m_fEncoder[2] = *ldistance;
	pThis->m_fEncoder[3] = *rdistance; 
	pThis->m_fEncoder[4] = m_t; 

	//ʵ�ʻ����˵��ٶ���Ϣ
	pThis->V1 = *lvelocity;  //�����ٶ�
	pThis->V2 = *rvelocity;//�����ٶ�
	pThis->S1 = *ldistance;//����λ��
	pThis->S2 = *rdistance;  //����λ��
	pThis->acc1 = la; //���ּ��ٶ�
	pThis->acc2 = ra; //���ּ��ٶ�

	pThis->EncodeTime = m_t;  //�����������е�ʱ��
	char s[256];
	sprintf(s,"%.2f",pThis->m_fEncoderDis[0]);
	pThis->GetDlgItem(IDC_EDIT_LDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoderDis[1]);
	pThis->GetDlgItem(IDC_EDIT_RDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoderDis[2]);
	pThis->GetDlgItem(IDC_EDIT_XDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoderDis[3]);
	pThis->GetDlgItem(IDC_EDIT_YDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[0]);
	pThis->GetDlgItem(IDC_EDIT_V1)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[1]);
	pThis->GetDlgItem(IDC_EDIT_V2)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[2]);
	pThis->GetDlgItem(IDC_EDIT_D1)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[3]);
	pThis->GetDlgItem(IDC_EDIT_D2)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[4]);
	if (m_t>480*t&&m_t<483*t)//���8���Ӻ�����ļ�����
	{
		t++;
		outlv.close();
		outrv.close();
		outld.close();
		outrd.close();
		outla.close();
		outra.close();
		outlv.open("C:\\Data\\lv.txt");
		outrv.open("C:\\Data\\rv.txt");
		outld.open("C:\\Data\\ld.txt");
		outrd.open("C:\\Data\\rd.txt");
		outla.open("C:\\Data\\la.txt");
		outra.open("C:\\Data\\ra.txt");
	}
	else
	{
		float ttl=0.0f;
		float ttr=0.0f;
		static float m_fLv1 =0.0f;//��һʱ�������ٶ�ֵ
		static float m_fRv1 =0.0f;//��һʱ�������ٶ�ֵ
		ttl=(abs)(pThis->m_fLv)/pThis->m_la;//���ٻ���ٵ����������ٶ�ֵʱ��ʱ��

		if (m_t<=ttl||pThis->m_fLv!=m_fLv1||pThis->m_fRv!=m_fRv1)//��ʱ��û�е�������ʱ����ٶȸı�ʱ
		{
			if (pThis->m_fLv>m_fLv1)
			{
				lv_basic = m_fLv1+(m_t-pThis->m_CurrentTimer)*pThis->m_la;//���������ٶ�
			}
			else if (pThis->m_fLv>m_fLv1)
			{
				lv_basic = m_fLv1-(m_t-pThis->m_CurrentTimer)*pThis->m_la;
			}
			else if (pThis->m_fLv==m_fLv1)
			{
				if (pThis->m_fLv>=0)
				{
					lv_basic = (m_t-pThis->m_CurrentTimer)*pThis->m_la;
				}
				else
				{
					lv_basic = -(m_t-pThis->m_CurrentTimer)*pThis->m_la;
				}

			}
			la_basic = pThis->m_la;
			ld_basic1 = pThis->m_CurrentLD+0.5*pThis->m_la*(m_t-pThis->m_CurrentTimer)*(m_t-pThis->m_CurrentTimer);
		}
		else
		{
			lv_basic = pThis->m_fLv;
			la_basic = 0;
			ld_basic2 = pThis->m_fLv*(m_t-pThis->m_CurrentTimer);
		}
		m_fLv1 = pThis->m_fLv;
		ld_basic = ld_basic1+ld_basic2;
		outlv<<(*lvelocity)<<" "<<(*lvelocity)-lv_basic<<" "<<m_t<<" "<<lv_basic<<endl;//���������ٶȲ���ֵ��
		//��һ��Ϊʵ���ٶ�ֵ���ڶ���Ϊ���ֵ��������Ϊʱ�䣬���ĸ�Ϊ�����ٶ�ֵ
		outla<<la<<" "<<la-la_basic<<" "<<m_t<<" "<<la_basic<<endl;//�������ּ��ٶȲ���ֵ��
		//��һ��Ϊʵ�ʼ��ٶ�ֵ���ڶ���Ϊ���ֵ��������Ϊʱ�䣬���ĸ�Ϊ�������ٶ�ֵ
		outld<<(*ldistance)<<" "<<(*ldistance)-ld_basic<<" "<<m_t<<" "<<ld_basic<<endl;//��������λ�Ʋ���ֵ��
		//��һ��Ϊʵ��λ��ֵ���ڶ���Ϊ���ֵ��������Ϊʱ�䣬���ĸ�Ϊ����λ��ֵ

		ttr=pThis->m_fRv/pThis->m_ra;//���ٻ���ٵ����������ٶ�ֵʱ��ʱ��
		if (m_t<=ttr||pThis->m_fRv!=m_fRv1||pThis->m_fLv!=m_fLv1)
		{
			if (pThis->m_fRv>m_fRv1)
			{
				rv_basic = m_fRv1+(m_t-pThis->m_CurrentTimer)*pThis->m_ra;
			}
			else if (pThis->m_fRv>m_fRv1)
			{
				rv_basic = m_fRv1-(m_t-pThis->m_CurrentTimer)*pThis->m_ra;
			}
			else if (pThis->m_fRv==m_fRv1)
			{
				if (pThis->m_fRv>=0)
				{
					rv_basic = (m_t-pThis->m_CurrentTimer)*pThis->m_ra;
				}
				else
				{
					rv_basic = -(m_t-pThis->m_CurrentTimer)*pThis->m_ra;
				}
			}
			ra_basic = pThis->m_ra;
			rd_basic1 = pThis->m_CurrentRD+0.5*pThis->m_ra*(m_t-pThis->m_CurrentTimer)*(m_t-pThis->m_CurrentTimer);
		}
		else
		{
			rv_basic = pThis->m_fRv;
			ra_basic = 0;
			rd_basic2 = pThis->m_fRv*(m_t-pThis->m_CurrentTimer);
		}
		m_fRv1 = pThis->m_fRv;
		rd_basic = rd_basic1+rd_basic2;
		outrv<<(*rvelocity)<<" "<<(*rvelocity)-rv_basic<<" "<<m_t<<" "<<rv_basic<<endl;//���������ٶȲ���ֵ��
		//��һ��Ϊʵ���ٶ�ֵ���ڶ���Ϊ���ֵ��������Ϊʱ�䣬���ĸ�Ϊ�����ٶ�ֵ
		outra<<ra<<" "<<ra-ra_basic<<" "<<m_t<<" "<<ra_basic<<endl;//�������ּ��ٶȲ���ֵ��
		//��һ��Ϊʵ�ʼ��ٶ�ֵ���ڶ���Ϊ���ֵ��������Ϊʱ�䣬���ĸ�Ϊ�������ٶ�ֵ
		outrd<<(*rdistance)<<" "<<(*rdistance)-rd_basic<<" "<<m_t<<" "<<rd_basic<<endl;//��������λ�Ʋ���ֵ��
		//��һ��Ϊʵ��λ��ֵ���ڶ���Ϊ���ֵ��������Ϊʱ�䣬���ĸ�Ϊ����λ��ֵ
	}
	sLock.Unlock();
}

void CMyMotionDlg::on_odo()
{

	char str[256];
	DWORD t;
	unsigned int timestamp;
	static double x=posandnav.robpos.laser_pose.x,y=posandnav.robpos.laser_pose.y,r=posandnav.robpos.laser_pose.rot;
	t = GetTickCount();
	static unsigned int prevtime = t;
	timestamp = t;
	// ȡ���̷��������ӵ� odo����ϵͳʱ���timestamp
	if(fabs(m_fEncoderDis[0])<0.1&&fabs(m_fEncoderDis[0])>0.0&&fabs(m_fEncoderDis[1])>0.0&&fabs(m_fEncoderDis[1])<0.1)
	{
		double dr = (m_fEncoderDis[1] - m_fEncoderDis[0]) / WHEELWIDTH;
		if (r > PI)
			r -= 2*PI; 
		else if (r <= -PI)
			r += 2*PI;
		double s = sin(r);
		double c = cos(r);
		x += (m_fEncoderDis[2] * c - m_fEncoderDis[3] * s);
		y += (m_fEncoderDis[2] * s + m_fEncoderDis[3] * c);
		r += dr;
		posandnav.on_odo(Pose2d(x,y,r), timestamp);
	}
}

void CMyMotionDlg::OnBnClickedButtonDetadis()
{
	if (m_pEncoder)
	{
		m_pEncoder->EncoderDis();
	}
}




void CMyMotionDlg::update()
{
	UpdateData(TRUE);
	m_theta = theta;
	m_thetaR = thetaR;
	m_Wr = Wr;
	m_V21 = Vd;
	m_V22 = Y;
	m_Vr = e3;
	m_Xr = Xr;
	m_Yr = Yr;
	m_e1 = e1;
	m_e2 = e2;
	m_e3 = e3;
	UpdateData(FALSE);
}

void CMyMotionDlg::delay()
{
	//UpdateData(TRUE);

	if(delaycount == 10)
		delaycount = 0;
	else
		delaycount++;

}
void CMyMotionDlg::movetotarget(int count)
{
	UpdateData(TRUE);
	if(count>10)
		count =0;
	else
	{
		if(count<=10)
		{
			Move(m_fLeftSpeed, m_lKp,m_lKi,m_lKd,m_la,m_ls,m_fRightSpeed,m_rKp,m_rKi,m_rKd,m_ra,m_rs); //ǰ��
		}
		else
		{		
			Move(0, m_lKp,m_lKi,m_lKd,m_la,m_ls,0,m_rKp,m_rKi,m_rKd,m_ra,m_rs); 
			KillTimer(2);		
		}
	}
}

BOOL CMyMotionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam) 
		{
		case 'W':
			GetDlgItem(IDC_FORWARD )->SetFocus();
			OnBnClickedForward();
			UpdateData(FALSE);
			return TRUE;
			break;
		case 'S':
			GetDlgItem(IDC_BACKWARD)->SetFocus();
			OnBnClickedBackward();
			UpdateData(FALSE);
			return TRUE;
			break;
		case 'A':
			GetDlgItem(IDC_LEFT)->SetFocus();
			OnBnClickedLeft();
			UpdateData(FALSE);
			return TRUE;
			break;
		case 'D':
			GetDlgItem(IDC_RIGHT)->SetFocus();
			OnBnClickedRight();
			UpdateData(FALSE);
			return TRUE;
			break;			
		case VK_RETURN:
			UpdateData(FALSE);
			return TRUE;
			break;
		case VK_SPACE:
			GetDlgItem(IDC_STOP)->SetFocus();
			OnBnClickedStop();
			UpdateData(FALSE);
			return TRUE;
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
} 

void CMyMotionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	fL = m_fDis[LEFTCHANNEL];
	fR = m_fDis[RIGHTCHANNEL];
	fF = m_fDis[FRONTCHANNEL];


	if(PSD_m_fDis[0]<40) PSD_FM=1;   else PSD_FM=0;
	if(PSD_m_fDis[2]<40) PSD_FL1=1;  else PSD_FL1=0;
	if(PSD_m_fDis[4]<40) PSD_FL2=1;  else PSD_FL2=0;
	if(PSD_m_fDis[7]<40) PSD_BM=1;   else PSD_BM=0;
	if(PSD_m_fDis[10]<40) PSD_FR2=1; else PSD_FR2=0;
	if(PSD_m_fDis[12]<40) PSD_FR1=1; else PSD_FR1=0;

	//m_pEncoder->EncoderDis();
	CurrentAngel=posandnav.robpos.robot_pose.rot*180.0/PI;
	switch(nIDEvent)
	{
	case 1:
		{
			update();
			break;
		}

	case 2:
		{
			framecount++;
			movetotarget(framecount);
			break;
		}
	case 3:
		{				
			delay();
			break;
		}
	default:
		break;

	}
	CDialog::OnTimer(nIDEvent);
}




void CMyMotionDlg::OnBnClickedBtnrc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*UpdateData();
	if( m_bSonar )
	{	

	m_pSonar->OpenChannel(0);
	m_pSonar->OpenChannel(2);
	m_pSonar->OpenChannel(4);
	m_pSonar->OpenChannel(7);
	m_pSonar->OpenChannel(10);
	m_pSonar->OpenChannel(12);

	m_pPSD->OpenChannel(0);
	m_pPSD->OpenChannel(2);
	m_pPSD->OpenChannel(4);
	m_pPSD->OpenChannel(10);
	m_pPSD->OpenChannel(7);
	m_pPSD->OpenChannel(12);


	}
	else
	{
	m_iState = 1;
	for (int i=0;i<16;i++) m_fDis[i] = 100 ;

	m_pSonar->CloseChannel(0);
	m_pSonar->CloseChannel(2);
	m_pSonar->CloseChannel(4);
	m_pSonar->CloseChannel(7);
	m_pSonar->CloseChannel(10);
	m_pSonar->CloseChannel(21);

	m_pPSD->CloseChannel(0);
	m_pPSD->CloseChannel(2);
	m_pPSD->CloseChannel(4);
	m_pPSD->CloseChannel(7);
	m_pPSD->CloseChannel(10);
	m_pPSD->CloseChannel(12);
	}*/
	/*UpdateData(false);*/
	UpdateData(TRUE);
	AfxBeginThread(ThreadCmd,this);
	/***************************************/
// 	AfxBeginThread(ThreadImgRecv,this);
// 	AfxBeginThread(ThreadImgLocalRecv,this);
// 	AfxBeginThread(ThreadImg,this);
	/***************************************/
	AfxBeginThread(ThreadImgRtpSending,this);
	AfxBeginThread(ThreadImgRtpReceiving,this);
	
	/***************************************/
	m_EdtImg="Video Transmission";
	UpdateData(FALSE);

	//UpdateData(TRUE);
	//SetTimer(1,100,	NULL);

	////SetTimer(1,100,	TimerProc);
	////���������ڴ� ��ʼ����

	////Turn_Angel(90);
	//posandnav.robpos.robot_pose.x=0;//���û����˳�ʼλ��
	//posandnav.robpos.robot_pose.y=0;

	////ToPositionPD(1,0);
	//Turn_Angel(90);
	/*AfxBeginThread(ThreadDetecting,this);*/
	//AfxBeginThread(ThreadImg,NULL);
}


void CMyMotionDlg::OnBnClickedBtnip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	/*********************
	��ȡ����IP��ַ(CString)
	*********************/
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	CString ip;
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );

	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}

		WSACleanup( );
	}
	m_CstrIP=ip;
	UpdateData(FALSE);
}
afx_msg LRESULT CMyMotionDlg::OnMyMessage(WPARAM wParam,LPARAM lParam)
{
	UpdateData(TRUE);
	m_EdtRe=g_Commands;
	UpdateData(FALSE);
	if(strcmp(g_Commands, "left")==0)
	{
		OnBnClickedLeft();
	}
	else if(strcmp(g_Commands, "right")==0)
	{
		OnBnClickedRight();
	}
	else if(strcmp(g_Commands, "forward")==0)
	{
		OnBnClickedForward();
	}
	else if(strcmp(g_Commands, "backward")==0)
	{
		OnBnClickedBackward();
	}
	else if(strcmp(g_Commands, "stop")==0)
	{
		OnBnClickedStop();
	}
// 	else 
// 	{
// 		OnBnClickedStop();
// 	}
	return 0;
}
void CMyMotionDlg::DrawPicToHDC(IplImage *img, UINT ID)
{	CDC *pDC = GetDlgItem(ID)->GetDC(); 
HDC hDC= pDC->GetSafeHdc(); 
CRect rect; 
GetDlgItem(ID)->GetClientRect(&rect); 
CvvImage cimg; 
cimg.CopyOf(img); 
cimg.DrawToHDC(hDC,&rect); 
ReleaseDC(pDC); 
}

void CMyMotionDlg::DrawPicToHDC(Mat img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	IplImage pimg = IplImage(img); //Mat convto IplImage
	cimg.CopyOf(&pimg,1);           // ����ͼƬ
	cimg.DrawToHDC( hDC, &rect ); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
}
bool CMyMotionDlg::Turn_Angel(float angel)
{
	float angel_original=CurrentAngel;
	if(angel>0)//��ת
	{

		while(1)
		{

			Move(0.15,-0.15); 
			if(abs(CurrentAngel-angel_original)>=abs(angel))
			{Move(0,0);
			break;}

		}
	}

	else   //��ת
	{           
		while(1)
		{   
			Move(-0.15,0.15);
			if(abs(CurrentAngel-angel_original)>abs(angel))
			{Move(0,0);
			break;}
		}


	}


	return 0;
}


void CMyMotionDlg::Move(float left, float right,float a)
{
	static CString s1;
	char s[256];
	sprintf(s,"%f %f %f",left,right,a);
	ASSERT(m_pMotion);
	if (s1!=s)
	{
		if ( m_pMotion )
		{
			m_pMotion->drive(1, 1,left, 0, 0, 0, a, 0,  right, 0, 0, 0, a, 0);
		}
	}
	s1=s;
}
void CMyMotionDlg::Move(float lv,float rv)
{
	if (fabs(lv)>1.0||fabs(rv)>1.0)
	{
		AfxMessageBox("�ٶ�ֵ�������Χֵ",MB_OK);
	}
	else
	{
		static CString s1;
		char s[256];
		sprintf(s,"%f %f",lv,rv);
		ASSERT(m_pMotion);
		if (s1!=s)
		{
			if (m_pMotion)
			{
				m_pMotion->drive(1,1,lv,0,0,0,0.5,0,rv,0,0,0,0.5,0);
			}
		}
		s1=s;
	}

}