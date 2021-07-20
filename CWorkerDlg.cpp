// CWorkerDlg.cpp: 实现文件
//

#include "pch.h"
#include "Worker_Lx.h"
#include "CWorkerDlg.h"
#include "afxdialogex.h"


// CWorkerDlg 对话框

IMPLEMENT_DYNAMIC(CWorkerDlg, CDialogEx)
BOOL CWorkerDlg::m_bDesc = FALSE;

CWorkerDlg::CWorkerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORKER_DLG, pParent),m_sock(theApp.m_sock)
{
	m_imgList.Create(16, 16, ILC_COLOR24 | ILC_MASK, 4, 8);
	int i = -1;
	while (++i < 4)
	{
		HICON hIcon = theApp.LoadIcon(IDI_ICON1 + i);
		m_imgList.Add(hIcon);
	}
	int n = m_imgList.GetImageCount();
}

CWorkerDlg::~CWorkerDlg()
{
}

void CWorkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWorkerDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CWorkerDlg::OnColumnclickList)
	ON_BN_CLICKED(IDC_DELETE, &CWorkerDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_MODIFY, &CWorkerDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_ADD, &CWorkerDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CWorkerDlg 消息处理程序


void CWorkerDlg::Refresh(int nOrder )
{
	int nCmd = WK_PRINT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&nOrder, sizeof(nOrder));

	int nCount = 0;
	if (m_sock.Receive(&nCount, sizeof(nCount)) < sizeof(nCount))
	{
		MessageBox(_T("网络中断！"));
		return;
	}
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int i = -1;
	SInfo d;
	CString str;
	pList->SetRedraw(FALSE);
	int nTop = pList->GetTopIndex();
	int nItem = pList->GetNextItem(-1, LVNI_SELECTED);
	pList->DeleteAllItems();
	while (++i < nCount)
	{
		if (m_sock.Receive(&d, sizeof(d)) < sizeof(d))
			break;
		str.Format(_T("%d"), d.nNumb);
		pList->InsertItem(i, str,i%4);
		pList->SetItemText(i, 1, CString(d.sName));
		str.Format(_T("%g"), d.fSala);
		pList->SetItemText(i, 2, str);
		pList->SetItemText(i, 3, CString(d.sDate));
	}

	if (nItem > -1)
		pList->SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVIS_FOCUSED);
	//设置选中状态和虚线
	//pList->SetItemState(nItem, LVIS_SELECTED|LVIS_FOCUSED, 0); 清除选中状态
	pList->SetFocus();
	pList->SetRedraw(TRUE);
}

BOOL CWorkerDlg::CheckNumb(CString sNumb)
{
	int nNumb = atoi(_bstr_t(sNumb));//_ttoi(sNumb);
	int nCmd = WK_CHECK_NUMB;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&nNumb, sizeof(nNumb));
	int nCount = 0;
	if (m_sock.Receive(&nCount, sizeof(nCount)) < sizeof(nCount))
	{
		MessageBox(_T("网络中断！"));
		return TRUE;
	}
	return nCount>0;
}

BOOL CWorkerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	pList->SetBkColor(RGB(128, 255, 255));
	pList->SetTextBkColor(RGB(128, 255, 255));
	pList->SetTextColor(RGB(255, 0, 255));
	pList->SetImageList(&m_imgList, LVSIL_SMALL);
	pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	pList->InsertColumn(0, _T("工号"), LVCFMT_CENTER, 100);//内部结构：请问是CArray和CList
	pList->InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 140);
	pList->InsertColumn(2, _T("工资"), LVCFMT_CENTER, 120);
	pList->InsertColumn(3, _T("入职日期"), LVCFMT_CENTER, 200);

	Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//方案一、发给服务器 Order 和 Desc
//方案二、本地数据排序
//CArray<LVITEM> 

void CWorkerDlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW p= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nColumn = p->iSubItem;

	if (nColumn == m_nCol)
		m_bDesc = !m_bDesc;
	else
		m_bDesc = FALSE;
	m_nCol = nColumn;
	PFNLVCOMPARE fs[] = {byNumb,byName,bySalary,byDate};
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int i = pList ->GetItemCount();
	while (i-->0)
		pList->SetItemData(i, i);
	pList -> SortItems(fs[nColumn],(DWORD_PTR)pList);


	*pResult = 0;
}


void CWorkerDlg::OnBnClickedDelete()
{
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
	int nNumb = _ttoi(sNumb);
	int nCmd = WK_DELETE;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&nNumb, sizeof(nNumb));

	Refresh();
}


void CWorkerDlg::OnBnClickedModify()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int nItem = pList->GetNextItem(-1, LVNI_SELECTED);
	if (nItem < 0)
	{
		MessageBox(_T("请选中一行再删除！"));
		return;
	}
	CString str = pList->GetItemText(nItem, 0);
	if (MessageBox(_T("确定要删除 ") + str + _T(" 这条记录吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;
	SInfo d;
	d.nNumb = _ttoi(str);
	
	GetDlgItemText(IDC_NAME, str);
	strcpy_s(d.sName, sizeof(d.sName), _bstr_t(str));
	GetDlgItemText(IDC_SALARY, str);
	d.fSala = (float)_ttof(str);
	GetDlgItemText(IDC_DATE, str);
	theApp.CorrectDate(str);
	strcpy_s(d.sDate, sizeof(d.sDate), _bstr_t(str));

	int nCmd = WK_MODIFY;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&d, sizeof(d));

	Refresh();
}

	//strcpy_s(d.sName, sizeof(d.sName),(LPCSTR)(LPCTSTR)str);

void CWorkerDlg::OnBnClickedAdd()
{
	CString str;
	SInfo d;
	GetDlgItemText(IDC_NUMB, str);
	if (CheckNumb(str))
	{
		MessageBox(_T("工号已存在，请重新输入！"),_T("错误"),MB_ICONSTOP);
		SetFocus();
		return;
	}

	d.nNumb = _ttoi(str);
	GetDlgItemText(IDC_NAME, str);
	strcpy_s(d.sName, sizeof(d.sName), _bstr_t(str));
	GetDlgItemText(IDC_SALARY, str);
	d.fSala =(float) _ttof(str);
	GetDlgItemText(IDC_DATE, str);
	theApp.CorrectDate(str);
	strcpy_s(d.sDate, sizeof(d.sDate), _bstr_t(str));

	int nCmd = WK_INSERT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&d, sizeof(d));

	Refresh();
}
