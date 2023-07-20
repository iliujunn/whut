#pragma once
#include "afxdialogex.h"


// CGameSettingDlg 对话框

class CGameSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameSettingDlg)

public:
	CGameSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = GAME_SETTING_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int effectID;
	int themeID;
	afx_msg void OnBnClickedOk();
	CComboBox m_comEffect;
	CComboBox m_comTheme;
	afx_msg void OnSelchangeSelectEffect();
	afx_msg void OnSelchangeSelectTheme();
	virtual BOOL OnInitDialog();
};
