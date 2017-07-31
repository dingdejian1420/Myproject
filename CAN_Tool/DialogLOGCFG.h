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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenFile();
	virtual BOOL OnInitDialog();
};
