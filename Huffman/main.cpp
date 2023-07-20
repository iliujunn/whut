#include <iostream>
#include"HuffmanTree.h"
#include "Compress.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Print_Menu(){
	printf("1 哈夫曼编码\n");
	printf("2 解码\n");
	printf("3 压缩\n");
	printf("0 退出\n\n");
}
int main(int argc, char** argv) {
	while(true){
		Print_Menu();
		int op ; 
		cin>>op;
		switch(op){
		case 1 : {
			HuffmanTree T ;
			T.HuffmanCode();
			break ;
		}
		case 2 :{
			Compress C ;
			C.build();
			C.decode();
			break ;
		}
		case 3:{
			Compress C ;
			C.encode();
			break ;
		}
		default:
			exit(0);
		}
	}
	return 0;
}
