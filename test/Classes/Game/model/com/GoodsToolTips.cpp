#include "GoodsToolTips.h"
#include "utils/ColorUtil.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/com/vo/GoodsDynamic.h"
#include "model/com/GoodsDynamicManager.h"
#include "utils/ValuesUtil.h"

SUBGOODSTIPS GoodsToolTips::getExplain(GoodsBasic* goodBasic, bool isShopPrice, int chipNum)
{
    SUBGOODSTIPS newrnt;
	if (!goodBasic) 
		return newrnt;

	newrnt.color_goodName = ColorUtil::getGoodColor(goodBasic->quality);
	newrnt.goodName = goodBasic->goodName;
	newrnt.chipNum = chipNum;
	newrnt.chipNeedNum = clipNeedNum[goodBasic->quality];//May be the color attributes
	newrnt.hp[0] = goodBasic->hp;//May be the color attributes
	newrnt.att[0] = goodBasic->att;//May be the color attributes
	newrnt.def[0] = goodBasic->def;//May be the color attributes
	newrnt.magicAtt[0] = goodBasic->magicAtt;//May be the color attributes
	newrnt.magicDef[0] = goodBasic->magicDef;//May be the color attributes
	newrnt.needLevel = goodBasic->level;
	newrnt.needCareer = getCareerStr(goodBasic->career_id);
	newrnt.intro = goodBasic->intro;
	newrnt.shopPrice = goodBasic->price;
	newrnt.s_sell_price = goodBasic->sell_price;

	return newrnt;

}

std::string GoodsToolTips::getCareerStr(int careerIds)
{
	std::string str = "";
	if (careerIds == 0x7F){
		str = ValuesUtil::Instance()->getString("BB019");
		return str;
	}
	if (careerIds & 0x1){
		str += ValuesUtil::Instance()->getString("BB020");
	}
	if(careerIds & 0x2){
		str += ValuesUtil::Instance()->getString("BB021");
	}
	if(careerIds & 0x4){
		str += ValuesUtil::Instance()->getString("BB022");
	}
	if(careerIds & 0x8){
		str += ValuesUtil::Instance()->getString("BB023");
	}
	if(careerIds & 0x10){
		str += ValuesUtil::Instance()->getString("BB024");
	}
	if(careerIds & 0x20){
		str += ValuesUtil::Instance()->getString("BB025");
	}
	if(careerIds & 0x40){
		str += ValuesUtil::Instance()->getString("BB026");
	}
	return str;
}

/**
	* 构造物品的tooltips 
	* @param myBasic
	* @param myDynamic
	* @return 
	* 
	*/	
SUBGOODSTIPS GoodsToolTips::getGoodsTooltips(GoodsBasic* myBasic, GoodsDynamic* myDynamic, std::string* roleName)
{
    SUBGOODSTIPS newrnt;
	if (!myBasic || !myDynamic)
		return newrnt;

	newrnt.color_goodName = ColorUtil::getGoodColor(myBasic->quality);
	newrnt.equiTypeArr = equiTypeArr[myBasic->equip_type];
	newrnt.goodName = myBasic->goodName;
	newrnt.addDyn = myDynamic->e_strengthen;
	newrnt.hp[0] = myDynamic->r_hp;newrnt.hp[1] = myBasic->hp;
	newrnt.att[0] = myDynamic->j_att;newrnt.att[1] = myBasic->att;
	newrnt.def[0] = myDynamic->k_def;newrnt.def[1] = myBasic->def;
	newrnt.magicAtt[0] = myDynamic->l_magicAtt;newrnt.magicAtt[1] = myBasic->magicAtt;
	newrnt.magicDef[0] = myDynamic->m_magicDef;newrnt.magicDef[1] = myBasic->magicDef;
	newrnt.needLevel = myBasic->level;
	newrnt.needCareer = getCareerStr(myBasic->career_id);
	newrnt.quality = myBasic->quality;
	newrnt.u_stamina = myDynamic->u_stamina;
	newrnt.v_wrist = myDynamic->v_wrist;
	newrnt.w_intellect = myDynamic->w_intellect;
	newrnt.intro = myBasic->intro;
	newrnt.s_sell_price = myDynamic->s_sell_price;
	if (roleName)
		newrnt.roleName = *roleName;
	else
		newrnt.roleName = "";

	return newrnt;
}

SUBGOODSTIPS GoodsToolTips::getDefaultExplain(GoodsBasic* goodBasic,int32 id, std::string* roleName)
{
    SUBGOODSTIPS newrnt;
    
	if (!goodBasic) 
		return newrnt;
	//Doyang 20120716
	
	/*if (!newrnt)
		return 0;*/
	if (goodBasic->type == 2)
	{
		GoodsDynamic* myDynamic = g_pGoodsDynamicManager->getGoodsDynamic(id);
		if (myDynamic)
		{
			newrnt = getGoodsTooltips(goodBasic, myDynamic, roleName);
		}
		else
		{//With color_goodName and goodName instead
			
			newrnt.color_goodName = ColorUtil::getGoodColor(goodBasic->quality);
			newrnt.goodName = "资料加载中...";
		}
	}
	else
	{
		newrnt.goodName = goodBasic->goodName;
		newrnt.intro = goodBasic->intro;
	}
	return newrnt;
}