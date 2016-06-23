#ifndef HLQS_StoryCityLists_H_
#define HLQS_StoryCityLists_H_
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "UIListView/CCUIListView.h"

class StoryCityLists:public LayerNode, public CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	CCUIListView *_pListView;
	std::vector<LayerNode*> m_vMapList;
	std::vector<int> _dataList;
public:
	StoryCityLists();
	virtual int getCount();
	virtual LayerNode * getView(int position);
	virtual void onItemClickListener(LayerNode *itemCell, int position);
	void startListViewHandler();
	void initDataList(int index, bool open);
	void setViewAdapter();
	int indexToMapId(int index);
	void clearDataList();
	void sendMapRequest(int mapId);


	int _currentTaskMapId;
};

#endif