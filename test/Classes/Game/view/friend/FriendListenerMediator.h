#ifndef _FRIENDLISTENERMEDIATOR_H_
#define _FRIENDLISTENERMEDIATOR_H_

#include "mvc/Mediator.h"
#include "model/player/vo/PlayerBaseVo.h"

class GameDispatcher;
class FriendView;
class SCMD201;
class SCMD205;
class SCMD207;
class SCMD20b;
class SCMD20d;
class SCMD20F;
class SCMD209;
class SCMD211;
class SCMD216;
class RequestAddInVo;
class NoticeManager;
class FriendListenerMediator:public Mediator
{
public:
	enum
	{
		GET_FRIENDSLIST,
		OPEN_REQ_PANEL,
	};

	FriendListenerMediator();

	void popHandler(CCObject* pSender);
	void loadReportSource();
	void popControl();
	void popView();
	void handleNotification(int M2Vcmd, char* data);
	void requestForFriendList(PlayerBaseVo* vo);
	void quickAddRecFriHandler(CCNode* n, void* data);
	void receiveFList(SCMD201* param);
	void receiveRList(SCMD205* param);
	void receiveBList(SCMD207* param);
	void receiveDFSuccess(SCMD20b* param);
	void receiveDBFLSuccess(SCMD211* param);
	void receiveMBSuccess(SCMD20d* param);
	void receiveDBSuccess(SCMD20F* param);
	void receiveRQSuccess(SCMD209* param);
	void receiveAddFriendRQ(SCMD216* param);

	void viewListener();
	void changeListHandler(CCNode* n, void* data);
	void deleteFriendHandler(CCNode* n, void* data);
	void addFriendHandler(CCNode* n, void* data);
	void changePageHandler(CCNode* n, void* data);
	void moveToBlackHandler(CCNode* n, void* data);
	void moveFriendOutHandler(CCNode* n, void* data);
	void openRequstTip(RequestAddInVo* obj);
	void popRequestTip();

public:
	uint32 _viewType;
	GameDispatcher* _gameDispatcher;
	FriendView* _view;
	RequestAddInVo* _obj;
	//NoticeManager* _noticManager;
};

#endif