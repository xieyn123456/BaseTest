// SaejongDlg.h : 头文件
//
#pragma once
#include "Saejong.h"
#include "btnst.h"
#include "FlowChartInterface.h"
#include "MotionLibInterface.h"
#include "UserLoginInterface.h"
#include "FunModInterface.h"
#include "SetParamInterface.h"
#include "MainUIInterface.h"

// CSaejongDlg 对话框
class CSaejongDlg : public CDialog
{
// 构造
public:
	CSaejongDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SAEJONG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFlowChartInterface *m_FlowChartWin;
	CFlowChartInterface *m_FlowChartKeyWin;
	CMotionLibInterface *m_MotionLibWin;
	CUserLoginInterface *m_UserLoginWin;
	FunModInterface     *m_FunModInterface;	
	CSetParamInterface * m_SetParamWin;
	CMainUIInterface * m_MainUIWin;

	CButtonST m_Min;
	CButtonST m_Max;
	CButtonST m_Close;

	CButtonST m_workshow;
	CButtonST m_manualctrl;
	CButtonST m_setparam;
	CButtonST m_system;
	CButtonST m_Dispense;
	CButtonST m_changeuser;
	CButtonST m_help;
	CButtonST m_exit;

	int  GetApplicationPath(TCHAR *Path);
	void InitMain();
	void DoEvent();
	void InitFlowChart();
	void InitMotionLib();
	void InitDataBase();
	void InitUserLogin();
	void InitSetParam();
	void InitMainUI();
	void InitFunMod();
	void DrawGradientHeight(COLORREF color1,COLORREF color2,RECT& DrawRect,CRect &rect,CPaintDC &dc);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonMonitor();
	afx_msg void OnBnClickedButtonManual();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDispense();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonMax();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonInfo();
	afx_msg void OnBnClickedButtonSystem();
public:
	CString GetSystemTime();
	int SplitString(CString mainstr, CString delistr, CString strarr[],int arrsize);

};
