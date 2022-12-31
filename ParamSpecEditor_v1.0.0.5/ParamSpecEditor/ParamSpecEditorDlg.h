// ParamSpecEditorDlg.h : ͷ�ļ�
//
#pragma once
#include "afxcmn.h"
#include "EditListCtrl.h"
#include <vector>

CONST UINT MAXITEMCNT=2000;

typedef struct PARAMSPECTABLE
{
	BOOL SaveToFile(TCHAR *ptr)
	{
		FILE *fp;
		if ( ptr!=NULL)
		{
			TRY
			{				
				_wfopen_s(&fp,ptr,_T("wb"));
				if (fp==NULL)
				{
					AfxMessageBox(_T("�ļ�����ʧ��"));

				}
				fwrite(this,sizeof(PARAMSPECTABLE),1,fp);
				fclose(fp);
				return TRUE;
			}
			CATCH(CFileException, pe)
			{		
				return FALSE;
			}
			END_CATCH
		}
		return FALSE;
	}

	BOOL LoadFromFile(TCHAR *ptr)
	{
		FILE *fp;
		if ( ptr!=NULL)
		{
			_wfopen_s(&fp,ptr,_T("rb"));					

			if ( fp == NULL ) 
			{				
				return FALSE;
			}
			TRY
			{				
				fread(this,sizeof(PARAMSPECTABLE),1,fp);
				fclose(fp);
				return TRUE;
			}
			CATCH(CFileException, pe)
			{		
				return FALSE;
			}
			END_CATCH
		}
		return FALSE;
	}

	double	dblMax[MAXITEMCNT];
	double	dblMin[MAXITEMCNT];
	int		nAceLv[MAXITEMCNT];
	int		nModifyFlag[MAXITEMCNT];
	int		nCheckFlag[MAXITEMCNT];
}PARAMSPECTABLE;

struct PARAMSPEC
{
	double dblMaxVal;
	double dblMinVal;
	int nAcessLv;
	int nModifyFlag;
	int nCheckFlag;
	CString strUnit;

	PARAMSPEC ()
	{
		dblMaxVal=0;
		dblMinVal=0;
		nAcessLv=0;
		nModifyFlag=0;
		nCheckFlag=0;
		strUnit=_T("");
	}
};

// CParamSpecEditorDlg �Ի���
class CParamSpecEditorDlg : public CDialog
{
// ����
public:
	CParamSpecEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PARAMSPECEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	EditListCtrl m_listctrlParams;
	PARAMSPECTABLE m_ParamSpecData;

	std::vector<PARAMSPEC> vecParamSpec;

	int GetApplicationPath(TCHAR *Path);
	void GetAppPath(CString& AppPath);
	CString GetTimeStr(CTime t=CTime::GetCurrentTime());
	CString ReadINIPara(CString section,CString key,CString strError=_T(""),CString path=_T(""));
	CString ReadINIParaSpec(CString section,CString key,CString strError,CString path);
	void WriteINIPara(CString section,CString key,CString WriteStr,CString path);
	int SplitString(CString mainstr, CString delistr, CString strarr[],int arrsize);
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedLoadDat();
};
