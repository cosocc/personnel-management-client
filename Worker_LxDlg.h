
// Worker_LxDlg.h: 头文件
//

#pragma once


// CWorkerDlg 对话框
class CWorkerDlg : public CDialogEx
{
// 构造
public:
	CWorkerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORKER_LX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnClickedDelete();
	afx_msg void OnClickedModify();
	afx_msg void OnBnClickedSave();
};
