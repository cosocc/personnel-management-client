
// Worker_Lx.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "Worker_Lx.h"
#include "MainDlg.h"
#include "CLoginDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApp

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CApp 构造

CApp::CApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CApp 对象

CApp theApp;


// CApp 初始化

BOOL CApp::ConnectServer()
{
	CWnd w;
	if (!m_sock.Create())
	{
		w.MessageBox(_T("创建套接字失败！"));
		return FALSE;
	}

	if (m_sock.Connect(_T("192.168.1.168"), SERVER_PORT))
		return TRUE;
	if (m_sock.Connect(_T("192.168.1.102"), SERVER_PORT))
		return TRUE;
	w.MessageBox(_T("连接服务器失败！"));
	return FALSE;
}
#include "CWorkerDlg.h"
BOOL CApp::InitInstance()
{
	AfxSocketInit();//WSAStartup(0x0202,..)
	if (!ConnectServer())
		return FALSE;
	//CWorkerDlg dlg;
	//dlg.DoModal();
	CLoginDlg logDlg;
	if (logDlg.DoModal() == IDCANCEL)
		return FALSE;

	CMainDlg dlg;
	dlg.DoModal();

	return FALSE;
}

