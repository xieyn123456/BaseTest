// ParamSpecEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CParamSpecEditorApp:
// �йش����ʵ�֣������ ParamSpecEditor.cpp
//

class CParamSpecEditorApp : public CWinApp
{
public:
	CParamSpecEditorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CParamSpecEditorApp theApp;