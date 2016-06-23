#pragma once

#include "PopContainer.h"
#include "BaseType.h"
#include "model/notice/NoticeManager.h"
#include "UIListView/CCUIListView.h"

class NoticeItem;
class CenterView:public PopContainer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	enum
	{
		CenterViewZ_bg1,
		CenterViewZ_bg2,
		CenterViewZ_title,
		CenterViewZ_ListView,
		CenterViewZ_closeBtn,
	};

	enum
	{
		CenterViewTAG_bg1,
		CenterViewTAG_bg2,
		CenterViewTAG_title,
		CenterViewTAG_ListView,
		CenterViewTAG_closeBtn,
	};

	enum
	{
		ADD_FRIEND,
		BLESS_FRIEND,
		SEE_REPORT,
		GOTO_NPC,

	};
	CenterView();
	bool init(int type, NoticeManager::NoteElmArr* arr);
	void reLocate();
	void pageLayout(int32 now, int32 max);
	void clear();

	void updateRes();
	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemClickListener( LayerNode *itemCell, int position );
public:
	std::vector<NoticeItem*> _itemArr;
	NoticeManager* _noticeManager;
	int32 _type;
	int32 _pageMax;
	int32 _pageNum;
	LayerNode* _panel;
	CCUIListView *_pListView;

};