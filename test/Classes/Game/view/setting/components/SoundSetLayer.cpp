#include "SoundSetLayer.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "manager/sound/SoundManager.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "model/player/RoleManage.h"

#define LENGTH_VOL_PROGRESS (600)

SoundSetLayer::SoundSetLayer()
{
	_pSoundVolumeProgressBack = 0;
	_pSoundVolumeProgress = 0;
	_pSoundVolumeSlipButton = 0;
	_pEffectVolumeProgressBack = 0;
	_pEffectVolumeProgress = 0;
	_pEffectVolumeSlipButton = 0;

	_fCurSoundVolume = 0.6f;
	_fCurEffectVolume = 0.7f;
	
	SoundManager * pSoundManager = SoundManager::Instance();
	_nCurMapID = pSoundManager->_nCurMapID;
	setIsSoundOpen(pSoundManager->getIsSoundOpen());
	setIsEffectOpen(pSoundManager->getIsEffectOpen());
}

bool SoundSetLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_winSize = winSize;
	this->setContentSize(CCSizeMake(960,640));
	this->setPosition(CCPointZero);
	this->setAnchorPoint(CCPointZero);

	//loadSlipItems();
	loadButtonItems();

	this->setIsTouchEnabled(false);

	return true;
}

void SoundSetLayer::loadSlipItems()
{
	CCSize layerSize = this->getContentSize();
	/*background sound*/
	// back
	char path[64] = "setting/sound/probg.png";
	
	_pSoundVolumeProgressBack = new SpriteNode();
	_pSoundVolumeProgressBack->initWithSpriteFrameName(path);
	CCSize size = _pSoundVolumeProgressBack->getContentSize();
	_progressSize = size;
	if (_pSoundVolumeProgressBack)
	{
		//_pSoundVolumeProgressBack->initWithFile(path,CCPointZero,CCPointZero,CCSizeMake(POSX(LENGTH_VOL_PROGRESS),POSX(size.height)));
		_pSoundVolumeProgressBack->setAnchorPoint(ccp(0,0));
		_pSoundVolumeProgressBack->setPosition(ccp(POSX(-size.width/2),POSX(80)));
		//_pSoundVolumeProgressBack->setPosition(ccp(POSX(layerSize.width/2),POSX(layerSize.height*23/30)));
		this->addChild(_pSoundVolumeProgressBack,0,TAG_SOUND_PROGRESS_BG);
		_pSoundVolumeProgressBack->release();
	}

	// progress
	_pSoundVolumeProgress = CCProgressTimer::progressWithFile("assets/ui/setting/sound/pro.png");
	if (_pSoundVolumeProgress)
	{
		_pSoundVolumeProgress->setType(CCProgressTimerType(2));
		_pSoundVolumeProgress->setAnchorPoint(ccp(0,0));
		_pSoundVolumeProgress->setPosition(CCPointZero);
		_pSoundVolumeProgressBack->addChild(_pSoundVolumeProgress,0,TAG_PROGRESS);
		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.5f, _fCurSoundVolume); 
		_pSoundVolumeProgress->runAction(pProgressTo);
		_pSoundVolumeProgress->setPercentage(_fCurSoundVolume);
	}

	// button
	_pSoundVolumeSlipButton = new SpriteNode();
	if (_pSoundVolumeSlipButton)
	{
		_pSoundVolumeSlipButton->initWithSpriteFrameName("setting/sound/btn.png");
		_pSoundVolumeSlipButton->setPosition(ccp(size.width - size.width * _fCurSoundVolume ,0));
		_spriteSoundBtnPoint = _pSoundVolumeSlipButton->getPosition();
		_pSoundVolumeProgressBack->addChild(_pSoundVolumeSlipButton,1,TAG_SLIP_BTN);
		_pSoundVolumeSlipButton->release();
	}

	/*effect sound*/
	// back
	_pEffectVolumeProgressBack = new SpriteNode();
	if (_pEffectVolumeProgressBack)
	{
		_pEffectVolumeProgressBack->initWithSpriteFrameName(path);
		_pEffectVolumeProgressBack->setAnchorPoint(ccp(0,0));
		_pEffectVolumeProgressBack->setPosition(CCPointZero);
		_pEffectVolumeProgressBack->setPosition(ccp(POSX(-size.width/2),POSX(-80)));
		this->addChild(_pEffectVolumeProgressBack,0,TAG_EFFECT_PROGRESS_BG);
		_pEffectVolumeProgressBack->release();
	}

	// progress
	_pEffectVolumeProgress = CCProgressTimer::progressWithFile("assets/ui/setting/sound/pro.png");
	if (_pEffectVolumeProgress)
	{
		_pEffectVolumeProgress->setType(CCProgressTimerType(2));
		_pEffectVolumeProgress->setAnchorPoint(ccp(0,0));
		_pEffectVolumeProgressBack->addChild(_pEffectVolumeProgress,0,TAG_PROGRESS);
		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.5f, _fCurEffectVolume); 
		_pEffectVolumeProgress->runAction(pProgressTo);
		_pEffectVolumeProgress->setPercentage(_fCurEffectVolume);
	}

	// button
	_pEffectVolumeSlipButton = new SpriteNode();
	if (_pEffectVolumeSlipButton)
	{
		_pEffectVolumeSlipButton->initWithSpriteFrameName("setting/sound/btn.png");
		_pEffectVolumeSlipButton->setPosition(ccp(size.width - size.width * _fCurEffectVolume ,0));
		_spriteSoundBtnPoint = _pEffectVolumeSlipButton->getPosition();
		_pEffectVolumeProgressBack->addChild(_pEffectVolumeSlipButton,1,TAG_SLIP_BTN);
		_pEffectVolumeSlipButton->release();
	}
}

