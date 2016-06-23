#include "RecruitCommand.h"
#include "socket/command/s30/SCMD300.h"
#include "model/recruit/vo/RookieVo.h"
#include "socket/command/s30/SCMD301.h"
#include "model/recruit/vo/DismissVo.h"
#include "socket/command/s30/SCMD303.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "model/player/vo/FigureCfgBaseVo.h"
#include "model/player/FigureBaseManage.h"
#include "socket/command/s30/SCMD305.h"
#include "model/train/vo/TrainManager.h"
#include "../formation/FormationCommand.h"
#include "../AppFacade.h"
#include "model/player/RoleManage.h"
#include "model/figure/EquipmentManager.h"
#include "manager/LangManager.h"
#include "model/skill/vo/SkillType.h"
#include "view/figure/components/FigureCreate.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c30/CCMD30D.h"

RecruitCommand::RecruitCommand()
{
	_recruitProxy = 0;
	_skillProxy = 0;
	_roleManage = 0;
	_skillChangedMercId = 0;
}

void RecruitCommand::execute( int32 command, char* data )
{
	if ( !_recruitProxy )
	{
		_recruitProxy = (RecruitProxy*)g_pFacade->retrieveProxy( AppFacade_RECRUIT_PROXY_CHANGE );
		_skillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
		_roleManage = RoleManage::Instance();
	}

	switch( command )
	{
	case INIT_ROOKIE_LIST:
		initRookieList( data );
		break;
	case INIT_DISMISS_LIST:
		initDismissList( data );
		break;
	case RECRUIT_MERC:
		recruitMerc( data );
		break;
	case DISMISS_MERC:
		dismissMerc( data );
		break;
	}
}

void RecruitCommand::initRookieList( char* obj )
{
	SCMD300* param = (SCMD300*)obj;
	vector<RookieVo*> list;
	for ( uint i = 0; i < param->a_mercenarys.size(); i++ )
	{
		RookieVo* rookieVo = new RookieVo;
		rookieVo->mercId = param->a_mercenarys[i];
		list.push_back( rookieVo );
	}
	_recruitProxy->initRookieList( list );

	for ( uint i = 0; i < list.size(); i++ )
	{
		CC_SAFE_DELETE( list[i] );
	}
}
		
void RecruitCommand::initDismissList( char* obj )
{
	SCMD301* param = (SCMD301*)obj;
	vector<DismissVo*> list;
	for ( uint i = 0; i < param->a_mercenarys.size(); i++ )
	{
		SCMD301Node* node = &(param->a_mercenarys[i]);
		DismissVo* dismissVo = new DismissVo;
		dismissVo->id = node->a_mercenaryId;
		dismissVo->mercId = node->b_prototypeId;
		dismissVo->level = node->c_level;
		dismissVo->exp = node->d_exp;
		dismissVo->strength = node->e_strength;
		dismissVo->intellect = node->f_intellect;
		dismissVo->stamina = node->g_stamina;
		dismissVo->skill = node->i_skill;

		dismissVo->reborn = node->j_reborn;
		dismissVo->maxhp = node->k_maxHp;
		list.push_back( dismissVo );
	}

	_recruitProxy->initDismissList( list );
}
		
