#ifndef _SCENE_WORLD_MEDIATOR_H_
#define _SCENE_WORLD_MEDIATOR_H_
#include "manager/layer/MapManage.h"
#include "components/WorldScene.h"
#include "mvc/Mediator.h"
#include "model/scene/vo/SceneVo.h"
#include "../BaseMediator.h"

class SceneWorldMediator : public BaseMediator
{
public:
	SceneWorldMediator();
	~SceneWorldMediator();
	virtual void handleNotification( int M2Vcmd, char* data );
	
	void createWorldScene();
	void showMap(CCNode* n, void* data);
	void createWorldSceneHandle();
	void childExitClick(CCNode* n, void* data);
	void returnPreMap();
	void captainExit(SceneVo* sceneVo);
	void memberExit(SceneVo* sceneVo);
	void backTown(CCNode* n, void* data);
	void findExit();
	void roleMove(CCNode* n, void* data);
	void showChildScene(CCNode* n, void* data);
	void resetLayerStar(int childId);
	void closeWorldScene();
	void dispose();
	void startListener();
	void triggerExit(CCNode* n, void* data);
	void addExit(CCNode* n, void* data);
	void addRole();
	void onClearCD();
	void onCancelAdd();
	void selectChildScene(CCNode* n, void* data);
	void returnFromWorldScene();
	void okFunc();
	void cancelFunc();
	void roleMoveElement(IElement* element);

public:
	
	enum
	{
		CREATE_WORLD_SCENE = 0,
		CLOSE_WORLD_SCENE,
		REMOVE_WORLD_SCENE,
		INIT_PROGRESS,
		WORLDBOSS_VISIBLE,
		WORLDBOSS_TIPS,
	};

	WorldScene *_worldScene;

	IElement currElement;
	int _sceneVoid;
	//MapManage *_pMapManage;

	//TipHelps *_pMineTips;
};
#endif