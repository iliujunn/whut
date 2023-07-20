
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include<iostream>
#include<queue>
using namespace std;
struct TNode{
	unsigned char h ;
	int weight;
	int parent,lchild,rchild ;
	int index ;
	bool operator < (const TNode & _Node) const{
		return weight < _Node.weight ;
	}
	bool operator > (const TNode & _Node) const{
		return weight > _Node.weight ;
	}
};
class HuffmanTree {
public:
	int Size ;
	TNode *HT; 
	priority_queue<TNode, vector<TNode>,greater<TNode> > SELECT ;
	char filename[256] ;
	int weight[256];
	char *HC[256];
public:
	
	HuffmanTree() ;
	~HuffmanTree() {
		if(HT ) delete []HT;
		for(int i = 0 ; i < 256 ; ++ i ){
			if(HC[i] != NULL) delete HC[i];
		}
	}
	int size(){
		return this->Size ;
	}
	bool HuffmanCode();
	bool build();
	bool Read();
};
#endif
