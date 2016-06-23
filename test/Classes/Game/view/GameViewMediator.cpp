#include "GameViewMediator.h"
#include "view/task/TaskFollowMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "scene/SceneMediator.h"
#include "mainStreng/MainStrengMediator.h"
#include "view/mainUI/MainUIMediator.h"
#include "view/smallMap/SmallMapMediator.h"
#include "levy/LevyMediator.h"
#include "control/scene/SceneCommand.h"
#include "report/ReportMediator.h"
#include "honor/HonorMediator.h"


GameViewMediator::~GameViewMediator()
{
	CC_SAFE_DELETE(g_pMainStrengMediator);
	CC_SAFE_DELETE(g_pLevyMediator);
	CC_SAFE_DELETE(g_pReportMediator);
	CC_SAFE_DELETE(g_pHonorMediator);
}

GameViewMediator::GameViewMediator()
{
}

void GameViewMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd) 
	{
	case GOTO_GAME_VIEW:
		gameViewAddChilds();
		break;
	}
}

void GameViewMediator::gameViewAddChilds()
{
	CCLog("------------------gameViewAddChilds");
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::STARTUP_GAME_SCENE);

	//jaeno

	sendNotification(Facade_Mediator, AppFacade_MainUIMediator, NULL, MainUIMediator::STARTUP_PEOPLE_UI);

	sendNotification(Facade_Mediator, AppFacade_SmallMapMediator, NULL, SmallMapMediator::STARTUP_SMALLMAP_UI);	

	sendNotification(Facade_Mediator, AppFacade_TASK_FOLLOW_MEDIATOR, NULL, TaskFollowMediator::ADD_TO_STAGE);

	//STARTUP_CD_LIST
	sendNotification(Facade_Mediator, AppFacade_MainUIMediator, NULL, MainUIMediator::STARTUP_CD_LIST);

	// MainStrengMediator
	g_pMainStrengMediator = new MainStrengMediator();
	//g_pMainStrengMediator->mainViewPop();
	// LevyMediator
	g_pLevyMediator = new LevyMediator();
	//g_pLevyMediator->loadReportSource();
	g_pReportMediator = new ReportMediator();
	g_pHonorMediator = new HonorMediator();

	SceneCommand* cmd = (SceneCommand*)g_pFacade->retrieveController(AppFacade_SCENE_COMMAND);
	if(cmd)
		cmd->setSceneInfo();
}
