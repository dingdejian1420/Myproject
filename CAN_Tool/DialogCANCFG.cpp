// DialogCANCFG.cpp : 实现文件
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogCANCFG.h"
#include "afxdialogex.h"
#include "CAN_ToolDlg.h"
#include "ControlCAN.h"

extern const DWORD GCanBrTab[10];
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

	DDX_Control(pDX, IDC_COMBO_CANTYPE, m_ComboDevType);
	DDX_Control(pDX, IDC_COMBO_CANINDEX, m_ComboDevIndex);
	DDX_Control(pDX, IDC_COMBO_CANCHANNEL, m_ComboChannel);
	DDX_Control(pDX, IDC_COMBO_CANBUARD, m_ComboBaud);
	DDX_Control(pDX, IDC_COMBO_FILTERTYPE, m_ComboFilterMode);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_ComboWorkMode);
}


BEGIN_MESSAGE_MAP(CDialogCANCFG, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_CANTYPE, &CDialogCANCFG::OnCbnSelchangeComboCantype)
	ON_CBN_SELCHANGE(IDC_COMBO_CANINDEX, &CDialogCANCFG::OnCbnSelchangeComboCanindex)
	ON_CBN_SELCHANGE(IDC_COMBO_CANCHANNEL, &CDialogCANCFG::OnCbnSelchangeComboCanchannel)
	ON_CBN_SELCHANGE(IDC_COMBO_CANBUARD, &CDialogCANCFG::OnCbnSelchangeComboCanbuard)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTERTYPE, &CDialogCANCFG::OnCbnSelchangeComboFiltertype)
END_MESSAGE_MAP()


BOOL CDialogCANCFG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	CCAN_ToolDlg *dlg;
	int i;
	CString tmpstr;

	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	//dlg = (CCAN_ToolDlg *)GetDlgItem(IDD_CAN_TOOL_DIALOG);
	// TODO:  在此添加额外的初始化
	m_ComboDevType.AddString("PCI_5010_U");
	m_ComboDevType.AddString("USBCAN_E_U");
	m_ComboDevType.AddString("USBCAN_2E_U");
	m_ComboDevType.AddString("PCI_5020_U");

	for (i = 0; i < 8; i++)
	{
		tmpstr.Format("%d",i);
		m_ComboDevIndex.AddString(tmpstr);
	}

	for (i = 0; i < 2; i++)
	{
		tmpstr.Format("%d", i);
		m_ComboChannel.AddString(tmpstr);
	}



	m_ComboFilterMode.AddString("标准帧滤波");
	m_ComboFilterMode.AddString("扩展帧滤波");
	m_ComboFilterMode.AddString("滤波关");

	m_ComboWorkMode.AddString("正常模式");
	m_ComboWorkMode.AddString("只听模式");

	/*************************************************************/
	if (dlg->m_CANDevType == VCI_PCI5010U)
	{
		m_ComboDevType.SetCurSel(0);
	}
	else if (dlg->m_CANDevType == VCI_USBCAN_E_U)
	{
		m_ComboDevType.SetCurSel(1);
	}
	else if (dlg->m_CANDevType == VCI_USBCAN_2E_U)
	{
		m_ComboDevType.SetCurSel(2);
	}
	else if (dlg->m_CANDevType == VCI_PCI5020U)
	{
		m_ComboDevType.SetCurSel(3);
	}
	else
	{
		m_ComboDevType.SetCurSel(2);
	}
	/*************************************************************/
	for (i = 0; i < 8; i++)
	{
		if (dlg->m_CANDevIndex == i)
		{
			m_ComboDevIndex.SetCurSel(i);
		}
	}
	/*************************************************************/
	if (dlg->m_CANChannel ==0 )
	{
		m_ComboChannel.SetCurSel(0);
	}
	else if (dlg->m_CANChannel == 1)
	{
		m_ComboChannel.SetCurSel(1);
	}
	else
	{
		m_ComboChannel.SetCurSel(0);
	}

	/*************************************************************/
	
	if (dlg->m_FilterMode == 0)
	{
		m_ComboFilterMode.SetCurSel(0);
	}
	else if (dlg->m_FilterMode == 1)
	{
		m_ComboFilterMode.SetCurSel(1);
	}
	else if (dlg->m_FilterMode == 2)
	{
		m_ComboFilterMode.SetCurSel(2);
	}
	else
	{
		m_ComboFilterMode.SetCurSel(2);
	}
	/*************************************************************/
	if (dlg->m_WorkMode == 0)
	{
		m_ComboWorkMode.SetCurSel(0);
	}
	else if (dlg->m_WorkMode == 1)
	{
		m_ComboWorkMode.SetCurSel(1);
	}
	else
	{
		m_ComboWorkMode.SetCurSel(0);
	}

	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

// CDialogCANCFG 消息处理程序

void CDialogCANCFG::OnCbnSelchangeComboCantype()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogCANCFG::OnCbnSelchangeComboCanindex()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogCANCFG::OnCbnSelchangeComboCanchannel()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogCANCFG::OnCbnSelchangeComboCanbuard()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogCANCFG::OnCbnSelchangeComboFiltertype()
{
	// TODO:  在此添加控件通知处理程序代码
}


