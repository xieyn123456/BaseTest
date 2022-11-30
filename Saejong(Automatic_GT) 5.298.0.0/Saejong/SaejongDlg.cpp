// SaejongDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Saejong.h"
#include "SaejongDlg.h"
#include "DataBaseInterface.h"
#include <shlwapi.h>
#include <string>
#include <fstream>
#include <locale.h>

#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CDataBaseInterface *m_DataBaseWin;

// CSaejongDlg �Ի���

CBrush      m_WhiteBrush;


CSaejongDlg::CSaejongDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaejongDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaejongDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_BUTTON_MIN, m_Min);
	DDX_Control(pDX, IDC_BUTTON_MAX, m_Max);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_Close);

	DDX_Control(pDX, IDC_BUTTON_MONITOR, m_workshow);
	DDX_Control(pDX, IDC_BUTTON_MANUAL, m_manualctrl);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_setparam);
	DDX_Control(pDX, IDC_BUTTON_SYSTEM, m_system);
	DDX_Control(pDX, IDC_BUTTON_DISPENSE, m_Dispense);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_changeuser);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_help);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_exit);

	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSaejongDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_MONITOR, &CSaejongDlg::OnBnClickedButtonMonitor)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL, &CSaejongDlg::OnBnClickedButtonManual)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CSaejongDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CSaejongDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CSaejongDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CSaejongDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CSaejongDlg::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_MAX, &CSaejongDlg::OnBnClickedButtonMax)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSaejongDlg::OnBnClickedButtonClose)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_DISPENSE, &CSaejongDlg::OnBnClickedButtonDispense)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM, &CSaejongDlg::OnBnClickedButtonSystem)
END_MESSAGE_MAP()


// CSaejongDlg ��Ϣ�������

BOOL CSaejongDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	int sw = GetSystemMetrics(SM_CXSCREEN),sh = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(0,0,sw,sh);
	SetWindowPos(&this->wndNoTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);

	m_WhiteBrush.DeleteObject();
	m_WhiteBrush.CreateSolidBrush(RGB(255,255,255));//��ɫ

	m_Min.SetBitmaps(IDB_BITMAP_MIN1,0,IDB_BITMAP_MIN0,0);
	m_Max.SetBitmaps(IDB_BITMAP_MAX1,0,IDB_BITMAP_MAX0,0);
	m_Close.SetBitmaps(IDB_BITMAP_CLOSE1,0,IDB_BITMAP_CLOSE0,0);

	m_Min.DrawTransparent(true);
	m_Max.DrawTransparent(true);
	m_Close.DrawTransparent(true);

	m_workshow.SetIcon(IDI_ICON_WORK1,IDI_ICON_WORK0);
	m_manualctrl.SetIcon(IDI_ICON_MANUAL1,IDI_ICON_MANUAL0);
	m_setparam.SetIcon(IDI_ICON_PARAM1,IDI_ICON_PARAM0);
	m_system.SetIcon(IDI_ICON_CODE1,IDI_ICON_CODE0);
	m_Dispense.SetIcon(IDI_ICON_DISPEN1,IDI_ICON_DISPEN0);
	m_changeuser.SetIcon(IDI_ICON_USER1,IDI_ICON_USER0);
	m_help.SetIcon(IDI_ICON_HELP1,IDI_ICON_HELP0);
	m_exit.SetIcon(IDI_ICON_EXIT1,IDI_ICON_EXIT0);

	m_workshow.SetAlign(1,TRUE);
	m_manualctrl.SetAlign(1,TRUE);
	m_setparam.SetAlign(1,TRUE);
	m_system.SetAlign(1,TRUE);
	m_Dispense.SetAlign(1,TRUE);
	m_changeuser.SetAlign(1,TRUE);
	m_help.SetAlign(1,TRUE);
	m_exit.SetAlign(1,TRUE);

	m_workshow.DrawTransparent(true);
	m_manualctrl.DrawTransparent(true);
	m_setparam.DrawTransparent(true);
	m_system.DrawTransparent(true);
	m_Dispense.DrawTransparent(true);
	m_changeuser.DrawTransparent(true);
	m_help.DrawTransparent(true);
	m_exit.DrawTransparent(true);

	m_workshow.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_manualctrl.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_setparam.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_system.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_Dispense.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_changeuser.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_help.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));
	m_exit.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(0,0,0));

	m_workshow.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_manualctrl.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_setparam.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_system.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_Dispense.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_changeuser.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_help.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));
	m_exit.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(85,63,127));

	CRect rect;
	GetClientRect(&rect);
	::MoveWindow(GetDlgItem(IDC_BUTTON_MONITOR)->m_hWnd,20+70*0,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_MANUAL)->m_hWnd,20+70*1,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_SETTING)->m_hWnd,20+70*2,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_SYSTEM)->m_hWnd,20+70*3,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_DISPENSE)->m_hWnd,20+70*4,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_CHANGE)->m_hWnd,20+70*5,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_HELP)->m_hWnd,20+70*6,8,60,68,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_EXIT)->m_hWnd,20+70*7,8,60,68,true);

	::MoveWindow(GetDlgItem(IDC_BUTTON_MIN)->m_hWnd,rect.right-rect.left-106,0,27,18,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_MAX)->m_hWnd,rect.right-rect.left-78,0,26,18,true);
	::MoveWindow(GetDlgItem(IDC_BUTTON_CLOSE)->m_hWnd,rect.right-rect.left-51,0,46,18,true);

	//�ȼ���InitMotionLib() �����InitFlowChart() ������InitFunMod()
	InitMainUI();
	InitDataBase();
	InitMotionLib();
	InitUserLogin();
	InitFlowChart();
	InitFunMod();
	InitSetParam();

	if(0==m_FlowChartKeyWin->GetKey())
	{
		m_MainUIWin->ShowVersion(_T("����汾: 5.298.0.0"));
	}
	else
	{
		m_MainUIWin->ShowVersion(_T("����汾(δ����): 5.298.0.0"));
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSaejongDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	RECT rect1={0,0,1024,80};
	DrawGradientHeight(RGB(200,200,200),RGB(170,170,170),rect1,rect,dc);
}

