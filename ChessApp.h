
// ChessApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChessAppApp:
// �йش����ʵ�֣������ ChessApp.cpp
//

class CChessAppApp : public CWinApp
{
public:
	CChessAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChessAppApp theApp;