#ifndef _SOCKETCMDCONST_H_
#define _SOCKETCMDCONST_H_

const int MESSAGE_MAX = 1500;

enum SocketCMDConst
{
	CMSG_CREATE_ACCOUNT = 0x104, // create role
	GMSG_CREATE_ACCOUNT = 0x105, // create role response
	XMSG_ERROR_RESPONSE	= 0x108,
	CMSG_COMMU_REGISTER_REQUEST = 0x24A, // guest register
	GMSG_COMMU_REGISTER_RESP = 0x24B, // guest register response
	CMSG_COMMU_HARTBEAT = 0x010, //send to gate heartbeat
	CMSG_WORLD_HARTBEAT = 0x011, //send to world heartbeat
	CMSG_LOGIN = 0x101, // Gate user login
	SMSG_LOGIN_RESPONSE = 0x102, // Gate user login reply
	CMSG_WORLD_LOGIN_RESPONSE = 0x106, // line node landed in response
	WMSG_WORLD_LOGIN_RESPONSE = 0x107, // line node landed in response
	WMSG_WORLD_TIME_BROADCAST = 0x109, //(265) server time broadcast
	CMSG_CLIENT_SY_LOGIN = 0x10F,
	CMSG_WORLD_MOVE			  = 0x110, // player move
	WMSG_WORLD_MOVE = 0x111, // player mobile radio (confirmed the player movement commands)
	WMSG_WORLD_PLAYER_VIEW_IN = 0x112, // players come into view
	WMSG_WORLD_PLAYER_VIEW_OUT = 0x113, // player out of view
	CMSG_WORLD_MOVE_STEP	= 0x114,		// move step
	CMSG_WORLD_MOVE_STOP	= 0x115,        // change path 277
	CMSG_WORLD_MAP_ENTER	= 0x116,		//root map jump
	WMSG_WORLD_MAP_SKIP = 0x118, // root/child map jump results
	CMSG_WORLD_PLAYER_VIEW_GET = 0x119, // get the map info
	WMSG_WORLD_PLAYER_VIEW_GET = 0x11A, // get a map in the information
	WMSG_WORLD_MOVE_EVENT = 0x11B, // 283 people to move events
	WMSG_WORLD_RELOCATION = 0x11C, // 284 players relocation
	WMSG_WORLD_MAP_PROCESS = 0x11D, // 285 map already completed progress information
	CMSG_WORLD_REDO_MAP_PROCESS = 0x11E, // 286 against the green monster
	WMSG_WORLD_FOLLOW_PROCESS = 0x11F, // 287 progress after fight
	WMSG_WORLD_COMPLETE_PROCESS = 0x120, // 288 to complete a progress
	CMSG_WORLD_MAP_PROCESS_GET = 0x121,  // 289 get the progress
	CMSG_WORLD_PROCESS = 0x122, // 290 get what map already open, which will open
	WMSG_WORLD_PROCESS = 0x123, // 291 send what map has open, which will open
	WMSG_WORLD_OPEN_NEW_MAP = 0x124, // 292 open new map, which will open
	WMSG_WORLD_BATTLE_PVE_START = 0x131, // 305 pve copy to the battle began SCMD135 special!!!
	WMSG_WORLD_BATTLE_CONTENT = 0x132, // 306 PVE combat content (attack position 1-9, defending position 10 to 18)
	WMSG_WORLD_BATTLE_FINISH = 0x133, // 307 end PVE battle
	CMSG_WORLD_BATTLE_REPORT_REQUEST 		= 0x134,		//(546) �鿴PVE����,int64:ս������ID(������int����)
	WMSG_WORLD_BATTLE_REPORT_START = 0x135, // 309 PVE strategy began to fight
	CMSG_WORLD_BATTLE_EXIT = 0x138,
	WMSG_WORLD_BATTLE_UPDATE_ROLE = 0x139,
	CMSG_WORLD_BATTLE_PK_START = 0x13B,
	WMSG_WORLD_BATTLE_PVP_START = 0x13C, // 316 PVP or PK started fighting

	CMSG_WORLD_TRADER_MOVE_STEP = 0x0F0,	// trader move step
	WMSG_WORLD_TRADE_PLAYER_VIEW_IN = 0x0F1,
	WMSG_WORLD_TRADE_PLAYER_VIEW_OUT = 0x0F2,

	WMSG_WORLD_BATTLE_REWARD = 0x13D, // reward of fight.
	WMSG_REQUEST_BATTLE_REPORT = 0x3B1,	

	WMSG_ACHIVEMENT_REACHED = 0x140,     	//������֪ͨ�ͻ�����Ҵﵽ��һ���ɾ�
	CMSG_GET_ACHIVEMENT_INFO   		  	= 0x141,    	//�ͻ��˻�ȡ��ҳɾ���Ϣ
	WMSG_GET_ACHIVEMENT_LIST_RESP  	  	= 0x142,	   	//��������Ӧ��ҳɾ��б�����
	CMSG_GET_ACHIVEMENT_AWARD = 0x143,     	//client get honor award
	WMSG_GET_ACHIVEMENT_AWARD_REPLY= 0x144, //��ҿͻ�����ȡ�ɾͽ������

	CMSG_WORLD_BAG_ITEM_UPDATE = 0x160, // parcel items position change request
	WMSG_WORLD_BAG_ITEM_UPDATE = 0x161, // parcel items position change notices
	CMSG_WORLD_BAG_INIT = 0x164, // parcel items initialize request
	WMSG_WORLD_BAG_INIT = 0x165, // parcel items initialization notice
	CMSG_WORLD_BAG_ITEM_DELETE = 0x16B, 		//delete item
	CMSG_WORLD_BAG_SORT = 0x168,
	CMSG_WORLD_BANK_SORT = 0x169,
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	/* Task */
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	WMSG_WORLD_TASK_ALL = 0x150, // 336 to the client push players routine tasks to complete
	WMSG_WORLD_TASK_ACCEPT = 0x151, // 337 to the client delivery has connected information task
	WMSG_WORLD_ENTRUST_TASK_VISIBLE = 0x153, // 339 to the client delivery may meet entrust task information
	CMSG_WORLD_ACCEPT_TASK = 0x154, // 340 client submitted to accept task
	WMSG_WORLD_ACCEPT_TASK = 0x155, // 341 accept task to return to pack
	CMSG_WORLD_COMPLETE_TASK = 0x156, // 342 clients directly submit completed the task
	WMSG_WORLD_COMPLETE_TASK = 0x157, // 343 to complete the task directly to return to pack
	WMSG_WORLD_TASK_UPDATE = 0x158, // 344 update task progress
	CMSG_WORLD_SUBMIT_TASK = 0x159, // 345 client submit task
	WMSG_WORLD_SUBMIT_TASK = 0x15A, // 346 submit task to return to pack
	CMSG_WORLD_GIVE_UP_TASK = 0x15B, // 347 client submitted to give up the task
	WMSG_WORLD_GIVE_UP_TASK = 0x15C, // 348 to give up the task to return to pack
	CMSG_WORLD_REFRESH_TASK = 0x15D, // 349 client submitted to refresh task
	WMSG_WORLD_REFRESH_TASK = 0x15E, // 350 refresh task to return to pack
	CMSG_WORLD_ALL_TASK_REQUEST = 0x15F, // (351) the client requests for information of all tasks
	CMSG_WORLD_BANK_INIT = 0x166, // bank items initialize request
	WMSG_WORLD_BANK_INIT = 0x167, // bank items initialization notice
	CMSG_WORLD_BANK_ITEM_UPDATE = 0x162, // bank items position change request
	WMSG_WORLD_BANK_ITEM_UPDATE = 0x163, // bank items position change notices
	CMSG_WORLD_BAG_BANK_SWAP = 0x16A, // parcel Banks swap articles