void CSaejongDlg::DrawGradientHeight(COLORREF color1,COLORREF color2,RECT& DrawRect,CRect &rect,CPaintDC &dc)
{
	int r = GetRValue( color1 );
	int g = GetGValue( color1 );
	int b = GetBValue( color1 );

	int r2 = GetRValue( color2 );
	int g2 = GetGValue( color2 );
	int b2 = GetBValue( color2 );

	if(DrawRect.right-DrawRect.left<=0) return;
	int DrawRectHeight=DrawRect.bottom-DrawRect.top;

	CBrush hbr;
	hbr.CreateSolidBrush(RGB(r,g,b));
	dc.FillRect(CRect(0,25,5,rect.bottom-rect.top),&hbr);
	dc.FillRect(CRect(rect.right-rect.left-5,25,rect.right-rect.left,
		    rect.bottom-rect.top),&hbr);
	hbr.DeleteObject();

	for(int i=DrawRectHeight/2;i>0;i-=1) 
	{
		//����ˢ��
		hbr.CreateSolidBrush( RGB( r, g, b ) );
		dc.FillRect(CRect(0,DrawRect.top,rect.right,DrawRect.top+1),&hbr);
		hbr.DeleteObject();

		//�ı�С�������λ��
		DrawRect.top += 1;

		//�ж�С�������Ƿ񳬽�
		if( DrawRect.top > DrawRect.bottom )
			rect.bottom = DrawRect.bottom;

		//�ı���ɫ
		r += ( r2 - r + i / 2 ) / i * 1;
		g += ( g2 - g + i / 2 ) / i * 1;
		b += ( b2 - b + i / 2 ) / i * 1;
	}

	r = GetRValue( color2 );
	g = GetGValue( color2 );
	b = GetBValue( color2 );

	r2 = GetRValue( color1);
	g2 = GetGValue( color1 );
	b2 = GetBValue( color1);

	for(int i=DrawRectHeight/2;i>0;i-=1) 
	{
		//����ˢ��
		hbr.CreateSolidBrush( RGB( r, g, b ) );
		dc.FillRect(CRect(0,DrawRect.top,rect.right,DrawRect.top+1),&hbr);
		hbr.DeleteObject();

		//�ı�С�������λ��
		DrawRect.top += 1;

		//�ı���ɫ
		r += ( r2 - r + i / 2 ) / i * 1;
		g += ( g2 - g + i / 2 ) / i * 1;
		b += ( b2 - b + i / 2 ) / i * 1;
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSaejongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSaejongDlg::DoEvent()
{
	static MSG msg;
	if( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) )
	{
		AfxGetApp()->PumpMessage();
	}
}

void CSaejongDlg::InitFlowChart()
{
	HINSTANCE m_FlowChart = LoadLibrary(_T("FlowChart.dll"));
	if(NULL==m_FlowChart)
	{
		MessageBox(_T("���� FlowChart.dll ʧ��"));
		return;
	}

	typedef CFlowChartInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_FlowChart,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_FlowChartWin = pShowDlg();


	typedef CFlowChartInterface* (*hpDllFun)();
	hpDllFun pShowDlg2 = (hpDllFun)GetProcAddress(m_FlowChart,"InitDialog2");
	if(NULL==pShowDlg2)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_FlowChartKeyWin = pShowDlg2();
}

void CSaejongDlg::InitMotionLib()
{
	HINSTANCE m_MotionLib = LoadLibrary(_T("MotionLibrary.dll"));
	if(NULL==m_MotionLib)
	{
		MessageBox(_T("���� MotionLibrary.dll ʧ��"));
		return;
	}

	typedef CMotionLibInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_MotionLib,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_MotionLibWin = pShowDlg();
	m_MotionLibWin->InitMotionLib();
}

void CSaejongDlg::InitDataBase()
{
	HINSTANCE m_DataBase = LoadLibrary(_T("DataBase.dll"));
	if(NULL==m_DataBase)
	{
		MessageBox(_T("���� DataBase.dll ʧ��"));
		return;
	}

	typedef CDataBaseInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_DataBase,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_DataBaseWin = pShowDlg();
}

void CSaejongDlg::InitUserLogin()
{
	HINSTANCE m_UserLogin = LoadLibrary(_T("UserLogin.dll"));
	if(NULL==m_UserLogin)
	{
		MessageBox(_T("���� UserLogin.dll ʧ��"));
		return;
	}

	typedef CUserLoginInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_UserLogin,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_UserLoginWin = pShowDlg();
}
void CSaejongDlg::InitSetParam()
{
	HINSTANCE m_SetParam = LoadLibrary(_T("SetParam.dll"));
	if(NULL==m_SetParam)
	{
		MessageBox(_T("���� SetParam.dll ʧ��"));
		return;
	}

	typedef CSetParamInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_SetParam,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_SetParamWin = pShowDlg();
}
void CSaejongDlg::InitMainUI()
{
	HINSTANCE m_MainUI = LoadLibrary(_T("MainUI.dll"));
	if(NULL==m_MainUI)
	{
		MessageBox(_T("���� MainUI.dll ʧ��"));
		return;
	}

	typedef CMainUIInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_MainUI,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_MainUIWin = pShowDlg();

	m_MainUIWin->ShowMainUI(this);
}

void CSaejongDlg::InitFunMod()
{
	HINSTANCE m_FlowChart = LoadLibrary(_T("DoubleTableDispenseUR.dll"));
	if(NULL==m_FlowChart)
	{
		MessageBox(_T("���� DoubleTableDispenseUR.dll ʧ��"));
		return;
	}

	typedef FunModInterface* (*hpDllFun)();
	hpDllFun pShowDlg = (hpDllFun)GetProcAddress(m_FlowChart,"InitDialog");
	if(NULL==pShowDlg)
	{
		MessageBox(_T("DLL�к���Ѱ��ʧ��"));
		return;
	}
	m_FunModInterface = pShowDlg();
}

HBRUSH CSaejongDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_DLG) 
	{ 
		pDC->SetTextColor(RGB(0, 0, 0)) ; 
		pDC-> SetBkMode(TRANSPARENT); 
		return m_WhiteBrush;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CSaejongDlg::OnBnClickedButtonMonitor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MotionLibWin->ShowMonitorDlg();
}

