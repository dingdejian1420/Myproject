#pragma once


// CDialogCANCFG �Ի���

class CDialogCANCFG : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCANCFG)

public:
	CDialogCANCFG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogCANCFG();

// �Ի�������
	enum { IDD = IDD_DIALOG_CAN_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
