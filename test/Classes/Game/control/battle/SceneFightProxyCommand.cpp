#include "SceneFightProxyCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/battle/FightProxy.h"
#include "manager/ViewManager.h"
#include "socket/command/s13/SCMD131.h"
#include "view/scene/layer/FightLayer.h"
#include "utils/loader/AnimationManager.h"
#include "cocos2d.h"
#include "model/scene/MonsterManager.h"
#include "model/scene/vo/EventType.h"
#include "socket/command/s13/SCMD132.h"
#include "socket/command/s13/SCMD133.h"
#include "view/battle/SceneFightMediator.h"
#include "utils/Utils.h"
#include "CCActionProgressTimer.h"
#include "manager/SourceCacheManage.h"

SceneFightProxyCommand::SceneFightProxyCommand()
{
	_fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
}
void SceneFightProxyCommand::execute(int32 command, char* data)
{
	switch(command)
	{
	case JOIN_ELEMENT:
		this->joinElement();
		break;
	case INIT_PVE_SCENEVO:
		setPVEFightSceneVo(data);
		break;
	case INIT_PVP_SCENEVO:
		setPVPFightSceneVo(data);
		break;
	case INIT_PVE_DATA:
		if(_fightProxy)
			_fightProxy->setPVEData(data);
		break;
	case INIT_PVP_DATA:
		if(_fightProxy)
			_fightProxy->setPVPData(data);
		break;
	case ADD_FIGHTPACK:
		if(_fightProxy)
		{
			_fightProxy->addFightPack((SCMD132*)data);
		}
		break;
	case ADD_FIGHTRET:
		if(_fightProxy)
		{
			_fightProxy->setFightRet((SCMD133*)data);
		}
		break;
	case ADD_REWARD:
		//if(_fightProxy)
		//	_fightProxy->fightReward(data);
		break;
	case ADD_FOLLOW_PROCESS:
		/*var sCMD11F:SCMD11F = notification.getBody() as SCMD11F;
		_fightProxy._bData._tailStoryAction = new FightFollowStoryAction(sCMD11F.b_id.value);
		*/
		break;
	case ADD_NEW_MERC:
		//var obj2:SCMD125 = notification.getBody() as SCMD125;
		//if(roleManage.roleLev > 15 ){  // 8级之后才显示 
		//	_fightProxy._bData._callbacks.push(new MercNewComeAction(obj2.a_mercId.value));
		//}
		break;
	default:
		break;
	}
}

void SceneFightProxyCommand::setPVEFightSceneVo(char* data)
{
	int type = EventType::PVE;
	int id = *(int*)data;
	if(_fightProxy)
		_fightProxy->setPVEFight(id, type);
}

void SceneFightProxyCommand::setPVPFightSceneVo(char* data)
{
	int type = EventType::PVP;
	if(_fightProxy)
		_fightProxy->setPVPFight(type);
}




/**
* Add elements
* 
*/		
void SceneFightProxyCommand::joinElement()
{
    CCLog("11......................");
/*	if(_fightProxy->battleId == 0)
		return;*/
    CCLog("12......................");
	_fightProxy->removeElement();
	// 	Add combat elements
    CCLog("12......................");
	if(_fightProxy->id != 0)
	{
        CCLog("13......................");
		// 怪物组合ID不为0 即是PVE 为0即PVP 
		this->addMonsters();
	}
	this->addPlayers();
	_fightProxy->fightResLoaded = true;
    CCLog("16......................");

}

//Add monsters
void SceneFightProxyCommand::addMonsters()
{
	if(_fightProxy->id == 0)
	{
		sendNotification(Facade_Mediator, AppFacade_FIGHT_PROXY_CHANGE, NULL, SceneFightMediator::ABORT_FIGHT);
		return;
	}
	
	int groupId = _fightProxy->id;
	NPCVo* npc = MonsterManager::Instance()->getMonsterGroup(groupId);
	if(!npc)
		return;

	std::string groupInfoStr = npc->forInfo; //For example groupinfo="90|0|0|8|0|8|0|0|0"
	_fightProxy->oppositeFormation = npc->formId;
	//"90|0|0|8|0|8|0|0|0"Conversion for a int array
	char groupinfoChar[ 50 ];
	sprintf(groupinfoChar,"%s", groupInfoStr.c_str());
	int enemyArr[9];
	int j=0;
	char *token;
	token = strtok( groupinfoChar, "|" );
	while( token != NULL )
	{
		enemyArr[j++] = atoi(token);
		token = strtok( NULL, "|" ); 
	}

	int vpos[18] = {0};
	int enemyStation = 10;
	for( int i = 0; i < 9; i++ )
	{
		if(enemyArr[i]!=0)
		{
			NPCVo* enemyMonster = MonsterManager::Instance()->getMonsters(enemyArr[i]);   //
			if(enemyMonster)
			{
				NPCVo npcVo = *enemyMonster;
				CCPoint pos = Utils::Instance()->getStationPoint(enemyStation - 1);
				vpos[enemyStation - 1] = 1;
				npcVo.arraySeat = enemyStation - 1;
				npcVo.x = pos.x+POSX(20);
				npcVo.y = pos.y;
				npcVo._isCell = false;
				npcVo.id = enemyStation;
				npcVo.state = 3;
				npcVo._isMonster = true;
				//FightLayer::getInstance()->addNPC2(enemyMonster, enemyStation);
				if(ViewManager::getInstance()->_fightScene)
				{
					MapNPC * pMapNPC = ViewManager::getInstance()->_fightScene->addNPC(&npcVo);
					//pMapNPC->release();//jae
					pMapNPC->arraySeat = npcVo.arraySeat;
					//pMapNPC->setIsVisible(false);//kevin0702
					if (pMapNPC)
					{
						if (pMapNPC->getChildByTag(LiveThing::TAG_BLOOD))
						{
							pMapNPC->getChildByTag(LiveThing::TAG_BLOOD)->setIsVisible(true);//kevinchange0811
							//pMapNPC->hp()
							/*std::list<SCMD131Node>::iterator iter = _fightProxy->players.begin();
							for (iter ; iter != _fightProxy->players.end() ; iter++)
							{
								if (iter->a_id == npcVo.id)
								{
									pMapNPC->hp(iter->d_hp);
									if (iter->d_hp != iter->j_maxHp)
									{
										pMapNPC->updateHPBar(0.1f , (float)iter->d_hp * 100.0f / (float)iter->j_maxHp);
									}
								}	
							}*/						
						}
					}				
				}
			}
		}
		enemyStation++;
	}
 /*
	for (int i = 0; i < 18; i++)
	{//kevinu 设置方块位置
		CCPoint pos = Utils::Instance()->getStationPoint(i);
		//pos.y = POSX(640) - pos.y;
		SpriteNode* pSp = new SpriteNode();
		if (vpos[i] !=0 )
			pSp->initWithFile("assets/ui/formation_1.png");
		else
			pSp->initWithFile("assets/ui/formation_0.png");
		ViewManager::getInstance()->_fightScene->_movingLayer->addChild(pSp, -1);
		pSp->release();
		pSp->setPosition(ccpAdd(pos, ccp(0, pSp->getTexture()->getContentSize().height/2)));
	}
*/	
}

