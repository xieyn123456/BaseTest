// Saejong.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Saejong.h"
#include "SaejongDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSaejongApp

BEGIN_MESSAGE_MAP(CSaejongApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSaejongApp ����

CSaejongApp::CSaejongApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSaejongApp ����

CSaejongApp theApp;


// CSaejongApp ��ʼ��

BOOL CSaejongApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	HANDLE hHandle;
	hHandle=CreateMutex(NULL,TRUE,_T("Saejong"));
	if(ERROR_ALREADY_EXISTS==GetLastError())
	{
		AfxMessageBox(_T("�����Ѿ������������ظ��򿪣�"));
		::ShowWindow(this->GetMainWnd()->GetSafeHwnd(),SW_SHOW);
		return false;
	}

	CSaejongDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CSaejongApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch ( pMsg->wParam )
	{
	case VK_ESCAPE:
		return TRUE;
	case VK_RETURN:
		return TRUE;
	case VK_UP://�������
		return TRUE;
	case VK_DOWN://�������
		return TRUE;
	}
	if(pMsg->message==WM_SYSKEYDOWN && pMsg->wParam==VK_F4) return TRUE;
	return CWinApp::PreTranslateMessage(pMsg);
}