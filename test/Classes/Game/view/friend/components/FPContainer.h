#pragma once


#include "BaseType.h"
#include "model/friend/vo/FriendInfoVo.h"
#include "UIListView/CCUIListView.h"
#include "CCUIPartialScrollView.h"

class FListItem;
class FriendView;
class FPContainer:public CCUIPartialScrollView
{
public:
	enum
	{
		FPContainerZ_ListView,
	};

	enum
	{
		FPContainerTAG_ListView,
	};
public:
    static FPContainer* friendScrollViewWithCCRect(const CCRect& mRect);

	FPContainer(const CCRect& mRect);
	~FPContainer();

	void setlistItem(FriendInfoVo friInfo, int32 tag, CCLayer* dst);

	//void updateFList();

	//bool init();
//	virtual int getCount();
	//virtual LayerNode * getView( int position );
	//virtual void onItemClickListener( LayerNode *itemCell, int position );
	FriendView* view();
	void quickAddFriHandler(FriendInfoVo* param);

	CCLayer* getCurScreen();
	virtual void handleTouchEndPagePre();
	virtual void handleTouchEndPageNext();

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void handleTouchEndAfter(bool same, int curlayertag);
	void registerWithTouchDispatcher();
public:

	CC_PROPERTY(int32, _index, index)
	std::vector<FListItem*> _list;//列表，动态更新
	//CCUIListView *_pFListView;
	int stateSscroll;
};
