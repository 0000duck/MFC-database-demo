
// MFC database demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCdatabasedemoApp:
// �йش����ʵ�֣������ MFC database demo.cpp
//

class CMFCdatabasedemoApp : public CWinApp
{
public:
	CMFCdatabasedemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCdatabasedemoApp theApp;