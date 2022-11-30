#pragma once

class FunModInterface
{
public:
	FunModInterface(void);
	~FunModInterface(void);
public:
	virtual int InitFunctionModule(CString Param);
	virtual int RunFunctionModule(int VectorNum,int ProgramNum);
	virtual int DeleteFunctionModuleParam();
	virtual int ReadFunctionModuleName(CString &Param);
	virtual int ShowFunctionModule(CString &Param,int ShowType);
};
