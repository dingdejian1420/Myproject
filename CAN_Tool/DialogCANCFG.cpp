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
	ON_CBN_SELCHANGE(IDC_COMBO_WORKMODE, &CDialogCANCFG::OnCbnSelchangeComboWorkmode)
	ON_BN_CLICKED(IDOK, &CDialogCANCFG::OnBnClickedOk)
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

	m_ComboBaud.AddString("1000kbps");
	m_ComboBaud.AddString("800kbps");
	m_ComboBaud.AddString("500kbps");
	m_ComboBaud.AddString("250kbps");
	m_ComboBaud.AddString("125kbps");
	m_ComboBaud.AddString("100kbps");
	m_ComboBaud.AddString("50kbps");
	m_ComboBaud.AddString("20kbps");
	m_ComboBaud.AddString("10kbps");
	m_ComboBaud.AddString("5kbps");

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
	switch (dlg->m_BuardIndex)
	{
	case 0:m_ComboBaud.SetCurSel(0);  break;
	case 1:m_ComboBaud.SetCurSel(1);  break;
	case 2:m_ComboBaud.SetCurSel(2);  break;
	case 3:m_ComboBaud.SetCurSel(3);  break;
	case 4:m_ComboBaud.SetCurSel(4);  break;
	case 5:m_ComboBaud.SetCurSel(5);  break;
	case 6:m_ComboBaud.SetCurSel(6);  break;
	case 7:m_ComboBaud.SetCurSel(7);  break;
	case 8:m_ComboBaud.SetCurSel(8);  break;
	case 9:m_ComboBaud.SetCurSel(9);  break;
	default: break;
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
	CCAN_ToolDlg *dlg;
	int i;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	i = m_ComboDevType.GetCurSel();

	if (i == 0)
	{
		dlg->m_CANDevType = VCI_PCI5010U;
	}
	else if (i == 1)
	{
		dlg->m_CANDevType = VCI_USBCAN_E_U;
	}
	else if (i == 2)
	{
		dlg->m_CANDevType = VCI_USBCAN_2E_U;
	}
	else if (i == 3)
	{
		dlg->m_CANDevType = VCI_PCI5020U;
	}
	else
	{
	}
}


void CDialogCANCFG::OnCbnSelchangeComboCanindex()
{
	// TODO:  在此添加控件通知处理程序代码
	CCAN_ToolDlg *dlg;
	int i;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	i = m_ComboDevIndex.GetCurSel();

	dlg->m_CANDevIndex = i;
}


void CDialogCANCFG::OnCbnSelchangeComboCanchannel()
{
	// TODO:  在此添加控件通知处理程序代码
	CCAN_ToolDlg *dlg;
	int i;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	i = m_ComboChannel.GetCurSel();

	dlg->m_CANChannel = i;
}


void CDialogCANCFG::OnCbnSelchangeComboCanbuard()
{
	// TODO:  在此添加控件通知处理程序代码
	CCAN_ToolDlg *dlg;
	int i;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	i = m_ComboBaud.GetCurSel();

	dlg->m_BuardIndex = i;
}


void CDialogCANCFG::OnCbnSelchangeComboFiltertype()
{
	// TODO:  在此添加控件通知处理程序代码
	CCAN_ToolDlg *dlg;
	int i;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	i = m_ComboFilterMode.GetCurSel();

	dlg->m_FilterMode = i;
}




void CDialogCANCFG::OnCbnSelchangeComboWorkmode()
{
	// TODO:  在此添加控件通知处理程序代码
	CCAN_ToolDlg *dlg;
	int i;
	HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	dlg = (CCAN_ToolDlg *)FromHandle(hwnd);
	i = m_ComboWorkMode.GetCurSel();

	dlg->m_WorkMode = i;
}


void CDialogCANCFG::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//m_CANDevType = VCI_USBCAN_2E_U;
	//m_CANDevIndex = 0;
	//m_CANChannel = 0;

	//m_CANBuard = GCanBrTab[2];//500kbp
	//m_sendTimeout = 100;

	//m_WorkMode = 0;//0： 正常模式 1：只听模式
	//m_FilterMode = 0;//0: 标准帧滤波 1:扩展帧滤波 2:禁止滤波
	CString str;
	if (m_ComboDevType.GetCurSel() == 0)
	{
		str.Format("%d", VCI_PCI5010U);
	}
	else if (m_ComboDevType.GetCurSel() == 1)
	{
		str.Format("%d", VCI_USBCAN_E_U);
	}
	else if (m_ComboDevType.GetCurSel() == 2)
	{
		str.Format("%d", VCI_USBCAN_2E_U);
	}
	else if (m_ComboDevType.GetCurSel() == 3)
	{
		str.Format("%d", VCI_PCI5020U);
	}
	else
	{
	}
	::WritePrivateProfileString(("CAN Config value"), ("Type"), (str), (".//CANparaSet.cfg"));
	str.Format("%d", m_ComboDevIndex.GetCurSel());
	::WritePrivateProfileString(("CAN Config value"), ("Index"), (str), (".//CANparaSet.cfg"));
	str.Format("%d", m_ComboChannel.GetCurSel());
	::WritePrivateProfileString(("CAN Config value"), ("Channel"), (str), (".//CANparaSet.cfg"));
	str.Format("%d", m_ComboBaud.GetCurSel());
	::WritePrivateProfileString(("CAN Config value"), ("Buard"), (str), (".//CANparaSet.cfg"));
	str.Format("%d", m_ComboFilterMode.GetCurSel());
	::WritePrivateProfileString(("CAN Config value"), ("FilteMode"), (str), (".//CANparaSet.cfg"));
	str.Format("%d", m_ComboWorkMode.GetCurSel());
	::WritePrivateProfileString(("CAN Config value"), ("WorkMode"), (str), (".//CANparaSet.cfg"));
	//::WritePrivateProfileString(("CAN Config value"), ("LogFilePath"), (""), (".//CANparaSet.cfg"));

	CDialogEx::OnOK();
}
