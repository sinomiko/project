// MyMotionDlg.h : ͷ�ļ�
#include "stdafx.h"

#pragma once
#include "afxmt.h"
#include "afxwin.h"
#define WM_USER_THREAD WM_USER+1
static CString g_Commands; 
using namespace std;
using namespace cv;
// CMyMotionDlg �Ի���
class CMyMotionDlg : public CDialog
{
// ����
public:
	CMyMotionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYMOTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int BuildSystem(void);
	int DestroySystem(void);
	void Cleanup(void);
	afx_msg void OnDestroy();
public:
	int m_lKp;
	int m_lKi;
	int m_lKd;
	float m_la;
	float m_ls;
	int m_rKp;
	int m_rKi;
	int m_rKd;
	float m_ra;
	float m_rs;
public:
	int m_ModeSelect;
	int m_PidSelect;
	int m_ModeSelect1;
	void Move(float lSpeed, int lKp,int lKi,int lKd,float la,float ls,float rSpeed,int rKp,int rKi,int rKd,float ra,float rs);

	afx_msg void OnBnClickedForward();
	afx_msg void OnBnClickedBackward();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedCheckVelocity();
	afx_msg void OnBnClickedCheckPosition();
	afx_msg void OnBnClickedCheckCorrespond();
	afx_msg void OnBnClickedCheckPid();
	afx_msg void OnBnClickedCheckDebugpid();
	afx_msg void OnBnClickedCheckLoadpid();
	afx_msg void OnBnClickedCheckSavepid();
	afx_msg void OnBnClickedButtonSavepid();
	afx_msg void OnBnClickedButtonLook();
	CMutex m_Mutex;
	DeviceMotionProc m_proc;
	DeviceEncoderProc m_EncoderProc;

	float m_fLeftSpeed;
	float m_fRightSpeed;
	float m_fLv;
	float m_fRv;
	int m_ClrState;
	float e_la;
	float e_ra;
	float m_CurrentTimer;
	float m_CurrentLD;
	float m_CurrentRD;
	afx_msg void OnBnClickedButtonDetadis();
	float m_fEncoder[5];
public:
	void targetRobot(IplImage* img,int i);
	void targetTrajectory(int framecount);
	void update();
	void robotmove(float lSpeed, float la,float rSpeed,float ra);
	void robotdrawline(IplImage* img,CvBox2D pre_Rage2D,CvBox2D End_Rage2D);
	void movetotarget(int count);
	void robotController(float lSpeed,float rSpeed,float acce);
	void delay();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ����������x�᷽���ٶ�
	float Vrx;
	// ����������y�᷽���ٶ�
	float Vry;
	// ͼ����ʵ�ʻ����˵�X��λ��
	float X;
	// ͼ����ʵ�ʻ����˵�Y��λ��
	float Y;
	// ͼ����ʵ�ʻ����˷����
	float theta;
	// ��һ֡ͼ��ʵ�ʻ����˵�X������
	float PreXd;
	// ��һ֡ͼ��ʵ�ʻ�����Y�������
	float PreYd;
	// ʵ�ʻ����˵Ľ��ٶ�
	float Wd;
	// ʵ�ʻ����˵����ٶ�
	float Vd;
	// ��������˵����ٶ�
	float Vr;
	// ��������˵Ľ��ٶ�
	float Wr;
	// �����õ��Ļ����˵����ٶ�
	float V;
	// �����õ��Ļ����˵Ľ��ٶ�   ͨ��������
	float W;
	// cvWaitKey�ĵȴ�ʱ��
	int WaitTime;
	// ��һ֡ͼ��ʵ�ʻ��������������ٶ�
	float PreVd;
	// ��һ֡ͼ��ʵ�ʻ����������Ľ��ٶ�
	float PreWd;
	// ���������˵ķ����
	float thetaR;
	// �ο������˵���������X
	float Xr;
	// �ο������˵���������Y
	float Yr;
	// ����
	float e1;
	float e2;
	float e3;
	// ��������ϵ�²�����ֵ��������ֵ�Ĳ�
	float N1;
	float N2;
	// ����
	float T1;
	// ��������
	float T2;
	// ת������
	float I;
	// �����ٶ�
	float V1;
	// �����ٶ�
	float V2;
	// ���������ӵİ뾶
	float r;
	// ���������ּ�ľ���
	float R;
	afx_msg void OnBnClickedButtonopencamera();
	float m_Vr;
	float m_Wr;
	float m_X;
	float m_Xr;
	float m_Y;
	float m_Yr;
	float m_theta;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	// ���Գ������
	int m;
	int md;
	int n;
	int nd;
	// ��Ƶ֡��
	int framecount;
	float m_thetaR;
	float m_T1;
	float m_T2;
	// ���ֻ���
	float S1;
	// ���ֻ���
	float S2;
	float m_V21;
	float m_V22;
	// �����������е�ʱ��
	float EncodeTime;
	// ����ת����Բ�Ľ�
	float alfa1;
	// ����ת����Բ�Ľ�
	float alfa2;
	// ���ּ��ٶ�
	float acc1;
	// ���ּ��ٶ�
	float acc2;
	float X1;
	float X2;
	float Y1;
	float px;
	float py;
	float m_e1;
	float m_e2;
	float m_e3;
	afx_msg void OnBnClickedBtnrc();
	CString m_EdtImg;
	CString m_EdtRe;
	CEdit m_Commands;
	CEdit m_EdtCMD;
	CString m_CstrIP;
	afx_msg void OnBnClickedBtnip();
	afx_msg LRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
	void DrawPicToHDC(IplImage *img, UINT ID);
	void DrawPicToHDC(Mat img, UINT ID);
	int m_iState;
	public:
		IMTDevice* m_pDevMotion;//�˶������豸
		IMTMotion* m_pMotion;

