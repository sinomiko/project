#include "stdafx.h"

#include "MyMotion.h"
#include "MyMotionDlg.h"
//#include ".\mymotiondlg.h"


CvPoint RPoint[100000];

CvBox2D End_Rage2D;
CvBox2D End_Rage2D1;
CvBox2D Pre_Rage2D;
float PI = 3.1415926;
//float sum = 0;
CvPoint2D32f point4[4];
float Wsum;
float w;
CvSeq *robotcontour = NULL;


void CMyMotionDlg::imageContour(IplImage* src,int framecount)
{
	//src->origin = 1;  //����ṹ
	//src->origin = 0;  //����ṹ
	//update();
	Pre_Rage2D = End_Rage2D;
	IplImage *dsw = cvCreateImage(cvGetSize(src),8,1);
	cvCvtColor(src,dsw,CV_BGR2GRAY);
	IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);  
	IplImage* Trajectory = cvCreateImage(cvGetSize(src),8,3);
	CvMemStorage *storage = cvCreateMemStorage(0);  
	CvSeq *first_contour = NULL;  

	dst->origin = 1;  //����Ϊԭ��
	Trajectory->origin = 1;

	cvThreshold(dsw, dsw, 100, 255, CV_THRESH_BINARY_INV); 
//	cvShowImage("dsw",dsw);
	cvDilate(dsw,dsw,NULL,2);
	cvErode(dsw,dsw,NULL,2);
	cvFindContours(dsw, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);  
	cvZero(dst);
	double maxarea=1500;
	double minarea=100;
	int center_x[20];
	int center_y[20];
	int cnt = 0; 
	
	//������ϵ
	cvLine(dst,cvPoint(0,0),cvPoint(640,0),CV_RGB(255,0,0),2,8,0);
	cvLine(dst,cvPoint(0,0),cvPoint(0,480),CV_RGB(255,0,0),2,8,0);
	cvLine(Trajectory,cvPoint(0,0),cvPoint(640,0),CV_RGB(255,0,0),2,8,0);
	cvLine(Trajectory,cvPoint(0,0),cvPoint(0,480),CV_RGB(255,0,0),2,8,0);


	for(; first_contour != 0; first_contour = first_contour->h_next)  
	{  
		double tmparea=fabs(cvContourArea(first_contour));  
		
		if(tmparea > maxarea)   
		{  			
			cvSeqRemove(first_contour,0); //ɾ����������趨ֵ������  
		    continue;  
		} 
		if(tmparea < minarea)   
		{  
			cvSeqRemove(first_contour,0); //ɾ�����С���趨ֵ������  
			continue;  
		} 				
		cnt++;	
		CvScalar color = CV_RGB(rand()&255, rand()&255, rand()&255);  
		cvDrawContours(dst, first_contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0));

	//	CvRect rect = cvBoundingRect(first_contour,0);		
		if(tmparea>100&&tmparea<400)
		{			
			End_Rage2D1 = cvMinAreaRect2(first_contour);   //�����˽Ƕ�			
		}
		if(tmparea>500&&tmparea<1400)
		{
			End_Rage2D = cvMinAreaRect2(first_contour);
		}		
	}
	if(cnt == 2)
	{
		X = End_Rage2D.center.x;
		Y = End_Rage2D.center.y;
		X1 = End_Rage2D1.center.x;
		Y1 = End_Rage2D1.center.y;
		

		//ԭ��
		cvLine(Trajectory,cvPoint(0,py),cvPoint(636,py),CV_RGB(255, 0, 0),2,8,0);
		cvLine(Trajectory,cvPoint(px,0),cvPoint(px,482),CV_RGB(0, 255, 0),2,8,0);
		cvLine(dst,cvPoint(0,py),cvPoint(636,py),CV_RGB(255, 0, 0),2,8,0);
		cvLine(dst,cvPoint(px,0),cvPoint(px,482),CV_RGB(0, 255, 0),2,8,0);

		cvLine(dst,cvPoint(0,Y),cvPoint(dst->width,Y),CV_RGB(255, 0, 0),2,8,0);
		cvLine(dst,cvPoint(X,0),cvPoint(X,dst->width),CV_RGB(255, 0, 0),2,8,0);
		cvLine(dst,cvPoint(0,Y1),cvPoint(dst->width,Y1),CV_RGB(255, 0, 0),2,8,0);
		cvLine(dst,cvPoint(X1,0),cvPoint(X1,dst->width),CV_RGB(255, 0, 0),2,8,0);

		cvBoxPoints(End_Rage2D,point4);   //cvBoxPoints�����������ε�4����������
		CvPoint pt[4];
		for(int i = 0;i<4;i++)
			pt[i] = cvPoint((int)point4[i].x,(int)point4[i].y);   //��CvPoint2D32f���͵ĵ�ת��ΪCvPoint����
		CvPoint* ppt = pt;
		int count = 4;
		cvPolyLine(Trajectory,&ppt,&count,1,1,CV_RGB(0,0,255),4,8,0);  //������

		////������
		//cvRectangle(dst, cvPoint(X,Y), cvPoint(X + End_Rage2D.size.width,Y + End_Rage2D.size.height),CV_RGB(255, 0, 0), 2, 8, 0);
		//cvRectangle(dst, cvPoint(X1,Y1), cvPoint(X1 + End_Rage2D1.size.width,Y1 + End_Rage2D1.size.height),CV_RGB(255, 0, 0), 2, 8, 0);
	
	}		
		cvShowImage("dst",dst);	
		
		RPoint[framecount] = cvPoint(X,Y);	//ʵ�ʵĹ켣			
		for(int i = 1 ;i<framecount;i++)
		{			
			cvLine(Trajectory,RPoint[i-1],RPoint[i],CV_RGB(255,255,0),2,8,0); 	
		}
    
 		CvFont font;
 		cvInitFont(&font,CV_FONT_HERSHEY_COMPLEX,0.5f,0.5f,1,1,8);
 	    cvPutText(Trajectory,"RealRobot",cvPoint(X1,Y1),&font,CV_RGB(255,0,0));
		cvCircle(Trajectory,cvPoint(277,178),100,cvScalar(0,0,0),4,8,0);
		// targetTrajectory(framecount);
	    targetRobot(Trajectory,framecount);
		////robotdrawline(Trajectory,Pre_Rage2D,End_Rage2D);
		cvShowImage("Trajectory",Trajectory);				
		RobotControl(framecount);
	//	robotcontrolorigion(framecount);
		
	//}
cvReleaseImage(&dsw);
cvReleaseImage(&Trajectory);
cvReleaseImage(&dst);
cvReleaseMemStorage(&storage);
}


