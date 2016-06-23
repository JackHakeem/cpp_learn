#include "StrengCreate.h"
#include "model/player/RoleManage.h"
#include "StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "model/newhand/NewhandManager.h"

StrengCreate::StrengCreate()
{
	i = 0;
}


bool StrengCreate::init()
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

	this->setIsTouchEnabled(true);

    return true;
}

void StrengCreate::createGood(  StrengGoodsVo* strengGoodsVo,int sitNum  )
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
		strengGoods->release();

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

void StrengCreate::removeSkinChild()
{
	for ( map<int, StrengGoods*>::iterator it = _goodsDic.begin(); it != _goodsDic.end(); it++ )
	{
		StrengGoods* child = it->second;
		child->removeFromParentAndCleanup(true);
		//child->removeAllChildrenWithCleanup(true);
		//this->removeChild( child, true );
	}
	
	_goodsDic.clear();
}

void StrengCreate::updateTip(  int id  )
{
	//StrengGoods* strengGoods = getStrengGoods( id );
	//if(strengGoods)
	//	strengGoods->updateTip();
}

StrengGoods* StrengCreate::getStrengGoods( int id )
{
	std::map<int, StrengGoods*>::iterator it = _goodsDic.find( id );
	if ( it != _goodsDic.end() )
	{
		return it->second;
	}
	
	return 0;
}

CCNode * StrengCreate::getNewHandItem( int eqSitNum )
{
	//return this->getStrengGoods(eqSitNum);
	

	//Doyang 20102727
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


void StrengCreate::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common-1, true);
}

CCRect StrengCreate::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool StrengCreate::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool StrengCreate::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ( !containsTouchLocation(touch) ) return false;

	return true;
}

void StrengCreate::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	std::map<int, StrengGoods*>::iterator it;
	for(it = _goodsDic.begin(); it != _goodsDic.end(); ++ it)
	{
		StrengGoods* pGood = it->second;

		CCPoint itemPoint = getScreenPos(pGood);
		CCSize itemSize = pGood->getContentSize();
		CCPoint locationInView = pTouch->locationInView(pTouch->view());
		CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			pGood->ccTouchEnded(pTouch, pEvent);

			NewhandManager::Instance()->touchNextEvent(121);
		}
	}
}