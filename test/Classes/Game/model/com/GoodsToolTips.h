#ifndef _GOODSTOOLTIPS_H_
#define _GOODSTOOLTIPS_H_

#include "BaseType.h"


//const char* equiTypeArr[8] = {"","帽子","项链","衣服","披风","武器","戒指"};
const int32 clipNeedNum[] = {0,0,0,2,5,10,20};
const std::string equiTypeArr[8] = {"","帽子","项链","衣服","披风","武器","戒指"};

struct SUBGOODSTIPS
{
	SUBGOODSTIPS()
	{
		color_goodName = cocos2d::ccc3(255,255,255);
		chipNum = 0;
		chipNeedNum = 0;
		addDyn = 0;
		hp[0] = 0;hp[1] = 0;
		att[0] = 0;att[1] = 0;
		def[0] = 0;def[1] = 0;
		magicAtt[0] = 0;magicAtt[1] = 0;
		magicDef[0] = 0;magicDef[1] = 0;
		needLevel = 0;
		quality = 0;
		u_stamina = 0;
		v_wrist = 0;
		w_intellect = 0;
		s_sell_price = 0;

		goodName = "";
		equiTypeArr = "";
		needCareer = "";
		intro = "";
		roleName = "";
	}

	~SUBGOODSTIPS()
	{
		//s_sell_price = 0;
		//CCLog("ssssssssssssssssss");
	}

	cocos2d::ccColor3B  color_goodName;
	std::string			goodName;
	std::string			equiTypeArr;
	int32				chipNum;//Debris number may not have
	int32				chipNeedNum;//The total number of debris demand
	int32				addDyn;
	int32				hp[2];
	int32				att[2];
	int32				def[2];
	int32				magicAtt[2];
	int32				magicDef[2];
	int32				needLevel;
	std::string			needCareer;
	int32				quality;
	int32				u_stamina;
	int32				v_wrist;
	int32				w_intellect;
	std::string			intro;
	int32				shopPrice;
	int32				s_sell_price;
	std::string			roleName;
};



class GoodsBasic;
class GoodsDynamic;
class GoodsToolTips
{
public:

public:
	GoodsToolTips(){};
	~GoodsToolTips(){};

	static SUBGOODSTIPS getExplain(GoodsBasic* goodBasic, bool isShopPrice, int chipNum = 0);
	static SUBGOODSTIPS getGoodsTooltips(GoodsBasic* myBasic, GoodsDynamic* myDynamic, std::string* roleName = 0);
	static SUBGOODSTIPS getDefaultExplain(GoodsBasic* goodBasic,int32 id, std::string* roleName = 0);
	static std::string getCareerStr(int careerIds);
private:
};

#endif