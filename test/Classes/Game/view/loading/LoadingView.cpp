#include "LoadingView.h"
#include "utils/ScaleUtil.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "CCUIBackground.h"
#include "../scene/SceneMediator.h"
#include "socket/command/c12/CCMD122.h"

static float s_progressLength = POSX(848.0f);
static float s_progressPer = POSX(46.0f);
static float s_cur_pro_x = POSX( 62-(42+5/*-25*/)/2/*+(40-25)*/ );

LoadingView::LoadingView()
{
	pParentLayer = 0;
	_proBg = 0;
}

LoadingView::~LoadingView()
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/loading/res_loading.pvr.ccz");
}

bool LoadingView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pParentLayer = new CCLayer();
	if(!pParentLayer)
	{
		return false;
	}
	pParentLayer->init();
	pParentLayer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER_TOP));	
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setTag(TAG_PARENT);
	this->addChild( pParentLayer );
	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight( ccc4(0, 0,255,255), size.width, size.height );
	//pParentLayer->addChild( pColor );

	// title
	CCSprite* sprite = CCSprite::spriteWithSpriteFrameName("loading/girl.png");
	sprite->setAnchorPoint( CCPointZero );
	sprite->setPosition( ccp(POSX(426), POSX(144)) );
	pParentLayer->addChild( sprite );

	sprite = CCSprite::spriteWithSpriteFrameName("loading/name.png");
	sprite->setAnchorPoint( CCPointZero );
	sprite->setPosition( ccp(POSX(202), POSX(157)) );
	pParentLayer->addChild( sprite );

	CCUIBackground* _infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("loading/back.png", 
		ccp(POSX(62), POSX(119)),
		ccp(3,2.5),
		CCSizeMake(POSX(848),POSX(27)));
	pParentLayer->addChild(_infoContainer);
	_infoContainer->release();

	_proBg = new CCUIBackground();
	_proBg->initWithSpriteFrame("loading/loading.png", 
		ccp(POSX(62), POSX(119-4)),
		ccp(0,0),
		CCSizeMake(POSX(2),POSX(27)));
	pParentLayer->addChild(_proBg);
	_proBg->release();
	CCSize cs( POSX(2), POSX(27) );
	_proBg->changeSize(cs);
	_proBg->setPosition(ccp(POSX(62), POSX(119-7)));

	_curSprite = CCSprite::spriteWithSpriteFrameName("loading/loading_cur.png");
	_curSprite->setAnchorPoint( CCPointZero );
	_curSprite->setPosition( ccp(s_cur_pro_x, POSX(119-(42-24)/2)) );
	_curSprite->setTag( TAG_LOADING_CUR );
	pParentLayer->addChild( _curSprite );

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/loading/res_loading.plist");

	return true;
}

void LoadingView::loadOneProgress( CCObject* obj, void* pData ) //Kenfly 20121121
{
	g_pGlobalManage->loadOneProgress( 1 );
}

void LoadingView::visit()
{
	//char tmp[10]={0};
	//sprintf(tmp,"LoadingView::visit loaded:%d", g_pGlobalManage->m_nNumberOfLoadedSprites);
	CCLog("LoadingView::visit loaded:%d", g_pGlobalManage->m_nNumberOfLoadedSprites);
	//CCLog("------------------LoadingView::visit:%x", this);

	float f = 100*((float)g_pGlobalManage->m_nNumberOfLoadedSprites / g_pGlobalManage->m_nNumberOfSprites);
	if (f>100.0f)
	{
		f = 100.0f;
	}
	//CCSize cs( f*POSX(848)/POSX(100.0f), POSX(27) );
	CCSize cs( POSX(f*848/100.0f), POSX(27) );
	CCLog("------------------LoadingView::visit:%f", f);

	_curSprite->setPosition( ccp(POSX(62-25)+cs.width, POSX(119-7)) );
	_proBg->changeSize(cs);

	static int packetIDCnt = 0;
	packetIDCnt++;
	if (packetIDCnt>120)
	{
		packetIDCnt = 0;

		// 290 what get a map has open, which will open
		CCMD122 packet122;
		packet122.a_byte = 0;
		GameServerSocket::getInstance()->sendMessage(&packet122);

		//SceneMediator* _sceneMediator = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
		//_sceneMediator->_scene->dispatchEvent(SceneConst::MAP_BG_INIT, NULL);

	}
	

	CCLayer::visit();
}