/**
* 招募佣兵返回
* @param mercId 原型ID
* @param id 世界ID
*/ 
void RecruitCommand::recruitMerc( char* obj )
{
	SCMD303* param = (SCMD303*)obj ;
			
 	if( param->b_mercenaryId == 0 )
	{
		LangManager::msgShow("RCR026");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR026") );
		return;
	}	

	FigureCfgBaseVo* mercBase = FigureBaseManage::Instance()->getMercBase( param->a_prototypeId );
	if ( !mercBase )
	{
		return;
	}

	PlayerInfoVo* mercObj = new PlayerInfoVo();
	PlayerBaseVo& playBase = mercObj->playerBaseInfo;
	FigureBaseVo& figureBase = mercObj->figureBaseInfo;
			
	playBase.color = mercBase->color;    //佣兵颜色
	playBase.id = param->b_mercenaryId;
	playBase.name = mercBase->name;
	playBase.career = mercBase->careerId;
	playBase.cloth = mercBase->cloth;
	playBase.sex = mercBase->sex;
	playBase.isRole = false;
	playBase.lev( mercBase->lev );
	playBase.hp( mercBase->maxHp );
	playBase.maxHp( mercBase->maxHp );  
	playBase.skill1 = mercBase->skill1[1];  // default skill second
	playBase.skill2 = mercBase->skill2;
	playBase.exp( mercBase->exp );
			
	figureBase.mercId = mercBase->mercId;
	figureBase.agility = mercBase->agility;
	figureBase.crit = mercBase->crit;
	figureBase.hitRate = mercBase->hitRate;
	figureBase.silver = mercBase->silver;
	figureBase.intellect = mercBase->intellect;
	figureBase.stamina = mercBase->stamina;
	figureBase.strength = mercBase->strength;
			
			
	DismissVo* dismissVo = _recruitProxy->getDismissVoByMercId( param->a_prototypeId);
	if( dismissVo )
	{
		// if exist ever fired data ,then recover it
		playBase.lev( dismissVo->level );
		playBase.exp( dismissVo->exp );
		playBase.skill1 = dismissVo->skill;
		figureBase.intellect = dismissVo->intellect;
		figureBase.stamina = dismissVo->stamina;
		figureBase.strength = dismissVo->strength;
		figureBase.rebornNum = dismissVo->reborn;
		playBase.maxHp( dismissVo->maxhp );
		playBase.hp( dismissVo->maxhp );
	}

	// jae mend 如果有选择了特技2的 强制发请求修改为特技1
	FigureCfgBaseVo * pFigureCfgBaseVo = FigureBaseManage::Instance()->getMercBase(figureBase.mercId);
	if (pFigureCfgBaseVo)
	{
		if (pFigureCfgBaseVo->skill1.size()>1)
		{
			if (playBase.skill1==pFigureCfgBaseVo->skill1[1])
			{
				CCMD30D c;
				c.a_merId = playBase.id;//figureBase.mercId;
				c.b_skillRank = SkillType::SKILL;
				c.c_skillId = pFigureCfgBaseVo->skill1[0];
				GameServerSocket::getInstance()->sendMessage(&c);

				playBase.skill1 = pFigureCfgBaseVo->skill1[0];  // default skill

				int skill01 = pFigureCfgBaseVo->skill1[0];
				int skill02 = pFigureCfgBaseVo->skill1[1];
				pFigureCfgBaseVo->skill1.clear();
				pFigureCfgBaseVo->skill1.push_back(skill02);
				pFigureCfgBaseVo->skill1.push_back(skill01);

				_skillChangedMercId = playBase.id;

				FigureBaseManage::Instance()->setMercenaryDic(pFigureCfgBaseVo);
			}
		}
	}

	_roleManage->addMercenary( param->b_mercenaryId, mercObj );
	_roleManage->accountInfo()->roleNum++;
			
	_recruitProxy->recruitMerc( param->b_mercenaryId );
			 
}
/**
* 解雇佣兵返回
* @param id 佣兵唯一ID
* @param result 处理结果  0-不成功  1-成功
*/
void RecruitCommand::dismissMerc( char* obj )
{
	SCMD305* param = (SCMD305*)obj;
	int id = param->a_mercenaryId;
			
	if( TrainManager::Instance()->_trainDic.find(id) != TrainManager::Instance()->_trainDic.end() )
	{
		LangManager::msgShow("RCR028");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR028") );
		return;	
	}
			
	if( param->b_result == 0 )
	{
		LangManager::msgShow("RCR027");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR027") );
		return;
	}
	
	std::map<RoleManage::MercKeyIndex, PlayerInfoVo>* dicEx = _roleManage->mercListEx();
	std::map<RoleManage::MercKeyIndex, PlayerInfoVo>::iterator iterEx = dicEx->begin();
	for (; iterEx != dicEx->end() ; iterEx++)
	{
		if (iterEx->first.id == id)
		{
			dicEx->erase( iterEx );
			break;
		}
	}

	std::map<int, PlayerInfoVo>* dic = _roleManage->mercList();
	std::map<int, PlayerInfoVo>::iterator it = dic->find(id);
	if( it != dic->end() )
	{
		PlayerInfoVo& playerInfoVo = it->second;
		_recruitProxy->saveDismissedMerc( &playerInfoVo );  // 保存被解雇的佣兵 
		_skillProxy->updateSkillState( playerInfoVo.playerBaseInfo.skill3, false );

		sendNotification( Facade_Mediator, AppFacade_FORMATION_PROXY_CHANGE, (char*)param->a_mercenaryId, FormationCommand::DISMISS_FIGURE );
				
		dic->erase( it );
		_roleManage->accountInfo()->roleNum--;
		EquipmentManager::Instance()->deleteEquipment(id);
		_recruitProxy->dismissMerc();

	}

	// refresh formation members
	// by LH0802
	std::map<int, SkillNode> * pLearnedFormation = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::FORMATION);
	if (!pLearnedFormation)	{return;	}		
	std::map<int, SkillNode>::iterator iter = pLearnedFormation->begin();
	for(; iter != pLearnedFormation->end(); ++iter)
	{
		if (iter->second.formationInfo)
		{
			std::map<int, int> * formMap =  &iter->second.formationInfo->figuresMap;
			if ( formMap && (!formMap->empty()))
			{
				std::map<int, int>::iterator it = formMap->begin();
				for (; it != formMap->end(); it++)
				{
					if (it->second == param->a_mercenaryId)
					{
						formMap->erase(it->first);
						break;
					}
				}
			}			
		}
	}


	if (g_pFigureScrollView&&g_pFigureScrollView->getIsVisible())
	{
		g_pFigureScrollView->showEquipInfo();
		g_pFigureScrollView->showSkillInfo();
		g_pFigureScrollView->moveToPage(1);
	}
}

RecruitCommand::~RecruitCommand()
{

}