//CGameLogic.cpp

#include "pch.h"
#include "CGameLogic.h"
#include"CGameControl.h"


CGameLogic::CGameLogic() {
	m_nVexNum = 0;
	m_nCorner = 0;
}
void CGameLogic::InitMap(CGraph& graph) {
	int anTemp[MAX_VERTEX_NUM] = { 0 };
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	int nRepeatNum = (nRows * nCols) / nPicNum;
	for (int i = 0; i < nPicNum; ++i) {
		for (int j = 0; j < nRepeatNum; ++j) {
			anTemp[i * nRepeatNum + j] = i;
		}
	}
	srand(time(NULL));
	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;
		std::swap(anTemp[index1], anTemp[index2]);
	}

	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		graph.AddVertex(anTemp[i]);
	}
	for (int i = 0; i < MAX_COL; ++i) {
		for (int j = 0; j < MAX_ROW; ++j) {
			UpdateArc(graph, j, i);
		}
	}
}

void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol) {
	int nIndex1 = nRow * MAX_COL + nCol;

	if (nCol > 0) { // 左邻点
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);

		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nCol < MAX_COL - 1) { // 右邻点
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);

		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow > 0) { // 上邻点
		int nIndex2 = nIndex1 - MAX_COL;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);

		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow < MAX_ROW - 1) {
		int nIndex2 = nIndex1 + MAX_COL;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);

		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
}
void CGameLogic::ReleaseMap(CGraph& graph) {
	graph.InitGraph();
}

/*
判断是否联通
*/
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2) {
	ClearStack();
	int nIndex1 = v1.Row * MAX_COL + v1.Col;
	int nIndex2 = v2.Row * MAX_COL + v2.Col;
	PushVertex(v1);
	if (v1.Num == BLANK || v2.Num == BLANK) return false;
	if (Search(graph, nIndex1, nIndex2)) {
		PushVertex(v2);
		return true;
	}
	PopVertex();
	return false;
}

//一条直线消子

int CGameLogic::GetVexPath(Vertex avPath[4]) {
	Vertex point = { 0,0,-1 };

	for (int i = 0; i < m_nVexNum; ++i) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::PushVertex(Vertex  v) {
	m_avPath[m_nVexNum++] = v;
	if (isCorner() ) {
		++m_nCorner;
		assert(m_nCorner > 0);
		
	}

}

void CGameLogic::PopVertex() {
	if (isCorner()) {
		--m_nCorner;
	}
	--m_nVexNum;
}

void CGameLogic::ClearStack() {
	m_nVexNum = 0;
	m_nCorner = 0;
}
bool CGameLogic::isCorner() {

	if (m_nVexNum >= 3) {
		int i1 = m_avPath[m_nVexNum - 1].Col + m_avPath[m_nVexNum - 1].Row * MAX_COL;
		int i2 = m_avPath[m_nVexNum - 2].Col + m_avPath[m_nVexNum - 2].Row * MAX_COL;
		int i3 = m_avPath[m_nVexNum - 3].Col + m_avPath[m_nVexNum - 3].Row * MAX_COL;
		if (i2 * 2 != i1 + i3) {
			return true;
		}
	}
	return false;
}
void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2) {
	int nIndex1 = v1.Row * MAX_COL + v1.Col;
	int nIndex2 = v2.Row * MAX_COL + v2.Col;

	//点信息
	graph.UpdateVertex(nIndex1, BLANK);
	graph.UpdateVertex(nIndex2, BLANK);

	//更新边
	UpdateArc(graph, v1.Row, v1.Col);
	UpdateArc(graph, v2.Row, v2.Col);
}

void CGameLogic::ReArrangement(CGraph& graph) {
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	srand(int(time(NULL)));
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; ++i) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		graph.SwapVertex(nIndex1, nIndex2);
	}
	for (int i = 0; i < MAX_ROW; ++i) {
		for (int j = 0; j < MAX_COL; ++j) {
			UpdateArc(graph, i, j);
		}
	}
}

bool CGameLogic::isExist(int Index) {

	for (int i = 0; i < m_nVexNum; ++i) {
		int Index2 = m_avPath[i].Row * MAX_COL + m_avPath[i].Col;
		if (Index == Index2) {
			return true;
		}
	}
	return false;
}

bool CGameLogic::Search(CGraph& graph, int Index1, int Index2) {
	int nVexnum = graph.GetVexnum();
	//cout << nVexnum << std::endl;
	Vertex v = { 0,0,0 };
	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		v.Row = i / MAX_COL;
		v.Col = i % MAX_COL;
		if (!isExist(i) && graph.GetArc(Index1, i)) {
			PushVertex(v);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}
			if (i != Index2) {
				if (graph.GetVertex(i) != BLANK) {
					PopVertex();
					continue;
				}
				if (Search(graph, i, Index2)) {

					return TRUE;
				}
			}
			else {
				//PopVertex();
				return TRUE;
			}
			PopVertex();
		}
	}
	return FALSE;
}