
// CAN_ToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "CAN_ToolDlg.h"
#include "afxdialogex.h"

#include "ControlCAN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCAN_ToolDlg �Ի���



CCAN_ToolDlg::CCAN_ToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCAN_ToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_CANDevType = VCI_USBCAN_2E_U;
	m_CANDevIndex = 0;
	m_CANChannel = 0;

	m_CANBuard = 500;
	m_sendTimeout = 100;

	m_WorkMode = 1;
	m_FilterMode = 1;


	m_Connect = FALSE;
}

void CCAN_ToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCAN_ToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCAN_ToolDlg::OnBnClickedOk)
	ON_COMMAND(ID_MENU_CANCFG, &CCAN_ToolDlg::OnCANConfig)
	ON_COMMAND(ID_LOGGING_CFG, &CCAN_ToolDlg::OnLoggingConfig)
	ON_COMMAND(ID_LOGGING_START, &CCAN_ToolDlg::OnLoggingStart)
	ON_COMMAND(ID_LOGGING_STOP, &CCAN_ToolDlg::OnLoggingStop)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CCAN_ToolDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_START, &CCAN_ToolDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CCAN_ToolDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CCAN_ToolDlg ��Ϣ�������

BOOL CCAN_ToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCAN_ToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCAN_ToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCAN_ToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCAN_ToolDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	VCI_OpenDevice(1,1,1);
	CDialogEx::OnOK();
}


void CCAN_ToolDlg::OnCANConfig()
{
	// TODO:  �ڴ���������������

	 
	CDialogCANCFG dlg;
	//m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
}


void CCAN_ToolDlg::OnLoggingConfig()
{
	// TODO:  �ڴ���������������
	CDialogLOGCFG dlg;
	//m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
}


void CCAN_ToolDlg::OnLoggingStart()
{
	// TODO:  �ڴ���������������
}


void CCAN_ToolDlg::OnLoggingStop()
{
	// TODO:  �ڴ���������������
}


void CCAN_ToolDlg::OnBnClickedButtonConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Connect == TRUE)
	{
		m_Connect = FALSE;
		Sleep(500);
		//GetDlgItem(IDC_EDIT_BTR)->EnableWindow(!m_connect);
		//GetDlgItem(IDC_EDIT_STARTID)->EnableWindow(!m_connect);
		//GetDlgItem(IDC_EDIT_ENDID)->EnableWindow(!m_connect);
		//GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(!m_connect);
		//GetDlgItem(IDC_COMBO_FILTER)->EnableWindow(!m_connect);
		//GetDlgItem(IDC_COMBO_MODE)->EnableWindow(!m_connect);
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("����");
		VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
		return;
	}

	VCI_INIT_CONFIG init_config;
	init_config.Mode = m_WorkMode;

	if (VCI_OpenDevice(m_CANDevType, m_CANDevIndex, 0) != STATUS_OK)
	{
		MessageBox("���豸ʧ��!", "����", MB_OK | MB_ICONQUESTION);
		return;
	}
	if (VCI_SetReference(m_CANDevType, m_CANDevIndex, m_CANChannel, 0, &m_CANBuard) != STATUS_OK)
	{
		MessageBox(_T("���ò����ʴ��󣬴��豸ʧ��!"), _T("����"), MB_OK | MB_ICONQUESTION);
		VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
		return;
	}
	if (VCI_InitCAN(m_CANDevType, m_CANDevIndex, m_CANChannel, &init_config) != STATUS_OK)
	{
		MessageBox("��ʼ��CANʧ��!", "����", MB_OK | MB_ICONQUESTION);
		VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
		return;
	}

/**********************************   �˲�����   ************************************/
	VCI_FILTER_RECORD filterRecord;
	if (m_FilterMode != 2)
	{
		filterRecord.ExtFrame = m_FilterMode;
		filterRecord.Start = 0;
		filterRecord.End = 1;

		if (filterRecord.Start>filterRecord.End)
		{
			MessageBox(_T("�˲���Χ��ʼID��Ӧ�ô��ڽ���ID!"), _T("����"), MB_OK | MB_ICONQUESTION);
			VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
			return;
		}
		//����˲����
		VCI_SetReference(m_CANDevType, m_CANDevIndex, m_CANChannel, 1, &filterRecord);
		//ʹ�˲������Ч
		if (VCI_SetReference(m_CANDevType, m_CANDevIndex, m_CANChannel, 2, NULL) != STATUS_OK)
		{
			MessageBox(_T("�����˲�ʧ��!"), _T("����"), MB_OK | MB_ICONQUESTION);
			VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
			return;
		}
	}

	m_Connect = TRUE;
	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("�Ͽ�");

	m_pReceiveThread = AfxBeginThread(ReceiveThread, this);
}

UINT CCAN_ToolDlg::ReceiveThread(void *param)
{
	while (1)
	{
		Sleep(1);
	}
}

void CCAN_ToolDlg::OnBnClickedButtonStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Connect == 0)
		return;
	if (VCI_StartCAN(m_CANDevType, m_CANDevIndex, m_CANChannel) == 1)
	{
		MessageBox("�����ɹ�", 0);
	}
	else
	{
		CString str;
		str = "����ʧ��";
		MessageBox(str);
	}
}


void CCAN_ToolDlg::OnBnClickedButtonReset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Connect == 0)
		return;
	if (VCI_ResetCAN(m_CANDevType, m_CANDevIndex, m_CANChannel) == 1)
	{
		//GetDlgItem(IDC_BUTTON_STARTCAN)->EnableWindow(true);
		MessageBox("��λ�ɹ�");
	}
	else
	{
		CString str;
		str = "��λʧ��";
		MessageBox(str);
	}
}
