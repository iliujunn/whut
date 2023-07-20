//CGameControl.h
#pragma once
#ifndef CGAMECONTROL_H
#define CGAMECONTROL_H



#include"CGameException.h"
#include"CGameLogic.h"


class CGameControl {
public:
	static int s_nRows ; //��Ϸ����
	static int s_nCols; // ��Ϸ����
	static int s_nPicNum; // ͼƬ��
	static int ItemRest;
	int** m_pGameMap;// ��Ϸ��ͼ����ָ��
	CGameLogic m_GameLogic; //��Ϸ�߼���������
	Vertex m_svSelFst;//ѡ�е�һ����
	Vertex m_svSelSec;//ѡ�еڶ�����

	
	void StartGame(void); //��ʼ��Ϸ
	int GetElement(int nRow, int nCol);// �õ�ĳһ��Ԫ��
	CGameControl(int ,int ,int);
	CGameControl();
	bool Link(Vertex avPath[4], int& nVexnum);
	void SetFirstPoint(int, int);//���õ�һ����
	void SetSecondPoint(int, int);//���õڶ�����
	int IsWin(int );
	void Shuffle(); // ϴ��
	bool ForEach(Vertex avPath[] , int & ); // ������ ����ʾ��������
};


#endif // 