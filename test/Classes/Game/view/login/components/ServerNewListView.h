#ifndef _SERVER_NEW_LIST_VIEW_H_
#define _SERVER_NEW_LIST_VIEW_H_
#include "utils/ScaleUtil.h"

#define CCPOINT_SERVER_LIST ccp(POSX(17), POSX(30))
#define CCSIZE_SERVER_LIST CCSizeMake(POSX(800), POSX(246))

#include "cocos2d.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"

USING_NS_CC;

class CCUIListView;

class ServerNewListView : public CCLayer, CCUIListViewAdapter,CCUIListViewItemActionListener
{
public:
	ServerNewListView();
	~ServerNewListView();
	virtual bool init();

public:
	CC_SYNTHESIZE(int, areaID, AreaID);
	CC_SYNTHESIZE(std::string, selectedIP, SelectIP);
	CC_SYNTHESIZE(unsigned short, selectedPort, SelectedPort);
	CC_SYNTHESIZE(int,servState,ServState);
	CC_SYNTHESIZE(LayerNode *,preSeclecedItem,PreSeclecedItem);
	CC_SYNTHESIZE(bool,_isServSelected,IsServSelected);

	virtual int getCount();
	virtual LayerNode * getView(int position);

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );
    
    void refresh();
	void onServerSelected(CCObject * pSender);
	int getListTouchPri();
	LayerNode * getItemLayerByIndex(int index);
	void setItemLight(CCNode *pSender);

public:
	enum
	{
		TAG_LIST = 0,
		TAG_LIGHT = 101,
	};
	CCUIListView * _pListView;
	int _CurLightIndex;
};
#endif