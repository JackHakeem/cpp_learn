#include "BagUIPartialScrollView.h"

BagUIPartialScrollView::BagUIPartialScrollView(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	
}

BagUIPartialScrollView* BagUIPartialScrollView::bagScrollViewWithCCRect(const CCRect& mRect)
{
    BagUIPartialScrollView *pScrollView = new BagUIPartialScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}