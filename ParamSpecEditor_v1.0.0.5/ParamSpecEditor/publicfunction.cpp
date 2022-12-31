
void ::GetApplicationVersion()
{
	CString valStr; 
	HRSRC hsrc=FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	HGLOBAL hgbl=LoadResource(0,hsrc);
	BYTE *pBt=(BYTE *)LockResource(hgbl);
	VS_FIXEDFILEINFO* pFinfo = (VS_FIXEDFILEINFO*)(pBt+40);  


	//typedef struct tagVS_FIXEDFILEINFO { 
	//  DWORD dwSignature;         /* signature - always 0xfeef04bd */
	//  DWORD dwStrucVersion;      /* structure version - currently 0 */
	//  DWORD dwFileVersionMS;   /* Most significant file version dword */
	//  DWORD dwFileVersionLS;  /* Least significant file version dword */
	//  DWORD dwProductVersionMS;  /* Most significant product version */
	//  DWORD dwProductVersionLS;  /* Least significant product version */
	//  DWORD dwFileFlagMask;      /* File flag mask */
	//  DWORD dwFileFlags;         /* Debug/retail/prerelease/... */
	//  DWORD dwFileOS;      /* OS type. Will always be Windows32 value */
	//  DWORD dwFileType;          /* Type of file (dll/exe/drv/... )*/
	//  DWORD dwFileSubtype;       /* File subtype */
	//  DWORD dwFileDateMS;        /* Most significant part of date */
	//  DWORD dwFileDateLS;        /* Least significant part of date */
	//} VS_FIXEDFILEINFO;

	valStr.Format(_T("File Version: %d.%d.%d.%d"),
		(pFinfo->dwProductVersionMS >> 16) & 0xFF,
		(pFinfo->dwProductVersionMS) & 0xFF,
		(pFinfo->dwProductVersionLS >> 16) & 0xFF,
		(pFinfo->dwProductVersionLS) & 0xFF );   


	AfxMessageBox(valStr);
} 

#pragma comment(lib, "version.lib")

CString iGetApplicationVersion()
{
	TCHAR szFullPath[MAX_PATH];
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO * pFileInfo;

	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
	dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
	if (dwVerInfoSize)
	{
		// If we were able to get the information, process it:
		HANDLE  hMem;
		LPVOID  lpvMem;
		unsigned int uInfoSize = 0;

		hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);

		::VerQueryValue(lpvMem, (LPTSTR)_T("\\"), (void**)&pFileInfo, &uInfoSize);

		CString strVersion ;
		int ret = GetLastError();
		WORD m_nProdVersion[4];

		// Product version from the FILEVERSION of the version info resource 
		m_nProdVersion[0] = HIWORD(pFileInfo->dwFileVersionMS); 
		m_nProdVersion[1] = LOWORD(pFileInfo->dwFileVersionMS);
		m_nProdVersion[2] = HIWORD(pFileInfo->dwFileVersionLS);
		m_nProdVersion[3] = LOWORD(pFileInfo->dwFileVersionLS); 

		strVersion.Format(_T("The file's version : %d.%d.%d.%d"),m_nProdVersion[0],
			m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
		//AfxMessageBox(strVersion);

		// Product version from the FILEVERSION of the version info resource 
		/*m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
		m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
		m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
		m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 


		strVersion.Format(_T("The product's version : %d.%d.%d.%d"),m_nProdVersion[0],
			m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);*/
		//AfxMessageBox(strVersion);

		GlobalUnlock(hMem);
		GlobalFree(hMem);

		return strVersion;
		
	}
}

int CFunMod::Delay(int ProgramNum,double time)
{
	static MSG msg;
	long Curtime1,Curtime2=GetTickCount();
	while(true)
	{
		if( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) )
		{
			AfxGetApp()->PumpMessage();
		}
		Sleep(1);
		if((m_DataBaseWin->GetS(0)==1 && ProgramNum<90) || (m_DataBaseWin->GetS(1)==1 && ProgramNum<90) || 
			m_DataBaseWin->GetS(1997)==1 || m_DataBaseWin->GetS(1999)==1 || m_DataBaseWin->GetS(1600+ProgramNum)==1)//软件急停 || 硬件急停 || 流程图停止 || 系统退出
		{
			return -1;
		}

		Curtime1=GetTickCount()-Curtime2;
		if(Curtime1>=long(time)) return 0;
	}
}

