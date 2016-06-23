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

	std::list<FriendInfoVo> _currentList;//��ŵ�ǰ�б��������
	std::list<FriendInfoVo> _relashipList;//�����ϵ���б�
	std::vector<int32> _pageArr;//����б�����ҳ��, Ĭ�϶��ǵ�һҳ
	/*
	_relashipList:Array = [];//�����ϵ���б�
	_pageArr:Array = [1,1,1,1];//����б�����ҳ��, Ĭ�϶��ǵ�һҳ
	_currentPage:uint = 1;
	_blessInfo:BlessInfoVo;//ף����Ϣ
	*/
};

#endif