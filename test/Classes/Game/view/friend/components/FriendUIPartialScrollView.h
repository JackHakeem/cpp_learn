#ifndef _FRIENDUIPARITIALSCROLLVIEW_H_
#define _FRIENDUIPARITIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"

class FriendUIPartialScrollView: public CCUIPartialScrollView
{
public:
	virtual ~FriendUIPartialScrollView(){};

	FriendUIPartialScrollView(const CCRect& mRect);
    static FriendUIPartialScrollView* bagScrollViewWithCCRect(const CCRect& mRect);

public:
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif