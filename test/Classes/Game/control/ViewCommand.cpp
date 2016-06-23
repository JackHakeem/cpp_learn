#include "ViewCommand.h"
#include "mvc/Facade.h"
#include "AppFacade.h"

#include "view/backpack/BagMediator.h"
#include "view/battle/SceneFightMediator.h"
#include "view/dialog/DialogMediator.h"
#include "view/scene/SceneMediator.h"
#include "view/formation/FormationMediator.h"
#include "view/task/TaskListenerMediator.h"
#include "view/figure/FigureMediator.h"
#include "view/train/TrainViewMediator.h"
#include "view/task/TaskFollowMediator.h"
#include "view/GameViewMediator.h"
#include "view/scene/SceneListenerMediator.h"
#include "view/task/TaskMediator.h"
#include "view/backpack/BagMediator.h"
#include "view/bank/BankMediator.h"
#include "view/crystal/CrystalMediator.h"

#include "view/shop/ShopMediator.h"
#include "view/mainUI/MainUIMediator.h"
#include "view/arena/ArenaMediator.h"
#include "view/scene/SceneWorldMediator.h"
#include "view/skill/UpSkillMediator.h"

#include "view/smallMap/SmallMapMediator.h"
#include "view/map/MapMediator.h"
#include "view/recruit/RecruitMediator.h"
#include "view/login/LoginMediator.h"
#include "view/vip/VipMediator.h"

#include "view/friend/FriendMediator.h"
#include "view/friend/FriendListenerMediator.h"

#include "view/dungeonEntrys/DungeonEntrysMediator.h"

#include "view/noticeCenter/MsgMediator.h"

#include "view/purchase/PurchaseMediator.h"
#include "view/newhand/NewhandMediator.h"
#include "view/scene/SceneStoryMediator.h"
#include "view/mainUI/PlayerMediator.h"
#include "view/chat/ChatMediator.h"
#include "view/appoint/AppointMediator.h"
#include "view/mail/MailMediator.h"
#include "view/broadcast/BroadcastMediator.h"
#include "view/equipmentDrop/DropMediator.h"
#include "view/guild/GuildMediator.h"
#include "view/guild/GuildListenerMediator.h"
#include "view/tower/TowerMediator.h"
#include "view/worldBoss/WorldBossMediator.h"

#include "view/silverMine/SilverMineMediator.h"
#include "view/act/ActMediator.h"
#include "view/egg/EggMediator.h"
#include "view/trader/CityTraderMediator.h"
#include "view/dailyTaskEx/DailyTaskExMediator.h"

#include "view/ore/OreMediator.h"

#include "view/onlineReward/RewardMediator.h"
#include "view/gong/GongMediator.h"

#include "view/ranking/RankingMediator.h"
#include "view/campFight/CampFightMediator.h"

<<<<<<< .mine
=======
#include "view/zx/ZXMediator.h"

>>>>>>> .r5911
#include "view/campFight/CampFightMediator.h"