/**
*  Add our
* 
*/	
void SceneFightProxyCommand::addPlayers()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	std::list<SCMD131Node> playerList=_fightProxy->players;
	std::list<SCMD131Node>::iterator iter;
	int vpos[18] = {0};
	bool isrightbottom = true;
    CCLog("14......................");
	for(iter = playerList.begin(); iter != playerList.end(); iter++)     //list Iterators traverse
	{
		int32 pos = iter->b_station;
		if(pos <= 0 || pos > 18)
			continue;


		vpos[pos-1] = 1;

		//cocos2d::CCLog("SceneFightProxyCommand::pos %d",pos);
		//CCSprite* player= CCSprite::spriteWithFile("role/man.png");
		//FightLayer::getInstance()->addPlayer(player, pos);

		PlayerBaseVo playVo;
		CCPoint p = Utils::Instance()->getStationPoint(pos - 1);
		playVo.arraySeat = pos-1;
		playVo.x = p.x+POSX(6);
		playVo.y = p.y;
		playVo._isCell = false;
		playVo._hp = iter->d_hp;
		playVo._maxHp = iter->j_maxHp;
		playVo._mp = iter->k_startEP;
		playVo._lev = iter->c_lev;

		playVo.cloth = atoi(iter->i_cloth.c_str());
		playVo.accountId = iter->b_station;
		playVo.name = iter->h_name;  
		playVo.state = iter->b_station < 10 ? 7 : 3;
		playVo.skill1 = iter->e_skill1;
		playVo.skill2 = iter->f_skill2;
		playVo.skill3 = iter->g_skill3;

		if (iter->d_hp == 0)
		{
			continue;
		}	
		if(ViewManager::getInstance()->_fightScene)
		{
			Player* play = ViewManager::getInstance()->_fightScene->addPlayerHandler(&playVo);
			if(play)
			{
				play->arraySeat = playVo.arraySeat;
				if (play->getChildByTag(LiveThing::TAG_BLOOD))
				{
					play->getChildByTag(LiveThing::TAG_BLOOD)->setIsVisible(true);//kevinchange0811
					//pMapNPC->hp()
					//std::list<SCMD131Node>::iterator itertmp = _fightProxy->players.begin();
					//for (itertmp ; itertmp != _fightProxy->players.end() ; itertmp++)
					//{
					//	if (itertmp->b_station == iter->b_station)
					//	{
					//		//play->hp(iter->d_hp);
					//		float per = 100.0f - (float)itertmp->d_hp * 100.0f / (float)itertmp->j_maxHp;
					//		if (per >= 0 && per <= 100)
					//		{
					//			play->updateHPBar(0.1f , per);
					//		}	
					//	}	
					//}	
// 					Play->hp(playVo._hp);
// 					Play->maxHp(playVo._maxHp);
// 					Play->mp(playVo._mp);
// 					Play->maxMp(playVo._maxMp);

					play->_showHP = true;
					/*float percentHP = 100.0f - (float)playVo._hp * 100.0f / (float)playVo._maxHp;
					percentHP = (percentHP < 1.0f) ? 1.0f : percentHP;
					percentHP = (percentHP >= 100.0f) ? 99.0f : percentHP;
					play->updateHPBar(0.1f , percentHP);*/
				}
				
			}
		}
	}
    CCLog("15......................");
/*
	for (int i = 0; i < 18; i++)
	{//kevinu 设置方块位置
		CCPoint pos = Utils::Instance()->getStationPoint(i);
		//pos.y = POSX(640) - pos.y;
		SpriteNode* pSp = new SpriteNode();
		if (vpos[i] !=0 )
			pSp->initWithFile("assets/ui/formation_1.png");
		else
			pSp->initWithFile("assets/ui/formation_0.png");
		ViewManager::getInstance()->_fightScene->_movingLayer->addChild(pSp, -1);
		pSp->release();
		pSp->setPosition(ccpAdd(pos, ccp(0, pSp->getTexture()->getContentSize().height/2)));
	}
 */
}
