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
	CComboBox	m_ComboDevType;
	CComboBox	m_ComboDevIndex;
	CComboBox	m_ComboChannel;
	CComboBox	m_ComboBaud;

	CComboBox	m_ComboFilterMode;
	CComboBox	m_ComboWorkMode;
	
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboCantype();
	afx_msg void OnCbnSelchangeComboCanindex();
	afx_msg void OnCbnSelchangeComboCanchannel();
	afx_msg void OnCbnSelchangeComboCanbuard();
	afx_msg void OnCbnSelchangeComboFiltertype();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboWorkmode();
	afx_msg void OnBnClickedOk();
};
