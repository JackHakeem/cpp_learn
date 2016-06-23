#include "CommonList.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "model/guild/vo/ApplyVo.h"
#include "model/guild/vo/MemberVo.h"
#include "VerifyItem.h"
#include "MemberItem.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "PageNav.h"
#include "GuildItem.h"
#include "../GuildListenerMediator.h"

const float w_n_frame = 915-345;
const float h_n_frame = 520-145;
const float h_interval = 40;

CommonList::CommonList(const CCRect& mRect):CCUIPartialScrollView(mRect)
{}

CommonList::~CommonList()
{
	for (std::list<GuildVoBase*>::iterator it = _itemArr.begin(); it != _itemArr.end(); it++)
	{
		GuildVoBase* tp = *it;
		delete tp;
	}
	_itemArr.clear();
}

CommonList* CommonList::commonListScrollViewWithCCRect(const CCRect& mRect)
{
	CommonList *pScrollView = new CommonList(mRect);
    if(pScrollView && pScrollView->init()){
		// pScrollView->setIsTouchEnabled(false);//That may not be the touch
        //pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}


/**
	* 设置列表数据，外部接口
	* @param arr 存储Item的数组
	*/		
void CommonList::setDatas(std::list<GuildVoBase*>& voArr, int page)
{
	std::list<GuildVoBase*>::iterator it = _itemArr.begin();
	for ( ; it!= _itemArr.end(); it++ )
	{
		GuildVoBase* gvb = *it;
		CC_SAFE_DELETE( gvb );
	}
	_itemArr.clear();

	it = voArr.begin();
	for ( ; it!= voArr.end(); it++ )
	{
		GuildVoBase* gvb = *it;
		if (gvb)
		{
			if (gvb->getType() == GuildVoBase::GuildVoBase_ApplyVo)
			{
				//ApplyVo newnode = *((ApplyVo*)gvb);
				_itemArr.push_back((ApplyVo*)gvb);	
			}
			else if (gvb->getType() == GuildVoBase::GuildVoBase_GuildInfoVo)
			{
				//GuildInfoVo newnode = *((GuildInfoVo*)gvb);
				_itemArr.push_back((GuildInfoVo*)gvb);	
			}
			else if (gvb->getType() == GuildVoBase::GuildVoBase_MemberVo)
			{
				//MemberVo newnode = *((MemberVo*)gvb);
				_itemArr.push_back((MemberVo*)gvb);	
			}
		}
	}
	//
	updateList(page);
}


void CommonList::handleTouchEndPagePre()
{
	CCNode* par = (CCNode*)this->getParent();
	if (par)
	{
		PageNav* pageNav = 0;
		if ( g_pGuildListenerMediator->_preView == par->getParent() )
		{
			pageNav = g_pGuildListenerMediator->_preView->_pageNav;//par 是container
		}
		else
		{
			pageNav = (PageNav*)par->getChildByTag(99);
		}
		if (pageNav)
		{
			if (pageNav->_curPage <= 1) 
			{
				this->moveToPage(currentScreen);
			}
			else
				pageNav->onPrevHandler(0);
			
		}
	}
	//FriendView* father = ViewManager::getInstance()->friendView;
	////FriendView* father = (FriendView*)this->getParent()->getParent();
	//if (father)
	//	father->onClickPre();
}

void CommonList::handleTouchEndPageNext()
{
	CCNode* par = (CCNode*)this->getParent();
	if (par)
	{
		PageNav* pageNav = 0;
		if ( g_pGuildListenerMediator->_preView == par->getParent() )
		{
			pageNav = g_pGuildListenerMediator->_preView->_pageNav;//par 是container
		}
		else
		{
			pageNav = (PageNav*)par->getChildByTag(99);
		}
		
		if (pageNav)
		{
			if (pageNav->_curPage >= pageNav->_maxPage)
			{
				this->moveToPage(currentScreen);
			}
			else
				pageNav->onNextHandler(0);
		}
	}
	//FriendView* father = ViewManager::getInstance()->friendView;
	////FriendView* father = (FriendView*)this->getParent()->getParent();
	//if (father)
	//	father->onClickNext();
}

void CommonList::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	int newX = (int)touchPoint.x;
		
	stateSscroll = -1;
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) > totalScreens )
	{
		handleTouchEndPageNext();
		stateSscroll = 0;
	}

	else 
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		//this->moveToNextPage();
		handleTouchEndPageNext();
		stateSscroll = 0;
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		//this->moveToPreviousPage();
		handleTouchEndPagePre();
		stateSscroll = 1;
	}
	else
	{
		this->moveToPage(currentScreen);
		handleTouchEnd2Page();
		stateSscroll = 2;
	}	
	

	this->setIsTouchingMoving(false);
}

void CommonList::handleTouchEndAfter(bool same, int curlayertag)
{
	if (!same && stateSscroll == 0)
	{
		this->moveToNextPage();
	}
	else if (!same && stateSscroll == 1)
	{
		this->moveToPreviousPage();
	}
	else if (same)
	{
		this->moveToPage(currentScreen);
		if (stateSscroll == 0)
		{//目标是下一页，但是没下页了，所以要把原来下页的东西都清除
			CCLayer* l = this->getLayerByTag(curlayertag+1);
			if (l)
				l->removeAllChildrenWithCleanup(true);
		}
		else if (stateSscroll == 1)
		{//目标是上一页，但是没上页了，所以要把原来下页的东西都清除
			CCLayer* l = this->getLayerByTag(curlayertag-1);
			if (l)
				l->removeAllChildrenWithCleanup(true);
			
		}
	}

	stateSscroll = -1;
}

