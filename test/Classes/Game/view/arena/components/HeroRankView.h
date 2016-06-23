#pragma once

#include "BaseType.h"
#include "UIListView/CCUIListView.h"
#include "model/arena/vo/HeroRankVo.h"

class SCMD285;
class HeroRankView:public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	enum
	{
		HeroRankViewZ_bg1,
		HeroRankViewZ_bg2,
		HeroRankViewZ_ListView,
		HeroRankViewZ_closebtn,
		HeroRankViewZ_title,
	};

	enum
	{
		HeroRankViewTAG_bg1,
		HeroRankViewTAG_bg2,
		HeroRankViewTAG_ListView,
		HeroRankViewTAG_closebtn,
		HeroRankViewTAG_title_0,
		HeroRankViewTAG_title_1,
		HeroRankViewTAG_title_2,
		HeroRankViewTAG_title_3,
		HeroRankViewTAG_title_name,
	};

	HeroRankView();
	~HeroRankView();

	bool init();

	void updateRes();
	virtual int getCount();
	virtual LayerNode * getView( int position );
	void update(SCMD285* param);
	void clickClose(CCObject* pSender);
	int getMaxLevByRange(int range);
	void createItems(std::vector<HeroRankVo>& arr);
	//virtual void onItemClickListener( LayerNode *itemCell, int position );
public:

	CCUIListView *_pListView;
	std::vector<CCObject*> _scrollPaneContent;
};