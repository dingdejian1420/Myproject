// DialogLOGCFG.cpp : 实现文件
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogLOGCFG.h"
#include "afxdialogex.h"

extern int SampleCount;
extern UINT LoggingID[];
// CDialogLOGCFG 对话框

IMPLEMENT_DYNAMIC(CDialogLOGCFG, CDialogEx)

CDialogLOGCFG::CDialogLOGCFG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogLOGCFG::IDD, pParent)
{

	m_FocuseItem = 0;
}

CDialogLOGCFG::~CDialogLOGCFG()
{
}

void CDialogLOGCFG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG_INFO, m_ListLogIDInfo);

	DDX_Text(pDX, IDC_EDIT_LOGID, m_ID);
	DDX_Text(pDX, IDC_EDIT_LOGID_TIME, m_Time);
}


BEGIN_MESSAGE_MAP(CDialogLOGCFG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CDialogLOGCFG::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_ADDLOG, &CDialogLOGCFG::OnBnClickedButtonAddlog)
	ON_BN_CLICKED(IDC_BUTTON_DELLOG, &CDialogLOGCFG::OnBnClickedButtonDellog)
	ON_BN_CLICKED(IDOK_LOGSAVE, &CDialogLOGCFG::OnBnClickedLogsave)
	//ON_BN_CLICKED(IDOK, &CDialogCANCFG::OnBnClickedLogsave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LOG_INFO, &CDialogLOGCFG::OnNMClickListLogInfo)
END_MESSAGE_MAP()


// CDialogLOGCFG 消息处理程序


void CDialogLOGCFG::OnBnClickedButtonOpenFile()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(true);

	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	fileDlg.m_ofn.lpstrTitle = "打开Logging文件夹";
	fileDlg.m_ofn.lpstrFilter = "Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		m_FilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_LOG_FILEPATH, m_FilePath);

		dlg->m_LogFilePath = m_FilePath;
	}

}


BOOL CDialogLOGCFG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString tmpstr;
	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	SetDlgItemText(IDC_EDIT_LOG_FILEPATH, dlg->m_LogFilePath);

	tmpstr.Format("%d", dlg->m_LogTime);
	SetDlgItemText(IDC_EDIT_LOGID_TIME, tmpstr);

	m_FilePath = dlg->m_LogFilePath;
	LONG lStyle;
	lStyle = GetWindowLong(m_ListLogIDInfo.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_ListLogIDInfo.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_ListLogIDInfo.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_ListLogIDInfo.SetExtendedStyle(dwStyle); //设置扩展风格

	m_ListLogIDInfo.InsertColumn(0, "ID", LVCFMT_CENTER, 50);
	//m_ListLogIDInfo.InsertColumn(1, "周期", LVCFMT_CENTER, 50);

	for (int i = 0; i < SampleCount; i++)
	{
		tmpstr.Format("%03x", LoggingID[i]);
		m_ListLogIDInfo.InsertItem(i, tmpstr);
	}
	
	m_FocuseItem = -1;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialogLOGCFG::OnBnClickedButtonAddlog()
{
	// TODO:  在此添加控件通知处理程序代码
	int iPos;
	CString temp;
	UpdateData(true);
	GetDlgItemText(IDC_EDIT_LOGID, temp);
	iPos = m_ListLogIDInfo.InsertItem(SampleCount, temp);//每次添加都是count_points行

	//m_ListLogIDInfo.SetItemText(iPos, 1, m_Time);
	m_ID.Empty();
	UpdateData(false);
	SampleCount++;
}

void CDialogLOGCFG::OnBnClickedButtonDellog()
{
	// TODO:  在此添加控件通知处理程序代码
	
	if (m_FocuseItem != -1)
	{
		m_ListLogIDInfo.DeleteItem(m_FocuseItem);
		m_FocuseItem = -1;
		SampleCount--;
	}
}


void CDialogLOGCFG::OnBnClickedLogsave()
{
	CString tempstr, logtempstr;
	// TODO:  在此添加控件通知处理程序代码

	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	UpdateData(true);

	SampleCount = m_ListLogIDInfo.GetItemCount();

	for (int i = 0; i < SampleCount; i++)
	{
		tempstr = m_ListLogIDInfo.GetItemText(i, 0);
		LoggingID[i] = strtol(tempstr, NULL, 16);  //保存到全局变量

		tempstr += " ";
		logtempstr += tempstr;
	}


	dlg->m_LogTime = atoi(m_Time);

	::WritePrivateProfileString(("CAN Config value"), ("LogFilePath"), m_FilePath, (".//CANparaSet.cfg"));
	::WritePrivateProfileString(("CAN Config value"), ("LogTime"), m_Time, (".//CANparaSet.cfg"));
	::WritePrivateProfileString(("CAN Config value"), ("LogMsgID"), logtempstr, (".//CANparaSet.cfg"));
}



void CDialogLOGCFG::OnNMClickListLogInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	m_FocuseItem = pNMListView->iItem;

	*pResult = 0;
}
