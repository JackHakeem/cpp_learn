#ifndef _GuildListenerMediator_H_
#define _GuildListenerMediator_H_

#include "mvc/Mediator.h"
#include "components/GuildView.h"
#include "socket/command/s1b/SCMD1B2.h"
#include "socket/command/s1c/SCMD1C3.h"
#include "socket/command/s1c/SCMD1C1.h"
#include "socket/command/s1b/SCMD1B7.h"
#include "socket/command/s1c/SCMD1C6.h"
#include "socket/command/s1b/SCMD1BF.h"
#include "socket/command/s1c/SCMD1C7.h"
#include "socket/command/s1b/SCMD1BC.h"
#include "socket/command/s1c/SCMD1CB.h"
#include "socket/command/s1c/SCMD1CD.h"
#include "socket/command/s1d/SCMD1D6.h"
#include "socket/command/s1b/SCMD1B8.h"
#include "components/GuildPreView.h"
#include "components/GuildEditView.h"

class GuildListenerMediator:public Mediator
{
public:
	enum
	{
		GET_INITDATA = 0,
	};
public:
	GuildListenerMediator();
	~GuildListenerMediator();

	void handleNotification( int M2Vcmd, char* data );
	void popHandler( CCNode* n, void* data );
	void popPreViewHandler( int param1 );
	void popViewHandler( int param );
	void myGuildInfoHandler();
	void guildInfoHandler();

	void getGListHandler( SCMD1B2* param );
	void getMBInfoHandler( SCMD1C3* param );
	void getMBListHandler( SCMD1C1* param );
	void newGuildSuccessHandler( SCMD1B7* param );
	void getTEListHandler( SCMD1C6* param );
	void viewListener();
	void editGuildInfoHandler(CCNode *pNode, void *pData);
	void creatGuildHandler(CCNode *pNode, void *pData);
	void guildListHandler(CCNode *pNode, void *pData);
	void guildSearchHandler(CCNode *pNode, void *pData);
	void disGuildHandler(CCNode *pNode, void *pData);
	void disGuildCancelHandler(CCNode *pNode, void *pData);
	void appointmentHandler(CCNode *pNode, void *pData);
	void applyGuildHandler(CCNode *pNode, void *pData);
	void applyListHandler(CCNode *pNode, void *pData);
	void approvalHandler(CCNode *pNode, void *pData);
	void memberListHandler(CCNode *pNode, void *pData);
	void memberInfoHandler(CCNode *pNode, void *pData);
	void defaultTecEditHandler(CCNode *pNode, void *pData);
	void tecListHandler(CCNode *pNode, void *pData);
	void expelMemberHandler(CCNode *pNode, void *pData);
	void updateEmblemHandler(CCNode *pNode, void *pData);
	void editGuildHandler(CCNode *pNode, void *pData);
	void exitGuildHandler(CCNode *pNode, void *pData);
	void addFriendHandler(CCNode *pNode, void *pData);
	void inviteTeamHander(CCNode *pNode, void *pData);
	void applyDonateViewData(CCNode *pNode, void *pData);
	void donateHandler(CCNode *pNode, void *pData);
	void popEditViewHandler(CCNode *pNode, void *pData);
	void popGuildView(CCNode *pNode, void *pData);
	void popPreGuildView(CCNode *pNode, void *pData);
	void popDonateViewHandler(CCNode *pNode, void *pData);
	void getGInfoHandler( SCMD1BF* param );
	void oprateHandler( SCMD1C7* param );
	void getApListHandler( SCMD1BC* param );
	void getApplyHandler(SCMD1CB* param);
	void exitGuildReturnHandler(SCMD1CD* param);
	void receiveDonateData( SCMD1D6* param );
	void showGuildTip(SCMD1B8* param);
	void appointSuccess();
	void donateSuccess();
	void expelledMember( string alertStr );
	void closeAllView();
	void preViewListener();
	void editViewListener(bool start);
	void donateViewListener();
	void openGuildInfoView(CCNode *pNode, void *pData);

public:
	GuildView* _view;				//公会主界面
	GuildPreView* _preView;		//公会列表界面
	GuildEditView* _editView;		//公会信息编辑界面
	//_donateView:DonateView;		//公会科技捐献界面
};
 
extern GuildListenerMediator* g_pGuildListenerMediator;

#endif