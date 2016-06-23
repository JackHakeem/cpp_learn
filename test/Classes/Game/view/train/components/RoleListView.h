#ifndef _TrainRoleListView_H_
#define _TrainRoleListView_H_
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "UIListView/CCUIListView.h"

class LayerNode;

class RoleListView : public CCUIListView, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	RoleListView(const CCRect& mRect);
	static RoleListView* listViewWithCCRect(const CCRect& mRect, bool isHorizontal);

	void showIsTrained(int position);
	void resetView();
	void showHighLight(LayerNode *itemCell);

public:
	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemClickListener( LayerNode *itemCell, int position );
	virtual void onItemTouchListener( LayerNode *itemCell, int position );
	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

public:

	enum
	{
		Tag_ListItem = 100,
		Tag_HighLight = 200,
	};

	CCRect _rect; 
};


#endif
