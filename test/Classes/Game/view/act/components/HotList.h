#pragma once

#include "UIListView/CCUIListView.h"
#include "socket/command/s38/SCMD38F.h"
class ActItem;
class HotList:public CCUIListView,public CCUIListViewAdapter,public CCUIListViewItemActionListener
{
public:
	static HotList* listViewWithCCRect(const CCRect& mRect, bool isHorizontal);
	~HotList();

	virtual int getCount();
	virtual LayerNode * getView( int position );

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	void updateView();

public:
	std::list<SCMD38FNode> m_arr;
	std::vector<ActItem*> m_arrItem;
	int _index;
	int _curClickIndex;
	bool _isCurClickItemExpand;
};