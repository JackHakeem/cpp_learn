#include "CrystalCommand.h"
#include "model/skill/SkillManager.h"
#include "model/crystal/vo/CrystalType.h"
#include "socket/command/c19/CCMD19C.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/s18/SCMD18A.h"
#include "model/player/RoleManage.h"
#include "socket/command/s18/SCMD185.h"
#include "model/crystal/CrystalProxy.h"
#include "view/crystal/CrystalMediator.h"
#include "model/crystal/CrystalManager.h"
#include "socket/command/s19/SCMD19D.h"
#include "socket/command/s18/SCMD186.h"
#include "utils/ValuesUtil.h"
#include "Message.h"

CrystalCommand::CrystalCommand()
{
	_crystalProxy		= (CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
//	_crystalProxy->autorelease();
	_taskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
}

CrystalCommand::~CrystalCommand()
{
	std::map<int, CrystalInfo*>::iterator it;
	for ( it = idToVo.begin(); it != idToVo.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	idToVo.clear();
}

void CrystalCommand::execute( int32 command, char* data )
{
	switch(command)
	{
	case INIT_CRYSTALS:
		initAccountInfo( data);
		initCrystals(data);
		break;
	case INIT_ACCOUNT_INFO:
		initAccountInfo( data);
		 break;
	case UPDATE_CRYSTALS:
		updateCrystals( data);
		break;
	case LINK_ITEMS_TO_DICT:
		linkItemsToDict(data);
		break;
	case UPGRADE_CRYSTALS:
		upgradeCrystals(data);
	case UPGRADE_CDTIME:
		updateCDTime(data);
		break;
	case UPGRADE_CDLIST:
		updateCDList(data);
		break;
	default:
		break;
	}
}

void CrystalCommand::sendCDListRequest(int id)
{
	CCMD19C* s = new CCMD19C();
	if (s)
	{
		s->a_type	= int8(3);
		s->b_id = (int16)id;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(s);
		}
		cocos2d::CCLog("Crystal:Crystal %d CDList Request:CCMD19C",id);
	}
	SAFE_DELETE(s);
}

void CrystalCommand::initCrystals(char * data)
{
	CCLog("Crystal:begin Command::initCrystals()");
	SkillManager* sm=SkillManager::Instance();
	for(uint32 i=0;i<CrystalType::CRYSTAL_NUM;i++)
	{
		int id=CRYSTALS[i];
		if(idToVo.find(id)!=idToVo.end())
		{
			CrystalInfo* item=idToVo.find(id)->second;
			item->name = sm->getSkill(id)->name;
			item->des = sm->getSkill(id)->des;
			char tmp[40] = {0};
			sprintf(tmp,"CAT%d",i);
			item->tip= ValuesUtil::Instance()->getString(tmp);//ACTIVETIP[i];
		}
		else
		{
			CrystalInfo* info=new CrystalInfo();
			info->name=sm->getSkill(id)->name;
			info->level=0;
			info->time=0;
			info->des=sm->getSkill(id)->des;
			char tmp[40] = {0};
			sprintf(tmp,"CAT%d",i);
			info->tip=ValuesUtil::Instance()->getString(tmp); //ACTIVETIP[i];
			idToVo.insert(make_pair(info->id, info));
		}
	}
	//send CD List Request
	for(uint32 i=0;i<CrystalType::CRYSTAL_NUM;i++)
	{
		sendCDListRequest(CRYSTALS[i]);
	}
	_crystalProxy->initCrystal(data);
}
	 
// init crystal data
void CrystalCommand::initAccountInfo( char* data )   
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
			RoleManage::Instance()->_accountInfo._crystalLev = node.b_level;
			// task activate until the role is initialized 
			_taskProxy->initCanTaskList(node.b_level);
		}
		if(idToVo.find(id)!=idToVo.end())
		{
			CrystalInfo* info = idToVo.find(id)->second;
			info->level = node.b_level;
		}
		else
		{
			CrystalInfo* info = new CrystalInfo();
			info->id = id;
			info->level = node.b_level ;
			idToVo.insert(make_pair(id, info));
		}
	}
	// sliver limit
	if(idToVo.find(CrystalType::CRYSTAL_SHUI)!=idToVo.end())
	{
		CrystalInfo* info=idToVo.find(CrystalType::CRYSTAL_SHUI)->second;
		int lev=info->level;
	    lev = lev>0?lev:1;
	    RoleManage::Instance()->_accountInfo._silverLim = 99990000/*lev * 25000  + 5000000*/;
	}
	_crystalProxy->initCrystal(data);
}

