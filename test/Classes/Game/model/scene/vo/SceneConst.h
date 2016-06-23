#ifndef _SCENECONST_H_
#define _SCENECONST_H_

static const std::string NPC_TYPE				= "npc";
static const std::string MONSTER_TYPE			= "monster";
static const std::string PLAYER_TYPE			= "player";
static const std::string EXIT_TYPE				= "exit";
static const std::string ITEM_TYPE				= "item";
static const std::string TRADEPLAYER_TYPE		= "tradeplayer";

class SceneConst
{
public:

	enum
	{
		WALK_COMPLETE 			        = 0,
		WALK_COMPLETE_NODE,
		WALK_START_NODE,
		WALK_START,
		WALK_START_1,
		ATTACK_COMPLETE,
		WALK_PATH_CHANGE,
		CHANGE_POSITION,
		CHANGE_POSITION_X,
		CHANGE_POSITION_Y,
		DEAD_EVENT,
		RELIVE_EVENT,
		REMOVE_NPC_DEADBODY_EVENT,
		REMOVE_PLAYER_DEADBODY_EVENT,
		STOP_AND_ATTACK_COMPLETE,
		PLAYER_LAYOUT,
		SELECT_PLAYER,
		CANCEL_PLAYER,
		VIRTUAL_WALK_COMPLETE,
		MAP_BG_INIT,
		ROLE_MOVE,
		ROLE_POS_CHANGED,
		NPC_REMOVEDEADBODY,
		TRIGGER_EXIT,
		ATTACKMONSTER,
		DIALOG_NPC,
		ELEMENT_LAYOUT,
		NPC_MOVE,
		BUILD,
		SMLMAP_BG_INIT,
		PLAYER_REMOVEDEADBODY,
		DISPOSE,
		RAISE_CITY_NAME,

		// from world scene
		SHOW_CHILD_SCENE ,
		RETURN_PRE_MAP,
		REQUEST_REMAIN_TIME,
		REQUEST_BUG_TIME,
		BTN_ENTER_CLICK,
		// from child exit
		CHILD_EXIT_CLICK,
		CHANGE,
		CHANGE1,
		CLICK_EXIT_IN_WORLDMAP,


		TRADE_WALK_START_NODE,
	};

	static const int TALK = 0;
	static const int FIGHT = 1;
	static const int WANDER = 2;
	static const int STORY = 3;

	static const int STAND					= 0; //Stand animation
	static const int MOVE					= 1; //Walk animation
	static const int HITED					= 2; //Walking by the animation and animation
	static const int ATTACK					= 3; //Attack animations
	static const int DEAD					= 4; //Death animation

	static const int PVE						= 0;
	static const int PVP						= 1;
	static const int EVP						= 2;
	static const int EVE						= 3;

	static const int ATTACK_SIDE				= 0;//offense
	static const int DEFEND_SIDE				= 1;//The party

};

#endif