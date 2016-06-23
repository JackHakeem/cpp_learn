#include "LiveThing.h"
#include "NPCChat.h"
#include "utils/flash/TweenLite.h"
#include "CCProgressTimer.h"
#include "utils/ScaleUtil.h"
#include "Player.h"
#include "utils/effect/FightEffectGroup.h"
#include "model/scene/vo/BuffTypeVo.h"
#include "utils/EffectHelps.h"

LiveThing::LiveThing()
{
	hasDead = false;
	nameY = 135.0f;
	_level = 0;
	_hp = 0;
	_maxHp = 0;
	_mp = 0;
	_maxHp = 100.0f;
	_maxMp = 100.0f;
	_energy = 0;
	_range = 3;
	_showHP = 0;
	skill1 = 0;
	skill2 = 0;
	skill3 = 0;
	//_shadow = NULL;
	_voice = 0;
	_npcChat = 0;
	_mPercentage = 0.0f;
// 	_pHPBarProgressTimer = 0;
// 	_pHPBarProgressTimer1 = 0;
	//_pHPLayer = 0;
	arraySeat = -1;
	livingMovieClip = NULL;

	configMC();
	loadHPMPBar();

	m_fStepCounter = 0;//keving
	m_iStepState = StepState_idle;//keving

	
	schedule (schedule_selector (LiveThing::step), 0.1f);//keving

}
LiveThing::LiveThing(int hp, int maxhp, int mp, int maxmp)
{
	hasDead = false;
	nameY = 135.0f;
	_level = 0;
	_hp = hp;
	_maxHp = maxhp;
	_mp = mp;
	_maxMp = maxmp;
	_energy = 0;
	_range = 3;
	_showHP = 0;
	skill1 = 0;
	skill2 = 0;
	skill3 = 0;
	//_shadow = NULL;
	_voice = 0;
	_npcChat = 0;
	_mPercentage = 0.0f;
	// 	_pHPBarProgressTimer = 0;
	// 	_pHPBarProgressTimer1 = 0;
	//_pHPLayer = 0;
	arraySeat = -1;
	livingMovieClip = NULL;

	configMC();
	loadHPMPBar();

	m_fStepCounter = 0;//keving
	m_iStepState = StepState_idle;//keving


	schedule (schedule_selector (LiveThing::step), 0.1f);//keving
}
LiveThing::~LiveThing()
{
	//livingMovieClip->dispose(true);
	//CC_SAFE_DELETE( _pHPLayer );
	//CC_SAFE_DELETE( _pHPBarProgressTimer );
	//CC_SAFE_DELETE( _pHPBarProgressTimer1 );
	//CC_SAFE_DELETE( _npcChat );
	//CC_SAFE_DELETE( _shadow );
	//CC_SAFE_DELETE( livingMovieClip );
}

int LiveThing::level()
{
	return _level;
}

void LiveThing::level(int lv)
{
	_level = lv;
}

int LiveThing::hp()
{
	return _hp;
}

void LiveThing::hp(int hp)
{
	_hp = hp;
}

int LiveThing::maxHp()
{
	return _maxHp;
}

void LiveThing::maxHp(int mh)
{
	_maxHp = mh;
}

int LiveThing::mp()
{
	return _mp;
}

void LiveThing::mp(int value)
{
	/*if(value>=100 && _mp < 100 && _hp >0)
	{
		var obj:Object =EffectHelps.getSkillEffectMC(EffectHelps.MP_FULL); 
		var __y:int = 0;
		if(obj.offsety!=0)
		{
			__y = nameY + obj.offsety;
		}
		addMC(EffectHelps.MP_FULL,obj.value,0,__y);
	}
	else if(value<100 && _mp>=100)
	{
		removeMC(EffectHelps.MP_FULL);
	}*/

	_mp = value;
}

int LiveThing::maxMp()
{
	return _maxMp;
}

void LiveThing::maxMp(int value)
{
	_maxMp = value;
}

int LiveThing::energy()
{
	return _energy;
}

void LiveThing::endPoint(int value)
{
	_energy = value;
}

int LiveThing::range()
{
	return _range;
}

void LiveThing::range(int value)
{
	_range = value;
}

int LiveThing::showHP()
{
	return _showHP;
}

