#pragma once

#include "BaseType.h"
#include "CCUIPartialScrollView.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "model/guild/vo/MemberVo.h"

class GuildVoBase;
class CommonList:public CCUIPartialScrollView
{
public:
	CommonList(const CCRect& mRect);
	~CommonList();

    static CommonList* commonListScrollViewWithCCRect(const CCRect& mRect);

	void setDatas(std::list<GuildVoBase*>& voArr, int page);
	void updateList(int page = -1);

public:
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	int stateSscroll;
	void handleTouchEndPagePre();
	void handleTouchEndPageNext();
	void handleTouchEndAfter(bool same, int curlayertag);
public:
	std::list<GuildVoBase*> _itemArr;//存放列表元素的数组
	//std::list<VerifyItem> _itemArr_VerifyItem;
};