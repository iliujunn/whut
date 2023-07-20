#ifndef COMPRESS_H
#define COMPRESS_H
struct Node{
	unsigned char h ; 
	int parent ;
	int lchild,rchild;
	bool is_leaf ;
	Node(){
		parent = lchild = rchild = -1 ;
		is_leaf = false ; 
	}
};
class Compress {
public:
	char *HC[256] ;
	char dict[256];
	char filename[256] ;
	Node HT[512] ;
public:
	Compress();
	~Compress();
	bool encode();
	unsigned char String_to_Byte(char *__String);
	bool build();
	bool decode();
};
#endif
