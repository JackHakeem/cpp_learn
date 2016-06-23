#include "BankCreate.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "BankGoods.h"

BankCreate* g_pBankCreate = 0;

BankCreate::BankCreate(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	_goodsDic = new cocos2d::CCMutableArray<cocos2d::CCObject *>(BANKMAXGRID);

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
}

BankCreate* BankCreate::bankScrollViewWithCCRect(const CCRect& mRect)
{
    BankCreate *pScrollView = new BankCreate(mRect);
    if(pScrollView && pScrollView->init()){
		 pScrollView->setIsTouchEnabled(false);//That may not be the touch
        //pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}

BankCreate::~BankCreate()
{
	if (_goodsDic)
		_goodsDic->release();
}

void BankCreate::creatGood(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum)
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
void BankCreate::reBuildGoods(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum)
{
	BankGoods* bankGoods;
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
		CCLayer* layer = getLayerByTag(sitNum/BANK_ITEM_COUNT_PER_PAGE);//0KK
		
		if (layer)
		{
			
			bankGoods = (BankGoods*)layer->getChildByTag(sitNum);
			if (!bankGoods)
			{
				//If not the new construction
				bankGoods = new BankGoods();
				layer->addChild(bankGoods, 1, sitNum);//tag is sitnum
                bankGoods->release();
			}

			//Insert containers
			if (bankGoods->initBankGoods(tmp, sitNum%BANK_ITEM_COUNT_PER_PAGE, sitNum/BANK_ITEM_COUNT_PER_PAGE) && _goodsDic)
				_goodsDic->addObject(bankGoods);
		}
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist"); 
	
	for (int i = goodsNum; i < BANKMAXGRID; i++)
	{
		//Join
		//int page = i/BANK_ITEM_COUNT_PER_PAGE;
		CCLayer* layer = getLayerByTag(i/BANK_ITEM_COUNT_PER_PAGE);//0KK
		if (layer)
		{
			bankGoods = (BankGoods*)layer->getChildByTag(i);
			if (!bankGoods)
			{
				//If not the new construction
				bankGoods = new BankGoods();
				//bagGoods->init();
				layer->addChild(bankGoods, 1, i);//tag is sitnum
                bankGoods->release();
			}

			//Insert containers
			if (bankGoods->initBankGoods(0, i%BANK_ITEM_COUNT_PER_PAGE, i/BANK_ITEM_COUNT_PER_PAGE, true) && _goodsDic)
				_goodsDic->addObject(bankGoods);
		}
	}
}


void BankCreate::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 10, true);
}

BankGoods* BankCreate::getCurSelectedBankGoods(CCPoint curTouchPoint)//通过坐标
{
	CCMutableArray<cocos2d::CCObject *>::CCMutableArrayIterator it;

	for( it = _goodsDic->begin(); it != _goodsDic->end(); it++) 
	{
		BankGoods* bankGoods = 0;
		bankGoods = (BankGoods*)(*it);//dynamic_cast<CCStringToStringDictionary*>(*it);
		

		if(!bankGoods)
			break;

		if (bankGoods->m_page != currentScreen-1)
			continue;

		//计算点击碰撞
		CCRect bagGoodsRect = CCRectZero;
		bagGoodsRect.origin = ccpAdd(bankGoods->getPosition(), ccp(-bankGoods->getContentSize().width/2, -bankGoods->getContentSize().height/2));
		bagGoodsRect.size = bankGoods->getContentSize();

        bool sus = CCRect::CCRectContainsPoint(bagGoodsRect, curTouchPoint);
		if (sus)
		{//碰撞成功
			return bankGoods;
		}
	}

	return 0;
}
/*
bool BankCreate::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
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
	*  更新物品 
	* @param arr
	* @return 
	* 
	*/		
void BankCreate::updateGoods(char* arr)
{
	if (!arr) 
		return;
	std::list<GoodsInfo*>* tmparr = (std::list<GoodsInfo*>*)arr;
	std::list<GoodsInfo*>::iterator it;
	for (it = tmparr->begin(); it != tmparr->end(); it++)
	{
		GoodsInfo* info = *it;
		if (!info) continue;
		BankGoods* bankGoods = getBankGoods(info->sitGrid);
		if (bankGoods->isHasCopy)
		{
			//bagGoods.dispose();用全局删除
		}
		bankGoods->removeAllChildrenWithCleanup(true);//删除

		//插入容器
		bankGoods->initBankGoods(info, info->sitGrid%BANK_ITEM_COUNT_PER_PAGE, info->sitGrid/BANK_ITEM_COUNT_PER_PAGE);
	}
	/*
	for each(var info:GoodsInfo in arr){
		var bagGoods:BankGoods = getBankGoods(info.sitGrid);
		if(bagGoods.isHasCopy)
		{
			bagGoods.dispose();
		}
		this.removeChild(bagGoods);
		var sitNum:int = info.sitGrid;	//物品位置			
		bagGoods = new BankGoods(info, sitNum,0,false);
		addChild(bagGoods);				
		_goodsDic[sitNum] = bagGoods;
	}
	*/
}

BankGoods* BankCreate::getBankGoods(int32 index)
{
	CCMutableArray<cocos2d::CCObject *>::CCMutableArrayIterator it;

	for( it = _goodsDic->begin(); it != _goodsDic->end(); it++) 
	{
		BankGoods* bankGoods = 0;
		bankGoods = (BankGoods*)(*it);
		if (!bankGoods)
			continue;

		if (bankGoods->getTag() == index)
			return bankGoods;

	}
	return 0;
}

/**
	*  多个进行设置高亮
	* @param sitNum
	* @param capacity
	* @param value
	* 
	*/	
void BankCreate::setHeightLine(uint32 sitNum, bool value)
{
	for (int i = 0; i <= sitNum; i++)
	{
		BankGoods* bankGoods = getBankGoods(i);	
		if (bankGoods && bankGoods->_lock)
		{
			SpriteNode* oldnode = (SpriteNode*)bankGoods->getChildByTag(9);
			if (oldnode)
				bankGoods->removeChild(oldnode, true);

			if (value)
			{
				CCPoint tarpos = bankGoods->getPosition();
				SpriteNode* pSelect = new SpriteNode();
				pSelect->initWithSpriteFrameName("pack/select.png");
				bankGoods->addChild(pSelect, 20 ,9);
				pSelect->release();
				pSelect->setPosition(ccp(0,0));			
			}
		}
	}
}