#include "RecruitProxy.h"
#include "vo/DismissVo.h"
#include "vo/RecruitInfo.h"
#include "vo/RookieVo.h"
#include "../player/vo/PlayerInfoVo.h"
#include "../player/FigureBaseManage.h"
#include "mvc/Facade.h"
#include "view/recruit/RecruitMediator.h"
#include "control/AppFacade.h"
#include "../player/RoleManage.h"
#include <algorithm>

RecruitProxy::RecruitProxy()
{

}

RecruitProxy::~RecruitProxy()
{
	map< int, DismissVo* >_dismissDic;
	vector<RecruitInfo*> _storyList;
	vector<RecruitInfo*> _fameList;

	for ( map< int, DismissVo* >::iterator it = _dismissDic.begin(); it != _dismissDic.end(); it++ )
	{
		CC_SAFE_DELETE(it->second);
	}
	_dismissDic.clear();

	for ( uint i = 0; i < _storyList.size(); i++ )
	{
		CC_SAFE_DELETE( _storyList[i] );
	}
	_storyList.clear();

	for ( uint i = 0; i < _fameList.size(); i++ )
	{
		CC_SAFE_DELETE( _fameList[i] );
	}
	_fameList.clear();
}

/**
* never recuit
* @param list Array never tecuit array
*/ 
void RecruitProxy::initRookieList( vector<RookieVo*> list )
{  // all is juqing's 
	for ( uint i = 0; i < list.size(); i++ )
	{
		RookieVo* rookie = list[i];
		if ( !rookie )
		{
			continue;
		}
		RecruitInfo* info = new RecruitInfo();
		FigureCfgBaseVo* baseVo = FigureBaseManage::Instance()->getMercBase(rookie->mercId);
		if( !baseVo || baseVo->needPop > 0 )
		{  // 
			continue;
		}
		info->setBaseProperty( baseVo );
		info->mercId = rookie->mercId;
		info->id = 0;
		info->isHired = false;
		_storyList.push_back(info);
	}
	sendNotification( Facade_Mediator, AppFacade_RECRUIT_PROXY_CHANGE, 0, RecruitMediator::DATA_CHANGE );
}
		
/**
* update ever recuit figure list
* @param list Array
*/  
void RecruitProxy::initDismissList( vector<DismissVo*> list )
{  // include juqing and mingsheng
	for ( uint i = 0; i < list.size(); i++ )
	{
		DismissVo* dismiss = list[i];
		if ( !dismiss )
		{
			continue;
		}
		if (  (dismiss->mercId < 0)  )
		{
			continue;
		}

		RecruitInfo* info = new RecruitInfo();
		FigureCfgBaseVo* baseVo = FigureBaseManage::Instance()->getMercBase( dismiss->mercId );		 
		info->setBaseProperty(baseVo);
		info->mercId = dismiss->mercId;
		info->id = dismiss->id; 
		info->isHired = false;
		info->level = dismiss->level;
		info->intell = dismiss->intellect;
		info->stamina = dismiss->stamina;
		info->strength = dismiss->strength;
		info->rebornNum = dismiss->reborn;
		_storyList.push_back(info);

		map< int, DismissVo* >::iterator it = _dismissDic.find(dismiss->mercId);
		if (it!=_dismissDic.end())
		{
			CC_SAFE_DELETE(it->second);
			_dismissDic.erase(it);
		}
		_dismissDic.insert(make_pair(dismiss->mercId, dismiss));
		
	}
	sendNotification( Facade_Mediator, AppFacade_RECRUIT_PROXY_CHANGE, 0, RecruitMediator::DATA_CHANGE );
}
		
/**
* clear can recuit figure list
*/ 
void RecruitProxy::cleanRecruitList()
{
	for ( uint i = 0; i < _storyList.size(); i++ )
	{
		CC_SAFE_DELETE( _storyList[i] );
	}
	_storyList.clear();

	for ( uint i = 0; i < _fameList.size(); i++ )
	{
		CC_SAFE_DELETE( _fameList[i] );
	}
	_fameList.clear();
}
		
