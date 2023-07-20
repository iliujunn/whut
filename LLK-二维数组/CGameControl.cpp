//CGameControl.cpp
#include "pch.h"
#include "CGameControl.h"

int CGameControl::s_nRows = MAX_ROW;
int CGameControl::s_nCols = MAX_COL;
int CGameControl::s_nPicNum = MAX_PIC_NUM;
int CGameControl::ItemRest = MAX_ROW * MAX_COL;
CGameControl::CGameControl() {

}
CGameControl::CGameControl(int Row, int Col, int Num) {

}

void CGameControl::StartGame() {

	m_GameLogic.InitMap(m_graph);

}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}

bool CGameControl::Link(Vertex avPath[4], int& nVexnum) {
	if (m_svSelFst.Col == m_svSelSec.Col && m_svSelFst.Row == m_svSelSec.Row) {
		return false;
	}
	if (m_graph.GetVertex(m_svSelSec) != m_graph.GetVertex(m_svSelFst)) {
		return false;
	}
	// «∑Ò¡¨Õ®
	if (m_GameLogic.IsLink(m_graph, m_svSelFst, m_svSelSec)) {
		m_GameLogic.Clear(m_graph, m_svSelFst, m_svSelSec);
		nVexnum = m_GameLogic.GetVexPath(avPath);
		ItemRest -= 2;
		return TRUE;
	}

	return FALSE;
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_svSelFst.Col = nCol;
	m_svSelFst.Row = nRow;
	m_svSelFst.Num = m_graph.GetVertex(nRow*MAX_COL + nCol);
}

void CGameControl::SetSecondPoint(int nRow, int nCol) {
	m_svSelSec.Col = nCol;
	m_svSelSec.Row = nRow;
	m_svSelSec.Num = m_graph.GetVertex(nRow*MAX_COL+nCol);
}

int CGameControl::IsWin(int countDown) {
	if (countDown == 0) return -1;
	if (ItemRest == 0 && countDown != 0) {
		return 1;
	}
	return 0;
}

void CGameControl::Shuffle() {
	m_GameLogic.ReArrangement(m_graph);
}

bool CGameControl::ForEach(Vertex avPath[], int& nVexnum) {
	
	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		if (m_graph.GetVertex(i) == BLANK) continue;
		SetFirstPoint(i / MAX_COL, i % MAX_COL);
		for (int j = 0; j < MAX_VERTEX_NUM; ++j) {
			if (j == i || m_graph.GetVertex(j) == BLANK) continue;
			SetSecondPoint(j / MAX_COL, j % MAX_COL);
			int m = m_graph.GetVertex(i), n = m_graph.GetVertex(j);
			if (Link(avPath, nVexnum)) {
				return true;
			}
		}
	}
	return false;
}