#include "FriendUIPartialScrollView.h"

FriendUIPartialScrollView::FriendUIPartialScrollView(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	
}

FriendUIPartialScrollView* FriendUIPartialScrollView::bagScrollViewWithCCRect(const CCRect& mRect)
{
    FriendUIPartialScrollView *pScrollView = new FriendUIPartialScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}


void FriendUIPartialScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	return;
	int newX = (int)touchPoint.x;
		
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
		handleTouchEndPageNext();
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
		handleTouchEndPagePre();
	}
	else
	{
		this->moveToPage(currentScreen);
		handleTouchEnd2Page();
	}	

	this->setIsTouchingMoving(false);
}