int ::SplitString(CString mainstr, CString delistr, CString strarr[],int arrsize)
//返回值:解析成功结果数量; mainstr:需要解析的字符串; delistr:分隔符字符串; strarr[]:用来返回的字符串数组; arrsize:strarr字符串数组大小,
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
			strx=mainstr.Mid(aindex+1); //用来解析最后一项没有分隔符的字符串
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
int CDataToolPageDlg::EnsureFolderPathExist(CString strFolder)
{
	CString strArr[10];
	int n=SplitString(strFolder,_T("\\"),strArr,10);

	CString str=_T("");

	for (int i=0;i<n;i++)
	{
		if (i==0)
		{
			str=strArr[0];
		}
		else
		{
			str+=_T("\\")+strArr[i];
		}
		if (PathFileExists(str)==FALSE)
		{
			if (i==0)//磁盘根目录不存在
			{
				return 1;
			}
			else
			{
				if (!CreateDirectory(str,NULL))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
int CFunMod::GetFolderFileList(CString folderpath,CString strFileArr[],int arrsize)
{
	int nFileCnt=0;
	CFileFind tempFind;
	BOOL bFound; //判断是否成功找到文件
	bFound=tempFind.FindFile(folderpath+_T("\\*.*")); 
	while(bFound)      //遍历所有文件
	{
		bFound=tempFind.FindNextFile(); //第一次执行FindNextFile是选择到第一个文件，以后执行为选择

		if(tempFind.IsDirectory() || tempFind.IsDots())   //找到的是文件夹，则遍历该文件夹下的文件
		{
			continue;
		}
		else
		{
			strFileArr[nFileCnt]=tempFind.GetFileName(); //保存文件名，包括后缀名
			nFileCnt++;
		}
	}
	tempFind.Close();
	return nFileCnt;
}
int SplitStringM(CString mainstr, CString delistr, CString strarr[],int arrsize)//多个分隔符版本
//返回值:解析成功结果数量; mainstr:需要解析的字符串; delistr:分隔符字符串; strarr[]:用来返回的字符串数组; arrsize:strarr字符串数组大小,
{
	int ncount=0;
	int aindex=-1,bindex=0;
	CString strx;
	int nmax=delistr.GetLength();
	if (nmax>20) nmax=20;
	CString deliArr[20];
	for (int i=0;i<nmax;i++)
	{
		deliArr[i]=delistr.Mid(i,1);
	}
	for (int i=0;i<arrsize;i++)
	{
		for (int j=0;j<nmax;j++)
		{
			bindex=mainstr.Find(deliArr[j],aindex+1);
			if (bindex!=-1 && deliArr[j]!=_T(""))
			{
				break;
			}
		}
		//bindex=mainstr.Find(delistr,aindex+1);
		if (bindex!=-1)
		{
			strx=mainstr.Mid(aindex+1,bindex-aindex-1);		
			strarr[i]=strx;
			aindex=bindex;
			ncount++;
		}
		else
		{
			strx=mainstr.Mid(aindex+1); //用来解析最后一项没有分隔符的字符串
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
int CFunMod::SplitStringN(CString mainstr, CString delistr, CString strarr[],int arrsize)//分隔符长度可以为多位
{
	int delistrlen=delistr.GetLength();
	int ncount=0;
	int aindex=(0-delistrlen),bindex=0;
	CString strx;
	for (int i=0;i<arrsize;i++)
	{
		bindex=mainstr.Find(delistr,aindex+delistrlen);
		if (bindex!=-1)
		{
			strx=mainstr.Mid(aindex+delistrlen,bindex-aindex-delistrlen);		
			strarr[i]=strx;
			aindex=bindex;
			ncount++;
		}
		else
		{
			strx=mainstr.Mid(aindex+delistrlen); //用来解析最后一项没有分隔符的字符串
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

#import   "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename   ("EOF",   "adoEOF")
int InsertRecordToDB(CString strt,CString ucode,CString fcode)	//向数据库插入记录
{
	try
	{
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_CommandPtr m_pCommanda;
		CString dbpath;
		CTime ct=CTime::GetCurrentTime();
		dbpath.Format(_T("CodeData%d%02d"),ct.GetYear(),ct.GetMonth());
		dbpath=_T("D:\\CODEDATA\\")+dbpath+_T(".mdb");
		if (!PathFileExists(dbpath))
		{
			CopyFile(_T("D:\\CODEDATA\\CODEDATAblank.mdb"),dbpath,TRUE);
		}
		
		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source="+_bstr_t(dbpath)+";Jet OLEDB:Database Password=sae";


		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10;   
			//hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CodeDataopen.mdb","","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,无密码的数据库
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库
			//hr = m_pConnection->Open("Provider=Microsoft.Ace.Oledb.12.0;Data Source=D:\\MessageDB.accdb;Jet OLEDB:Database Password=84952...","", "", adModeUnknown);//这是OFFICE2007以上的,包括OFFICE2010,这个连接字符串就是在OFFICE2010下用的,没问题
			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			CString strInsert; 
			strInsert.Format(_T("INSERT INTO CODEDATA (INPUTTIME,UUTCODE,FIXTURECODE) VALUES('%s','%s','%s');"),strt,ucode,fcode); 
			_variant_t RecordsAffected; 
			m_pConnectiona->Execute(_bstr_t(strInsert),&RecordsAffected,adCmdText); 	
		
		m_pConnectiona->Close();
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("写入数据库失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return 1;
	}
	return 0;
}
void ::InsertDataToDB(CString strbandsn,CString strfixturesn)//插入一条等待上传数据到数据库
{
	bool bfindexist=TRUE;
	try
	{
		CoInitialize(NULL);
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_CommandPtr m_pCommanda;
		_RecordsetPtr m_pRecordSeta;

		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CODEDATA\\KJTrackCommDB.mdb;Jet OLEDB:Database Password=saejong.kjtrackcomm";

		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10; 
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库
			//检测是否有记录存在
			CString strs=_T("");
			strs.Format(_T("SELECT * FROM LOADTABLE WHERE [STRFIXTURESN]='%s';"),strfixturesn);
			_bstr_t x=_bstr_t(strs);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (m_pRecordSeta == NULL || m_pRecordSeta->adoEOF) 
			{ 
				bfindexist=FALSE;
			} 


			//插入或者更新
			//  
			//hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库

			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			CString strtime;
			CTime ct=CTime::GetCurrentTime();
			strtime.Format(_T("%d/%d/%d %d:%d:%d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
			CString strInsert; 
			if (bfindexist==FALSE)
			{
				strInsert.Format(_T("INSERT INTO LOADTABLE ([STRTIME],[STRBANDSN],[STRFIXTURESN]) VALUES ('%s','%s','%s');"),
					strtime,strbandsn,strfixturesn); 
			}
			else
			{
				strInsert.Format(_T("UPDATE LOADTABLE SET [STRTIME]='%s',[STRBANDSN]='%s' WHERE [STRFIXTURESN]='%s';"),
					strtime,strbandsn,strfixturesn); 
			}
			
			_variant_t RecordsAffected; 
			m_pConnectiona->Execute(_bstr_t(strInsert),&RecordsAffected,adCmdText); 	

			m_pConnectiona->Close();
			CoUninitialize();
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("写入数据库失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return ;
	}
	return ;
}
#import   "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename   ("EOF",   "adoEOF")
int ::SelectRecordFromDB(CString strs,CString strArr[][4])//从数据库读取记录到二维数组
{
	try
	{
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_RecordsetPtr m_pRecordSeta;
		CString dbpath;
		CTime ct=CTime::GetCurrentTime();
		dbpath.Format(_T("CodeData%d%02d"),ct.GetYear(),ct.GetMonth());
		dbpath=_T("D:\\CODEDATA\\")+dbpath+_T(".mdb");
		if (!PathFileExists(dbpath))
		{
			return 0;
		}

		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source="+_bstr_t(dbpath)+";Jet OLEDB:Database Password=sae";


		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10;   
			//hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CodeDataopen.mdb","","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,无密码的数据库
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库
			//hr = m_pConnection->Open("Provider=Microsoft.Ace.Oledb.12.0;Data Source=D:\\MessageDB.accdb;Jet OLEDB:Database Password=84952...","", "", adModeUnknown);//这是OFFICE2007以上的,包括OFFICE2010,这个连接字符串就是在OFFICE2010下用的,没问题

			_bstr_t x=_bstr_t(strs);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (m_pRecordSeta == NULL) 
			{ 
				AfxMessageBox(_T("RecordSet 对象创建失败! 请确认是否初始化了COM环境.")); 
				return 0;
			} 
			if (m_pRecordSeta->adoEOF)
			{
				AfxMessageBox(_T("无法查找到记录: \r\n"+strs)); 
				return 0;
			}
			m_pRecordSeta->MoveFirst();  

			int i=0; 
			while (!m_pRecordSeta->adoEOF) 
			{ 				
				strArr[i][0] = m_pRecordSeta->GetCollect("ID"); 
				strArr[i][1] = m_pRecordSeta->GetCollect("INPUTTIME"); 
				strArr[i][2] = m_pRecordSeta->GetCollect("UUTCODE"); 
				strArr[i][3] = m_pRecordSeta->GetCollect("FIXTURECODE"); 
				m_pRecordSeta->MoveNext(); 
				i++; 
			} 	
		
			m_pConnectiona->Close();
			return i;
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取数据库失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return 0;
	}
}

CString ::ReadINIPara(CString section,CString key,CString strError,CString path)
{
	WCHAR strBuffer[200];
	::GetPrivateProfileStringW(section,key ,strError,strBuffer,200,path);
	return (CString)strBuffer;
}

//写入INI配置档单项配置
void ::WriteINIPara(CString section,CString key,CString WriteStr,CString path)
{
	WritePrivateProfileStringW(section,key,WriteStr,path);
}

//获取当前文件路径
void GetAppPath(CString& AppPath)
{
	CString strt=_T("");
	TCHAR temp[1024];
	::GetModuleFileName(NULL,temp,1023);
	strt=(CString)temp;
	int n=strt.ReverseFind('\\');
	AppPath=strt.Left(n);
}

//取得当前时间,可选择是否显示日期,时间与毫秒数
CString GetSTime(bool bShowDates,bool bShowTimes,bool bShowMillseconds)
{//获取当前时间函数
	//bShowDads: year/month/day
	//bShowTimes:hour/minutes/second/milisecond
	CString strDates,strTimes;
	SYSTEMTIME time;
	GetLocalTime(&time);
	if(bShowDates)
	{
		strDates.Format(_T("%d-%d-%d"),time.wYear,time.wMonth,time.wDay);
	}
	else
	{
		strDates=L"";
	}
	if(bShowTimes)
	{
		if (bShowMillseconds)
		{
			strTimes.Format(_T("%02d:%02d:%02d.%d"),time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		}
		else
		{
			strTimes.Format(_T("%02d:%02d:%02d"),time.wHour,time.wMinute,time.wSecond);
		}
	}
	else
	{
		strTimes=L"";
	}
	if(!strTimes.IsEmpty()&&!strDates.IsEmpty())
	{
		strDates+=L"_";
	}
	return strDates+strTimes;
}
CString GetStrTime(bool bShowDates,bool bShowTimes)
{
	CString strDates,strTimes,retstr;
	retstr=_T("");
	CTime t=CTime::GetCurrentTime();
	strDates=t.Format(_T("%Y/%m/%d "));
	strTimes=t.Format(_T("%H:%M:%S"));

	if (bShowDates)
	{
		retstr+=strDates;
	}
	if (bShowTimes)
	{
		retstr+=strTimes;
	}
	return retstr;
}

//解密文件
bool ToUnEncryptFile(CString szFileName)
{
	CFileFind finder;
	finder.FindFile(szFileName,0);

	if(!finder.FindFile(szFileName,0))
	{
		AfxMessageBox(_T("[Err]找不到文件，解密文件失败!"));
		return FALSE;
	}

	CFile* file;
	DWORD dwFileLen;
	char* pData = NULL;

	file= new CFile;

	if(!file->Open(szFileName,CFile::shareDenyNone|CFile::modeReadWrite))
	{
		AfxMessageBox(_T("[Err]解密文件失败，文件将被删除!"));
		delete file;
		::DeleteFile(szFileName);
		return FALSE;
	}

	dwFileLen=(DWORD)file->GetLength(); 
	pData=new char[(int)dwFileLen];

	file->SeekToBegin();//定位到文件开头
	file->Read(pData,dwFileLen);

	for(int i =0;i< (int)dwFileLen;i++)
	{	
		pData[i]^=g_lnPwKey;
		pData[i]^=(dwFileLen);
	}

	file->SeekToBegin();
	file->Write(pData,dwFileLen);
	file->SetLength(dwFileLen);
	file->Close();

	delete [] pData;
	delete file;

	return TRUE;
}

//加密文件
bool ToEncryptFile(CString szFileName)
{
	CFileFind finder;
	finder.FindFile(szFileName,0);	
	if(!finder.FindFile(szFileName,0))
	{
		AfxMessageBox(_T("[Err]找不到文件，加密文件失败!"));
		return FALSE;
	}

	CFile* file;
	DWORD dwFileLen;
	char* pData = NULL;

	file= new CFile;
	if(!file->Open(szFileName,CFile::shareDenyNone|CFile::modeReadWrite))
	{
		AfxMessageBox(_T("[Err]加密文件失败，文件将被删除!"));
		delete file;
		::DeleteFile(szFileName);
		return FALSE;
	}

	dwFileLen=(DWORD)file->GetLength();
	pData=new char[(int)dwFileLen];

	file->SeekToBegin();
	file->Read(pData,dwFileLen);

	for(int i =0;i< (int)dwFileLen;i++)
	{
		pData[i]^=g_lnPwKey;
		pData[i]^=dwFileLen;
	}

	file->SeekToBegin();
	file->Write(pData,dwFileLen);

	delete [] pData;
	delete file;
	return TRUE;
}

bool DateDiff(CString strtime)
{
	TCHAR * chartime=(TCHAR*)(LPCTSTR)strtime;
	CString sFormat=_T("%d/%d/%d %d:%d:%d");
	TCHAR* charformat=(TCHAR*)(LPCTSTR)sFormat;
	int nyear,nmonth,nday,nhour,nminute,nsec;
	swscanf_s(chartime,charformat,&nyear,&nmonth,&nday,&nhour,&nminute,&nsec);
	CTime t(nyear,nmonth,nday,nhour,nminute,nsec);
	CTimeSpan ts=CTime::GetCurrentTime()-t;
	if (ts.getTotalHours>=24)
	{
		return true;
	}
	else
	{
		return false
	}
}

int WriteSqlDBProcess() //写入远程SQL数据库
{
	HRESULT hr;
	_ConnectionPtr m_pConnectiona;
	_CommandPtr m_pCommanda;
	_RecordsetPtr m_pRecordset;

	try
	{
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			return 1;//初始化COM失败
		}

		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (FAILED(hr))
		{
			return 1;//对象指针实例化失败
		}

		//Data Source 数据源，简单说就是你安装数据库那台机器，.代表本机。如果在其它机器中等号后面填写要连接的主机IP。
		//Initial Catalog是你要连接的数据库的名字。
		//User ID 连接数据库用户名。
		//Pwd 连接数据库密码。
		//Persist Security Info是否保存安全信息，可理解为”ADO在数据库连接成功后是否保存密码信息”，True表示保存，False表示不保存
		m_pConnectiona->ConnectionTimeout = 5;
		m_pConnectiona->ConnectionString = "Provider=SQLOLEDB;Data Source=GODEYES01\\BG01;Initial Catalog=GodEyes01;User ID=GodEyes;PWD=123456;Server=169.254.211.96,1433";
		hr = m_pConnectiona->Open("","","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库
		if (SUCCEEDED(hr))
		{
			CTime time = CTime::GetCurrentTime();
			m_GodEyesParam.strLastUpdateTime = time.Format(_T("%Y/%m/%d %H:%M:%S"));

			CString strInsert;
			_variant_t RecordsAffected;
			strInsert.Format(_T("INSERT INTO %s(Customer,LastUpdateTime,Area,Line,Process_ID,EQU_ID,EQU_Type,Count_Output,Count_Fail,Count_Output_R,Count_Output_L,Pre_A,Pre_B,Flow_A,Flow_B,Mix_Ration,DHH,Yield,Speed,Pip_Life,Pip_Time,Equ_Status,ErrorMsg) VALUES('%s','%s','%s','%s','%s','%s','%s',%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%d,'%s',%d,'%s')"),
				m_GodEyesParam.strTitle,m_GodEyesParam.strCustomer,m_GodEyesParam.strLastUpdateTime,m_GodEyesParam.strArea,m_GodEyesParam.strLine,m_GodEyesParam.strProcessID,m_GodEyesParam.strEquID,m_GodEyesParam.strEquType,(m_GodEyesParam.nCountOutput-m_GodEyesParam.nCountOutputEx),diff,(m_GodEyesParam.nCountOutputR-m_GodEyesParam.nCountOutputREx),(m_GodEyesParam.nCountOutputL-m_GodEyesParam.nCountOutputLEx),m_GodEyesParam.dPreA,m_GodEyesParam.dPreB,m_GodEyesParam.dFlowA,m_GodEyesParam.dFlowB,m_GodEyesParam.dMixRation,m_GodEyesParam.dDHH,m_GodEyesParam.dYield,m_GodEyesParam.dSpeed,m_GodEyesParam.nPipLife,m_GodEyesParam.strPipTime,m_GodEyesParam.nEquStatus,m_GodEyesParam.strErrorMsg);
			m_pConnectiona->Execute(_bstr_t(strInsert),&RecordsAffected,adCmdText);

		}
	}
	catch(_com_error e)///捕捉异常6
	{
		CTime time = CTime::GetCurrentTime();
		CString errormessage;
		errormessage.Format(_T("写入数据库失败!错误信息:%s"),(LPCTSTR)e.Description());
		m_lstMsg.AddString(time.Format(_T("%Y/%m/%d %H:%M:%S:  ")) + errormessage);
		m_lstMsg.SetCurSel(m_lstMsg.GetCount() - 1);

	}

	if (m_pConnectiona->State == 1)
	{
		m_pConnectiona->Close();
	}
	return 0;
}
void WriteLog(CString strmsg,CString strpath=_T(""))
{
	CTime t=CTime::GetCurrentTime();
	CString strfilename=_T("");
	strfilename.Format(_T("%d%2d%2d"),t.GetYear(),t.GetMonth(),t.GetDay());
	CString strpath;
	GetAppPath(strpath);
	strpath=strpath+_T("\\Data\\") +strfilename+ _T(".txt");
		
	CFile hLog;
	hLog.Open(strpath,CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	hLog.SeekToEnd();

	USES_CONVERSION;
	char * buf=T2A(strmsg);
	hLog.Write(buf,strlen(buf));
	hLog.Close();
}
//************************************************************************
//线程同步: 互斥锁
	//初始化:
	HANDLE hMutex;
	hMutex=CreateMutex(NULL,TRUE,_T("t"));
	ReleaseMutex(hMutex);

	//使用
	WaitForSingleObject(hMutex,INFINITE);
	//do something...
	ReleaseMutex(hMutex);
//************************************************************************

//播放声音
#include <MMSystem.h>
#pragma comment(lib, "Winmm")
PlaySound(_T("D:\\mailin.wav"), NULL,SND_FILENAME | SND_ASYNC);


#pragma warning(disable:4146)
#import  "C:\Program Files\Common Files\System\ado\msado15.dll" named_guids rename ("EOF","adoEOF") rename ("BOF","adoBOF")
#pragma warning(default:4146)
#import  "C:/Program Files/Common Files/System/ADO/msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
#import  "c:/Program Files/Common Files/System/ADO/Msadox.dll"  rename_namespace("ADOCG") rename("EOF", "adoXEOF") rename("DataTypeEnum","adoXDataTypeEnum") 
using namespace ADODB;  
using namespace ADOCG;
int	::TraceDBInsertData(TRACEDATA pdata)//将贴合机发来的数据保存到数据库
{
	CString strInsert,strDelete; 
	try
	{
		::CoInitialize(NULL);
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_CommandPtr m_pCommanda;
		_bstr_t constr;
		_variant_t RecordsAffected; 

		constr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\TraceCollect\\TraceCollect.mdb;Jet OLEDB:Database Password=saejong.trace";
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10;   
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库
			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			strDelete.Format(_T("DELETE * FROM trace_collect WHERE [bg_sn] = '%s'"),pdata.strBgSn);
			m_pConnectiona->Execute(_bstr_t(strDelete),&RecordsAffected,adCmdText); 	

			strInsert.Format(_T("INSERT INTO trace_collect([bg_sn],[assy_start_time],[assy_stop_time],[station_id],[head_id],[line_id],[line_type],[machine_id],[fixture_id],[sw_version],[full_sn_bg],[bg_glue_start_time],[bg_glue_stop_time],[bg_cavity_id],[bg_glue_process_rev],[bg_glue_machine_id],[bg_glue_fixture_id],[bg_glue_open_time],[full_sn_band],[bd_glue_start_time],[bd_glue_stop_time],[bd_cavity_id],[bd_glue_process_rev],[bd_glue_machine_id],[bd_glue_fixture_id],[bd_glue_open_time],[status],[assy_process_rev],[bg_sw_version],[bd_sw_version],[assy_bond_time],[assy_bond_end_time],[audit]) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');"),
				pdata.strBgSN,pdata.strAssyStartTime,pdata.strAssyStopTime,pdata.strStationID,pdata.strHeadID,pdata.strLineID,pdata.strLineType,pdata.strMachineID,pdata.strFixtureID,pdata.strVersion,
				pdata.strBgFullSN,pdata.strBgGlueStartTime,pdata.strBgGlueStopTime,pdata.strBgGlueCavityID,pdata.strBgGlueProcessRev,pdata.strBgGlueMachineID,pdata.strBgGlueFixtureID,pdata.strBgGlueOpenTime,
				pdata.strBandFullSN,pdata.strBandGlueStartTime,pdata.strBandGlueStopTime,pdata.strBandGlueCavityID,pdata.strBandGlueProcessRev,pdata.strBandGlueMachineID,pdata.strBandGlueFixtureID,pdata.strBandGlueOpenTime,
				pdata.strPdcaDataStatus,pdata.strProcessRev,pdata.strBgGlueVersion,pdata.strBandGlueVersion,pdata.strBondStartTime,pdata.strBondStopTime,pdata.strAuditMode); 
			m_pConnectiona->Execute(_bstr_t(strInsert),&RecordsAffected,adCmdText); 	
			m_pConnectiona->Close();
			::CoUninitialize();

			SaveCsvLog(_T("数据信息"),strInsert,_T("InsertDBRecord"));
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("%s,%s"),e.ErrorMessage(),pdata.strBgFullSN);
		SaveCsvLog(_T("Error,Data"),errormessage,_T("InsertDBError"));
		::CoUninitialize();
		return 1;
	}
	return 0;
}
void ::InsertDataToDB()//插入一条等待上传数据到数据库
{
	try
	{
		CoInitialize(NULL);
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_CommandPtr m_pCommanda;
		_RecordsetPtr m_pRecordSeta;

		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CODEDATA\\KJTrackBufferDB.mdb;Jet OLEDB:Database Password=bg@saejong";

		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10; 
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库

			strDelete.Format(_T("DELETE * FROM trace_collect WHERE [bg_sn] = '%s'"),pdata.strBgSn);
			m_pConnectiona->Execute(_bstr_t(strDelete),&RecordsAffected,adCmdText); 
			//插入

			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			CString strtime;
			CTime ct=CTime::GetCurrentTime();
			strtime.Format(_T("%d/%d/%d %d:%d:%d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
			CString strInsert; 

			strInsert.Format(_T("INSERT INTO BUFFERTABLE ([STRTIME],[STRBGSN],[STRBANDSN],[STRFIXTURESN],[STRDISPENNAME],[STRPASTENAME]) VALUES ('%s','%s','%s','%s','%s','%s');"),
					strtime,
					m_MotionData.m_ShowInfo.strBgSn,
					m_MotionData.m_ShowInfo.strBandSn,
					m_MotionData.m_ShowInfo.strFixutreSn,
					m_MotionData.m_ShowInfo.strBgDispenName,
					m_MotionData.m_ShowInfo.strPasteName); 

			_variant_t RecordsAffected; 
			m_pConnectiona->Execute(_bstr_t(strInsert),&RecordsAffected,adCmdText); 	

			m_pConnectiona->Close();
			CoUninitialize();
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("写入数据库失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return ;
	}
	return ;
}
int ::ReadDataFromDB(CString& strbg,CString& strband,CString& strfixture)//从数据库读取一条等待上传数据
{
	CString str2=_T("");
	long t=0;
	try
	{		
		CoInitialize(NULL);
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_RecordsetPtr m_pRecordSeta;

		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CODEDATA\\KJTrackBufferDB.mdb;Jet OLEDB:Database Password=bg@saejong";


		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10;   
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库

			CString strs=_T("");
			strs=_T("SELECT TOP 1 * FROM BUFFERTABLE;");
			_bstr_t x=_bstr_t(strs);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (m_pRecordSeta == NULL) 
			{ 
				return 1;
			} 
			if (m_pRecordSeta->adoEOF)
			{
				return 1;
			}
			m_pRecordSeta->MoveFirst();

			strbg=m_pRecordSeta->GetCollect(_T("STRBGSN"));
			strband=m_pRecordSeta->GetCollect("STRBANDSN");
			strfixture=m_pRecordSeta->GetCollect("STRFIXTURESN");

			m_pConnectiona->Close();
			CoUninitialize();
			return 0;
		}
		else
		{
			return 1;
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取/删除数据库记录失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return 1;
	}
}
void ::DeleteDataFromDB(CString strbg)//从数据库删除一条等待上传数据
{
	try
	{
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_CommandPtr m_pCommanda;

		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CODEDATA\\KJTrackBufferDB.mdb;Jet OLEDB:Database Password=bg@saejong";


		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10;   
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库
			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			CString strdelete; 
			strdelete.Format(_T("DELETE * FROM BUFFERTABLE WHERE [STRBGSN]='%s';"),strbg); 
			_variant_t RecordsAffected; 
			m_pConnectiona->Execute(_bstr_t(strdelete),&RecordsAffected,adCmdText); 	

			m_pConnectiona->Close();
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("数据库删除记录失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return ;
	}
	return ;
}
int ::GetDataCntFromDB()//获取数据库表格数据数量
{

	CString str=_T("");
	long t=-1;
	try
	{		
		CoInitialize(NULL);
		HRESULT hr;
		_ConnectionPtr m_pConnectiona;
		_RecordsetPtr m_pRecordSeta;

		_bstr_t constr;
		constr="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\CODEDATA\\KJTrackBufferDB.mdb;Jet OLEDB:Database Password=bg@saejong";


		hr=m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout   =   10;   
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);//这是OFFICE2003和ACCESS2003以下的,带密码的数据库

			CString strs=_T("");
			strs=_T("SELECT COUNT (*) FROM BUFFERTABLE;");
			_bstr_t x=_bstr_t(strs);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			
			t=m_pRecordSeta->Fields->GetItem((long)0)->GetValue();

			m_pConnectiona->Close();
			CoUninitialize();
			return t;
		}
		else
		{
			return t;
		}
	}
	catch(_com_error   e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取/删除数据库记录失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return t;
	}
}

int WriteCsvLog(CString str)
{
	CStdioFile file;
	CString strFileName,strLogTime,strFloderYear,strFloderMonth,temp,tempWrite;
	CTime m_Date = CTime::GetCurrentTime();
	strFileName=_T("CoderData-")+m_Date.Format("%Y-%m-%d.csv");//
	strLogTime=m_Date.Format("%Y.%m.%d  %H:%M:%S");
	strFloderYear=m_Date.Format(_T("%Y"))+_T("年");//
	strFloderMonth=m_Date.Format(_T("%m"))+_T("月");//

	temp=_T("D:\\CODEDATA");
	if (PathIsDirectory(temp)==FALSE)	 CreateDirectory(temp, NULL);//判断路径是否存在，不存在则创建
	temp=_T("D:\\CODEDATA\\CoderData");
	if (PathIsDirectory(temp)==FALSE)	 CreateDirectory(temp, NULL);//判断路径是否存在，不存在则创建
	temp=_T("D:\\CODEDATA\\CoderData\\")+strFloderYear;
	if (PathIsDirectory(temp)==FALSE)	 CreateDirectory(temp, NULL);//判断路径是否存在，不存在则创建
	temp=_T("D:\\CODEDATA\\CoderData\\")+strFloderYear+_T("\\")+strFloderMonth;
	if (PathIsDirectory(temp)==FALSE)	 CreateDirectory(temp, NULL);//判断路径是否存在，不存在则创建

	temp=_T("D:\\CODEDATA\\CoderData\\")+strFloderYear+_T("\\")+strFloderMonth+_T("\\")+strFileName;
	file.Open(temp,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText);//打开文件
	file.SeekToEnd();
	USES_CONVERSION;

	tempWrite=strLogTime+_T(",")+str+_T("\n");
	char * ss = T2A(tempWrite);
	file.Write(ss,strlen(ss));
	file.Close(); 
	return 0;
}

int CTraceUploadDlg::SaveCsvLog(CString fileTitle,CString fileContent,CString fileName)
{
	CStdioFile file;
	BOOL bNeedWriteTitle = FALSE,strResult = FALSE;
	CString strFileName,strLogTime,strFloderYear,strFloderMonth,temp,tempWrite,path;
	SYSTEMTIME time;
	GetLocalTime(&time);
	if (fileName.Find(_T(".csv")) == -1 && fileName.Find(_T(".CSV")) == -1)
	{
		temp.Format(_T("-%d-%02d-%02d.csv"),time.wYear,time.wMonth,time.wDay);
		fileName += temp;
	}
	strFileName = fileName;

	strLogTime.Format(_T("[%02d:%02d:%02d.%03d]"),time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	strFloderYear.Format(_T("%d年"),time.wYear);//
	strFloderMonth.Format(_T("%02d月"),time.wMonth);//
	GetAppPath(path);
	if (path.Find(_T(".exe")) != -1)
	{
		path = path.Left(path.ReverseFind('\\'));
	}

	temp.Format(_T("%s\\Data"),path);
	if (PathIsDirectory(temp)==FALSE)	 //判断路径是否存在，不存在则创建
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\TestData"),path);
	if (PathIsDirectory(temp)==FALSE)	 //判断路径是否存在，不存在则创建
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\TestData\\%s"),path,strFloderYear);
	if (PathIsDirectory(temp)==FALSE)	 //判断路径是否存在，不存在则创建
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\TestData\\%s\\%s"),path,strFloderYear,strFloderMonth);
	if (PathIsDirectory(temp)==FALSE)	//判断路径是否存在，不存在则创建	 
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\TestData\\%s\\%s\\%s"),path,strFloderYear,strFloderMonth,strFileName);
	if (PathFileExists(temp) == FALSE)
	{
		bNeedWriteTitle = TRUE;
	}

	try
	{
		strResult = file.Open(temp,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText);//打开文件
		if (!strResult)
		{
			//SendMotionInfo(_T("Log文件保存失败."));
			temp.Replace(_T(".csv"),_T(".txt"));
			::WritePrivateProfileString(_T("Error"),strLogTime,fileContent,temp);
			return 1;
		}
		file.SeekToEnd();
		USES_CONVERSION;
		if (bNeedWriteTitle)
		{
			tempWrite = _T("Time,") + fileTitle + _T("\n");
			//file.WriteString(tempWrite);
			char * ss = T2A(tempWrite);
			file.Write(ss,strlen(ss));
		} 
		tempWrite = strLogTime + _T(",") + fileContent + _T("\n");
		//file.WriteString(tempWrite);
		char * ss = T2A(tempWrite);
		file.Write(ss,strlen(ss));
		file.Close(); 
	}
	catch (...)
	{
		temp.Replace(_T(".csv"),_T(".txt"));
		::WritePrivateProfileString(_T("Error"),strLogTime,fileContent,temp);
		return 1;
	}
	return 0;
}

GotoDlgCtrl((CEdit*)GetDlgItem(IDC_EDIT_BGCODE)); //设置控件焦点

void ::OnSysCommand(UINT nID, LPARAM lParam) //重载OnSysCommand函数, 屏蔽关闭按钮
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nID!=61536)//关闭按钮
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void MoveFolderFile()//往不同分区,或者网络共享目录移动文件夹
{
	// TODO: 在此添加控件通知处理程序代码
	CString strorg=_T("D:\\123");
	CString strdes=_T("Z:\\456");
	CString filenamearr[]={_T("\\0.txt"),_T("\\1.txt"),_T("\\2.txt"),_T("\\3.txt"),_T("\\4.txt")};//文件名列表

	if (!PathFileExists(strdes))	//如果新目录不存在,则创建
	{
		CreateDirectory(strdes,NULL);//新建目标目录
	}
	int bret=-1;
	if (!PathFileExists(strorg+filenamearr[i])) //判断源文件是否存在
	{
		AfxMessageBox(_T("file not exist"));
	}
	for (int i=0;i<5;i++)
	{
		bret=MoveFileEx(strorg+filenamearr[i],strdes+filenamearr[i],MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);//移动文件
		if (bret!=0)
		{
			AfxMessageBox(_T("move file successed"));
		}
		else
		{
			AfxMessageBox(_T("move file fail"));
		}
	}
	if (PathFileExists(strorg))//删除源文件目录
	{
		RemoveDirectory(strorg);
	}
}

ShellExecute(NULL,_T("open"),_T("\\1.bat"), NULL, NULL, SW_SHOWNORMAL);
net time \\192.168.1.112 /set /y  //时间同步命令


//获取当前文件路径
void CxmltestDlg::GetAppPath(CString& AppPath)
{
	CString strt=_T("");
	TCHAR temp[1024];

	::GetModuleFileName(NULL,temp,1023);
	strt=(CString)temp;

	int n=strt.ReverseFind('\\');

	AppPath=strt.Left(n);
}
CString ::ReadSingleNodeXml(CString sec,CString key)
{
	CoInitialize(NULL); 
	BSTR strv=L"";
	CString strdir=_T("");
	CString selnodecstr=_T("");
	CComPtr<IXMLDOMDocument> spXmldoc;      
	HRESULT hr = spXmldoc.CoCreateInstance(L"MSXML2.DOMDocument.6.0");        
	if(SUCCEEDED(hr))      
	{          
		VARIANT_BOOL isSuccessFul;

		GetAppPath(strdir);
		strdir=strdir+_T("\\Program\\SaejongConfig.xml");
		CComVariant varXmlFile(strdir);  

		spXmldoc->put_async(VARIANT_FALSE);          
		HRESULT hr= spXmldoc->load(varXmlFile, &isSuccessFul);            
		if(isSuccessFul==VARIANT_TRUE)          
		{              
			CComBSTR bstrXml;              
			CComPtr<IXMLDOMElement> spRoot=NULL;                                                       
			hr = spXmldoc->get_documentElement(&spRoot);              
			spRoot->get_xml(&bstrXml);                


			CComPtr<IXMLDOMNode> spTheNode=NULL;   
			selnodecstr=_T("/SaejongConfig/")+sec+_T("/")+key;

			spRoot->selectSingleNode(::SysAllocString(selnodecstr), &spTheNode); 
			if (spTheNode!=NULL)//节点未找到
			{
				spTheNode->get_text(&strv);
			}
			spRoot.Release();              
			bstrXml.Empty(); 
		} 
		varXmlFile.ClearToZero();      
	}        
	spXmldoc.Release();        
	CoUninitialize();  
	return (CString)strv;
}
int ::WriteSingleNodeXml(CString sec,CString key,CString val)
{
	CoInitialize(NULL); 
	int result=1;
	CString strdir=_T("");
	CString selnodecstr=_T("");
	CComPtr<IXMLDOMDocument> spXmldoc;      
	HRESULT hr = spXmldoc.CoCreateInstance(L"MSXML2.DOMDocument.6.0");        
	if(SUCCEEDED(hr))      
	{          
		VARIANT_BOOL isSuccessFul;  

		GetAppPath(strdir);
		strdir=strdir+_T("\\Program\\SaejongConfig.xml");
		CComVariant varXmlFile(strdir); 

		spXmldoc->put_async(VARIANT_FALSE);          
		HRESULT hr= spXmldoc->load(varXmlFile, &isSuccessFul);            
		if(isSuccessFul==VARIANT_TRUE)          
		{              
			CComBSTR bstrXml;              
			CComPtr<IXMLDOMElement> spRoot=NULL;                            
			CComPtr<IXMLDOMElement> spTheElem=NULL;              
			CComPtr<IXMLDOMNode> spNewNode=NULL;  
			CComPtr<IXMLDOMNode> spTheNode=NULL; 
			hr = spXmldoc->get_documentElement(&spRoot);              
			spRoot->get_xml(&bstrXml);                


			selnodecstr=_T("/SaejongConfig/")+sec+_T("/")+key;

			spRoot->selectSingleNode(::SysAllocString(selnodecstr), &spTheNode); 
			if (spTheNode!=NULL)//节点未找到
			{
				spTheNode->put_text(::SysAllocString(val));
				spXmldoc->save(varXmlFile); //保存xml。
				result=0;
			}
			else
			{
				spXmldoc->createElement(::SysAllocString(key),&spTheElem);
				spTheElem->put_text(::SysAllocString(val));

				spRoot->selectSingleNode(::SysAllocString(_T("/SaejongConfig/")+sec),&spTheNode);
				spTheNode->appendChild(spTheElem,&spNewNode);

				spXmldoc->save(varXmlFile); //保存xml。
				result=0;
			}

			spRoot.Release();              
			bstrXml.Empty(); 
		}  
		varXmlFile.ClearToZero(); 
	}       
	spXmldoc.Release();        
	CoUninitialize(); 

	return result;
}

int ::ReadAllNodeXml(CString sec,const CString titlearr[],CString configarr[],int arrsize)
{
	CoInitialize(NULL); 
	BSTR strv=L"";
	CString strdir=_T("");
	CString selnodecstr=_T("");
	CComPtr<IXMLDOMDocument> spXmldoc;      
	HRESULT hr = spXmldoc.CoCreateInstance(L"MSXML2.DOMDocument.6.0");        
	if(SUCCEEDED(hr))      
	{          
		VARIANT_BOOL isSuccessFul;

		GetAppPath(strdir);
		strdir=strdir+_T("\\Program\\SaejongConfig.xml");//此处修改配置档文件名
		CComVariant varXmlFile(strdir);  

		spXmldoc->put_async(VARIANT_FALSE);          
		HRESULT hr= spXmldoc->load(varXmlFile, &isSuccessFul);            
		if(isSuccessFul==VARIANT_TRUE)          
		{              
			CComBSTR bstrXml;              
			CComPtr<IXMLDOMElement> spRoot=NULL;                            
			hr = spXmldoc->get_documentElement(&spRoot);              
			spRoot->get_xml(&bstrXml);                

			CComPtr<IXMLDOMNode> spTheNode=NULL; 

			
			for (int i=0;i<arrsize;i++)
			{
				spTheNode=NULL;
				selnodecstr=_T("/SaejongConfig/")+sec+_T("/")+titlearr[i];
			
				spRoot->selectSingleNode(::SysAllocString(selnodecstr), &spTheNode); 
				if (spTheNode!=NULL)//节点未找到
				{
					spTheNode->get_text(&strv);
					configarr[i]=(CString)strv;
				}	
				else
				{
					configarr[i]=_T("");
				}
			}
			  

			spRoot.Release();              
			bstrXml.Empty(); 
		} 
		varXmlFile.ClearToZero();      
	}        
	spXmldoc.Release();        
	CoUninitialize();

	for (int i=0;i<arrsize;i++)
	{
		if (configarr[i].IsEmpty())
		{
			return 1;
		}
	}
	return 0;
}

CString ConvertRelAbsPath(CString inpath,int mode)//mode 0:绝对路径转相对路径,1:相对路径转绝对路径
{
	CString exepath=_T(""),strexeArr[50],strinArr[50],newpath=_T("");
	int nexecnt=0,nincnt=0,nmincnt=0,nsamecnt=0;
	GetAppPath(exepath);

	nexecnt=SplitString(exepath,_T("\\"),strexeArr,50);
	nincnt=SplitString(inpath,_T("\\"),strinArr,50);
	nmincnt=(nexecnt>nincnt)?nincnt:nexecnt;

	if (mode==0)//0:绝对路径转相对路径
	{
		for (int i=0;i<nmincnt;i++)
		{
			if (strexeArr[i]==strinArr[i])
			{
				nsamecnt++;
			}
			else
			{
				break;
			}
		}

		newpath=_T(".");
		for (int i=0;i<(nexecnt-nsamecnt);i++)
		{
			newpath+=_T(".");
		}

		for (int i=nsamecnt;i<nincnt;i++)
		{
			newpath+=_T("\\")+strinArr[i];
		}

		return newpath;

	}
	else if (mode==1)//1:相对路径转绝对路径
	{
		int deldircnt=0;
		deldircnt=strinArr[0].GetLength()-1;

		if (deldircnt>nexecnt)
		{
			return _T("");
		}

		newpath=strexeArr[0];
		for (int i=1;i<(nexecnt-deldircnt);i++)
		{
			newpath+=_T("\\")+strexeArr[i];
		}

		for (int i=1;i<nincnt;i++)
		{
			newpath+=_T("\\")+strinArr[i];
		}
		return newpath;
	}

	return _T("");
}
int CbgTraceTestDlg::DBInsertBgGlueInfo(CString bgsn,CString headid,CString starttime,CString stoptime)				//BG点胶机插入数据
{
	CString strcmd=_T("");


	HRESULT hr;
	_ConnectionPtr m_pConnectiona=NULL;
	_RecordsetPtr m_pRecordSeta=NULL;
	_CommandPtr m_pCommanda;
	_bstr_t constr;
	_variant_t RecordsAffected; 
	constr = "Dsn=bgremote;UID=root;PWD=8107@saejong;db=db_bg_assembly;";
	try
	{
		CoInitialize(NULL);
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10;   
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);
			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			strcmd.Format(_T("delete from tb_trace_data where bg_sn='%s'"),bgsn);
			m_pConnectiona->Execute(_bstr_t(strcmd),&RecordsAffected,adCmdText);

			strcmd.Format(_T("insert into tb_bg_glue_info (bg_sn,glue_start_time,glue_stop_time,head_id) values('%s','%s','%s','%s');"),bgsn,headid,starttime,stoptime);
			m_pConnectiona->Execute(_bstr_t(strcmd),&RecordsAffected,adCmdText);	
			m_pConnectiona->Close();

			::CoUninitialize();
			return 0;
		}
		else
		{
			AfxMessageBox(_T("Create ADODB Instance failed"));///////////////////////////////////////////
			return 1;
		}

	}
	catch(_com_error e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("执行数据库插入失败!错误信息: %s"),e.ErrorMessage());
		AfxMessageBox(errormessage);///////////////////////////////////////////
		::CoUninitialize();
		return 1;
	}
}
int CbgTraceTestDlg::DBQueryBgGlueInfo(CString bgsn,CString& headid,CString& starttime,CString& stoptime)			//贴合机根据BG码查询点胶机信息
{
	CString strcmd=_T("");
	HRESULT hr;
	_ConnectionPtr m_pConnectiona=NULL;
	_RecordsetPtr m_pRecordSeta=NULL;
	_bstr_t constr;
	_variant_t RecordsAffected;
	constr = "Dsn=bgremote;UID=root;PWD=8107@saejong;db=db_bg_assembly;";
	try
	{
		::CoInitialize(NULL);
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10; 
			m_pConnectiona->CommandTimeout = 5;  
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);

			strcmd.Format(_T("select * from tb_bg_glue_info where bg_sn='%s';"),bgsn);
			_bstr_t x = _bstr_t(strcmd);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (!m_pRecordSeta->adoEOF && m_pRecordSeta != NULL)
			{
				m_pRecordSeta->MoveFirst();
				headid=(CString)m_pRecordSeta->GetCollect("head_id");
				starttime=(CString)m_pRecordSeta->GetCollect("glue_start_time");
				stoptime=(CString)m_pRecordSeta->GetCollect("glue_stop_time");
			}
			else
			{
				headid=_T("");
				starttime=_T("");
				stoptime=_T("");
			}


			m_pConnectiona->Close();
			::CoUninitialize();
			return 0;
		}
		else
		{
			AfxMessageBox(_T("Create ADodb Instance failed"));
			return 1;
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取数据库失败!错误信息 :%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		::CoUninitialize();
	}
}
int CbgTraceTestDlg::DBFindFixtureCycle(CString fixtureid,CString& fixturecycle)										//查找并刷新FixtureCycle表格
{
	CString strcmd=_T("");
	HRESULT hr;
	_ConnectionPtr m_pConnectiona=NULL;
	_RecordsetPtr m_pRecordSeta=NULL;
	_bstr_t constr;
	_variant_t RecordsAffected;
	constr = "Dsn=bgremote;UID=root;PWD=8107@saejong;db=db_bg_assembly;";
	try
	{
		::CoInitialize(NULL);
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10; 
			m_pConnectiona->CommandTimeout = 5;  
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);

			strcmd.Format(_T("select * from tb_fixture_cycle where fixture_id='%s';"),fixtureid);
			_bstr_t x = _bstr_t(strcmd);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (!m_pRecordSeta->adoEOF && m_pRecordSeta != NULL)
			{
				m_pRecordSeta->MoveFirst();
				fixturecycle=(CString)m_pRecordSeta->GetCollect("cycle_count");
				int n=_wtoi(fixturecycle);
				n=n+1;

				if (n>100)
				{
					n=1;
				}
				fixturecycle.Format(_T("%d"),n);
				strcmd.Format(_T("update tb_fixture_cycle set cycle_count='%s' where fixture_id='%s'"),fixturecycle,fixtureid);
			}
			else
			{
				fixturecycle=_T("1");
				strcmd.Format(_T("insert into tb_fixture_cycle (fixture_id,cycle_count) values('%s','%s');"),fixtureid,fixturecycle);
			}


			m_pConnectiona->Execute(_bstr_t(strcmd),&RecordsAffected,adCmdText);	

			m_pConnectiona->Close();
			::CoUninitialize();
			return 0;
		}
		else
		{
			AfxMessageBox(_T("Create ADodb Instance failed"));
			return 1;
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取数据库失败!错误信息 :%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		::CoUninitialize();
	}
}
int CbgTraceTestDlg::DBInsertFullTraceData(TRACE_DATA t)															//贴合机插入完整数据
{
	CString strInsert=_T("insert into db_bg_assembly.tb_trace_data (line_id,station_id,software_name,software_version,band_glue_software_version,bg_glue_software_version,");
	strInsert+=_T("unit_sn,test_result,uut_start,uut_stop,fixture_id,head_id,bg_sn,band_sn,");
	strInsert+=_T("band_glue_station_id,band_glue_fixture_id,band_glue_head_id,band_glue_start_time,band_glue_stop_time,");
	strInsert+=_T("bg_glue_station_id,bg_glue_fixture_id,bg_glue_head_id,bg_glue_start_time,bg_glue_stop_time,");
	strInsert+=_T("bg_glue_open_time,band_glue_open_time,fixture_cycle,assy_start_time,assy_stop_time,assy_bond_time,assy_bond_end_time,upload_status) ");
	strInsert+=_T("values('LINEID','STATIONID','SOFTWARENAME','SOFTWAREVERSION','BANDGLUESOFTVERSION','BGGLUESOFTVERSION',");
	strInsert+=_T("'UNITSN','TESTRESULT','UUTSTART','UUTSTOP','FIXTUREID','HEADID','BGSN','BANDSN',");
	strInsert+=_T("'BANDSTATION','BANDFIXTURE','BANDHEAD','BANDSTART','BANDSTOP',");
	strInsert+=_T("'BGSTATION','BGFIXTURE','BGHEAD','BGSTART','BGSTOP',");
	strInsert+=_T("'BGOPENTIME','BANDOPENTIME','FIXTURECYCLE','ASSYSTART','ASSYSTOP','ASSYBONDTIME','ASSYBONDENDTIME','UPLOADSTATUS');");

	strInsert.Replace(_T("LINEID"),t.strLineId);
	strInsert.Replace(_T("STATIONID"),t.strStationId);
	strInsert.Replace(_T("SOFTWARENAME"),t.strSoftwareName);
	strInsert.Replace(_T("SOFTWAREVERSION"),t.strSoftwareVersion);
	strInsert.Replace(_T("BANDGLUESOFTVERSION"),t.strBandGlueSoftwareVersion);
	strInsert.Replace(_T("BGGLUESOFTVERSION"),t.strBgGlueSoftwareVersion);

	strInsert.Replace(_T("UNITSN"),t.strUnitSn);
	strInsert.Replace(_T("TESTRESULT"),t.strTestResult);
	strInsert.Replace(_T("UUTSTART"),t.strUutStart);
	strInsert.Replace(_T("UUTSTOP"),t.strUutStop);
	strInsert.Replace(_T("FIXTUREID"),t.strFixtureId);
	strInsert.Replace(_T("HEADID"),t.strHeadId);
	strInsert.Replace(_T("BGSN"),t.strBgSn);
	strInsert.Replace(_T("BANDSN"),t.strBandSn);

	strInsert.Replace(_T("BANDSTATION"),t.strBandGlueStationId);
	strInsert.Replace(_T("BANDFIXTURE"),t.strBandGlueFixtureId);
	strInsert.Replace(_T("BANDHEAD"),t.strBandGlueHeadId);
	strInsert.Replace(_T("BANDSTART"),t.strBandGlueStartTime);
	strInsert.Replace(_T("BANDSTOP"),t.strBandGlueStopTime);

	strInsert.Replace(_T("BGSTATION"),t.strBgGlueStationId);
	strInsert.Replace(_T("BGFIXTURE"),t.strBgGlueFixtureId);
	strInsert.Replace(_T("BGHEAD"),t.strBgGlueHeadId);
	strInsert.Replace(_T("BGSTART"),t.strBgGlueStartTime);
	strInsert.Replace(_T("BGSTOP"),t.strBgGlueStopTime);

	strInsert.Replace(_T("BGOPENTIME"),t.strBgGlueOpenTime);
	strInsert.Replace(_T("BANDOPENTIME"),t.strBandGlueOpenTime);
	strInsert.Replace(_T("FIXTURECYCLE"),t.strFixtureCycle);
	strInsert.Replace(_T("ASSYSTART"),t.strAssyStartTime);
	strInsert.Replace(_T("ASSYSTOP"),t.strAssyStopTime);
	strInsert.Replace(_T("ASSYBONDTIME"),t.strAssyBondTime);
	strInsert.Replace(_T("ASSYBONDENDTIME"),t.strAssyBondEndTime);
	strInsert.Replace(_T("UPLOADSTATUS"),t.strUploadStatus);

	CString strcmd=_T("");

	HRESULT hr;
	_ConnectionPtr m_pConnectiona=NULL;
	_RecordsetPtr m_pRecordSeta=NULL;
	_CommandPtr m_pCommanda;
	_bstr_t constr;
	_variant_t RecordsAffected; 
	constr = "Dsn=bgremote;UID=root;PWD=8107@saejong;db=db_bg_assembly;";
	try
	{
		CoInitialize(NULL);
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10;   
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);
			m_pCommanda.CreateInstance(__uuidof(Command));
			m_pCommanda->CommandTimeout = 5;
			m_pCommanda->ActiveConnection = m_pConnectiona;

			strcmd.Format(_T("delete from tb_trace_data where band_sn='%s'"),t.strBandSn);
			m_pConnectiona->Execute(_bstr_t(strcmd),&RecordsAffected,adCmdText);

			m_pConnectiona->Execute(_bstr_t(strInsert),&RecordsAffected,adCmdText);	
			m_pConnectiona->Close();

			::CoUninitialize();
			return 0;
		}
		else
		{
			AfxMessageBox(_T("Create ADODB Instance failed"));///////////////////////////////////////////
			return 1;
		}

	}
	catch(_com_error e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("执行数据库插入失败!错误信息: %s"),e.ErrorMessage());
		AfxMessageBox(errormessage);///////////////////////////////////////////
		::CoUninitialize();
		return 1;
	}
}
int CbgTraceTestDlg::DBReadWaitUploadInfo(CString uploadstatus,CString& bgsn,CString& bandsn,CString& fixtureid)	//从数据库查询需要进行上传的信息,比如Autolink或者MDFT
{
	CString strcmd=_T("");
	HRESULT hr;
	_ConnectionPtr m_pConnectiona=NULL;
	_RecordsetPtr m_pRecordSeta=NULL;
	_bstr_t constr;
	_variant_t RecordsAffected;
	constr = "Dsn=bgremote;UID=root;PWD=8107@saejong;db=db_bg_assembly;";
	try
	{
		::CoInitialize(NULL);
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10; 
			m_pConnectiona->CommandTimeout = 5;  
			hr = m_pConnectiona->Open(constr,"","", adModeUnknown);

			strcmd.Format(_T("select * from tb_trace_data where upload_status='%s' order by uut_start desc limit 1;"),uploadstatus);
			_bstr_t x = _bstr_t(strcmd);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(x,m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (!m_pRecordSeta->adoEOF && m_pRecordSeta != NULL)
			{
				m_pRecordSeta->MoveFirst();
				bgsn=(CString)m_pRecordSeta->GetCollect("bg_sn");
				bandsn=(CString)m_pRecordSeta->GetCollect("band_sn");
				fixtureid=(CString)m_pRecordSeta->GetCollect("fixture_id");
			}
			else
			{
				bgsn=_T("");
				bandsn=_T("");
				fixtureid=_T("");
			}


			m_pConnectiona->Close();
			::CoUninitialize();
			return 0;
		}
		else
		{
			AfxMessageBox(_T("Create ADodb Instance failed"));
			return 1;
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取数据库失败!错误信息 :%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		::CoUninitialize();
	}
}

//更新BG点胶部分信息
int BgTraceData::DBUpdateBgGlueInfo(CString strbg)				
{
	CString strcmd=_T("");
	HRESULT hr;
	_ConnectionPtr m_pConnectiona=NULL;
	_RecordsetPtr m_pRecordSeta=NULL;
	_variant_t RecordsAffected;
	CString strconn=_T("");
	strconn.Format(_T("Dsn=%s;UID=%s;PWD=%s;db=%s;"),DSN_NAME,DB_USER,DB_PWD,DB_NAME);
	try
	{
		::CoInitialize(NULL);
		hr = m_pConnectiona.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{   
			m_pConnectiona->ConnectionTimeout = 10; 
			m_pConnectiona->CommandTimeout = 5;  
			hr = m_pConnectiona->Open(_bstr_t(strconn),"","", adModeUnknown);

			strcmd.Format(_T("select * from tb_bg_glue_info where bg_sn='%s';"),strBgSn);

			m_pRecordSeta.CreateInstance(__uuidof(Recordset));
			m_pRecordSeta->Open(_bstr_t(strcmd),m_pConnectiona.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			if (!m_pRecordSeta->adoEOF && m_pRecordSeta != NULL)
			{
				m_pRecordSeta->MoveFirst();
				strBgGlueHeadId=(CString)m_pRecordSeta->GetCollect("head_id");
				strBgGlueStartTime=(CString)m_pRecordSeta->GetCollect("glue_start_time");
				strBgGlueStopTime=(CString)m_pRecordSeta->GetCollect("glue_stop_time");
			}
			else
			{
				strBgGlueHeadId=_T("-1");
				strBgGlueStartTime=_T("-1");
				strBgGlueStopTime=_T("-1");
				m_pConnectiona->Close();
				::CoUninitialize();
				return 1;
			}


			m_pConnectiona->Close();
			::CoUninitialize();
			return 0;
		}
		else
		{
			AfxMessageBox(_T("Create ADodb Instance failed"));
			return 1;
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString   errormessage;
		errormessage.Format(_T("读取数据库失败!错误信息 :%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		::CoUninitialize();
		return 1;
	}
}

int CHomePageDlg::SaveCsvLog(CString fileTitle,CString fileContent,CString fileName)
{
	CString fileFolderName=fileName;
	CStdioFile file;
	BOOL bNeedWriteTitle = FALSE,strResult = FALSE;
	CString strFileName,strLogTime,strFloderYear,strFloderMonth,temp,tempWrite,path;
	SYSTEMTIME time;
	GetLocalTime(&time);
	if (fileName.Find(_T(".csv")) == -1 && fileName.Find(_T(".CSV")) == -1)
	{
		temp.Format(_T("-%d-%02d-%02d.csv"),time.wYear,time.wMonth,time.wDay);
		fileName += temp;
	}
	strFileName = fileName;

	strLogTime.Format(_T("[%02d:%02d:%02d.%03d]"),time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	strFloderYear.Format(_T("%d年"),time.wYear);//
	strFloderMonth.Format(_T("%02d月"),time.wMonth);//
	GetAppPath(path);
	if (path.Find(_T(".exe")) != -1)
	{
		path = path.Left(path.ReverseFind('\\'));
	}

	temp.Format(_T("%s\\Data"),path);
	if (PathIsDirectory(temp)==FALSE)	 //判断路径是否存在，不存在则创建
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\%s"),path,fileFolderName);
	if (PathIsDirectory(temp)==FALSE)	 //判断路径是否存在，不存在则创建
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\%s\\%s"),path,fileFolderName,strFloderYear);
	if (PathIsDirectory(temp)==FALSE)	 //判断路径是否存在，不存在则创建
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\%s\\%s\\%s"),path,fileFolderName,strFloderYear,strFloderMonth);
	if (PathIsDirectory(temp)==FALSE)	//判断路径是否存在，不存在则创建	 
	{
		CreateDirectory(temp, NULL);
	}

	temp.Format(_T("%s\\Data\\%s\\%s\\%s\\%s"),path,fileFolderName,strFloderYear,strFloderMonth,strFileName);
	if (PathFileExists(temp) == FALSE)
	{
		bNeedWriteTitle = TRUE;
	}

	try
	{
		strResult = file.Open(temp,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText);//打开文件
		if (!strResult)
		{
			//SendMotionInfo(_T("Log文件保存失败."));
			temp.Replace(_T(".csv"),_T(".txt"));
			::WritePrivateProfileString(_T("Error"),strLogTime,fileContent,temp);
			return 1;
		}
		file.SeekToEnd();
		USES_CONVERSION;
		if (bNeedWriteTitle)
		{
			tempWrite = _T("Time,") + fileTitle + _T("\n");
			//file.WriteString(tempWrite);
			char * ss = T2A(tempWrite);
			file.Write(ss,strlen(ss));
		} 
		tempWrite = strLogTime + _T(",") + fileContent + _T("\n");
		//file.WriteString(tempWrite);
		char * ss = T2A(tempWrite);
		file.Write(ss,strlen(ss));
		file.Close(); 
	}
	catch (...)
	{
		temp.Replace(_T(".csv"),_T(".txt"));
		::WritePrivateProfileString(_T("Error"),strLogTime,fileContent,temp);
		return 1;
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int CParamDlg::WriteLog(CString strmsg,CString filetype,CString foldername,bool bneedtime,CString strtitle)
{
	CStdioFile file;
	CString strFileName,strFloderYear,strFloderMonth,fpath,tempWrite,strTime=_T("");
	SYSTEMTIME t;
	GetLocalTime(&t);
	bool createfileflag=FALSE;

	strFileName.Format(_T("%s%d-%02d-%02d.txt"),filetype,t.wYear,t.wMonth,t.wDay);

	strFloderYear.Format(_T("%d年"),t.wYear);//
	strFloderMonth.Format(_T("%02d月"),t.wMonth);//

	fpath=_T("D:\\SaejongLog");
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建

	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth+_T("\\")+strFileName;

	if (!PathFileExists(fpath))
	{
		createfileflag=TRUE;
	}

	if (file.Open(fpath,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText))	 //打开文件
	{
		USES_CONVERSION;

		if (createfileflag && !(strtitle.IsEmpty()))
		{
			tempWrite=strtitle+_T("\n");
			char * ss = T2A(tempWrite);
			file.Write(ss,strlen(ss));
		}

		file.SeekToEnd();

		if (bneedtime)
		{
			strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d,"),t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);
		}
		tempWrite=strTime+strmsg+_T("\n");
		char * ss = T2A(tempWrite);
		file.Write(ss,strlen(ss));
		file.Close(); 
		return 0;
	}
	else
	{
		return 1;
	}
}

int CMainUIDlg::WriteLog(CString strmsg,CString filetype,CString foldername,bool bneedtime,CString strtitle)
{
	CStdioFile file;
	CString strFileName,strFloderYear,strFloderMonth,fpath,tempWrite,strTime=_T("");
	SYSTEMTIME t;
	GetLocalTime(&t);
	bool createfileflag=FALSE;

	strFileName.Format(_T("%s%d-%02d-%02d.txt"),filetype,t.wYear,t.wMonth,t.wDay);

	strFloderYear.Format(_T("%d年"),t.wYear);//
	strFloderMonth.Format(_T("%02d月"),t.wMonth);//

	fpath=_T("D:\\SaejongLog");
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建

	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth+_T("\\")+strFileName;

	if (!PathFileExists(fpath))
	{
		createfileflag=TRUE;
	}

	int retryTimes = 0;
retryWrite:
	if (file.Open(fpath,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText))	 //打开文件
	{
		USES_CONVERSION;

		if (createfileflag && !(strtitle.IsEmpty()))
		{
			tempWrite=strtitle+_T("\n");
			char * ss = T2A(tempWrite);
			file.Write(ss,strlen(ss));
		}

		file.SeekToEnd();

		if (bneedtime)
		{
			strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d,"),t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);
		}
		tempWrite=strTime+strmsg+_T("\n");
		char * ss = T2A(tempWrite);
		file.Write(ss,strlen(ss));
		file.Close(); 
		return 0;
	}
	else
	{
		Delay(10);
		retryTimes ++;
		if (retryTimes>10000)
		{
			AfxMessageBox(_T("RunRecord记录写入失败"));
			return 1;
		}
		goto retryWrite;
	}
}
void COeeUploadDlg::OnBnClickedBtnExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPath=_T(""),strit=_T(""),strTitle=_T("");
	CString strdefaultname=_T("");
	CTime t=CTime::GetCurrentTime();
	strdefaultname.Format(_T("OeeRecord-%d-%d-%d-%d-%d-%d"),t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	CFileDialog fdlg(FALSE,_T("csv"),strdefaultname,OFN_OVERWRITEPROMPT,_T("Csv Files(*.csv)|*.csv|Txt Files(*.txt)|*.txt|All Files(*.*)|*.*||;"));
	fdlg.m_ofn.lpstrTitle=_T("请选择文件:");
	if (fdlg.DoModal()==IDOK)
	{
		strPath=fdlg.GetPathName();
		if (strPath.IsEmpty())
		{
			return;
		}

		if (PathFileExists(strPath))
		{
			DeleteFile(strPath);
		}
		CStdioFile file;
		file.Open(strPath,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText);//打开文件
		strTitle=_T("序号,开始时间,结束时间,异常代码,异常持续时间,异常信息\n");
		file.SeekToEnd();
		USES_CONVERSION;

		char * ss = T2A(strTitle);
		file.Write(ss,strlen(ss));

		for (unsigned int i=0;i<m_listDowntimeRecord.GetItemCount();i++)
		{
			strit.Format(_T("%s,%s,%s,%s,%s,%s\n"),m_listDowntimeRecord.GetItemText(i,0),m_listDowntimeRecord.GetItemText(i,1),m_listDowntimeRecord.GetItemText(i,2),
				m_listDowntimeRecord.GetItemText(i,3),m_listDowntimeRecord.GetItemText(i,4),m_listDowntimeRecord.GetItemText(i,5));
			ss=T2A(strit);
			file.Write(ss,strlen(ss));
		}
		file.Close();
	}
	else
	{
		return;
	}
}
int PartMonitorDlg::WriteLog2(CString sn,CString strCaption,CString strmsg,CString filetype,CString foldername,bool bneedtime,CString strtitle)
{
	CStdioFile file;
	CString strFileName,strFloderYear,strFloderMonth,strFloderDay,fpath,tempWrite,strTime=_T("");
	SYSTEMTIME t;
	GetLocalTime(&t);
	bool createfileflag=FALSE;

	strFileName.Format(_T("%s.txt"),filetype);
	//strFileName.Format(_T("%s%d-%02d-%02d.txt"),filetype,t.wYear,t.wMonth,t.wDay);

	strFloderYear.Format(_T("%d年"),t.wYear);//
	strFloderMonth.Format(_T("%02d月"),t.wMonth);//
	strFloderDay.Format(_T("%02d日"),t.wDay);//

	fpath=_T("D:\\SaejongLog");
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth+_T("\\")+strFloderDay;
	if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	if(!sn.IsEmpty())
	{
		fpath=_T("D:\\SaejongLog\\")+foldername+_T("\\")+strFloderYear+_T("\\")+strFloderMonth+_T("\\")+strFloderDay+_T("\\")+sn;
		if (PathIsDirectory(fpath)==FALSE)	 CreateDirectory(fpath, NULL);//判断路径是否存在，不存在则创建
	}

	fpath=fpath+_T("\\")+strFileName;

	if (!PathFileExists(fpath))
	{
		createfileflag=TRUE;
	}

	int retryTimes = 0;
retryWrite:
	if (file.Open(fpath,CStdioFile::modeNoTruncate|CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeText))	 //打开文件
	{
		USES_CONVERSION;

		if (createfileflag && !(strtitle.IsEmpty()))
		{
			tempWrite=strtitle+_T("\n");
			char * ss = T2A(tempWrite);
			file.Write(ss,strlen(ss));
		}

		file.SeekToEnd();

		if (bneedtime)
		{
			strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d,"),t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);
		}
		tempWrite=strTime+strmsg+_T("\n");
		char * ss = T2A(tempWrite);
		file.Write(ss,strlen(ss));
		file.Close(); 
		return 0;
	}
	else
	{
		Delay(10);
		retryTimes ++;
		if (retryTimes>10000)
		{
			//AfxMessageBox(_T("记录写入失败"));
			return 1;
		}
		goto retryWrite;
	}
}