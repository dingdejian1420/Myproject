
// CAN_Tool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCAN_ToolApp: 
// �йش����ʵ�֣������ CAN_Tool.cpp
//

class CCAN_ToolApp : public CWinApp
{
public:
	CCAN_ToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCAN_ToolApp theApp;