// MyMotion.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#include "stdafx.h"
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMyMotionApp:
// �йش����ʵ�֣������ MyMotion.cpp
//

class CMyMotionApp : public CWinApp
{
public:
	CMyMotionApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyMotionApp theApp;
