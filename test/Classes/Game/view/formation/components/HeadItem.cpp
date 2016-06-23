#include "HeadItem.h"

 
const float SCALE = 1.4f;// / CCDirector::sharedDirector()->getContentScaleFactor();

HeadItem::HeadItem( uint32  sitGrid , PlayerInfoVo info, float scale ): _mySitNum(0), _figureId(0), _clickNum(0),isHasCopy(false), isMove(false)
{
	this->_mySitNum=sitGrid;
	this->_figureId=info.playerBaseInfo.id;
	 
	this->initHeadInfo(info.playerBaseInfo, info.figureBaseInfo, scale);

 
}

       /**
		 *Increase the head, tip information
		 * @param playerBase
		 * @param figureBase
		 * 
		 */	

void HeadItem::initHeadInfo( PlayerBaseVo playerBase , FigureBaseVo figureBase, float scale )
{
	//char *pIconPath = new char[20];
	char pIconPath[32]; // LH0713
	sprintf(pIconPath, "assets/icon/head/%d.png", playerBase.cloth);
	if (this->initWithFile(pIconPath))
	{
		CCSprite *pLeftGrid = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
		_pLeftGridSize = pLeftGrid->getContentSize();
		CC_SAFE_DELETE(pLeftGrid);
		this->setScale(_pLeftGridSize.width / this->getContentSize().width);
		this->setAnchorPoint(CCPointZero);
		this->setPosition(ccp(4, 4));
	}
	//int lev=playerBase-> GetLevelId();
	//
}



        /**
		*Set for state
		* @ param set true: battle; False: rest
		 * 
		 */		
		 
void HeadItem::setPlayIcon( bool set )
{
	if(set){
		 this->setOpacity(110);
	}else{
		 this->setOpacity(255);
	}
}