	CMSG_WORLD_ITEM_INFO = 0x16E,		// get item info
	WMSG_WORLD_ITEM_INFO = 0x16F,		// item info

	CMSG_WORLD_EQUIP_UP = 0x170,
	CMSG_WORLD_EQUIP_DOWN = 0x171,
	WMSG_WORLD_EQUIP_ITEM_UPDATE = 0x172,
	CMSG_WORLD_CONTAINER_EXPAND		 		= 0x176,		//��??��?a??�㨹1��/��?DD??����

	CMSG_WORLD_LOGIN_CD					= 0x17E,	// player landing request initialization CD list
	WMSG_WORLD_LOGIN_CD_FEEDBACK		= 0x17F,	// server response initialization CD player on the list 
	CMSG_WORLD_CLEAR_CD					= 0x182,	// player request CD reset 
	WMSG_WORLD_CLEAR_CD_RESULT			= 0x183,	// server response CD reset the results 
	WMSG_WORLD_UPDATE_CD				= 0x187,	// server update CD information 


	CMSG_WORLD_CLEAR_CD_COST			= 0x19E,	// (414) request for CD player cleared gold COINS 
	WMSG_WORLD_CLEAR_CD_COST			= 0x19F,	// (415) server response CD reset for gold 

	CMSG_WORLD_GET_IMPOSE_INFO = 0x322,				// client access information collection 
	WMSG_WORLD_FEEKBACK_IMPOSE_INFO = 0x323,		// server response to obtain information collection 
	CMSG_WORLD_IMPOSE	= 0x320,					// (800) the client collection bags 
	WMSG_WORLD_IMPOSE_RESULT = 0x321,				// (801) server response to the tax package 

	GMSG_COMMU_GUILD_DONATE_BY_IMPOSE = 0x324,		/**zhengshou juntuan juanxian*/


	/************************************************************************/
	/* Team                                                                 */
	/************************************************************************/
	WMSG_WORLD_TEAM_NEW					  = 0x328,
	CMSG_WORLD_TEAM_CAPTAIN_CHANGE		  = 0x32A,
	GMSG_WORLD_TEAM_CAPTAIN_CHANGE		  = 0x32B,
	CMSG_WORLD_TEAM_QUIT                  = 0x32C,
	WMSG_WORLD_TEAM_QUIT                  = 0x32D,

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	/*			Strengthen*/
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	CMSG_WORLD_SYS_EQUIPSTREN_PROB = 0x17C, // player on request of the current server equipment strengthen probability
	WMSG_WORLD_SYS_EQUIPSTREN_PROB = 0x17D, // server response the current equipment strengthen the request of probability
	CMSG_WORLD_ITEM_STRENGTHEN = 0x180, // player request equipment strengthening
	WMSG_WORLD_ITEM_STRENGTHEN_RESULT = 0x181, // server response equipment improved results

	WMSG_WORLD_UPDATE_HP = 0x18B, // HP changed
	WMSG_UPDATE_SILVER= 0x18C,		//396 update silver
	WMSG_UPDATE_GOLD = 0x18D,		//397update gold

	CMSG_WORLD_UPGRADE_CRYSTAL = 0x184, // (388) players request upgrade crystal
	WMSG_WORLD_UPGRADE_CRYSTAL_RESULT = 0x185, // (389) server response crystal upgrade the results
	WMSG_WORLD_ACTIVATE_CRYSTAL = 0x186, // (390) server activate the crystal
	WMSG_UPDATE_VIGOUR			= 0x188,
	CMSG_WORLD_LOGIN_CRYSLTAL = 0x189, // (393) players request all crystal information
	WMSG_WORLD_LOGIN_CRYSTAL_FEEDBACK = 0x18A, // (394) server return all crystal information
//	WMSG_UPDATE_SILVER				= 0x18C, // update sliver
//	WMSG_UPDATE_GOLD				= 0x18D, // Update gold
	WMSG_UPDATE_PRACTICE			= 0x18E, 		//398 update practice
	WMSG_UPDATE_POPULARITY			= 0x18F,		//399 update popularity

	CMSG_WORLD_REQ_UPGRADE_TIME = 0x19C, // (412) players request for crystal upgrade CD time
	WMSG_WORLD_REQ_UPGRADE_TIME = 0x19D, // (413) server response crystal upgrade time needed for CD
	WMSG_WORLD_ITEM_ADD_INFO = 0x16D, // (365) items to get information
	CMSG_WORLD_ITEM_BUY = 0x178, // player to the NPC buy goods
	CMSG_WORLD_ITEM_SELL = 0x17A, // player to the NPC sell items

	CMSG_WORLD_USE_ITEM = 0x1D9,		// 473 use item



