#include "FightProxy.h"
#include "control/AppFacade.h"
#include "view/battle/SceneFightMediator.h"
#include "control/battle/SceneFightProxyCommand.h"
#include "../scene/fight/CombatDataManage.h"
#include "view/scene/SceneMediator.h"
#include "manager/GlobalManage.h"
#include "socket/command/s13/SCMD13C.h"
#include "view/smallMap/SmallMapMediator.h"
#include "../scene/vo/EventType.h"
#include "mvc/Facade.h"
#include "../scene/vo/SceneType.h"
#include "socket/command/c12/CCMD121.h"
#include "view/fight/callback/CDEnergyAction.h"

FightProxy::FightProxy()
{

	_pveData = 0;

	fightLayerCreate=false ;

	fightDataCreate=false ;

	fightResLoaded=false ;

	fightPack133Loaded=false ;
	/*count132=0;*/
	battleId = 0;
	//_hasDungonAward = false;
	//dungeonAward = 0;
	_callCount = 0;

	_hasDungonAward = false;
	_fightSceneCreate = false;
	_hasTailStory = false;
	playAgain = false;
	formation = 0;
	oppositeFormation = 0;
	playFactor = 0;
	type = 0;
	procid = 0;
	id = 0;
}

FightProxy::~FightProxy(){
}


void FightProxy::setPVEData(char* data)
{
	fightPack.clear();//kevin0827

	SCMD131* scmd131 = (SCMD131*)data;
	if(g_pGlobalManage && g_pGlobalManage->_isInFight)
	{
		CCLog("current is in fight");
		return;
	}

	if(g_pGlobalManage)
		g_pGlobalManage->_isInFight = true;

	if(battleId >0 && scmd131->c_formationId != battleId)
		return;

	//CC_SAFE_DELETE( _pveData );
	
	//_pveData = new SCMD131;
	//memcpy( (void*)_pveData, (void*)scmd131, sizeof(SCMD131) );

	id=scmd131->b_GroupId;       //Monster combination id
	// Doyang 20130123
	//battleId = scmd131->a_BattleId;
	battleId = 0;
	formation = scmd131->c_formationId;
	players = scmd131->d_SCMD131Node;
	fightDataCreate = true;
	cocos2d::CCLog("fightDataCreate = true");
}


void FightProxy::addFightPack(SCMD132* scmd132){    //Combat process in the list of 132 packets
	if (!scmd132)
	{
		CCLog("xxxxxxxxx");
		return;
	}

	if(battleId > 0 && battleId != scmd132->a_BattleId)
	{ 
		CCLog("error content %d:%d", battleId, scmd132->a_BattleId);
		return;
	}

	fightPack.push_back(*scmd132);
	/*count132++;
	cocos2d::CCLog("count132 %d",count132);*/
}

void FightProxy::setFightRet(SCMD133* scmd133){       //Will fight in the bag
	if(!scmd133)
	{
		cocos2d::CCLog("scmd133 pointer null");
		return ;
	}

	if(battleId > 0 && battleId != scmd133->a_BattleId)
	{
		CCLog("battle result packet error, %d:%d", battleId, scmd133->a_BattleId);
		return;
	}

	_fightRet.f_members.clear();
	_fightRet.a_BattleId = scmd133->a_BattleId;
	_fightRet.b_type = scmd133->b_type;	
	_fightRet.c_win = scmd133->c_win;  
	_fightRet.d_damage = scmd133->d_damage;
	_fightRet.e_round = scmd133->e_round;
	_fightRet.f_members = scmd133->f_members;

	_winMark = scmd133->c_win;
	//Doyang 20121010
	_bData._callbacks.push_back(new CDEnergyAction());

	fightPack133Loaded = true;
	cocos2d::CCLog("fightPack133Loaded = true");

	gotoFightScene();
}

void FightProxy::setFightLayer(){
	//let FightLayer began to initUI
	sendNotification(Facade_Mediator, AppFacade_FIGHT_PROXY_CHANGE, 0, SceneFightMediator::INTO_FIGHT);   //Model layer to send messages

}

