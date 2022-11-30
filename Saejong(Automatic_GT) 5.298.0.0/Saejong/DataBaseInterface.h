#pragma once

class CDataBaseInterface : public CDialog
{
public:
	CDataBaseInterface(void);
	~CDataBaseInterface(void);
public:
	CString m_Version;
public:
	virtual int InitDataBase();
	virtual int ShowDataMonitor();
public:
	virtual CString GetMark(int Type,int Num);//0:D  1:L  2:M  3:T  4:S  5:C  6:P

	virtual double GetP(int Card,int Axis,int Num);
	virtual double GetD(int num);
	virtual double GetL(int num);
	virtual double GetT(int num);
	virtual int GetM(int num);
	virtual int GetS(int num);
	virtual CString GetC(int num);

	virtual int SetP(int Card,int Axis,int Num,double Value);
	virtual int SetD(int num,double Value);
	virtual int SetL(int num,double Value);
	virtual int SetT(int num,int Value);
	virtual int SetM(int num,int Value);
	virtual int SetS(int num,int Value);
	virtual int SetC(int num,CString Value);

	virtual int SetRunInfo(CString str,int num);
	virtual int GetRunInfo(CString &str,int num);

	virtual int SetRunAlarmInfo(CString str,int num);
	virtual int GetRunAlarmInfo(CString &str,int num);

	virtual int SetListAlarmInfo(CString str,int num);
	virtual int GetListAlarmInfo(CString &str,int num);
};
