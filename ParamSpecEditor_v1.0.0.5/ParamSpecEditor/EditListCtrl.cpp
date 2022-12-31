#include "StdAfx.h"
#include "EditListCtrl.h"


#define ID_EDIT 9999

IMPLEMENT_DYNAMIC(iEdit, CEdit)
iEdit::iEdit(void)
{
	m_TextBkColor=RGB(100,100,100);
	m_TextColor = RGB(255,255,255);
	m_brush.CreateSolidBrush(m_TextBkColor);
}

iEdit::~iEdit(void)
{
}

BEGIN_MESSAGE_MAP(iEdit, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &iEdit::OnEnKillfocus)
END_MESSAGE_MAP()

void iEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	GetWindowText(m_strText);
	((EditListCtrl*)m_pPar)->SetItemText(m_nItem, m_nSubItem, m_strText);
	this->ShowWindow(SW_HIDE);
}

void iEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	SetWindowText(m_strText);
}

void iEdit::SetParent(CWnd* pWnd)
{
	m_pPar = pWnd;
}

HBRUSH iEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	HBRUSH   hbr;
	pDC->SetTextColor(m_TextColor);
	pDC->SetBkColor(m_TextBkColor);
	hbr   =   (HBRUSH)m_brush;
	return hbr;
}

void iEdit::OnEnKillfocus()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1;
	CString str2;
	int pos=-2;
	GetWindowText(str1);	
	if (m_nEnable == 1)
	{
		double d=_wtof(str1);
		str2.Format(_T("%0.3f"),d);
	}
	else if (m_nEnable == 2)
	{
		int l=_wtoi(str1);
		str2.Format(_T("%d"),l);
	}
	else if (m_nEnable == 3)
	{
		str2 = str1;
	}
	SetWindowText(str2);
}

BOOL iEdit::CheckUniqueStr(char nChar)
{
	CString str;
	int nPos = 0;
	GetWindowText(str);
	nPos = str.Find(nChar);
	return (nPos>=0)?TRUE:FALSE;
}



//EditListCtrl
IMPLEMENT_DYNAMIC(EditListCtrl, CListCtrl)

EditListCtrl::EditListCtrl(void)
{
	nCopyIndex=-1;
	m_MenuCtrl.LoadMenu(IDR_MENU1);//加载菜单
}

EditListCtrl::~EditListCtrl(void)
{
}
BEGIN_MESSAGE_MAP(EditListCtrl, CListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_COPY, &EditListCtrl::OnCopy)
	ON_COMMAND(ID_PASTE, &EditListCtrl::OnPaste)
	ON_COMMAND(ID_APPALL, &EditListCtrl::OnAppall)
END_MESSAGE_MAP()

BOOL EditListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if ( m_bFixed )
	{
		switch(((NMHDR*)lParam)->code)
		{
		case HDN_BEGINTRACKW:
		case HDN_BEGINTRACKA:
		case HDN_DIVIDERDBLCLICK:
			*pResult = TRUE;
			return TRUE;
		}
	}

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

void EditListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this,ID_EDIT);
	m_Edit.SetParent(this);

	CListCtrl::PreSubclassWindow();
}

CString EditListCtrl::GetColumnStr(int Colnum)
{
	LV_COLUMN lvColumn;
	char uin[100];
	lvColumn.pszText=LPWSTR(uin);
	lvColumn.cchTextMax =100;
	lvColumn.mask = LVCF_TEXT;
	GetColumn(Colnum,&lvColumn);
	return CString(lvColumn.pszText);
}

void EditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnLButtonDblClk(nFlags, point);
	//获取当前点击的行列(lvinfo.iItem行，lvinfo.iSubItem列)
	DWORD dwPos = GetMessagePos();
	CPoint ipoint( LOWORD(dwPos), HIWORD(dwPos) );
	ScreenToClient(&ipoint);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = ipoint;
	lvinfo.flags = LVHT_ABOVE;
	SubItemHitTest(&lvinfo);

	if(lvinfo.iSubItem !=0)
	{
		LVHITTESTINFO lvhti;
		lvhti.pt = point;
		lvhti.flags=LVHT_ONITEMLABEL;
		this->SubItemHitTest(&lvhti);
		nItem = lvhti.iItem;
		nSubItem = lvhti.iSubItem;

		CString str=GetColumnStr(nSubItem);
		CString str1;
		str1=GetItemText(nItem, 0);

		if (nSubItem==3 || nSubItem==4)
		{
			m_Edit.m_nEnable=1;
		}
		else if (nSubItem==2  || nSubItem == 6|| nSubItem == 7)
		{
			m_Edit.m_nEnable=2;
		}
		else if (nSubItem == 5 )
		{
			m_Edit.m_nEnable=3;
		}
		else
		{
			return;
		}

		CRect rectCell;
		this->GetSubItemRect(nItem, nSubItem, LVIR_LABEL,rectCell);
		rectCell.InflateRect(1,1,1,1);
		m_Edit.m_nItem = nItem;
		m_Edit.m_nSubItem = nSubItem;
		m_Edit.m_strText = this->GetItemText(nItem, nSubItem);
		m_Edit.MoveWindow(&rectCell, TRUE);
		m_Edit.SetFocus();
		m_Edit.SetSel(0, -1); 
		m_Edit.ShowWindow(SW_SHOW);
	}
}
void EditListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnRButtonDown(nFlags, point);

	DWORD dwPos = GetMessagePos();
	CPoint ipoint( LOWORD(dwPos), HIWORD(dwPos) );
	ScreenToClient(&ipoint);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = ipoint;
	lvinfo.flags = LVHT_ABOVE;
	SubItemHitTest(&lvinfo);

	nItem = lvinfo.iItem;
	nSubItem = lvinfo.iSubItem;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_Menu=m_MenuCtrl.GetSubMenu(0);

	CPoint pt;
	GetCursorPos(&pt);
	m_Menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);
}
int EditListCtrl::DeleteList()
{
	DeleteAllItems();
	while(DeleteColumn(0))
	{}
	return 0;
}

