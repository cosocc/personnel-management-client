// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Worker_Lx.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
SAdmin a;

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)


CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DLG, pParent),m_sock(theApp.m_sock)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::CheckUser()
{
	//SAdmin a;
	
	GetDlgItemTextA(m_hWnd, IDC_NAME, a.sName, sizeof(a.sName));
	GetDlgItemTextA(m_hWnd, IDC_PASS, a.sPass, sizeof(a.sPass));
	a.nState = 1;
	_strlwr_s(a.sName, sizeof(a.sName));

	int nCmd = ADM_LOGIN;
	m_sock.Send(&nCmd, sizeof(nCmd));
	/*m_sock.Send(&a, sizeof(a)-sizeof(int));*/
	m_sock.Send(&a, sizeof(a));

	int nPrior = -1;//登录失败 -1 0高级 1普通
	if (m_sock.Receive(&nPrior, sizeof(nPrior)) < sizeof(nPrior))
	{
		MessageBox(_T("网络中断！"));
		return FALSE;
	}
	if (nPrior < 0)
		return FALSE;

	theApp.SetUserInfo(CString(a.sName), CString(a.sPass), nPrior);
	return TRUE;
}

void CLoginDlg::OnBnClickedOk()
{
	if (CheckUser())
	{
		EndDialog(IDOK);
		return;
	}


	MessageBox(_T("你输入的账号或密码错误！"));
	this->SetFocus();
}


void CLoginDlg::OnBnClickedCancel()
{
	EndDialog(IDCANCEL);
}