void LiveThing::showHP(bool value)
{
	_showHP = value;
}

void LiveThing::configMC()
{
	//Doyang 20120713
	CCSprite *pShadow = new CCSprite();
	pShadow->initWithFile("role/icon/shadow.png");
	pShadow->setPosition(ccp(POSX(0), POSX(0)));
	pShadow->setTag(TAG_Shadow);
	this->addChild(pShadow);
	pShadow->release();

	//if(!_shadow)
	//{
	//	//_shadow = new CCSprite();
	//	_shadow = CCSprite::spriteWithFile("role/icon/shadow.png");
	//	//_shadow->init();//kevinz
	//}

	//if(_shadow)
	//{
	//	//_shadow->setPosition(ccp(22.0f, 0));
	//	_shadow->setPosition(ccp(POSX(0), POSX(-4)));
	//	this->addChild(_shadow);
	//	//_shadow->release();//kevinz
	//}

	if ( _npcChat && _npcChat->getParent())//jae change //LH
	{
		this->removeChild( _npcChat, true );
		if (_npcChat)
		{
			_npcChat->release();
		}
	}
	
	_npcChat = new NPCChat(1);

	_npcChat->setPosition(ccp(-30,200));
	this->addChild((CCNode *)_npcChat,1);
	_npcChat->release();//kevinz
	//CC_SAFE_DELETE(_npcChat);
	
	loadDeadRes();
}

void LiveThing::setShadowPos(CCPoint pos)
{
	CCSprite *pShadow = (CCSprite *)this->getChildByTag(TAG_Shadow);
	if (pShadow)
	{
		pShadow->setPosition(pos);
	}
}

CCPoint LiveThing::getShadowPos()
{
	CCPoint pos = ccp(0,0);
	CCSprite *pShadow = (CCSprite *)this->getChildByTag(TAG_Shadow);
	if (pShadow)
	{
		pos = pShadow->getPosition();
	}
	return pos;
}

void LiveThing::loadDeadRes()
{

}
void LiveThing::updateAction(bool repeat)
{
	Element::updateAction(repeat);

	if(poseState && dirState)
	{
		if(livingMovieClip && poseState->_state == SceneConst::MOVE) 
		{
			livingMovieClip->runActionEx(BitmapMovieClip::ACTION_WALK, dirState->state(), repeat);
		}
		else if(livingMovieClip && poseState->_state == SceneConst::STAND)
		{
			livingMovieClip->runActionEx(BitmapMovieClip::ACTION_STAND, dirState->state(), repeat);
		}
		else if(livingMovieClip && poseState->_state == SceneConst::ATTACK)
		{
			livingMovieClip->runActionEx(BitmapMovieClip::ACTION_ATTACK, dirState->state(), repeat);
		}
		else if(livingMovieClip && poseState->_state == SceneConst::HITED)
		{
			livingMovieClip->runActionEx(BitmapMovieClip::ACTION_HIT, dirState->state(), repeat);
		}
		else if(poseState && poseState->_state == SceneConst::DEAD)
		{
			removeAllMC();

			dispatchEvent(SceneConst::DEAD_EVENT, NULL);
			dispatchEvent(SceneConst::REMOVE_PLAYER_DEADBODY_EVENT, NULL);

			_isInteractive = false;
		}
	}
}

ResourceVo* LiveThing::resource()
{
	return &(_res);
}

void LiveThing::resource(ResourceVo& value)
{
	_res = value;
}

void LiveThing::removeDead()
{
	dispatchEvent(SceneConst::REMOVE_PLAYER_DEADBODY_EVENT, NULL);
}

bool LiveThing::toAttack()
{
	return true;
}


