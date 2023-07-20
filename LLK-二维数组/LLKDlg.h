
// LLKDlg.h: 头文件
//

#pragma once

#include "CRankDialog.h"

// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CLLKDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CDC m_dcMem;
	HICON m_hIcon;

	// 生成的消息映射函数
	void InitBackground();
	void Paint();
	void PlayMusic(int);
	void StopMusic(int);
	void SetVolumn(int,int);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MyDataExchange *m_dataExchange; 
	static  CString BGM[];//BGM列表
	int CurrentBGMID; // 当前播放背景音乐的id，PlayMusic中更新
	int CurrentBGMVolumn; 
	afx_msg void OnBnClickedBtnBasic();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnClickedBtnRank();

};
