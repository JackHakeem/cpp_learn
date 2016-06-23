#ifndef _APPFACADE_H_
#define _APPFACADE_H_

#include "mvc/Facade.h"

//Control layer code

enum APPFACADEENUM
{
	/*Packages modified*/
	AppFacade_BAG_PROXY_CHANGE = 0,
	/*Warehouse modify*/
	AppFacade_BANK_PROXY_CHANGE,
	/*Shop modify*/
	AppFacade_SHOP_PROXY_CHANGE,
	/* Fight*/
	AppFacade_FIGHT_PROXY_CHANGE, 

	/*formation*/
	AppFacade_FORMATION_PROXY_CHANGE,

	/*Scene*/
	AppFacade_SCENE_COMMAND,
	AppFacade_SCENEPROXY_COMMAND,
	AppFacade_SCENE_PROXY,
	AppFacade_SCENE_MEDIATOR,
	AppFacade_SCENELISTENER_MEDIATOR,
	AppFacade_SCENEWORLD_MEDIATOR,
	AppFacade_SCENESTORY_PROXY_CHANGE,

	/*Role and mercenaries*/
	AppFacade_FIGURE_COMMAND,
	AppFacade_FIGURE_PROXY,
	AppFacade_FIGURE_MEDIATOR,
	AppFacade_PLAYER_MEDIATOR,

	/*Skill */
	AppFacade_SKILL_COMMAND,
	AppFacade_SKILL_PROXY,
	//AppFacade_SKILL_MEDIATOR,

	/* NPC dialog*/
	AppFacade_NPCDIALOGUE_PROXY_CHANGE, 
	
	/*Task data changes*/
	AppFacade_TASK_COMMAND,
	AppFacade_TASK_PROXY,
	AppFacade_TASK_MEDIATOR,
	AppFacade_TASK_LISTENER_MEDIATOR,

	AppFacade_TASK_FOLLOW_MEDIATOR,

	/*Task data changes */
	AppFacade_GAME_VIEW_MEDIATOR,
	/* landing */
	AppFacade_LOGIN_MEDIATOR,

	/*Training module*/
	AppFacade_TRAIN_PROXY_CHANGE,

	/* Arena */
	AppFacade_ARENA_COMMAND,
	AppFacade_ARENA_PROXY,
	AppFacade_ARENA_MEDIATOR,
	
	/*Chat*/
	AppFacade_CHAT_CHANGE,
	
	/*figure recruit*/
	AppFacade_RECRUIT_PROXY_CHANGE,

	/* Crystal module*/
	AppFacade_CRYSTAL_PROXY_CHANGE,
	AppFacade_MainUIMediator,

	AppFacade_Friend_PROXY_CHANGE,
	AppFacade_OPEN_FRIENDS_COMMAND,
	
	/*初始化公会信息*/
	AppFacade_GUILD_START,
	/*公会交互事件*/
	AppFacade_GUILD_CHANGE,

	/*UPSkill */
	AppFacade_UPSKILL_PROXY_CHANGE,

	/*small map*/
	AppFacade_SmallMapMediator,
	AppFacade_MapMediator,

	/*vip*/
	AppFacade_VIP_COMMAND,
	AppFacade_VIP_PROXY,
	AppFacade_VIP_MEDIATOR,

	/*copy*/
	AppFacade_DungeonEntrysMediator,


	AppFacade_Notice,

	/*Purchase*/
	AppFacade_PURCHASE_MEDIATOR,
	AppFacade_PURCHASE_COMMAND,
	AppFacade_PURCHASE_PROXY,


	/*Newhand*/
	AppFacade_NEWHAND_MEDIATOR,
	AppFacade_NEWHAND_COMMAND,
	AppFacade_NEWHAND_PROXY,

	// item update
	AppFacade_COM_PROXY_CHANGE,

	/*Mail*/
	AppFacade_Mail_Mediator,
	AppFacade_Mail_Command,
	AppFacade_Mail_Proxy,

	//appoint
	AppFacade_APPOINT_MEDIATOR,
	AppFacade_APPOINT_COMMAND,
	AppFacade_APPOINT_PROXY,

	// BroadCast
	AppFacade_BroadCast_Mediator,

	//equipmentDrop
	AppFacade_EQ_Mediator,



	//tower
	AppFacade_TOWER_PROXY_CHANGE,


	//trader
	AppFacade_CITY_TRADER_CHANGE,
	
	// wordboss
	AppFacade_WorldBoss_Command,
	AppFacade_WorldBoss_Proxy,
	AppFacade_WorldBoss_Mediator,


	AppFacade_SilverMine_PROXY_CHANGE,


	AppFacade_Act_CHANGE,

	AppFacade_HONOR_PROXY_CHANGE,

	AppFacade_EGG_CHANGE,


	/*DailyTaskEx*/
	AppFacade_DAILY_TASK_EX_MEDIATOR,
	AppFacade_DAILY_TASK_EX_COMMAND,
	AppFacade_DAILY_TASK_EX_PROXY,

	/* online reward */
	AppFacade_OnlineReward_Command,
	AppFacade_OnlineReward_Proxy,
	AppFacade_OnlineReward_Mediator,

	AppFacade_ORE,


	AppFacade_GONG,


	/* ranking */
	AppFacade_Ranking_Mediator,
	AppFacade_Ranking_Proxy,
	AppFacade_Ranking_Proxy_Change,
	
	/* camp fight */
	AppFacade_CampFight_Mediator,
	AppFacade_CampFight_Command,
	AppFacade_CampFight_Proxy,
	AppFacade_CampFight_Proxy_Change,

<<<<<<< .mine
=======
	AppFacade_ZX,

>>>>>>> .r5911
	/*maximum*/
	AppFacade_APPFACADEENUM_MAX,

};

#endif 