bool LiveThing::toHited(bool iscrit) 
{
	float vx;
	float vy; 
	CCPoint pos = getPosition();
	if(this->hp() <= 0)
	{
		float ranger = POSX(80);
		float angle = 30 * 3.14159f / 180.0f;
		vx = ranger * cos(angle);
		vy = ranger * sin(angle);

		if (pos.x > POSX(500.0f))
		{//右下
			vx = pos.x + vx;
			vy = pos.y - vy;
		}
		else
		{//左上
			vx = pos.x - vx;
			vy = pos.y + vy;
		}
		
		m_cBackcall.tarpos = ccp(vx, vy);
		beHitedActionBefore(0,0);
		changeStepState(StepState_beKill);

		this->runAction(cocos2d::CCMoveTo::actionWithDuration(0.5f, ccp(vx, vy)));

		return true;
	}

	int quakeX = POSX(10); 
	float duration = 0.05f;
	int i;
	vx = pos.x;
	vy = pos.y;
	
	int _vx;
	int _vy;
	if(iscrit)
	{
		m_cBackcall.tarpos = ccp(vx, vy);
		beHitedActionBefore(0,0);
		changeStepState(StipState_beCritHited);
		CCActionInterval* acsequ = (CCActionInterval*)(CCSequence::actions(
			cocos2d::CCMoveTo::actionWithDuration(0.05f, ccp(pos.x - quakeX, pos.y)), 
			cocos2d::CCMoveTo::actionWithDuration(0.05f, ccp(pos.x + quakeX, pos.y)), 
			cocos2d::CCMoveTo::actionWithDuration(0.05f, ccp(pos.x - quakeX, pos.y)), 
			cocos2d::CCMoveTo::actionWithDuration(0.05f, ccp(pos.x + quakeX, pos.y)), 
			NULL));
		this->runAction(acsequ);
	}
	else
	{
		if (pos.x > POSX(500.0f))
		{//角色
			_vx = pos.x + POSX(18);
			_vy = pos.y - POSX(12);
		}
		else
		{//怪物
			_vx = pos.x - POSX(18);
			_vy = pos.y + POSX(12);
		}
		m_cBackcall.tarpos = ccp(vx, vy);
		beHitedActionBefore(0,0);
		changeStepState(StepState_beHited);
		this->runAction(cocos2d::CCMoveTo::actionWithDuration(0.3f, ccp(_vx, _vy)));
	}
    
    return true;
}

void LiveThing::toStand()
{
	if(poseState == NULL)
		return;

	poseState->state(SceneConst::STAND);
	//bitmapMovieClip.scaleX = dirState.scale;
	if(poseState->_isChanged)
	{
		update();
	}
}

void LiveThing::beHitedActionBefore(CCNode* n, void* data)//kevine
{
	this->stopAllActions();
	if (!poseState)
		return;
	poseState->state(SceneConst::HITED);
	update(true);
//	this->runAction();
}

void LiveThing::beHitedActionAfter(HitData data)//kevine
{
	if (hp() == 0)
		data.isDead = true;

	if (data.isDead == true)
	{//死去
		this->setIsVisible(false);
	}
	else
	{//受击还没死
		setPosition(ccp(data.vx, data.vy));
		if(data.isDead)
		{
			setIsVisible(false);
		}	
		if(poseState == 0)
		{
			return;
		}
			
		poseState->state(SceneConst::STAND);
		update();
	}
}

void LiveThing::onTweenComplete(CCNode* n, void* data)
{
	if(!data)
		return;

	struct Data
	{
		float vx;
		float vy;
		bool isDead;
		Data()
		{
			isDead = false;
			vx = 0;
			vy = 0;
		}
	};
	Data* d = (Data*)data;
	setPosition(ccp(d->vx, d->vy));
	if(d->isDead)
	{
		setIsVisible(false);
	}
}

bool LiveThing::has0hp()
{
	return _hp == 0;
}

void LiveThing::addMC(int type, BitmapMovieClip* effectMC ,int vx, int vy)
{
	std::map<int, BitmapMovieClip>::iterator iter = _buffList.find(type);
	if(iter == _buffList.end())
	{
		BitmapMovieClip data;
		data = *effectMC;
		data._x = vx;
		data._y = vy;
		_buffList.insert(make_pair(type, data));
		addChild(&data);
		data.runActionEx(0, 1);
	}
	else
	{
		iter->second._x = vx;
		iter->second._y = vx;
		iter->second.runActionEx(0, 1);
	}
}

BitmapMovieClip* LiveThing::getMC(int type)
{
	std::map<int, BitmapMovieClip>::iterator iter = _buffList.find(type);
	if(iter != _buffList.end())
		return &(iter->second);

	return NULL;
}

void LiveThing::removeAllMC()
{
	std::map<int, BitmapMovieClip>::iterator iter = _buffList.begin();
	for(; iter != _buffList.end(); ++iter)
	{
		removeMC(iter->first);
	}
}

