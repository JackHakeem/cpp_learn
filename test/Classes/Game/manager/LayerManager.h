#ifndef _LAYERMANAGER_H_
#define _LAYERMANAGER_H_

#include "BaseType.h"
#include "manager/layer/WindowLayer.h"
#include "manager/layer/SceneUILayer.h"
#include "manager/layer/TipsLayer.h"
#include "manager/layer/ArenaUILayer.h"
#include "view/scene/components/Scene.h"
#include "view/scene/layer/FightLayer.h"
#include "layer/WorldLayer.h"
#include "view/scene/components/WorldScene.h"
#include "layer/LoadingLayer.h"
#include "view/newhand/components/NewhandLayer.h"
#include "manager/layer/IntervalLayer.h"
#include "manager/layer/SilverMineLayer.h"
#include "manager/layer/PreTipsLayer.h"

class LayerManager
{
public:
	static WindowLayer* windowLayer;
	static SceneUILayer *sceneUILayer;
	static BaseScene* sceneLayer;
	static BaseScene* storyLayer;
	static TipsLayer *tipsLayer;
	static WorldScene *worldLayer;

	//GPH 2012.3.28 Test add combat layer
	static FightLayer* fightLayer;
	
	static ArenaUILayer* arenaUILayer;

	static LoadingLayer* loadingPic;

	static NewhandLayer* newhandLayer;

	static CCLayer* battleLayer;

	static LayerNode* chatLayer;

	static IntervalLayer* intervalLayer;

	static SilverMineLayer* silverMineLayer;

	static PreTipsLayer* preTipsLayer;
};

#endif