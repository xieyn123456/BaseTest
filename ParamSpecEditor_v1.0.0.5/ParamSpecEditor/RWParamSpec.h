#pragma once
#include "IniOper.h"

#define MAXVALUE	2000

class CRWParamSpec
{
public:
	CRWParamSpec(void);
	~CRWParamSpec(void);

public:
	int ReadSystemParam();
	int WriteSystemParam();

	int ReadLeftSlipParam();
	int WriteLeftSlipParam();
	
	int ReadRightSlipParam();
	int WriteRightSlipParam();

	int ReadLeftUpSmallMaterialParam();
	int WriteLeftUpSmallMaterialParam();
	
	int ReadRightUpSmallMaterialParam();
	int WriteRightUpSmallMaterialParam();

	int ReadDispensingParam();
	int WriteDispensingParam();

	int ReadHSGAutoUpParam();
	int WriteHSGAutoUpParam();

	int ReadBlastFlagParam();
	int WriteBlastFlagParam();
	
	CString m_strPath;

	CString ReadParamSpeciniPara(CString section,CString key,CString strError=_T(""),CString path=_T(""));

public:
	double dMax[MAXVALUE];
	double dMin[MAXVALUE];
	CString strUnit[MAXVALUE];
	int nAcessLv[MAXVALUE];
	int nSetValueFlag[MAXVALUE];
	int nBlastFlag[MAXVALUE];

};
