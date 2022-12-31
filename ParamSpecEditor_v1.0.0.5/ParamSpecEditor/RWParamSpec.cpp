#include "StdAfx.h"
#include "RWParamSpec.h"

CRWParamSpec::CRWParamSpec(void)
{
	m_strPath = _T("");
}

CRWParamSpec::~CRWParamSpec(void)
{

}

CString CRWParamSpec::ReadParamSpeciniPara(CString section,CString key,CString strError,CString path)
{
	CString strValue;
	if (path.IsEmpty())
	{
		GetAppPath(path);
		path=path+_T("/����/ParamSpec.INI");
	}
	WCHAR strBuffer[200];
	::GetPrivateProfileStringW(section,key ,strError,strBuffer,200,path);
	strValue=(CString)strBuffer;
	strValue.Replace(_T(" "),_T(""));//english
	strValue.Replace(_T(" "),_T(""));//simple-chinese	
	m_strPath = strValue;
	return strValue;
}

int CRWParamSpec::ReadMaxParam()
{
 CIniOper	RwData(m_strPath);
	dMax[0]=RwData.getKeyValueDouble(_T("0"),_T("���ֵ")); 
	dMax[1]=RwData.getKeyValueDouble(_T("1"),_T("���ֵ")); 
	return TRUE;
}

int CRWParamSpec::WriteMaxParam()
{
	CIniOper	RwData(m_strPath);
	RwData.setKey(m_ParamSpecData.dblMax[0], _T("0"), _T("���ֵ"));
	RwData.setKey(m_ParamSpecData.dblMax[1], _T("1"), _T("���ֵ"));
	return TRUE;
}

int CRWParamSpec::ReadMinParam()
{
 CIniOper	RwData(m_strPath);
	m_ParamSpecData.dblMin[0]=RwData.getKeyValueDouble(_T("0"),_T("��Сֵ")); 
	m_ParamSpecData.dblMin[1]=RwData.getKeyValueDouble(_T("1"),_T("��Сֵ")); 
	return TRUE;
}
int CRWParamSpec::WriteMinParam()
{
	CIniOper	RwData(m_strPath);
	RwData.setKey(m_ParamSpecData.dblMin[0], _T("0"), _T("��Сֵ"));
	RwData.setKey(m_ParamSpecData.dblMin[1], _T("1"), _T("��Сֵ"));
	return TRUE;
}

int CRWParamSpec::ReadUnitParam()
{
 CIniOper	RwData(m_strPath);
	/*m_ParamSpecData.sUnit[0]=RwData.getKeyValue(_T("0"),_T("��λ")); 
	m_ParamSpecData.sUnit[1]=RwData.getKeyValue(_T("1"),_T("��λ")); */
	return TRUE;
}
int CRWParamSpec::WriteUnitParam()
{
	CIniOper	RwData(m_strPath);
	/*RwData.setKey(m_ParamSpecData.sUnit[0], _T("0"), _T("��λ"));
	RwData.setKey(m_ParamSpecData.sUnit[1], _T("1"), _T("��λ"));*/
	return TRUE;
}

int CRWParamSpec::ReadAcessLvParam()
{
 CIniOper	RwData(m_strPath);
	m_ParamSpecData.nAcessLv[0]=RwData.getKeyValueDouble(_T("0"),_T("Ȩ��")); 
	m_ParamSpecData.nAcessLv[1]=RwData.getKeyValueDouble(_T("1"),_T("Ȩ��")); 
	return TRUE;
}
int CRWParamSpec::WriteAcessLvParam()
{
	CIniOper	RwData(m_strPath);
	RwData.setKey(m_ParamSpecData.nAcessLv[0], _T("0"), _T("Ȩ��"));
	RwData.setKey(m_ParamSpecData.nAcessLv[1], _T("1"), _T("Ȩ��"));
	return TRUE;
}

int CRWParamSpec::ReadSetValFlagParam()
{
 CIniOper	RwData(m_strPath);
	m_ParamSpecData.nSetValueFlag[0]=RwData.getKeyValueInt(_T("0"),_T("�޸��ϴ���־")); 
	m_ParamSpecData.nSetValueFlag[1]=RwData.getKeyValueInt(_T("1"),_T("�޸��ϴ���־")); 
	return TRUE;
}
int CRWParamSpec::WriteSetValFlagParam()
{
	CIniOper	RwData(m_strPath);
	RwData.setKey(m_ParamSpecData.nSetValueFlag[0], _T("0"), _T("�޸��ϴ���־"));
	RwData.setKey(m_ParamSpecData.nSetValueFlag[1], _T("1"), _T("�޸��ϴ���־"));
	return TRUE;
}

int CRWParamSpec::ReadBlastFlagParam()
{
 CIniOper	RwData(m_strPath);
	m_ParamSpecData.nBlastFlag[0]=RwData.getKeyValueInt(_T("0"),_T("�ȶ��ϴ���־")); 
	m_ParamSpecData.nBlastFlag[1]=RwData.getKeyValueInt(_T("1"),_T("�ȶ��ϴ���־")); 
	return TRUE;
}
int CRWParamSpec::WriteBlastFlagParam()
{
	CIniOper	RwData(m_strPath);
	RwData.setKey(m_ParamSpecData.nBlastFlag[0], _T("0"), _T("�ȶ��ϴ���־"));
	RwData.setKey(m_ParamSpecData.nBlastFlag[1], _T("1"), _T("�ȶ��ϴ���־"));
	return TRUE;
}

