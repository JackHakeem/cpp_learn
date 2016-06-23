#include "ActionHandler.h"
#include "utils/loader/AnimationManager.h"
#include "BattleEnginer.h"
#include "control/AppFacade.h"
#include "model/skill/SkillManager.h"
#include "utils/EffectHelps.h"
#include "manager/ViewManager.h"
#include "model/scene/vo/BuffTypeVo.h"
#include "utils/effect/FightEffectGroup.h"
#include "cocos2d.h"
#include "manager/GlobalManage.h"
#include "manager/sound/SoundManager.h"
#include "BaseType.h"
#include "view/scene/components/FightSpecialFontField.h"
#include "model/scene/vo/BuffStateVo.h"
#include "model/com/ResourceManage.h"
#include "utils/Utils.h"
USING_NS_CC;


static ActionHandler *_instance;

ActionHandler* ActionHandler::getInstance()
{
	if(NULL == _instance)
	{
		_instance = new ActionHandler();
	}
	return _instance;
}

static void Release()
{
	if(NULL != _instance)
	{
		delete _instance;
	}
	_instance = NULL;
}

void ActionHandler::type(int value)
{
	_type = value;
}

void ActionHandler::playOneAction(SCMD132::SCMD132Node1 action)
{
	//kevinh cocos2d::CCLog("---ActionHandler::playOneAction");
	if(!ViewManager::getInstance()->_fightScene)
		return;

	this->_action = action;

	if(this->_action.g_hiteds.empty())
	{
		// No target
		this->completeHandler();
		return;
	}

	
	SCMD132::SCMD132Node2 firstHited = _action.g_hiteds.front();
  
	// Attacker
	m_attacker = ViewManager::getInstance()->_fightScene->getLiveThing(_type, _action.a_attackId);

	// The first attacker
	m_firstHiter = ViewManager::getInstance()->_fightScene->getLiveThing(_type, firstHited.a_hitedId);
	// Skills action

	m_skill = SkillManager::Instance()->getSkill(action.c_skill);//kevinyy action.c_skill 409

	if(NULL == m_attacker|| NULL == m_firstHiter)
	{
		// Skills, the attacker, an attacker has a null
		this->completeHandler();
		return;
	}

	// Play the animation
	this->execute();
}

void ActionHandler::execute()
{
	switchUpdate(true);
	//_permitRun = true;

	//FightEffect* skillEff = createSkillEff();
	//if ( skillEff )
	//{
	//	FightEffectGroup::Instance()->addTween( skillEff, "SkillEffect" );//技能效果
	//}

	////被攻击者被击中后产生的动作（被吸血，mp发生变化等） 
	//FightEffect* laterEff = createLaterEff();
	//if ( laterEff )
	//{
	//	FightEffectGroup::Instance()->addTween(laterEff,"AfterAttackEffect");//攻击后效果
	//}

	//if( canRun() )
	//{
	//	FightEffectGroup::Instance()->registerCallback( callfunc_selector(ActionHandler::completeHandler), this );
	//	FightEffectGroup::Instance()->play();
	//}
}

ActionHandler::ActionHandler()
{
	_permitRun = true;
	_rate = 0;
	m_firstHiter = NULL;
	m_skill = NULL;
	_type = 0;

	_fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	//this->_feGroup = FightEffectGroup::getInstance();
	
	//_stations = Utils.getStations();

	m_attacker = 0;
	m_firstHiter = 0;
	m_skill = 0;

	_rate = 1.0f;
	setFEGS(FEGS_idleStart);
}

void ActionHandler::completeHandler()
{
	// Completing this sub-Action
	//FightLayer::getInstance()->stopActions();
	//kevinh cocos2d::CCLog("-----------------completeHanlder");

	// Stop all of the action
	if(ViewManager::getInstance()->_fightScene)
		ViewManager::getInstance()->_fightScene->stopActions();

	FightEffectGroup::Instance()->stop();
	FightEffectGroup::Instance()->dispose();

	BattleEnginer::getInstance()->nextActions();
}

void ActionHandler::dispose()
{
	     //Stop all of the action
		if(ViewManager::getInstance()->_fightScene)
			ViewManager::getInstance()->_fightScene->stopActions();
	
		FightEffectGroup::Instance()->stop();
		FightEffectGroup::Instance()->dispose();
}

