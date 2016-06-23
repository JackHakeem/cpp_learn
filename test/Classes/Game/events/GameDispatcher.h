#ifndef _GAMEDISPATCHER_H_
#define _GAMEDISPATCHER_H_

#include "utils/flash/CCIEventDispatcher.h"

class GameDispatcher
{
public:
	enum
	{
		// Add by Doyang.
		// For avoidance of repetition.
		// TaskEvent's flag from 500~510
		DEFAULT_FLAG_TASK_EVENT = 500,
		// TaskFollowView's flag from 510~520
		DEFAULT_FLAG_TASK_FOLLOW = 511,
		// Appoint bless exchange
		BLESS_EXCHANGE = 521,
		APPOINT_BLESS_EXCHANGE = 522,

		GET_USER_INFO = 1000,
		/*  background map is loaded*/
		MAP_BG_COMPLETE,
		/* into the game interface */
		BEGIN_GAME_COMPLETE,
		/* * big  switch scene*/
		SCENE_CHANGE,
		/* * the switch scene*/ 
		TRIGGER_EXIT,
		/* * received new email */
		RECEIVE_NEW_MAIL,
		/* create the player character */
		CREATE_PALYER_FINISH,
		CREATE_TRADEPALYER_FINISH,
		ROLE_MOVE,
		WALK_COMPLETE,
		WALK_PATH_CHANGE,
		WALK_START,
		CHANGE_POSITION,
		DEAD_EVENT,
		WALK_START_NODE,
		/* * * * * * * * mobilerole */
		ROLE_MOVIE,
		/*  coordinate change roles*/
		ROLE_POS_CHANGED,
		/* NPC removed a corpse */
		NPC_REMOVEDEADBODY,
		/* * display battle report */
		SHOW_UI_REPORT,
		MERCENARY_SKILL_ENABLED,
		/* *  sending chat messages*/
		SEND_CHAT_MESSAGE,
		/* display panel  skills*/
		SHOW_SKILL_PANEL,
		/* store for a click change */
		SHOP_VIEW_CLICK,
		/* show strengthening window */
		SHOW_UI_STRENG,
		/* click on strengthening panel items such as update  events*/
		SHOW_STRENG_CLICK,
		/* click enchantment panel items such as update events*/ 
		SHOW_MAGIC_CLICK,
		/* window click events achievements*/ 
		HONOR_CHANGR,
		/*  show buy energy */
		ALERT_UI_ENERGY,
		/*  send items*/
		SEND_GOOD,
		/* * send battle report */
		SEND_REPORT,
		/* private chat */
		PRIVATE_CHAT,
		/* backpack items change */
		PACK_CHANGE,
		/* bank items change */
		BANK_CHANGE,
		/* character panel */
		FIGURE_CHANGE,
		OTHER_FIGURE_CHANGE,
		/* a map of the world*/ 
		SHOW_UI_MAP,
		/*  arena*/
		SHOW_UI_ARENA,
		/* PVP battle report */
		SHOW_UI_PVPREPORT,
		/*  warehouse click event*/
		BANK_VIEW_CLICK,
		/* can  quests*/
		CAN_TASK_DATA_CHANGE,
		/* have  quests*/
		REC_TASK_DATA_CHANGE,
		ENTRUST_TASK_DATA_CHANGE,
		/* automatically accept or submit task */
		TASK_AUTO_REC_OR_SMT,
		/* combat exit event*/ 
		FIGHT_OUT_EVENT,
		PUT_ON_SKILL,
		PUT_ON_OFFENSIVE,
		AUTO_PUT_ON_EQUIP,
		FIND_ELEMENT,
		/* crystal level update */
		CRYSTAL_LEVEL_CHANGE,
		/* show VIP interface */
		SHOW_UI_VIP,
		/* show task with interface */
		SHOW_TASK_FOLLOW,
		/* task follow interface state */
		TASK_FOLLOW_VISIBLE,
		/* open resources tian interface */
		OPEN_RESOURCE_FIELD,
		SHOW_RESOURCE_FIELD,
		LEVY_TYPE,
		VIEW_GOOD,
		SHOW_SURPRISE_VIEW,
		SHOW_FESTIVAL_VIEW,
		SHOW_ACTIVITY_VIEW,
		NO_LEVY_LEFT,
		SHOW_UI_ACTIVITY,
		SHOW_MAIN_ACTIVITY,
		UP_VIP_LEV,
		TEST_NEW_HAND,
		/* *request to buy energy */ 
		REQ_ENERGY,
		/* *  request clear combat CD*/
		CLEAR_FIGHT_CD,
		/* *  back to town*/
		BACK_TOWN,
		/* * mysterious businessman interface */
		SHOW_MYS_TRADER,
		/* * delete clear guidance arrow free CD */
		DEL_FREECD_ARROW,
		/* * view others information */
		SHOW_OTHER_FIGURE,
		SKILL_DYNAMIC,
		/* *
		* into the scene
		*/
		LOAD_COMPLETE,
		SHOW_WORLD_SCENE,
		MAP_TEST,
		/* enter battle*/ 
		INTO_FIGHT,
		/*  exit battle*/
		OUT_FIGHT,
		/*  to the story*/
		INTO_STORY,
		/* exit the plot*/ 
		OUT_STROY,
		/* story all dialog*/ 
		CONTENT_COMPLETE,
		/*  silver into battle*/
		INTO_SILVERMINE,
		/* open prevent addiction */
		SHOW_FCM,
		CHANGE_NAME, // visitors registration successful change name nickname
		CD_BACK_TOWN,
		/* * opened a map customs clearance award */
		OPEN_MAP_AWARD,
		/* * open perfect customs clearance reward */
		OPEN_PERFECT_AWARD,
		SHOW_ROB_INFO,
		/* arena > reputation rewards */
		SHOW_UI_REPUTATION,
		/* melting request */
		MELTING_REQUEST,
		/*  drag melting items*/
		MELTING_GOODS_CHANGE,
		/* enchantment request */
		MAGIC_REQUEST,
		/* request for inheritance*/ 
		INHERIT_REQUEST,
		GET_REPUTATION_AWARD,
		SHOW_STATS_PANEL,
		SHOW_GOLD_PANEL,
		CAN_MOVE_CHANGE,
		CDCHANGED,
		//world scene
		MAP_BG_INIT,
		CHILD_EXIT_CLICK,
		SHOW_CHILD_SCENE,

