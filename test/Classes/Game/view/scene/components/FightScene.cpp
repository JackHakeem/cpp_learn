#include "FightScene.h"
#include "manager/RenderManage.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "model/skill/vo/SkillVo.h"
#include "model/skill/SkillManager.h"
#include "model/scene/vo/EventType.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "BattlePlay.h"
#include "utils/ValuesUtil.h"
#include "fight/FightEnd.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "fight/BattleEnginer.h"

#include "manager/TouchLayerEnum.h"
#include "manager/GlobalManage.h"
#include "events/GameDispatcher.h"
#include "model/scene/vo/SceneConst.h"
#include "manager/sound/SoundManager.h"
#include "manager/SourceCacheManage.h"
#include "manager/GlobalManage.h"
#include "EndBtnTips.h"
#include "model/silverMine/SilverMineProxy.h"

FightScene::FightScene()
{
	_type = 0;
	_battleType = 0;
	_isNewHandLeader = false;
	_warPlace = NULL;
	_roundLabel = NULL;

	_resultWin = 0;

	_pEndFightMenu = 0;
	_pFastFightMenu = 0;

	addEventListener(Event::ADDED_TO_STAGE, this, callfuncND_selector(FightScene::addedToStage));

	// add by LH
	GameDispatcher::getInstance()->dispatchEvent(SceneConst::WALK_COMPLETE,0);
	Scene * scene = ViewManager::getInstance()->_scene;
	if (scene)
	{
		scene->_elementLayer->setIsVisible(false);
		scene->_mouseLayer->setIsVisible(false);
		if(scene->_role && scene->_role->poseState)
		{
			scene->_role->poseState->state(SceneConst::STAND);
		}
	}
	g_pGlobalManage->_isInFight = true;
	g_pGlobalManage->showAllUI(false);

	initUI();
}

FightScene::~FightScene()
{
	//if (_warPlace){_warPlace->release();}	// LH0708LEAK
	//if (_roundLabel){_roundLabel->release();}// LH0708LEAK
	//if (_resultWin){_resultWin->release();}// LH0708LEAK
	//if (_pEndFightMenu){_pEndFightMenu->release();}// LH0708LEAK
	//if (_pFastFightMenu){_pFastFightMenu->release();}// LH0708LEAK
}

