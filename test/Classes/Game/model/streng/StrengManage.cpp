#include "StrengManage.h"
#include "vo/StrengVo.h"
#include "../backpack/vo/GoodsBasic.h"
#include "../backpack/GoodsManager.h"
#include <assert.h>
#include "../backpack/vo/GoodsInfo.h"
#include "vo/StrengGoodsVo.h"

StrengManage::StrengManage()
{

}

StrengManage::~StrengManage()
{
	std::map<int, StrengGoodsVo*>::iterator it1;
	for ( it1 = _goodsStreng.begin(); it1 != _goodsStreng.end(); it1++ )
	{
		CC_SAFE_DELETE( it1->second );
	}

	std::map<std::string, StrengRise*>::iterator it2;
	for ( it2 = _goodsStrengRise.begin(); it2 != _goodsStrengRise.end(); it2++ )
	{
		CC_SAFE_DELETE( it2->second );
	}

	//std::map<std::string, StrengVo*>::iterator it3 = m_strengVoMap.begin();
	//while ( it3++ != m_strengVoMap.end() )
	//{
	//	CC_SAFE_DELETE( it3->second );
	//}
}

void StrengManage::createStrengRise( StrengRise* info )
{
	if ( !info )
	{
		return; 
	}
	char str[10];
	sprintf( str, "%d_%d_%d", info->gradeLevel, info->equipPos, info->smallType );
	if ( _goodsStrengRise.find( str ) != _goodsStrengRise.end() )
	{
		cocos2d::CCLog( "strengrise.xml appears same config! equipos_lev_type:%s", str );
		return; 
	}
	_goodsStrengRise.insert( make_pair( str, info ) );
}

StrengVo* StrengManage::getGoodsStrengInfo( int id,int levle,StrengVo* streng /*= 0*/ )
{
	GoodsBasic* goodsBasic =  g_pGoodsManager->getBasicGood( id );
	char key[10];
	sprintf( key, "%d_%d_%d", goodsBasic->quality, goodsBasic->equip_type, goodsBasic->item_type );
	//std::map<std::string, StrengVo*>::iterator it = m_strengVoMap.find( key );
	//if ( it != m_strengVoMap.end() )
	//{
	//	StrengVo* streng = it->second;
	//	return streng;
	//}
	//else
	//{
		std::map<std::string, StrengRise*>::iterator itRise = _goodsStrengRise.find( std::string(key) );
		if ( itRise == _goodsStrengRise.end() )
		{
			if(goodsBasic->hp > 0) streng->hp = goodsBasic->hp + goodsBasic->growUp * levle;
			if(goodsBasic->att > 0) streng->att = goodsBasic->att + goodsBasic->growUp * levle;
			if(goodsBasic->def > 0) streng->def = goodsBasic->def + goodsBasic->growUp * levle;
			if(goodsBasic->magicAtt > 0) streng->magicAtt =goodsBasic->magicAtt + goodsBasic->growUp * levle;
			if(goodsBasic->magicDef) streng->magicDef = goodsBasic->magicDef + goodsBasic->growUp * levle;
		}
		else
		{
			StrengRise* strengRise = itRise->second;
			if(goodsBasic->hp > 0) streng->hp = goodsBasic->hp + strengRise->phygrowUp * levle;
			if(goodsBasic->att > 0) streng->att = goodsBasic->att + strengRise->phygrowUp * levle;
			if(goodsBasic->def > 0) streng->def = goodsBasic->def + strengRise->phygrowUp * levle;

			if(goodsBasic->magicAtt > 0) streng->magicAtt =goodsBasic->magicAtt + strengRise->maggrowUp * levle;
			if(goodsBasic->magicDef) streng->magicDef = goodsBasic->magicDef + strengRise->maggrowUp * levle;
		}
		return streng;
	//}
}

