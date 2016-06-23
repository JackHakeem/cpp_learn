#include "CrystalProxy.h"
#include "CrystalManager.h"
#include "vo/CrystalType.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "socket/command/s18/SCMD18A.h"
#include "../skill/SkillManager.h"
#include "utils/ValuesUtil.h"
#include "socket/command/s19/SCMD19D.h"
#include "socket/command/s18/SCMD185.h"

CrystalProxy::CrystalProxy()
{

}

CrystalProxy::~CrystalProxy()
{
	std::map <int,CrystalInfo*>::iterator it;
	for ( it = _idToVos.begin(); it != _idToVos.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}	
	_idToVos.clear();
}

void CrystalProxy::initData()
{
	/*
	SkillManager* sm=SkillManager::Instance();
	for(uint32 i=0;i<CrystalType::CRYSTAL_NUM;i++)
	{
		CrystalInfo* info=new CrystalInfo();
		int id = CRYSTALS[i];
		info->id=id;
		info->name=sm->getSkill(id)->name;
		info->level=0;
		info->tip="";
		info->des=sm->getSkill(id)->des;
		info->time=0;
		char tmp[40] = {0};
		sprintf(tmp,"CAT%d",i);
		info->tip=ValuesUtil::Instance()->getString(tmp); ;
		_idToVos.insert(make_pair(info->id,info));
	}
	*/
}

void CrystalProxy::initCrystal( char* data)
{
	initData();
	SCMD18A * s = (SCMD18A *)data;
	if(!s) return;
	//int n = s->a_items.size();
	std::list<SCMD18A::SCMD18ANode> *sn = (std::list<SCMD18A::SCMD18ANode>*)&s->a_items;
	if(!sn) return;
	std::list<SCMD18A::SCMD18ANode>::iterator it;
	for(it=sn->begin();it!=sn->end();it++)
	{
		SCMD18A::SCMD18ANode node=*it;
		uint32 id=node.a_id;
		if(id == CrystalType::CRYSTAL_MAIN)
		{
			//RoleManage::Instance()->_accountInfo._crystalLev = node.b_level;
			// task activate until the role is initialized 
			//_taskProxy->initCanTaskList(node.b_level);
		}
		if(_idToVos.find(id)!=_idToVos.end())
		{
			CrystalInfo* info = _idToVos.find(id)->second;
			info->level = node.b_level;
		}
		else
		{
			CrystalInfo* info = new CrystalInfo();
			info->id = id;
			info->level = node.b_level ;
			_idToVos.insert(make_pair(id, info));
		}
	}
	// sliver limit
// 	if(_idToVos.find(CrystalType::CRYSTAL_SHUI)!=_idToVos.end())
// 	{
// 		CrystalInfo* info=_idToVos.find(CrystalType::CRYSTAL_SHUI)->second;
// 		int lev=info->level;
// 		lev = lev>0?lev:1;
// 		RoleManage::Instance()->_accountInfo._silverLim = lev * 25000  + 1000000;
// 	}
	sendNotification(Facade_Mediator, AppFacade_CRYSTAL_PROXY_CHANGE, data, CrystalMediator::INIT_CRYSTAL);
}

void CrystalProxy::upgradeCrystal( char* data)
{
	SCMD185 * cmd = (SCMD185 *)data;
	if(_idToVos.find(cmd->b_id)!=_idToVos.end())
	{
		CrystalInfo* info = _idToVos.find(cmd->b_id)->second;
		if (info && info->level <cmd->c_level )
		{
			info->level=cmd->c_level;
		}		
	}
	sendNotification(Facade_Mediator, AppFacade_CRYSTAL_PROXY_CHANGE, data, CrystalMediator::UPGRADE_CRYSTAL);
}

void CrystalProxy::updateCrystal( char* data)
{
	sendNotification(Facade_Mediator, AppFacade_CRYSTAL_PROXY_CHANGE, data, CrystalMediator::UPDATE_VIEW);
}

// update CDList
void CrystalProxy::crystalCDTime(char *data)
{
	SCMD19D* tmpdata=(SCMD19D*)data;
	if(!tmpdata) return;
	if(_idToVos.find(tmpdata->b_id)!=_idToVos.end())
	{
		CrystalInfo* info=_idToVos.find(tmpdata->b_id)->second;
		info->time=tmpdata->c_time;
	}
	sendNotification(Facade_Mediator, AppFacade_CRYSTAL_PROXY_CHANGE, data, CrystalMediator::UPDATE_CDTIME);
}

void CrystalProxy::crystalCDList(char *data)
{
	sendNotification(Facade_Mediator, AppFacade_CRYSTAL_PROXY_CHANGE, data, CrystalMediator::UPDATE_CDLIST);
}

std::map <int,CrystalInfo*> CrystalProxy::getIdToVos()

{
	return this->_idToVos;
}

std::map <int,CrystalInfo*> CrystalProxy::getItemToVos()
{
	return this->_itemToVos;
}

int CrystalProxy::getCrystalLev(int id)
{
	int lev = 0;
	if(this->_idToVos.find(id) != this->_idToVos.end())
	{
		CrystalInfo* info = _idToVos.find(id)->second;
		lev = info->level;
	}
	return lev;
}

std::string CrystalProxy::getUpgradeTip(int type)
{
	int lev = getCrystalLev(type);
	std::string tip = CrystalManager::Instance()->getUpgradeTip(type, lev);
	return tip;
}

int CrystalProxy::getIndex(int id)
{
	for(int i=0; i<CrystalType::CRYSTAL_NUM; i++)
	{
		if(CRYSTALS[i] == id) return i;
	}
	return -1;
}
