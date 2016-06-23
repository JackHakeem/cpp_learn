#ifndef _OnlineRewardView_H_
#define _OnlineRewardView_H_
#include "PopContainer.h"

USING_NS_CC;

class OnlineRewardView : public PopContainer
{
public:
	OnlineRewardView();
	~OnlineRewardView();

	virtual bool init();
	virtual void close();

	void addStaic();
	void addVListView();

	void NewHandHandle();

	void clickCloseHandler(CCObject * pSender);

	void refreshListView();

public:
	enum
	{
		TAG_BG,
		Tag_ListView,
	};
	enum
	{
		Z_BG,
	};
	enum
	{
		
	};

	CCSize _viewSize;
	CCLayer * _pContainer;
};

#endif
