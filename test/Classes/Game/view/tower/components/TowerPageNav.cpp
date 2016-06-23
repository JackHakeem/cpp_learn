#include "TowerPageNav.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "../TowerMediator.h"
#include "TowerRank.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"

TowerPageNav::TowerPageNav()
{
	_maxPage = 1;
	_curPage = 1;
}

TowerPageNav::~TowerPageNav()
{}

bool TowerPageNav::init()
{
	if (!LayerNode::init())
		return false;

	this->setContentSize( CCSizeMake(POSX(217), POSX(70)) );
	//
	{
		CCSize cellsize = CCSizeMake(80, 70);
		float offsetX = 20.0f;

		CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		CCMenuItemSprite *pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			this,
			menu_selector(TowerPageNav::onPrevHandler) );
		pDirectItem->setPosition(ccp(POSX(0), POSX(70/2)));
		CCMenu* pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( -20000 );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect);
		pDirectItem->setScaleY(0.7f);
		// right direct image btn
		pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			this,
			menu_selector(TowerPageNav::onNextHandler) );//
		CCSprite* pS = (CCSprite*)pDirectItem->getNormalImage();
		pS->setFlipX( true );
		pS = (CCSprite*)pDirectItem->getSelectedImage();
		pS->setFlipX( true );
		pDirectItem->setPosition(POSX(171), POSX(70/2));
		pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( -20000 );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect);
		pDirectItem->setScaleY(0.7f);
	}

	CCSize csThis = this->getContentSize();
	CCLabelTTF* pLable_pTp = CCLabelTTF::labelWithString(" / ", 
		CCSizeMake(POSX(200), POSX(50)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(50));
	pLable_pTp->setPosition(ccp(csThis.width/2-POSX(20), csThis.height/2));
	this->addChild(pLable_pTp, 0, TowerPageNavTAG_page);
	pLable_pTp->setColor(ccc3(254, 189, 0));

	return true;
}

void TowerPageNav::onPrevHandler(CCObject* pSender)
{
	if (_curPage <= 1) return;

	int page = _curPage-1; 

	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = _towerProxy->getpanel1Vo()->maxFloor;
	//int lev = RoleManage::Instance()->roleLev();
	int pageLimit = 0;
	if(lev <= 40){
		pageLimit = 9;
	}else if(lev <= 60){
		pageLimit = 7;
	}else if(lev <= 80){
		pageLimit = 5;
	}else if(lev <= 100){
		pageLimit = 3;
	}else if(lev <= 120){
		pageLimit = 1;
	}

	if (lev>40)
	{
		if ( (page<pageLimit) || (page>(pageLimit+1)) )
		{
			LangManager::msgShow("TOWR108");
			return;
		}
	}
	else
	{
		if ( (page<pageLimit) || (page>(pageLimit+3)) )
		{
			LangManager::msgShow("TOWR108");
			return;
		}
	}

	_curPage--;
	//updateText();


	if (g_pTowerMediator->_towerRank)
	{
		g_pTowerMediator->_towerRank->_listContainer->stateSscroll = 1;
	}
	this->dispatchEvent(PAGE_CHANGE, &_curPage);
}

void TowerPageNav::onNextHandler(CCObject* pSender)
{
	if (_curPage >= _maxPage) return;


	int page = _curPage+1; 

	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = _towerProxy->getpanel1Vo()->maxFloor;
	//int lev = RoleManage::Instance()->roleLev();
	int pageLimit = 0;
	if(lev <= 40){
		pageLimit = 9;
	}else if(lev <= 60){
		pageLimit = 7;
	}else if(lev <= 80){
		pageLimit = 5;
	}else if(lev <= 100){
		pageLimit = 3;
	}else if(lev <= 120){
		pageLimit = 1;
	}

	if (lev>40)
	{
		if ( (page<pageLimit) || (page>(pageLimit+1)) )
		{
			LangManager::msgShow("TOWR108");
			return;
		}
	}
	else
	{
		if ( (page<pageLimit) || (page>(pageLimit+3)) )
		{
			LangManager::msgShow("TOWR108");
			return;
		}
	}

	_curPage++;
	//updateText();

	if (g_pTowerMediator->_towerRank)
	{
		g_pTowerMediator->_towerRank->_listContainer->stateSscroll = 0;
	}
	this->dispatchEvent(PAGE_CHANGE, &_curPage);
}

void TowerPageNav::setPage(int max, int index)
{
	if(index > max) return;
	if(index<1) index = 1;
	if(max<1) max = 1;
	_maxPage = max;
	_curPage = index;
	updateText();
}

void TowerPageNav::updateText()
{
	CCLabelTTF* pLable_pTp = (CCLabelTTF*)this->getChildByTag(TowerPageNavTAG_page);
	if (pLable_pTp)
	{
		char pTp[10];
		sprintf(pTp, "%d/%d", _curPage, _maxPage);

		pLable_pTp->setString(pTp);
	}	
}