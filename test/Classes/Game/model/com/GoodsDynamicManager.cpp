#include "GoodsDynamicManager.h"

#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/com/vo/GoodsDynamic.h"
#include "model/backpack/GoodsManager.h"
#include "../streng/vo/StrengVo.h"
#include "../streng/StrengManage.h"

GoodsDynamicManager* g_pGoodsDynamicManager = 0;

GoodsDynamicManager::GoodsDynamicManager()
{

}

GoodsDynamicManager::~GoodsDynamicManager()
{
	std::map<int32, GoodsDynamic*>::iterator it;
	for ( it = _goodsDynamic.begin(); it != _goodsDynamic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_goodsDynamic.clear();
}

/**
	*构建物品完整的动态信息 
	* @param goodInfo 包含strengthen、stamina、wrist、intellect信息，有多少就填多少，没有为0
	* @param goodsBasic 可有可无
	* @return GoodsDynamic
	* 
	*/	
GoodsDynamic* GoodsDynamicManager::createDynamic(GoodsInfo* goodInfo, GoodsBasic* goodsBasic)
{
	if (!goodsBasic)
	{
		goodsBasic = g_pGoodsManager->getBasicGood(goodInfo->goodId);
	}

	GoodsDynamic* myDynamic = 0;
	std::map<int32, GoodsDynamic*>::iterator it;
	if (  (it =_goodsDynamic.find( goodInfo->id )) != _goodsDynamic.end()  )
		myDynamic = it->second;

	if ( !myDynamic )
	{
		myDynamic  = new GoodsDynamic();
	}

	//calculation
	myDynamic->a_id = goodInfo->id;
	myDynamic->b_goodID = goodInfo->goodId;
	myDynamic->c_sit = goodInfo->sitGrid;
	myDynamic->d_number = goodInfo->number;
	myDynamic->e_strengthen = goodInfo->strengthen;
	myDynamic->f_holds = 0;
	myDynamic->h_hold2 = 0;
	myDynamic->i_hold3 = 0;
	StrengVo strengVo;
	StrengManage::Instance()->getGoodsStrengInfo( goodInfo->goodId, goodInfo->strengthen, &strengVo );
	myDynamic->j_att = strengVo.att;
	myDynamic->l_magicAtt = strengVo.magicAtt;
	myDynamic->k_def = strengVo.def;
	myDynamic->m_magicDef = strengVo.magicDef;
	myDynamic->r_hp = strengVo.hp;
	myDynamic->n_hit = goodsBasic->hit;
	myDynamic->o_dodge = goodsBasic->dodge;
	myDynamic->p_crit = goodsBasic->crit;
	myDynamic->q_back = goodsBasic->back;
	myDynamic->s_sell_price = goodsBasic->sell_price;
	myDynamic->t_propety = 0;
	myDynamic->u_stamina = goodInfo->stamina;
	myDynamic->v_wrist = goodInfo->wrist;
	myDynamic->w_intellect = goodInfo->intellect;
	if (goodInfo->id != 0)
	{
		addDynamic(myDynamic);
	}
	return myDynamic;
}

/**
	* 给物品添加动态属性 
	* @param params 物品信息
	* @param location 物品所在位置
	*/
void GoodsDynamicManager::addDynamic(GoodsDynamic* params, bool disEvent)
{
	/*
		_goodsDynamic[params.a_id] = params;
	if(disEvent){
		var goodsBasic:GoodsBasic = GoodsManager.getInstance().getBasicGood(params.b_goodID); 
		var str:String = GoodsToolTips.getExplain(goodsBasic);
		this.dispatchEvent(new ParamEvent(CHANGE_GOODS_DYNAMIC,{id:params.a_id,goodId:params.b_goodID,tips:str}));
	}
	*/
	std::map<int32, GoodsDynamic*>::iterator it;
	if (  (it =_goodsDynamic.find( params->a_id )) == _goodsDynamic.end()  )
	{
		_goodsDynamic.insert( make_pair( params->a_id , params ) );
	}
}

GoodsDynamic* GoodsDynamicManager::getGoodsDynamic(int32 id)
{
	std::map<int32, GoodsDynamic*>::iterator it;
	if ((it =_goodsDynamic.find(id)) != _goodsDynamic.end())
	{
		return it->second;
	}
	return 0;
} 
