
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

const DWORD GCanBrTab[10] = {
	0x060003, 0x060004, 0x060007,
	0x1C0008, 0x1C0011, 0x160023,
	0x1C002C, 0x1600B3, 0x1C00E0,
	0x1C01C1
};


#define SampleNum  10
VCI_CAN_MSGDATA CanObj[SampleNum];
int SampleCount;
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

	CString strDevType;
	CString strDevIndex;
	CString strCANChannel;
	CString strWorkMode;
	CString strFilterType;
	CString strBuard;
	CString strLogFilePath;

	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(("CANparaSet.cfg"));
	if (ifFind)
	{
		//::WritePrivateProfileStringW(_T("Database connection Info"), _T("IP"), _T("10.210.0.9"), _T("d:\\RoadDataManagerApp.ini"));
		//::WritePrivateProfileStringW(_T("Database connection Info"), _T("Database"), _T("RoadNetData"), _T("d:\\RoadDataManagerApp.ini"));
		//::WritePrivateProfileStringW(_T("Database connection Info"), _T("UID"), _T("sa"), _T("d:\\RoadDataManagerApp.ini"));
		//::WritePrivateProfileStringW(_T("Database connection Info"), _T("PWD"), _T("4814278"), _T("d:\\RoadDataManagerApp.ini"));
		::GetPrivateProfileString(("CAN Config value"), ("Type"), ("没找到Type信息"), strDevType.GetBuffer(10), 10, (".//CANparaSet.cfg"));
		::GetPrivateProfileString(("CAN Config value"), ("Index"), ("没找到Index信息"), strDevIndex.GetBuffer(10), 10, (".//CANparaSet.cfg"));
		::GetPrivateProfileString(("CAN Config value"), ("Channel"), ("没找到Channel信息"), strCANChannel.GetBuffer(10), 10, (".//CANparaSet.cfg"));
		::GetPrivateProfileString(("CAN Config value"), ("Buard"), ("没找到Buard信息"), strBuard.GetBuffer(10), 10, (".//CANparaSet.cfg"));
		::GetPrivateProfileString(("CAN Config value"), ("FilteMode"), ("没找到FilteMode信息"), strFilterType.GetBuffer(10), 10, (".//CANparaSet.cfg"));
		::GetPrivateProfileString(("CAN Config value"), ("WorkMode"), ("没找到WorkMode信息"), strWorkMode.GetBuffer(10), 10, (".//CANparaSet.cfg"));
		::GetPrivateProfileString(("CAN Config value"), ("LogFilePath"), ("没找到LogFilePath信息"), strLogFilePath.GetBuffer(100), 100, (".//CANparaSet.cfg"));

		m_CANDevType = atoi(strDevType);
		m_CANDevIndex = atoi(strDevIndex);
		m_CANChannel = atoi(strCANChannel);

		m_CANBuard = GCanBrTab[atoi(strBuard)];//500kbp

		m_LogFilePath = strLogFilePath;

		m_sendTimeout = 100;

		m_WorkMode = atoi(strWorkMode);//0： 正常模式 1：只听模式
		m_FilterMode = atoi(strFilterType);//0: 标准帧滤波 1:扩展帧滤波 2:禁止滤波


	}
	else
	{
		m_CANDevType = VCI_USBCAN_2E_U;
		m_CANDevIndex = 0;
		m_CANChannel = 0;

		m_CANBuard = GCanBrTab[2];//500kbp
		m_sendTimeout = 100;

		m_WorkMode = 0;//0： 正常模式 1：只听模式
		m_FilterMode = 0;//0: 标准帧滤波 1:扩展帧滤波 2:禁止滤波

		::WritePrivateProfileString(("CAN Config value"), ("Type"), ("21"), (".//CANparaSet.cfg"));
		::WritePrivateProfileString(("CAN Config value"), ("Index"), ("0"), (".//CANparaSet.cfg"));
		::WritePrivateProfileString(("CAN Config value"), ("Channel"),("0"), (".//CANparaSet.cfg"));
		::WritePrivateProfileString(("CAN Config value"), ("Buard"), ("2"), (".//CANparaSet.cfg"));
		::WritePrivateProfileString(("CAN Config value"), ("FilteMode"), ("2"), (".//CANparaSet.cfg"));
		::WritePrivateProfileString(("CAN Config value"), ("WorkMode"), ("0"), (".//CANparaSet.cfg"));
		::WritePrivateProfileString(("CAN Config value"), ("LogFilePath"), (""), (".//CANparaSet.cfg"));

	}

	m_Connect = FALSE;
}

