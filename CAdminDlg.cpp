// CAdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "Worker_Lx.h"
#include "CAdminDlg.h"
#include "afxdialogex.h"
#include <string>


// CAdminDlg 对话框

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)


CAdminDlg::CAdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMIN_DLG, pParent),m_sock(theApp.m_sock)
{

}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CAdminDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CAdminDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_PRINT, &CAdminDlg::OnBnClickedPrint)
END_MESSAGE_MAP()


// CAdminDlg 消息处理程序


void CAdminDlg::Refresh()
{
	int nCmd = ADM_PRINT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	int nCount = 0;
	if (m_sock.Receive(&nCount, sizeof(nCount)) < sizeof(nCount))
	{
		MessageBox(_T("网络中断！"));
		return;
	}
	SAdmin a;
	int i = -1;
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	pList->DeleteAllItems();
	while (++i < nCount)
	{
		if (m_sock.Receive(&a, sizeof(a)) < sizeof(a))
			break;
		pList->InsertItem(i, _bstr_t(a.sName));
		pList->SetItemText(i, 1, _bstr_t(a.sPass));
		pList->SetItemText(i, 2, a.nPrior ? _T("普通") : _T("高级"));
		pList->SetItemText(i, 3, a.nState ? _T("离线") : _T("在线"));
	}
}
BOOL CAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//SetDlgItemText(IDC_PRIOR, _T("普通"));
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_PRIOR);
	pCombo->AddString(_T("高级"));
	pCombo->AddString(_T("普通"));
	pCombo->SetCurSel(1);
	pList->InsertColumn(0, _T("账号"), 0, 100);//内部结构：请问是CArray和CList
	pList->InsertColumn(1, _T("密码"), 0, 140);
	pList->InsertColumn(2, _T("权限"), 0, 120);
	pList->InsertColumn(3, _T("状态"), 0, 120);
	Refresh();
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAdminDlg::OnBnClickedAdd()
{
	CString str;
	GetDlgItemText(IDC_NAME, str);
	str.MakeLower();

	SAdmin a;
	strcpy_s(a.sName, sizeof(a.sName), _bstr_t(str));
	GetDlgItemText(IDC_PASS, str);
	strcpy_s(a.sPass, sizeof(a.sPass), _bstr_t(str));
	GetDlgItemText(IDC_PRIOR, str);
	a.nPrior = str == _T("普通");
	int nCmd = ADM_INSERT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&a,sizeof(a));
	int nRes = -1;
	if (m_sock.Receive(&nRes, sizeof(nRes)) < sizeof(nRes))
	{
		MessageBox(_T("网络中断！"));
		return;
	}
	if (!nRes)
	{
		Refresh();
		return;
	}
	if (nRes == 1062)
		MessageBox(_T("该账号已经存在，请重新输入！"));
	else
		MessageBox(_T("账号录入失败！"));

	SetFocus();
}


void CAdminDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int nItem = pList->GetNextItem(-1, LVNI_SELECTED);
	if (nItem < 0)
	{
		MessageBox(_T("请选中一行再删除！"));
		return;
	}
	CString sNumb = pList->GetItemText(nItem, 0);
	if (MessageBox(_T("确定要删除 ") + sNumb + _T(" 这条记录吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;
	char sName[32];
	strcpy_s(sName, sizeof(sName), _bstr_t(sNumb));

	int nCmd = ADM_DELETE;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&sName, sizeof(sName));

	int nRes = -1;
	if (m_sock.Receive(&nRes, sizeof(nRes)) < sizeof(nRes))
	{
		MessageBox(_T("网络中断！"));
		return;
	}
	if (!nRes)
	{
		return;
	}
	Refresh();
	SetFocus();
}


void CAdminDlg::OnBnClickedPrint()
{
	// TODO: 在此添加控件通知处理程序代码

	Refresh();
	SetFocus();

}
