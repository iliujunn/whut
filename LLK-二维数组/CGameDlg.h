#pragma once
#include "afxdialogex.h"
#include "CGameControl.h"
#include "global.h"
#include "CGameSettingDlg.h"
#include <Vfw.H>
#include "Windows.h"
#include "mmsystem.h"
#pragma comment(lib, "WINMM.LIB")
#include"MyDataExchange.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CGameDlg(CWnd* pParent = nullptr, MyDataExchange *dataExchange = nullptr);
	virtual ~CGameDlg();


	CDC m_dcMem;//内存DC
	CDC m_dcBG; //背景DC
	CDC m_dcElement; //元素内存DC
	CDC m_dcMask; //掩码内存DC
	CPoint m_ptGameTop; //游戏区起始点，游戏第一张图片坐标，相对于窗口客户区
	CSize m_sizeElem; //元素图片大小
	CRect m_rtGameRect; //游戏区域大小
	CGameControl m_GameC; //游戏控制类
	// 倒计时（秒）
	CStatic m_staticCountdown;// 倒计时（秒）
	int m_CountDownSeconds;


	
	void UpdateWindow();//更新界面
	void UpdateMap(); //更新游戏地图

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitElement(); //初始化元素图片与DC
	void InitBackground();
	void PlayEffect(int);
	void StopEffect(int);
	void InsertIntoDataBase(int);
	DECLARE_MESSAGE_MAP()
public:
	int m_Victory; // 1胜利， -1 失败，0比赛中
	MyDataExchange *m_dataExchange;
	static CString Effect[]; //音效
	static CString Theme[][3]; // 主题
	int EffectID; // 音效id ，0开始
	int ThemeID; // 主题id，0开始
	CFont font;
	bool m_bFirstPoint;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint(); // WM_Paint消息函数
	void DrawTipFrame(int, int);
	void DrawTipLine(Vertex avPath[],int);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedStaticCountdown();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton StartBtn;
	afx_msg void OnClickedGameSetting();
	afx_msg void OnClickedReset();
	afx_msg void OnClickedTipButton();
	CButton m_TipBtn;
	CButton m_ResetBtn;
	CButton m_SettingBtn;
};
