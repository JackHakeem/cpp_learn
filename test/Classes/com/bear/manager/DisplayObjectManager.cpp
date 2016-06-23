#include "DisplayObjectManager.h"
#include "manager/ViewManager.h"
#include "model/scene/vo/FindVo.h"
#include "events/GameDispatcher.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "view/report/ReportMediator.h"
#include "utils/loader/KKAnimationFactory.h"
#include "manager/layer/WindowLayer.h"
#include "manager/CDManage.h"

DisplayObjectManager *_pInstance = NULL;
void DisplayObjectManager::showFirstGoldEffect()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/newhand/res_newhand_gold.plist");
	_pGoldSprite = CCSprite::spriteWithSpriteFrameName("newhand/gold.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/newhand/res_newhand_gold.plist");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_pGoldSprite->setAnchorPoint(ccp(0.5, 0.5));
	_pGoldSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	LayerManager::windowLayer->addChild(_pGoldSprite);

	CCFiniteTimeAction *pMoveAction = CCMoveTo::actionWithDuration(1, POS(ccp(108, 620), ScaleUtil::TOP_LEFT));
	CCFiniteTimeAction *pScaleAction = CCScaleTo::actionWithDuration(1, 0.2, 0.2);
	CCSpawn *pSpawnAction = CCSpawn::actionOneTwo(pMoveAction, pScaleAction);
	CCCallFunc *pGoldChangedFunc = CCCallFunc::actionWithTarget(this, callfunc_selector(DisplayObjectManager::onGoldEffComplete));
	CCCallFunc *pFindNpcFunc = CCCallFunc::actionWithTarget(this, callfunc_selector(DisplayObjectManager::fineNpcHandle));
	CCAction *pAction = CCSequence::actions(pSpawnAction, pGoldChangedFunc, pFindNpcFunc, NULL);
	_pGoldSprite->runAction(pAction);
}

void DisplayObjectManager::onGoldEffComplete()
{
	if(_pGoldSprite && _pGoldSprite->getParent())
		_pGoldSprite->removeFromParentAndCleanup(true);

	if(ViewManager::getInstance()->_roleUI){
		ViewManager::getInstance()->_roleUI->setGold(RoleManage::Instance()->_accountInfo._gold);
	}
}

void DisplayObjectManager::fineNpcHandle()
{
	FindVo findVo;
	findVo._type = 1;
	findVo._sceneId = 1001;
	findVo._npcId = 1;
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
}

DisplayObjectManager * DisplayObjectManager::getInstance()
{
	if(!_pInstance)
	{
		_pInstance = new DisplayObjectManager();
	}
	return _pInstance;
}

void DisplayObjectManager::loadPassGiftSkin( int honorId )
{
	//ModuleLoaderManage.getInstance().load(ResourceName.PASS_GIFT_PATH, LoadLevel.FIRST, playPassGift);
	//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(GameDispatcher.OPEN_MAP_AWARD, _honorId));
	g_pReportMediator->openAward( honorId );
}


void DisplayObjectManager::PlayRecvTaskEffect()
{
	CCAnimation* clickEffect = g_pKKAnimationFactory->registAni("assets/effect/recvTask/recvTask.plist", "recvImg%d.png", 12, 0.1f);
	if ( !clickEffect )
	{
		return;
	}

	CCSprite* _clickEffectMc = (CCSprite*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTag_RecvTaskEffect);

	if ( !_clickEffectMc )
	{

		_clickEffectMc = new CCSprite();
		_clickEffectMc->init();
		LayerManager::windowLayer->addChild(_clickEffectMc,
			WindowLayer::WindowLayerZ_RecvTaskEffect, WindowLayer::WindowLayerTag_RecvTaskEffect);
		_clickEffectMc->release();

		CCSize cs = CCDirector::sharedDirector()->getWinSize();
		_clickEffectMc->setPosition( ccp( cs.width/2, cs.height/2+POSX(200) ) );

		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(DisplayObjectManager::PlayRecvTaskEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect/*, false*/ ), 
			callBack, 
			NULL );
		action->setTag(321);
		_clickEffectMc->runAction( action );
	}
	else
	{
		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(DisplayObjectManager::PlayRecvTaskEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect, false ), 
			callBack, 
			NULL );
		action->setTag(321);
		_clickEffectMc->runAction( action );

		_clickEffectMc->setIsVisible(true);
	}
}

