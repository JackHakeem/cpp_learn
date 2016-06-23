#include "FPContainer.h"
#include "FListItem.h"
#include "utils/ScaleUtil.h"
#include "FriendView.h"
#include "FriendEventConst.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"


FPContainer* FPContainer::friendScrollViewWithCCRect(const CCRect& mRect)
{
    FPContainer *pScrollView = new FPContainer(mRect);
    if(pScrollView && pScrollView->init()){
		// pScrollView->setIsTouchEnabled(false);//That may not be the touch
        //pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;	
}

FPContainer::FPContainer(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	_index = 0;
	_list.clear();
	stateSscroll = -1;
	//this->setPosition(ccp(POSX(16), POSX(0)));
}

FPContainer::~FPContainer()
{}

void FPContainer::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Friend, true);
}

/*
bool FPContainer::init()
{
	if (!CCLayer::init())
		return false;
	
	//this->setIsRelativeAnchorPoint(true);
   // this->setAnchorPoint(ccp(0,0));
	this->setPosition(ccp(POSX(16), POSX(0)));

	//CCPoint aaa = getScreenPos(this,true);

	
	//　Has connected a task list
	_pFListView = CCUIListView::listViewWithCCRect(CCRectMake(0, 80, 960, 430), false);
	_pFListView->setIsRelativeAnchorPoint(true);
    _pFListView->setAnchorPoint(ccp(0,0));
	//_pListView->setAnchorPoint(CCPointZero);
	_pFListView->setSpacingVertical(POSX(8));

	_pFListView->setWorldSpaceBottomLeftPoint(ccpAdd(getScreenPos(this, true), ccp(0, 120)));//ccpAdd(_pFListView->getPositionInPixels(), getScreenPos(this, true))
	_pFListView->setOnItemActionListener(this);
	this->addChild(_pFListView, FPContainerZ_ListView, FPContainerTAG_ListView);
	//_pListView->setAdapter(this);
	
	return true;
}
*/

//CC_PROPERTY(int32, _index, index)
void FPContainer::setindex(int32 var)
{
	_index = var;
}

int32 FPContainer::getindex()
{
	return _index;
}

/**
	* 确定item上的显示按钮，在新UI出来前暂不处理 
	* @param friInfo
	* 
	*/		
void FPContainer::setlistItem(FriendInfoVo friInfo, int32 tag, CCLayer* dst)
{
	if (!dst)
		return;
    //Doyang 20120718
//	int32 btnCategory = 0;
//	if(getindex() == 0)//tabIndex为Sprite自带的属性，在FriendView里设置
//		btnCategory = 0;
//	else
//		btnCategory = 1;
//	if(view() && !view()->_friCrystalEnabel && btnCategory == 0)
//		btnCategory = 3;
	FListItem* fl = new FListItem;
	fl->init(friInfo, getindex()/*btnCategory*/, tag);
	_list.push_back(fl);

	//CCLayer* cl = getCurScreen();
	//if (cl)
	dst->addChild(fl, 0, tag);
}

FriendView* FPContainer::view()
{
//	FriendView* tempVar = (FriendView*)this->getParent();
//	return tempVar ? tempVar : 0; 
	FriendView* fv = ViewManager::getInstance()->friendView;
	if (fv)
	{
		return fv;
	}
	return 0;
}
/*
void FPContainer::updateFList()
{
	if (_pFListView)
		_pFListView->setAdapter(this);
}

int FPContainer::getCount()
{
	return _list.size();
}

LayerNode* FPContainer::getView( int position )
{
	if (position < _list.size() && position >= 0)
		return _list[position];
	else
		return 0;
}

void FPContainer::onItemClickListener( LayerNode *itemCell, int position )
{
	CCLog("FPContainer::onItemClickListener %d", position);
}
*/
/**
	* item上面的按钮触发 
	* @param event
	* 
	*/		
void FPContainer::quickAddFriHandler(FriendInfoVo* param)
{
	//if(event.param as FriendInfoVo){
	if (param && view())//kevinq
		view()->dispatchEvent(FriendEventConst::ADD_FRIEND, (void*)&param->name);//new ParamEvent(FriendEventConst.ADD_FRIEND, (event.param as FriendInfoVo).name));
	//}
}

CCLayer* FPContainer::getCurScreen()
{
	return (CCLayer*)this->getContentLayer()->getChildByTag(currentScreen-1);
}

void FPContainer::handleTouchEndPagePre()
{
	FriendView* father = ViewManager::getInstance()->friendView;
	//FriendView* father = (FriendView*)this->getParent()->getParent();
	if (father)
		father->onClickPre();
}

void FPContainer::handleTouchEndPageNext()
{
	FriendView* father = ViewManager::getInstance()->friendView;
	//FriendView* father = (FriendView*)this->getParent()->getParent();
	if (father)
		father->onClickNext();
}

void FPContainer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
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

void FPContainer::handleTouchEndAfter(bool same, int curlayertag)
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