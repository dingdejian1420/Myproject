
// CAN_ToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CAN_Tool.h"
#include "CAN_ToolDlg.h"
#include "afxdialogex.h"

#include "ControlCAN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCAN_ToolDlg 对话框



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


// CCAN_ToolDlg 消息处理程序

BOOL CCAN_ToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCAN_ToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCAN_ToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCAN_ToolDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	VCI_OpenDevice(1,1,1);
	CDialogEx::OnOK();
}


void CCAN_ToolDlg::OnCANConfig()
{
	// TODO:  在此添加命令处理程序代码

	 
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
}


void CCAN_ToolDlg::OnLoggingStop()
{
	// TODO:  在此添加命令处理程序代码
}


void CCAN_ToolDlg::OnBnClickedButtonConnect()
{
	// TODO:  在此添加控件通知处理程序代码
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
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("连接");
		VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
		return;
	}

	VCI_INIT_CONFIG init_config;
	init_config.Mode = m_WorkMode;

	if (VCI_OpenDevice(m_CANDevType, m_CANDevIndex, 0) != STATUS_OK)
	{
		MessageBox("打开设备失败!", "警告", MB_OK | MB_ICONQUESTION);
		return;
	}
	if (VCI_SetReference(m_CANDevType, m_CANDevIndex, m_CANChannel, 0, &m_CANBuard) != STATUS_OK)
	{
		MessageBox(_T("设置波特率错误，打开设备失败!"), _T("警告"), MB_OK | MB_ICONQUESTION);
		VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
		return;
	}
	if (VCI_InitCAN(m_CANDevType, m_CANDevIndex, m_CANChannel, &init_config) != STATUS_OK)
	{
		MessageBox("初始化CAN失败!", "警告", MB_OK | MB_ICONQUESTION);
		VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
		return;
	}

/**********************************   滤波设置   ************************************/
	VCI_FILTER_RECORD filterRecord;
	if (m_FilterMode != 2)
	{
		filterRecord.ExtFrame = m_FilterMode;
		filterRecord.Start = 0;
		filterRecord.End = 1;

		if (filterRecord.Start>filterRecord.End)
		{
			MessageBox(_T("滤波范围起始ID不应该大于结束ID!"), _T("警告"), MB_OK | MB_ICONQUESTION);
			VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
			return;
		}
		//填充滤波表格
		VCI_SetReference(m_CANDevType, m_CANDevIndex, m_CANChannel, 1, &filterRecord);
		//使滤波表格生效
		if (VCI_SetReference(m_CANDevType, m_CANDevIndex, m_CANChannel, 2, NULL) != STATUS_OK)
		{
			MessageBox(_T("设置滤波失败!"), _T("警告"), MB_OK | MB_ICONQUESTION);
			VCI_CloseDevice(m_CANDevType, m_CANDevIndex);
			return;
		}
	}

	m_Connect = TRUE;
	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("断开");

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
	// TODO:  在此添加控件通知处理程序代码
	if (m_Connect == 0)
		return;
	if (VCI_StartCAN(m_CANDevType, m_CANDevIndex, m_CANChannel) == 1)
	{
		MessageBox("启动成功", 0);
	}
	else
	{
		CString str;
		str = "启动失败";
		MessageBox(str);
	}
}


void CCAN_ToolDlg::OnBnClickedButtonReset()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_Connect == 0)
		return;
	if (VCI_ResetCAN(m_CANDevType, m_CANDevIndex, m_CANChannel) == 1)
	{
		//GetDlgItem(IDC_BUTTON_STARTCAN)->EnableWindow(true);
		MessageBox("复位成功");
	}
	else
	{
		CString str;
		str = "复位失败";
		MessageBox(str);
	}
}
