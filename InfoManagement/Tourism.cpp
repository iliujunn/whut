#include "Tourism.h"


void Tourism:: CreateGraph(){
	if(m_Graph.get_Num_of_Vexs() != 0 ){
		throw MyException("Repeated initialization!");
	}
	ifstream in ; 
	in.open("data/Vex.txt",ios::binary|ios::in) ;
	int Num_of_Vex ; 
	in>>Num_of_Vex; 
	//m_Graph.init(Num_of_Vex);
	Vex temp ; 
	for(int i = 0 ; i < Num_of_Vex ; ++ i ){
		in>>temp.num>>temp.name>>temp.desc;
		m_Graph.InsertVex(temp);
	}
	in.close();
	
	ifstream in2 ; 
	in2.open("data/Edge.txt",ios::binary|ios::in);
	Edge e ; 
	while((in2>>e.vex1>>e.vex2>>e.weight)){
		m_Graph.InsertEdge(e);
	}
	in2.close();
}

Vex Tourism::getVex(int i){
	return m_Graph.getVex(i);
}

void Tourism::getVexInfo(vector<Vex>&vex_info){
	if(m_Graph.get_Num_of_Vexs() == 0 ){
		throw MyException("The object was not initialized");
	}
	
	m_Graph.getAllVexs(vex_info);
}

void Tourism::GetSpotInfo(int id){
	if(m_Graph.get_Num_of_Vexs() == 0 ){
		throw MyException("The object was not initialized");
	}
	if(id >= m_Graph.get_Num_of_Vexs() || id < 0){
		throw MyException("The Vexs does not exist !");
	}
	//该节点信息
	Vex v = m_Graph.getVex(id);
	//找相邻边
	cout<<v.num<<"---"<<v.name<<"\n";
	cout<<v.desc<<"\n";
	
	vector<Edge>around;
	m_Graph.FindEdge(id,around);

	cout<<"\n周边景区：  距离(m)\n";
	int spotID;
	for(auto spot : around){
		spotID = (spot.vex1 == id ? spot.vex2 : spot.vex1);
		cout<<v.name<<"-->"<<getVex(spotID).name<<"   "<<spot.weight<<endl;
	}
	

	return ; 
}

void Tourism::FindShortPath(int s, int e ){
	if(m_Graph.get_Num_of_Vexs() == 0 ){
		throw MyException("The object was not initialized");
	}
	if(m_Graph.get_Num_of_Vexs() <= s || m_Graph.get_Num_of_Vexs() <= e || s < 0 || e < 0  ){
		throw MyException("The Vexs does not exist !");
	}
	int MinDis ;
	vector<int>num_of_path;
	m_Graph.FindShortPath(s,e,MinDis,num_of_path);
	cout<<"\n最短距离：   "<<MinDis<<endl;
	cout<<getVex(num_of_path[0]).name;
	for(int i = 1 ; i < (int)num_of_path.size() ; ++ i){
		cout<<"--->"<<getVex(num_of_path[i]).name;
	}
	cout<<"\n";
}

void Tourism::TravelPath(int start ){
	
	if(m_Graph.get_Num_of_Vexs() == 0 ){
		throw MyException("The object was not initialized");
	}
	if(m_Graph.get_Num_of_Vexs() <= start || start < 0){
		throw MyException("The Vex does not exist !");
	}
	Path *path ;
	m_Graph.dfsTraverse(start,path);
	
    
	
	Path *p = path->next;
	Vex theVex ;  
	while(p != NULL){
		if(p->num){
			cout<<getVex(start).name;
			for(int i = 1 ; i < p->num ; ++ i ){
				theVex = getVex(p->vex[i]);
				cout<<"--->"<<theVex.name;
			}	
			cout<<endl;
		}
		p=p->next;
	}
	
	//释放空间
	Path *q ;
	p = path ;
	while(p->next != nullptr){
		q = p ;
		p = p->next ;
		if(q) delete q ;
	}
	
}

void Tourism::DesignMinpath(){
	if(m_Graph.get_Num_of_Vexs() == 0 ){
		throw MyException("The object was not initialized");
	}
	vector<Edge>edges ;
	int MinCost ;
	m_Graph.FindMinTree(edges,MinCost);
	cout<<"最小距离： "<<MinCost<<"\n";
	for(auto ed : edges){
		cout<<getVex(ed.vex1).name<<"---"<<getVex(ed.vex2).name<<"---"<<ed.weight<<"\n";
	}
}
