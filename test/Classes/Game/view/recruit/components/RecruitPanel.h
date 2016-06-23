#ifndef _RECUITPANEL_H_
#define _RECUITPANEL_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "model/recruit/vo/RecruitInfo.h"
#include "RecruitItem.h"
#include "CCUIPartialScrollView.h"
using namespace cocos2d;

class RecruitPanel : public CCUIPartialScrollView
{
public:
	//RecruitPanel();
	RecruitPanel(const CCRect& mRect);
	~RecruitPanel(){};

public:
	static RecruitPanel* recruitPanelScrollViewWithCCRect(const CCRect& mRect);
public:
	bool init();
	//LAYER_NODE_FUNC(RecruitPanel);
	void createItems( vector<RecruitInfo> infos, int page, uint totalPage, int pagesize );
	void reBuildItems( vector<RecruitInfo> infos, int page, int pagesize );
	void onSingleClickHandler( RecruitItem* item );
	map<int, RecruitItem*> _dic;
	RecruitItem* _item;
	bool isList;

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void removeAllChild();
	void visit();
};

#endif