void FightProxy::showProcess(){
	//Judge fightLayerCreate and _fightDataCreate are ready to start fighting
    CCLog("4.......................");
	if(fightLayerCreate && fightDataCreate){
         CCLog("5.......................");
		this->beforeHandler();
		this->afterHandler();
	}
}

void  FightProxy::beforeHandler() {
	//Doyang 20120713
	// to set clickTarget NULL.
	if(LayerManager::sceneLayer)
	{
		LayerManager::sceneLayer->clickTarget = NULL;
	}
     CCLog("6.......................");
	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE,0,SceneFightProxyCommand::JOIN_ELEMENT);

}


void  FightProxy::afterHandler()
{
	fightStart();
}


bool   FightProxy::getIsCanPlay(){
	return fightResLoaded && fightPack133Loaded /*&& (count132==totalRound)*/;
}

void FightProxy::removeElement(){
}

void FightProxy::fightReward( SCMD13D *pData )
{
	//Doyang 20120727
	if(!pData)
	{
		return;
	}
	//CombatDataManage::Instance()->addFightReward(pData);
	
	/*if(battleId > 0 && battleId != pData->_sceneId)
	return;*/

	_fightReward = *pData;
}

void FightProxy::battleReport( SCMD3B1 *pData )
{
	if(!pData)
		return;
    _battleReport._battleId1 = pData->_battleId1;
    _battleReport._battleId2 = pData->_battleId2;
//	_battleReport = *pData;
}

SCMD131 * FightProxy::getPVEData()
{
	return _pveData;
}

void FightProxy::fightStart()
{
	if (!getIsCanPlay())
		return;
    CCLog("9.......................");
	sendNotification(Facade_Mediator, AppFacade_FIGHT_PROXY_CHANGE, 0, SceneFightMediator::FIGHT_START);
	fightResLoaded =false;
	fightPack133Loaded =false;/*&& (count132==totalRound)*/;
}

void FightProxy::fightExit()
{
	//Doyang 20120727
	_fightReward._rewards.clear();
	_fightReward._sceneId = 0;
	_fightReward._exps.clear();

	_fightRet.a_BattleId = 0;
	_fightRet.b_type = 0;
	_fightRet.c_win = 0;
	_fightRet.d_damage = 0;
	_fightRet.e_round = 0;
	_fightRet.f_members.clear();

	sendNotification(Facade_Mediator, AppFacade_FIGHT_PROXY_CHANGE, 0, SceneFightMediator::ABORT_FIGHT);
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, 0, SceneMediator::REMOVE_FIGHT_SCENE);
}

void FightProxy::setPVPData(char* data)
{
	fightPack.clear();//kevin0827

	if(g_pGlobalManage && g_pGlobalManage->_isInFight)
	{
		CCLog("current in fight when set pvp data");
		return;
	}
	SCMD13C* scmd13c = (SCMD13C*)data;
	if(!scmd13c)
		return;

	if(battleId>0 && scmd13c->a_BattleId != battleId)
		return;

	if(g_pGlobalManage)
		g_pGlobalManage->_isInFight = true;
	
	// Doyang 20130123
	//battleId = scmd13c->a_BattleId;
	battleId = 0;

	formation = scmd13c->b_attackFid;
	oppositeFormation = scmd13c->c_defendFid;
	players = scmd13c->d_players;
	fightDataCreate = true;
}

void FightProxy::setPVEFight(int procId, int type)
{
	type = type;
	procid = procId;

	bool i = true;
	sendNotification(Facade_Mediator, AppFacade_SmallMapMediator, (char*)&i, SmallMapMediator::LOCK_STATE);
	int id = procId;
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)&id, SceneMediator::ROLE_STOPANDNPC_MOVE);
}

void FightProxy::setPVPFight(int type)
{
	type = EventType::PVP;
}

void FightProxy::gotoFightScene()
{  
	fightStart();
}

void FightProxy::clear()
{
	_fightSceneCreate = false;
	playAgain = false;
	memset( (void *)&_battleReport, 0, sizeof(_battleReport) );
	_hasDungonAward = false;

	//_bData = new BattleData;
	id = 0;
}
