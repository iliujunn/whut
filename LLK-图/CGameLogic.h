//CGameLogic.h
#pragma once
#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H



#include"global.h"
#include"CGameException.h"

class CGameLogic {
public:
	CGameLogic(){}
	Vertex m_avPath[4];
	int m_nVexNum;
	int** InitMap();// 初始化游戏地图
	void ReleaseMap(int**& pGameMap); //释放地图
	bool IsLink(int**, Vertex, Vertex);
	void Clear(int** &, Vertex, Vertex);
	int GetVexPath(Vertex avPath[4]);
	void ReArrangement(int** &);
protected:
	void PushVertex(Vertex);
	void PopVertex();
	bool LinkInRow(int**, Vertex, Vertex);
	bool LinkInCol(int**, Vertex, Vertex);
	bool LineY(int**, int, int, int);
	bool LineX(int**, int, int, int);
	bool OneCornerLink(int**, Vertex, Vertex);
	void ClearStack();
	bool TwoCornerLink(int**, Vertex, Vertex);

};

#endif // !1