void ViewCommand::execute(int32 command, char* data)
{
	g_pFacade->registerMediator(AppFacade_BAG_PROXY_CHANGE, new BagMediator());
	g_pFacade->registerMediator(AppFacade_FIGHT_PROXY_CHANGE, new SceneFightMediator());
	g_pFacade->registerMediator(AppFacade_NPCDIALOGUE_PROXY_CHANGE, new DialogMediator());
	g_pFacade->registerMediator(AppFacade_SCENE_MEDIATOR, new SceneMediator());
	g_pFacade->registerMediator(AppFacade_SCENELISTENER_MEDIATOR, new SceneListenerMediator());
	g_pFacade->registerMediator(AppFacade_SCENEWORLD_MEDIATOR, new SceneWorldMediator());

	g_pFacade->registerMediator(AppFacade_TASK_LISTENER_MEDIATOR, new TaskListenerMediator());
	g_pFacade->registerMediator(AppFacade_LOGIN_MEDIATOR, new LoginMediator());

	g_pFacade->registerMediator(AppFacade_FORMATION_PROXY_CHANGE, new FormationMediator());

	g_pFacade->registerMediator(AppFacade_FIGURE_MEDIATOR, new FigureMediator());

	g_pFacade->registerMediator(AppFacade_GAME_VIEW_MEDIATOR, new GameViewMediator());
	g_pFacade->registerMediator(AppFacade_TASK_FOLLOW_MEDIATOR, new TaskFollowMediator());
	
	g_pFacade->registerMediator(AppFacade_TRAIN_PROXY_CHANGE, new TrainViewMediator());
	g_pFacade->registerMediator(AppFacade_TASK_MEDIATOR, new TaskMediator());
	g_pFacade->registerMediator(AppFacade_BANK_PROXY_CHANGE, new BankMediator());

	g_pFacade->registerMediator(AppFacade_CRYSTAL_PROXY_CHANGE, new CrystalMediator());
	g_pFacade->registerMediator(AppFacade_SHOP_PROXY_CHANGE, new ShopMediator());
	g_pFacade->registerMediator(AppFacade_MainUIMediator, new MainUIMediator());
	g_pFacade->registerMediator(AppFacade_ARENA_MEDIATOR, new ArenaMediator());

	g_pFacade->registerMediator(AppFacade_SKILL_COMMAND, new UpSkillMediator());
	
	g_pFacade->registerMediator(AppFacade_SmallMapMediator, new SmallMapMediator());
	g_pFacade->registerMediator(AppFacade_MapMediator, new MapMediator());

	g_pFacade->registerMediator(AppFacade_RECRUIT_PROXY_CHANGE, new RecruitMediator());

	g_pFacade->registerMediator(AppFacade_VIP_MEDIATOR, new VipMediator());

	g_pFacade->registerMediator(AppFacade_Friend_PROXY_CHANGE, new FriendMediator());
	g_pFacade->registerMediator(AppFacade_OPEN_FRIENDS_COMMAND, new FriendListenerMediator());

	g_pFacade->registerMediator(AppFacade_DungeonEntrysMediator, new DungeonEntrysMediator());

	g_pFacade->registerMediator(AppFacade_Notice, new MsgMediator());

	g_pFacade->registerMediator(AppFacade_PURCHASE_MEDIATOR, new PurchaseMediator());

	g_pFacade->registerMediator(AppFacade_NEWHAND_MEDIATOR, new NewhandMediator());

	g_pFacade->registerMediator(AppFacade_SCENESTORY_PROXY_CHANGE,new SceneStoryMediator());
	g_pFacade->registerMediator(AppFacade_PLAYER_MEDIATOR, new PlayerMediator());
	g_pFacade->registerMediator(AppFacade_CHAT_CHANGE, new ChatMediator());
	g_pFacade->registerMediator(AppFacade_APPOINT_MEDIATOR, new AppointMediator());
	g_pFacade->registerMediator(AppFacade_Mail_Mediator, new MailMediator());
	g_pFacade->registerMediator(AppFacade_BroadCast_Mediator, new BroadcastMediator());
	g_pFacade->registerMediator(AppFacade_EQ_Mediator, new DropMediator());

	g_pFacade->registerMediator(AppFacade_GUILD_START, new GuildListenerMediator());
	g_pFacade->registerMediator(AppFacade_GUILD_CHANGE, new GuildMediator());
	g_pFacade->registerMediator(AppFacade_TOWER_PROXY_CHANGE, new TowerMediator());

	g_pFacade->registerMediator(AppFacade_WorldBoss_Mediator, new WorldBossMediator());


	g_pFacade->registerMediator(AppFacade_SilverMine_PROXY_CHANGE, new SilverMineMediator());

	
	g_pFacade->registerMediator(AppFacade_Act_CHANGE, new ActMediator());

	g_pFacade->registerMediator(AppFacade_EGG_CHANGE, new EggMediator()); 
	g_pFacade->registerMediator(AppFacade_CITY_TRADER_CHANGE, new CityTraderMediator());

	g_pFacade->registerMediator(AppFacade_DAILY_TASK_EX_MEDIATOR, new DailyTaskExMediator());


	g_pFacade->registerMediator(AppFacade_ORE, new OreMediator());
	
	g_pFacade->registerMediator(AppFacade_OnlineReward_Mediator, new RewardMediator());


	g_pFacade->registerMediator(AppFacade_GONG, new GongMediator());
	


	g_pFacade->registerMediator(AppFacade_Ranking_Mediator, new RankingMediator());
	g_pFacade->registerMediator(AppFacade_CampFight_Mediator, new CampFightMediator());
	g_pFacade->registerMediator(AppFacade_ZX, new ZXMediator());

	g_pFacade->registerMediator(AppFacade_CampFight_Mediator, new CampFightMediator());

}
