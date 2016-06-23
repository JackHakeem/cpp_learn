#ifndef _AREA_LIST_VIEW_H_
#define _AREA_LIST_VIEW_H_

#include "cocos2d.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "CCLayer.h"
#include "utils/ScaleUtil.h"

#define CCPOINT_AREA_LIST ccp(POSX(0), POSX(0))
#define CCSIZE_AREA_LIST CCSizeMake(POSX(230), POSX(300))

USING_NS_CC;

class CCUIListView;

class AreaListView : public CCLayer, CCUIListViewAdapter,CCUIListViewItemActionListener
{
public:
	AreaListView();
	~AreaListView();
	virtual bool init();

public:
	CC_SYNTHESIZE(LayerNode *,preSeclecedItem,PreSeclecedItem);
	CC_SYNTHESIZE(bool,_isAreaSelected,IsAreaSelected);

	virtual int getCount();
	virtual LayerNode * getView(int position);

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

    void refresh();
public:
	enum
	{
		TAG_LIST = 0,
		TAG_LIGHT,
	};
	CCUIListView * _pListView;
};

#endif