	/** �û������½���������*/		
	 CMSG_COMMU_GUILD_NEW        		  = 0x1B0,  
	/**�û�����鿴�����б�����*/		
	 CMSG_COMMU_GUILD_GET_LIST   		  = 0x1B1,     
	/**�û�������ҹ�������*/	
	 CMSG_COMMU_GUILD_FIND        		  = 0x1B3,  
	/**�û�����Ľ�ɢ��������*/	
	 CMSG_COMMU_GUILD_DISSOLVE     	  = 0x1B5, 
	/**�û������ȡ����ɢ��������*/	
	 CMSG_COMMU_GUILD_DISSOLVE_CANCEL    = 0x1B6,
	/**������ʾ��Ϣ*/
	GMSG_COMMU_GUILD_TIP_RESP = 0x1B8,
	/**�û�����������Ա����*/	
	 CMSG_COMMU_GUILD_NOMINATE   		  = 0x1B9,  
	/**�û������������*/	
	 CMSG_COMMU_GUILD_APPLY       		  = 0x1BA,  
	/**�û�����鿴��������б�����*/	
	 CMSG_COMMU_GUILD_APPLY_LIST         = 0x1BB,
	/**�û����������������*/	
	 CMSG_COMMU_GUILD_APPLY_HANDLE   	  = 0x1BD, 
	/**�û�����鿴������Ϣ����*/	
	 CMSG_COMMU_GUILD_INFO   			  = 0x1BE,       
	/**�û�����鿴��Ա�б�����*/	
	 CMSG_COMMU_GUILD_MEMBER_LIST        = 0x1C0,   
	/**�û�����鿴��Ա��Ϣ����*/	
	 CMSG_COMMU_GUILD_MEMBER_INFO        = 0x1C2,  
	/**�û������޸�Ĭ�ϿƼ�����*/	
	 CMSG_COMMU_GUILD_DEFAULT_TECH       = 0x1C4, 
	/**�û�����鿴�Ƽ��б�����*/	
	 CMSG_COMMU_GUILD_TECH_LIST          = 0x1C5,        
	/**�û������߳���Ա����*/	
	 CMSG_COMMU_GUILD_KICK_MEMBER        = 0x1CA,
	/**�û������˳���������*/
	 CMSG_COMMU_GUILD_QUIT               = 0x1CC,
	/**�û������޸Ĺ�����Ϣ����*/	
	 CMSG_COMMU_GUILD_ALTER_INFO         = 0x1CE,
	/**����˷��صĹ����б�*/	
	 GMSG_COMMU_GUILD_GET_LIST       	  = 0x1B2,          
	/**����˷��صĲ��ҹ����*/	
	 GMSG_COMMU_GUILD_FIND        		  = 0x1B4,    
	/**����˷��ص��½������*/	
	 GMSG_COMMU_GUILD_NEW_RESP        	  = 0x1B7, 
	/**����˷��ز鿴��������б�*/	
	 GMSG_COMMU_GUILD_APPLY_LIST         = 0x1BC, 
	/**����˷��ز鿴�鿴������Ϣ*/	
	 GMSG_COMMU_GUILD_INFO        		  = 0x1BF,            
	/**����˷��ز鿴��Ա�б���ҳ)*/	
	 GMSG_COMMU_GUILD_MEMBER_LIST        = 0x1C1,            
	/**����˷��ز鿴��Ա��Ϣ*/	
	 GMSG_COMMU_GUILD_MEMBER_INFO        = 0x1C3,            
	/**����˷��ز鿴�Ƽ��б�*/	
	 GMSG_COMMU_GUILD_TECH_LIST          = 0x1C6,            
	/**����˷��ع��������Ӧ*/	
	 GMSG_COMMU_GUILD_ERR        		  = 0x1C7,
	/**��������������������*/
	 GMSG_COMMU_GUILD_APPLY_HANDLE		  = 0x1CB,
	/**����˷����˳�����Ľ��*/
	 GMSG_COMMU_GUILD_QUIT          	  = 0x1CD,
	/**��������Ŀͻ�������*/
	 CMSG_COMMU_GUILD_FLAG_UPDATE         = 0x1CF,
	/**����򹫻�Ƽ���������*/
	CMSG_COMMU_GUILD_DONATE 			  = 0x1D1,		
	/**�����վ������ޡ��Ѿ����� */
	CMSG_COMMU_GUILD_DONATE_REQ		  = 0x1D5,
	/**���ص��վ������ޡ��Ѿ����� */
	GMSG_COMMU_GUILD_DONATE			  = 0x1D6,


	CMSG_WORLD_GUIDE_CDCONDITION = 0x1DE,	/**���������������CD����*/
	WMSG_WORLD_GUIDE_CDCONDITION = 0x1DF,	/**������������������CD������*/

	CMSG_COMMU_WORLD_CHAT						 = 0x190,		//400�������죬����Ϣ��������㲥
	GMSG_COMMU_WORLD_CHAT     					 = 0x191,		//401�������죬����Ϣ��������㲥
	CMSG_COMMU_GUILD_CHAT						 = 0x192,
	GMSG_COMMU_GUILD_CHAT 						 = 0x193,		//403�������죬����˸��ݷ�����idȷ����
	CMSG_COMMU_PRIVATE_CHAT		 				 = 0x196,		//406˽������
	GMSG_COMMU_PRIVATE_CHAT  				     = 0x197,		//407˽������
	CMSG_COMMU_GM_CHAT 					         = 0x198,		//408��GM������Ϣ���ĵ��ʼ�������ȽϺ�
	GMSG_COMMU_ERR_CHAT  					     = 0x199,		//409������������߷�����Ϣ

	CMSG_COMMU_FRIENDS_LIST                      = 0x200,//friend
	GMSG_COMMU_FRIENDS_LIST                      = 0x201,
	CMSG_COMMU_FRIENDS_SAME_LEVEL                = 0x204,
	GMSG_COMMU_FRIENDS_SAME_LEVEL				 = 0x205,
	CMSG_COMMU_FRIENDS_BLACK_LIST                = 0x206,
	GMSG_COMMU_FRIENDS_BLACK_LIST                = 0x207,
	CMSG_COMMU_FRIENDS_ADD_FRIEND				 = 0x208,
	GMSG_COMMU_FRIENDS_ADD_FRIEND				 = 0x209,
	CMSG_COMMU_FRIENDS_DEL_FRIEND				 = 0x20A,
	GMSG_COMMU_FRIENDS_DEL_FRIEND		         = 0x20B,
	CMSG_COMMU_FRIENDS_BLACK_A_FRIEND		     = 0x20C,
	GMSG_COMMU_FRIENDS_BLACK_A_FRIEND            = 0x20d,
	CMSG_COMMU_FRIENDS_ADD_BLACK                 = 0x20E,
	GMSG_COMMU_FRIENDS_ADD_BLACK				 = 0x20F,
	CMSG_COMMU_FRIENDS_DEL_FROM_LIST             = 0x210,
	GMSG_COMMU_FRIENDS_DEL_FROM_LIST             = 0x211,
	CMSG_COMMU_FRIENDS_VIEW_INFO                 = 0x212,
	GMSG_COMMU_FRIENDS_VIEW_INFO				 = 0x213,
	GMSG_COMMU_FRIENDS_ERR_CODE                  = 0x214,
	CMSG_COMMU_FRIENDS_APPLY_HANDLE				 = 0x217,
	GMSG_COMMU_FRIENDS_HAS_APPLY				 = 0x216,
	GMSG_COMMU_FRIENDS_BLESS					 = 0x219,
	CMSG_COMMU_FRIENDS_APPLY_BAT				 = 0x21C,
	CMSG_WORLD_BUY_VIGOUR						= 0x21D,
	CMSG_WORLD_BUY_VIGOUR_INFO					= 0x21E,
	WMSG_WORLD_BUY_VIGOUR_INFO_RESP				= 0x21F,

	CMSG_WORLD_HERO_REQ = 0x284,	//client requests hero rank info
	WMSG_WORLD_HERO_INFO = 0x285,	//server responses hero rank info
	CMSG_WORLD_HERO_GET_AWARD = 0x286,	//client requests hero award
	WMSG_WORLD_HERO_GET_AWARD = 0x287,	//server responses hero award
	CMSG_WORLD_SMELT = 0x2D2,		//��722��/**melting equiment**/
	WMSG_WORLD_SMELT = 0x2D3,		//��723��	/**response melting result**/


	CMSG_WORLD_INHERITABLE_INFO = 0x2D8, 	//��728��	/**request inherit list**/	
	WMSG_WORLD_INHERITABLE_INFO = 0x2D9, 	//��729��/**response list**/	
	CMSG_WORLD_INHERI = 0x2DA,				//��730��/**rquest to inherit**/	
	WMSG_WORLD_INHERI = 0x2DB, 				//��731��/**response result**/


	CMSG_WORLD_HERITAGE								= 0X2DE,			// �ͻ��˿�ʼװ������ jae
	WMSG_WORLD_HERITAGE								= 0X2DF,			// ����˷���װ�����н�� jae

	CMSG_WORLD_REQ_ENCHANT_INFO = 0x2D4,		//��724��	/**request magic info**/
	WMSG_WORLD_REQ_ENCHANT_INFO = 0x2D5, 	//��725��	/**response magic info**/
	CMSG_WORLD_ENCHANT = 0x2D6,				//��726��	/**magic equip**/
	WMSG_WORLD_ENCHANT = 0x2D7, 				//��727��	/**response magic result**/

	CMSG_REP_CAN_HIRE_MAX_MER_NUM = 0x290,// (656)   check can recruit figure
	WMSG_REP_CAN_HIRE_MAX_MER_NUM = 0x291, //(657)   can recruit figure
	CMSG_WORLD_NOTIFY_REQ = 0x292,
	CMSG_WORLD_BUY_CRYSTAL_CD = 0x2E0, // buy cd list
	WMSG_WORLD_BUY_CRYSTAL_CD = 0x2E1, // buy cd list response

	CMSG_WORLD_INCREASE_PRICE = 0x294, // wash price changed
	WMSG_WORLD_INCREASE_PRICE = 0x295,

	CMSG_WORLD_GET_VIP_AWARD_REQ = 0x29F, // vip reward
	WMSG_WORLD_GET_VIP_AWARD_REQ = 0x29A, // vip reward

	WMSG_WORLD_MERCENARY_RECRUIT_LIST = 0x300, // (768) to the client delivery can recruit mercenaries ID list
	WMSG_WORLD_MERCENARY_RECRUITED = 0x301, // (769) to the client push the firing of the mercenaries list
	CMSG_WORLD_MERCENARY_RECRUIT = 0x302, // (770) recruiting mercenaries
	WMSG_WORLD_MERCENARY_RECRUIT = 0x303, // (771) recruiting mercenaries to return to pack
	CMSG_WORLD_MERCENARY_DISMISS = 0x304, // (772) fired mercenaries
	WMSG_WORLD_MERCENARY_DISMISS = 0x305, // (773) fired mercenaries to return to pack
	CMSG_WORLD_MERCENARY_EMPLOYNPC = 0x306, // (774) the client requests for can recruit mercenaries list
	CMSG_WORLD_MERCENARY_BASE_INFO = 0x307, // (775) the client requests for mercenaries foundation information
	CMSG_WORLD_MERCENARY_EQUIP_INFO = 0x308, // (776) the client requests for mercenaries equipment information, byte = 0
	WMSG_WORLD_MERCENARY_BASE_INFO = 0x309, // (777) to the client push mercenaries foundation information
	WMSG_WORLD_MERCENARY_EQUIP_INFO = 0x30A, // (778) to the client with information push mercenaries
	CMSG_WORLD_MERCENARY_RERSIE = 0x30B, // (779) the client requests for rebirth mercenaries, int = mercenaries only ID
	WMSG_WORLD_MERCENARY_RERSIE = 0x30C, // (780) mercenaries reincarnate back to bag
	CMSG_WORLD_MERCENARY_SKILL_ENABLED = 0x30D, // (781) request mercenaries skills replacement
	WMSG_WORLD_MERCENARY_SKILL_ENABLED = 0x30E, // (782) skills change to return to pack
	WMSG_WORLD_MERCENARY_SKILL_EXCHANGED = 0x2FF, // (767) mercenaries swap skills to return to pack
	CMSG_WORLD_MERCENARY_ALTER_SITE = 0x30F, // the client requests for replacement in a system that the position of the mercenaries
	CMSG_WORLD_FORMATION_ENABLED = 0x311, // the client requests for opening formations
	CMSG_WORLD_FORMATION_UPGRADE = 0x313,// the client requests for upgrade formations
	CMSG_WORLD_PASSIVESKILL_UPGRADE = 0x315, // upgrade passive skill request
	CMSG_WORLD_FORMATION_PASSIVESKILL = 0x317, // client requests have already learn with passive skill formation
	CMSG_WORLD_MERCENARY_FOSTER_SAVE = 0x31C,
	CMSG_WORLD_MERCENARY_FOSTER_REFRESH = 0x31E,
	WMSG_WORLD_MERCENARY_ALTER_SITE = 0x310, // the client requests for replacement in a position in the formation are to return to pack
	WMSG_WORLD_FORMATION_ENABLED = 0x312, // client request to return to enable formation bag
	WMSG_WORLD_FORMATION_INFO = 0x318, // to the client delivery system information list
	WMSG_WORLD_PASSIVESKILL_INFO = 0x319, // to the client push passive skill list
	WMSG_WORLD_PASSIVESKILL_ADD = 0x31A, // to the client push new passive information
	WMSG_WORLD_FORMATION_ADD = 0x31B, // to the client push new formation information
	WMSG_WORLD_MERCENARY_FOSTER_SAVE = 0x31D, // save mercenaries training information to return to pack
	WMSG_WORLD_MERCENARY_FOSTER_REFRESH = 0x31F, // refresh mercenaries training information to return to pack
	WMSG_WORLD_LEVEL_UP = 0x35D, /* * the server radio upgrade */
	WMSG_WORLD_MER_ATTRIBUTE_CHANGE = 0x35F, /* * tip mercenaries attribute information change */
	WMSG_WORLD_OPEN_UPGRADE_BALL_PANEL = 0x349,
	/* * experience value update package */
	WMSG_WORLD_UPDATE_EXP = 0x350,
	/* * request training information  role*/
	CMSG_WORLD_TRAIN_INFO = 0x351,
	/* * character training information to return to pack */
	WMSG_WORLD_TRAIN_INFO_RESP = 0x352,
	/* *  purchase request training position*/
	CMSG_WORLD_TRAIN_BUY_PLACE = 0x353,
	/* * buy to return to training position bag */
	WMSG_WORLD_TRAIN_BUY_PLACE_RESP = 0x354,
	/* *  training mode request a change*/
	CMSG_WORLD_TRAIN_CHANGE_MODEL = 0x355,
	/* * change training mode to return to pack */
	WMSG_WORLD_TRAIN_CHANGE_MODEL_RESP = 0x356,
	/* *  end request training*/
	CMSG_WORLD_TRAIN_END = 0x357,
	/* * end to return to training package */
	WMSG_WORLD_TRAIN_END_RESP = 0x358,
	/* * training request role */
	CMSG_WORLD_TRAIN_REQUEST = 0x359,
	/* * request to return to training package  role*/
	WMSG_WORLD_TRAIN_RESP = 0x35A,
	/* * request by leaps and bounds*/ 
	CMSG_WORLD_TRAIN_SPEED_UP_REQUEST = 0x35B,
	/* * advance by leaps and bounds to return to pack */
	WMSG_WORLD_TRAIN_SPEED_UP_RESP = 0x35C,
	/* *  change combat effectiveness*/
	WMSG_WORLD_BS_CHANGE = 0x35E,

	/**pass gift*/
	WMSG_WORLD_DUNGEON_AWARD = 0x376,
	
