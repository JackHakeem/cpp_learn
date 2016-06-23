#include "control/figure/FigureCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "socket/command/s30/SCMD30A.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/FigureBaseManage.h"
#include "socket/command/s2f/SCMD2FF.h"
#include "socket/command/s31/SCMD31F.h"
#include "socket/command/s31/SCMD31D.h"
#include "socket/command/c30/CCMD30D.h"
#include "socket/network/GameServerSocket.h"
#include "model/skill/vo/SkillType.h"
#include "../recruit/RecruitCommand.h"

//#include "socket/command/s31/SCMD31B.h"

//#include "socket/command/s2f/SCMD2FF"
FigureCommand::FigureCommand()
{
	//Doyang 20120711
	_figureProxy = NULL;
	/*if (!_figureProxy)
	{
	_figureProxy = new FigureProxy();
	}*/
}

FigureCommand::~FigureCommand()
{
	//CC_SAFE_DELETE( _figureProxy );
}


void FigureCommand::execute(int32 command, char* data)
{
	//_figureProxy = (FigureProxy*)g_pFacade->retrieveProxy(AppFacade_FIGURE_PROXY);
	if(!g_pFacade)
		return;

	_figureProxy = (FigureProxy*)g_pFacade->retrieveProxy(AppFacade_FIGURE_PROXY);
	if(!_figureProxy)
		return;
	switch(command)
	{
	case INIT_FIGURE_BASE_INFO:
		{
			initFigureBaseInfo((SCMD309*)data);
			break;
		}
	case INIT_FIGURE_EQUIP_INFO:
		{
			if(!data)
				break;

			SCMD30A* scmd30a = (SCMD30A*)data;
			_figureProxy->updateEquitInfo((char*)(&(scmd30a->a_eqpList)));
			break;
		}

	case UPDATE_EQUIP_INFO:
		_figureProxy->updateEquipment((SCMD172*)data);
		break;

	case UPDATE_SKILL_INFO:
		_figureProxy->updateSkill((SCMD30E*)data);
		break;

	case FIGURE_SELECT:
		{
			if(!data)
				break;

			RoleManage::Instance()->currentId(((int*)data)[0]);
			break;
		}
	case MERC_SKILL_EXCHANGE:
		{
			if(!data)
				break;

			SCMD2FF* scmd2ff = (SCMD2FF*)data;
			_figureProxy->mercSkillExchange(scmd2ff->a_mercId1, scmd2ff->b_skill1, scmd2ff->c_mercId2, scmd2ff->d_skill2);
			break;
		}

	case REFRESH_WASH_VALUE:
		{
			if(!data)
				break;

			WashVo vo;

			SCMD31F* scmd31f = (SCMD31F*)data;
			vo.intellect = scmd31f->e_intellect;
			vo.stamina = scmd31f->d_stamina;
			vo.strength = scmd31f->c_strength;
			_figureProxy->addWashValueCache(scmd31f->b_figureId, vo);
			break;
		}

	case SAVE_WASH_VALUE:
		{
			if(!data)
				break;

			WashVo vo1;
			SCMD31D* scmd31d = (SCMD31D*)data;
			vo1.intellect = scmd31d->e_intellect;
			vo1.stamina = scmd31d->d_stamina;
			vo1.strength = scmd31d->c_strength;
			_figureProxy->replaceWashValue(scmd31d->b_figureId, vo1);
			break;
		}
	case DELETE_WASH_VALUE:
		{
			if(!data)
				break;

			_figureProxy->delWashValueCache(((int*)data)[0]);
			break;
		}
	case INIT_OTHER_BASE_INFO:
		{
			if(!data)
				break;

			int len = data[0];
			data++;
			char playerName[64];
			memcpy(playerName, data, len);
			data += len;
			SCMD309* scmd309 = (SCMD309*)data;
			initOtherBaseInfo(std::string(playerName), scmd309);
			break;
		}
	case INIT_SPIRIT_INFO:
		initSpInfo((SCMD349*)data);
		break;
	}
}

/**
* Initial character information, b_mercInfo including main character and his mercenaries, but a_mercLim did not include
* @param scmd SCMD309
* 
*/

