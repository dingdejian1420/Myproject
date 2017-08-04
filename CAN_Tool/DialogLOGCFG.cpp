// DialogLOGCFG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogLOGCFG.h"
#include "afxdialogex.h"

extern int SampleCount;
extern UINT LoggingID[];
// CDialogLOGCFG �Ի���

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


// CDialogLOGCFG ��Ϣ�������


void CDialogLOGCFG::OnBnClickedButtonOpenFile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(true);

	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	fileDlg.m_ofn.lpstrTitle = "��Logging�ļ���";
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString tmpstr;
	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	SetDlgItemText(IDC_EDIT_LOG_FILEPATH, dlg->m_LogFilePath);

	tmpstr.Format("%d", dlg->m_LogTime);
	SetDlgItemText(IDC_EDIT_LOGID_TIME, tmpstr);

	m_FilePath = dlg->m_LogFilePath;
	LONG lStyle;
	lStyle = GetWindowLong(m_ListLogIDInfo.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_ListLogIDInfo.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_ListLogIDInfo.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_ListLogIDInfo.SetExtendedStyle(dwStyle); //������չ���

	m_ListLogIDInfo.InsertColumn(0, "ID", LVCFMT_CENTER, 50);
	//m_ListLogIDInfo.InsertColumn(1, "����", LVCFMT_CENTER, 50);

	for (int i = 0; i < SampleCount; i++)
	{
		tmpstr.Format("%03x", LoggingID[i]);
		m_ListLogIDInfo.InsertItem(i, tmpstr);
	}
	
	m_FocuseItem = -1;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDialogLOGCFG::OnBnClickedButtonAddlog()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int iPos;
	CString temp;
	UpdateData(true);
	GetDlgItemText(IDC_EDIT_LOGID, temp);
	iPos = m_ListLogIDInfo.InsertItem(SampleCount, temp);//ÿ����Ӷ���count_points��

	//m_ListLogIDInfo.SetItemText(iPos, 1, m_Time);
	m_ID.Empty();
	UpdateData(false);
	SampleCount++;
}

void CDialogLOGCFG::OnBnClickedButtonDellog()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CCAN_ToolDlg *dlg;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);

	UpdateData(true);

	SampleCount = m_ListLogIDInfo.GetItemCount();

	for (int i = 0; i < SampleCount; i++)
	{
		tempstr = m_ListLogIDInfo.GetItemText(i, 0);
		LoggingID[i] = strtol(tempstr, NULL, 16);  //���浽ȫ�ֱ���

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	m_FocuseItem = pNMListView->iItem;

	*pResult = 0;
}
