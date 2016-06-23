#ifndef _CHATMEDIATOR_H_
#define _CHATMEDIATOR_H_

#include "mvc/Mediator.h"
#include "socket/command/s19/SCMD191.h"
#include "socket/command/s19/SCMD193.h"
#include "socket/command/s19/SCMD197.h"
#include "socket/command/s19/SCMD199.h"

//class BankProxy;
//class BankView;
class ChatTextPanel;
class GameDispatcher;
class ChatView;
class GmView;
class PmView;
class ChatPopContainer;

class ChatMediator:public Mediator
{
public:

public:
	ChatMediator();
public:
	void handleNotification(int M2Vcmd, char* data);
	void startUpChatView();
	void addLoginTip();
	void pmChat(CCNode* n, void* data);
	void onChatError(SCMD199* param);
	void onWorldChat(SCMD191* param);
	void onGuildChat(SCMD193* param);
	void onPrivateChat(SCMD197* param);
	void chatResponse(uint32 channel, char* cmd);
	void showChatViewHandler();
	void sendMessage(CCNode* n, void* data);
	void specialSystemTips();
	void SystemNoticeCast(std::string content);
	void SystemAchiveCast(std::string content);
	void SystemChargeCast(std::string content);
	ChatPopContainer* getThisView();
public:

	GameDispatcher* _dispatcher;
	ChatPopContainer* _chatPopContainer;
	GmView* _gmView;
	PmView* _pmView;
	bool _isInFight;	//防止重复战斗
	ChatTextPanel* _textPanel; 				//聊天信息显示面板
};

#endif