void FightScene::initUI()
{
	_elementDic.clear();
	_faceList.clear();

	_warPlace = createWarField(m_screenWidth / 2, m_screenHeight / 2, 1, 1);
	_frontBGLayer->addChild(_warPlace, 10); 
	_warPlace->release();

	this->setIsTouchEnabled(true);//kevinz
	//CCUIBackground* fightBg = new CCUIBackground();
	//fightBg->initWithSpriteFrame("ui.png", ccp(0, 0), ccp(POSX(20), POSX(20)), CCSizeMake(m_screenWidth, m_screenHeight));
	//_frontBGLayer;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColorWidthHeight(ccc4(0,0,0,100), winSize.width, winSize.height);
    blackBG->setPosition(ccp(-winSize.width /2 , -winSize.height /2 ));
    blackBG->setAnchorPoint(CCPointZero);
    blackBG->setIsRelativeAnchorPoint(true);
	_warPlace->addChild(blackBG, 1);
//	blackBG->setPosition(ccp(POSX(-960/2), POSX(-640/2)));
	//_frontBGLayer->addChild(cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,150)), 11);

//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// stop fight

	// world boss 
	// LH20120919
	int curMapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if (curMapId == 1208)
	{
		g_pGlobalManage->setIsShowEndFightButton(true);
	}

	SilverMineProxy* _mineProxy = (SilverMineProxy*) g_pFacade->retrieveProxy(AppFacade_SilverMine_PROXY_CHANGE);
	if (_mineProxy->isInMine)
	{
		g_pGlobalManage->setIsShowEndFightButton(true);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	g_pGlobalManage->setIsShowEndFightButton(true);
#endif

	/*if (RoleManage::Instance()->roleLev() >= 8)
	{
	g_pGlobalManage->setIsShowEndFightButton(true);
	}*/
	

	if(g_pGlobalManage->getIsShowEndFightButton())	
    {
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_pEndFightMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
                this,
                menu_selector(FightScene::endFight));
			_pEndFightMenu = CCMenu::menuWithItem(_pEndFightMenuItem);
			_pEndFightMenu->setPosition(ccp(winSize.width-POSX(180),POSX(580)));
			_pEndFightMenu->setTouchLayer(TLE::FightLayer-5);
			_pEndFightMenu->setTag(TAG_BTN_END);
			this->addChild(_pEndFightMenu);
			CCLabelTTF * _pEndText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FT001").c_str(),CCSizeMake(POSX(120), POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(26));
			_pEndText->setColor(ccc3(250,215,0));
			_pEndText->setPosition(ccp(winSize.width-POSX(180),POSX(580)));
			this->addChild(_pEndText,1);
		}
	}
	

	// to fast kevinf
	/*
	CCMenuItemImage * _pFastFightMenuItem = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/button.png",
		"assets/ui/button1.png",
		this,
		menu_selector(FightScene::fastFight));
	_pFastFightMenu = CCMenu::menuWithItem(_pFastFightMenuItem);
	_pFastFightMenu->setPosition(ccp(POSX(winSize.width-420),POSX(60)));
	_pFastFightMenu->setTouchLayer(-1200);
	_pFastFightMenu->setScaleX(0.8);
	this->addChild(_pFastFightMenu);
	CCLabelTTF * _pFastText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FT002").c_str(),CCSizeMake(60,30),CCTextAlignmentCenter,g_sSimHeiFont,POSX(26));
	_pFastText->setColor(ccc3(250,215,0));
	_pFastText->setPosition(ccp(POSX(winSize.width-320),POSX(60)));
	this->addChild(_pFastText,1);
	*/


	//_peratingSP = new Sprite;
	//_peratingSP.visible = false;
	//_faceLayer.addChild(_peratingSP);

	//_controlBtns = Reflection.createInstance("war_controlBtns") as MovieClip;
	//_peratingSP.addChild(_controlBtns);

	//_btnEnd = _controlBtns["_btnEnd"] as SimpleButton;
	//_btnEnd.addEventListener(MouseEvent.CLICK,onClick);
	//new TipHelps().setToolTips(_btnEnd, "结束战斗<font color='#00FF00'>[Esc]</font>");

	//_btnNormal = _controlBtns["_btnNormal"] as SimpleButton;
	//_btnNormal.addEventListener(MouseEvent.CLICK, onNormalPlay);
	//_btnNormal.visible = false;
	//new TipHelps().setToolTips(_btnNormal, LangManager.getText("SCE043"));

	//_btnFast = _controlBtns["_btnFast"] as SimpleButton;
	//_btnFast.addEventListener(MouseEvent.CLICK, onSpeedPlay);
	//_btnFast.visible = true;
	//new TipHelps().setToolTips(_btnFast, LangManager.getText("SCE044"));

	//_roundMc = Reflection.createInstance("war_round");  // 战斗回合 
	//_roundMc.x = StageProxy.width/2 ;
	//_roundMc.y = 60;
	//_faceLayer.addChild(_roundMc);
	//_roundMc.visible = false;

	//if (SourceCacheManage.getInstance().has("war_place") == false) {
	//	mc = createWarField(StageProxy.fightCenterPoint().x, StageProxy.fightCenterPoint().y);
	//	SourceCacheManage.getInstance().put("war_place", mc);
	//}else {
	//	mc = SourceCacheManage.getInstance().getObject( "war_place") as MovieClip;
	//	mc.x = StageProxy.fightCenterPoint().x;
	//	mc.y = StageProxy.fightCenterPoint().y;
	//}
	//_frontBGLayer.addChild(mc);
    
    this->setPosition(CCPointZero);
    this->setAnchorPoint(CCPointZero);
}