void SoundSetLayer::loadButtonItems()
{
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pMenuSoundItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(SoundSetLayer::clickSoundButton));
			CCMenu * pMenuSound = CCMenu::menuWithItem(pMenuSoundItem);
			pMenuSound->setTouchLayer(TLE::WindowLayer_Setting);
			pMenuSound->setPosition(ccp(POSX(_progressSize.width/2 + 80),POSX(85)));
			this->addChild(pMenuSound);
		}
	}

	std::string textS = ( getIsSoundOpen() ) ? ("MSC002") : ("MSC001");
	CCLabelTTF * pLabTextS = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(textS).c_str(),g_sSimHeiFont,POSX(20));
	pLabTextS->setColor(ccc3(255,215,0));
	pLabTextS->setPosition(ccp(POSX(_progressSize.width/2 + 80),POSX(85)));
	this->addChild(pLabTextS,1,TAG_SOUND_BTN);

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pMenuEffectItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(SoundSetLayer::clickEffectButton));
			CCMenu * pMenuEffect = CCMenu::menuWithItem(pMenuEffectItem);
			pMenuEffect->setTouchLayer(TLE::WindowLayer_Setting);
			pMenuEffect->setPosition(ccp(POSX(_progressSize.width/2 + 80),POSX(-75)));
			this->addChild(pMenuEffect);
		}
	}

	std::string textE = ( getIsSoundOpen() ) ? ("MSC004") : ("MSC003");
	CCLabelTTF * pLabTextE = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(textE).c_str(),g_sSimHeiFont,POSX(20));
	pLabTextE->setColor(ccc3(255,215,0));
	pLabTextE->setPosition(ccp(POSX(_progressSize.width/2 + 80),POSX(-75)));
	this->addChild(pLabTextE,1,TAG_EFFECT_BTN);

	
}

