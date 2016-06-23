#include "PageNav.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

PageNav::PageNav()
{
	_maxPage = 1;
	_curPage = 1;
}

PageNav::~PageNav()
{}

bool PageNav::init()
{
	if (!LayerNode::init())
		return false;

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
			0 );//menu_selector(PageNav::onPrevHandler)
		pDirectItem->setPosition(ccp(POSX(540), POSX(640-565)));
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
			0 );//menu_selector(PageNav::onNextHandler)
		CCSprite* pS = (CCSprite*)pDirectItem->getNormalImage();
		pS->setFlipX( true );
		pS = (CCSprite*)pDirectItem->getSelectedImage();
		pS->setFlipX( true );
		pDirectItem->setPosition(POSX(700), POSX(640-565));
		pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( -20000 );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect);
		pDirectItem->setScaleY(0.7f);
	}

	//char pTp[10];
	//sprintf(pTp, "%d/%d", _pageNum, _fpContainer->totalScreens);
	CCLabelTTF* pLable_pTp = CCLabelTTF::labelWithString(" / ", 
		CCSizeMake(POSX(200), POSX(50)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(50));
	pLable_pTp->setPosition(ccp(POSX(620), POSX(640-565)));
	this->addChild(pLable_pTp, 0, PageNavTAG_page);
	pLable_pTp->setColor(ccc3(254, 189, 0));

	return true;
}

void PageNav::onPrevHandler(CCObject* pSender)
{
	if (_curPage <= 1) return;
	_curPage--;
	//updateText();
	this->dispatchEvent(PAGE_CHANGE, &_curPage);
}

void PageNav::onNextHandler(CCObject* pSender)
{
	if (_curPage >= _maxPage) return;
	_curPage++;
	//updateText();
	this->dispatchEvent(PAGE_CHANGE, &_curPage);
}

void PageNav::setPage(int max, int index)
{
	if(index > max) return;
	if(index<1) index = 1;
	if(max<1) max = 1;
	_maxPage = max;
	_curPage = index;
	updateText();
}

void PageNav::updateText()
{
	CCLabelTTF* pLable_pTp = (CCLabelTTF*)this->getChildByTag(PageNavTAG_page);
	if (pLable_pTp)
	{
		char pTp[10];
		sprintf(pTp, "%d/%d", _curPage, _maxPage);

		pLable_pTp->setString(pTp);
	}	
}