	WMSG_WORLD_DUNGEON_RESP_ROOM_LIST = 0x37c,
	//arena
	CMSG_WORLD_QUALIFYING_ENTER = 0x360,	//client requests winning streak info
	WMSG_WORLD_QUALIFYING_INFO = 0x361, //server responses battle info 
	CMSG_WORLD_QUALIFYING_CHALLENGE  = 0x362,          //(866)��ҷ�����ս
	WMSG_WORLD_QUALIFYING_CHALLENGE_RES  = 0x363,          //(867)��ҷ�����ս�ظ�
	CMSG_WORLD_QUALIFYING_AWARD    = 0x364,          //(868)��ҷ�ȡ5����ս����
	WMSG_WORLD_PVP_CHALLENGE_RETURN = 0x366,
	CMSG_WORLD_AREANA_WORSHIPINFO_REQ	 = 0x36C,		// �����̨Ĥ����Ϣ����
	WMSG_WORLD_QUALIFYING_AWARD_RES = 0x36E,			// ���ƽ������
	CMSG_WORLD_QUALIFYING_BUY	 = 0x36F,			// ��ҹ��򾺼�����ս����
	WMSG_WORLD_QUALIFYING_BUY_RES = 0x38C,			// ���򾺼�����ս�������
	CMSG_WORLD_QUALIFYING_OPP_RESET_REQ  = 0x38D,	// ˢ�¾�������ս��������  hwj
	//WMSG_WORLD_QUALIFYING_OPP_RESET_RESP = 0x38E,	// ����ˢ�¾�����������Ϣ  hwj
	CMSG_WORLD_ACTIVITY_INFO_REQ    = 0x38E,			// ǰ�˻�ȡ��˻��Ϣ   
	WMSG_WORLD_ACTIVITY_INFO_RES	= 0x38F,			// ��˷���ǰ�˻��Ϣ

	CMSG_WORLD_PVP_QUALIFYING_REQUEST = 0x398, //client requests available PVP list
	WMSG_WORLD_PVP_QUALIFYING_REQUEST = 0x39A, //server responses available PVP list
	WMSG_WORLD_PVP_ARENACONTEST_REQUEST = 0x39B, //server responses requested contest pack
	WMSG_WORLD_PVP_ARENACONTEST_LIST = 0x39C,	//server responses all contest pack
	WMSG_WORLD_PVP_REPORT_LIST = 0x39D,	//server responses PVP report list
	
	WMSG_WORLD_Req_Talent = 0x3c9, // to the client push talent skills information list
	WMSG_WORLD_FORMATION_UPGRADE = 0x314, // client request to return to pack formation upgrade
	WMSG_WORLD_PASSIVESKILL_UPGRADE = 0x316, // the client requests for passive skill upgrades to return to pack
	WMSG_WORLD_UPGRADE_TALENT = 0x3AC, // the client requests for upgrade talent skills
	WMSG_WORLD_ADD_TALENT = 0x3AA, // to the client push new talent power information

	// vip
	WMSG_WORLD_VIP_AWARD_INFO_RESP = 0x29E,
	/**�ͻ�����������VIP��Ϣ*/
	CMSG_WORLD_REQ_TRIAL_VIP						= 0x3c7,
	WMSG_WORLD_REQ_TRIAL_VIP = 0x3C8,
	WMSG_WORLD_VIP_LEVEL = 0x1EF,
	WMSG_WORLD_UPDATE_GOLDSUM = 0x1EE,
	//login
	CMSG_WORLD_VIP_AWARD_INFO_REQ = 0x29D,

	/*
			����BOSS
		*/
	/** �ͻ��˻�ȡ����BOSS�����ʱ�� */
	CMSG_WORLDBOSS_GETOPENTIME	= 0X2C6,
	/** ����BOSS�����ʱ�� */
	WMSG_WORLDBOSS_OPENTIME	= 0X2C7,
	/** ����BOSS������Ϣ */
	WMSG_WORLDBOSS_PLAYERINFO = 0X2C8,
	/** ����BOSS�BOSS��Ϣ */
	WMSG_WORLDBOSS_BOSSINFO = 0X2C9,
//		/** ����BOSS�����ս������ */
//		WMSG_WORLDBOSS_PLAYERINFO:int = 0X2CA	;
		/** ���ʹ������BOSS��͹��� */
	CMSG_WORLDBOSS_INSPIRE	= 0X2CB,
	/** ����BOSS��͹����� */
	WMSG_WORLDBOSS_INSPIRE_RES = 0X2CC,
	/** ���ʹ�ø��� */
	CMSG_WORLDBOSS_RELIVE	= 0X2CD,
	/** ���ʹ�ø����� */
	WMSG_WORLDBOSS_RELIVE = 0X2CE,
	/** �����������BOSS������Ϣ */
	CMSG_WORLDBOSS_PLAYERINFO = 0X2CF,
	/** ������� ����BOSS�BOSS��Ϣ */
	CMSG_WORLDBOSS_BOSSINFO = 0X2DC,
	/** ������� �˳�����BOSS� */
	CMSG_WORLDBOSS_QUIT = 0X2DD,
	/* ����BOSS end */
	CMSG_COMMU_BE_BLESSED = 0x231,

	//
	CMSG_MAPS_OF_CITY_INFO = 0x3DA,
	WMSG_MAPS_OF_CITY_INFO = 0x3DB,

	CMSG_WORLD_DUNGEON_ENTER_TIMES					= 0x372,			//���󸱱����������Ϣ
	WMSG_WORLD_DUNGEON_ENTER_TIMES					= 0x373,			//���ظ������������Ϣ
	CMSG_WORLD_DUNGEON_BUY_ENTER_TIMES				= 0x374,			//�����򸱱��������
	WMSG_WORLD_DUNGEON_BUY_ENTER_TIMES				= 0x375,			//���ع��򸱱��������
	CMSG_WORLD_DUNGEON_ROOM_OP = 0x37D,
	WMSG_WORLD_DUNGEON_ROOM_OP_RESP = 0x37E,
	WMSG_WORLD_DUNGEON_ROOM_MEMBER_LIST = 0x37F,

	//*******************
	// Appoint
	//*******************
	CMSG_WORLD_DELEGATE_INFO = 0x1E0,
	WMSG_WORLD_DELEGATE_INFO_RETURN = 0x1E1,
	CMSG_WORLD_DELEGATE_REQUEST = 0x1E2,
	WMSG_WORLD_DELEGATE_RESULT = 0x1E3,
	CMSG_WORLD_DELEGATE_GET_ITEM = 0x1E4,
	CMSG_WORLD_DELEGATE_SELL_ITEM = 0x1E5,
	WMSG_WORLD_DELEGATE_GET_ITEM_RESULT = 0x1E6,
	WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP = 0x1DB,
	CMSG_WORLD_DELEGATE_GET_BLESS_ITEM = 0x1DC,
	WMSG_WORLD_DELEGATE_BLESS_INFO = 0x1DD,

