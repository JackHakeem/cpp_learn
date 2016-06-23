#ifndef HLQS_ChallengeMapLists_H_
#define HLQS_ChallengeMapLists_H_
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "UIListView/CCUIListView.h"
#include "TouchMapNode.h"

class ChallengeMapLists:public LayerNode, public CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	CCUIListView *_pListView;
	std::map<int /*index*/, LayerNode*> m_vMapList;
	int _mapCnt;

public:
	ChallengeMapLists();
	~ChallengeMapLists();
	virtual int getCount();
	virtual LayerNode * getView(int position);
	void startListViewHandler();
	void initDataList(MapData node, bool open);
	void setViewAdapter();
	void deleteIcons();
};

#endif