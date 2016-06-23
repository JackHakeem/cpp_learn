#ifndef _KKCC_UI_LISTVIEW_CLICK_LISTENER_H_
#define _KKCC_UI_LISTVIEW_CLICK_LISTENER_H_
#include "cocos2d.h"
#include "../LayerNode.h"

class KKCCUIListViewItemActionListener 
{
public:
	KKCCUIListViewItemActionListener(){}
	~KKCCUIListViewItemActionListener(){}
	
	virtual void onItemClickListener(LayerNode *itemCell, int position) {}
	virtual void onItemTouchListener(LayerNode *itemCell, int position) {}
	virtual void onItemTouchCancelListener(LayerNode *itemCell, int position) {}
};
#endif
