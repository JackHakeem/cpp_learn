#include "BagCreate.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "BagGoods.h"

BagCreate* g_pBagCreate = 0;

BagCreate::BagCreate(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	_goodsDic = new cocos2d::CCMutableArray<cocos2d::CCObject *>(BAGMAXGRID);
}

BagCreate* BagCreate::bagScrollViewWithCCRect(const CCRect& mRect)
{
    BagCreate *pScrollView = new BagCreate(mRect);
    if(pScrollView && pScrollView->init()){
		 pScrollView->setIsTouchEnabled(false);//That may not be the touch
        //pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}

BagCreate::~BagCreate()
{
	if (_goodsDic)
		_goodsDic->release();
}

void BagCreate::creatGood(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum)
{//m_pChildren->count()
	/*
	if (m_pChildren && m_pChildren > 0)
	{
		int32 size = m_pChildren->count();
		for (int i=0; i < size; i++)
		{
			
		}
		this->removeAllChildrenWithCleanup(true);
	}
	*/
	//OverPanelManage.getInstance().setSprite(this.parent);
	//OverPanelManage.getInstance().setMousechild(true);
	reBuildGoods(goodDic, goodsNum);
}

/**
* Reconstruct items
* @param goodDic
* @param goodsNum
* 
*/		
void BagCreate::reBuildGoods(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum)
{
	BagGoods* bagGoods;
	std::map<int32, GoodsInfo*>::iterator it;

	_goodsDic->removeAllObjects();
	for (int i = 0; i < 10; i++)
	{
		CCLayer* layer = getLayerByTag(i);//0KK
		if (layer)
			layer->removeAllChildrenWithCleanup(true);
	}

	for (it = goodDic.begin(); it != goodDic.end(); it++)
	{
		GoodsInfo* tmp = it->second;
		if (tmp == 0)
			continue;

		int32 sitNum = tmp->sitGrid;
		
		//join
		CCLayer* layer = getLayerByTag(sitNum/BACKPACK_ITEM_COUNT_PER_PAGE);//0KK
		if (layer)
		{
			bagGoods = (BagGoods*)layer->getChildByTag(sitNum);
			if (!bagGoods)
			{
				//If not the new construction
				bagGoods = new BagGoods();
				layer->addChild(bagGoods, 1, sitNum);//tag is sitnum
                bagGoods->release();
			}

			//Insert containers
			if (bagGoods->initBagGoods(tmp, sitNum%BACKPACK_ITEM_COUNT_PER_PAGE, sitNum/BACKPACK_ITEM_COUNT_PER_PAGE) && _goodsDic)
				_goodsDic->addObject(bagGoods);
		}
	}

	for (int i = goodsNum; i < BAGMAXGRID; i++)
	{
		//join
		//int page = i/BACKPACK_ITEM_COUNT_PER_PAGE;
		CCLayer* layer = getLayerByTag(i/BACKPACK_ITEM_COUNT_PER_PAGE);//0KK
		if (layer)
		{
			bagGoods = (BagGoods*)layer->getChildByTag(i);
			if (!bagGoods)
			{
				//If not the new construction
				bagGoods = new BagGoods();
				//bagGoods->init();
				layer->addChild(bagGoods, 1, i);//tag是sitnum
                bagGoods->release();
			}

			//Insert containers
			if (bagGoods->initBagGoods(0, i%BACKPACK_ITEM_COUNT_PER_PAGE, i/BACKPACK_ITEM_COUNT_PER_PAGE, true) && _goodsDic)
				_goodsDic->addObject(bagGoods);
		}
	}
	
}


void BagCreate::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 10, true);
}