// activate
void CrystalCommand::updateCrystals( char* data )
{
	SCMD186 * tmpdate = (SCMD186 *) data;  
	if(!tmpdate) return;
	if(2 == tmpdate->a_result)
	{
		if(idToVo.find(tmpdate->b_id)!=idToVo.end())
		{
			CrystalInfo* info=idToVo.find(tmpdate->b_id)->second;

			// LH20121030
			//info->level=tmpdate->c_level;
			info->level = RoleManage::Instance()->roleLev();

			if (tmpdate->b_id == CrystalType::CRYSTAL_SHUI)
			{
				RoleManage::Instance()->_accountInfo._silverLim = 99990000/*tmpdate->c_level * 25000  + 5000000*/;
			}
			
		}
		tmpdate->c_level = RoleManage::Instance()->roleLev();
		_crystalProxy->updateCrystal((char *)tmpdate);

//		Message::Instance()->show(ValuesUtil::Instance()->getString("CSL25").c_str(),ccc3(12,233,25),1.0f);
	}


	struct Data
	{
		int type;
		int lev;
	};
	Data *pData = new Data();
	pData->type = tmpdate->b_id;
	pData->lev = tmpdate->c_level;
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::CRYSTAL_LEVEL_CHANGE, pData);

	CC_SAFE_DELETE(pData); // jae0813
}

// update CD Time
void CrystalCommand::updateCDTime(char * data)
{
	SCMD19D* tmpdata=(SCMD19D*)data;
	if(!tmpdata) return;
	if(idToVo.find(tmpdata->b_id)!=idToVo.end())
	{
		CrystalInfo* info=idToVo.find(tmpdata->b_id)->second;
		info->time=tmpdata->c_time;
		CCLog("Crystal:CD id:%d,time:%d",tmpdata->b_id,tmpdata->c_time);
	}
	// note to view to update CD list
	_crystalProxy->crystalCDTime(data);
}

//update left CD time
void CrystalCommand::updateCDList(char * data)
{
	_crystalProxy->crystalCDList(data);
}

// upgrade
void CrystalCommand::upgradeCrystals( char* data)
{

	SCMD185* tmpdata=(SCMD185*)data;
	switch(tmpdata->b_id)
	{
	case CrystalType::CRYSTAL_MAIN:		// update the main crystal level
		RoleManage::Instance()->_accountInfo._crystalLev = tmpdata->c_level;
		break;
	case CrystalType::CRYSTAL_SHUI:		// shui crystal impact the limit of money
		int lev =tmpdata->c_level;
		RoleManage::Instance()->_accountInfo._silverLim = 99990000 /*lev * 25000  + 5000000*/;
		break;
	}
	if(idToVo.find(tmpdata->b_id)!=idToVo.end())
	{
		CrystalInfo* info = idToVo.find(tmpdata->b_id)->second;
		if (info && info->level < tmpdata->c_level)
		{
			info->level=tmpdata->c_level;
		}
	}
	_crystalProxy->upgradeCrystal(data);
}

// init crystal data 		
void CrystalCommand::initData()
{
	for(uint32 i=0;i<CrystalType::CRYSTAL_NUM;i++)
	{
		CrystalInfo* info=new CrystalInfo();
		int id = CRYSTALS[i];
		info->id=id;
		info->name="";
		info->level=0;
		info->tip="";
		info->des="";
		info->time=0;
		idToVo.insert(make_pair(id,info));
	}

}

std::map<int, CrystalInfo*> CrystalCommand::getIdToVo()
{
	CrystalProxy* cp=(CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);

	return cp->_idToVos;

}

std::map <int,CrystalInfo*> CrystalCommand::getItemToVo()
{
	CrystalProxy* cp=(CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	return cp->_itemToVos;
}

// crystal object to map
void CrystalCommand::linkItemsToDict( char* data )
{
	/*std::map <int,CrystalInfo *> items=(std::map <int,CrystalInfo *>&)data;
	std::map <int,CrystalInfo *>::iterator it1;
	for(it1=items.begin();it1!=items.end();it1++)
	{


	}*/
}


		 
