#pragma once
class CMainUIInterface : public CDialog
{
public:
	CMainUIInterface(void);
	~CMainUIInterface(void);
public:
	virtual int ShowMainUI(CWnd* it);
	virtual void ShowVersion(CString str);
};
