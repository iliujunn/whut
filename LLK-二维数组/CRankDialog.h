#pragma once
#include "afxdialogex.h"
#include<vector>
#include"MyDataExchange.h"
// CRankDialog 对话框

class CRankDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDialog)

public:
	CRankDialog(CWnd* pParent = nullptr);
	CRankDialog(CWnd* pParent = nullptr, MyDataExchange *dataExchange= nullptr);   // 标准构造函数
	virtual ~CRankDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = RANK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CBrush m_brushBackground; // 用于存储背景色的画刷对象
	void InitBackground();
	CDC m_dcMem;
	DECLARE_MESSAGE_MAP()
public:
	MyDataExchange* m_dataExchange;
	CListCtrl m_rankList;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd , UINT nCtlColor);
};
