
// QQbomb.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQQbombApp: 
// �йش����ʵ�֣������ QQbomb.cpp
//

class CQQbombApp : public CWinApp
{
public:
	CQQbombApp();

// ��д
public:
	virtual BOOL InitInstance();
	
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQQbombApp theApp;