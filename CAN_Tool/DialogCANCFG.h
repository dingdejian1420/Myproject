#pragma once


// CDialogCANCFG 对话框

class CDialogCANCFG : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCANCFG)

public:
	CDialogCANCFG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogCANCFG();

// 对话框数据
	enum { IDD = IDD_DIALOG_CAN_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
