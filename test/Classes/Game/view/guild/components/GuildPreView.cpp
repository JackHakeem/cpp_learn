#include "GuildPreView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"
#include "PopUIBg.h"
#include "manager/layer/IntervalLayer.h"
#include "manager/LayerManager.h"
#include "utils/ValuesUtil.h"
#include "CreateGuild.h"
#include "GuildItem.h"
#include "../GuildListenerMediator.h"
#include "manager/ViewManager.h"
#include "../GuildMediator.h"
#include "utils/loader/KKAnimationFactory.h"

static const float FontSize3 = 24.0f;
static float FontSize2 = 20.0f;

GuildPreView::GuildPreView()
{
	_hasInit = false;
	_hasGuild = false;

	_guildList = 0;
	_btnCreate = 0;
}

bool GuildPreView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//key = PopEventName::PRE_GUILD;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/guild/res_guild.plist");

	//
	_container = new LayerNode();
	this->addChild(_container);
	_container->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	_container->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER_TOP));
	//_container->setPosition(POSX(-960/2), POSX(-640/2)); 

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//CCUIBackground* _bg0 = new CCUIBackground();
	//_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	//this->addChild(_bg0);
	//_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	//_bg1->initWithFile("assets/ui/popuibg/bg1.png",
	//	POS(ccp(16.0f, 12.0f), ScaleUtil::CENTER_TOP), ccp(0,0), CCSizeMake(w_bg1, h_bg1));
	_bg1->initWithSpriteFrame("popuibg/bg1.png",
		ccp(POSX(16.0f), POSX(12.0f)), ccp(0,0), CCSizeMake(w_bg1, h_bg1));
	_container->addChild(_bg1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	//_bg2->initWithFile("assets/ui/popuibg/bg2.png",
	//	POS(ccp(25.0f, 32.0f), ScaleUtil::CENTER_TOP), ccp(0,0), CCSizeMake(w_bg2, h_bg2));
	_bg2->initWithSpriteFrame("popuibg/bg2.png",
		ccp(POSX(25.0f), POSX(32.0f)), ccp(0,0), CCSizeMake(w_bg2, h_bg2));
	_container->addChild(_bg2);
	_bg2->release();

	//
	CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		pCloseNormalSprite,
		pClosePressedSprite,
		this, 
		menu_selector(GuildPreView::dispear) );
	//_btnX->setPosition(ccp(screenSize.width-POSX(133/4), 
	//	screenSize.height-POSX(53)/2));
	_btnX->setPosition(ccp(POSX(928), 
		POSX(607)) );


	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
	buttonMenu->addChild(_btnX, 0, 0);
	buttonMenu->setPosition(ccp(0, 0));
	buttonMenu->setTouchLayer(TLE::WindowLayer_PopUIBgTAG_btn_X-200);
	_container->addChild(buttonMenu);
	buttonMenu->setIsVisible(true);
	buttonMenu->release();


	this->setContentSize(CCSizeMake(w_bg1, h_bg1));


	initView();

	_pageNav = new PageNav();
	_pageNav->init();
	_pageNav->addEventListener(PageNav::PAGE_CHANGE,
		this, callfuncND_selector(GuildPreView::onPageChange)); 
	_container->addChild(_pageNav, 1, 99);
	_pageNav->setPosition( ccp( POSX(111), 0 ) );

	//创建公会
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(GuildPreView::onCreatClick) );
		_btn->setPosition(ccp(POSX(489), POSX(640-570)));
		_btn->setTag(0);

		_btnCreate = CCMenu::menuWithItems(_btn, 0); 
		_btnCreate->setPosition( CCPointZero );
		_btnCreate->setTouchLayer(TLE::IntervalLayer-1);
		_container->addChild(_btnCreate);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1007").c_str(),
			CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}

	this->setIsTouchEnabled(true);
	return true;
}