void DisplayObjectManager::PlayRecvTaskEffectComplete( CCNode* pnode )
{

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/effect/recvTask/recvTask.plist");//kevinshit

	//if (CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/recvTask/recvTask.pvr.ccz"))
	//{
	//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/effect/recvTask/recvTask.pvr.ccz");
	//}


	CCSprite* _clickEffectMc = (CCSprite*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTag_RecvTaskEffect);
	if ( _clickEffectMc )
	{
		//_clickEffectMc->setIsVisible(false);
		CCAction* act = _clickEffectMc->getActionByTag(321);
		_clickEffectMc->stopAction(act);
		_clickEffectMc->removeFromParentAndCleanup(true);
	}

	g_pKKAnimationFactory->removeUnusedTextureForKey("assets/effect/recvTask/recvTask");
	//CCAnimationCache::sharedAnimationCache()->removeAnimationByName( "assets/effect/recvTask/recvTask.plist" );
	//
	//if ( CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/recvTask/recvTask.pvr.ccz"))
	//{
	//	if (p->retainCount()>1)
	//	{
	//		CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(CDManage::removeUnusedTexturesLater),
	//			CDManage::Instance(), 1.5f, false);
	//	}
	//	else
	//	{
	//		CCTextureCache::sharedTextureCache()->removeUnusedTextureForKey("assets/effect/recvTask/recvTask.pvr.ccz");
	//	}
	//}
}

void DisplayObjectManager::PlayFinTaskEffect()
{
	CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/finTask/finTask.pvr.ccz");

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444);
	CCAnimation* clickEffect = g_pKKAnimationFactory->registAni("assets/effect/finTask/finTask.plist", "finTask%d.png", 12, 0.1f);
	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default);
	if ( !clickEffect )
	{
		return;
	}

	CCSprite* _clickEffectMc = (CCSprite*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTag_FinTaskEffect);

	if ( !_clickEffectMc )
	{		

		_clickEffectMc = new CCSprite();
		_clickEffectMc->init();
		LayerManager::windowLayer->addChild(_clickEffectMc,
			WindowLayer::WindowLayerZ_FinTaskEffect, WindowLayer::WindowLayerTag_FinTaskEffect);
		_clickEffectMc->release();

		CCSize cs = CCDirector::sharedDirector()->getWinSize();
		_clickEffectMc->setPosition( ccp( cs.width/2, cs.height/2+POSX(200) ) );

		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(DisplayObjectManager::PlayFinTaskEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect, false ), 
			callBack, 
			NULL );
		_clickEffectMc->runAction( action );
	}
	else
	{
		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(DisplayObjectManager::PlayFinTaskEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect, false ), 
			callBack, 
			NULL );

		_clickEffectMc->runAction( action );

		_clickEffectMc->setIsVisible(true);
	}
}

void DisplayObjectManager::PlayFinTaskEffectComplete( CCNode* pnode )
{

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/effect/finTask/finTask.plist");//kevinshit

	//if (CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/finTask/finTask.pvr.ccz"))
	//{
	//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/effect/finTask/finTask.pvr.ccz");
	//}


	CCSprite* _clickEffectMc = (CCSprite*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTag_FinTaskEffect);
	if ( _clickEffectMc )
	{
		_clickEffectMc->stopAllActions();
		_clickEffectMc->removeFromParentAndCleanup(true);
	}

	g_pKKAnimationFactory->removeUnusedTextureForKey("assets/effect/finTask/finTask");
	//CCAnimationCache::sharedAnimationCache()->removeAnimationByName( "assets/effect/finTask/finTask.plist" );
	//if ( CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/finTask/finTask.pvr.ccz"))
	//{
	//	if (p->retainCount()>1)
	//	{
	//		CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(CDManage::removeUnusedTexturesLater),
	//			CDManage::Instance(), 1.5f, false);
	//	}
	//	else
	//	{
	//		CCTextureCache::sharedTextureCache()->removeUnusedTextureForKey("assets/effect/finTask/finTask.pvr.ccz");
	//	}
	//}
}

void DisplayObjectManager::showAwardEffect()
{
	_pGoldSprite = CCSprite::spriteWithSpriteFrameName("mainUI/award_btn.png");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_pGoldSprite->setAnchorPoint(ccp(0.5, 0.5));
	_pGoldSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	LayerManager::windowLayer->addChild(_pGoldSprite);

	CCFiniteTimeAction *pMoveAction = CCMoveTo::actionWithDuration(1,
		POS(ccp(313+139/2-120, 540), ScaleUtil::TOP_LEFT));
	CCFiniteTimeAction *pScaleAction = CCScaleTo::actionWithDuration(1, 1.0, 1.0);
	CCSpawn *pSpawnAction = CCSpawn::actionOneTwo(pMoveAction, pScaleAction);
	CCCallFunc *pGoldChangedFunc = CCCallFunc::actionWithTarget(this,
		callfunc_selector(DisplayObjectManager::onGoldAwardEffComplete));
	CCAction *pAction = CCSequence::actions(pSpawnAction, pGoldChangedFunc, NULL);
	_pGoldSprite->runAction(pAction);

	ViewManager::getInstance()->_secNavigate->hideBtnAward();
}

void DisplayObjectManager::onGoldAwardEffComplete()
{
	_pGoldSprite->removeFromParentAndCleanup(true);
	ViewManager::getInstance()->_secNavigate->addButtonAward();
}
