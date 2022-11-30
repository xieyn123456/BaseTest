#pragma once

class CUserLoginInterface : public CDialog
{
public:
	CUserLoginInterface(void);
	~CUserLoginInterface(void);
public:
	virtual int GetUserLevel();
	virtual int ShowUserLogin();
};
