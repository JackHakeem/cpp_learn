#ifndef _MAINUIMEDIATOR_H_
#define _MAINUIMEDIATOR_H_

#include "mvc/Mediator.h"
#include "components/SecNavigate.h"
#include "components/RoleUI.h"
#include "socket/command/s16/SCMD16F.h"
#include "socket/command/s1d/SCMD1DF.h"
#include "socket/command/s2d/SCMD2D5.h"
#include "socket/command/s24/SCMD24F.h"

class MainNavigate;
class GameDispatcher;
class CDPanel;
class SCMD18D;
class SCMD2ED;

class MainUIMediator:public Mediator
{
public:
	enum
	{
		STARTUP_PEOPLE_UI = 0,
		//				STARTUP_DATA_BAR,
		//				CLOSE_DATA_BAR,
		STARTUP_TEAM_UI,
		ADD_QUIT_COPY_BTN,
		SET_QUIT_BTN_ENABLED,
		CLOSE_TEAM_UI,
		STARTUP_REPORT_UI,
		CLOSE_REPORT_UI,
		STARTUP_CD_LIST,
		STARTUP_SEC_NAV,
		IS_BAG_FULL,
		CHECK_FCM,
		STARTUP_TOKEN_BAR,
		SET_REPORT_VISIBLE,
		STARTUP_HELP_ICON,
		UPDATE_OLREWARD_CD,
		STARTUP_SCENE_NAME,
		SET_CDLIST_VISIBLE,
		SET_SEC_NAVIGATE_VISIBLE,
	};
	MainUIMediator();
	~MainUIMediator();
public:

	virtual void handleNotification(int M2Vcmd, char* data);

	void startUpPeopleView();
	void startUpCdList();

	void getMainUIInfo();

	void startUpSecondaryNavigate();

	void onRequestEnergy();
	void onAddEnergy();
	//Doyang 20120731
	void startListener();
	void changeVipLev(CCNode *pNode, void *pData);

	void updateGoldHandler( SCMD18D* param );

	//added by chenjian Begin
	void startupReportUI(int mapId);
	void closeReportUI();
	void setReportUIVisible(bool visible);
	//added by chenjian End
public:
	void initBuyEnergy(char *pPacket);
	void updateEnergy(char * pPacket);
	void updateSliverHandler(char * pPacket);
	void updateGoldHandler(char * pPacket);
	void updatePracticeHandler(char * pPacket);
	void updatePopularityHandler(char * pPacket);
	void updateGoodsDynamic( SCMD16F* param );
	void freeClearCDHandler( SCMD1DF* param );
	void updateStoneHandler( SCMD2D5* param );
	void mineTimeChange(CCNode* pSender, void* data);
	void mineOpenTime(SCMD2ED* param);
	void stepMineTime(float dt);
	void stepGongTime(float dt);
	void startUpTokenBar();
	void updateTokenInfo(SCMD24F* cmd);
public:
	GameDispatcher* _dispatcher;
	MainNavigate* _buttomView;

	CDPanel* _cdList;

	SecNavigate* _secNavigate;

	RoleUI * _roleUI;
};

#endif