void LiveThing::removeMC(int type, bool clean)
{
	std::map<int, BitmapMovieClip>::iterator iter = _buffList.find(type);
	if(iter != _buffList.end())
	{
		if(iter->second.getParent() != NULL)
			removeChild(&(iter->second), clean);
		iter->second.dispose(clean);
	}
	_buffList.erase(iter);
}

bool LiveThing::isLeader()
{
	return false;
}

void LiveThing::dispose()
{
	Element::dispose();
	if(livingMovieClip)
		livingMovieClip->stopActionEx();

	//Doyang 20120713
	if(_npcChat && _npcChat->getParent())
		_npcChat->removeFromParentAndCleanup(true);
	CCLayer *pHPLayer = (CCLayer *) this->getChildByTag(TAG_BLOOD);
	if(pHPLayer)
	{
		pHPLayer->removeChildByTag(TAG_BLOOD_BG_ICON, true);
		pHPLayer->removeChildByTag(TAG_BLOOD_ICON_1, true);
		pHPLayer->removeChildByTag(TAG_BLOOD_ICON_2, true);
	}
	this->removeChildByTag(TAG_BLOOD, true);
	unschedule(schedule_selector (LiveThing::step));
}

void LiveThing::toShade(bool value)
{}

void LiveThing::speak(struct _VOICE_ *voice)
{
	_voice = voice;
	updateInfo();
}

void LiveThing::shutup()
{
	if(_npcChat)
	{
		_npcChat->hideDialog();
		//updateInfo();
	}
}

void LiveThing::updateInfo()
{
	this->Element::updateInfo();
	if(_voice&&_npcChat)
	{
		_npcChat->hideDialog();
		_npcChat->showContent(_voice);
		float fY = _npcChat->getContentSize().height;
		_npcChat->setPositionY(POSX(this->nameY -30)- fY/3);

		// reset player dialog position
		LiveThing * pPlayer = (LiveThing *)_npcChat->getParent();
		if (pPlayer && (pPlayer->type() == PLAYER_TYPE))
		{
			_npcChat->setPositionY(POSX(this->nameY/* + 250*/));
		}
	}
}

