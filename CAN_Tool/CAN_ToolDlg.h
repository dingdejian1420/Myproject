
// CAN_ToolDlg.h : ͷ�ļ�
//

#pragma once

#include "DialogCANCFG.h"
#include "DialogLOGCFG.h"

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
	DWORD m_sendTimeout;

	UCHAR m_WorkMode;
	DWORD m_FilterMode;

	BOOL m_Connect;



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

};