void FightScene::addedToStage(CCNode* n, void* data)
{
	removeEventListener(Event::ADDED_TO_STAGE);
	RenderManage::Instance()->add(this);
}

void FightScene::showPeratingSP(bool value)
{
	//_peratingSP.visible = value;
}

CCLayer* FightScene::createWarField(int x, int y, int scaleX, int scaleY)
{
	/*var mcWarField:MovieClip = Reflection.createInstance("war_place") as MovieClip;
	mcWarField.x = x;
	mcWarField.y = y;
	mcWarField.scaleX = scaleX;
	mcWarField.scaleY = scaleY;
	return mcWarField;*/

	CCLayer* ly = new CCLayer();
	ly->init();
	ly->setPosition(ccp(x, y));
	return ly;
}

void FightScene::loadWarFormation(int formationId, int x, int y, int scaleX, int scaleY, int alpha)
{
	SkillVo* skillVo = SkillManager::Instance()->getSkill(formationId);
	if(!skillVo)
		return;

	FormationLoader* formationLoader = new FormationLoader();
	if(formationLoader)
	{
		char tmp[32] = {0};
		sprintf(tmp, "%d_%d", x, y);

		formationLoader->_x = x;
		formationLoader->_y = y;
		formationLoader->_scaleX = scaleX;
		formationLoader->_scaleY = scaleY;
		/*char stmp[128] = {0};
		sprintf(stmp, "fight/formation/%d.png", skillVo->resId);
      std::string tmpStr = std::string(stmp);*/
		formationLoader->load(skillVo->resId);
		formationLoader->setPosition(ccp(x, y));
		_formationLoaderDic.insert(make_pair(std::string(tmp), formationLoader));
		_warPlace->addChild(formationLoader);

		formationLoader->release(); // LH0708LEAK

	}
}

LiveThing* FightScene::getLiveThing(int type, int id)
{
	if(type == EventType::PVE && id > 9)
	{
		return (LiveThing*)(getNPC(id));
	}
	return getPlayer(id);
}

void FightScene::showResult(int result, int typeBattle, SCMD13D *pReward, SCMD3B1 *pReport)
{
	/*_type = result > 0 ? 1 : 0;
	_battleType = typeBattle;
	if(typeBattle == BattleType::BATTLE_TYPE_PVE && result>0 && reward)
	{
		_resultWin = new FightEnd(result, reward, report, 2);
	}
	else{
		_resultWin = new FightEnd(result, reward, report, 1);
	}
	_resultWin.x = StageProxy.width - _resultWin.width>> 1;
	_resultWin.y = StageProxy.height - _resultWin.height>> 1;
	_resultWin.addEventListener(FightEnd.REPLAY, replay);
	_resultWin.addEventListener(FightEnd.COPY_REPORT, copyReport);
	_resultWin.addEventListener(FightEnd.RESULT_CLICK, closeResult);
	LayerManager.windowLayer.addChild(_resultWin);*/
    
    //Doyang 20120811
    g_pGlobalManage->setIsShowEndFightButton(false);
    
	FightEnd *pResultLayer = new FightEnd(result, pReward, pReport, typeBattle);
	if(!pResultLayer || !pResultLayer->init())
		return;
	pResultLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
	pResultLayer->setAnchorPoint(CCPointZero);
	pResultLayer->setPosition(CCPointZero);
	pResultLayer->setIsRelativeAnchorPoint(true);
	// 	if (this->getChildByTag(100))
	// 	{
	// 		this->removeChildByTag(100,true);
	// 	}
	if(_fightLayer)
	{
		if (!_fightLayer->getChildByTag(TAG_RESULT_LAYER))
		{
			_fightLayer->addChild(pResultLayer,0,TAG_RESULT_LAYER);
			CCMenu * pEndMenu = (CCMenu *)this->getChildByTag(TAG_BTN_END);
			if (pEndMenu)
			{
				pEndMenu->setIsTouchEnabled(false);
			}
			
		}		
	}
	pResultLayer->release();
    
}

