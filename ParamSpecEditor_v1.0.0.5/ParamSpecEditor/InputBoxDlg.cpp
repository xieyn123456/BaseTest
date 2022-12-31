// InputBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ParamSpecEditor.h"
#include "InputBoxDlg.h"


// CInputBoxDlg 对话框

IMPLEMENT_DYNAMIC(CInputBoxDlg, CDialog)

CInputBoxDlg::CInputBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputBoxDlg::IDD, pParent)
{
	m_nLoginSuccessed=0;
}

CInputBoxDlg::~CInputBoxDlg()
{
}

void CInputBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputBoxDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CInputBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputBoxDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInputBoxDlg 消息处理程序

void CInputBoxDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strit=_T("");
	GetDlgItemText(IDC_EDIT_INPUT,strit);
	if (strit==_T("saejong123**#"))
	{
		m_nLoginSuccessed=1;
	}
	OnOK();
}

void CInputBoxDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL CInputBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("ParamSpecEditor"));
	GetDlgItem(IDC_EDIT_INPUT)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