void CSaejongDlg::OnBnClickedButtonManual()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MotionLibWin->ShowManualDlg();
}

void CSaejongDlg::OnBnClickedButtonSetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_UserLoginWin->GetUserLevel()>=2)
	{
		m_SetParamWin->ShowSetParam();//ShowWindow(TRUE);
	}
	else
	{
		MessageBox(_T("��Ҫ����ԱȨ��"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
	}
}

void CSaejongDlg::OnBnClickedButtonSystem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_UserLoginWin->GetUserLevel()>=4)
	{
		int num=m_FlowChartWin->IsWindowVisible();
		if(num==0)
		{
			m_FlowChartWin->ShowWindow(true);
		}
		else if(num==1)
		{
			m_FlowChartWin->ShowWindow(false);
			m_FlowChartWin->ShowWindow(true);
		}
	}
	else
	{
		MessageBox(_T("��Ҫ����ԱȨ��"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
	}
}

void CSaejongDlg::OnBnClickedButtonDispense()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_UserLoginWin->GetUserLevel()>=1)
	{
		CString str;
    	m_FunModInterface->ShowFunctionModule(str,1);
	}
	else
	{
		MessageBox(_T("��Ҫ����ԱȨ��"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
	}
}

void CSaejongDlg::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_UserLoginWin->ShowUserLogin();
}

