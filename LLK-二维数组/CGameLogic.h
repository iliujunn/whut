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

	// 初始化游戏地图
	void InitMap(CGraph&);
	void UpdateArc(CGraph&, int, int);
	void ReleaseMap(CGraph&); //释放地图
	bool IsLink(CGraph&, Vertex, Vertex);
	void Clear(CGraph& graph, Vertex, Vertex);
	int GetVexPath(Vertex avPath[4]);
	void ReArrangement(CGraph&);
protected:
	void PushVertex(Vertex);
	void PopVertex();
	bool isCorner();
	bool isExist(int); // 点是否存在于路径中
	bool Search(CGraph&, int, int);
	void ClearStack();


};

#endif // !1