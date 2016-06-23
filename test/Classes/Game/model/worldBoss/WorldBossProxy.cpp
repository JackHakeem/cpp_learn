#include "WorldBossProxy.h"
#include "vo/BossInfoVo.h"
#include "../player/RoleManage.h"
#include "vo/WBPlayerInfoVo.h"
#include "socket/command/s2c/SCMD2C7.h"
#include "socket/command/s2c/SCMD2CC.h"
#include "socket/command/s2c/SCMD2CE.h"
#include "view/worldBoss/WorldBossMediator.h"
#include "manager/LevLimitConst.h"

WorldBossProxy::WorldBossProxy()
{
	_dmgRKList.clear();
	_worldBossOpTime = 0;
	_playerInfo = new WBPlayerInfoVo();
	_bossInfo = new BossInfoVo();
	_curMapID = 0;
	_isInTime = false;
}

WorldBossProxy::~WorldBossProxy()
{

}

void WorldBossProxy::handleBossInfo(SCMD2C9 * data)
{
	if (!data)	{		return;	}
	if (_bossInfo)
	{
		_bossInfo->currentHP = data->a_currentHP ;
		_bossInfo->maxHP = data->b_maxHP ;
		_bossInfo->totalDamageLow = data->c_totalDamage_low;
		_bossInfo->totalDamageHigh = data->c_totalDamage_high;
	}
	_dmgRKList = data->d_damageRankList;

	if (RoleManage::Instance()->roleInfo())
	{
		_curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	}

	if (_curMapID == _worldBossMapID)
	{
		// ���½���
		// UPDATE_BOSS_INFO
		sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)data , WorldBossMediator::UPDATE_BOSS_INFO);
	}
}

void WorldBossProxy::handlePlayerInfo(SCMD2C8 * data)
{
	if (!data)	{		return;	}
	if (_playerInfo)
	{
		_playerInfo->damage = data->d_damage;
		_playerInfo->boostNum = data->c_boostNum;
		_playerInfo->deathCD = data->a_movingCD;
		_playerInfo->awardList = data->e_awardList;
	}

	if (RoleManage::Instance()->roleInfo())
	{
		_curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	}

	if (_curMapID == _worldBossMapID)
	{
		// ���½���
		// UPDATE_PLAYER_INFO
		sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)data , WorldBossMediator::UPDATE_PLAYER_INFO);
	}
}

void WorldBossProxy::handleOpenTime(SCMD2C7 * data)
{
	if (!data)	{		return;	}
	_worldBossOpTime = data->a_nextTime;
	_isInTime = data->b_inTime;

	//���µ�ͼͼ�� ���´�����ʱ��
	//IS_WORLDBOSS_TIME
	sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)data , WorldBossMediator::UPDATE_OPEN_TIME);
}

void WorldBossProxy::handleRelive(SCMD2CE * data)
{
	if (!data)	{		return;	}

	_curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if (_curMapID == _worldBossMapID)
	{
		// ���½���
		// RELIVE
		sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)data , WorldBossMediator::RELIVE);
	}
}

void WorldBossProxy::handleBoost(SCMD2CC * data)
{
	if (!data)	{		return;	}

	_curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if (_curMapID == _worldBossMapID)
	{
		// ���½���
		// BOOST
		sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)data , WorldBossMediator::BOOST);
	}
}

void WorldBossProxy::setCurMapID(int mapID)
{
	_curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	// ���������Boss��ͼ��ת��������ͼ ������Ϣ�����ؽ���
	if(_curMapID == _worldBossMapID && mapID != _worldBossMapID)
	{
		sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)0 , WorldBossMediator::QUIT);
	}
	// �����������ͼ���뵽����Boss��ͼ ������Ϣ�Դ򿪽���
	if(/*_curMapID != _worldBossMapID && */mapID == _worldBossMapID)
	{
		INITInfo initInfo;
		// �����Ϣ
		if (_playerInfo)
		{
			SCMD2C8 cmd2c8; 
			cmd2c8.a_movingCD = _playerInfo->deathCD;
			cmd2c8.b_battleCD = 0;
			cmd2c8.c_boostNum = (uint8)_playerInfo->boostNum;
			cmd2c8.d_damage = _playerInfo->damage;
			initInfo.cmd2c8 = cmd2c8; 
		}

		// Boss��Ϣ
		if (_bossInfo)
		{
			SCMD2C9 cmd2c9;
			cmd2c9.a_currentHP = _bossInfo->currentHP;
			cmd2c9.b_maxHP = _bossInfo->maxHP;
			cmd2c9.c_totalDamage_low = _bossInfo->totalDamageLow;
			cmd2c9.c_totalDamage_high = _bossInfo->totalDamageHigh;
			cmd2c9.d_damageRankList = _dmgRKList;
			initInfo.cmd2c9 = cmd2c9;
		}
		
		initInfo.wbOpTime = _worldBossOpTime; // �����ʱ��		
		
// 		if (_isInTime)
// 		{
			sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)&initInfo , WorldBossMediator::ENTER);
//		}
		
	}
	_curMapID = mapID;
}

bool WorldBossProxy::canEnter()
{
	// ����ȼ�40���ſ���
	if(RoleManage::Instance()->roleInfo()->playerBaseInfo._lev < LevLimitConst::Limit_WorldBoss)
	{
		return false;
	}
	return (_isInTime == 1);
}

std::list<SCMD2C8::SCMD2C8Node> * WorldBossProxy::getAwardList()
{
	if (_playerInfo)
	{
		return &_playerInfo->awardList;
	}
	return 0;
}

int WorldBossProxy::getMapID()
{
	return _worldBossMapID;
}

int WorldBossProxy::getTime()
{
	return _worldBossOpTime;
}

void WorldBossProxy::handleQuit()
{
	sendNotification(Facade_Mediator , AppFacade_WorldBoss_Mediator , (char *)0 , WorldBossMediator::QUIT);
}