bool ActionHandler::canRun()
{
	return _permitRun;
}


void ActionHandler::soundPlay(ccTime dt)
{
	if (_count == 1)
	{
		if (SoundManager::Instance()->getIsEffectOpen())
		{
			SoundManager::Instance()->playAction(_soundUrl,false);
		}
		CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(ActionHandler::soundPlay),this);
	}
	++_count;
}

void ActionHandler::onStartAttack()
{
	//除去BUFF特效
	if ( m_attacker && m_attacker->getParent())
	{
		if (m_attacker->getChildByTag(BuffTypeVo::XUAN_YUN))
			m_attacker->removeChildByTag(BuffTypeVo::XUAN_YUN, true);
	}

	bool ret = m_attacker->toAttack();

	if(!ret)
	{
		FightEffectGroup::Instance()->completeOneAction();
	}

	// HP Bar handler
	//LiveThing* hiter = ViewManager::getInstance()->_fightScene->getLiveThing(_type, _action.a_attackId);
	HPMPBarHandler(_action.d_attackhp ,_action.e_attackmp, m_attacker);

	// 攻击音效
	
}

void ActionHandler::HPMPBarHandler(float curHP,float curMP,LiveThing * hiter)
{
	// HP
	if (hiter->_maxHp)
	{
		float percentHP =100.0f - (float)(curHP * 100.0f) / hiter->_maxHp;

		//kevinh CCLog("========================================HP percent decries:%f/100.00, MAX %d",percentHP, hiter->_maxHp);

		percentHP = (percentHP < 1.0f) ? 1.0f : percentHP;
		percentHP = (percentHP >= 100.0f) ? 99.0f : percentHP;

		if (percentHP < 99.0f)
		{
			hiter->updateHPBar(DELTA_TIME_BLOOD_CHANGE,percentHP);
		}
		else
		{
			hiter->updateHPBar(0.1f,percentHP);
		}
	}

	// MP
	hiter->_maxMp = 100.0f; // ...
	if (hiter->_maxMp)
	{
		float percentMP =100.0f - (float)(curMP * 100.0f) / hiter->_maxMp;

		//kevinh CCLog("========================================MP percent decries:%f/100.00, MAX %d",percentMP, hiter->_maxMp);

		percentMP = (percentMP < 1.0f) ? 1.0f : percentMP;
		percentMP = (percentMP >= 100.0f) ? 99.0f : percentMP;
		
		hiter->updateMPBar(DELTA_TIME_BLOOD_CHANGE * 2+0.2, percentMP);
	}

	if (curMP >= hiter->_maxMp)
	{//欲加怒气特效
		if (!hiter->getChildByTag(BuffTypeVo::NUQI))
		{
			BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC(204, 0.1f);
			if ( hiter && hiter->getParent() && effectMC )
			{
				effectMC->setPosition(ccpAdd(ccp(POSX(0), POSX(70)), ccp(0, 0)));


				hiter->addChild( effectMC, -1, BuffTypeVo::NUQI );//渲染在脚底下
				effectMC->release();
				
				effectMC->runActionPVRCommonRepeat();					
			}
			else
				CC_SAFE_RELEASE_NULL(effectMC);  //Kenfly 20121110
		}
	}
	else
	{//欲除去怒气特效
		if ( hiter && hiter->getParent())
		{
			if (hiter->getChildByTag(BuffTypeVo::NUQI))
				hiter->removeChildByTag(BuffTypeVo::NUQI, true);
		}
	}
}

void ActionHandler::playSkillEffect(int effectid)
{
	string _soundUrl = "";
	if( effectid != 0 )

	{
		char path[128] = {0};
		sprintf(path,"assets/sound/skill/%d.mp3",effectid);
		_soundUrl.append(path);
	}
	else
	{
		_soundUrl = "assets/sound/skill/1.mp3";
	}
	if (SoundManager::Instance()->getIsEffectOpen())
	{
		SoundManager::Instance()->playAction(_soundUrl,false);
	}
}



void ActionHandler::update(float dt)
{
	switch (getFEGS())
	{
	case FEGS_idleStart:
		{
			intervalCounter+=dt;
			if (intervalCounter >= 1.0f)
			{
				CCLog("SKILL==%d    %d", m_skill->id, m_skill->resId);
				setFEGS(FEGS_shining);
				BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC((m_skill->nameid <= 0)?201:200, 0.07f);//m_skill->resId
				if ( m_attacker && m_attacker->getParent() && effectMC )
				{
					effectMC->setPosition(ccpAdd(ccp(POSX(0), POSX(70)), m_attacker->getPosition()));

					if (!m_attacker->getParent())
					{
						CC_SAFE_RELEASE_NULL(effectMC);
						break;
					}
					m_attacker->getParent()->addChild( effectMC, 1000, 8500 );
					effectMC->release();

					cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(effectMC, callfuncN_selector(BitmapMovieClip::endHandler));//特效的自身删除还是靠自己的回调
					effectMC->runActionPVRCommon( callBack );
				}
				else
					CC_SAFE_RELEASE_NULL(effectMC); // Kenfly 20121110
                
                if (m_attacker->arraySeat >= 9)
                {
                    CCNode* tparant = m_attacker;
                    int i = 0;
                    CCLog("......*****.......begin");
                    while (tparant) {
                        CCLog("%f %f   index=%d", tparant->getPosition().x, tparant->getPosition().y, i++);
                        tparant = tparant->getParent();
                    }
                    CCLog("..................end");
                }
			}
		}break;
	case FEGS_idle:
		{
			intervalCounter+=dt;
			if (intervalCounter >= 0.5f)
			{
				setFEGS(FEGS_shining);
				CCLog("SKILL==%d    %d", m_skill->id, m_skill->resId);
				BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC((m_skill->nameid <= 0)?201:200, 0.07f);//m_skill->resId
				if ( m_attacker && m_attacker->getParent() && effectMC )
				{
					effectMC->setPosition(ccpAdd(ccp(POSX(0), POSX(70)), m_attacker->getPosition()));
					m_attacker->getParent()->addChild( effectMC, 1000, 8501 );
					effectMC->release();

					cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(effectMC, callfuncN_selector(BitmapMovieClip::endHandler));//特效的自身删除还是靠自己的回调
					effectMC->runActionPVRCommon( callBack );
				}
				else
					CC_SAFE_RELEASE_NULL(effectMC); //Kenfly 20121110
                if (m_attacker->arraySeat < 9)
                {
                    CCNode* tparant = m_attacker;
                    int i = 0;
                    CCLog("......*****.......begin");
                    while (tparant) {
                        CCLog("%f %f   index=%d", tparant->getPosition().x, tparant->getPosition().y, i++);
                        tparant = tparant->getParent();
                    }
                    CCLog("..................end");
                }
			}
		}break;
	case FEGS_shining:
		{
			intervalCounter+=dt;
			if (intervalCounter >= 0.3f)
			{
				setFEGS(FEGS_attacking);
				//addchild播放攻击动画
				onStartAttack();
			}			
		}break;
	case FEGS_attacking:
		{
			intervalCounter+=dt;
			float delay = m_attacker->_res.getAttackingMCStartDelay();

			if (intervalCounter >= delay)//攻击动画的第N帧时间
			{
				//addchild播放特效,技能字
				setFEGS(FEGS_MCing);
				//
				BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC(m_skill->resId,  m_skill->acttime);//kevinyy m_skill->resId  m_skill->resId
				if ( m_firstHiter && m_firstHiter->getParent() && effectMC )
				{
					m_firstHiter->getParent()->addChild( effectMC, 1000 );
					effectMC->release();
					cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this, callfuncN_selector(BitmapMovieClip::endHandler));//特效的自身删除还是靠自己的回调
					CCSprite* runAnimation = effectMC->runActionPVRCommon( callBack );
					effectMC->setPosition(getMCPos(m_firstHiter, runAnimation));
                    //skill sound
                    playSkillEffect(m_skill->musid);
				}
				else
					CC_SAFE_RELEASE_NULL(effectMC); //Kenfly 20121110
				//
				//	
				//技能名称 
				if(m_skill->nameid == 0)
				{
					EffectHelps::getSkillNameEx(m_attacker, *m_skill, 0, -50, 0.2*_rate, 0.7*_rate);
				}
				else
				{
					EffectHelps::getSkillNameEx(m_attacker, *m_skill, 0, -50, 0.2*_rate, 0.7*_rate);
				}
			}
		}break;
	case FEGS_MCing:
		{
			intervalCounter+=dt;
            float delay = m_skill->actzhen * m_skill->acttime;
			if (intervalCounter >= delay)//0.2秒
			{
				//addchild播放受击数字,动作
				setFEGS(FEGS_aboutBeHit);

					//播放血 闪避 暴击 
					float hp_delay = 0.4*_rate; // 比技能的delay 0.3快
					float mp_delay = 0.4*_rate;  // 0.3
					float buff_delay = 0.7*_rate;  // 0.9 -> 0.6  关键点 
	
					std::list<SCMD132::SCMD132Node2>::iterator node132_it;

					for ( node132_it = _action.g_hiteds.begin(); node132_it != _action.g_hiteds.end(); node132_it++ )
					{
						SCMD132::SCMD132Node2 hited = *node132_it;
						//if (!g_pGlobalManage->_isInFight){return;}
						LiveThing* hiter = ViewManager::getInstance()->_fightScene->getLiveThing(_type, hited.a_hitedId);
						if( !hiter )
						{
							CCLog("攻击动作: 被攻击者为空");			
							continue;
						}

						//设置血量
						hiter->hp(abs(hited.c_hitedhp));
						// 处理 HP Bar 
						HPMPBarHandler(hited.c_hitedhp ,hited.d_hitedmp, hiter);					
						//做受击动作
						if (hited.e_damage < 0)
						{
							BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC(202, 0.1f);
							if ( hiter && hiter->getParent() && effectMC )
							{
								effectMC->setPosition(ccpAdd(ccp(POSX(0), POSX(70)), hiter->getPosition()));
								hiter->getParent()->addChild( effectMC, 1000, 8502 );
								effectMC->release();

								cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this, callfuncN_selector(BitmapMovieClip::endHandler));//特效的自身删除还是靠自己的回调
								effectMC->runActionPVRCommon( callBack );
							}
							else
								CC_SAFE_RELEASE_NULL(effectMC); //Kenfly 20121110
							hiter->toHited(hited.b_crit);			
						}
						//冒伤害数字
						EffectHelps::getEffectEx(hiter, hited.b_crit==1, hited.e_damage, hited.c_hitedhp, 0, -50, hp_delay*_rate, 0.8*_rate);
						//冒闪避
						if(hited.g_state == BuffStateVo::BATTLE_STATUS_DODGE)
						{
							EffectHelps::getMCNameEffectEx(hiter, FightSpecialFontField::SHANBI, 100, 20, buff_delay*_rate);
						}
						//冒暴击
                        
                        
						//if (hited.b_crit == 1)
						//{
							//EffectHelps::getMCNameEffectEx(hiter, FightSpecialFontField::BAOJI, 100, 20, hp_delay*_rate);
						//}
                         
						if( hited.f_buffType > 0 )
						{
							EffectHelps::addBuffEffectEx(hiter, hited.f_buffType);//hited.f_buffType
						}						
					}
			}
		}break;
	case FEGS_aboutBeHit:
		{
			intervalCounter+=dt;
			if (intervalCounter >= 0.0f)//应该轮询伤害数字队列，都播放完毕则时间到
			{
					//处理反击，怒气改变，躲闪，加血
					std::list<SCMD132::SCMD132Node2>::iterator node132_it2;
					std::list<SCMD132::SCMD132Node3>::iterator node132_it3;
					for ( node132_it2 = _action.g_hiteds.begin(); node132_it2 != _action.g_hiteds.end(); node132_it2++ )
					{
						SCMD132::SCMD132Node2 hited = *node132_it2;
						LiveThing* _hiter = ViewManager::getInstance()->_fightScene->getLiveThing(_type, hited.a_hitedId);
						if( !_hiter )
						{
							CCLog("攻击后产生的动作: 被攻击者2为空");
							continue;
						}

						int num = 1;
						for ( node132_it3 = hited.h_hiteds.begin(); node132_it3 != hited.h_hiteds.end(); node132_it3++ )
						{
							SCMD132::SCMD132Node3 _hited = *node132_it3;

							LiveThing* _hiter3 = ViewManager::getInstance()->_fightScene->getLiveThing(_type, _hited.a_hitedId);
							if( !_hiter )
							{
								CCLog("攻击后产生的动作: 被攻击者3为空");
								continue;
							}

							float later_hp_delay = 0.05 * num ;  // 0.05
							float later_mp_delay = 0.05 * num ;  // 0.05;
							float later_buff_delay = 0.05 * num ; // 0.1;


							//冒伤害数字
							//if (_hited.d_damage != 0)
							EffectHelps::getEffectEx(_hiter3, false, _hited.d_damage, _hited.b_hitedhp, 0, -50, later_hp_delay*_rate, 0.8*_rate);
							//设置血量
							_hiter3->hp(abs(_hited.b_hitedhp));
							// 处理 HP Bar 
							HPMPBarHandler(_hited.b_hitedhp ,_hited.c_hitedmp, _hiter3);	

							if (_hited.d_damage == 0)
							{
								EffectHelps::getMPEffectEx(_hiter3, _hited.c_hitedmp, later_mp_delay*_rate, 0.7*_rate, _hited.e_diffEp);
							}
							else
							{}
							//if(_hited.d_damage == 0){
							//	laterEff.addTween( EffectHelps.getMPEffect(_hiter, _hited.c_hitedmp.value, later_mp_delay*rate, 0.7*rate, true, _hited.e_diffEp));
							//}
							//else{
							//	laterEff.addTween( EffectHelps.getMPEffect(_hiter, _hited.c_hitedmp.value, later_mp_delay*rate, 0.5*rate));
							//}

							if(_hited.g_state == BuffStateVo::BATTLE_STATUS_DODGE)
							{  // 闪避
								EffectHelps::getMCNameEffectEx(_hiter, FightSpecialFontField::SHANBI, 100, 20, 0.6*_rate);
							}

							if( _hited.f_buffType > 0 )
							{ 
								//EffectHelps::addBuffEffectEx(_hiter, 3);//hited.f_buffType
								EffectHelps::addBuffEffectEx(_hiter, _hited.f_buffType);
							}
						}
					}

			//	setFEGS(FEGS_fightEndDelay);
			//	float delay = 0.0f;
				if (BattleEnginer::getInstance()->haveNextEffect())
				{//后面还有特效
					//技能是否是连续攻击动作
					if (m_skill->combo==0)
					{
						switchUpdate(false);
						completeHandler();
						setFEGS(FEGS_attacking);
						onStartAttack();
					}
					else
					{
						switchUpdate(false);
						setFEGS(FEGS_idle);
						completeHandler();			
					}
				}
				else
				{//战斗要完毕了，进入延时阶段
					setFEGS(FEGS_fightEndDelay);
				}

			}
		}break;
	case FEGS_fightEndDelay:
		{
			intervalCounter+=dt;
			if (intervalCounter >= 1.5f)
			{
				//技能是否是连续攻击动作
				if (m_skill->combo==0)
				{
					switchUpdate(false);
					completeHandler();
					setFEGS(FEGS_attacking);
					onStartAttack();
				}
				else
				{
					switchUpdate(false);
					setFEGS(FEGS_idle);
					completeHandler();			
				}
			}
		}
		break;
	default:
		CCLog("BUG:void BattleEnginer::update(float dt) default");
		break;
	}
}

