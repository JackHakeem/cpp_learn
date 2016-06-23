#ifndef _VIP_SCROLLVIEW_H_
#define _VIP_SCROLLVIEW_H_
#include "CCUIPartialScrollView.h"
#include "VipScrollViewListener.h"
#include "cocos2d.h"

USING_NS_CC;

class VipScrollView : public CCUIPartialScrollView
{
public:
	VipScrollView(CCRect rect);
	~VipScrollView();
	static VipScrollView *scrollViewWithRect(CCRect rect);

	void initData();
	void scrollToPage(int pageId);

	CC_SYNTHESIZE(VipScrollViewListener *, _pScrollListener, ScrollListener);

private:
	int _currentPageId;

	CCLayer *buildPageLayer(int pageId);

	virtual void handleTouchEndPagePre();

	virtual void handleTouchEndPageNext();

	virtual void handleTouchEnd2Page();

};

#endif