#ifndef _TRAINVIEWMEDIATOR_H_
#define _TRAINVIEWMEDIATOR_H_

#include "model/train/vo/TrainManager.h"
#include "manager/CDManage.h"
#include "mvc/Mediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/train/TrainProxy.h"
#include "model/player/RoleManage.h"
#include "socket/command/s35/SCMD35A.h"
#include "components/TrainView.h"
#include "socket/command/s35/SCMD354.h"

class TrainViewMediator:public Mediator
{
public:
	enum
	{
		BEGIN_TRAINING = 0,
		END_TRAINING,
		RAPIC_LEAP,
		UPDATE_TRAIN_MODE,
	};
public:
	TrainViewMediator();
	~TrainViewMediator();
public:
	virtual void handleNotification(int M2Vcmd, char* data);
	void trainListListener( char* data );
	void startTrainHandler(  int mercId, int type, int model, int gold, int silver  );				//train start
	void selectMercHandler( int mercId );	//figure choose
	void openMercPanel( int id );
	void viewPop();
	void startTrainingListener( SCMD35A* param );
	void beginTraining( char* obj );
	void endTraining( char* obj );
	void updateExpHandler();
	void updateMercExp(int mercId);	//update exp
	void endTrainHandler( int mercId );
	void buyPositionHandler();
	void onAlertBuySit( CCObject* pObject );
	void onCancelBuySit( CCObject* pObject );
	void rapidLeapHandler( int mercId, int type );
	void changeModeListener( char* param );
	void endTrainingListener( char* param );
	void trainNumHandler();
	void updateRapicTips( int id );
	void rapicLeapListener(char* param );
	void rapicLeap( char* data );
	void buyPositionListener( SCMD354* param );
	void sitNumChangeHandler( int trainSit );
	void showUIHandler(CCNode* n, void* data);
	void updateLevHandler(CCNode* n, void* data);
	void cdChangeHandler( CCNode* n, void* data );
	void trainTimeEndHandler(int id);
public:
	TrainView* _trainView;
	TrainProxy* _trainProxy;
	TrainManager* _trainManager;
	CDManage* _cdManage;

	RoleManage* _roleManage;

	int m_buyPosNeedGold;
};
#endif