/**
* Save and login in again, after this, allows to be fired figure
*/
void RecruitProxy::saveDismissedMerc( PlayerInfoVo* playerInfoVo )
{
	if ( !playerInfoVo )
	{
		return;
	}
	DismissVo* dismissVo = new DismissVo;
	dismissVo->id = playerInfoVo->playerBaseInfo.id;
	dismissVo->intellect = playerInfoVo->figureBaseInfo.intellect;
	dismissVo->level = playerInfoVo->playerBaseInfo.lev();
	dismissVo->mercId = playerInfoVo->figureBaseInfo.mercId;
	dismissVo->stamina = playerInfoVo->figureBaseInfo.stamina;
	dismissVo->strength = playerInfoVo->figureBaseInfo.strength;
 		
	dismissVo->reborn = playerInfoVo->figureBaseInfo.rebornNum;
	dismissVo->maxhp = playerInfoVo->playerBaseInfo.maxHp();

	_dismissDic[dismissVo->mercId] = dismissVo;

	FigureCfgBaseVo* baseVo = FigureBaseManage::Instance()->getMercBase(dismissVo->mercId);
	if(baseVo&& (baseVo->needPop > 0) )
	{  // 
		std::map<int, PlayerInfoVo>* cfgDic = RoleManage::Instance()->cfgMercList();
		std::map<int, PlayerInfoVo>::iterator it = cfgDic->find( dismissVo->mercId );

		if( it != cfgDic->end() )
		{
			cfgDic->erase( it ); // delte index but not null
			//delete cfgDic[dismissVo.mercId]; 
 		}
	}
}
		
void RecruitProxy::recruitMerc( int id )
{
	sendNotification( Facade_Mediator, AppFacade_RECRUIT_PROXY_CHANGE, (char*)id, RecruitMediator::RECRUIT_MERC );
}
		
void RecruitProxy::dismissMerc( int mercId /*= 0*/ )
{
	sendNotification( Facade_Mediator, AppFacade_RECRUIT_PROXY_CHANGE, (char*)mercId, RecruitMediator::DISMISS_MERC );
}
	 
/**
* getDismissVoByMercId
*/
DismissVo* RecruitProxy::getDismissVoByMercId( int mercId )
{
	return _dismissDic[mercId] ;
}
		
/**
* @param mercId int ID
* @return
*/
Number RecruitProxy::getRecruitSilver( int mercId )
{
	FigureCfgBaseVo* figureCfgBaseVo = FigureBaseManage::Instance()->getMercBase(mercId);
	if(!figureCfgBaseVo) return -1;
	return figureCfgBaseVo->silver;
}
//				
/**
* recruitList
*/
vector<RecruitInfo*> RecruitProxy::recruitList()
{
	return _storyList;
}
/**
	* 可招募名声佣兵列表
	*/
