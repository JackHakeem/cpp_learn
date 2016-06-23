//
//  ViewManager.h
//  HLQS
//
//  Created by edward liu on 12-2-23.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_ViewManager_h
#define HLQS_ViewManager_h

#include "cocos2d.h"
#include "view/dialog/components/DialogView.h"
#include "view/formation/components/FormationView.h"
#include "view/figure/components/FigureMainView.h"
#include "view/task/components/TaskFollowView.h"
#include "view/train/components/TrainView.h"
#include "view/scene/components/Scene.h"
#include "view/task/components/TaskView.h"
#include "view/crystal/components/CrystalView.h"
#include "view/scene/components/Scene.h"
#include "view/task/components/TaskView.h"
#include "view/crystal/components/CrystalView.h"
#include "view/scene/components/WorldScene.h"
#include "view/mainUI/components/MainNavigate.h"
#include "view/purchase/components/PurchaseView.h"
#include "view/figure/components/SkillView.h"
#include "view/figure/components/PeiyangView.h"
#include "view/skill/components/UpSkillView.h"
#include "view/mainUI/components/SecNavigate.h"
#include "view/noticeCenter/components/CenterView.h"
#include "view/dungeonEntrys/components/DungeonEntrysView.h"
#include "view/dungeonEntrys/components/StoryMapsView.h"
#include "view/mainUI/components/RoleUI.h"
#include "view/dungeonEntrys/components/ChallengeMapsView.h"
#include "view/scene/components/FightScene.h"
#include "view/mainStreng/components/StrengPanel.h"
#include "view/mainStreng/components/MainStrengView.h"
#include "view/backpack/components/BagView.h"
#include "view/smallMap/components/SmallMapUI.h"
#include "view/appoint/components/AppointView.h"
#include "view/guild/components/GuildView.h"
#include "view/guild/components/GuildPreView.h"
#include "view/worldBoss/components/WorldBossMainView.h"
#include "view/figure/components/IdentifyView.h"
#include "view/report/components/ReportView.h"
#include "view/task/components/TaskUIView.h"
#include "view/mainUI/components/VScrollUI.h"
#include "view/trader/components/TraderView.h"
#include "view/onlineReward/components/OnlineRewardView.h"
#include "view/tower/components/TowerView.h"
#include "view/levy/components/LevyView.h"
#include "view/shop/components/ShopView.h"

class DialogView;
class TrainView;
class BagView;
class BankView;
class MainStrengView;
class StrengPanel;
class CDPanel;
class CrystalView;
class ArenaUI;
class SkillView;
class PeiyangView;
class SmallMapUI;
class Map;
class RecruitView;
class FriendView;
class CenterView;
class LevyView;
class SettingView;
class MailView;
class NewHandHelpView;
class DropCheckView;
class ActView;
class PoolView;
class ReportView;
class DailyTaskExView;
class OreView;

class ViewManager
{
private:
    ViewManager();
    ~ViewManager();
    
public:
	static ViewManager* getInstance();
	static void detroyInstance();
	Scene* scene();
	void scene(Scene* scene);
public:
	
	// BaseScene * BaseScene; // scene layer
	DialogView * dialogView; // NPC dialog box
	BagView * bagView; // backpack panel
	BankView * bankView; // warehouse panel
	FormationView * formationView; // formation panels
	FigureMainView * figureView; // role panel
	TaskFollowView * taskFollowView; // task tip box
	//TaskView * taskView; // task panel
	CrystalView * crystalView; // crystal panel add 20120401
	TrainView * trainView;
	Scene * _scene;
	WorldScene * worldScene; // a map of the world
	MainStrengView * _mainStrengView; // strengthen panel
	StrengPanel * strengPanel; // strengthen panel

	SkillView * _skillView;
	UpSkillView * _upSkillView;
	PeiyangView * _peiyangView;

	MainNavigate* mainNavigate; // 主导航

	PurchaseView *purchaseView;

	ArenaUI* arenaUI;

	SmallMapUI* smallMapUI;  // 小地图

	Map* mapView;   // 城中地图 
	RecruitView* recruitView;

	FriendView* friendView;

	SecNavigate* _secNavigate;
	DungeonEntrysView* dungeonEntrysView;
	StoryMapsView* storyMapsView;
	ChallengeMapsView* challengeMapsView;


	CenterView* _centerView;


	LevyView* levyView;

	RoleUI * _roleUI;
	FightScene* _fightScene;

	SettingView* _settingView;
	AppointView *_appointView;

	MailView * _mailView;
	CCMenu * _mailButton;
	CCLabelTTF * _mailText;
	CCSprite * _mailLight;

	CCMenu * _helpButton;
	NewHandHelpView * _helpView;

	DropCheckView* dropCheckView;
	GuildView* guildView;
	GuildPreView* guildPreView;


	WorldBossMainView * _pWBMainView;
	CCLabelTTF * _WorldBossOpenTimeText;
	CCLabelTTF * _SilverMineEnterTimeText;
	CCLabelTTF * _GongEnterTimeText;
	ActView* actView;


	PoolView* poolView;

	IdentifyView * _pIdentifyView;

	ReportView* reportView;

	TaskUIView * _taskUIView;
	VScrollUI * _pVScrollUI;
	TraderView* traderView;

	DailyTaskExView * _pDailyTaskExView;

	OreView* oreView;

	OnlineRewardView * _pOLRewardView;

	TowerView * _pTowerView;

	ShopView * _shopView;
};

#endif