int EditListCtrl::LoadMainList()
{
	SetColumnFixed(TRUE);
	ModifyStyle(NULL,LVS_REPORT);
	ShowScrollBar(TRUE);
	SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_MULTIWORKAREAS);
	return 0;
}

void EditListCtrl::SetColumnFixed(BOOL bFixed)
{
	m_bFixed = bFixed;
}
void  EditListCtrl::InsertRow(CString type,CString name,int lv,double maxv,double minv,CString unit,int setvf,int blaf)
{
	CString strit=_T("");
	int n=GetItemCount();
	InsertItem(n,type);
	SetItemText(n,1,name);

	strit.Format(_T("%d"),lv);
	SetItemText(n,2,strit);
	strit.Format(_T("%0.3f"),maxv);
	SetItemText(n,3,strit);
	strit.Format(_T("%0.3f"),minv);
	SetItemText(n,4,strit);

	SetItemText(n,5,unit);

	strit.Format(_T("%d"),setvf);
	SetItemText(n,6,strit);
	strit.Format(_T("%d"),blaf);
	SetItemText(n,7,strit);
}

void  EditListCtrl::InsertRowdat(CString type,CString name,int lv,double maxv,double minv)
{
	CString strit=_T("");
	int n=GetItemCount();
	InsertItem(n,type);
	SetItemText(n,1,name);

	strit.Format(_T("%d"),lv);
	SetItemText(n,2,strit);
	strit.Format(_T("%0.3f"),maxv);
	SetItemText(n,3,strit);
	strit.Format(_T("%0.3f"),minv);
	SetItemText(n,4,strit);

}
void EditListCtrl::OnCopy()
{
	// TODO: 在此添加命令处理程序代码
	if (nItem<0 || nItem>GetItemCount())
	{
		return ;
	}
	else
	{
		nCopyIndex=nItem;
	}
}

void EditListCtrl::OnPaste()
{
	// TODO: 在此添加命令处理程序代码
	if (nItem<0 || nItem>GetItemCount() || nCopyIndex==-1)
	{
		return ;
	}
	else
	{
		SetItemText(nItem,2,GetItemText(nCopyIndex,2));
		SetItemText(nItem,3,GetItemText(nCopyIndex,3));
		SetItemText(nItem,4,GetItemText(nCopyIndex,4));

		SetItemText(nItem,5,GetItemText(nCopyIndex,5));
		SetItemText(nItem,6,GetItemText(nCopyIndex,6));
		SetItemText(nItem,7,GetItemText(nCopyIndex,7));
	}
}

void EditListCtrl::OnAppall()
{
	// TODO: 在此添加命令处理程序代码
	if (nCopyIndex==-1)
	{
		return ;
	}
	else
	{
		CString strit=_T("");
		strit.Format(_T("请确认是否将 %s-%s 的配置应用到全部参数? \n所有参数都将改变!!!"),GetItemText(nCopyIndex,0),GetItemText(nCopyIndex,1));
		if (IDYES==AfxMessageBox(strit,MB_YESNO | MB_ICONEXCLAMATION))
		{
			for (int i=0;i<GetItemCount();i++)
			{
				SetItemText(i,2,GetItemText(nCopyIndex,2));
				SetItemText(i,3,GetItemText(nCopyIndex,3));
				SetItemText(i,4,GetItemText(nCopyIndex,4));

				SetItemText(i,5,GetItemText(nCopyIndex,5));
				SetItemText(i,6,GetItemText(nCopyIndex,6));
				SetItemText(i,7,GetItemText(nCopyIndex,7));
			}
		}
	}
}
