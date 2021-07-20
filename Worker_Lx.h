
// Worker_Lx.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CApp:
// 有关此类的实现，请参阅 Worker_Lx.cpp
//

class CApp : public CWinApp
{
	BOOL ConnectServer();
	CString m_sName, m_sPass;
	int m_nPrior = 1;
public:
	CSocket m_sock;
	inline void SetUserInfo(const CString& sName, const CString& sPass, int nPrior)
	{
		m_sName = sName;
		m_sPass = sPass;
		m_nPrior = nPrior;
	}
	inline void CorrectDate(CString& sDate)
	{
		sDate.Replace(_T('年'), _T('/'));
		sDate.Replace(_T('月'), _T('/'));
		sDate.Replace(_T('日'), _T('\0'));
	}
	inline CString GetUserName() const
	{
		return m_sName;
	}
	inline int GetPrior() const
	{
		return m_nPrior;
	}
	inline CString GetPText() const
	{
		return m_nPrior ? _T("普通") : _T("高级");
	}
	CApp();
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CApp theApp;
