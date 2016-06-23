#ifndef _FRIENDPROXYCOMMAND_H_
#define _FRIENDPROXYCOMMAND_H_

#include "mvc/SimpleCommand.h"

class FriendProxy;
class SCMD201;
class SCMD205;
class SCMD213;
class SCMD216;
class SCMD219;
class SCMD207;
class FriendProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		CREATE_FRIENDS_LIST,
		CREATE_LATER_LIST,
		CREATE_RECOMMEND_LIST,//组装推荐好友列表
		CREATE_BLACK_LIST,//组装黑名单列表
		ADD_LATER_LIST,//聊天发生私聊时触发, 增加最近联系人
		CHANGE_LIST_INDEX,//切换列表
		CHANGE_LIST_PAGE,//翻页
		PAGE_CHANGE_DERECT,//指定某列表下次请求页码
		REQUEST_FRIENDS_LIST,//请求好友列表
		REQUEST_RECOMMEND_LIST,//请求推荐好友列表
		REQUEST_BLACK_LIST,//请求黑名单列表
		ADD_FRIEND,//添加好友请求
		DELETE_FRIEND,//删除好友请求
		MOVE_TO_BLACK,//移到黑名单
		UPDATE_CURRENT_LIST,//请求当前列表
		CHECK_REQUEST,//处理好友请求
		RECEIVE_REQUEST,//接收好友请求
		BLESS_INFO,
		QUICK_ADD_RECOMMEND_FRIENDS,
		MOVE_FRIEND_OUT,
		REQUEST_FOR_CHAT,//发起聊天
		REQUEST_FOR_TROOP,//邀请组队
	};

public:
	FriendProxyCommand();
	~FriendProxyCommand(){}
	virtual void execute(int32 command, char* data);


public:
	void updateFList(SCMD201* param);
	void updateLList(SCMD213* param);
	void updateRList(SCMD205* param);
	void updateBList(SCMD207* param);
	void changeListIndex(uint32 index);
	void requestForLater(uint32 page = 1);
	void requestForREList(uint32 page = 1);
	void requestForFList(uint32 page = 1);
	void requestForBList(uint32 page = 1);
	void requestForPlayInfo(std::string name);
	void requestForAddF(std::string name = "");
	void requestForMTB(std::string name = "");
	void moveOutOfCurrentList(char* obj);
	void requestForDELF(std::string name);
	void checkAddReqHandler(char* obj);
	void blessInfoHandler(SCMD219* params);
	void quickAddRecFriHandler();
	void requestForChat(int32 id);
	void setPageDerect(char* obj);
	void changeListPage(uint32 page);
	void requestForCurrentList();
	void receiveRequest(SCMD216* param);
public:
	FriendProxy* _friendProxy;
};

#endif