#pragma once
/**
 *公会事件常量的定义
 * author, zhouwenbo 
 */
class GuildEventConst
{
public:
	enum
	{
		/**创建公会*/
		CREAT_GUILD	,								
		/**查看公会信息*/
		GUILD_VIEW,									
		/**查找公会*/
		GUILD_SEARCH,								
		/**升级军徽*/
		UPDATE_EMBLEM,								
		/**修改公会信息*/
		EDIT_GUILD_NOTICE,							
		/**搜索成员*/
		MEMBER_SEARCH,								
		/**查看我的排名*/
		FIND_ME,									
		/**显示离线玩家*/
		DISPLAY_OFFLINE,							
		/**转移会长*/
		LEADER_SHIF,								
		/**解散公会*/
		REMOVE_GUILD,								
		/**开除成员*/
		EXPEL_MEMBER,								
		/**加为好友*/
		ADD_FRIEND,									
		/**邀请组队*/
		INVITE_TEAM,								
		/**修改默认科技*/
		DEGAULT_TECH_CHANGE,						
		/**捐献银币*/
		DONATE_YB,									
		/**批准入会申请*/
		APPROVE_MEMBER,								
		/**拒绝入会申请*/
		REFUSE_MEMBER,								
		/**打开修改公会信息窗口*/
		OPEN_EDIT_VIEW,								
		/** 打开银币捐献窗口 */
		OPEN_DONATE_VIEW,							
		/** 向公会科技捐献银币 */
		DONATE_MONEY,								
	
		/** -- 后来增加 -- */
		
		/**退出公会*/
		EXIT_GUILD,									
		/**撤销取消公会*/
		REMOVE_GUILD_CANCEL,						
		/**查看成员列表*/
		GUILD_MEMBER_LIST,							
		/**查看成员信息*/
		GUILD_MENBER_INFO,							
		/**更改职务*/
		MEMBER_NOMINATE,							
		/**查看科技列表*/
		GUILD_TECH_LIST,							
		/**入会申请*/
		APPLY_GUILD,								
		/**查看公会列表*/
		GUILD_GET_LIST,								
		/**查看入会申请列表*/
		GUILD_APPLY_LIST,							
		/**显示申请的公会列表*/
		GUILD_APPLID_LIST,							
		/**点击成员列表弹出菜单 */
		MEMBER_ITEM_CLICK,							
		
		
		/**打开公会信息窗口*/
		OPEN_GUILD_INFO_VIEW,						
		/**关闭公会主窗口*/
		POP_GUILD_VIEW,								
		/**关闭公会列表窗口*/
		POP_PRE_GUILD_VIEW,							
		
	}; 
};
