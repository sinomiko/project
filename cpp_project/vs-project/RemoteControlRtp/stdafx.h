// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// ��Ŀ�ض��İ����ļ�

#pragma once
#pragma warning(disable:4081)
#pragma warning(disable:4101)
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#pragma warning(disable:4996)
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0500		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0500		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0510 //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
#define _WIN32_IE 0x0500	//Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ��������������ȫ���Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����
#include <afxsock.h>
#include <WinSock2.h>
#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

//MTSOFT Include
#include "globalDef.h"   //ȫ�ֶ���ͷ�ļ�
#include "MTSystem.h"   //ϵͳͷ�ļ�
#include "MTDevice.h"   //�豸ͷ�ļ�
#include "MTConfig.h"   //ϵͳ����ͷ�ļ�
#include "IMTMotion.h"        //�˶��ӿ�ͷ�ļ�
#include "Ingenious.h"        //�������Ͷ���
#include "IngeniousException.h" //�쳣����
#include "IMTEncoder.h"
#include "IMTImageProcess.h"
#include "IMTImageCapture.h"
#include "IMTNetwork.h"
#include "IMTvoice.h"
#include "IMTUltraSonic.h"
#include "IMTPSD.h"
#include "IMotionDecision.h"
#include "IMTPosNav.h"
class CMTSystem;   //ϵͳ��
interface IMTMotion;  //�˶��ӿ�
interface IMotionDecision;
interface IMTUltraSonic;
#define FRONTCHANNEL		0
#define LEFTCHANNEL			2
#define RIGHTCHANNEL		12

#define Avoid_FM 0
#define Avoid_FL1 2
#define Avoid_FL2 4
#define Avoid_FR1 12
#define Avoid_FR2 10
#define Avoid_BM 7
#define WHEELWIDTH 0.399
#include <fstream>
#include <afxcontrolbars.h>

//���opencv��ͷ�ļ�
// #include<opencv\cv.h>
// #include<opencv\highgui.h>
// #include<opencv\cxcore.h>
// #include<opencv\cvaux.h>
#include<opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <afxsock.h>
#include<iostream>
#include "CvvImage.h"
using namespace cv;
using namespace std;
