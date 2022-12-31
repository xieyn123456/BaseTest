// ParamSpecEditorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParamSpecEditor.h"
#include "ParamSpecEditorDlg.h"
#include "InputBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParamSpecEditorDlg �Ի���




CParamSpecEditorDlg::CParamSpecEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParamSpecEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CParamSpecEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRLPARAMS, m_listctrlParams);
}

BEGIN_MESSAGE_MAP(CParamSpecEditorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOAD, &CParamSpecEditorDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CParamSpecEditorDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BUTTON1, &CParamSpecEditorDlg::OnBnClickedLoadDat)
END_MESSAGE_MAP()


// CParamSpecEditorDlg ��Ϣ�������

BOOL CParamSpecEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CInputBoxDlg indlg;
	indlg.DoModal();
	if (indlg.m_nLoginSuccessed==0)
	{
		AfxMessageBox(_T("��������¼�ſ�����!!!"));
		exit(0);
	}
	// TODO: �ڴ���Ӷ���ĳ�ʼ������	
	SetWindowText(_T("�������༭��_v1.0.0.5"));
	m_listctrlParams.DeleteList();
	m_listctrlParams.LoadMainList();
	m_listctrlParams.InsertColumn(0,_T("��������"),LVCFMT_LEFT,120);
	m_listctrlParams.InsertColumn(1,_T("��������"),LVCFMT_LEFT,280);
	m_listctrlParams.InsertColumn(2,_T("�޸�Ȩ��"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(3,_T("���ֵ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(4,_T("��Сֵ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(5,_T("��λ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(6,_T("�޸��ϴ���־"),LVCFMT_CENTER,100);
	m_listctrlParams.InsertColumn(7,_T("�ȶ��ϴ���־"),LVCFMT_CENTER,100);			
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CParamSpecEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CParamSpecEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
int CParamSpecEditorDlg::GetApplicationPath(TCHAR *Path)
{
	TCHAR temp[1024];
	TCHAR strPath[1024];
	::GetModuleFileName(NULL,temp,1024);
	int i;
	for(i=1023;temp[i]!='\\';i--)
	{
	}
	wcsncpy_s(strPath,_countof(strPath),temp,i);
	wcsncpy_s(Path,1024,strPath,1024);
	return 0;
}
void CParamSpecEditorDlg::GetAppPath(CString& AppPath)
{
	CString strt=_T("");
	TCHAR temp[1024];
	::GetModuleFileName(NULL,temp,1023);
	strt=(CString)temp;
	int n=strt.ReverseFind('\\');
	AppPath=strt.Left(n);
}
CString CParamSpecEditorDlg::GetTimeStr(CTime t)
{
	CString str=_T("");
	str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	return str;
}
CString CParamSpecEditorDlg::ReadINIPara(CString section,CString key,CString strError,CString path)
{
	CString strValue;
	if (path.IsEmpty())
	{
		GetAppPath(path);
		path=path+_T("/����/����.txt");
	}
	WCHAR strBuffer[200];
	::GetPrivateProfileStringW(section,key ,strError,strBuffer,200,path);
	strValue=(CString)strBuffer;
	strValue.Replace(_T(" "),_T(""));//english
	strValue.Replace(_T(" "),_T(""));//simple-chinese
	return strValue;
}


CString CParamSpecEditorDlg::ReadINIParaSpec(CString section,CString key,CString strError,CString path)
{
	CString strValue;
	if (path.IsEmpty())
	{
		GetAppPath(path);
		path=path+_T("\\����\\ParamSpec.ini");
	}
	WCHAR strBuffer[200];
	::GetPrivateProfileStringW(section,key ,strError,strBuffer,200,path);
	return (CString)strBuffer;
}

void CParamSpecEditorDlg::WriteINIPara(CString section,CString key,CString WriteStr,CString path)
{
	WritePrivateProfileStringW(section,key,WriteStr,path);
}

int CParamSpecEditorDlg::SplitString(CString mainstr, CString delistr, CString strarr[],int arrsize)
//����ֵ:�����ɹ��������; mainstr:��Ҫ�������ַ���; delistr:�ָ����ַ���; strarr[]:�������ص��ַ�������; arrsize:strarr�ַ��������С,
{
	int ncount=0;
	int aindex=-1,bindex=0;
	CString strx;
	for (int i=0;i<arrsize;i++)
	{
		bindex=mainstr.Find(delistr,aindex+1);
		if (bindex!=-1)
		{
			strx=mainstr.Mid(aindex+1,bindex-aindex-1);		
			strarr[i]=strx;
			aindex=bindex;
			ncount++;
		}
		else
		{
			strx=mainstr.Mid(aindex+1); //�����������һ��û�зָ������ַ���
			if (!strx.IsEmpty())
			{
				strarr[i]=strx;
				ncount++;
				break;
			}
			else
			{
				break;
			}
		}
	}
	for (int i=ncount;i<arrsize;i++)
	{
		strarr[i]=_T("");
	}
	return ncount;
}

void CParamSpecEditorDlg::OnBnClickedBtnLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listctrlParams.DeleteList();
	m_listctrlParams.LoadMainList();
	m_listctrlParams.InsertColumn(0,_T("��������"),LVCFMT_LEFT,120);
	m_listctrlParams.InsertColumn(1,_T("��������"),LVCFMT_LEFT,280);
	m_listctrlParams.InsertColumn(2,_T("�޸�Ȩ��"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(3,_T("���ֵ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(4,_T("��Сֵ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(5,_T("��λ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(6,_T("�޸��ϴ���־"),LVCFMT_CENTER,100);
	m_listctrlParams.InsertColumn(7,_T("�ȶ��ϴ���־"),LVCFMT_CENTER,100);		

	int nold=m_listctrlParams.GetItemCount();
	if (nold>0) 
	{
		if (IDNO==AfxMessageBox(_T("��ȷ���Ƿ������������������õ�?\n(��������е�ǰ�ı�!!!)"),MB_YESNO))
		{
			return;
		}
	}	
	m_listctrlParams.DeleteAllItems();

	//���²����б�
	CString strsec=_T(""),strkey=_T(""),strval=_T(""),strdir=_T("");
	std::vector<CString> vecPage;
	GetAppPath(strdir);
	strdir+=_T("\\����\\����.txt");
	for (int i=0;i<100;i++)
	{
		strkey.Format(_T("%d"),i);
		strval=ReadINIPara(_T("��������-�����б�"),strkey);
		if (strval.IsEmpty())
		{
			break;
		}
		else
		{
			vecPage.push_back(strval);
		}
	}

	int nIndex=0;
	vecParamSpec.clear();
	for (unsigned int i=0;i<vecPage.size();i++)
	{
		strsec=_T("��������-")+vecPage[i];

		for (int j=0;j<200;j++)
		{
			strkey.Format(_T("������%d"),j);
			strval=ReadINIPara(strsec,strkey);
			if (strval.IsEmpty())
			{
				break;
			}
			else
			{
				int n=strval.Find(_T(","));
				if (n!=-1)
				{
					strval=strval.Left(n);
				}
				CString strArr[6];
				CString strPath=_T(""),strKey=_T(""),strTemp=_T("");	
				GetAppPath(strPath);
				strPath+=_T("\\����\\ParamSpec.ini");	
				strKey.Format(_T("%d"),nIndex);	
				strTemp = ReadINIParaSpec(_T("�������"),strKey,_T(""),strPath);
				if (!strTemp.IsEmpty())
				{
					SplitString(strTemp,_T(","),strArr,6);	
					PARAMSPEC it;
					it.nAcessLv		=_wtoi(strArr[0]);
					it.dblMaxVal	=_wtof(strArr[1]);
					it.dblMinVal	=_wtof(strArr[2]);
					it.strUnit		= strArr[3];
					it.nModifyFlag	=_wtoi(strArr[4]);
					it.nCheckFlag	=_wtoi(strArr[5]);
					vecParamSpec.push_back(it);
				}
				m_listctrlParams.InsertRow(vecPage[i],strval,vecParamSpec[nIndex].nAcessLv,vecParamSpec[nIndex].dblMaxVal,vecParamSpec[nIndex].dblMinVal,vecParamSpec[nIndex].strUnit,vecParamSpec[nIndex].nModifyFlag,vecParamSpec[nIndex].nCheckFlag);
				nIndex++;
			}	
		}
	}
}

void CParamSpecEditorDlg::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nold=m_listctrlParams.GetItemCount();
	if (nold==0 || IDNO==AfxMessageBox(_T("��ȷ���Ƿ񱣴����������õ�?"),MB_YESNO))
	{
		return;
	}

	CString strPath=_T("");
	GetAppPath(strPath);
	strPath+=_T("\\����\\ParamSpec.ini");
	for (int i=0;i<m_listctrlParams.GetItemCount();i++)
	{
		CString strVal=_T(""),strKey=_T("");
		strVal.Format(_T("%s,%s,%s,%s,%s,%s"),
			m_listctrlParams.GetItemText(i,2),m_listctrlParams.GetItemText(i,3),
			m_listctrlParams.GetItemText(i,4),m_listctrlParams.GetItemText(i,5),
			m_listctrlParams.GetItemText(i,6),m_listctrlParams.GetItemText(i,7));

		strKey.Format(_T("%d"),i);
		WriteINIPara(_T("�������"),strKey,strVal,strPath);
	}
}

void CParamSpecEditorDlg::OnBnClickedLoadDat()
{
	//TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listctrlParams.DeleteList();
	m_listctrlParams.LoadMainList();
	m_listctrlParams.InsertColumn(0,_T("��������"),LVCFMT_LEFT,120);
	m_listctrlParams.InsertColumn(1,_T("��������"),LVCFMT_LEFT,280);
	m_listctrlParams.InsertColumn(2,_T("�޸�Ȩ��"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(3,_T("���ֵ"),LVCFMT_CENTER,80);
	m_listctrlParams.InsertColumn(4,_T("��Сֵ"),LVCFMT_CENTER,80);

	int nold=m_listctrlParams.GetItemCount();
	if (nold>0) 
	{
		if (IDNO==AfxMessageBox(_T("��ȷ���Ƿ������������������õ�?\n(��������е�ǰ�ı�!!!)"),MB_YESNO))
		{
			return;
		}
	}
	TCHAR path[1024];
	GetApplicationPath(path);
	wcscat_s(path,_countof(path),_T("\\����\\ParamSpec.dat"));
	m_ParamSpecData.LoadFromFile(path);

	for (int i=0;i<MAXITEMCNT;i++)
	{	
		if (m_ParamSpecData.nAceLv[i]<0 || m_ParamSpecData.nAceLv[i]>10)
		{
			m_ParamSpecData.nAceLv[i]=0;
		}

		if (m_ParamSpecData.dblMax[i]<-92559631000000 || m_ParamSpecData.dblMax[i]>92559631000000)
		{
			m_ParamSpecData.dblMax[i]=0;
		}

		if (m_ParamSpecData.dblMin[i]<-92559631000000 || m_ParamSpecData.dblMin[i]>92559631000000)
		{
			m_ParamSpecData.dblMin[i]=0;
		}
	}

	m_listctrlParams.DeleteAllItems();

	//���²����б�
	CString strsec=_T(""),strkey=_T(""),strval=_T(""),strdir=_T("");
	std::vector<CString> vecPage;
	GetAppPath(strdir);
	strdir+=_T("\\����\\����.txt");
	for (int i=0;i<100;i++)
	{
		strkey.Format(_T("%d"),i);
		strval=ReadINIPara(_T("��������-�����б�"),strkey);
		if (strval.IsEmpty())
		{
			break;
		}
		else
		{
			vecPage.push_back(strval);
		}
	}

	int nIndex=0;
	for (unsigned int i=0;i<vecPage.size();i++)
	{
		strsec=_T("��������-")+vecPage[i];

		for (int j=0;j<200;j++)
		{
			strkey.Format(_T("������%d"),j);
			strval=ReadINIPara(strsec,strkey);
			if (strval.IsEmpty())
			{
				break;
			}
			else
			{
				int n=strval.Find(_T(","));
				if (n!=-1)
				{
					strval=strval.Left(n);
				}
				m_listctrlParams.InsertRowdat(vecPage[i],strval,m_ParamSpecData.nAceLv[nIndex],m_ParamSpecData.dblMax[nIndex],m_ParamSpecData.dblMin[nIndex]);
				nIndex++;
			}	
		}
	}
}
