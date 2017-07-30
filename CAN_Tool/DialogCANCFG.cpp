// DialogCANCFG.cpp : 实现文件
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogCANCFG.h"
#include "afxdialogex.h"


// CDialogCANCFG 对话框

IMPLEMENT_DYNAMIC(CDialogCANCFG, CDialogEx)

CDialogCANCFG::CDialogCANCFG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogCANCFG::IDD, pParent)
{

}

CDialogCANCFG::~CDialogCANCFG()
{
}

void CDialogCANCFG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogCANCFG, CDialogEx)
END_MESSAGE_MAP()


// CDialogCANCFG 消息处理程序