	// mail
	CMSG_COMMU_MAIL_LIST				= 0x1A0,		//�����û��ʼ��б�
	GMSG_COMMU_MAIL_LIST				= 0x1A1,		//��Ӧ�û��ʼ�ͷ�б�����
	CMSG_COMMU_MAIL_CONTENT				= 0x1A2,		//�û������ʼ���ϸ����, Int:�ʼ�ΨһId
	GMSG_COMMU_MAIL_CONTENT				= 0x1A3,		//�����û��ʼ���ϸ����
	CMSG_COMMU_MAIL_DELETE				= 0x1A4,		//(420),�û�ɾ���ʼ�
	GMSG_COMMU_MAIL_DELETE				= 0x1A5,		//(421)��Ӧ�û�ɾ���ʼ����
	CMSG_COMMU_MAIL_SEND				= 0x1A6,		//(422),�û������ʼ�
	GMSG_COMMU_MAIL_SEND				= 0x1A7,		//(423)��Ӧ�û������ʼ����
	CMSG_COMMU_MAIL_REQUEST_ATTAC		= 0x1A8,		//(424)�ͻ���������������ȡ������Ʒ,Int:�ʼ�ID
	GMSG_COMMU_MAIL_RECV				= 0x1A9,		//(425)�û����յ����ʼ�
	CMSG_COMMU_MAIL_COUNTINFO			= 0x1AA,		//(426),�����û��ʼ��б�����
	GMSG_COMMU_MAIL_COUNTINFO			= 0x1AB,		//�����û��ʼ�������Ϣ
	GMSG_COMMU_MAIL_REQUEST_ATTAC_RESP	= 0x1AE,		//(430)Gate��Client������ȡ������Ʒ���

	// ����͹㲥
	WMSG_COMMU_SYS_BROADCAST			= 0x19A,		//410 ϵͳ�㲥
	WMSG_COMMU_SYS_MSG					= 0x19B,		//411 ϵͳ����
	WMSG_WORLD_HERO_BROADCAST		 	= 0x28B,		//651 Ӣ�۰�㲥
	
	CMSG_WORLD_TOWER_RECLIMB_REQ				= 0x3DE,//��������
	WMSG_WORLD_TOWER_RECLIMB_RESP			= 0x3DF,//�������÷���
	/**�ͻ���������������а���*/
	CMSG_WORLD_REQUEST_TOWER_AWARD	= 0X3C1,
	WMSG_WORLD_SEND_TOWER_GIFT		= 0x3C2,					//������������������ 

	/**�ͻ��˴򿪻��������*/
	CMSG_WORLD_ENTER_TOWER_GATE	= 0X3B2,
	/**����˷��ش򿪻����������Ϣ*/
	WMSG_WORLD_ENTER_TOWER_GATE = 0X3B3,
	/**�ͻ��˿�ʼ����*/
	CMSG_WORLD_APPLY_CLIMB_TOWER	= 0X3B4,
	/**����˷��ش��������Ϣ*/
	WMSG_WORLD_APPLY_CLIMB_TOWER	= 0X3B5,
	/**�ͻ��˿�ʼ��ս���ڹ���*/
	CMSG_WORLD_START_CLIMB_TOWER	= 0X3B6,
	/**����˷���ս�������Ϣ(����ս�ɹ�������Ӧ��¥�㽱��)*/
	WMSG_WORLD_RESULT_CLIMB_TOWER = 0X3B7,
	/**�ͻ��˳齱*/
	CMSG_WORLD_BEGIN_LOTTERY	= 0X3B8,
	/**����˷��س齱���*/
	WMSG_WORLD_BEGIN_LOTTERY	= 0X3B9,
	/**�ͻ�������*/
	CMSG_WORLD_LEAVE_TOWER	= 0X3BA,
	/**�ͻ��������������λ��Ϣ*/
	CMSG_WORLD_REQ_RANKLIST_BY_PAGE	= 0X3CA,
	/**����˷��������������λ��Ϣ*/
	WMSG_WORLD_REQ_RANKLIST_BY_PAGE	= 0X3CB,
	/**�ͻ��������Լ�������������Ϣ(*/
	CMSG_WORLD_REQ_MY_RANK	= 0X3CC,
	/**�ͻ�����������(�����ɹ���������ҳ��Ϣ)*/
	CMSG_WORLD_REPLACE_RANK	= 0X3CD,

	/**�ͻ��˹���*/
	CMSG_WORLD_TOWER_INSPIRE	= 0X3AD,
	/**����˷��ع�����*/
	WMSG_WORLD_TOWER_INSPIRE	= 0X3AE,
	/**�ͻ��˴�����boss*/
	CMSG_WORLD_TOWER_CHALLENGE_HIDDEN_MONSTER	= 0X3AF,
	/**�ͻ�����������boss��������*/
	CMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD	= 0X3CE,
	/**����˷�������boss��������*/
	WMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD	= 0X3CF,

	/*�ͻ��������������ս��ͼ*/
	CMSG_SILVERMINE_ENTER	 = 0x2E2,
	/*�����������ս��ͼ���*/					  
	WMSG_SILVERMINE_ENTER_RES	 = 0x2E3,
	/*����˳�����ս��ͼ*/						
	CMSG_SILVERMINE_QUIT		 = 0x2E4,
	/*�ͻ�����������ս��Ϣ*/					   
	CMSG_SILVERMINE_INFO		 = 0x2E5,
	/*����ս��Ϣ����*/							  
	WMSG_SILVERMINE_INFO		 = 0x2E6,
	/*�ͻ��������ƶ�*/							  
	CMSG_SILVERMINE_MOVE		 = 0x2E7,
	/*�����ƶ����*/							   
	WMSG_SILVERMINE_MOVE_RES		 = 0x2E8,
	/*����ս��֪ͨ*/							   
	WMSG_SILVERMINE_BATTLE	 = 0x2E9,
	/*�ͻ��˲ɼ�����*/							  
	CMSG_SILVERMINE_DIG		 = 0x2EA,
	/*����ɼ����*/							   
	WMSG_SILVERMINE_DIG_RES	 = 0x2EB,
	/*�ͻ��˻�ȡ��һ������ս����ʱ��*/			   
	CMSG_SILVERMINE_GETOPENTIME	 = 0x2EC,
	/*����˷�����һ������ս����ʱ��*/			   
	WMSG_SILVERMINE_OPENTIME	 = 0x2ED,
	/*���ʹ������ս����*/						
	CMSG_SILVERMINE_TOKEN	 = 0x2EE,			
	/*����ս����ʹ�ý��*/						
	WMSG_SILVERMINE_TOKEN_RES = 0x2EF,
	/*�����������*/							   
	WMSG_SILVERMINE_RANK = 0x367,
	/*���ʹ������ս����*/						
	CMSG_SILVERMINE_INSPIRE = 0x368,
	/*����ս����ʹ�ý��*/						
	WMSG_SILVERMINE_INSPIRE_RES = 0x369,
	
