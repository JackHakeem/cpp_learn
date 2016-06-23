#include "model/player/ClothManage.h"

ClothManage::ClothManage()
{
	for(int i = 1; i<=10; ++i)
	{
		clothDic[i] = 900 + i;
	}
	RES_PATH_ONBUSINESS = "assets/res/900";
}

std::string ClothManage::getCloth(int mercId)
{
	char str[] = "assets/res/%d";
	char path[50] = {0};
	sprintf(path, str, clothDic[mercId]);
	return std::string(path);
}