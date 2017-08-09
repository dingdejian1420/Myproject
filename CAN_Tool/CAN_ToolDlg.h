
// CAN_ToolDlg.h : ͷ�ļ�
//

#pragma once

#include "DialogCANCFG.h"
#include "DialogLOGCFG.h"


#define WM_THREAD_STOP 0x0427   //�Զ���һ����Ϣ��Ҳ������ϵͳ�������WM_QUIT
// CCAN_ToolDlg �Ի���
class CCAN_ToolDlg : public CDialogEx
{
// ����
public:
	CCAN_ToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CWinThread *m_pReceiveThread;
	CWinThread *m_pLoggingThread;

// �Ի�������
	enum { IDD = IDD_CAN_TOOL_DIALOG };

	DWORD m_CANDevType;
	DWORD m_CANDevIndex;
	DWORD m_CANChannel;

	DWORD m_CANBuard;
	int m_BuardIndex;

	DWORD m_sendTimeout;

	UCHAR m_WorkMode;
	DWORD m_FilterMode;

	BOOL m_Connect;

	CListCtrl m_ListRevDis;

	CString  m_LogFilePath;

	int m_LogTime;
	/**********************��������*************************/
	CComboBox	m_ComboSendType;
	CComboBox	m_ComboSendFrmType;
	CComboBox	m_ComboSendFrmFmt;
	CString	    m_EditSendFrmID;
	CString	    m_EditSendData;

	CButton  m_BtnDiaMode;
	CButton  m_BtnContinueSend;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCANConfig();
	afx_msg void OnLoggingConfig();
	afx_msg void OnLoggingStart();
	afx_msg void OnLoggingStop();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonReset();

	static UINT ReceiveThread(void *param);
	static UINT LoggingThread(void *param);

	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSend();

	int strtodata(unsigned char *str, unsigned char *data, int len, int flag);
	int chartoint(unsigned char chr, unsigned char *cint);
	afx_msg void OnBnClickedCheck_DIA();
	afx_msg void OnBnClickedCheckContinue();
};
