#pragma once

class CFlowChartInterface : public CDialog
{
public:
	CFlowChartInterface(void);
	~CFlowChartInterface(void);
public:
	virtual int GetKey();
	virtual int CloseFlowChart();
};
