#ifndef _RECRUITWMEDIATOR_H_
#define _RECRUITWMEDIATOR_H_
#include "mvc/Mediator.h"
#include "model/figure/EquipmentManager.h"
#include "model/train/vo/TrainManager.h"

class SCMD291;
class SCMD300;
class SCMD301;
class SCMD303;
class SCMD305;
class RecruitView;
class RecruitProxy;

class RecruitMediator:public Mediator
{
public:
	enum
	{
		DATA_CHANGE = 0,
		RECRUIT_MERC,
		DISMISS_MERC,
	};
public:
	RecruitMediator();
	~RecruitMediator();
	void handleNotification( int M2Vcmd, char* data );
	void viewPopHandler( CCNode* n, void* data );
	void viewPop();
	void closeHandler();
	void openHandler();
	void refreshView();
	void updateRecruitPanel();
	void proxyDataHandler(char* data);
	void firstOpen();
	void freshPanel();
	void changePageHandler();
	void popuChangeHandler();
	void recruitMercHandler( int mercId );
	void recruitMerc( int id );
	void dismissMerc( char* data );
	void dismissMercHandler( int mercId );
	void rookieListListener( SCMD300* param );
	void dismissListListener( SCMD301* param );
	void recruitListener( SCMD303* param );
	void dismissListener( SCMD305* param );
	void mercLimListener( SCMD291* param );

public:
	RecruitView* _recruitView;
	bool _firstOpen;
	EquipmentManager* _equipmentManager;
	TrainManager* _trainManager;
	RecruitProxy* _recruitProxy;

};
#endif