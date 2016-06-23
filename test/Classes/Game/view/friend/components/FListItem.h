#pragma once

#include "BaseType.h"
#include "model/friend/vo/FriendInfoVo.h"
#include "utils/Timer.h"

class FriendView;
class FListItem: public LayerNode
{
public:
	enum
	{
		FListItemZ_frame,
		FriendViewZ_fight,
		FriendViewZ_check,
		FriendViewZ_name,
		FriendViewZ_lvname,
		FriendViewZ_lv,
		FriendViewZ_sex,
	};

	enum
	{
		FListItemTAG_frame,
		FriendViewTAG_fight,
		FriendViewTAG_check,
		FriendViewTAG_name,
		FriendViewTAG_lvname,
		FriendViewTAG_lv,
		FriendViewTAG_sex,
	};

	FListItem();
	~FListItem();

	void init(FriendInfoVo info, int32 btnCategory, int32 tag);
	void applyFight(CCObject* pSender);
	void applyCheck(CCObject* pSender);
	void addPlayer(CCObject* pSender);
	void applyRemove(CCObject* pSender);
	void moveFriendOut(CCObject* pSender);
	void privateChat(CCObject* pSender);
	void delPlayer(CCObject* pSender);
	FriendView* list();
	void moveToBlack(CCObject* pSender);
public:
	FriendInfoVo _friendInfo;
	CC_PROPERTY(int32, _btnIndex, btnIndex)
	Number lastZhengliTime;
};