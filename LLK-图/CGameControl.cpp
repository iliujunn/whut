//CGameControl.cpp
#include "pch.h"
#include "CGameControl.h"
int CGameControl::s_nRows = MAX_ROW;
int CGameControl::s_nCols = MAX_COL;
int CGameControl::s_nPicNum = MAX_PIC_NUM;
int CGameControl::ItemRest = MAX_ROW * MAX_COL;
CGameControl::CGameControl(){
	
}
CGameControl::CGameControl(int Row, int Col, int Num) {
	
}

void CGameControl::StartGame() {
	m_pGameMap = m_GameLogic.InitMap();
}

int CGameControl::GetElement(int nRow , int nCol) {
	return m_pGameMap[nRow][nCol];
}

bool CGameControl::Link(Vertex avPath[4], int& nVexnum) {
	if (m_svSelFst.Col == m_svSelSec.Col && m_svSelFst.Row == m_svSelSec.Row) {
		return false;
	}
	if (m_pGameMap[m_svSelFst.Row][m_svSelFst.Col] != m_pGameMap[m_svSelSec.Row][m_svSelSec.Col]) {
		return false;
	}
	// «∑Ò¡¨Õ®
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec)) {
		m_GameLogic.Clear(m_pGameMap, m_svSelFst, m_svSelSec);
		nVexnum = m_GameLogic.GetVexPath(avPath);
		ItemRest -= 2;
		return TRUE;
	}
	
	return FALSE;
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_svSelFst.Col = nCol;
	m_svSelFst.Row = nRow;
	m_svSelFst.Num = m_pGameMap[nRow][nCol];
}

void CGameControl::SetSecondPoint(int nRow, int nCol) {
	m_svSelSec.Col = nCol;
	m_svSelSec.Row = nRow;
	m_svSelSec.Num = m_pGameMap[nRow][nCol];
}

int CGameControl::IsWin(int countDown) {
	if (countDown == 0) return -1;
	if (ItemRest == 0 && countDown != 0) {
		return 1;
	}
	return 0;
}

void CGameControl::Shuffle() {
	m_GameLogic.ReArrangement(m_pGameMap);
}

bool CGameControl::ForEach(Vertex avPath[] , int & nVexnum) {
	bool is_Link = false;
	for (int i = 0; i < s_nCols; ++i) {
		for (int j = 0; j < s_nRows; ++j) {
			if(m_pGameMap[j][i] != BLANK ){
				SetFirstPoint(j, i);
				for (int x = 0; x < s_nCols; ++x) {
					for (int y = 0; y < s_nRows; ++y) {
						if (m_pGameMap[y][x] != BLANK) {
							SetSecondPoint(y, x);
							is_Link = Link(avPath, nVexnum);
							if (is_Link) {
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}