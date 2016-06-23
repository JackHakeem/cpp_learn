#ifndef _CC_UI_TASK_PANEL_LIST_VIEW_H_
#define _CC_UI_TASK_PANEL_LIST_VIEW_H_
#include "../UIListView/CCUIListView.h"

class CCUITaskPanelListView : public CCUIListView
{
public:
	//CCUITaskPanelListView(const CCRect& mRect, bool isHorizontal);
	static CCUITaskPanelListView* listViewWithCCRect(const CCRect& mRect, bool isHorizontal);
	virtual void onItemClick( int position );

	//virtual void bindView( CCNode *itemCell, int position, CCPoint ccPosition );

	void update(ccTime dt);
	void resetContentLayerSize();
	bool _hasExpand;
	int _clickPos;
protected:

private:
	bool _actionsRunning;
	int _heightDistance;
};
#endif