		IMTDevice* sonarDev;//���������豸
		IMTUltraSonic* m_pSonar;

		IMTDevice* m_PSDDev;//PSD�����豸
		IMTPSD* m_pPSD;

		IMTDevice* m_pDevEncoder;//�����������豸
		IMTEncoder* m_pEncoder;
		DeviceProc m_EncoderDisProc;

		imtposnav::RangeData range;
		imtposnav::IMTPosNav posandnav;
		float m_fDis[16] ;//���������෵��ֵ
		float PSD_m_fDis[16];//��ź����෵��ֵ
		float m_fEncoderDis[8];//��ű���������ֵ
		int num;
		int m_bSonar;
		float m_fRobotSpeed;
		void* pGlobalDevLst;

	CString cstrClientIP;
	CString m_UltraSonic_B;
	CString m_UltraSonic_F;
	CString m_UltraSonic_FL;
	CString m_UltraSonic_FR;
	CString m_UltraSonic_L;
	CString m_UltraSonic_R;
	CString m_PSD_B;

		float fF;
		float fL;
		float fR;


		//��������ֵ �Ƿ����ϰ���  �� Ϊ1   û��  Ϊ 0
		int PSD_FM;
		int PSD_FL1;
		int PSD_FL2;
		int PSD_FR1;
		int PSD_FR2;
		int PSD_BM;

		int UltraSonic_FM;
		int UltraSonic_FL1;
		int UltraSonic_FL2;
		int UltraSonic_FR1;
		int UltraSonic_FR2;
		int UltraSonic_BM;

public:
	CString m_PSD_F;
	CString m_PSD_FL;
	CString m_PSD_FR;
	CString m_PSD_L;
	CString m_PSD_R;
public:
	static void __stdcall RecvProc(void* pParam, float32* speed, UInt16 num);//�������ص�����
	static void __stdcall PSD_RecvProc(void* pParam, float32* speed, UInt16 num);//����ص�����
	static void _stdcall EncoderDisProcFun(void *pParam, float32* value, UInt16 num);//�������ص�����
	static void _stdcall EncoderProcFun(void *pParam,float32* lvelocity, float32* rvelocity, float32* ldistance,float32* rdistance,float32 timer);
//    static void _stdcall EncoderProcFun(void *pParam,float32* lvelocity, float32* rvelocity, float32* ldistance,float32* rdistance,float32 timer);
	
	static void __stdcall PIDFunc(void* pParam, UInt8 LP, UInt8 LI,UInt8 LD,UInt8 RP,UInt8 RI,UInt8 RD);
	bool Turn_Angel(float angel);//ת��Ƕ�
	void Move(float left, float right,float a);//ʹ���˶��ĺ���
	void Move(float lv,float rv);//ʹ���˶��ĺ���
   
	void on_odo();
};