void CSaejongDlg::OnBnClickedButtonHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	TCHAR path[1024];
	GetApplicationPath(path);
	temp.Format(_T("%s"),path);
	ShellExecute(m_hWnd,_T("open"),_T("Manual.pdf"),NULL,temp,SW_SHOWNORMAL);
}

void CSaejongDlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(IDYES==MessageBox(_T("ȷ���˳�����"),_T("��ʾ"),MB_ICONINFORMATION|MB_YESNO))
	{
		m_DataBaseWin->SetS(1999,1);//S[10]=1ϵͳ�˳�
		m_FlowChartKeyWin->CloseFlowChart();//����ͷ�ļ�����
		Sleep(100);
		OnClose();
		OnOK();
	}
	else
	{
		return;
	}
}

int CSaejongDlg::GetApplicationPath(TCHAR *Path)
{
	TCHAR temp[1024];
	TCHAR strPath[1024];
	::GetModuleFileName(NULL,temp,1024);
	int i;
	for(i=1023;temp[i]!='\\';i--)
	{
	}
	wcsncpy_s(strPath,_countof(strPath),temp,i);
	wcsncpy_s(Path,1024,strPath,1024);
	return 0;
}

void CSaejongDlg::OnBnClickedButtonMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
}

void CSaejongDlg::OnBnClickedButtonMax()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sw = GetSystemMetrics(SM_CXSCREEN),sh = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(0,0,sw,sh);
}

void CSaejongDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButtonExit();
}

void CSaejongDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}

void CSaejongDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

void CSaejongDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnBnClickedButtonMax();

	CDialog::OnLButtonDblClk(nFlags, point);
}

int CSaejongDlg::SplitString(CString mainstr, CString delistr, CString strarr[],int arrsize)
{
	int ncount=0;
	int aindex=-1,bindex=0;
	CString strx;
	for (int i=0;i<arrsize;i++)
	{
		bindex=mainstr.Find(delistr,aindex+1);
		if (bindex!=-1)
		{
			strx=mainstr.Mid(aindex+1,bindex-aindex-1);		
			strarr[i]=strx;
			aindex=bindex;
			ncount++;
		}
		else
		{
			strx=mainstr.Mid(aindex+1); //�����������һ��û�зָ������ַ���
			if (!strx.IsEmpty())
			{
				strarr[i]=strx;
				ncount++;
				break;
			}
			else
			{
				break;
			}
		}
	}
	for (int i=ncount;i<arrsize;i++)
	{
		strarr[i]=_T("");
	}
	return 0;
}