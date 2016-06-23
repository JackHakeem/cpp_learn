#ifndef _POPEVENTNAME_H_
#define _POPEVENTNAME_H_

namespace PopEventName
{
	enum
	{
		FIGURE = 1, // backpack
		BANK = 2, // warehouse
		UPSKILL = 3, // skills, formation to upgrade
		RECRUIT = 4, // recruitment
		TRAIN = 5, // training
		SHOP = 6, // character
		FORMATION = 7, // formations
		BAG = 8, // SHOP
		EMAIL = 9, // mail
		CRYSTAL = 10, // CRYSTAL
		STRENG = 11, // strengthening
		HONOR = 12, // achievement rankings
		GUILD = 13, // GUILD
		PRE_GUILD = 14, // guild rank
		TASK = 15, // TASK
		FRIEND = 16, // good friends
		DIALOGUE = 17, // NPC dialog box
		WASH = 18, // WASH attributes
		LEVY = 19, // collection
		GOLD_LEVY = 20, // lucky charm
		// BLOOD_SUPPLY = 20, // buy blood
		MISSION = 21, // MISSION
		TRADER = 22,
		ACTIVITY = 23, // ACTIVITY
		GIFTCARD = 24, // gift card and novice card, property card
		HELP = 25, // HELP
		OTHER_FIGURE = 26, // the other characters
		APPOINT = 27, // assigned
		SYSTEMTIP = 28, // open system
		DAILY = 29, // DAILY goals
		REPORT = 30, // strategy
		REPORT_LIST = 31, // strategy list
		MAP = 32,
		GM = 33, // GM panel
		PM = 34, // private chat panel
		RANKING = 35, // rankings
		CITY_TRADER = 36, // run business panel
		ARMY = 37, // legion war
		REPUTATION = 38, // arena > REPUTATION rewards
		REWARD = 39, // online award
		TEMA_ROOM = 40, // copy team room
		EQUIPMENT_DROP = 41, // equipment has fallen off
		RANDGIFT = 42, // random gift bag
		VIP = 43, // VIP window
		MEDITATION = 44, // MEDITATION window
		FESTIVAL = 45, // FESTIVAL activities
		// INHERIT = 46 // inheritance window
		TOWER = 47, // HuanLong TOWER
		SECRETARY = 49, // small SECRETARY
		SEC_TASK = 50, // small secretary choice
		SEC_TYPE = 51, // small secretary new task
		DAILY_TASK = 52, // daily activities
		SKILL	= 53,
		PEIYANG = 54,

		ARENA = 55, //Add arena view id, does not exist in flash either.	
		PURCHASE = 56, // Add a purchase view id, it isn't exist in flash.
		JUMP_COPYS = 57,
		STORYMAP_COPYS = 58,
		CHALLENGEMAP_COPYS = 59,
		SETTING = 60,
		APPOINT_BLESS = 61,
		MAIL = 62,
		FIRST_PURCHASE = 63,
		MAP_AWARD = 64,

		EGG_POOL = 65,
		EGG_DEPOT = 66,	
		EGG_WASH = 67,	
		EGG_NUMBOX = 68,

		IDENTIFY = 69,

		DAILY_TASK_EX = 70,
		CAMPFIGHT     = 71,
		MAX_COUNT,


