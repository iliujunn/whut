#include "Compress.h"
#include<fstream>
#include<cstring>
#include<iostream>
using namespace std;
Compress::Compress(){
	cout<<"字典名：\n";
	dict[0] = '\0';
	strcpy(dict,"dictfile/\0");
	char tmp[256];
	scanf("%s",tmp);
	strcat(dict,tmp);
	for(int i = 0 ; i < 256 ; ++ i ){
		HC[i] = new char[1];
		HC[i][0] = '\0';
	}
	ifstream in ; 
	in.open(dict,ios::in|ios::binary);
	if(!in.is_open()){
		printf("文件打开失败");
		return ;
	}
	unsigned char ch ; 
	unsigned char num ;
	int size = 0 ; 
	char *hc ;
	
	while(!in.eof() && in.read((char *)&ch , 1)){
		in.read((char *)&num,1);
		size = num-'0';
		hc = new char[size+1];
		hc[0] = '\0';
		in.read((char *)hc,size);
		hc[size] = '\0';
		HC[(int)ch] = new char[size+1];
		HC[(int)ch][0] = '\0';
		strcat(HC[(int)ch],hc);
		if(hc != NULL ) delete hc ;
	}
	in.close();
}

Compress::~Compress(){
	for(int i = 0 ; i < 256 ; ++ i ){
		if(HC[i] != NULL) delete HC[i];
	}
}

bool Compress::encode(){

	cout<<"待压缩文件名：\n";
	memset(filename,0,sizeof filename);
	char _tmp[256];
	_tmp[0] = '\0';
	scanf("%s",filename);
	strcpy(_tmp,"sourcefile/\0");
	strcat(_tmp,filename);
//	cout<<_tmp<<endl;
	ifstream in ; 
	in.open(_tmp,ios::in|ios::binary);
	if(!in.is_open()) return false ;

	unsigned char b ; 
	
	char filename2[256];
	filename2[0] = '\0';
	strcpy(filename2,"compressfile/\0");
	strcat(filename2,filename);
	strcat(filename2,".huf\0");
	
	ofstream out ;
//	cout<<filename2<<endl;
	out.open(filename2,ios::out|ios::binary);
	if(!out.is_open()) return false ;
	unsigned char to_write ;
	int index = 0 ; 
	char tmp[9];
	int Len ; 
	int count = 0 ; 
	while(!in.eof() && in.read((char *) &b , 1)){
		int i = 0 ; 
		Len = strlen(HC[(int)b]);
		while(i != Len){
			for(;index < 8 &&  i < Len ; ++ index){
				tmp[index] = HC[(int)b][i++];
			}
			tmp[index] ='\0';
			
			if(index == 8 ) {
				to_write = String_to_Byte(tmp);
				out<<to_write;
				//cout<<(int)to_write<<endl;
			}
			index %= 8 ;
		}
	}
	if(index < 8 ) {
		count = 8 - index ; 
		to_write = String_to_Byte(tmp);
		out.write((char *)&to_write,1);
		//cout<<(int)to_write<<endl;
	}

	in.close();
	out.close(); 
	
	ifstream file1( _tmp, ios::binary | ios::ate);
	ifstream file2( filename2, ios::binary | ios::ate);
	cout<<file2.tellg()<<" "<<file1.tellg()<<endl;
	printf("压缩比率:%.2f \%\n",file2.tellg()*100.0/file1.tellg());
	
	file1.close();
	file2.close();
	ofstream o ; 

	cout<<filename2<<endl;
	strcat(filename2,".count\0");
	cout<<filename2<<endl;
	o.open(filename2,ios::out|ios::binary);
	if(!o.is_open()) return false ;
	unsigned char tb = count;
	o.write((char*)&tb, 1);
	return true ;
	
}

unsigned char Compress:: String_to_Byte(char *__String){
	unsigned char res = 0  ; 
	int len = strlen(__String);
	for(int i = 0 ; i < len ; ++ i  ){
		res <<= 1 ;
		if(__String[i] == '1'){
			res |= 1 ;
		}
	}
	for(int i = len ; i  < 8 ; ++ i ){
		res <<= 1 ;
	}
	return  res ; 
}

bool Compress::build(){
	int root ; 
	int len ; 
	int tot = 1 ; 
	for(int i = 0 ; i < 256 ; ++ i ){
		root = 1 ;		
		if(HC[i][0] != '\0'){
			len = strlen(HC[i]);
			for(int j = 0 ; j < len ; ++ j ){
				if(HC[i][j] == '0' ){
					if(HT[root].lchild == -1 ){
						++ tot ; 
						HT[root].lchild = tot ; 
						HT[tot].parent = root;
					}
					root = HT[root].lchild ;
				}else{
					if(HT[root].rchild == -1 ){
						++ tot ;
						HT[root].rchild = tot ;
						HT[tot].parent = root ;
					}
					root = HT[root].rchild ; 
				}
			}
	
			HT[root].is_leaf = true ;
			HT[root].h= (unsigned char)i ;
		}
	}
	return true ;
}

bool Compress::decode(){
	cout<<"解压文件名：\n";
	memset(filename,0,sizeof filename);
	scanf("%s",filename);
	
	char sourceFile[256];
	sourceFile[0] = '\0';
	strcpy(sourceFile,"compressfile/\0");
	strcat(sourceFile,filename);//待解压缩文件
	
	int l = strlen(filename);
	filename[l-4] = '\0' ;
	char target[256];
	target[0] = '\0';
	strcpy(target,"targetfile/\0");
	strcat(target,filename);
	
	char sourceCount[256] ; 
	sourceCount[0] = '\0';
	strcpy(sourceCount,sourceFile);
	strcat(sourceCount,".count");

	ifstream i ;

	i.open(sourceCount,ios::in|ios::binary);
	if(!i.is_open()) return false ; 
	unsigned char tb ; 
	i.read((char *)&tb,1);
	i.close();
	
	int count = tb ; 
	
	ifstream in ; 
	in.open(sourceFile,ios::in|ios::binary);
	if(!in.is_open()){
		return false ; 
	}
	
	ofstream out ;
	out.open(target,ios::out|ios::binary);
	if(!out.is_open()){
		return false ;
	}
	
	unsigned char b ; 
	int root = 1 ; 
	int e = 0 ; 
	unsigned char to_write ; 
	while(in.read((char *) &b , 1)){
		if(in.peek()==EOF){
			e = count ; 
		}
		for(int i = 7 ; i >= e ; -- i ){
			if((b>>i) & 1 ){
				root = HT[root].rchild ;
			}else{
				root = HT[root].lchild ;	
			}
			if(HT[root].is_leaf){
				to_write = HT[root].h ;
				out.write((char *)&to_write,1);
				//cout<<HT[root].h;
				root = 1 ; 
			}
		}
	}
	in.close();
	out.close();
	return true ;
}
