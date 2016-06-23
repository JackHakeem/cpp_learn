#ifndef _MAINSTRENGMEDIATOR_H_
#define _MAINSTRENGMEDIATOR_H_

#include "mvc/Mediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "components/MagicPanel.h"
#include "socket/command/s2d/SCMD2DF.h"
#include "components/HeritagePanel.h"

class GameDispatcher;
class RoleManage;
class MainStrengView;
class StrengPanel;
class MeltingPanel;
class SCMD181;
class SCMD2D3;
class SCMD2D7;
class SCMD2D9;
class SCMD2DB;
class SCMD17D;

class MainStrengMediator:public Mediator
{
public:
	enum
	{
		STRENG_VIEW_TIP = 0,
	};
public:
	MainStrengMediator();
	~MainStrengMediator();
public:
	virtual void handleNotification(int M2Vcmd, char* data);
	void mainViewPop();
	void mainOpenPop(CCNode* n, void* data);
	void equipmentOnclickHandler(CCNode* n, void* data);
	void openStreng();
	void createList();
	void getBagEquipment();
	void cdChangedHandler( CCNode* n, void* data );
	void onTabClick( int roleId );	// TabClick(man or bag)
	//void updateStrengTip( char* obj );	// update tips
	void sendSocketDynamic( int location, int sitNum, int roleId /*= 0*/ );
	void sockStrengInfo( SCMD181* param );	// response
	StrengPanel* getStrengPanel();
	void tabChange( int type );
	//----------melting
	void bagPageChange( );
	void gridClickHandler( CCNode* n, void* data );
	void meltingClickHandler( CCNode* n, void* data );
	void returnMeltingInfo( SCMD2D3* param );
	void openMagic();
	void createMagicList();
	void getMagicBagEquipment();
	void equipmentMagicHandler( CCNode* n, void* data );
	void returnMagicResult( SCMD2D7* param );
	void figureClickHandler( int roleID );

	//----------inherit
	//void inheritClickHandler( CCNode* n, void* data );
	//void returnInheritList( SCMD2D9* param );
	//void returnInheritResult( SCMD2DB* param );
	void updateStrengTip( char* obj );
	void sockStrengPROBchange( SCMD17D* param );

	void heritageClickHandler( CCNode* n, void* data );
	void returnHeritageResult( SCMD2DF* param );
public:
	GameDispatcher* _dispatcher;
	RoleManage* _roleManage;

	MainStrengView* _mainStrengView;

	StrengPanel* _strengPanel;
	MeltingPanel* _meltingPanel;
	MagicPanel* _magicPanel;
	HeritagePanel* _inheritPanel;

};

extern MainStrengMediator* g_pMainStrengMediator;

#endif