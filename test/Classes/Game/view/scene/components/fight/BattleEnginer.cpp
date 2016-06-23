#include "BattleEnginer.h"
#include "manager/ViewManager.h"

static BattleEnginer *_instance;

 BattleEnginer * BattleEnginer::getInstance()
	{
		if(!_instance)
		{
			_instance = new BattleEnginer();
		}
		return _instance;
	}
	
 void BattleEnginer::Release()
	{
		if(NULL != _instance)
		{
			delete _instance;
		}
		_instance = NULL;
	}


BattleEnginer::BattleEnginer(){
	/*this->context = context;
	this->type = type;*/

	FightEffectGroup::Instance();
	/*this->actionHandler = new ActionHandler(this.context, this._feGroup, this.type);
	this.buffsHandler = new BuffsHandler(this.context, _feGroup, this.type);*/
	_fightReward = NULL;
	_battleReport = NULL;
	_fightRet = NULL;
	_fightPack = 0;
	_type = 0;
	_action_num = 0;

	this->_actionHandler=ActionHandler::getInstance();
	this->_round = 0;
 
	this->_rate = 0.5f;

	//this->_feGroup = new FightEffectGroup();
	
}

void BattleEnginer::execute()
{//void scheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget, ccTime fInterval, bool bPaused);
	
	
	nextRound();
}

bool BattleEnginer::haveNextEffect()
{
	if(!_actions.empty() && _actions.size() > _action_num)
	{
		return true;
	}
	else
	{
		if(_fightPack->size()<=_round)
		{
			return false;//最后的特效组已经播完了，战斗要完结了
		}
	}
	return true;
}

void BattleEnginer::nextRound()
{
	if(_fightPack->size()<=_round)
	{
		cocos2d::CCLog("_fightPack->size() %d",_fightPack->size());
		cocos2d::CCLog("_round %d",_round);
 
		stop();
		return;
	}
	_action_num=0;

	SCMD132 *scmd132 = &(*_fightPack)[_round];

	// 当前回合数加1
	this->_round ++;


	// 动作集合
	this->_actions = scmd132->c_Actions;
	this->_buffs = scmd132->d_buffs;
	//this.context.showRoundMc(sCMD132.b_round.value + 1);  // 通知FightLayer显示第几回合
	cocos2d::CCLog("this->_round is  %d",this->_round);
	//FightLayer::getInstance()->showRound(this->_round);
	if(ViewManager::getInstance()->_fightScene)
		ViewManager::getInstance()->_fightScene->showRound(this->_round);
	nextActions();
}

void BattleEnginer::nextActions(CCNode* n, void* data)
{
	if(!_actions.empty() && _actions.size() > _action_num)
	{
		SCMD132::SCMD132Node1 action = _actions[_action_num];
		_action_num ++;
		this->playOneAction(action);
	}
	else
	{
		nextRound();
	}
}

void BattleEnginer::playBuffs(std::list<SCMD132::SCMD132Node4>& buffs)
{
	_buffs.clear();
	nextActions(NULL, NULL);
}

void BattleEnginer::stop()
{
	cocos2d::CCLog ("stop");
	this->_actionHandler->_permitRun = false;
	if (_fightPack)
	{
		_fightPack->clear();
	}
	this->_round = 0;


	//FightLayer::getInstance()->showResult(_fightRet->c_win, _fightRet->b_type, _fightReward, _battleReport);
	if(ViewManager::getInstance()->_fightScene && _fightRet)
		ViewManager::getInstance()->_fightScene->showResult(_fightRet->c_win, _fightRet->b_type, _fightReward, _battleReport);
}

void BattleEnginer::playOneAction(SCMD132::SCMD132Node1 action)
{
	this->_actionHandler->_rate = _rate;
	this->_actionHandler->_type = this->_type;
	
	this->_actionHandler->playOneAction(action);
}

void BattleEnginer::dispose()
{
	FightEffectGroup::Instance()->stop();
	FightEffectGroup::Instance()->dispose();
}
