#include "Graph.h"

int Graph::get_Num_of_Vexs(){
	return Num_of_Vexs;
}
bool Graph::InsertVex(Vex __Vex){
	if(Num_of_Vexs  == 20 ){
		return false ; 
	}
	Vexs[Num_of_Vexs++] = __Vex ; 
	return true ; 
}

bool Graph::InsertEdge(Edge __Edge){
	int v1 = __Edge.vex1 , v2 = __Edge.vex2;
	int weight = __Edge.weight ; 
	if((v1 <0 || v2 < 0 || v1 >= Num_of_Vexs || v2 >= Num_of_Vexs )){
		return false ; 
	}
	G[v1].push_back({v1,v2,weight});
	G[v2].push_back({v2,v1,weight});
	return true ; 
}

bool Graph::init(){
	Num_of_Vexs = 0  ; 
	return true ; 
}
bool Graph::init(int x){
	Num_of_Vexs = x ;
	return true ; 
}

Vex Graph:: getVex(int id){
	return Vexs[id];
}

int Graph::FindEdge(int id,Edge round[]){
	int k = 0 ; 
	for(int i = 0 ; i < (int)G[id].size() ; ++ i ){
		round[k++] = G[id][i];
	}
	return G[id].size();
}
void Graph::FindEdge(int id,vector<Edge> &around){ 
	for(auto ed: G[id] ){
		around.push_back(ed);
	}
}
int Graph::getVexNum(char *s){
	for(int i = 0 ; i < Num_of_Vexs ; ++ i ){
		if(strcmp(Vexs[i].name,s)){
			return i ; 
		}
	}
	return -1 ; 
}

void Graph::getAllVexs(vector<Vex> & vex_info){
	for(int i = 0 ; i < Num_of_Vexs ; ++ i ){
		vex_info.push_back(Vexs[i]);
	}
}

void Graph::FindShortPath(int s , int e , int &MinDis,vector<int>&num_of_path){

	
	priority_queue<Edge,vector<Edge>,greater<Edge> > q ; 
	bool vis[20] = {0};
	int dis[20] = {0};
	memset(dis,63,sizeof dis);
	dis[s] = 0 ;   
	q.push({s,0,0});
	int path[20];
	path[s] = -1 ; 
	while(!q.empty()){
		int t = q.top().vex1 ; 
		q.pop();
		if(vis[t]) continue ; 
		vis[t] = true ; 
		
		for(auto ed : G[t]){
			int to = ed.vex2 , w = ed.weight ; 
			if(dis[to] >= dis[t] + w ){
				dis[to] = dis[t] + w ; 
				path[to] = t ; 
				q.push({to,to,dis[to]});
			}
		}
	}
	for(int p = e ; p != -1 ; p = path[p]){
		num_of_path.push_back(p);
	}
	reverse(num_of_path.begin(),num_of_path.end());
	MinDis = dis[e];
	//return shortPath ; 
}
bool Graph::dfsTraverse(int start , Path* & _pathList){

	bool vis[20] = {false};
	int apath[20];
	int index = 0 ;
	if(pathList != NULL )delete pathList;
	pathList = new Path ;
	pathList->next = nullptr;
	dfs(start,apath,index,vis);
	_pathList = pathList ;

	return true ;
}
bool Graph::dfs(int start  , int apath[],int & index,bool vis[]){
	vis[start] = true ;
	apath[index++] = start ;
	int cnt = 0 ;
	for(int i = 0 ; i < Num_of_Vexs ; ++ i ) {
		if(vis[i]) ++ cnt ;
	}
	if(cnt == Num_of_Vexs){
		//cout<<"***\n";
		Path * newPath = new Path ;
		newPath->num = index ;
		for(int i = 0 ; i < index ; ++ i ){
			newPath->vex[i] = apath[i];
		}
		newPath->next = nullptr;
		Path *p = this->pathList->next;
		//cout<<pathList->next;
		this->pathList->next = newPath ;
		this->pathList->next->next=p;
		return true ;
	}
	else{
		int nextvex ;
		for(auto ed : G[start]){
			nextvex = (ed.vex1 == start ? ed.vex2 :ed.vex1 );
			if(!vis[nextvex]){
				dfs(nextvex,apath,index,vis);
				vis[nextvex] = false ;
				apath[index--]=-1 ;
			}
		}
	}

	return true ;
}

void Graph::FindMinTree(vector<Edge>&edges,int &minCost){
	minCost = 0 ;
	priority_queue<Edge,vector<Edge>,greater<Edge> > q ; 
	for(int i = 0 ; i < Num_of_Vexs ; ++ i ){
		for(auto ed:G[i]){
			q.push(ed);
		}
	}
	int f[20];
	for(int i = 0 ; i < 20 ; ++ i ) f[i] = i ;
	const auto & find = [&f] (const int& x){
		const auto& s = [&](auto&& self, const int& x) -> int{
			return x == f[x] ? f[x] :f[x] = self(self, f[x]);
		};
		return s(s,x);
	};
	int cnt = 0 ; 
	int x , y ;
	while(!q.empty() && cnt < Num_of_Vexs){
		
		Edge ed = q.top();
		q.pop();
		x = ed.vex1,y=ed.vex2;
		x = find(x),y=find(y);
		if(x!=y){
			f[x] = y;
			++ cnt ;
			edges.push_back(ed);
			minCost += ed.weight;
		}
	}
}
