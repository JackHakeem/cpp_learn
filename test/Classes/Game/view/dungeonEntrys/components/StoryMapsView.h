#ifndef HLQS_StoryMapsView_H_
#define HLQS_StoryMapsView_H_
#include "PopContainer.h"
//#include "UIListView/CCUIListView.h"
//#include "UIListView/CCUIListViewAdapter.h"
//#include "UIListView/CCUIListViewItemActionListener.h"
#include "StoryCityLists.h"
#include "StoryMapLists.h"
#include "TouchMapNode.h"
#include "CCUIBackground.h"

class StoryMapsView: public PopContainer
{
public:
	StoryMapsView();
	~StoryMapsView();
	void openCity(int index, bool open);
	void selectTab(int tab, bool byInit);
	bool init();
	void addScrollViews();
	void setViewAdapter();
	void addIcons(std::vector<MapData>& data);
	void deleteIcons();
	void clickCloseHandler(CCObject* pSender);
	//virtual void removeDataObjectChild();
	//virtual int getCount();
	//virtual LayerNode * getView( int position );
	//virtual void onItemClickListener( LayerNode *itemCell, int position );
	void clearCityDataList();

public:
	StoryCityLists* _storyCityList;
	StoryMapLists* _storyMapList;
	CCUIBackground* _container1;
	CCUIBackground* _container2;
	CCLayer* layer;
	enum
	{
		STORYMAP_LAYER = 0,
		STORYMAP_CONTAINER1,
		STORYMAP_CONTAINER2,
	};
};

#endif