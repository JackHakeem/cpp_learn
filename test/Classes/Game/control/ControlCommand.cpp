#include "ControlCommand.h"
#include "mvc/Facade.h"
#include "AppFacade.h"

#include "control/backpack/BagProxyCommand.h"
#include "control/battle/SceneFightProxyCommand.h"
#include "control/scene/SceneCommand.h"
#include "control/task/TaskProxyCommand.h"
#include "control/formation/FormationCommand.h"
#include "figure/FigureCommand.h"
#include "train/TrainCommand.h"
#include "scene/SceneProxyCommand.h"
#include "control/bank/BankProxyCommand.h"
#include "crystal/CrystalCommand.h"
#include "skill/SkillCommand.h"
#include "arena/ArenaProxyCommand.h"
#include "recruit/RecruitCommand.h"
#include "vip/VipCommand.h"
#include "friend/FriendProxyCommand.h"
#include "scene/SceneStoryProxyCommand.h"
#include "com/ComProxyCommand.h"
#include "appoint/AppointCommand.h"
#include "mail/MailProxyCommand.h"
#include "guild/GuildChangeCommand.h"
#include "tower/TowerCommand.h"
#include "wordBoss/WorldBossCmd.h"
#include "egg/EggCommand.h"
#include "trader/TraderProxyCommand.h"
#include "onlineReward/OnlineRewardCommand.h"
#include "control/ranking/RankingCommand.h"
<<<<<<< .mine
#include "control/campFight/campFightCommand.h"
=======
#include "control/campFight/CampFightCommand.h"
>>>>>>> .r5911

void ControlCommand::execute(int32 command, char* data)
{
	g_pFacade->registerCommand(AppFacade_BAG_PROXY_CHANGE, new BagProxyCommand());
	g_pFacade->registerCommand(AppFacade_FIGHT_PROXY_CHANGE, new SceneFightProxyCommand());
	g_pFacade->registerCommand(AppFacade_FORMATION_PROXY_CHANGE,new FormationCommand());
	g_pFacade->registerCommand(AppFacade_SCENE_COMMAND, new SceneCommand());
	g_pFacade->registerCommand(AppFacade_TASK_COMMAND, new TaskProxyCommand());
	//g_pFacade->registerCommand(AppFacade_FIGURE_COMMAND, new FigureCommand());
	g_pFacade->registerCommand(AppFacade_FIGURE_COMMAND, new FigureCommand());
	g_pFacade->registerCommand(AppFacade_SCENEPROXY_COMMAND, new SceneProxyCommand());
	g_pFacade->registerCommand(AppFacade_TRAIN_PROXY_CHANGE, new TrainCommand());
	g_pFacade->registerCommand(AppFacade_BANK_PROXY_CHANGE, new BankProxyCommand());
	g_pFacade->registerCommand(AppFacade_CRYSTAL_PROXY_CHANGE, new CrystalCommand());
	g_pFacade->registerCommand(AppFacade_SKILL_COMMAND, new SkillCommand());
	g_pFacade->registerCommand(AppFacade_ARENA_COMMAND, new ArenaProxyCommand());

	g_pFacade->registerCommand(AppFacade_RECRUIT_PROXY_CHANGE, new RecruitCommand());

	g_pFacade->registerCommand(AppFacade_VIP_COMMAND, new VipCommand());
	g_pFacade->registerCommand(AppFacade_Friend_PROXY_CHANGE, new FriendProxyCommand());
	g_pFacade->registerCommand(AppFacade_SCENESTORY_PROXY_CHANGE, new SceneStoryProxyCommand());

	g_pFacade->registerCommand(AppFacade_COM_PROXY_CHANGE, new ComProxyCommand());
	g_pFacade->registerCommand(AppFacade_APPOINT_COMMAND, new AppointCommand());
	g_pFacade->registerCommand(AppFacade_Mail_Command, new MailProxyCommand());

	g_pFacade->registerCommand(AppFacade_GUILD_START, new GuildChangeCommand()); 

	g_pFacade->registerCommand(AppFacade_TOWER_PROXY_CHANGE, new TowerCommand());
	g_pFacade->registerCommand(AppFacade_WorldBoss_Command, new WorldBossCmd());

	g_pFacade->registerCommand(AppFacade_EGG_CHANGE, new EggCommand());
	g_pFacade->registerCommand(AppFacade_CITY_TRADER_CHANGE, new TraderProxyCommand());

	g_pFacade->registerCommand(AppFacade_OnlineReward_Command, new OnlineRewardCommand());
	
	g_pFacade->registerCommand(AppFacade_Ranking_Proxy_Change, new RankingCommand());
	g_pFacade->registerCommand(AppFacade_CampFight_Proxy_Change, new CampFightCommand());
}