		EventName = MAX_COUNT + 1,
		SHOW_UI_BAG = EventName + BAG, // backpack
		SHOW_UI_BANK = EventName + BANK, // warehouse
		SHOW_UI_UPSKILL = EventName + UPSKILL, // skills, formation to upgrade
		SHOW_UI_RECRUIT = EventName + RECRUIT, // recruitment
		SHOW_UI_TRAIN = EventName + TRAIN, // training
		SHOW_UI_FIGURE = EventName + FIGURE, // character
		SHOW_UI_FORMATION = EventName + FORMATION, // formations
		SHOW_UI_SHOP = EventName + SHOP, // SHOP
		SHOW_UI_EMAIL = EventName + EMAIL, // mail
		SHOW_UI_CRYSTAL = EventName + CRYSTAL, // CRYSTAL
		SHOW_UI_STRENG = EventName + STRENG, // strengthening
		SHOW_UI_HONOR = EventName + HONOR, // achievement rankings
		SHOW_UI_GUILD = EventName + GUILD, // GUILD
		SHOW_UI_TASK = EventName + TASK, // TASK
		SHOW_UI_FRIEND = EventName + FRIEND, // good friends
		SHOW_UI_DIALOGUE = EventName + DIALOGUE, // NPC dialog box
		SHOW_UI_LEVY = EventName + LEVY, // collection
		// SHOW_UI_BLOOD_SUPPLY = EventName + BLOOD_SUPPLY, // buy blood
		SHOW_UI_MISSION = EventName + MISSION, // MISSION
		SHOW_UI_TRADER = EventName + TRADER,
		SHOW_UI_GIFTCARD = EventName + GIFTCARD, // gift card and novice card, property card
		SHOW_UI_HELP = EventName + HELP, // HELP
		SHOW_UI_APPOINT = EventName + APPOINT, // assigned
		SHOW_UI_DAILY = EventName + DAILY,
		SHOW_UI_MAP = EventName + MAP,
		SHOW_UI_GM = EventName + GM, // GM panel
		SHOW_UI_PM = EventName + PM, // private chat panel
		SHOW_UI_RANKING = EventName + RANKING, // private chat panel
		SHOW_UI_CITY_TRADER = EventName + CITY_TRADER,
		SHOW_UI_ARMY = EventName + ARMY, // legion war
		SHOW_UI_REWARD = EventName + REWARD, // online award
		SHOW_UI_TEAM_ROOM = EventName + TEMA_ROOM, // copy room
		SHOW_UI_EQUIPMENT_DROP = EventName + EQUIPMENT_DROP, // equipment has fallen off
		SHOW_UI_VIP = EventName + VIP, // VIP window
		SHOW_UI_SEC = EventName + SECRETARY,
		SHOW_UI_MEDITATION = EventName + MEDITATION, // MEDITATION window
		SHOW_UI_FESTIVAL = EventName + FESTIVAL, // holiday window
		// SHOW_UI_INHERIT = EventName + INHERIT, // inheritance window
		SHOW_UI_SECTASK = EventName + SEC_TASK,
		SHOW_UI_SECTYPE = EventName + SEC_TYPE,
		SHOW_UI_DAILY_TASK = EventName + DAILY_TASK, // daily activities
		SHOW_UI_TOWER = EventName + TOWER, // climb TOWER system

		//Doyang 20120723
		SHOW_UI_ARENA = EventName + ARENA,
		//jump copys
		SHOW_UI_JUMP_COPYS= EventName + JUMP_COPYS,
		SHOW_UI_STORYMAP_COPYS = EventName + STORYMAP_COPYS,
		SHOW_UI_CHALLENGEMAP_COPYS = EventName + CHALLENGEMAP_COPYS,

		SHOW_UI_APPOINT_BLESS = EventName + APPOINT_BLESS,
		SHOW_UI_FIRST_PURCHASE = EventName + FIRST_PURCHASE,
		SHOW_UI_PURCHASE = EventName + PURCHASE,

		SHOW_UI_EGG_POOL =  EventName + EGG_POOL, //幸运池/彩蛋
		SHOW_UI_EGG_DEPOT =  EventName + EGG_DEPOT, //心愿宝箱（许愿池里的蛋蛋仓库）
		SHOW_UI_EGG_WASH =  EventName + EGG_WASH, //洗礼面板（蛋蛋打开后的洗礼面板）
		SHOW_UI_EGG_NUMBOX = EventName + EGG_NUMBOX,//数量选择框（蛋蛋拾取时候的数量选择框）
		
		//added by chenjian Begin
		SHOW_UI_REPORT = EventName + REPORT,
		//added by chenjian End

		SHOW_UI_DAILY_TASK_EX = EventName + DAILY_TASK_EX,
		SHOW_UI_CAMPFIGHT = EventName + CAMPFIGHT,
	};
};

#endif