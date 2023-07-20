//CGameLogic.h
#pragma once
#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H


#include "CGraph.h"
#include"global.h"
#include"CGameException.h"

class CGameLogic {
public:
	CGameLogic();
	Vertex m_avPath[MAX_VERTEX_NUMS];
	int m_nVexNum;
	int m_nCorner;

	// ��ʼ����Ϸ��ͼ
	void InitMap(CGraph&);
	void UpdateArc(CGraph&, int, int);
	void ReleaseMap(CGraph&); //�ͷŵ�ͼ
	bool IsLink(CGraph&, Vertex, Vertex);
	void Clear(CGraph& graph, Vertex, Vertex);
	int GetVexPath(Vertex avPath[4]);
	void ReArrangement(CGraph&);
protected:
	void PushVertex(Vertex);
	void PopVertex();
	bool isCorner();
	bool isExist(int); // ���Ƿ������·����
	bool Search(CGraph&, int, int);
	void ClearStack();


};

#endif // !1