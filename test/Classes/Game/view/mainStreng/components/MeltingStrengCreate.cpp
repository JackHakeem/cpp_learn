#include "MeltingStrengCreate.h"
#include "model/player/RoleManage.h"
#include "StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"

MeltingStrengCreate::MeltingStrengCreate()
{
	i = 0;
}


bool MeltingStrengCreate::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCUIBackground* bgEquip = new CCUIBackground();
	bgEquip->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(0, 0), ccp(0,0), CCSizeMake(STRENG_CREATE_W, STRENG_CREATE_H) );
	this->addChild( bgEquip );
	bgEquip->release();

	return true;
}

void MeltingStrengCreate::createGood(  StrengGoodsVo* strengGoodsVo,int sitNum  )
{
	if ( !strengGoodsVo )
	{
		return;
	}
	int index(0);
	GoodsInfo* pGoodsInfo = strengGoodsVo->StrengGoodsInfo;

	//Doyang 20120718
	if(!pGoodsInfo)
		return;

	if ( pGoodsInfo )
	{
		index = strengGoodsVo->StrengGoodsInfo->id;
	}

	std::map<int, StrengGoods*>::iterator it = _goodsDic.find( index );
	if ( it == _goodsDic.end() )
	{
		CCRect rect( POSX(15 + (sitNum%2)*250), POSX(285 - (sitNum/2)*135), POSX(245), POSX(120) );

		StrengGoods* strengGoods = StrengGoods::StrengGoodsWithRect( rect );
		strengGoods->initStrengGoodsVo( strengGoodsVo, sitNum );
		addChild( strengGoods ); 

		_goodsDic.insert( make_pair(index, strengGoods) );
		++index;
	}

	struct sdata
	{
		int UseType;
		StrengGoodsVo* sdataStrengGoodsVo;
	};
	sdata s;
	// reget dynamic 
	if( pGoodsInfo->id != 0 )
	{
		s.UseType = 1;	// {UseType:1/* 1 get dynamic info*/
		s.sdataStrengGoodsVo = strengGoodsVo;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
	}

	if(i==0)
	{
		s.UseType = 6;	// {UseType:6/* 6 click get info */
		s.sdataStrengGoodsVo = strengGoodsVo;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
	}

	i++;
}

void MeltingStrengCreate::removeSkinChild()
{
	for ( map<int, StrengGoods*>::iterator it = _goodsDic.begin(); it != _goodsDic.end(); it++ )
	{
		StrengGoods* child = it->second;
		child->removeAllChildrenWithCleanup(true);
		this->removeChild( child, true );
	}

	_goodsDic.clear();
}

void MeltingStrengCreate::updateTip(  int id  )
{
	//StrengGoods* strengGoods = getStrengGoods( id );
	//if(strengGoods)
	//	strengGoods->updateTip();
}

StrengGoods* MeltingStrengCreate::getStrengGoods( int id )
{
	std::map<int, StrengGoods*>::iterator it = _goodsDic.find( id );
	if ( it != _goodsDic.end() )
	{
		return it->second;
	}

	return 0;
}

CCNode * MeltingStrengCreate::getNewHandItem( int eqSitNum )
{
	std::map<int, StrengGoods*>::iterator it;
	for(it = _goodsDic.begin(); it != _goodsDic.end(); ++ it)
	{
		if(it->second && 
			it->second->_equpInfo &&
			it->second->_equpInfo->sitGrid == eqSitNum)
		{
			return it->second;
		}
	}
	return NULL;
}

MeltingStrengCreate::~MeltingStrengCreate()
{

}
