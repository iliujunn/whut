#include <iostream>
#include<fstream>
#include "Tourism.h"
#include<cstring>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void showMenu(){
	cout<<"==== 景区信息管理系统 ===="<<endl;
	cout<<"1. 创建景区景点图\n";
	cout<<"2. 查询景点信息\n";
	cout<<"3. 旅游景点导航\n";
	cout<<"4. 搜索最短路径\n";
	cout<<"5. 铺设电路规划\n";
	cout<<"0. 退出\n";
}
void querySpotInformation(Tourism & t);
void createSpotGraph(Tourism & t);
void navigateTourismAttractions(Tourism & t);
void searchForTheShortestPath(Tourism & t);
void planToLayCircuit(Tourism &t);
int main(int argc, char** argv) {
	int op ;
	//cin>>op ;
	Tourism t ; 
	while(true){
		cout<<"\n";
		showMenu();
		cin>>op ;
		switch (op) {
		case 1:
			createSpotGraph(t);
			break;
		case 2:
			querySpotInformation(t);
			break;
		case 3:
			navigateTourismAttractions(t);
			break;
		case 4:	
			searchForTheShortestPath(t);
			break;
		case 5:
			planToLayCircuit(t);
			break;
		default:
			exit(0);
			break;
		}
	}
	return 0;
}
void createSpotGraph(Tourism & t){
	try{
		t.CreateGraph();
	}catch(const MyException & exception ){
		cout<<"Exception Caught!"<<"\n"<<exception.getMessage()<<'\n';
		cout<<"请选择其他选项!\n";
		return ;
	}
}
void querySpotInformation(Tourism & t){
	vector<Vex>vex_info;
	try{
		t.getVexInfo(vex_info);
	}catch(const MyException &exception){
		cout<<"Exception Caught!"<<"\n"<<exception.getMessage()<<endl;
		cout<<"请选择选项1\n";
		return ;
	}
	
	
	cout<<"景点总数：\t"<<(int)vex_info.size()<<"\n";
	
	for(auto v : vex_info){
		cout<<v.num<<"---"<<v.name<<'\n';
	}
	cout<<"输入查询景点的编号:";
	int id ; 
	cin>>id ;
	cout<<"\n";
	try{
		t.GetSpotInfo(id);
	}catch(const MyException &exception){
		cout<<"Exception Caught!"<<"\n"<<exception.getMessage()<<endl;
		cout<<"请重新选择！\n";
		return ;
	}
}

void navigateTourismAttractions(Tourism & t){
	int start ;
	cout<<"请输入起点编号：\t";
	cin>>start;
	cout<<"\n";
	
	try{
		t.TravelPath(start);
	}catch(const MyException &exception){
		cout<<"Exception Caught!"<<"\n"<<exception.getMessage()<<endl;
		cout<<"请重新选择！\n";
		return ;
	}
}

void searchForTheShortestPath(Tourism & t){
	int s , e ;
	cout<<"输入起点编号:    ";
	cin>>s;
	cout<<"输入终点编号:    ";
	cin>>e;
	try{
		t.FindShortPath(s,e);
	}catch(const MyException &exception){
		cout<<"Exception Caught!"<<"\n"<<exception.getMessage()<<endl;
		cout<<"请选择选项1\n";
		return ;
	}
}
void planToLayCircuit(Tourism &t){
	try{
		t.DesignMinpath();
	}catch(const MyException &exception){
		cout<<"Exception Caught!"<<"\n"<<exception.getMessage()<<endl;
		cout<<"请选择选项1\n";
		return ;
	}
}
