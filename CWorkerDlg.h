#pragma once


// CWorkerDlg 对话框

class CWorkerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkerDlg)
	CSocket& m_sock;
	static BOOL m_bDesc;//TRUE是反序
	int m_nCol = -1;
	void Refresh(int nOrder=0);
	BOOL CheckNumb(CString sNumb);
	CImageList m_imgList;


	static int CALLBACK byNumb(LPARAM p1, LPARAM p2, LPARAM p)
	{
		CListCtrl* pList = (CListCtrl*)p;
		CString s1 = pList->GetItemText(p1, 0);
		CString s2 = pList->GetItemText(p2, 0);
		if(m_bDesc)
			return _ttoi(s1) < _ttoi(s2);
		else
			return _ttoi(s1) > _ttoi(s2);
	}
	static int CALLBACK byName(LPARAM p1, LPARAM p2, LPARAM p)
	{
		//CString s1 = m_list.GetItemText(p1, 1);
		//CString s2 = m_list.GetItemText(p2, 1);
		CListCtrl* pList = (CListCtrl*)p;
		CString s1 = pList->GetItemText(p1, 1);
		CString s2 = pList->GetItemText(p2, 1);
	//	return m_bDesc && s1.CompareNoCase(s2) < 0;
		if (m_bDesc)
			return s1.CompareNoCase(s2) < 0;
		else
			return s1.CompareNoCase(s2) > 0;


	}
	static int CALLBACK bySalary(LPARAM p1, LPARAM p2, LPARAM p)
	{
		CListCtrl* pList = (CListCtrl*)p;
		CString s1 = pList->GetItemText(p1, 2);
		CString s2 = pList->GetItemText(p2, 2);
		if (m_bDesc)
			return _ttof(s1) < _ttof(s2);
		else
			return _ttof(s1) > _ttof(s2);
	}
	static int CALLBACK byDate(LPARAM p1, LPARAM p2, LPARAM p)
	{
		CListCtrl* pList = (CListCtrl*)p;
		CString s1 = pList->GetItemText(p1, 3);
		CString s2 = pList->GetItemText(p2, 3);
		
		//	s1.FindOneOf(_T("/-"));//strpbrk 
		COleDateTime t1, t2;
		t1.ParseDateTime(s1, VAR_DATEVALUEONLY);
		t2.ParseDateTime(s2, VAR_DATEVALUEONLY);
		if (m_bDesc)
			return t1 < t2;//time_t
		else
			return t1 > t2;//time_t

	}
public:
	CWorkerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CWorkerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORKER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedAdd();
};
