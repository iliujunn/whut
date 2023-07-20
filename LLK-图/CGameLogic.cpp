//CGameLogic.cpp
#include "pch.h"
#include "CGameLogic.h"
#include"CGameControl.h"
int **CGameLogic::InitMap() {
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	int** pGameMap = new int* [nRows];
	if (pGameMap == nullptr) {
		throw new CGameException("内存操作异常");
	}
	else {
		for (int i = 0; i < nRows; ++i) {
			pGameMap[i] = new int[nCols];
			if (nullptr == pGameMap) {
				throw new CGameException("内存操作异常");
			}
			else {
				memset(pGameMap[i], 0, sizeof(int) * nCols);
			}
		}
	}

	if ((nRows * nCols) % (2 * nPicNum) != 0) {
		ReleaseMap(pGameMap);
		throw new CGameException("游戏花色与游戏地图不匹配");
	}
	int nRepeatNum = (nRows * nCols) / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; ++i) {
		for (int j = 0; j < nRepeatNum; ++j) {
			pGameMap[nCount / nCols][nCount %nCols] = i;
			++nCount;
		}
	}

	srand(int(time(NULL)));
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; ++i) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		std::swap(pGameMap[nIndex1/nCols][nIndex1%nCols],pGameMap[nIndex2/nCols][nIndex2%nCols]);
	}
	return pGameMap;
}

void CGameLogic::ReleaseMap(int** &pGameMap) {
	for (int i = 0; i < CGameControl::s_nRows; ++i) {
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}

/*
判断是否联通
*/
bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2) {
	ClearStack();
	PushVertex(v1);
	//一条直线
	if (v1.Row == v2.Row) {
		if (LinkInRow(pGameMap, v1, v2)  ) {
			PushVertex(v2);
			return true;
		}
	}

	if (v1.Col == v2.Col) {
		if (LinkInCol(pGameMap, v1, v2) ) {
			PushVertex(v2);
			return true;
		}
	}
	//两条直线
	if (OneCornerLink(pGameMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}
	//三条直线
	if (TwoCornerLink(pGameMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}
	return false;
}

//一条直线消子
bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1 , Vertex v2) {
	int nCol1 = v1.Col, nCol2 = v2.Col;
	int nRow = v1.Row;
	if (nCol1 > nCol2) {
		std::swap(nCol1, nCol2);
	}

	for (int i = nCol1 + 1; i <= nCol2; ++i) {
		
		if (i == nCol2) return true;
		if (pGameMap[nRow][i] != BLANK) break;
	}
	return false;
}

//一条直线消子
bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2) {
	int nCol = v1.Col;
	int nRow1 = v1.Row, nRow2 = v2.Row;
	if (nRow1 > nRow2) {
		std::swap(nRow1, nRow2);
	}
	for (int i = nRow1 + 1; i <= nRow2; ++i) {
		
		if (i == nRow2) return true;
		if (pGameMap[i][nCol] != BLANK) break;
	}
	return false;
}

//判断是否竖线联通
bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol) {
	if (nRow1 > nRow2) {
		std::swap(nRow1, nRow2);
	}
	if (nCol == -1 || nCol == CGameControl::s_nCols) return true;
	for (int i = nRow1 + 1; i <= nRow2; ++i) {
		if (i == nRow2) return TRUE;
		if (pGameMap[i][nCol] != BLANK) {
			CString s1;
			break;
		}
	}
	return FALSE;
}

//横线连通
bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2) {
	if (nCol1 > nCol2) {
		std::swap(nCol1, nCol2);
	}
	if (nRow == -1 || nRow == CGameControl::s_nRows) return true;
	for (int i = nCol1 + 1; i <= nCol2; ++i) {
		if (i == nCol2) return TRUE;
		if (pGameMap[nRow][i] != BLANK) {
			break;
		}
	}
	return FALSE;
}

/*
两条直线消子
*/
bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2) {
	if (pGameMap[v1.Row][v2.Col] == BLANK) {
		if (LineX(pGameMap, v1.Row, v1.Col, v2.Col) && LineY(pGameMap, v1.Row, v2.Row, v2.Col)) {
			Vertex v = { v1.Row,v2.Col,BLANK };
			PushVertex(v);
			return TRUE;
		}
	}
	if (pGameMap[v2.Row][v1.Col] == BLANK) {
		if (LineY(pGameMap, v1.Row, v2.Row, v1.Col) && LineX(pGameMap, v2.Row, v1.Col, v2.Col)) {
			Vertex v = { v2.Row,v1.Col,BLANK };
			PushVertex(v);
			return TRUE;
		}
	}
	return FALSE;
}

//三条直线消子
bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2) {
	for (int i = -1; i <=CGameControl::s_nCols; ++i) {
		if((i == -1 || i == CGameControl::s_nCols) || (pGameMap[v1.Row][i] == BLANK && pGameMap[v2.Row][i] == BLANK) )
		{
			if (LineX(pGameMap, v1.Row, v1.Col, i) && LineX(pGameMap, v2.Row, v2.Col, i) && LineY(pGameMap, v1.Row, v2.Row, i)) {
				Vertex v3 = { v1.Row,i,BLANK };
				Vertex v4 = { v2.Row,i,BLANK };
				PushVertex(v3);
				PushVertex(v4);
				//throw 114;
				return TRUE;
			}
		}
	}
	for (int i = -1; i <= CGameControl::s_nRows; ++i) {
		if ( (i == -1 || i == CGameControl::s_nRows) || (pGameMap[i][v1.Col] == BLANK && pGameMap[i][v2.Col] == BLANK)) {
			if (LineX(pGameMap, i, v1.Col, v2.Col) && LineY(pGameMap, i, v1.Row, v1.Col) && LineY(pGameMap, i, v2.Row, v2.Col)) {
				Vertex v3 = { i,v1.Col,BLANK };
				Vertex v4 = { i,v2.Col,BLANK };
				PushVertex(v3);
				PushVertex(v4);
				return TRUE;
			}
		}
	}

	
	return FALSE;
}

int CGameLogic::GetVexPath(Vertex avPath[4]) {
	for (int i = 0; i < m_nVexNum; ++i) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::PushVertex(Vertex  v) {
	m_avPath[m_nVexNum++] = v;
}

void CGameLogic::PopVertex() {
	--m_nVexNum;
}

void CGameLogic::ClearStack() {
	m_nVexNum = 0;
}

void CGameLogic::Clear(int** &pGameMap, Vertex v1, Vertex v2) {
	pGameMap[v1.Row][v1.Col] = BLANK;
	pGameMap[v2.Row][v2.Col] = BLANK;
}

void CGameLogic:: ReArrangement(int** &pGameMap) {
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	srand(int(time(NULL)));
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; ++i) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		std::swap(pGameMap[nIndex1 / nCols][nIndex1 % nCols], pGameMap[nIndex2 / nCols][nIndex2 % nCols]);
	}
}