void CCAN_ToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REV_DIS, m_ListRevDis);
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

	LONG lStyle;
	lStyle = GetWindowLong(m_ListRevDis.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_ListRevDis.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_ListRevDis.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_ListRevDis.SetExtendedStyle(dwStyle); //设置扩展风格

	m_ListRevDis.InsertColumn(0, "时间", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(1, "ID", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(2, "帧格式", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(3, "帧类型", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(4, "00", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(5, "01", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(6, "02", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(7, "03", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(8, "04", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(9, "05", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(10, "06", LVCFMT_CENTER, 50);
	m_ListRevDis.InsertColumn(11, "07", LVCFMT_CENTER, 50);


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
	m_pLoggingThread = AfxBeginThread(LoggingThread, this);
}


void CCAN_ToolDlg::OnLoggingStop()
{
	// TODO:  在此添加命令处理程序代码
	if (m_pLoggingThread)
	{
		//m_pLoggingThread = NULL;
		::PostThreadMessage(m_pLoggingThread->m_nThreadID, WM_THREAD_STOP, 0, 0);
	}
	
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
		filterRecord.Start = 0x352;
		filterRecord.End = 0x353;

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
	CCAN_ToolDlg *dlg = (CCAN_ToolDlg*)param;
	//CListBox *box = (CListBox *)dlg->GetDlgItem(IDC_LIST_REV_DIS);
	VCI_CAN_OBJ frameinfo[50];
	VCI_ERR_INFO errinfo;
	int len = 1;
	int iPos = 0;
	int counter=0;
	CString tmpstr;

	SampleCount = 0;
	while (1)
	{
		Sleep(10);

		if (dlg->m_Connect == FALSE) break;
		len = VCI_Receive(dlg->m_CANDevType, dlg->m_CANDevIndex, dlg->m_CANChannel, frameinfo, 50, 500);
		if (len <= 0)
		{
			//注意：如果没有读到数据则必须调用此函数来读取出当前的错误码，
			//千万不能省略这一步（即使你可能不想知道错误码是什么）
			VCI_ReadErrInfo(dlg->m_CANDevType, dlg->m_CANDevIndex, dlg->m_CANChannel, &errinfo);
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				tmpstr.Format("%d ", counter++);
				iPos = dlg->m_ListRevDis.InsertItem(counter, tmpstr);     //时间

				tmpstr.Format("%03x ", frameinfo[i].ID);
				dlg->m_ListRevDis.SetItemText(iPos, 1, tmpstr);  //ID
				dlg->m_ListRevDis.SetItemText(iPos, 2, frameinfo[i].RemoteFlag == 0 ? "数据帧" : "远程帧"); //帧格式
				dlg->m_ListRevDis.SetItemText(iPos, 3, frameinfo[i].ExternFlag == 0 ? "标准帧" : "扩展帧"); //帧类型
				tmpstr.Format("%02x ", frameinfo[i].Data[0]);
				dlg->m_ListRevDis.SetItemText(iPos, 4, tmpstr); //00
				tmpstr.Format("%02x ", frameinfo[i].Data[1]);
				dlg->m_ListRevDis.SetItemText(iPos, 5, tmpstr); //01
				tmpstr.Format("%02x ", frameinfo[i].Data[2]);
				dlg->m_ListRevDis.SetItemText(iPos, 6, tmpstr); //02
				tmpstr.Format("%02x ", frameinfo[i].Data[3]);
				dlg->m_ListRevDis.SetItemText(iPos, 7, tmpstr); //03
				tmpstr.Format("%02x ", frameinfo[i].Data[4]);
				dlg->m_ListRevDis.SetItemText(iPos, 8, tmpstr); //04
				tmpstr.Format("%02x ", frameinfo[i].Data[5]);
				dlg->m_ListRevDis.SetItemText(iPos, 9, tmpstr); //05
				tmpstr.Format("%02x ", frameinfo[i].Data[6]);
				dlg->m_ListRevDis.SetItemText(iPos, 10, tmpstr);//06
				tmpstr.Format("%02x ", frameinfo[i].Data[7]);
				dlg->m_ListRevDis.SetItemText(iPos, 11, tmpstr);//07


				//update used for Logging 
				if (frameinfo[i].ID == 1)
				{
					CanObj[1].ID = frameinfo[i].ID;
					for (int j = 0; j < 8; j++)
					{
						CanObj[1].Data[j] = frameinfo[i].Data[j];
					}
				}
			}

		}

	}
	return 0;
}

UINT CCAN_ToolDlg::LoggingThread(void *param)
{
	MSG msg;   //增加一个MSG的变量msg来接收消息
	while (1)
	{
		Sleep(1000);



		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_THREAD_STOP){     //如果收到终止消息则退出
			//TODO：放在堆里的变量要在这里手动清理
			return 0;      //线程正常返回，会释放局部变量等内存资源
		}
		else{
			DispatchMessage(&msg);//字面意思，不解释
		}

	}
	return 0;
}


void CCAN_ToolDlg::OnBnClickedButtonStart()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_Connect == FALSE)
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
