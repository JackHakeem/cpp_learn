#include "model/player/RoleManage.h"
#include "model/figure/EquipmentManager.h"
#include "../scene/vo/SceneVo.h"
#include "../scene/SceneManager.h"
#include "../scene/vo/SceneType.h"
#include "FigureBaseManage.h"

RoleManage::RoleManage():_currentId(0),_indexCount(0)
{
}

RoleManage::~RoleManage()
{

}

void RoleManage::addMercenary(int id, PlayerInfoVo* mercObj)
{
	if(!mercObj)
		return;

	PlayerInfoVo playerInfovo = *mercObj;

	
	/*playerInfovo.playerBaseInfo.x = 31;
	playerInfovo.playerBaseInfo.y = 49;
	playerInfovo.playerBaseInfo._mapId = 1002;*/
	addMercenaryEx(id , &playerInfovo);

	_mercList.insert(make_pair(id, playerInfovo));

	_cfgMercList.insert(make_pair(mercObj->figureBaseInfo.mercId, playerInfovo));

	//_mercList[id] = playerInfovo;
	//_cfgMercList[mercObj->figureBaseInfo.mercId] = playerInfovo;
}

void RoleManage::addMercenaryEx(int id, PlayerInfoVo* mercObj)
{
	if(!mercObj)		{	return;}
	PlayerInfoVo playerInfovo = *mercObj;

	bool isExist = false;
	std::map<MercKeyIndex, PlayerInfoVo>::iterator iter = _mercListEx.begin();
	for (iter ; iter != _mercListEx.end() ; iter++)
	{
		if (iter->first.id == id)
		{
			isExist = true;
			iter->second = playerInfovo;
			break;
		}
	}
	if (!isExist)
	{
		MercKeyIndex mercKey;
		mercKey.index = _indexCount;
		++_indexCount;
		mercKey.id = id;
		_mercListEx.insert(make_pair(mercKey , playerInfovo));
	}
}
 
void RoleManage::updateMercenaryEx(int id, PlayerInfoVo* mercObj)
{
	std::map<MercKeyIndex, PlayerInfoVo>::iterator iter = _mercListEx.begin();
	for (iter ; iter != _mercListEx.end() ; iter++)
	{
		if (id == iter->first.id)
		{
			PlayerInfoVo infoVo = *mercObj;
			iter->second = infoVo;
		}
	}
}

void RoleManage::updateEnergy(int present, int diffrence)
{
	present += diffrence;
	_accountInfo._energy = present;
}

/**
*  Account information
	* @return 
	* 
	*/		
AccountInfoVo* RoleManage::accountInfo()
{
	return &_accountInfo;
}
		
void RoleManage::accountInfo(AccountInfoVo value)
{
	_accountInfo=value;
}
		
/**
	* @param id
	* @return 
	* 
	*/		
PlayerInfoVo* RoleManage::getMercenary(int id)
{
	if(_mercList.find(id) != _mercList.end())
		return &(_mercList[id]);
    return 0;
}
		
/**
	* @return 
	* 
	*/		
PlayerInfoVo* RoleManage::roleInfo()
{
	return getMercenary(_accountInfo.roleId);
}
		
std::map<int ,PlayerInfoVo>* RoleManage::mercList()
{
	return &_mercList;
}

std::map<RoleManage::MercKeyIndex, PlayerInfoVo>* RoleManage::mercListEx()
{
	return &_mercListEx;
}
		
std::map<int, PlayerInfoVo>* RoleManage::cfgMercList()
{
	return &_cfgMercList;
}
		
		
void RoleManage::playlist(std::map<int, PlayerInfoVo> &value)
{
	_playlist=value;
}
		
std::map<int, PlayerInfoVo>* RoleManage::playlist()
{
	return &_playlist;
}
		
/**
	* @param id
	* 
	*/		
void RoleManage::currentId(int id)
{
	_currentId = id;
}
		
int RoleManage::currentId()
{
	return _currentId;
}
/**
	* @return int
	* 
	*/		
int RoleManage::currentFigureLev()
{
	PlayerInfoVo* info = getMercenary(_currentId);

	if(!info)
		return 0;

	return info->playerBaseInfo._lev;
}
		
/**
	* @return int
	* 
	*/	
int RoleManage::currentFigureCareer()
{
	PlayerInfoVo* info =getMercenary(_currentId);
	if(!info)
		return 0;

	return info->playerBaseInfo.career;
}
		
bool RoleManage::isRole()
{
	return _currentId == _accountInfo.roleId;
}
		
/**
	* @param sitGrid
	* @return 
	* 
	*/		
GoodsInfo* RoleManage::getSitGridEquip(int sitGrid)
{
	return EquipmentManager::Instance()->getEquip(_currentId, sitGrid);
}

/**
* @return 
* 
*/		
bool RoleManage::roleOpe()
{
	PlayerInfoVo* playerInfo = roleInfo();
	if(!playerInfo)
		return false;

	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic( playerInfo->playerBaseInfo._mapId);
	if(!sceneVo)
		return false;

	if(sceneVo->type == SceneType::COPY)
	{
		AccountInfoVo* acVo = accountInfo();

		if(!acVo || acVo->team == 2)
		{
			return false;
		}
	}
	return true;
}

int RoleManage::roleLev()
{
	PlayerInfoVo *pPlayerInfoVo = roleInfo();
	if(pPlayerInfoVo)
	{
		return pPlayerInfoVo->playerBaseInfo._lev;
	}
	return -1;
}

int RoleManage::getAccountIdByMerhId(int merhId)
{
	std::map<int, PlayerInfoVo>::iterator iter =  _mercList.begin();
	for (iter ; iter != _mercList.end() ; iter++)
	{
		if (iter->second.playerBaseInfo.cloth == merhId)
		{
			return iter->first;
		}
	}
	return 0;
}