void SoundSetLayer::clickSoundButton(CCObject * pSender)
{
	SoundManager * pSoundManager = SoundManager::Instance();

	setIsSoundOpen(!getIsSoundOpen());

	int mapID = RoleManage::Instance()->roleInfo()->playerBaseInfo.GetmapId();

	if (getIsSoundOpen())
	{
		pSoundManager->setIsSoundOpen(true);
		if (_nCurMapID != mapID)
		{
			pSoundManager->roleMapChangeHandler(true);
			pSoundManager->_pShareEngine->pauseBackgroundMusic();
		}
		pSoundManager->_pShareEngine->resumeBackgroundMusic();
		pSoundManager->_pShareEngine->setBackgroundMusicVolume(pSoundManager->getBackSoundVolValue());
	}
	else
	{
		//SoundManager::Instance()->_pShareEngine->stopBackgroundMusic();
		pSoundManager->_pShareEngine->pauseBackgroundMusic();
		pSoundManager->setIsSoundOpen(false);
		//SoundManager::Instance()->_pShareEngine->setBackgroundMusicVolume(0);
	}

	_nCurMapID = mapID;

	std::string textS = ( getIsSoundOpen() ) ? ("MSC002") : ("MSC001");
	CCLabelTTF * pLabText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(textS).c_str(),g_sSimHeiFont,POSX(20));
	pLabText->setColor(ccc3(255,215,0));
	pLabText->setPosition(ccp(POSX(_progressSize.width/2 + 80),POSX(85)));
	if (this->getChildByTag(TAG_SOUND_BTN))
	{
		this->removeChildByTag(TAG_SOUND_BTN,true);
	}
	this->addChild(pLabText,1,TAG_SOUND_BTN);

	pSoundManager->playButtonEffectSound();
}

void SoundSetLayer::clickEffectButton(CCObject * pSender)
{
	setIsEffectOpen(!getIsEffectOpen());
	if (getIsEffectOpen())
	{
		SoundManager::Instance()->setIsEffectOpen(true);
		//SoundManager::Instance()->_pShareEngine->setEffectsVolume(SoundManager::Instance()->getEffectVolValue());
	}
	else
	{
		SoundManager::Instance()->_pShareEngine->stopAllEffects();
		SoundManager::Instance()->setIsEffectOpen(false);
		//SoundManager::Instance()->_pShareEngine->setEffectsVolume(0);
	}

	std::string textE = ( getIsEffectOpen() ) ? ("MSC004") : ("MSC003");
	CCLabelTTF * pLabText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(textE).c_str(),g_sSimHeiFont,POSX(20));
	pLabText->setColor(ccc3(255,215,0));
	pLabText->setPosition(ccp(POSX(_progressSize.width/2 + 80),POSX(-75)));
	if (this->getChildByTag(TAG_EFFECT_BTN))
	{
		this->removeChildByTag(TAG_EFFECT_BTN,true);
	}
	this->addChild(pLabText,1,TAG_EFFECT_BTN);

	SoundManager::Instance()->playButtonEffectSound();
}

void SoundSetLayer::registerWithTouchDispatcher(void)
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Setting, true);
}

bool SoundSetLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	_preTouchPoint = touchPoint;
	if (!this->getChildByTag(TAG_SOUND_PROGRESS_BG)||(!this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_PROGRESS))){return false;}
	if (!this->getChildByTag(TAG_SOUND_PROGRESS_BG)||(!this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN))){return false;}
	if (!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)||(!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_PROGRESS))){return false;}
	if (!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)||(!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN))){return false;}
	
	CCPoint spriteSoundPoint		= getScreenPos((CCNode *)this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_PROGRESS));
	CCPoint spriteSoundBtnPoint		= getScreenPos((CCNode *)this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN));
	CCPoint spriteEffectPoint		= getScreenPos((CCNode *)this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_PROGRESS));
	CCPoint spriteEffectBtnPoint	= getScreenPos((CCNode *)this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN));

	

	if (CCRect::CCRectContainsPoint(CCRectMake(spriteSoundPoint.x,spriteSoundPoint.y,_progressSize.width,_progressSize.height),touchPoint))
	{
		setTouchSoundState(STAT_SOUND_0);
		if (CCRect::CCRectContainsPoint(CCRectMake(spriteSoundBtnPoint.x-20,spriteSoundBtnPoint.y-20,40,40),touchPoint))
		{
			setTouchSoundState(STAT_SOUND_1);
		}
		

		CCPoint pos = this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		float tx = touchPoint.x-spriteSoundBtnPoint.x + pos.x;
		if (tx<0){tx = 0;	}
		if (tx>_progressSize.width){tx = _progressSize.width;	}
		this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)
			->setPosition(ccp(tx,0));
		pos = this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		_spriteSoundBtnPoint = pos;
		_fCurSoundVolume = ((float)_progressSize.width -(float)(pos.x)) / (float)_progressSize.width;

		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.5f, _fCurSoundVolume); 
		_pSoundVolumeProgress->runAction(pProgressTo);
		_pSoundVolumeProgress->setPercentage(_fCurSoundVolume);
		SoundManager::Instance()->setBackSoundvolume(1-_fCurSoundVolume);
	}

	if (CCRect::CCRectContainsPoint(CCRectMake(spriteEffectPoint.x,spriteEffectPoint.y,_progressSize.width,_progressSize.height),touchPoint))
	{
		setTouchEffectState(STAT_EFFECT_0);
		if (CCRect::CCRectContainsPoint(CCRectMake(spriteEffectBtnPoint.x-20,spriteEffectBtnPoint.y-20,40,40),touchPoint))
		{
			setTouchEffectState(STAT_EFFECT_1);
		}


		CCPoint pos = this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		float tx = touchPoint.x-spriteEffectBtnPoint.x + pos.x;
		if (tx<0){tx = 0;	}
		if (tx>_progressSize.width){tx = _progressSize.width;	}
		this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)
			->setPosition(ccp(tx,0));
		pos = this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		_spriteEffectBtnPoint = pos;
		_fCurEffectVolume = ((float)_progressSize.width -(float)(pos.x)) / (float)_progressSize.width;

		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.5f, 1-_fCurEffectVolume); 
		_pEffectVolumeProgress->runAction(pProgressTo);
		_pEffectVolumeProgress->setPercentage(1-_fCurEffectVolume);
		SoundManager::Instance()->setEffectVolume(1-_fCurEffectVolume);
	}
	return true;
}

void SoundSetLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));

	if (!this->getChildByTag(TAG_SOUND_PROGRESS_BG)||(!this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_PROGRESS))){return;}
	if (!this->getChildByTag(TAG_SOUND_PROGRESS_BG)||(!this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN))){return;}
	if (!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)||(!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_PROGRESS))){return;}
	if (!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)||(!this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN))){return;}

	CCPoint spriteSoundPoint		= getScreenPos((CCNode *)this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_PROGRESS));
	CCPoint spriteSoundBtnPoint		= getScreenPos((CCNode *)this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN));
	CCPoint spriteEffectPoint		= getScreenPos((CCNode *)this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_PROGRESS));
	CCPoint spriteEffectBtnPoint	= getScreenPos((CCNode *)this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN));
	
	if (getTouchSoundState() == STAT_SOUND_1)
	{
		CCPoint pos = this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		float tx = _spriteSoundBtnPoint.x+touchPoint.x - _preTouchPoint.x;
		if (tx<0){tx = 0;	}
		if (tx>_progressSize.width){tx = _progressSize.width;	}
		this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)
			->setPosition(ccp(tx,0));
		pos = this->getChildByTag(TAG_SOUND_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		_fCurSoundVolume = ((float)_progressSize.width -(float)(pos.x)) / (float)_progressSize.width;

		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.5f, _fCurSoundVolume); 
		_pSoundVolumeProgress->runAction(pProgressTo);
		_pSoundVolumeProgress->setPercentage(_fCurSoundVolume);
		SoundManager::Instance()->setBackSoundvolume(1-_fCurSoundVolume);
		setTouchSoundState(STAT_SOUND_0);
	}

	if (getTouchEffectState() == STAT_EFFECT_1)
	{
		CCPoint pos = this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		float tx = _spriteSoundBtnPoint.x+touchPoint.x - _preTouchPoint.x;
		if (tx<0){tx = 0;	}
		if (tx>_progressSize.width){tx = _progressSize.width;	}
		this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)
			->setPosition(ccp(tx,0));
		pos = this->getChildByTag(TAG_EFFECT_PROGRESS_BG)->getChildByTag(TAG_SLIP_BTN)->getPosition();
		_fCurEffectVolume = ((float)_progressSize.width -(float)(pos.x)) / (float)_progressSize.width;

		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.5f, _fCurEffectVolume); 
		_pEffectVolumeProgress->runAction(pProgressTo);
		_pEffectVolumeProgress->setPercentage(_fCurEffectVolume);
		SoundManager::Instance()->setEffectVolume(1-_fCurEffectVolume);
		setTouchEffectState(STAT_EFFECT_0);
	}
}