	/******added by chenjian Begin*****/
	/*ս��*/
	/*(296)���ݵ�ͼId��ȡ��ͼ����*/
	CMSG_WORLD_PROCESS_GET_PERFECT = 0x128,
	/*(548)�鿴�������PVE�����б�, int:�������ID*/
	CMSG_WORLD_BATTLE_REPORT_MONSTERGROUP = 0x136,
	/*(549) �������PVE�����б�*/
	WMSG_WORLD_BATTLE_REPORT_MONSTERGROUP = 0x137,
	/*****added by chenjian End*******/
	/** �ͻ�������-����ʷ��¼ */
	CMSG_EGG_HISTORY= 0x400,
	/** ����˷���-����ʷ��¼ */
	WMSG_EGG_HISTORY= 0x401,
	/** �ͻ�������-��Ը */
	CMSG_EGG_PLEGE= 0x402,
	/** ����˷���-��Ӧ�� */
	WMSG_EGG_PLEGE= 0x403,
	/** �ͻ�������-���� */
	CMSG_EGG_OPEN= 0x404,
	/** ����˷���-��Ӧ�� */
	WMSG_EGG_OPEN= 0x405,
	/** �ͻ�������-�� */
	CMSG_EGG_PICK= 0x406,
	/** ����˷���-��Ӧ�� */
	WMSG_EGG_PICK= 0x407,
	/** �ͻ�������-ϴ�� */
	CMSG_EGG_WASH= 0x408,
	/** ����˷���-��Ӧ�� */
	WMSG_EGG_WASH= 0x409,
	/** �ͻ�������-�ֿ� */
	CMSG_EGG_DEPOT= 0x40A,
	/** ����˷���-�ֿ� */
	WMSG_EGG_DEPOT= 0x40B,
	/** �ͻ�������-ȫ��ʰȡ */
	CMSG_EGG_PICK_ALL= 0x40C,
	/** ����˷���-�ֿ� */		
	WMSG_EGG_PICK_ALL= 0x40D,

	/**�ͻ������������������*/
	CMSG_WORLD_BUY_IDENTIFY_POS				= 0x2A0,
	/**����˷��ع�����*/
	WMSG_WORLD_BUY_IDENTIFY_POS				= 0x2A1,
	/**�ͻ�����������ٸ������������Ϣ*/
	CMSG_WORLD_REQ_IDENTIFY_INFO				= 0x2A2,
	/**����˷��ؼ���������Ϣ���*/
	WMSG_WORLD_REQ_IDENTIFY_INFO				= 0x2A3,
	/**�ͻ�������ٸ�����Լ���*/
	CMSG_WORLD_MOD_IDENTIFY_INFO				= 0x2A4,
	/**����˷��ع�����*/
	WMSG_WORLD_MOD_IDENTIFY_INFO			= 0x2A5,		
	/**�ͻ��˱�����ʱ�������*/
	CMSG_WORLD_SAVE_IDENTIFY							= 0x2A6,
	/**����˷�����ʱ�������*/
	WMSG_WORLD_SAVE_IDENTIFY						= 0x2A7,

	CMSG_DUNGEON_GUA                                = 0x410,
	WMSG_DUNGEON_GUA                                = 0x411,
	CMSG_DUNGEON_GUA_FIGHT                          = 0x412,
	CMSG_CHALLENAGE_VIGOUR_GET                      = 0x413,
	WMSG_CHALLENAGE_VIGOUR_GET                      = 0x414,
	CMSG_CHALLENAGE_VIGOUR_USE                      = 0x415,
	WMSG_CHALLENAGE_VIGOUR_USE                      = 0x416,
	CMSG_CHALLENAGE_GUA_AWARD_GET					= 0x417,

	/**����������Ϣ*/
	CMSG_WORLD_FREE_TOKEN_INFO_REQUEST = 0x24E,
	/**������Ϣ����*/
	WMSG_WORLD_FREE_TOKEN_INFO_RESP = 0x24F,

	CMSG_WORLD_TRADE_ROB_INFO = 0x28E,
	WMSG_WORLD_TRADE_ROB_INFO = 0x28F,

	CMSG_WORLD_TRADE_BUY_TOKEN = 0x29B,

	CMSG_WORLD_ADDTRADEPLAYER = 0x12C,
	WMSG_WORLD_CREATETRADEPLAYER = 0x12D,
	WMSG_WORLD_TRADEMOVE = 0x12F,
	/**���̳�ʼ��*/
	CMSG_WORLD_TRADE_INIT = 0x2B0,
	/**���������¼��б�*/
	WMSG_WORLD_TRADE_EVENT_LIST = 0x2B1,
	/**���������Ʒ�б�*/
	WMSG_WORLD_TRADE_QUEUE = 0x2B2,
	/**������Ҳ�λ�����ʣ�๺�����*/
	WMSG_WORLD_TRADE_BANK = 0x2B3,

	/**���������Ʒ������ʷ*/
	WMSG_WORLD_TRADE_HISTORY = 0x2B4,

	/**��ȡ�������ǵ���Ʒ�۸�*/
	CMSG_WORLD_TRADE_PRICE= 0x2B5,

	/**���͸������ǵ���Ʒ�۸�*/
	WMSG_WORLD_TRADE_PRICE= 0x2B6,
	/**���һ�������¼�*/
	WMSG_WORLD_TRADE_EVENT= 0x2B7,
	/**����ʼͨ��*/

	/**��ʼ��������*/
	CMSG_WORLD_TRADE_BEGIN= 0x2B8,
	/**��ʼ���̻�Ӧ*/
	WMSG_WORLD_TRADE_BEGIN_RESP = 0x2B9,
	/**������������*/
	CMSG_WORLD_TRADE_END = 0x2BA,
	/**�������̻�Ӧ*/
	WMSG_WORLD_TRADE_END_RESP= 0x2BB,

	/**ˢ��*/
	CMSG_WORLD_TRADE_REFLASH= 0x2BD,
	/**�����*/
	CMSG_WORLD_TRADE_BANK_ADD = 0x2BC,
	/**����Ʒ*/
	CMSG_WORLD_TRADE_BUY= 0x2C1,
	/**����ɾ����Ʒ*/
	 CMSG_WORLD_DEL_GOOD= 0X2CF,
	/**��������*/
	CMSG_WORLD_TRADE_ATTACK_REQ = 0x2C2,
	/**��������ظ�*/
	WMSG_WORLD_TRADE_ATTACK_REP = 0x2C3,
	/**���̽��*/
	WMSG_WORLD_TRADE_ATTACK_RESULT = 0x2C4,
	/**������֪ͨ*/
	WMSG_WORLD_TRADE_ATTACKED_NOTIFY = 0x2C5,

	/**��ȡ�̶���Ϣ*/
	CMSG_WORLD_TRADE_INFO= 0x2BE,
	/***/
	WMSG_WORLD_TRADE_INFO = 0x2BF,	


	/* DailyTaskEx */
	CMSG_WORLD_DAILY_TASK_INFO = 0x420,
	WMSG_WORLD_DAILY_TASK_INFO = 0x421,
	CMSG_WORLD_DAILY_TASK_ACCEPT = 0x422,
	WMSG_WORLD_DAILY_TASK_ACCEPT = 0x423,
	CMSG_WORLD_DAILY_TASK_SUBMIT = 0x424,
	WMSG_WORLD_DAILY_TASK_SUBMIT = 0x425,
	WMSG_WORLD_DAILY_TASK_PROGRESS = 0x427,
	CMSG_WORLD_DAILY_TASK_REFRESH = 0x428,
	WMSG_WORLD_DAILY_TASK_REFRESH = 0x429,
	CMSG_WORLD_DAILY_TASK_GIVEUP = 0x42A,
	WMSG_WORLD_DAILY_TASK_GIVEUP = 0x42B,

