// DialogLOGCFG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogLOGCFG.h"
#include "afxdialogex.h"


// CDialogLOGCFG �Ի���

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


// CDialogLOGCFG ��Ϣ�������


void CDialogLOGCFG::OnBnClickedButtonOpenFile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString FilePath;
	CFileDialog fileDlg(true);

	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	fileDlg.m_ofn.lpstrTitle = "��Logging�ļ���";
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	SetDlgItemText(IDC_EDIT_LOG_FILEPATH, dlg->m_LogFilePath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
