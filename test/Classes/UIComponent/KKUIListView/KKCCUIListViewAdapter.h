#ifndef _KKCC_UI_LISTVIEW_ADAPTER_H_
#define _KKCC_UI_LISTVIEW_ADAPTER_H_
#include "cocos2d.h"
#include "LayerNode.h"
class KKCCUIListViewAdapter
{
public:
	KKCCUIListViewAdapter(){}
	~KKCCUIListViewAdapter(){}

	virtual int getCount() {return 0;}
	virtual LayerNode *getView(int position) {return 0;}
	virtual std::vector<LayerNode*>* getViewList() {return 0;}
};

#endif