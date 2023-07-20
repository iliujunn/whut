#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<fstream>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
#include "myexception.h"
using namespace std;
struct Edge{
	int vex1 ; 
	int vex2 ;
	int weight ;
	
	bool operator < (const Edge & a) const{
		return weight < a.weight ; 
	}
	bool operator > (const Edge & a ) const{
		return weight > a.weight ; 
	}
};
struct Path{
	int num ;
	int vex[20];
	Path *next ;
	Path():num(0){
		for(int i = 0 ; i < 20 ; ++ i ){
			vex[i] = 0 ;
		}
	}
};
struct Vex{
	int num ; 
	char name[20];
	char desc[1024];
};
class Graph{
private:
	vector<Edge>G[20] ;
	Vex Vexs[20];
	Path *pathList;
	const int MaxSize = 20 ; 
	
	int Num_of_Vexs ;
	
public:
	bool InsertVex(Vex a_Vex);//插入节点
	bool InsertEdge(Edge a_Edge);//插入边
	Vex getVex(int id); //根据节点得到点的编号
	int get_Num_of_Vexs();//总节点数
	bool init();
	bool init(int x);	
	void getAllVexs(vector<Vex> &vex_info ); //所有节点
	int FindEdge(int id, Edge round[]); //与id相邻的所有边
	void FindEdge(int id,vector<Edge> & around);
	void FindShortPath(int s,int e,int& minDis,vector<int>& num_of_path );//s-->e 最短路
	void FindMinTree(vector<Edge> & edges,int &Mincost); //最小生成树
	int getVexNum(char *name); //根据名称找编号
	bool dfs(int start , int apath[] ,int& index, bool vis[] ); //一次经过所有点的路径
	bool dfsTraverse(int start , Path *& pathList);
	Graph():Num_of_Vexs(0){pathList = new Path ;pathList->next=nullptr;}
	Graph(int x):Num_of_Vexs(x){pathList = new Path ;pathList->next=nullptr;}
};
#endif
