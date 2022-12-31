#pragma once


// CInputBoxDlg 对话框

class CInputBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputBoxDlg)

public:
	CInputBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputBoxDlg();

// 对话框数据
	enum { IDD = IDD_INPUTBOXDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

public:
	int m_nLoginSuccessed;

};
