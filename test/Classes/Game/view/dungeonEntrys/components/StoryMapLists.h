#ifndef HLQS_StoryMapLists_H_
#define HLQS_StoryMapLists_H_
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "UIListView/CCUIListView.h"
#include "socket/command/s3d/SCMD3DB.h"
#include "TouchMapNode.h"

class StoryMapLists:public LayerNode, public CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	CCUIListView *_pListView;
	std::map<int /*index*/, LayerNode*> m_vMapList;
	int _mapCnt;

public:
	StoryMapLists();
	virtual ~StoryMapLists();
	virtual int getCount();
	virtual LayerNode * getView(int position);
	//virtual void onItemClickListener(LayerNode *itemCell, int position);
	void startListViewHandler();
	void initDataList(MapData node, bool open);
	void setViewAdapter();
	void deleteIcons();

	// 20120629
	// Doyang.
	// Add last map tip.
	void setLastMapTip(int tipId);

	//LH
	int getNowMapIndex();

	CC_SYNTHESIZE(int , _nowMapId , NowMapId);
};

#endif