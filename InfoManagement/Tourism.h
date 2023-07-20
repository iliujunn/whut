#ifndef TOURISM_H
#define TOURISM_H
#include "Graph.h"

class Tourism{
	Graph m_Graph ; 
public:
	Vex getVex(int i);
	void getVexInfo(vector<Vex> & vex_info);
	void CreateGraph();
	void GetSpotInfo(int x);
	void FindShortPath(int s , int e );
	void TravelPath(int start );
	void DesignMinpath();
};
#endif
