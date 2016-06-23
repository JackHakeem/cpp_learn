#ifndef _RANKINGLISTVIEW_H_
#define _RANKINGLISTVIEW_H_

#include "BaseType.h"
#include "LayerNode.h"
#include "UIListView/CCUIListView.h"

class RankingListView : public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	enum
	{
		RANK_ITEM_SELECTED = 0,
	};

	RankingListView();
	~RankingListView();
public:
	virtual bool init();

	//ListView adapter
	virtual int getCount();
	virtual LayerNode* getView(int position);
	virtual void onItemClickListener(LayerNode* item, int position);

	void addItem(LayerNode* item);
	void removeAllItems();
	void refresh();
private:
	std::vector<LayerNode*> _itemList;

	CCUIListView* _pListView;
	LayerNode* _pSelectedItem;
};
#endif
