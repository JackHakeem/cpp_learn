#pragma once
#include "BaseType.h"
class SilverConst
{		
public:
	/// 定义常量 
	static const int NON_CAMP       = -1;  // 无阵营 
	static const int CAMP_ZERO 		= 0;  // 阵营1
	static const int CAMP_ONE  		= 1;  // 阵营2
	static const int CAMP_TWO  		= 2;  // 阵营3
		
	/// 定义令牌ID 即令牌的类型type   0：袭；1：扰；2：驰；3：查； 
	static const int TOKEN_RAID     = 0;   // 袭
	static const int TOKEN_HARASS   = 1;    // 扰
	static const int TOKEN_SPEED    = 2;    // 驰
	static const int TOKEN_SEARCH   = 3;    // 查

 	enum
	{
		/// 定义事件 
		
		EXIT_MINE_VIEW,//:String = "EXIT_MINE_VIEW";  // 离开银矿战 
	
		CLICK_MINE_ITEM,//:String = "CLICK_MINE_ITEM";  // 点击矿
	
		CLICK_DIG_BTN,//:String = "CLICK_DIG_BTN";  // 点击挖矿按钮 
	
		DIG_MINE,//:String = "DIG_MINE";   // 挖矿
	
		MOVE_MINE,//:String = "MOVE_MINE";  // 移动
	
		LOOK_REPORT,//:String = "LOOK_REPORT";  // 查看战报 
	
		PVP_REPROT,//:String = "PVP_REPROT";  // 查看PVP战报 
	
		DO_INSPIRE,//:String = "DO_INSPIRE";	// 使用鼓舞 
	
		CLICK_TOKEN,//:String = "CLICK_TOKEN";  // 点击令牌 区分于使用令牌 
	
		USE_TOKEN,//:String = "USE_TOKEN";   // 使用令牌 
	};

};