	/*ore*/
	CMSG_ORE_INFO                = 0x430,//����-ԭʯ������������                                                                                                        
	WMSG_ORE_INFO                = 0x431,//��Ӧ-ԭʯ������������                                                                                                        
	CMSG_ORE_OPEN_APPLY          = 0x432,//����-������                                                                                                                    
	WMSG_ORE_RESPONSE            = 0x433,//��Ӧ-������Ӧ��Ϣ                                                                                                              
	CMSG_ORE_PROGRESS            = 0x434,//����-ĳ����� ��ID��1~5 ľ~ˮ                                                                                                  
	WMSG_ORE_PROGRESS            = 0x435,//��Ӧ-ȫ�������ID ��λ��  �����쳣��0x433                                                                                      
	CMSG_ORE_REFRESH_APPLY       = 0x436,//����-ˢ��ĳ��  ��ID:1~5    ˢ��TYPE��0����ˢ 1����ˢ  ���ܳ���δ�����󣬿�CD�У��Ѿ��������ˢ��  �����쳣��0x433 ������0x435
	CMSG_ORE_PLANT               = 0x437,//����-��ֲ ��ID��1~5  �������¿����0x431 ���´˿�CD  ���½�Ǯ.����ԭʯ��0x431                                                  
	CMSG_ORE_BUY_STONE           = 0x438,//����-����ԭʯ  ��Ӧ������ɹ�����0x431 ʧ�ܷ���0x433                                                                           

	/* online Reward */
	/**�������߽�����*/
	CMSG_WORLD_ONLINE_AWARD_INFO	= 0x1E9,
	/**���߽�����Ϣ���ذ�*/
	WMSG_WORLD_ONLINE_AWARD_INFO_RETURN		= 0x1EA,
	/**���߽�����ʱȷ��*/
	CMSG_WORLD_ONLINE_AWARD_TIME_UP	= 0x1EB,
	/**��ȡ���߽�����Ʒ*/
	CMSG_WORLD_ONLINE_AWARD_GET	= 0x1EC,
	/**�ͻ��������Ծ����������Ϣ*/
	CMSG_WORLD_ACTIVEDAY_AWARD_INFO	= 0x1E7,
	/**��Ծ����������Ϣ���ذ�*/
	WMSG_WORLD_ACTIVEDAY_AWARD_INFO_RESP	= 0x1ED,
	/**��ȡ��Ծ��������*/
	CMSG_WORLD_ACTIVEDAY_AWARD_GET	= 0x1E8,


	WMSG_GONG_MSG = 0x440,
	CMSG_GONG_GETOPENTIME = 0x441,
	WMSG_GONG_OPENTIME = 0x442,
	WMSG_GONG_PROGRESS = 0x443,
	WMSG_GONG_SHOW_MONSTER = 0x444,
	CMSG_GONG_INFO = 0x445,
	WMSG_GONG_INFO = 0x446,
	WMSG_GONG_ISIN = 0x447,
	CMSG_GONG_MB   = 0x448,
	CMSG_GONG_MB_UIINFO   = 0x449,
	WMSG_GONG_MB_UIINFO   = 0x44A,
	WMSG_GONG_UPDATE_EXPBUFF = 0x44B,
	
	CMSG_CAMPFIGHT_ENTER_REQ                        = 0x450, // ��Ӫս��������
	WMSG_CAMPFIGHT_ENTER_RES                        = 0x451, //	��Ӫս���뷵��
	CMSG_CAMPFIGHT_QUIT_REQ                         = 0X452, //	��Ӫս�뿪����
	WMSG_CAMPFIGHT_QUIT_RES                         = 0X453, //	��Ӫս�뿪����
	CMSG_CAMPFIGHT_FIGHT_REQ                        = 0X454, //	��Ӫս��ս����
	WMSG_CAMPFIGHT_FIGHT_RES                        = 0X455, //	��Ӫս��ս����
	CMSG_CAMPFIGHT_CANCEL_REQ                       = 0X456, //	��Ӫսȡ����ս����
	WMSG_CAMPFIGHT_CANCEL_RES                       = 0X457, //	��Ӫսȡ����ս����
	CMSG_CAMPFIGHT_INFO_REQ                         = 0X458, //	��Ӫս��Ϣ����
	WMSG_CAMPFIGHT_INFO_RES                         = 0X459, //	��Ӫս��Ϣ����
	WMSG_CAMPFIGHT_LIVE_RES                         = 0X45A, //	��Ӫսֱ����Ϣ����
	WMSG_CAMPFIGHT_BROADCAST_RES                    = 0X45B, //	��Ӫս�㲥��Ϣ����
	CMSG_CAMPFIGHT_SCENEINFO_REQ                    = 0X45C, //	��Ӫսս����Ϣ����
	WMSG_CAMPFIGHT_SCENEINFO_RES                    = 0X45D, //	��Ӫսս����Ϣ����
	MSG_UNKNOW45E                                   = 0X45E, 
	MSG_UNKNOW45F								    = 0X45F,
	
	/* ------------------------------------------------------------------------------------------------ */
	
	CMSG_WORLD_GROUPLIST_REQ						= 0X270,			//��ս������ս���б�����
	WMSG_WORLD_GROUPLIST							= 0X271,			//��ս������ս���б���Ϣ
	CMSG_WORLD_GROUPINFO_REQ						= 0X272,			//��ս������Ϣ����
	WMSG_WORLD_GROUPINFO							= 0X273,			//��ս������Ϣ
	CMSG_WORLD_GROUPCREATE							= 0X274,			//��ս���齨������
	WMSG_WORLD_GROUPCREATE_RESULT					= 0X275,			//��ս���齨��������
	CMSG_WORLD_JOINGROUP 							= 0X276,			//������ս��������
	WMSG_WORLD_JOINGROUP_RESULT						= 0X277,			//������ս����������
	CMSG_WORLD_LEAVEGROUP							= 0X278,  // �뿪��������
	WMSG_WORLD_LEAVEGROUP_RESULT					= 0X279,	// �뿪������
	CMSG_WORLD_GROUPADJ								= 0X27A,	// ����λ������
	WMSG_WORLD_GROUPADJ_RESULT						= 0X27B,	// ����λ�ý��
	CMSG_WORLD_GROUPFIGHT							= 0X27C,	// ս������
	WMSG_WORLD_GROUPFIGHT_RESULT					= 0X27D, // ս�����
	WMSG_WORLD_GROUPFIGHT							= 0X27E,	// ս����������
	WMSG_WORLD_GROUPFIGHT_END						= 0X27F,	// ս���������
	/* ranking */
	/**�ͻ����������а��б���Ϣ*/
	CMSG_WORLD_RANK_LIST_REQUEST = 0x25B,
	/**����˷������а��б���Ϣ*/
	GMSG_WORLD_RANK_LIST_RESP = 0x25C,
	/**�ͻ����������������Ϣ*/
	CMSG_WORLD_RANK_PLAYER_INFO_REQUEST = 0x25D,
	/**����˷������������Ϣ*/
	GMSG_WORLD_RANK_PLAYER_INFO_RESP = 0x25E,


	CMSG_WORLD_KICKPLAYER							= 0X280,			//��ս�ӳ��Ƴ����
	WMSG_WORLD_KICKPLAYER_RESULT					= 0X281,			//��ս�ӳ��Ƴ���ҽ��
	/* ------------------------------------------------------------------------------------------------ */
};

#endif