void FigureCommand::initFigureBaseInfo(SCMD309* scmd309)
{
	if(!scmd309)
		return;

	AccountInfoVo* accountInfoVo = RoleManage::Instance()->accountInfo();
	if(!accountInfoVo)
		return;
	accountInfoVo->roleLim = scmd309->b_mercLim + 1;
	accountInfoVo->roleNum = scmd309->c_mercInfo.size();
	std::list<SCMD309Node> *sn = &(scmd309->c_mercInfo);
	std::list<SCMD309Node>::iterator iter;
	if(!sn) return;
	for(iter=sn->begin(); iter != sn->end(); ++iter)
	{
		FigureCfgBaseVo* mercBase = FigureBaseManage::Instance()->getMercBase(iter->b_typeId);
		if(!mercBase)
		{
			continue;
		}
		PlayerBaseVo* playBase = NULL;
		FigureBaseVo* figureBase = NULL;
		PlayerInfoVo* mercObj = NULL;

		if(mercBase->isRole)
		{
			mercObj = RoleManage::Instance()->roleInfo();
			if(!mercObj)
				continue;

			playBase = &(mercObj->playerBaseInfo);
			figureBase = &(mercObj->figureBaseInfo);
		}else
		{
			mercObj = new PlayerInfoVo();
			playBase = &(mercObj->playerBaseInfo);
			figureBase = &(mercObj->figureBaseInfo);
			playBase->name = mercBase->name;
		}

		playBase->color = mercBase->color;    //Increase mercenaries color
		playBase->career = mercBase->careerId;
		playBase->cloth = mercBase->cloth;//mercBase->mercId;	// Jae change
		playBase->sex = mercBase->sex;
		playBase->isRole = mercBase->isRole;

		figureBase->agility = mercBase->agility;
		figureBase->crit = mercBase->crit;
		figureBase->hitRate = mercBase->hitRate;
		figureBase->silver = mercBase->silver;

		playBase->id = iter->a_id;
		playBase->lev(iter->c_level);
		playBase->adLv = iter->d_ad_lv;
		playBase->maxHp(iter->h_maxHp);
		playBase->hp(iter->i_hp);
		figureBase->mercId = iter->b_typeId;
		figureBase->rebornNum= iter->e_rebornNum;
		//playBase->exp(iter->g1_exp);
		if(iter->f_exp_type == 0)
		{
			playBase->exp(iter->g1_exp);
		}
		else
		{
			playBase->adExp = iter->g0_ad_exp;
		}

		figureBase->pAttack = iter->s_p_att;
		figureBase->pDefense = iter->t_p_def;
		figureBase->mAttack = iter->u_m_att;
		figureBase->mDefense = iter->v_m_def;
		figureBase->strength = iter->j_strength;
		figureBase->intellect = iter->k_intellect;
		figureBase->stamina = iter->l_stamina;
		figureBase->plus_int = iter->n_plus_intel;
		figureBase->plus_str = iter->m_plus_str;
		figureBase->plus_sta = iter->o_plus_sta;
		figureBase->sp_int = iter->q_sp_intel; 
		figureBase->sp_sta = iter->r_sp_sta;
		figureBase->sp_str = iter->p_sp_str;
		figureBase->attPoint = iter->z_att;

		playBase->skill1 = iter->w_equipSkillId;
		playBase->skill2 = iter->x_aoyiId;
		playBase->skill3 = iter->y_passiveId;

		RoleManage::Instance()->addMercenary(iter->a_id, mercObj);
		

		if ( !mercBase->isRole )//jae release
		{
			// jae mend 如果有选择了特技2的 强制发请求修改为特技1
			FigureCfgBaseVo * pFigureCfgBaseVo = FigureBaseManage::Instance()->getMercBase(figureBase->mercId);
			if (pFigureCfgBaseVo)
			{
				if (pFigureCfgBaseVo->skill1.size()>1)
				{
					RecruitCommand* pRecruitCommand = (RecruitCommand*)g_pFacade->retrieveController(AppFacade_RECRUIT_PROXY_CHANGE);
					if (pRecruitCommand && (pRecruitCommand->_skillChangedMercId==0) )
					{
						if (playBase->skill1==pFigureCfgBaseVo->skill1[1])
						{
							CCMD30D c;
							c.a_merId = iter->a_id;
							c.b_skillRank = SkillType::SKILL;
							c.c_skillId = pFigureCfgBaseVo->skill1[0];
							GameServerSocket::getInstance()->sendMessage(&c);

							int skill01 = pFigureCfgBaseVo->skill1[0];
							int skill02 = pFigureCfgBaseVo->skill1[1];
							pFigureCfgBaseVo->skill1.clear();
							pFigureCfgBaseVo->skill1.push_back(skill02);
							pFigureCfgBaseVo->skill1.push_back(skill01);

							FigureBaseManage::Instance()->setMercenaryDic(pFigureCfgBaseVo);
						}
					}
					else
					{
						if (pRecruitCommand && (pRecruitCommand->_skillChangedMercId==iter->a_id))
						{
							pRecruitCommand->_skillChangedMercId = 0;
						}
					}
				}
			}

			CC_SAFE_DELETE( mercObj );
		}
	}

	if(_figureProxy)
		_figureProxy->initMercBaseInfo();
}

