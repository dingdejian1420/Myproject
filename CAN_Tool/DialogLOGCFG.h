#pragma once

#include "CAN_ToolDlg.h"
// CDialogLOGCFG 对话框

class CDialogLOGCFG : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLOGCFG)

public:
	CDialogLOGCFG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogLOGCFG();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGCFG };
	CString m_FilePath;
	CListCtrl m_ListLogIDInfo;

	CString m_ID;
	CString m_Time;

	int m_FocuseItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddlog();
	afx_msg void OnBnClickedButtonDellog();
	afx_msg void OnBnClickedLogsave();
	afx_msg void OnNMClickListLogInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
