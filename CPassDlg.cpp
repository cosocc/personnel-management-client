// CPassDlg.cpp: 实现文件
//

#include "pch.h"
#include "Worker_Lx.h"
#include "CPassDlg.h"
#include "afxdialogex.h"


// CPassDlg 对话框

IMPLEMENT_DYNAMIC(CPassDlg, CDialogEx)

CPassDlg::CPassDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PASS_DLG, pParent)
{

}

CPassDlg::~CPassDlg()
{
}

void CPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPassDlg, CDialogEx)
END_MESSAGE_MAP()


// CPassDlg 消息处理程序