void FigureCommand::initOtherBaseInfo(std::string playerName, SCMD309* scmd309)
{
	if(!scmd309)
		return;

	PlayerInfoVo roleInfo;
	std::vector<PlayerInfoVo*> playerArray;
	std::list<SCMD309Node>::iterator iter = scmd309->c_mercInfo.begin();
	for(; iter != scmd309->c_mercInfo.end(); ++iter)
	{
		FigureCfgBaseVo* mercBase = FigureBaseManage::Instance()->getMercBase(iter->b_typeId);
		if(!mercBase)
		{
			continue;
		}

		PlayerInfoVo* info = new PlayerInfoVo();
		PlayerBaseVo* playBase = &(info->playerBaseInfo);
		FigureBaseVo* figureBase = &(info->figureBaseInfo);

		playBase->color = mercBase->color;    //Increase mercenaries color
		playBase->career = mercBase->careerId;
		playBase->cloth = mercBase->cloth;
		playBase->sex = mercBase->sex;
		playBase->isRole = mercBase->isRole;

		figureBase->agility = mercBase->agility;
		figureBase->crit = mercBase->crit;
		figureBase->hitRate = mercBase->hitRate;
		figureBase->silver = mercBase->silver;

		playBase->id = iter->a_id;
		playBase->lev(iter->c_level);
		playBase->adLv = iter->d_ad_lv;
		playBase->maxHp(iter->h_maxHp);
		playBase->hp(iter->i_hp);
		figureBase->mercId = iter->b_typeId;
		figureBase->rebornNum= iter->e_rebornNum;
		//playBase->exp(iter->g1_exp);
		if(iter->f_exp_type == 0)
		{
			playBase->exp(iter->g1_exp);
		}
		else
		{
			playBase->adExp = iter->g0_ad_exp;
		}

		figureBase->pAttack = iter->s_p_att;
		figureBase->pDefense = iter->t_p_def;
		figureBase->mAttack = iter->u_m_att;
		figureBase->mDefense = iter->v_m_def;
		figureBase->strength = iter->j_strength;
		figureBase->intellect = iter->k_intellect;
		figureBase->stamina = iter->l_stamina;
		figureBase->plus_int = iter->n_plus_intel;
		figureBase->plus_str = iter->m_plus_str;
		figureBase->plus_sta = iter->o_plus_sta;
		figureBase->sp_int = iter->q_sp_intel; 
		figureBase->sp_sta = iter->r_sp_sta;
		figureBase->sp_str = iter->p_sp_str;
		figureBase->attPoint = iter->z_att;

		playBase->skill1 = iter->w_equipSkillId;
		playBase->skill2 = iter->x_aoyiId;
		playBase->skill3 = iter->y_passiveId;

		if(mercBase->isRole)
		{
			info->playerBaseInfo.name = playerName;
			info->playerBaseInfo.threat = scmd309->a_threat;
			playerArray[0] = info;
		}
		else
		{
			playerArray.push_back(info);
		}
	}

	/*for(std::vector<PlayerInfoVo*>::iterator it1 = playerArray.begin();
		it1 != playerArray.end(); ++it1)
	{
		if((*it1) != NULL)
			delete (*it1);
	}*/

	//sendNotification(OtherFigureMediator.INIT_BASE_INFO, playerArray);
}


void FigureCommand::initSpInfo(SCMD349* data)
{
	//var playerInfo:PlayerInfoVo;var arr:Array
	//	for each(var n1:SCMD349node1 in param)
	//	{

	//		var dic:Dictionary = RoleManage.getInstance().mercList;
	//		arr = [];
	//		if(dic[n1.a_mercId]!=null)
	//		{
	//			playerInfo =dic[n1.a_mercId]
	//			id = n1.b_merOId.value;
	//			dic[n1.a_mercId].figureBaseInfo.spiritAwoke = true;
	//			for each(var n2:SCMD349node2 in n1.e_spList)
	//			{
	//				lv = n2.b_spLv.value;
	//				type = n2.a_spType.value;
	//				var vo:LvSpiritVo = SpiritManager.getInstance().getLvSp(n1.b_merOId.value,lv,type);
	//				vo.nowExp = n2.c_exp;
	//				vo.needExp = n2.d_lvUpExp;
	//				arr.push(vo);
	//			}
	//		}
	//		_proxy.setMerSpInfo(n1.a_mercId,arr)
	//	}
}

void FigureCommand::sendChangeSkillRequest(int merID,int skillRank,int skillId)
{
	CCMD30D * c = new CCMD30D();
	if (c)
	{
		c->a_merId = merID;
		c->b_skillRank = skillRank;
		c->c_skillId = skillId;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
			cocos2d::CCLog("Skill2:send Change Skill Request:CCMD30D success");

		}
		CC_SAFE_DELETE(c); // LH0712LEAK
	}

}