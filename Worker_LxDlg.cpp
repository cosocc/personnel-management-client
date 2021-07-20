
// Worker_LxDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Worker_Lx.h"
#include "Worker_LxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWorkerDlg 对话框



CWorkerDlg::CWorkerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORKER_LX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWorkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWorkerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWorkerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWorkerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ADD, &CWorkerDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CWorkerDlg::OnClickedDelete)
	ON_BN_CLICKED(IDC_MODIFY, &CWorkerDlg::OnClickedModify)
	ON_BN_CLICKED(IDC_SAVE, &CWorkerDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CWorkerDlg 消息处理程序

BOOL CWorkerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	pList->InsertColumn(0, _T("工号"), 0, 100);//内部结构：请问是CArray和CList
	pList->InsertColumn(1, _T("姓名"), 0, 140);
	pList->InsertColumn(2, _T("工资"), 0, 120);
	pList->InsertColumn(3, _T("日志日期"), 0, 200);
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWorkerDlg::OnPaint()
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
HCURSOR CWorkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWorkerDlg::OnBnClickedOk()
{
//CDialogEx::OnOK();
}


void CWorkerDlg::OnBnClickedCancel()
{
	
	CDialogEx::OnCancel();
}


void CWorkerDlg::OnBnClickedAdd()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int nCount = pList->GetItemCount();
	CString str;
	GetDlgItemText(IDC_NUMB, str);
	pList->InsertItem(nCount,str);
	GetDlgItemText(IDC_NAME, str);
	pList->SetItemText(nCount, 1, str);
	GetDlgItemText(IDC_SALARY, str);
	pList->SetItemText(nCount, 2, str);
	GetDlgItemText(IDC_DATE, str);
	pList->SetItemText(nCount, 3, str);


}


void CWorkerDlg::OnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CWorkerDlg::OnClickedModify()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CWorkerDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
}
