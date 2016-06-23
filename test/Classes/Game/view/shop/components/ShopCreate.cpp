#include "ShopCreate.h"
#include "ShopGoods.h"

USING_NS_CC;

ShopCreate* g_pShopCreate = 0;

ShopCreate::ShopCreate(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	_goodsDic = new cocos2d::CCMutableArray<cocos2d::CCObject *>(SHOP_ITEM_COUNT_PER_PAGE*10);
	pagecount = 0;
}

ShopCreate::~ShopCreate()
{
	if (_goodsDic)
		_goodsDic->release();
}

ShopCreate* ShopCreate::shopScrollViewWithCCRect(const CCRect& mRect)
{
    ShopCreate *pScrollView = new ShopCreate(mRect);
    if(pScrollView && pScrollView->init()){
		 pScrollView->setIsTouchEnabled(false);//That may not be the touch
        //pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}

void ShopCreate::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 10, true);
}

/**
* 
* Loading items
* @ param goods
* @ param page page 1 begin
*/		
void ShopCreate::createGood(std::vector<ShopGoodsVo>* goods, int32 page, int32 pagesize)
{
	/*
	while (this.numChildren > 0)
	{
		if((getChildAt(0) as ShopGoods).isHasCopy)
		{
			(getChildAt(0) as ShopGoods).dispose();
		}
		this.removeChildAt(0);
	}
	OverPanelManage.getInstance().setSprite(this.parent);
	OverPanelManage.getInstance().setMousechild(true);
	*/
	if (!goods)
		return;

	reBuildGoods(goods,page,pagesize);
}

void ShopCreate::reBuildGoods(std::vector<ShopGoodsVo>* goods, int32 page, int32 pagesize)
{
	//int32 totalsize = goods->size();
	int32 sitNum = 0;
	std::vector<ShopGoodsVo>::iterator it;

	_goodsDic->removeAllObjects();

	for (int i = 0; i < 10; i++)
	{
		CCLayer* layer = getLayerByTag(i);//0KK
		if (layer)
			layer->removeAllChildrenWithCleanup(true);
	}



	for (it = goods->begin(); it != goods->end(); it++)
	{
		//Join
		CCLayer* layer = getLayerByTag(sitNum/SHOP_ITEM_COUNT_PER_PAGE);//0KK
		if (!layer)
		{
			addLayerByTag(sitNum/SHOP_ITEM_COUNT_PER_PAGE);
			layer = getLayerByTag(sitNum/SHOP_ITEM_COUNT_PER_PAGE);//0KK
			if (!layer)
			{
				CCLog("error ShopCreate::reBuildGoods");
			}
		}

		ShopGoodsVo n = *it;

		ShopGoods* shopGoods = new ShopGoods();
		shopGoods->initWithParam(&n, sitNum%SHOP_ITEM_COUNT_PER_PAGE, sitNum/SHOP_ITEM_COUNT_PER_PAGE);
		if (!shopGoods)
		{
			CCLog("error ShopCreate::reBuildGoods");
		}

		layer->addChild(shopGoods, 1, sitNum);
        shopGoods->release();
		//插入容器
		if (_goodsDic)
			_goodsDic->addObject(shopGoods);

		sitNum++;
	}

	pagecount = sitNum/SHOP_ITEM_COUNT_PER_PAGE;
}

ShopGoods* ShopCreate::getCurSelectedShopGoods(CCPoint curTouchPoint)//通过坐标
{
	CCMutableArray<cocos2d::CCObject *>::CCMutableArrayIterator it;

	for( it = _goodsDic->begin(); it != _goodsDic->end(); it++) 
	{
		ShopGoods* shopGoods = 0;
		shopGoods = (ShopGoods*)(*it);//dynamic_cast<CCStringToStringDictionary*>(*it);
		

		if(!shopGoods)
			break;

		if (shopGoods->m_page != currentScreen-1)
			continue;

		//计算点击碰撞
		CCRect shopGoodsRect = CCRectZero;
		//shopGoodsRect.origin = ccpAdd(shopGoods->getPosition(), ccp(-shopGoods->getContentSize().width/2, -shopGoods->getContentSize().height/2));
		shopGoodsRect.origin = shopGoods->getBgPos();
		shopGoodsRect.size = shopGoods->getContentSize();

        bool sus = CCRect::CCRectContainsPoint(shopGoodsRect, curTouchPoint);
		if (sus)
		{//碰撞成功
			return shopGoods;
		}
	}
	
	return 0;
}