//CC_PROPERTY(int, _FEGS, FEGS)
int ActionHandler::getFEGS()
{
	return _FEGS;
}

void ActionHandler::setFEGS(int value)
{
	_FEGS = value;
	intervalCounter = 0.0f;
	CCLog("void BattleEnginer::setFEGS(int %d)", _FEGS);
}

void ActionHandler::switchUpdate(bool value)
{
	if (value)
		CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(BattleEnginer::update), this, 0.01f, false);
	else
		CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(BattleEnginer::update), this);
}

CCPoint ActionHandler::getMCPos(LiveThing* src, CCSprite* ani)
{
	CCPoint rntPos = ccp(0, 0);
	if (!src || !ani)
		return rntPos;

	ani->setScale(m_skill->scale);

	switch (m_skill->longAttack)
	{
	case 0:
		{}break;
	case 1:
		{
			rntPos = Utils::Instance()->getStationPoint(src->arraySeat);
			rntPos.y += POSX(130.0f);
			
		}break;
	//case 2:
	//	{}break;
	case 3:
		{
			//(src->arraySeat >= 9)?ani->setRotation(10.0f):ani->setRotation(190.0f);
			ani->setRotation(6.0f);
			
			switch (src->arraySeat)
			{
			case 0:case 1:case 2:
				rntPos = Utils::Instance()->getStationPoint(1);
				break;
			case 3:case 4:case 5:
				rntPos = Utils::Instance()->getStationPoint(4);
				break;
			case 6:case 7:case 8:
				rntPos = Utils::Instance()->getStationPoint(7);
				break;
			case 9:case 10:case 11:
				rntPos = Utils::Instance()->getStationPoint(10);
				break;
			case 12:case 13:case 14:
				rntPos = Utils::Instance()->getStationPoint(13);
				break;
			case 15:case 16:case 17:
				rntPos = Utils::Instance()->getStationPoint(16);
				break;
			}	
			rntPos.y += POSX(90.0f);
			if (src->arraySeat >= 9)
				rntPos.y += POSX(30.0f);
		}break;
	case 4:
		{
			(src->arraySeat >= 9)?ani->setRotation(10.0f):ani->setRotation(190.0f);
			
			switch (src->arraySeat)
			{
			case 0:case 3:case 6:
				rntPos = Utils::Instance()->getStationPoint(3);
				break;
			case 1:case 4:case 7:
				rntPos = Utils::Instance()->getStationPoint(4);
				break;
			case 2:case 5:case 8:
				rntPos = Utils::Instance()->getStationPoint(5);
				break;
			case 9:case 12:case 15:
				rntPos = Utils::Instance()->getStationPoint(12);
				break;
			case 10:case 13:case 16:
				rntPos = Utils::Instance()->getStationPoint(13);
				break;
			case 11:case 14:case 17:
				rntPos = Utils::Instance()->getStationPoint(14);

				break;
			}
			rntPos.y += POSX(44.0f);
			if (src->arraySeat >= 9)
				rntPos.y += POSX(30.0f);
		}break;
	case 2:
	case 5:
		{
			if (src->arraySeat >= 9)
			{//右上角
				rntPos = Utils::Instance()->getStationPoint(13);
			}
			else
			{//左下角
				rntPos = Utils::Instance()->getStationPoint(4);
			}
			rntPos.y += POSX(44.0f*3);
		}break;
	case 6:
		{
			rntPos = Utils::Instance()->getStationPoint(src->arraySeat);
			rntPos.y += POSX(120.0f);
		}break;
	case 7:
		{
			if (m_attacker->arraySeat >= 9)
			{//右上角
				rntPos = Utils::Instance()->getStationPoint(13);//因为是辅助特效，所以要播放在自己场上(src是对手)
			}
			else
			{//左下角
				rntPos = Utils::Instance()->getStationPoint(4);//因为是辅助特效，所以要播放在自己场上(src是对手)
			}
			rntPos.y += POSX(44.0f*3);
		}break;
	case 8:
		{
			if (m_attacker->arraySeat >= 9)
			{//右上角s
				rntPos = Utils::Instance()->getStationPoint(13);//因为是辅助特效，所以要播放在自己场上(src是对手)
			}
			else
			{//左下角
				rntPos = Utils::Instance()->getStationPoint(4);//因为是辅助特效，所以要播放在自己场上(src是对手)
			}
			rntPos.y += POSX(44.0f*3);
		}break;
	default:
		{}break;
	}

	//single
	if (m_skill->longAttack == 1 || m_skill->longAttack == 6)
	{
		if (src->arraySeat < 9)
		{
			if (m_skill->flipX == 1)
				ani->setFlipX(true);

			if (m_skill->flipY == 1)
				ani->setFlipY(true);
		}
	}
	//偏移
	if (src->arraySeat < 9)
	{
		rntPos.x += POSX(m_skill->offsetX2);
		rntPos.y += POSX(m_skill->offsetY2);
	}
	else
	{
		rntPos.x += POSX(m_skill->offsetX);
		rntPos.y += POSX(m_skill->offsetY);	
	}

	return rntPos;
}