#include "ArenaConst.h"

// 根据排名获取对应图片的索引值 
int ArenaConst::getIndexByRank(int rank)
{
	int index = 1;
	if(rank==1){
		index = 12;				
	}
	else if(rank==2){
		index = 11;
	}
	else if(rank==3){
		index = 10;
	}
	else if(rank==4){
		index = 9;
	}
	else if(rank==5){
		index = 8;
	}
	else if(rank<=10){
		index = 7;
	}
	else if(rank<=25){
		index = 6;
	}
	else if(rank<=100){
		index = 5;
	}
	else if(rank<=200){
		index = 4;
	}
	else if(rank<=400){
		index = 3;
	}
	else if(rank<=600){
		index = 2;
	}
	else if(rank<=1000){
		index = 1;
	}
	return index;
}