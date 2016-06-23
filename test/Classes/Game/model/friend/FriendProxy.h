#ifndef _FRIENDPROXY_H_
#define _FRIENDPROXY_H_

#include "mvc/Proxy.h"
#include "vo/FriendInfoVo.h"


class PlayerInfoVo;
class FriendProxy: public Proxy
{
public:
	FriendProxy();
	~FriendProxy();

	void resetCurrentList();
	void addLinkHuman(FriendInfoVo& info);
	uint32 totalNum();
	void addLater(FriendInfoVo info);
	bool hasOwnProperty(FriendInfoVo* vo, std::list<FriendInfoVo>* list=0);
	void deleteHumanByName(std::string name);
	void deleteLinkHuman(FriendInfoVo fInfo);
	std::list<int> currentIds();
	void setDerectPage(uint32 index, uint32 page);
	void _saveCurrentList();
	PlayerInfoVo* getplayInfo();
	FriendInfoVo getmyInfo();

public:
	CC_PROPERTY(uint32, _currentPage, page)
	CC_PROPERTY(uint32, _listNum, listNum)
	CC_PROPERTY(BlessInfoVo, _blessInfo, blessInfo)

	std::list<FriendInfoVo> _currentList;//存放当前列表玩家数据
	std::list<FriendInfoVo> _relashipList;//最近联系人列表
	std::vector<int32> _pageArr;//存放列表所在页码, 默认都是第一页
	/*
	_relashipList:Array = [];//最近联系人列表
	_pageArr:Array = [1,1,1,1];//存放列表所在页码, 默认都是第一页
	_currentPage:uint = 1;
	_blessInfo:BlessInfoVo;//祝福信息
	*/
};

#endif