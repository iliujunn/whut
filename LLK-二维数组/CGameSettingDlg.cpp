// CGameSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameSettingDlg.h"


// CGameSettingDlg 对话框

IMPLEMENT_DYNAMIC(CGameSettingDlg, CDialogEx)

CGameSettingDlg::CGameSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(GAME_SETTING_DLG, pParent)
{

}

CGameSettingDlg::~CGameSettingDlg()
{
}

void CGameSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, SELECT_EFFECT, m_comEffect);
	DDX_Control(pDX, SELECT_THEME, m_comTheme);
}


BEGIN_MESSAGE_MAP(CGameSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGameSettingDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(SELECT_EFFECT, &CGameSettingDlg::OnSelchangeSelectEffect)
	ON_CBN_SELCHANGE(SELECT_THEME, &CGameSettingDlg::OnSelchangeSelectTheme)
END_MESSAGE_MAP()


// CGameSettingDlg 消息处理程序


void CGameSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
	CDialogEx::OnOK();
}


void CGameSettingDlg::OnSelchangeSelectEffect()
{
	int selectedIndex = m_comEffect.GetCurSel();  // 获取当前选中项的索引
	CString selectedText;
	m_comEffect.GetLBText(selectedIndex, selectedText);  // 获取当前选中项的文本
	
	if (selectedText == L"只因") {
		effectID = 0;
	}
	else if (selectedText == L"你干嘛") {
		effectID = 1;
	}
}


void CGameSettingDlg::OnSelchangeSelectTheme()
{
	int selectedIndex = m_comTheme.GetCurSel();  // 获取当前选中项的索引
	CString selectedText;
	m_comTheme.GetLBText(selectedIndex, selectedText);  // 获取当前选中项的文本

	if (selectedText == L"经典水果") {
		themeID = 0;
	}
	else if (selectedText == L"消消小黑子") {
		themeID = 1;
	}
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CGameSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_comEffect.AddString(_T("只因"));
	m_comEffect.AddString(_T("你干嘛"));
	m_comEffect.SetCurSel(0); //选中第一项*/

	m_comTheme.AddString(L"经典水果");
	m_comTheme.AddString(L"消消小黑子");
	m_comTheme.SetCurSel(0);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
