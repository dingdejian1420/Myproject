#pragma once

#include "CAN_ToolDlg.h"
// CDialogLOGCFG �Ի���

class CDialogLOGCFG : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLOGCFG)

public:
	CDialogLOGCFG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogLOGCFG();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGCFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenFile();
	virtual BOOL OnInitDialog();
};
