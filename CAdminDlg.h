#pragma once


// CAdminDlg 对话框

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)
	void Refresh();
	CSocket &m_sock;
public:
	CAdminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdminDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedPrint();
};