/** Expenses required to strengthen
* id = item Numbers
* levle = the current strengthening level
* */
int StrengManage::getGoodsUpStrengprice(int id,int levle)
{
	GoodsBasic* goodsBasic =  g_pGoodsManager->getBasicGood(id);
	char key[10];
	sprintf( key, "%d_%d_%d", goodsBasic->quality, goodsBasic->equip_type, goodsBasic->item_type );

	std::map<std::string, StrengRise*>::iterator itRise = _goodsStrengRise.find( key );
	if ( itRise != _goodsStrengRise.end() )
	{
		StrengRise* strengRise = itRise->second;
		return _initialcosts + (levle*10)+levle *(levle + 1) * strengRise->growUp;
	}
	else
	{
		return _initialcosts + (levle*10)+levle *(levle + 1) * goodsBasic->growUp;
	}
}

int StrengManage::getGoodsUpStrengpriceToLv( int id, int level )
{
	GoodsBasic* goodsBasic =  g_pGoodsManager->getBasicGood(id);
	char key[10];
	sprintf( key, "%d_%d_%d", goodsBasic->quality, goodsBasic->equip_type, goodsBasic->item_type );

	std::map<std::string, StrengRise*>::iterator itRise = _goodsStrengRise.find( key );

	if ( itRise != _goodsStrengRise.end() )
	{
		StrengRise* strengRise = itRise->second;
		//return _initialcosts + (level*10)+levle *(levle + 1) * strengRise->growUp;

		int EQUIPMENT_BASIC_STRENGTHEN_FEE			= 100;  // 强化初始费用
		int STREN_LEVEL_RADIX						= 10;	// 级别
		float EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC = 0.7;
		int n = level;
		int price = (EQUIPMENT_BASIC_STRENGTHEN_FEE+(n-1)*STREN_LEVEL_RADIX/2
			+(n-1)*(n+1)*strengRise->growUp/3)*n*EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC;

		return price;
	}
	else
	{
		int EQUIPMENT_BASIC_STRENGTHEN_FEE			= 100;  // 强化初始费用
		int STREN_LEVEL_RADIX						= 10;	// 级别
		float EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC = 0.7;
		int n = level;
		int price = (EQUIPMENT_BASIC_STRENGTHEN_FEE+(n-1)*STREN_LEVEL_RADIX/2
			+(n-1)*(n+1)*goodsBasic->growUp/3)*n*EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC;

		return price;
	}
	//price = Math.ceil((EQUIPMENT_BASIC_STRENGTHEN_FEE
	//	+(n-1)*STREN_LEVEL_RADIX/2+(n-1)*(n+1)*cfg_Growup/3)*n*EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC);//+pGoodsBasic;
}

/**Strengthening the return game relegation currency
* id = item Numbers
* levle = the current strengthening level
* */
int StrengManage::getGoodDownStrengprice(int id,int levle)
{
	GoodsBasic* goodsBasic =  g_pGoodsManager->getBasicGood(id);
	return (_initialcosts + (levle*10) + levle *(levle -1) * goodsBasic->growUp) * 0.5;
}

StrengGoodsVo* StrengManage::returnStrengGoodsVo( GoodsInfo* goodsInfo, int sitGrid, int roleID, int type /*=1*/ )
{
	GoodsBasic* goodsBasic =  g_pGoodsManager->getBasicGood( goodsInfo->goodId );
	if ( !goodsBasic )
	{
		return 0;
	}

	StrengGoodsVo* strengGoods = new StrengGoodsVo();
	strengGoods->type = type;
	strengGoods->sitGrid = sitGrid;
	strengGoods->roleId = roleID;
	strengGoods->StrengGoodsInfo = goodsInfo;
	strengGoods->level = goodsBasic->level;
	strengGoods->quality = goodsBasic->quality;
	return strengGoods;
}
		
StrengGoodsVo* StrengManage::getStrengGoods( int id )
{
	std::map<int, StrengGoodsVo*>::iterator it = _goodsStreng.find( id );
	if ( it++ != _goodsStreng.end() )
	{
		return it->second;
	}
	return 0;
}