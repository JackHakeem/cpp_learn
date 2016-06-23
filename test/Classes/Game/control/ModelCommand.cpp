#include "ModelCommand.h"
#include "mvc/Facade.h"
#include "AppFacade.h"

#include "model/backpack/BagProxy.h"
#include "model/battle/FightProxy.h"
 
#include "model/formation/FormationProxy.h"
 
#include "model/scene/SceneProxy.h"
#include "model/task/TaskProxy.h"
#include "model/skill/SkillProxy.h"
#include "model/figure/FigureProxy.h"
#include "model/train/TrainProxy.h"
#include "model/bank/BankProxy.h"
#include "model/crystal/CrystalProxy.h" 
#include "model/arena/ArenaProxy.h"
#include "model/recruit/RecruitProxy.h"
#include "model/vip/VipProxy.h"
#include "model/friend/FriendProxy.h"
#include "model/scene/StoryProxy.h"
#include "model/notice/NoticeProxy.h"
#include "model/mail/MailProxy.h"
#include "model/tower/TowerProxy.h"
#include "model/worldBoss/WorldBossProxy.h"
#include "model/silverMine/SilverMineProxy.h"
#include "model/honor/HonorProxy.h"
#include "model/egg/EggProxy.h"
#include "model/trader/TraderProxy.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "model/onlineReward/OnlineRewardProxy.h"
#include "model/ranking/RankingProxy.h"
#include "model/campFight/CampFightProxy.h"

void ModelCommand::execute(int32 command, char* data)
{
	g_pFacade->registerProxy(AppFacade_BAG_PROXY_CHANGE, new BagProxy());

	g_pFacade->registerProxy(AppFacade_FIGHT_PROXY_CHANGE, new FightProxy());
 
	g_pFacade->registerProxy(AppFacade_FORMATION_PROXY_CHANGE, new FormationProxy());

	g_pFacade->registerProxy(AppFacade_TASK_PROXY, new TaskProxy());

	g_pFacade->registerProxy(AppFacade_SCENE_PROXY, new SceneProxy());
 
	g_pFacade->registerProxy(AppFacade_SKILL_PROXY, new SkillProxy());

	g_pFacade->registerProxy(AppFacade_TRAIN_PROXY_CHANGE, new TrainProxy());
	g_pFacade->registerProxy(AppFacade_BANK_PROXY_CHANGE, new BankProxy());
 
	//g_pFacade->registerProxy(AppFacade_FIGURE_PROXY, new FigureProxy());
	g_pFacade->registerProxy(AppFacade_FIGURE_PROXY, new FigureProxy());

	g_pFacade->registerProxy(AppFacade_CRYSTAL_PROXY_CHANGE, new CrystalProxy());

	g_pFacade->registerProxy(AppFacade_ARENA_PROXY, new ArenaProxy());
	g_pFacade->registerProxy(AppFacade_SKILL_COMMAND, new SkillProxy());


	g_pFacade->registerProxy(AppFacade_RECRUIT_PROXY_CHANGE, new RecruitProxy());

	g_pFacade->registerProxy(AppFacade_VIP_PROXY, new VipProxy());
	g_pFacade->registerProxy(AppFacade_Friend_PROXY_CHANGE, new FriendProxy());
	g_pFacade->registerProxy(AppFacade_SCENESTORY_PROXY_CHANGE, new StoryProxy());
	//g_pFacade->registerProxy(AppFacade_Notice, new FriendProxy());
	g_pFacade->registerProxy(AppFacade_Mail_Proxy, new MailProxy());
	g_pFacade->registerProxy(AppFacade_TOWER_PROXY_CHANGE, new TowerProxy());
	g_pFacade->registerProxy(AppFacade_WorldBoss_Proxy, new WorldBossProxy());

	g_pFacade->registerProxy(AppFacade_SilverMine_PROXY_CHANGE, new SilverMineProxy());
	g_pFacade->registerProxy( AppFacade_HONOR_PROXY_CHANGE, new HonorProxy() );
	g_pFacade->registerProxy( AppFacade_EGG_CHANGE, new EggProxy() );
	g_pFacade->registerProxy(AppFacade_CITY_TRADER_CHANGE, new TraderProxy());

	g_pFacade->registerProxy(AppFacade_DAILY_TASK_EX_PROXY, new DailyTaskExProxy());

	g_pFacade->registerProxy(AppFacade_OnlineReward_Proxy, new OnlineRewardProxy());
	
	g_pFacade->registerProxy(AppFacade_Ranking_Proxy, new RankingProxy());
	g_pFacade->registerProxy(AppFacade_CampFight_Proxy, new CampFightProxy());
}