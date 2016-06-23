#ifndef _CC_UI_LISTVIEW_CLICK_LISTENER_H_
#define _CC_UI_LISTVIEW_CLICK_LISTENER_H_
#include "cocos2d.h"
#include "../LayerNode.h"

class CCUIListViewItemActionListener 
{
public:
	CCUIListViewItemActionListener(){}
	~CCUIListViewItemActionListener(){}
	
	virtual void onItemClickListener(LayerNode *itemCell, int position) {}
	virtual void onItemTouchListener(LayerNode *itemCell, int position) {}
	virtual void onItemTouchCancelListener(LayerNode *itemCell, int position) {}
};
#endif