void CommonList::updateList(int page)
{
	CCLog("page change:%d", page);
	//if (!_fpContainer) return;
	//_fpContainer->removeAllChildrenWithCleanup(true);
	CCLayer* l = this->getLayerByTag(page-1);
	if (l)
		l->removeAllChildrenWithCleanup(true);
	else
	{//新建页
		l = this->addLayerByTag(page-1);
	}


	//_fpContainer->_list.clear();//这里也要清除掉控件的所有条目
	std::list<GuildVoBase*>::iterator it;
	int32 index = 0;
	for (it = _itemArr.begin(); it != _itemArr.end(); it++, index++)
	{
		//_fpContainer->setlistItem(*it, index, l);	
		GuildVoBase* gvb = *it;
		if (gvb)
		{
			if (gvb->getType() == GuildVoBase::GuildVoBase_ApplyVo)
			{
				VerifyItem* newItem = new VerifyItem();
				newItem->init(*(ApplyVo*)gvb);
				l->addChild(newItem, index);
				newItem->release();
				newItem->setPosition(ccp(POSX(((920-335)-(915-345))/2), POSX(520-145-index*h_interval)));
			/*	MemberItem* newItem = new MemberItem();
				newItem->init(*(MemberVo*)gvb);
				l->addChild(newItem, index);
				newItem->release();*/
			}
			else if (gvb->getType() == GuildVoBase::GuildVoBase_GuildInfoVo)
			{
				GuildItem* newItem = new GuildItem();
				newItem->init(*(GuildInfoVo*)gvb);
				l->addChild(newItem, index);
				newItem->release();
				newItem->setPosition(ccp(POSX(((920-335)-(915-345))/2), POSX((353+20)-index*41))); 
			}
			else if (gvb->getType() == GuildVoBase::GuildVoBase_MemberVo)
			{
				MemberItem* newItem = new MemberItem();
				newItem->init(*(MemberVo*)gvb, index);
				l->addChild(newItem, index);
				newItem->release();
				newItem->setPosition(ccp(POSX(((920-335)-(915-345))/2), POSX(520-145-index*h_interval)));
			}
		}
	}
	//_fpContainer->updateFList();//更新显示
	//hasInit = true;
	//_fpContainer.index +1;
	bool same = (currentScreen == page)?true:false;
	this->handleTouchEndAfter(same, page-1);
	currentScreen = page;
	//_pageNum = page;

	//更新当前页总页数
	//updatePageShow();

}

/**
	* 更新显示列表 
	*/		
void updateList()
{
	//removeAllLayer();

	//for (int i = 0; i < pagecount; i++)
	//{
	//	this->addLayerByTag(i);
	//}


	//BankGoods* bankGoods;
	//std::map<int32, GoodsInfo*>::iterator it;

	//_goodsDic->removeAllObjects();
	//for (int i = 0; i < 10; i++)
	//{
	//	CCLayer* layer = getLayerByTag(i);//0KK
	//	if (layer)
	//		layer->removeAllChildrenWithCleanup(true);
	//}

	//for (it = goodDic.begin(); it != goodDic.end(); it++)
	//{
	//	GoodsInfo* tmp = it->second;
	//	if (tmp == 0)
	//		continue;

	//	int32 sitNum = tmp->sitGrid;
	//	
	//	//join
	//	CCLayer* layer = getLayerByTag(sitNum/BANK_ITEM_COUNT_PER_PAGE);//0KK
	//	
	//	if (layer)
	//	{
	//		
	//		bankGoods = (BankGoods*)layer->getChildByTag(sitNum);
	//		if (!bankGoods)
	//		{
	//			//If not the new construction
	//			bankGoods = new BankGoods();
	//			layer->addChild(bankGoods, 1, sitNum);//tag is sitnum
 //               bankGoods->release();
	//		}

	//		//Insert containers
	//		if (bankGoods->initBankGoods(tmp, sitNum%BANK_ITEM_COUNT_PER_PAGE, sitNum/BANK_ITEM_COUNT_PER_PAGE) && _goodsDic)
	//			_goodsDic->addObject(bankGoods);
	//	}
	//}

	//for (int i = goodsNum; i < BANKMAXGRID; i++)
	//{
	//	//Join
	//	//int page = i/BANK_ITEM_COUNT_PER_PAGE;
	//	CCLayer* layer = getLayerByTag(i/BANK_ITEM_COUNT_PER_PAGE);//0KK
	//	if (layer)
	//	{
	//		bankGoods = (BankGoods*)layer->getChildByTag(i);
	//		if (!bankGoods)
	//		{
	//			//If not the new construction
	//			bankGoods = new BankGoods();
	//			//bagGoods->init();
	//			layer->addChild(bankGoods, 1, i);//tag is sitnum
 //               bankGoods->release();
	//		}

	//		//Insert containers
	//		if (bankGoods->initBankGoods(0, i%BANK_ITEM_COUNT_PER_PAGE, i/BANK_ITEM_COUNT_PER_PAGE, true) && _goodsDic)
	//			_goodsDic->addObject(bankGoods);
	//	}
	//}	
}

/**
	* vo对象转换成item 
	* @param voArr 需要专业的vo对象数组
	* @return 返回转换后的item对象数组
	*/		
//Array CommonList::voToItem(std::list<GuildVoBase*>& voArr)
//{
//	var tmpArr:Array = new Array();
//	for(var i:uint=0; i<voArr.length; i++){
//		if(voArr[i] is ApplyVo){
//			tmpArr.push(new VerifyItem(voArr[i]));
//		}else if(voArr[i] is GuildInfoVo){
//			tmpArr.push(new GuildItem(voArr[i]));
//		}else if(voArr[i] is MemberVo){
//			tmpArr.push(new MemberItem(voArr[i]));
//		}
//	}
//	return tmpArr;
//}