vector<RecruitInfo> RecruitProxy::fameList()
{
	vector<RecruitInfo> infos;

	AccountInfoVo* pAccountInfoVo = RoleManage::Instance()->accountInfo();
	if ( !pAccountInfoVo )
	{
		return infos;
	}
	
	//std::map<int, PlayerInfoVo>* mercDic = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator it = mercDic->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* mercDic = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex , PlayerInfoVo>::iterator it = mercDic->begin();
	RecruitInfo* recruitInfo = 0;
	for (it ;  it != mercDic->end(); it++ )
	{
		RecruitInfo recruitInfo;
		recruitInfo.isHired = true;
		recruitInfo.setPlayInfo( &it->second );
		if( recruitInfo.needPop == 0 )	continue;
		if( recruitInfo.isRole )	continue;
		infos.push_back( recruitInfo );
	}

	// 处理配置的名声佣兵且不在已招募列表
	std::map<int, FigureCfgBaseVo>* dic = FigureBaseManage::Instance()->getCfgMercList();
	std::map<int, PlayerInfoVo>* roleDic = RoleManage::Instance()->cfgMercList();

	vector<RecruitInfo> cfgInfos;
	vector<RecruitInfo> tCfgInfos;
	for ( std::map<int, FigureCfgBaseVo>::iterator it = dic->begin(); it != dic->end(); it++ )
	{
		FigureCfgBaseVo* pFigureCfgBaseVo = &it->second;
		// 遍历所有的原型佣兵 
		if( !pFigureCfgBaseVo || pFigureCfgBaseVo->needPop == 0 )	continue;
		if(  roleDic->find(pFigureCfgBaseVo-> mercId ) != roleDic->end()  )		continue;

		RecruitInfo info;
		info.setBaseProperty( pFigureCfgBaseVo );
		map< int, DismissVo* >::iterator itDismiss = _dismissDic.find( it->first );
		if( itDismiss != _dismissDic.end() )
		{
			DismissVo* dismiss = itDismiss->second;
			info.mercId = dismiss->mercId;
			info.id = dismiss->id;
			info.isHired = false;
			info.level = dismiss->level;
			info.intell = dismiss->intellect;
			info.stamina = dismiss->stamina;
			info.strength = dismiss->strength;
			info.rebornNum = dismiss->reborn;
			info.maxHp = dismiss->maxhp;
			info.blood = dismiss->maxhp;
		}
		if( pAccountInfoVo->popularity() >=pFigureCfgBaseVo->needPop )
		{
			cfgInfos.push_back(info);
		}
		else
		{
			tCfgInfos.push_back(info);
		}
	}
			
	//tCfgInfos.sortOn(["needPop"], [Array.NUMERIC]);  // sort important！！
	int uSizetCfg = tCfgInfos.size();
	for ( int i = 0; i < uSizetCfg-1; i++ )			//infos.sortOn(["needPop"], [Array.NUMERIC]);
	{
		for ( uint j = 0; j < uSizetCfg-i-1; j++ )
		{
			if ( tCfgInfos[j].needPop > tCfgInfos[j+1].needPop )
			{
				RecruitInfo temp = tCfgInfos[j];
				tCfgInfos[j] = tCfgInfos[j+1];
				tCfgInfos[j+1] = temp;
			}
		}
	}

	int g = 2;  // 两个灰色名声佣兵
	for ( uint i = 0; i < tCfgInfos.size(); i++ )
	{
		RecruitInfo* cfgInfo = &tCfgInfos[i];
		if(  cfgInfo->needPop > pAccountInfoVo->popularity()  )
		{
			//infos.push_back( cfgInfo );
			cfgInfo->isGray = 1;
			if( g<=0 )
			{
				cfgInfo->isGray = 2;
			}
			g--;
			cfgInfos.push_back(*cfgInfo);
		}
	}

	int uSize1 = infos.size(), uSize2 = cfgInfos.size();
	for ( int i = 0; i < uSize1-1; i++ )			//infos.sortOn(["needPop"], [Array.NUMERIC]);
	{
		for ( uint j = 0; j < uSize1-i-1; j++ )
		{
			if ( infos[j].needPop > infos[j+1].needPop )
			{
				RecruitInfo temp = infos[j];
				infos[j] = infos[j+1];
				infos[j+1] = temp;
			}			
		}		
	}
	

	for ( int i = 0; i < uSize2; i++ )		//cfgInfos.sortOn(["needPop"], [Array.NUMERIC]);
	{
		for ( int j = 0; j < uSize2-i-1; j++ )
		{
			if ( cfgInfos[j].needPop > cfgInfos[j+1].needPop )
			{
				RecruitInfo temp = cfgInfos[j];
				cfgInfos[j] = cfgInfos[j+1];
				cfgInfos[j+1] = temp;
			}

		}		
	}
	
	for ( int i = 0; i < uSize2; i++ )	//infos = infos.concat(cfgInfos);
	{
		infos.push_back( cfgInfos[i] );
	}
	
	return infos;
}
/**
* storyList
*/
vector<RecruitInfo> RecruitProxy::storyList()
{
	vector<RecruitInfo> infos;
	vector<int> selfList; // 
			
	//RecruitInfo* recruitInfo = 0;
	//std::map<int, PlayerInfoVo>* mercDic = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator itPlayerInfo = mercDic->begin(); 
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* mercDic = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator itPlayerInfo = mercDic->begin();
	for (itPlayerInfo ; itPlayerInfo != mercDic->end(); itPlayerInfo++ )
	{
		PlayerInfoVo* pPlayerInfoVo = &itPlayerInfo->second;
		RecruitInfo recruitInfo;
		recruitInfo.isHired = true;
		recruitInfo.setPlayInfo( pPlayerInfoVo );
		if ( recruitInfo.needPop > 0 )		continue;
		if ( recruitInfo.isRole )		continue; // role pass

		for ( int i = 0; i < _storyList.size(); i++ )
		{
			RecruitInfo* storyInfo = _storyList[i];
			if ( storyInfo->mercId == recruitInfo.mercId )
			{
				selfList.push_back( storyInfo->mercId );
			}
		}

		infos.push_back( recruitInfo );
	}

	for ( int i = 0; i < _storyList.size(); i++ )
	{
		RecruitInfo* info = _storyList[i];
		if( info->needPop == 0 )
		{
			bool bNotInclude( true );
			for ( int j = 0; j <selfList.size(); j ++ )
			{
				if ( info->mercId == selfList[j] )
				{
					bNotInclude = false;
				}				
			}
			if( bNotInclude )
			{
				map< int, DismissVo* >::iterator itDismiss = _dismissDic.find( info->mercId );
				if( itDismiss != _dismissDic.end() )
				{
					DismissVo* dismiss = itDismiss->second;
					info->mercId = dismiss->mercId;
					info->id = dismiss->id; 
					info->isHired = false;
					info->level = dismiss->level;
					info->intell = dismiss->intellect;
					info->stamina = dismiss->stamina;
					info->strength = dismiss->strength;
					info->rebornNum = dismiss->reborn;
					info->maxHp = dismiss->maxhp;
					info->blood = dismiss->maxhp;
				}
				
				if( info->isRole )	continue;
				infos.push_back( *info );
			}
		}
	}

	std::map<int, PlayerInfoVo>* roleDic = RoleManage::Instance()->cfgMercList();
	vector<RecruitInfo> rawArr;
	std::map<int, FigureCfgBaseVo>* dic = FigureBaseManage::Instance()->getCfgMercList();
	std::map<int, FigureCfgBaseVo>::iterator itFigureCfgBase = dic->begin();

	for( ; itFigureCfgBase != dic->end(); itFigureCfgBase++ )
	{  // pass through all figures 
		int key = itFigureCfgBase->first;
		FigureCfgBaseVo* pFigureCfgBaseVo = &itFigureCfgBase->second;
		if( key <= 10 )	continue; // pass built figures
		if(  pFigureCfgBaseVo->needPop > 0 )continue;
		
		if(  roleDic->find( pFigureCfgBaseVo->mercId ) != roleDic->end()  )		continue;
		if( _dismissDic.find(key) != _dismissDic.end() )	continue;
				
		bool has = false;
		for ( uint k = 0; k < infos.size(); k++ )
		{
			RecruitInfo& p = infos[k];
			if( p.mercId == key )
				has=true;
		}
		if(has)	continue;
				
		RecruitInfo info;
		info.setBaseProperty( pFigureCfgBaseVo );
		info.isGray = 2;

		if( info.isRole )	continue;
		rawArr.push_back(info);
		//infos.push_back(info);
	}

	uint uSize1 = rawArr.size();
	for ( int i = 0; i < uSize1; i++ )			//rawArr.sortOn(["order"], [Array.NUMERIC]);
	{
		for ( int j = 0; j < uSize1-i-1; j++ )
		{
			if ( rawArr[j].order > rawArr[j+1].order )
			{
				RecruitInfo temp = rawArr[j];
				rawArr[j] = rawArr[j+1];
				rawArr[j+1] = temp;
			}
		}		
	}
	
	for ( int i = 0; i < uSize1; i++ )		//return infos.concat(rawArr);
	{
		infos.push_back( rawArr[i] );
	}
	return infos;
}
		
/**
* hasData
*/
bool RecruitProxy::hasData()
{
	return _storyList.size()>0?true:false;
}
		
bool RecruitProxy::hasFameDate()
{
	return _fameList.size()>0?true:false;
}