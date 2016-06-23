#ifndef _DynamicLocation_H_
#define _DynamicLocation_H_

/**
 * //	ITEM_POS_NONE = 0,		// 没有位置
//	ITEM_POS_BAG = 1,		// 包裹
//	ITEM_POS_BANK = 2,		// 仓库
//	ITEM_POS_ROLE = 3,		// 角色身上
//	ITEM_POS_MAIL = 4,		// 邮件 
 */

enum DynamicLocation
{
	BAG 	= 1,
	BANK,
	FIGURE,
	MAIL,
};

#endif