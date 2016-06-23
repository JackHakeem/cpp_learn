#ifndef HLQS_ClothManage_H_
#define HLQS_ClothManage_H_

#include "utils/Singleton.h"
#include "cocos2d.h"

class ClothManage: public Singleton<ClothManage>
{
public:
	ClothManage();

public:
    enum
    {
        RES_ID_ONBUSINESS = 900,
        RES_ID_ONMEDITATION
    };
//	static const int RES_ID_ONBUSINESS;    //Run business
//	static const int RES_ID_ONMEDITATION;  //meditation
	std::string RES_PATH_ONBUSINESS;
	int clothDic[11];
	std::string getCloth(int mercId);

};

//const int ClothManage::RES_ID_ONBUSINESS = 900;
//const int ClothManage::RES_ID_ONMEDITATION = 901;
#endif