#include "FriendProxy.h"
#include "model/player/FigureBaseManage.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"


FriendProxy::FriendProxy()
{
	_listNum = 0;
	_currentPage = 1;
	_pageArr.clear();
	_currentList.clear();
	for (int i = 0; i < 4; i++)
		_pageArr.push_back(1);
}

FriendProxy::~FriendProxy()
{}


/**保存当前列表*/
void FriendProxy::_saveCurrentList()
{
	if(_listNum == 1)//在线联系人列表， 客户端保存
		_relashipList = _currentList;

	_pageArr[_listNum] = _currentPage;//保存列表所在页码
}

/**设置当前要操作的列表*/
void FriendProxy::setlistNum(uint32 n)
{
	_saveCurrentList();//切换当前列表时，先保存当前列表信息
	_listNum = n;
			
	if(_listNum == 1)
		_currentList = _relashipList;
	else
		_currentList.clear();//非在线联系人列表，等待服务端数据
			
	_currentPage = _pageArr[_listNum];
}

/**得到当前列表代号*/
uint32 FriendProxy::getlistNum()
{
	return _listNum;
}

/**得到玩家自身信息*/
PlayerInfoVo* FriendProxy::getplayInfo()
{
	PlayerInfoVo* pInfo = RoleManage::Instance()->roleInfo();
	return pInfo;
}

/**得到玩家自身基本信息*/
FriendInfoVo FriendProxy::getmyInfo()
{
	AccountInfoVo accInfo =  RoleManage::Instance()->_accountInfo;
	FriendInfoVo friInfo;
	friInfo.id = accInfo.accountId;
	friInfo.level = RoleManage::Instance()->roleInfo()->playerBaseInfo.lev();
	friInfo.name = accInfo.name;
	friInfo.OF = 0;
	friInfo.cloth = getplayInfo()->playerBaseInfo.cloth;
	return friInfo;
}

/**
	* 清空当前列表 
	* 
	*/		
void FriendProxy::resetCurrentList()
{
	_currentList.clear();
}

/**
	* 得到当前列表条目总数，主要用于客户端保存的最近联系人列表 
	* @return 
	* 
	*/		
uint32 FriendProxy::totalNum()
{
	return _currentList.size();
}
	
/**增加当前列表*/
void FriendProxy::addLinkHuman(FriendInfoVo& info)
{
	if (_currentList.size() < 10)
	{
		FigureCfgBaseVo* figureBaseVo = FigureBaseManage::Instance()->getMercBase(info.avatarID);
		info.sex = figureBaseVo?figureBaseVo->sex : 1;//得到玩家性别
		info.cloth = figureBaseVo?figureBaseVo->cloth : 1;//得到玩家头像
		_currentList.push_back(info);
	}
}

//CC_PROPERTY(uint32, _currentPage, page)
/**
	* 设置当前页，翻页时同步 
	* @param num
	* 
	*/		
void FriendProxy::setpage(uint32 var)
{
	_currentPage = var;
}

/**
	* 得到当前页 
	* @return 
	* 
	*/		

uint32 FriendProxy::getpage()
{
	return _currentPage;
}

/**添加最近联系人*/
void FriendProxy::addLater(FriendInfoVo info)
{
	if(_currentList.size() < 10)
	{
		FigureCfgBaseVo* figureBaseVo = FigureBaseManage::Instance()->getMercBase(info.avatarID);
		info.sex = figureBaseVo?figureBaseVo->sex : 1;//得到玩家性别
		info.cloth = figureBaseVo?figureBaseVo->cloth : 1;//得到玩家头像
		info.OF = 0;
		info.blessDisable = 1;
		if(!hasOwnProperty(&info, &_relashipList))
			_relashipList.push_back(info);
	}
}

/**是否在对应列表存在玩家信息*/

bool FriendProxy::hasOwnProperty(FriendInfoVo* vo, std::list<FriendInfoVo>* list)
{
	if(!list)
		list = &_currentList;

	std::list<FriendInfoVo>::iterator info;
	for (info = list->begin(); info != list->end(); info++)
	{
		if(info->id == vo->id)
			return true;
	}
	return false;
}

/**删除联系人*/
void FriendProxy::deleteLinkHuman(FriendInfoVo fInfo)
{//用于删除客户端保存的在线联系人列表
	std::list<FriendInfoVo>::iterator vo;
	for (vo = _currentList.begin(); vo != _currentList.end(); vo++)
	{
		if (fInfo.id == vo->id)
		{
			_currentList.erase(vo);
			break;
		}
	}
//	var position:uint = _currentList.indexOf(fInfo);
//	var SPLICE:Array = _currentList.splice(position,1);		
}

void FriendProxy::deleteHumanByName(std::string name)
{
	std::list<FriendInfoVo>::iterator vo;
	for (vo = _currentList.begin(); vo != _currentList.end(); vo++)
	{
		if(vo->name == name)
			break;
	}

	deleteLinkHuman(*vo);
}

//CC_PROPERTY(uint32, _blessInfo, blessInfo)
/**设置玩家祝福信息*/
void FriendProxy::setblessInfo(BlessInfoVo var)
{
	_blessInfo = var;
}
		
/**返回玩家祝福信息*/
BlessInfoVo FriendProxy::getblessInfo()
{
	return _blessInfo;
}

/**
* 返回当前列表所有玩家的ID 
* @return 
* 
*/		
std::list<int> FriendProxy::currentIds()
{
	std::list<int> ids;

	std::list<FriendInfoVo>::iterator vo;
	for (vo = _currentList.begin(); vo != _currentList.end(); vo++)
	{
		ids.push_back(vo->id);
	}
	return ids;
}
	
/**
* 直接指定对应列表的请求page 
* @param index
* @param page
* 
*/		
void FriendProxy::setDerectPage(uint32 index, uint32 page)
{
	_pageArr[index] = page;
}

/*
		返回当前要显示的
		public function get currentList():Array{
			if(_currentList.length > 10)//最近联系人由客户端保存，可能不止一页，需要客户端实现翻页功能
				return _currentList.slice((_currentPage - 1) * 10, (_currentPage - 1) * 10 + 10);
			else
				return _currentList;
		}
		*/
		