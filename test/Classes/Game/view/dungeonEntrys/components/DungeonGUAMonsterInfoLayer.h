#pragma once

#include "BaseType.h"
#include "UIListView/CCUIListView.h"

class DungeonGUAMonsterInfoLayer:public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	DungeonGUAMonsterInfoLayer();
	~DungeonGUAMonsterInfoLayer();

	bool init(std::vector<std::string> values, CCPoint offset);
	virtual int getCount();
	virtual LayerNode * getView( int position );
	void updateRes();


public:
	CCUIListView *_pListView;
	std::vector<CCObject*> _scrollPaneContent;
};