void LiveThing::loadHPMPBar()
{
	CCSprite * pHPSpriteBack = new CCSprite();
	if (!pHPSpriteBack->initWithSpriteFrameName("figure/blood_bg.png"))
	{
		pHPSpriteBack->release();
		return;
	}

	CCSprite * pMPSpriteBack = new CCSprite();
	pMPSpriteBack->initWithSpriteFrameName("figure/blood_bg.png");

	// HP1
	CCProgressTimer * _pHPBarProgressTimer1 = new CCProgressTimer();
	if (_pHPBarProgressTimer1)
	{	
		if (_pHPBarProgressTimer1->initWithFile("assets/ui/figure/blood2.png"))
		{
			_pHPBarProgressTimer1->setPercentage(_mPercentage);
			_pHPBarProgressTimer1->setType(CCProgressTimerType(2));
			CCProgressTo * pProgressTo = 0; 
			if (_hp != 0 && _hp != _maxHp && _maxHp != 0)
			{
				float percentHP = 100.0f - (float)_hp * 100.0f / (float)_maxHp;
				percentHP = (percentHP < 1.0f) ? 1.0f : percentHP;
				percentHP = (percentHP >= 100.0f) ? 99.0f : percentHP;
				pProgressTo = CCProgressTo::actionWithDuration(0.2f, percentHP); 
			}
			else
			{
				pProgressTo = CCProgressTo::actionWithDuration(0.2f, 1.0f); 
			}
			_pHPBarProgressTimer1->runAction(pProgressTo);
		}
	}

	// HP2
	CCProgressTimer * _pHPBarProgressTimer2 = new CCProgressTimer();
	if (_pHPBarProgressTimer2)
	{	
		if (_pHPBarProgressTimer2->initWithFile("assets/ui/figure/blood1.png"))
		{
			_pHPBarProgressTimer2->getSprite()->setColor(ccc3(0,255,0));
			_pHPBarProgressTimer2->setPercentage(_mPercentage);
			_pHPBarProgressTimer2->setType(CCProgressTimerType(2));
			CCProgressTo * pProgressTo = 0;
			if (_hp != 0 && _hp != _maxHp && _maxHp != 0)
			{
				float percentHP = 100.0f - (float)_hp * 100.0f / (float)_maxHp;
				percentHP = (percentHP < 1.0f) ? 1.0f : percentHP;
				percentHP = (percentHP >= 100.0f) ? 99.0f : percentHP;
				pProgressTo = CCProgressTo::actionWithDuration(0.2f, percentHP); 
			}
			else
			{
				pProgressTo = CCProgressTo::actionWithDuration(0.2f, 1.0f); 
			}
			_pHPBarProgressTimer2->runAction(pProgressTo);
		}
	}

	// MP


	CCProgressTimer * _pMPBarProgressTimer = new CCProgressTimer();
	if (_pMPBarProgressTimer )
	{	
		if (_pMPBarProgressTimer->initWithFile("assets/ui/figure/mp1.png"))
		{
			//_pMPBarProgressTimer->getSprite()->setColor(ccc3(0,0,255));
			_pMPBarProgressTimer->setPercentage(99.9f);
			_pMPBarProgressTimer->setType(CCProgressTimerType(2));

			CCProgressTo * pProgressTo = 0;
			if (_mp != 0 /*&& _mp != _maxMp&& _maxMp != 0*/ )
			{
				float percentMP = 100.0f - (float)_mp * 100.0f / _maxMp;
				percentMP = (percentMP < 1.0f) ? 1.0f : percentMP;
				percentMP = (percentMP >= 100.0f) ? 99.0f : percentMP;
				pProgressTo = CCProgressTo::actionWithDuration(0.2f, percentMP); 

					
			}
			else
			{
				pProgressTo = CCProgressTo::actionWithDuration(0.2f, 99); 
			}

			_pMPBarProgressTimer->runAction(pProgressTo);
  			
		}
	}
	//怒气effect
	{
		if (_mp >= 100.f)
		{//欲加怒气特效
			if (!this->getChildByTag(BuffTypeVo::NUQI))
			{
				BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC(204, 0.1f);
				if (/*this->getParent() && */effectMC )
				{
					effectMC->setPosition(ccpAdd(ccp(POSX(0), POSX(70)), ccp(0, 0)));


					this->addChild( effectMC, -1, BuffTypeVo::NUQI );//渲染在脚底下
					//effectMC->release();  //Kenfly 20121110
				
					effectMC->runActionPVRCommonRepeat();					
				}
				CC_SAFE_RELEASE(effectMC);  //Kenfly 20121110
			}
		}
		//else只需加不需去除
		//{//欲除去怒气特效
		//	if ( hiter && hiter->getParent())
		//	{
		//		if (hiter->getChildByTag(BuffTypeVo::NUQI))
		//			hiter->removeChildByTag(BuffTypeVo::NUQI, true);
		//	}
		//}
	
	}

	LayerNode * pHPLayer = new LayerNode();
	if (pHPLayer)
	{
		pHPLayer->init();
		if (pHPSpriteBack)
		{
			pHPLayer->addChild(pHPSpriteBack,10,TAG_BLOOD_BG_ICON);
			pHPSpriteBack->release(); // LH0707LEAK
		}
		if (pMPSpriteBack)
		{
			CCPoint pos = pHPSpriteBack->getPosition();
			pMPSpriteBack->setPosition(ccp(pos.x,pos.y-POSX(10)));
			pMPSpriteBack->setScaleY(0.6);
			pHPLayer->addChild(pMPSpriteBack,10,TAG_MP_BG_ICON);
			pMPSpriteBack->release(); // LH0707LEAK
		}
		if (_pHPBarProgressTimer1)
		{
			pHPLayer->addChild(_pHPBarProgressTimer1,12,TAG_BLOOD_ICON_1);
			_pHPBarProgressTimer1->release(); // LH0707LEAK
		}
		if (_pHPBarProgressTimer2)
		{
			pHPLayer->addChild(_pHPBarProgressTimer2,13,TAG_BLOOD_ICON_2);
			_pHPBarProgressTimer2->release(); // LH0707LEAK
		}
		if (_pMPBarProgressTimer)
		{
			CCPoint pos = pMPSpriteBack->getPosition();
			_pMPBarProgressTimer->setPosition(pos);
			_pMPBarProgressTimer->setScaleY(0.6);
			pHPLayer->addChild(_pMPBarProgressTimer,14,TAG_MP_ICON);
			_pMPBarProgressTimer->release(); // LH0707LEAK
		}

		pHPLayer->setContentSize(pHPSpriteBack->getContentSize());
		pHPLayer->setIsVisible(false);
		pHPLayer->setPosition(ccp(POSX(0.0f), POSX(this->nameY + 30)));
		this->addChild(pHPLayer,0,TAG_BLOOD);
		pHPLayer->release(); // LH0707LEAK
	}
}

