#ifndef _REWARD_LIST_VIEW_H_
#define _REWARD_LIST_VIEW_H_
#include "utils/ScaleUtil.h"

#include "cocos2d.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"

#define CCRECT_REWARD_LISTVIEW  CCRectMake(POSX(120) , POSX(60) , POSX(720) , POSX(400))

USING_NS_CC;

class CCUIListView;

class RewardListView : public CCLayer, CCUIListViewAdapter,CCUIListViewItemActionListener
{
public:
	RewardListView();
	virtual ~RewardListView();
	virtual bool init();
	void load();
	void refresh();
	void onClickGetReward(CCObject * pSender);

public:
	enum
	{
		TAG_LIST,
	};

	virtual int getCount();
	virtual LayerNode * getView(int position);
	virtual void onItemClickListener( LayerNode *itemCell, int position );
	virtual void onItemTouchListener( LayerNode *itemCell, int position );
	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

	CCUIListView * _pListView;
    
};
#endif