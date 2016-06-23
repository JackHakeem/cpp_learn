#ifndef _NEWHAND_CONST_H_
#define _NEWHAND_CONST_H_
#include "manager/CDManage.h"
#include "BaseType.h"
#include "utils/Singleton.h"

USING_NS_CC;

class NewhandConst : public Singleton<NewhandConst>
{
public:
	enum
	{
		//新手阶段开启的各种功能
		ENABLE_TRAIN_CD 		= 51,//训练cd
		ENABLE_STRENG_CD	 	= 55,//强化cd
		ENABLE_WASH 			= 70, //开启培养按钮功能
		ENABLE_IDENTIFY 		= 75, //开启鉴定按钮功能
		ENABLE_RECRUIT 			= 71, //开启佣兵招募
		ENABLE_Appoint 			= 72, //开启委派黑市
		ENABLE_TRADER  			= 74, ///开启跑商
		ENABLE_SPIRIT  			= 76, ///开启武魂
		ENABLE_TRAIN  			= 77, ///开启训练tab按钮

		//新手引导的各种事件
		EVENT_OPEN_GIFT  							= 101, //打开礼包
		EVENT_TRIAN_SELECT 						 	= 102, //选择训练人物
		EVENT_TRIAN_START   						= 103, //开始训练
		EVENT_CRY_WIND  							= 104, //升级风之水晶
		EVENT_OPEN_PASSIVE  						= 105, //打开被动技能列表
		EVENT_OPEN_WASH 							= 106, //打开洗属性窗口
		EVENT_WASH_TYPE 							= 107, //加强洗属性方式
		EVENT_OPEN_ARENA 							= 108, //打开竞技场
		EVENT_OPEN_FARM 							= 109, //打开竞技场
		EVENT_DEPLOY_MV_ROLE_SIT					= 110, //布阵--更换主角位置动画结束
		EVENT_DEPLOY_OP_ROLE_SIT 					= 111, //布阵--更换主角位置操作
		EVENT_DEPLOY_MV_CHANGE_TYPE 				= 113, //布阵--更换阵型动画结束
		EVENT_DEPLOY_OP_CHANGE_TYPE 				= 115, //布阵--更换阵型操作
		EVENT_DEPLOY_OP_ACTIVE 						= 117, //布阵--启用阵型操作
		EVENT_STRENG_SELECT_MERC 					= 119, //强化--选择了人物
		EVENT_STRENG_SELECT_EQUIP 					= 121, //强化--选择了物品
		EVENT_MAP_AWARD_POP 						= 122, //通关奖励--弹出面板
		EVENT_MAP_AWARD_GET 						= 123, //通关奖励--领取奖励


		EVENT_LEVY_GET										= 201, // 领取赏金完成
		EVENT_ORE_OVER										= 203, // 水晶园加工完成
		EVENT_ARENA_OVER									= 205, // 竞技场打一次完成
		EVENT_TRAIN_OVER									= 207, // 训练完成

		EVENT_GOLDLEVY_GET							= 501, // 王国恩赐完成
		EVENT_ENTRANCE_OVER							= 502, // 传送门相关完成
		EVENT_CHALLEGE_COPY_OVER			= 503, // 挑战副本相关完成
		EVENT_TAOFA_OVER									= 504, // 讨伐相关完成
		EVENT_EGG_OVER										= 510, // 许愿池完成
		EVENT_DAILYTASK_OVER						= 515, // 日常任务完成

		EVENT_FRIEND_OVER								= 803, // 好友添加完成
		EVENT_UPFORMATION_OVER				= 806, // 研习升级完成
		EVENT_GUILD_OVER									= 809, // 公会引导完成
		EVENT_PEIYANG_OVER								= 812, // 培养引导完成

		//新手引导的各种位置编号
		LOC_POP = 10,//各种弹出框，对话框
		LOC_TASK = 11,//任务追踪栏
		LOC_MAIN = 12,//主导航
		LOC_CD = 13,//cd栏
		LOC_SEC = 14,//次导航
		LOC_MAP = 15,//小地图按钮
		LOC_WORLD = 16,//地图入口
		LOC_CHILD = 17,//子地图入口
		LOC_DEFAULT = 18, // Default loc should init a CCPoint.
		LOC_VSCROLL = 19, // Default loc should init a CCPoint.


		//以下为新手引导各种对象的编号，不能随便更改!
		ITEM_COM_WIN			= 0,//所有临时父窗口
		ITEM_BAG_CLOSE 			= 1,//关闭背包按钮
		ITEM_FIGURE_CLOSE 		= 2,//关闭角色按钮
		ITEM_WORLD_MAP 			= 3,//世界地图按钮
		ITEM_STRENG_UP 			= 4,//强化按钮
		ITEM_RECRUIT 			= 5,//招募
		ITEM_FORMATION_HEAD 	= 6,//阵型头像
		ITEM_FORMATION_SIT6 	= 7,//阵型位置
		ITEM_TRAIN_START 		= 8,//开始训练
		ITEM_TRAIN_EXP 			= 9,//突飞按钮
		ITEM_PASSIVE_PIC 		= 13,//被动技能
		ITEM_PASSIVE_LIST 		= 14,//被动技能列表
		ITEM_LEVY 				= 15,//领取按钮
		ITEM_UPSKILL 			= 16,//技能升级按钮
		ITEM_WASH 				= 17,//洗属性按钮
		ITEM_OPEN_GIFT 			= 18,//打开礼包
		ITEM_PUT_ON 			= 19,//穿上装备

		ITEM_CRYSTAL_UP 		= 10,//水晶升级按钮
		ITEM_CRYSTAL_WIND 		= 11,//风之水晶
		ITEM_CRYSTAL_CLOSE 		= 12,//关闭水晶
		ITEM_CRYSTAL_FIRE 		= 20,//火之水晶
		ITEM_CRYSTAL_EARTH 		= 21,//土之水晶
		ITEM_CRYSTAL_WATER 		= 22,//水之水晶

		ITEM_DEPLOY_IMD 		= 23,//立即布阵按钮
		ITEM_FORMATION_SIT5 	= 24,//阵型位置
		ITEM_FORMATION_CLIP13 	= 25,//鱼龙阵图标
		ITEM_FORMATION_ACTIVE 	= 26,//启用阵型按钮

		ITEM_MAP_AWARD_BTN 		= 31,//领取通关奖励按钮

		ITEM_TRAIN_CLOSE 		= 81,//关闭训练按钮
		ITEM_STRENG_CLOSE 		= 82,//关闭强化按钮
		ITEM_FRIEND_CLOSE 		= 83,//关闭好友按钮
		ITEM_FORMATION_CLOSE 	= 84,//关闭布阵按钮
	};

	int getCDType(int value)
	{
		switch(value){
		case 50: return CDManage::CRYSTAL_0;
		case 51: return CDManage::TRAINING;
		case 52: return CDManage::BLESSING;
		case 53: return CDManage::FIGHT;
		case 54: return CDManage::COLLECTION;
		case 55: return CDManage::STRENGTHEN;
		default: return -1;
		}
	}

	std::map<int, CCNode *> _itemDic;

	void registerItem(int id, CCNode *pNode)
	{
		_itemDic.insert(make_pair(id, pNode));
	}

	CCNode *getItem(int id)
	{
		std::map<int, CCNode *>::iterator it = _itemDic.find(id);
		if(it != _itemDic.end())
		{
			CCNode *pNode = it->second;
			return pNode;
		}
		return NULL;
	}
};
#endif