		NEW_ALERT_CLOSE,
		TASK_AUTO_FIND_NPC,

		GATE_SERVER_CONNECT_SUCCESS,
		GATE_SERVER_CONNECT_FAILED,
		GAME_SERVER_CONNECT_SUCCESS,
		GAME_SERVER_CONNECT_FAILED,
		LOGIN_SUCCESS,
		LOGIN_FAILED,

		LOGIN_UNREGISTER,
		LOGIN_VERSIONERR,
		LOGIN_FORBBIDEN,
		LOGIN_CREATEROLE,
		LOGIN_RESETSERVLIST,


		SHOW_HERO_RANK,

		STORY_CALLBACK,

		SHOW_EQUIP_TIP,

		SHOW_SKILL_HIGHLIGHT,

		RESET_NEWHELP_VIEW,
		NEWHAND_TIPS_LEVEL, // open tips by level

		/*战斗callback事件*/
		BATTLE_CALLBACK,

		//Begin chenjian 20121015
		SELECT_REPORT,
		APPLY_REPORT_LIST,
		//End chenij

		STORY_FOLLOW_CALLBACK,

		//
		RESET_AREA_TEXT,

		DEFAULT_BASE = 10000,
		ENTER_BACKGROUND,
		ENTER_FOREGROUND,

		BEGIN = 100000,

		MSG_UPDATE_CHALLENGE_TIME            = BEGIN + 1 ,
		/*阵营战使用的消息ID*/
		MSG_OPEN_CAMPFIGHT_VIEW                = BEGIN + 2,
		MSG_SELECT_CAMPFIGHT_ICEPLAYER_ITEM    = BEGIN + 3,
		MSG_SELECT_CAMPFIGHT_FIREPLAYER_ITEM   = BEGIN + 4,


	};

public:
	GameDispatcher()
	{
	}

    /**
    * Protected reliably against detective with
    */
	void addEventListener(int flag, CCNode* tar, SEL_CallFuncND selector)
	{
		eventDispatcher.addEventListener(flag, tar, selector);
	}

    /**
    * Protected reliably against detective removed
    */
	void removeEventListener(int flag)
	{
		eventDispatcher.removeEventListener(flag);
	}

    /**
    * Distributed events
    */
	void dispatchEvent(int flag, void* data)
	{
		eventDispatcher.dispatchEvent(flag, data);
	}

	/**
    * Return whether have the protected reliably against detective
    */
	bool hasEventListener(int flag)
	{
		return eventDispatcher.hasEventListener(flag);
	}

	/**
    * This don't know why use
	public function willTrigger(type) : Boolean 
    {
        return eventDispatcher.willTrigger( type ),
    }
    */
      	

public:


	CCIEventDispatcher eventDispatcher;

public:
	//singleton part
  	/**
   	* Return examples
   	*/ 
	static GameDispatcher * getInstance()
	{
		if (0 == instance)
		{
			instance = new GameDispatcher();
			static CGarbo Garbo;
		}

		return instance;
	}

	static void DestroyInstance()
	{
		if (instance) {		
			delete instance;

			instance = 0;
		}
	}

	static GameDispatcher *		instance;

private:
	class CGarbo // jae for aoto release
	{  
	public:  
		~CGarbo()  
		{  
			GameDispatcher::DestroyInstance();
		}
	};
};

#endif