#ifndef _CC_UI_LISTVIEW_ADAPTER_H_
#define _CC_UI_LISTVIEW_ADAPTER_H_
#include "cocos2d.h"
#include "LayerNode.h"
class CCUIListViewAdapter
{
public:
	CCUIListViewAdapter(){}
	~CCUIListViewAdapter(){}

	virtual int getCount() {return 0;}
	virtual LayerNode *getView(int position) {return NULL;}
};

#endif