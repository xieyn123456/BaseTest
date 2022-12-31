// InputBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParamSpecEditor.h"
#include "InputBoxDlg.h"


// CInputBoxDlg �Ի���

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


// CInputBoxDlg ��Ϣ�������

void CInputBoxDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

BOOL CInputBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(_T("ParamSpecEditor"));
	GetDlgItem(IDC_EDIT_INPUT)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
