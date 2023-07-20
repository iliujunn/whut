#include "pch.h"
#include "CGraph.h"
#include "global.h"

CGraph::CGraph() {
	InitGraph();
}
CGraph::~CGraph() {

}
void CGraph::InitGraph() {
	// 初始化
	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		m_Vertices[i] = -1;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		for (int j = 0; j < MAX_VERTEX_NUM; ++j) {
			m_AdjMatrix[i][j] = 0;
		}
	}
}

void CGraph::AddArc(int nIndex1, int nIndex2) {
	m_AdjMatrix[nIndex1][nIndex2] = m_AdjMatrix[nIndex2][nIndex1] = 1;
}

int CGraph::AddVertex(int info) { //加点，返回点数
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return 0;
	}

	m_Vertices[m_nVexnum++] = info;
	return m_nVexnum;
}

int CGraph::GetVertex(int index) {
	return m_Vertices[index];
}
int CGraph::GetVertex(Vertex v) {
	int index = v.Col + v.Row * MAX_COL;
	return m_Vertices[index];
}

bool CGraph::GetArc(int index1, int index2) {
	return m_AdjMatrix[index1][index2];
}

void CGraph::UpdateVertex(int index, int info) {
	m_Vertices[index] = info;
}

int CGraph::GetVexnum() {
	return m_nVexnum;
}

void CGraph::ClearGraph() {
	InitGraph();
}

void CGraph::SwapVertex(int nIndex1, int nIndex2) {
	std::swap(m_Vertices[nIndex1], m_Vertices[nIndex2]);
}