BagGoods* BagCreate::getCurSelectedBagGoods(CCPoint curTouchPoint)//Through the coordinates
{
	CCMutableArray<cocos2d::CCObject *>::CCMutableArrayIterator it;

	for( it = _goodsDic->begin(); it != _goodsDic->end(); it++) 
	{
		BagGoods* bagGoods = 0;
		bagGoods = (BagGoods*)(*it);//dynamic_cast<CCStringToStringDictionary*>(*it);
		

		if(!bagGoods)
			break;

		if (bagGoods->m_page != currentScreen-1)
			continue;

		//Calculation click collision
		CCRect bagGoodsRect = CCRectZero;
		bagGoodsRect.origin = ccpAdd(bagGoods->getPosition(), ccp(-bagGoods->getContentSize().width/2, -bagGoods->getContentSize().height/2));
		bagGoodsRect.size = bagGoods->getContentSize();

        bool sus = CCRect::CCRectContainsPoint(bagGoodsRect, curTouchPoint);
		if (sus)
		{//Collision success
			return bagGoods;
		}
	}

	return 0;
}
/*
bool BagCreate::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{    
	return true;
	if (currentScreen == 0 || totalScreens == 0)
		return false;//没任何页

    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);


    if (this->getIsTouchInContentLayer(pTouch)) {
        isScrolling = true;
		startSwipe = preTouchPoint.x;
        printf("Began Scrolling\n");
    }
    else 
	{
        isScrolling = false;
		startSwipe = 0;
	}
    return isScrolling;
}
*/

/**
	*   Update items
	* @param arr
	* @return 
	* 
	*/		
void BagCreate::updateGoods(char* arr)
{
	if (!arr) 
		return;
	std::list<GoodsInfo*>* tmparr = (std::list<GoodsInfo*>*)arr;
	std::list<GoodsInfo*>::iterator it;
	for (it = tmparr->begin(); it != tmparr->end(); it++)
	{
		GoodsInfo* info = *it;
		if (!info) continue;
		BagGoods* bagGoods = getBagGoods(info->sitGrid);
		if (bagGoods->isHasCopy)
		{
			//bagGoods.dispose();With global delete
		}
		bagGoods->removeAllChildrenWithCleanup(true);//delete

		//Insert containers
		bagGoods->initBagGoods(info, info->sitGrid%BACKPACK_ITEM_COUNT_PER_PAGE, info->sitGrid/BACKPACK_ITEM_COUNT_PER_PAGE);
	}
	/*
	for each(var info:GoodsInfo in arr){
		var bagGoods:BagGoods = getBagGoods(info.sitGrid);
		if(bagGoods.isHasCopy)
		{
			bagGoods.dispose();
		}
		this.removeChild(bagGoods);
		var sitNum:int = info.sitGrid;	//		Where things are	
		bagGoods = new BagGoods(info, sitNum,0,false);
		addChild(bagGoods);				
		_goodsDic[sitNum] = bagGoods;
	}
	*/
}

BagGoods* BagCreate::getBagGoods(int32 index)
{
	CCMutableArray<cocos2d::CCObject *>::CCMutableArrayIterator it;

	for( it = _goodsDic->begin(); it != _goodsDic->end(); it++) 
	{
		BagGoods* bagGoods = 0;
		bagGoods = (BagGoods*)(*it);
		if (!bagGoods)
			continue;

		if (bagGoods->getTag() == index)
			return bagGoods;

	}
	return 0;
}

/**
	*  ????????
	* @param sitNum
	* @param capacity
	* @param value
	* 
	*/	
void BagCreate::setHeightLine(uint32 sitNum, bool value)
{
	for (int i = 0; i <= sitNum; i++)
	{
		BagGoods* bagGoods = getBagGoods(i);	
		if (bagGoods && bagGoods->_lock)
		{
			SpriteNode* oldnode = (SpriteNode*)bagGoods->getChildByTag(9);
			if (oldnode)
				bagGoods->removeChild(oldnode, true);

			if (value)
			{
				CCPoint tarpos = bagGoods->getPosition();
				SpriteNode* pSelect = new SpriteNode();
				pSelect->initWithSpriteFrameName("pack/select.png");
				bagGoods->addChild(pSelect, 20 ,9);
				pSelect->release();
				pSelect->setPosition(ccp(0,0));			
			}
		}
	}
}