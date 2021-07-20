
// MainDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Worker_Lx.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "CPassDlg.h"
#include "CAdminDlg.h"
#include "CWorkerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern SAdmin a;
// CMainDlg 对话框

//CMainDlg* g_pDlg;

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, &CMainDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_ADMIN, &CMainDlg::OnBnClickedAdmin)
	ON_BN_CLICKED(IDC_CHPASS, &CMainDlg::OnBnClickedChpass)
	ON_BN_CLICKED(IDC_WORKER, &CMainDlg::OnBnClickedWorker)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CMainDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

void CMainDlg::ShowInfo()
{
	CString str = _T("员工信息管理 - ");
	str += theApp.GetUserName();
	str += _T("【");
	str += theApp.GetPText();
	str += _T("】");
	//pAdmin->EnableWindow(!theApp.GetPrior());//ShowWindow
	SetWindowText(str);
	CTime t = CTime::GetCurrentTime();
	str += _T("      ") + t.Format(_T("%H:%M:%S"));
	SetWindowText(str);

}
BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowInfo();
	//::SetTimer(m_hWnd, 1, 1000, NULL);
	SetTimer(1, 1000, NULL);//KillTImer(1);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	auto pAdmin = GetDlgItem(IDC_ADMIN);
	pAdmin->ShowWindow(theApp.GetPrior() ? SW_HIDE : SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedLogin()
{
	CLoginDlg logDlg;
	if (logDlg.DoModal() == IDOK)//EndDialog
	{
		ShowInfo();
		auto pAdmin = GetDlgItem(IDC_ADMIN);
		pAdmin->ShowWindow(theApp.GetPrior() ? SW_HIDE : SW_SHOW);
	}


}


void CMainDlg::OnBnClickedAdmin()
{
	this->ShowWindow(SW_HIDE);

	CAdminDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);

}

#include "CPassDlg.h"
void CMainDlg::OnBnClickedChpass()
{
	CPassDlg dlg;
	if (dlg.DoModal() == IDOK)//EndDialog
		MessageBox(_T("密码修改成功！"));
}

void CMainDlg::OnBnClickedWorker()
{
	this->ShowWindow(SW_HIDE);
	CWorkerDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
	ShowInfo();

}


void CMainDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CDialogEx::OnCancel();
	
}
