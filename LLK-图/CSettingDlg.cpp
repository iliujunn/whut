// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CSettingDlg.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_Setting, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, BGM_SELECT, m_BGMList);
	DDX_Control(pDX, BGM_SLIDER, m_sliderVolumn);
	DDX_Control(pDX, INC_VOLUMN, increaseVolumn);
	DDX_Control(pDX, DEC_VOLUMN, decreaseVolumn);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_CBN_SELCHANGE(BGM_SELECT, &CSettingDlg::OnComboBGMSelectionChange)
	ON_NOTIFY(NM_CUSTOMDRAW, BGM_SLIDER, OnHScrollSliderVolume)
	ON_BN_CLICKED(INC_VOLUMN, &CSettingDlg::OnClickedIncVolumnIncrease)
	ON_BN_CLICKED(DEC_VOLUMN, &CSettingDlg::OnClickedDecVolumnDecrease)
	ON_BN_CLICKED(SILENT_BUTTON, &CSettingDlg::OnClickedSilentButton)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_sliderVolumn.SetPos(volumn);
	m_BGMList.AddString(_T("鸡你太美"));
	m_BGMList.AddString(_T("开团小曲"));
	m_BGMList.SetCurSel(0);  // 默认选中第一项
	m_BGMList.SetEditSel(0, 0);
	m_sliderVolumn.SetRange(0, 100);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSettingDlg::OnComboBGMSelectionChange()
{
	int selectedIndex = m_BGMList.GetCurSel();  // 获取当前选中项的索引
	CString selectedText;
	m_BGMList.GetLBText(selectedIndex, selectedText);  // 获取当前选中项的文本
	if (selectedText == L"鸡你太美") {
		BGMID = 0;
	}
	else if(selectedText == L"开团小曲") {
		// TO DO 
		BGMID = 1;
	}
	// 处理用户选择的动作
}

void CSettingDlg::OnHScrollSliderVolume(NMHDR* pNMHDR, LRESULT* pResult)
{
	volumn = m_sliderVolumn.GetPos();
	*pResult = 0;
	
	// 处理滑块控件的消息
	// 可以通过滑块控件对象来获取滑块的位置，并进行相应的操作
}


void CSettingDlg::OnClickedIncVolumnIncrease()
{
	// TODO: 在此添加控件通知处理程序代码
	
	volumn = m_sliderVolumn.GetPos();
	if (volumn < 100) {
		volumn += 5;
		if (volumn > 100) {
			volumn = 100;
		}
	}
	else {
		MessageBox(L"100了， 加不动了！",L"音量");
	}
	m_sliderVolumn.SetPos(volumn);
}


void CSettingDlg::OnClickedDecVolumnDecrease()
{
	volumn = m_sliderVolumn.GetPos();
	if (volumn != 0) {
		volumn -= 5;
		if (volumn < 0) volumn = 0;
	}
	else {
		MessageBox(L"音量已经到0啦！",L"音量");
	}
	m_sliderVolumn.SetPos(volumn);
	
	// TODO: 在此添加控件通知处理程序代码
}


void CSettingDlg::OnClickedSilentButton()
{
	if (volumn != 0) {
		volumn = 0;
		m_sliderVolumn.SetPos(volumn);
	}
	else {
		MessageBox(L"别点了，退出去就静音了！",L"静音提示");
	}
	// TODO: 在此添加控件通知处理程序代码
}
