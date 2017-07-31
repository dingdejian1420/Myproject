// DialogCANCFG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "DialogCANCFG.h"
#include "afxdialogex.h"
#include "CAN_ToolDlg.h"
#include "ControlCAN.h"

extern const DWORD GCanBrTab[10];
// CDialogCANCFG �Ի���

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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



	m_ComboFilterMode.AddString("��׼֡�˲�");
	m_ComboFilterMode.AddString("��չ֡�˲�");
	m_ComboFilterMode.AddString("�˲���");

	m_ComboWorkMode.AddString("����ģʽ");
	m_ComboWorkMode.AddString("ֻ��ģʽ");

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
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// CDialogCANCFG ��Ϣ�������

void CDialogCANCFG::OnCbnSelchangeComboCantype()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogCANCFG::OnCbnSelchangeComboCanindex()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogCANCFG::OnCbnSelchangeComboCanchannel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogCANCFG::OnCbnSelchangeComboCanbuard()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogCANCFG::OnCbnSelchangeComboFiltertype()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


