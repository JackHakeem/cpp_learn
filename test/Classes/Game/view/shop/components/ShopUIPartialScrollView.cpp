#include "ShopUIPartialScrollView.h"

ShopUIPartialScrollView::ShopUIPartialScrollView(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	
}

ShopUIPartialScrollView* ShopUIPartialScrollView::bagScrollViewWithCCRect(const CCRect& mRect)
{
    ShopUIPartialScrollView *pScrollView = new ShopUIPartialScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}