void GuildPreView::initView()
{
	_guildList = CommonList::commonListScrollViewWithCCRect(
		CCRectMake(POSX(48), POSX(136-40), POSX(873), POSX(353+100))
		); 
	_guildList->m_pri = TLE::IntervalLayer;
	_container->addChild(_guildList);
	_guildList->release();
	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight(
	//	ccc4(0,0,255,100), POSX(873), POSX(353+100) );
	//_guildList->addChild(pColor);

	float titleoffsetX = 36.0f;//338.0f;
	//排名
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1002").c_str(),
			CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(26+titleoffsetX), POSX(640-124)));
		_container->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//公会
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1003").c_str(),
			CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(177+titleoffsetX), POSX(640-124)));
		_container->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//会长
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1004").c_str(),
			CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(314+titleoffsetX), POSX(640-124)));
		_container->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//等级
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1005").c_str(),
			CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(442+titleoffsetX), POSX(640-124)));
		_container->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//人数
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1006").c_str(),
			CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(592+titleoffsetX), POSX(640-124)));
		_container->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
}

void GuildPreView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::IntervalLayer, true );
}

bool GuildPreView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void GuildPreView::sethasGuild(bool bVar)
{
	_hasGuild = bVar;
	_btnCreate->setIsVisible(!_hasGuild);
}

bool GuildPreView::gethasGuild()
{
	return _hasGuild;
}

void GuildPreView::sethasInit(bool bVar)
{
	_hasInit = bVar;
	//_btnCreate.visible = !_hasGuild;
}

bool GuildPreView::gethasInit()
{
	return _hasInit;
}

/**
* 设置成员列表数据 
* @param listDatas 包含公会信息对象的vo数组
*/	
void GuildPreView::updateList( std::list<GuildVoBase*> listDatas )
{
	if (listDatas.size()==0)
	{
		_pageNav->dispatchEvent(PageNav::PAGE_CHANGE, &_pageNav->_curPage);
		return;
	}
 	_guildList->setDatas(listDatas, _pageNav->_curPage);
 	_hasInit = true;
 	if(_hasGuild)
	{
		//如果已入会，则隐藏“申请”按钮

		CCLayer* l = _guildList->getLayerByTag(_pageNav->_curPage-1);
		if (l)
		{
			CCArray* pArr = l->getChildren();
			if (pArr)
			{
				for (int i = 0; i< pArr->count(); i++)
				{
					GuildItem* item = (GuildItem*)pArr->objectAtIndex(i);
					item->canApply(false);
				}
			}
		}
 	}
}
		
void GuildPreView::setPage( int max/* = 1*/, int index/* = 1*/ )
{
	_pageNav->setPage(max, index);
}

/**
* 创建公会 
* @param event
*/
void GuildPreView::onCreatClick(CCObject* obj)
{
// 	if(!_creatView) _creatView = new CreateGuild();
// 	_creatView.isPop = !_creatView.isPop; 

	CreateGuild* oldp = (CreateGuild*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_guild_createGuild);
	if (!oldp)
	{
		oldp = new CreateGuild();
		oldp->init();
		LayerManager::intervalLayer->addChild(oldp,
			IntervalLayer::IntervalLayerZ_guild_creatGuild, IntervalLayer::IntervalLayerTAG_guild_createGuild);
		oldp->release();
	}
}

/**
* 翻页
* @param event
*/
void GuildPreView::onPageChange(CCNode* pSender, void* data)
{
	struct sdata
	{
		int page;
	};
	sdata obj;
	obj.page = *(int*)data;
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::GUILD_GET_LIST, &obj);
}

/**
* 初始化列表 
* 
*/		
void GuildPreView::onInit()
{
	int page = 1;
	GuildDispatcher::getInstance()->dispatchEvent( GuildEventConst::GUILD_GET_LIST, &page );
}


void GuildPreView::dispear(CCObject* pSender)
{
	GuildPreView* eqview = (GuildPreView*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_GuildPre);
	if (eqview)
	{
		eqview->removeFromParentAndCleanup(true);
	}
}

GuildPreView::~GuildPreView()
{

	if (ViewManager::getInstance()->guildPreView)
	{
		ViewManager::getInstance()->guildPreView = 0;
	}

	g_pGuildListenerMediator->_preView = 0;

	g_pGuildMediator->_preView = 0;

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/guild/res_guild.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/guild/res_guild.pvr.ccz");
	CCTextureCache::sharedTextureCache()->removeUnusedTextureForKey("assets/icon/guild/res_guild.pvr.ccz");
}
