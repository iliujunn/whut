#include "HuffmanTree.h"
#include<string.h>
#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
HuffmanTree::HuffmanTree(){
	Size = 0 ; 
	for(int i = 0 ; i < 256 ; ++ i ){
		HC[i] = new char[1];
		HC[i][0] = '\0';
	}
}
bool HuffmanTree::Read(){
	memset(weight,0,sizeof weight);

	cout<<"编码文件名\n";
	char source[256];
	source[0] = '\0';
	scanf("%s",filename);
	strcpy(source,"sourcefile/\0");
	strcat(source,filename);
	cout<<source<<endl;
	ifstream in;
	in.open(source, ios::in | ios::binary);
	if(!in.is_open())return false;
	unsigned char b = 0;
	while(in.read((char *)&b, 1))
	{
		weight[b]++;
	}
	in.close();
	return true ;
}
bool HuffmanTree::build(){
	if(Size == 0 ) Read() ;
	int index = 0 ; 
	for(int i = 0 ; i < 256 ; ++ i ){
		if(weight[i]){
			SELECT.push({(unsigned char)i,weight[i],-1,-1,-1,++index});
		}
	}
	Size = (int)SELECT.size() ; 
	int N = Size ;
	HT = new TNode[2*N+3];
	int m = 2*N -1 ; 
	for(int i = N + 1 ; i <= m ; ++ i ){
		TNode s1 = SELECT.top();SELECT.pop();
		TNode s2 = SELECT.top();SELECT.pop();
		s1.parent = s2.parent = i ;
		HT[i].weight = s1.weight+s2.weight;
		HT[i].lchild = s1.index , HT[i].rchild = s2.index ; 
		HT[i].index = i ; 
		HT[s1.index] = s1 , HT[s2.index] = s2 ;
		SELECT.push(HT[i]);
	}
	return true ;
}

bool HuffmanTree::HuffmanCode(){
	if(Size == 0 ) build();
	int root = 2*Size - 1 ;
	char *hc; 
	int tot = 0 ; 
	
	for(int i = 1 ; i <= Size ; ++ i ){
		tot = 0 ; 
		hc = new char[1000];
		int R = i,r = i ; 
		int j = (int)HT[i].h ;
		while(R != root){
			r = R ;
			R = HT[r].parent ; 
			if(HT[R].lchild == r ) hc[tot++] = '0' ;
			else if(HT[R].rchild == r ) hc[tot++] = '1';
			else return false ; 
			
		}
		hc[tot]='\0';
		int L = strlen(hc);
		if(L > 0 ) {
			//翻转
			for(int k = 0 ; k <= (tot-1)/2 ; ++ k ){
				swap(hc[k],hc[tot-k-1]);
			}

			HC[j] = new char[tot+1];
			HC[j][0] = '\0';
			
			strcat(HC[j],hc);		
			delete []hc;
		}else{
			HC[j] = new char[1];
			HC[j][0] ='\0';
		}	
	}
	char filename2[256];
	filename2[0] = '\0';
	strcpy(filename2,"dictfile/\0");
	strcat(filename2,filename);
	strcat(filename2,".dict\0");
	cout<<filename2<<endl;
	ofstream out ; 
	out.open(filename2,ios::out|ios::binary);
	if(!out.is_open()) return  false ;
	for(int i=0;i<256;i++){
		if(HC[i][0] != '\0'){
			out<<(unsigned char)i<<strlen(HC[i])<<HC[i];
		}
	}
	return true ; 
}
