#pragma once

#include "BaseType.h"
#include "mvc/Mediator.h"


class GameDispatcher;
class CenterView;
class NoticeManager;
class MsgMediator:public Mediator
{
public:
	enum
	{
		NEW_FRIEND_MSG,
	};

	MsgMediator();

	void handleNotification(int M2Vcmd, char* data);
	void newFriendMsg();
	void showMsg(CCObject* pSender);
	void openNews();
	void addListener();
	void addFriendHandler(CCNode* n, void* data);
public:
	std::vector<CCObject*> _noteArr;
	GameDispatcher* _dispatcher;
	int32 _num;            //Œª÷√À≥–Ú;

	CCMenuItemSprite* _targetBtn;
	CCMenuItemSprite* _btnFriend;
	CenterView* _msgView;
//	NoticeManager* _noticeManage;
};