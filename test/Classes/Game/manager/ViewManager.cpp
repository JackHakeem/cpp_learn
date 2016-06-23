//
//  ViewManager.cpp
//  HLQS
//
//  Created by edward liu on 12-2-23.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "ViewManager.h"
#include "view/mainStreng/components/StrengPanel.h"
#include "view/crystal/components/CrystalView.h"
#include "view/recruit/components/RecruitView.h"
#include "view/levy/components/LevyView.h"

ViewManager* _view_instance = NULL;

ViewManager::ViewManager()
{
	//_instance = NULL;
	figureView = 0;
	bagView = NULL;
	bankView = 0;
	dialogView = NULL;
	trainView = NULL;
	_scene = NULL;
	worldScene = NULL;
	_mainStrengView = 0;
	taskFollowView = 0;
	formationView = 0;
	//taskView = 0;
	strengPanel = 0;
	mainNavigate = 0;
	crystalView = 0;
	purchaseView = 0;
	arenaUI = 0;
	_peiyangView = 0;
	_skillView = 0;
	_upSkillView = 0;
	recruitView = 0;
	friendView = 0;
	_secNavigate = 0;
	_centerView = 0;
	dungeonEntrysView = NULL;
	storyMapsView = NULL;
	_roleUI = 0;
	challengeMapsView = NULL;
	_fightScene = NULL;
	_settingView = 0;
	_appointView = NULL;
	_mailView = 0;
	_mailButton = 0;
	_mailText = 0;
	_mailLight = 0;
	_helpButton = 0;
	_helpView = 0;
	dropCheckView = 0;
	_pWBMainView = 0;
	actView = 0;
	_WorldBossOpenTimeText = 0;

	poolView = 0;

	_pIdentifyView = 0;

	reportView = 0;

	_taskUIView= 0;
	_pVScrollUI = 0;
	_pDailyTaskExView = 0;
	levyView = 0;

	oreView = 0;

	_pOLRewardView = 0;
	_pTowerView = 0;
	_shopView = 0;
}

ViewManager::~ViewManager()
{
}

ViewManager* ViewManager::getInstance()
{
    if(_view_instance == NULL)
	{
        _view_instance = new ViewManager();
    }
    return _view_instance;
}

Scene* ViewManager::scene()
{
	return _scene;
}

void ViewManager::scene(Scene* scene)
{
	_scene = scene;
}

void ViewManager::detroyInstance()
{
	CC_SAFE_DELETE( _view_instance );
}
