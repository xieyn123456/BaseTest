//*********************************************
//             class CLDPCriticalSection      *
//             author  : Li dapeng            *
//             date    : 2014.12.16           *
//*********************************************

#ifndef __LDPCRITICALSECTION_H__
#define __LDPCRITICALSECTION_H__

#pragma once

class CLDPCriticalSection  
{
public:
	CLDPCriticalSection()
	{
		InitializeCriticalSection(&m_cs);
	}
	~CLDPCriticalSection()
	{
		DeleteCriticalSection(&m_cs);
	}

	void Init()
	{
		::EnterCriticalSection(&m_cs);
	}
	void Release()
	{
		::LeaveCriticalSection(&m_cs);
	}
private:
    CLDPCriticalSection(const CLDPCriticalSection& c);
    CLDPCriticalSection& operator= (const CLDPCriticalSection& c);
	CRITICAL_SECTION m_cs;
};


//类模板定义
template<class T>
class CLDPLock
{
public:
    CLDPLock(T& obj) 
        : m_objLock(obj)
    { 
        m_objLock.Init();
    }
	
    ~CLDPLock()
    {
        m_objLock.Release();
    }
	
private:
    T&  m_objLock;
};

typedef CLDPLock<CLDPCriticalSection> CLDPCriticalSectionLock;

#endif

