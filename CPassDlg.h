#pragma once


// CPassDlg 对话框

class CPassDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPassDlg)

public:
	CPassDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPassDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