void FightScene::showRound(int32 r)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	char roundChar[ 20 ];  
	sprintf(roundChar, ValuesUtil::Instance()->getString("fi_r").c_str(), r);
	if(!_roundLabel)
	{
		_roundLabel = CCLabelTTF::labelWithString( roundChar, "Arial", POSX(30) );     
		_roundLabel->setPosition(ccp(screenSize.width/2 , screenSize.height-POSX(30)));
		_frontBGLayer->addChild(_roundLabel, 13);
		_roundLabel->setColor(ccc3(254, 189, 0));
	}
	_roundLabel->setString(roundChar);
}

void FightScene::stopActions()
{
	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(; iter != _elementDic.end(); ++iter)
	{
		if(iter->second)
		{
			iter->second->stopAllActions();
		}
	}
}


void FightScene::dispose()
{
	BaseScene::dispose();

	//Doyang 20120716
	_fightLayer->removeChildByTag(TAG_RESULT_LAYER, true);
	_fightLayer->removeFromParentAndCleanup(true);

	//if(_isNewHandLeader)
	//{
	//	_isNewHandLeader = false;
	//	LeaderAlert.close();
	//}
	//_peratingSP.visible = false;
	//if( _resultWin )
	//{
	//	//_resultWin->dispose();
	//	if( _resultWin->getParent() )
	//		_resultWin->getParent()->removeChild( _resultWin, true );

	//	_resultWin = 0;
	//}

	for ( std::map<std::string, FormationLoader*>::iterator it = _formationLoaderDic.begin(); it != _formationLoaderDic.end(); it++ )
	{
		FormationLoader* formationLoader = it->second;
		if ( formationLoader )
		{
			formationLoader->dispose();

			if ( formationLoader->getParent() )
			{
				formationLoader->getParent()->removeChild( formationLoader, true );
				formationLoader = 0;
			}			
		}
	}
	_formationLoaderDic.clear();

	Scene * pScene = ViewManager::getInstance()->_scene;
	if (pScene&&!g_pGlobalManage->isInStory)
	{
		pScene->setIsTouchEnabled(true);
		pScene->_elementLayer->setIsVisible(true);
		pScene->_mouseLayer->setIsVisible(true);
		pScene->_movingLayer->setIsTouchEnabled(true);
	}
	//RenderManage.getInstance().remove(this);
	//StageProxy.removeListener(resize);
	g_pGlobalManage->_isInFight = false;
	if (!g_pGlobalManage->isInStory)
	{
		g_pGlobalManage->showAllUI(true);
	}

	//Begin Kenfly 20121213
	SourceCacheManage::Instance()->disposeEffect();
	SourceCacheManage::Instance()->disposeModel();
	//End Kenfly 20121213
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	//jae 20120117
	SourceCacheManage::Instance()->disposeSkillEffect();
#endif  // CC_PLATFORM_ANDROID

}

void FightScene::endFight(CCObject * pSender)
{
	int viplv = RoleManage::Instance()->_accountInfo.vipLev();
	bool istraial = RoleManage::Instance()->_accountInfo.trialVip();
//	bool isg = g_pGlobalManage->getIsShowEndFightButton() ;

	if ( /*istraial || 
		viplv>=3 || 
		(((Scene*)LayerManager::sceneLayer)->_redProgress.size() == 0)*/true)//is green monster  or vip3 or trail_vip
	{
		this->stopActions();
		ActionHandler::getInstance()->switchUpdate(false);
		ActionHandler::getInstance()->dispose();
		BattleEnginer::getInstance()->stop();		
	}
	else
	{
		EndBtnTips* oldp = (EndBtnTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_EndBtnTips);
		if (!oldp)
		{
			oldp = new EndBtnTips();
			oldp->init();
			LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_EndBtnTips, IntervalLayer::IntervalLayerTAG_EndBtnTips);
			oldp->release();
		}			
	}

	SoundManager::Instance()->playButtonEffectSound();
}

void FightScene::fastFight(CCObject * pSender)
{

}

void FightScene::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,TLE::FightLayer, true);
}

bool FightScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void FightScene::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}
