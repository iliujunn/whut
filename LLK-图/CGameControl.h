//CGameControl.h
#pragma once
#ifndef CGAMECONTROL_H
#define CGAMECONTROL_H



#include"CGameException.h"
#include"CGameLogic.h"


class CGameControl {
public:
	static int s_nRows ; //游戏行数
	static int s_nCols; // 游戏列数
	static int s_nPicNum; // 图片数
	static int ItemRest;
	int** m_pGameMap;// 游戏地图数组指针
	CGameLogic m_GameLogic; //游戏逻辑操作对象
	Vertex m_svSelFst;//选中第一个点
	Vertex m_svSelSec;//选中第二个点

	
	void StartGame(void); //开始游戏
	int GetElement(int nRow, int nCol);// 得到某一个元素
	CGameControl(int ,int ,int);
	CGameControl();
	bool Link(Vertex avPath[4], int& nVexnum);
	void SetFirstPoint(int, int);//设置第一个点
	void SetSecondPoint(int, int);//设置第二个点
	int IsWin(int );
	void Shuffle(); // 洗牌
	bool ForEach(Vertex avPath[] , int & ); // 遍历， “提示”键调用
};


#endif // 