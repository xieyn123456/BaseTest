#pragma once


// CInputBoxDlg �Ի���

class CInputBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputBoxDlg)

public:
	CInputBoxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputBoxDlg();

// �Ի�������
	enum { IDD = IDD_INPUTBOXDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

public:
	int m_nLoginSuccessed;

};
