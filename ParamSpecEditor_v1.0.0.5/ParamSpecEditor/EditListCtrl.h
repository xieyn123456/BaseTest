#pragma once
#include "afxcmn.h"
#include "resource.h"

class iEdit : public CEdit
{
	DECLARE_DYNAMIC(iEdit)

public:
	iEdit();
	virtual ~iEdit();
	DECLARE_MESSAGE_MAP();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	void SetParent(CWnd* pWnd);
	BOOL CheckUniqueStr(char nChar);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnEnKillfocus();
public:
	int    m_nEnable;
	CString m_strText;
	int m_nItem;
	int m_nSubItem;
	CBrush   m_brush; 
	COLORREF m_TextBkColor; 
	COLORREF m_TextColor;
	CWnd* m_pPar;
};

class EditListCtrl :
	public CListCtrl
{
	DECLARE_DYNAMIC(EditListCtrl)
public:
	EditListCtrl(void);
	~EditListCtrl(void);
	void SetColumnFixed(BOOL bFixed);
	int LoadMainList();
	int DeleteList();
	DECLARE_MESSAGE_MAP()
	BOOL m_bFixed;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	iEdit    m_Edit;
	CMenu* m_Menu;
	CMenu  m_MenuCtrl;

	int nCopyIndex;

	int nItem;
	int nSubItem;
	CString GetColumnStr(int Colnum);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
	void InsertRow(CString type,CString name,int lv,double maxv,double minv,CString unit,int setvf,int blaf);
	void InsertRowdat(CString type,CString name,int lv,double maxv,double minv);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnAppall();
};
