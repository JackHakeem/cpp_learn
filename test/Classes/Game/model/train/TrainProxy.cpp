#include "TrainProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/train/TrainViewMediator.h"
#include "../player/RoleManage.h"
#include "socket/command/s35/SCMD35C.h"
#include "utils/ValuesUtil.h"
#include "manager/LangManager.h"
#include "../crystal/vo/CrystalType.h"
#include "../crystal/CrystalProxy.h"

TrainProxy::TrainProxy()
{
	_endGold = 5;
	_trainManager = TrainManager::Instance();

	// The training time options initial array
	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	_timeList[0].id = 0; _timeList[0].silver = 0; _timeList[0].gold = 0; _timeList[0].desc = "";
	_timeList[1].id = 1; _timeList[1].silver = 0; _timeList[1].gold = 0; _timeList[1].desc = "";
	_timeList[2].id = 2; _timeList[2].silver = 0; _timeList[2].gold = 2; _timeList[2].desc = "";
	_timeList[3].id = 3; _timeList[3].silver = 0; _timeList[3].gold = 4; _timeList[3].desc = "";
	_timeList[4].id = 4; _timeList[4].silver = 0; _timeList[4].gold = 6; _timeList[4].desc = "";
	_timeList[5].id = 5; _timeList[5].silver = 0; _timeList[5].gold = 10; _timeList[5].desc = "";
	_timeList[6].id = 6; _timeList[6].silver = 0; _timeList[6].gold = 12; _timeList[6].desc = "";

	// Training mode option initial array
	_modeList[0].id = 0; _modeList[0].silver = 0; _modeList[0].gold = 0; _modeList[0].descMode =  "";
	_modeList[1].id = 1; _modeList[1].silver = 0; _modeList[1].gold = 2; _modeList[1].descMode =  "";
	_modeList[2].id = 2; _modeList[2].silver = 0; _modeList[2].gold = 5; _modeList[2].descMode =  "";
	_modeList[3].id = 3; _modeList[3].silver = 0; _modeList[3].gold = 10; _modeList[3].descMode = "";
	_modeList[4].id = 4; _modeList[4].silver = 0; _modeList[4].gold = 20; _modeList[4].descMode = "";
}

TrainProxy::~TrainProxy()
{

}

void TrainProxy::beginTraining( char* mercs, bool flag )
{
	sendNotification( Facade_Mediator, AppFacade_TRAIN_PROXY_CHANGE, mercs, TrainViewMediator::BEGIN_TRAINING );
}

void TrainProxy::endTraining( char* mercs, bool flag )
{
	sendNotification( Facade_Mediator, AppFacade_TRAIN_PROXY_CHANGE, mercs, TrainViewMediator::END_TRAINING );
}

void TrainProxy::rapicLeap( char* mercs/*mercId:int, rapicExp:int, rapicGold:int=0, critExp:int=0*/ )
{
	SCMD35C *param = (SCMD35C*)mercs;
	_rapicGold = param->c_goldPrice;

	sendNotification( Facade_Mediator, AppFacade_TRAIN_PROXY_CHANGE, mercs, TrainViewMediator::RAPIC_LEAP );
	//this.sendNotification(TrainViewMediator.RAPIC_LEAP, {mercId: mercId, rapicExp: rapicExp, rapicGold:rapicGold, critExp: critExp});
}

int TrainProxy::getEndGold()
{
	return _endGold;
}

void TrainProxy::setRapicGold( int value )
{
	_rapicGold = value;
}

int TrainProxy::getRapicGold()
{
	return _rapicGold;
}

/**
* According to the VIP generation training time array
*/ 
vector<TimeInitStruct> TrainProxy::getTimeList()
{
	int vip = RoleManage::Instance()->accountInfo()->vipLev();
	vector<TimeInitStruct> infos;
	CrystalProxy* crystalProxy	= (CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	if ( !crystalProxy )
	{
		return infos;
	}
	/*
	int huoLevel = crystalProxy->getCrystalLev(CrystalType::CRYSTAL_HUO);
	int yanLevel = crystalProxy->getCrystalLev(CrystalType::CRYSTAL_YAN);
	int yan2Level = crystalProxy->getCrystalLev(CrystalType::CRYSTAL_YAN2);
	*/	
	//base on table cfg_functionTrigger
	//the fire crystal levels 8 at the beginning
	int huoLevel = 0;
	if (8 > RoleManage::Instance()->roleLev())
	{
		huoLevel = 8;
	}
	else
	{
		huoLevel = RoleManage::Instance()->roleLev();
	}
	//the yan crystal is opened at level 55 is same to role lv
	int yanLevel = 0;
	if (55 <= huoLevel)
	{
		yanLevel = huoLevel;
	}
	int yan2Level = 0;
	//the yan2 crystal is opened at level 102 is same to role lv
	if (102 <= huoLevel)
	{
		yan2Level = huoLevel;
	}
	if(huoLevel>=0){
		char tmp[54];
		_timeList[0].silver = (huoLevel + yanLevel + yan2Level)*30;
		sprintf( tmp, "%d", _timeList[0].silver );
		_timeList[0].desc = "";

		_timeList[1].silver = (huoLevel + yanLevel + yan2Level)*90; 
		sprintf( tmp, "%d", _timeList[1].silver );
		_timeList[1].desc = "";

		infos.push_back(_timeList[0]);
		infos.push_back(_timeList[1]);
		infos.push_back(_timeList[2]);
	}
	if(vip>=2 || RoleManage::Instance()->accountInfo()->trialVip()){
		infos.push_back(_timeList[3]);
	}
	return infos;
}

/**
* According to the id for time options Object
* @ param id int the training time id the default is 0
*/
TimeInitStruct TrainProxy::getTimeObj( int id )
{
	if ( id >=0 && id < 8 )
	{
		return _timeList[ id ];
	}
    return _timeList[ 0 ];//kevinchange
}

		
ModeInitStruct* TrainProxy::getModeTextList()
{
	return _modeList;
}

/**
* According to the mode for training mode Object
* @ param mode int training mode for 0 ID the default
*/
ModeInitStruct* TrainProxy::getModeObj( int mode )
{
	return &_modeList[mode];
}

/**
* caculate lilian tufei according the crystal lev
* @param clevel Mingzhishuijing lev 
*/
Number TrainProxy::getPracticeDemand( int clevel )
{
	return _trainManager->getSpeedupByCrystal(clevel);
}

/**
* 根据水晶等级计算突飞增加经验值 (火水晶+炎水晶+雁水晶-2)*24+84
* @param hLevel 火之水晶等级
* @param yLevel 炎之水晶等级
*/
Number TrainProxy::getExpAdded( int hLevel, int yLevel, int yanLevel )
{
	Number hSpeedUp = _trainManager->getSpeedupByCrystal(hLevel);
	Number ySpeedUp = _trainManager->getSpeedupByCrystal(yLevel);
	Number yanSpeedUp = _trainManager->getSpeedupByCrystal(yanLevel);
	Number tmp = ( hSpeedUp + ySpeedUp + yanSpeedUp - 2) * 24 + 84;
	tmp = (Number)(tmp * 1.5f);
	return tmp;
}