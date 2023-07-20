#pragma once
#include "afxdialogex.h"


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_Setting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnComboBGMSelectionChange();
	afx_msg void OnHScrollSliderVolume(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	UINT BGMID;
	int volumn;
	CComboBox m_BGMList;
	virtual BOOL OnInitDialog();
	CSliderCtrl m_sliderVolumn;
	CButton increaseVolumn;
	CButton decreaseVolumn;
	afx_msg void OnClickedIncVolumnIncrease();
	afx_msg void OnClickedDecVolumnDecrease();
	afx_msg void OnClickedSilentButton();
};


