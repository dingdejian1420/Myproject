// DialogLOGCFG.cpp : 实现文件
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogLOGCFG.h"
#include "afxdialogex.h"


// CDialogLOGCFG 对话框

IMPLEMENT_DYNAMIC(CDialogLOGCFG, CDialogEx)

CDialogLOGCFG::CDialogLOGCFG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogLOGCFG::IDD, pParent)
{

}

CDialogLOGCFG::~CDialogLOGCFG()
{
}

void CDialogLOGCFG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogLOGCFG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CDialogLOGCFG::OnBnClickedButtonOpenFile)
END_MESSAGE_MAP()


// CDialogLOGCFG 消息处理程序


void CDialogLOGCFG::OnBnClickedButtonOpenFile()
{
	// TODO:  在此添加控件通知处理程序代码
	CString FilePath;
	CFileDialog fileDlg(true);

	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	fileDlg.m_ofn.lpstrTitle = "打开Logging文件夹";
	fileDlg.m_ofn.lpstrFilter = "Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		FilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_LOG_FILEPATH, FilePath);

		dlg->m_LogFilePath = FilePath;
	}

}


BOOL CDialogLOGCFG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	SetDlgItemText(IDC_EDIT_LOG_FILEPATH, dlg->m_LogFilePath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