void LiveThing::updateHPBar(float time,float percent)
{
	_mPercentage = percent;

	CCProgressTo * pProgressTo2 = CCProgressTo::actionWithDuration(time, percent);
	if(this->getChildByTag(TAG_BLOOD) && this->getChildByTag(TAG_BLOOD)->getChildByTag(TAG_BLOOD_ICON_2))
	{

		this->getChildByTag(TAG_BLOOD)->getChildByTag(TAG_BLOOD_ICON_2)->runAction(pProgressTo2);
	}

	float dt = (percent < 99.0f) ? 0.8f : 0.3f;
	CCProgressTo * pProgressTo1 = CCProgressTo::actionWithDuration(time+dt, percent); 
	if(this->getChildByTag(TAG_BLOOD) && this->getChildByTag(TAG_BLOOD)->getChildByTag(TAG_BLOOD_ICON_1))
	{
		this->getChildByTag(TAG_BLOOD)->getChildByTag(TAG_BLOOD_ICON_1)->runAction(pProgressTo1);
	}
}

void LiveThing::updateHPBarColor(ccTime dt)
{
	if (_mPercentage <= 1.0f) {_mPercentage = 0.0f;}
	else if (_mPercentage >= 99.0f) {_mPercentage = 100.0f;}
}

void LiveThing::updateMPBar(float time,float percent)
{
	CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(time, percent);
	if(this->getChildByTag(TAG_BLOOD) && this->getChildByTag(TAG_BLOOD)->getChildByTag(TAG_MP_ICON))
	{

		this->getChildByTag(TAG_BLOOD)->getChildByTag(TAG_MP_ICON)->runAction(pProgressTo);
	}
}

void LiveThing::changeStepState(int stepState)//keving
{
	m_fStepCounter = 0.0f;
	m_iStepState = stepState;
}

void LiveThing::step(ccTime dt)//keving
{
	switch (m_iStepState)
	{
	case StepState_idle:
		{}
		break;
	case StipState_beCritHited:
		{
			m_fStepCounter += dt;
			if (m_fStepCounter >= 0.4f)
			{
				changeStepState(StepState_idle);

				HitData d;
				d.vx = m_cBackcall.tarpos.x;
				d.vy = m_cBackcall.tarpos.y;

				beHitedActionAfter(d);

			}
		}
		break;
	case StepState_beHited:
		{
			m_fStepCounter += dt;
			if (m_fStepCounter >= 0.5f)
			{
				changeStepState(StepState_idle);

				HitData d;
				d.vx = m_cBackcall.tarpos.x;
				d.vy = m_cBackcall.tarpos.y;

				beHitedActionAfter(d);

			}
		}
		break;
	case StepState_beKill:
		{
			m_fStepCounter += dt;
			if (m_fStepCounter >= 0.8f)
			{
				changeStepState(StepState_idle);

				HitData d;
				d.vx = m_cBackcall.tarpos.x;
				d.vy = m_cBackcall.tarpos.y;

				beHitedActionAfter(d);

			}
		}
		break;
	default:
		break;
	}
}

//Begin Kenfly 20121025
void LiveThing::playSelectedEffect()
{
	CCSprite* pSprite = (CCSprite*)livingMovieClip->getPlayerSprite();
	if (pSprite)
	{
		CCActionInterval* pDarkAction = CCTintTo::actionWithDuration(0.1f, 255, 255, 0);
		CCActionInterval* pBrightAction = CCTintTo::actionWithDuration(0.1f, 255, 255, 255);
		if (pDarkAction && pBrightAction)
			pSprite->runAction(CCSequence::actions(pDarkAction, pBrightAction, 0));
	}
}
//End Kenfly