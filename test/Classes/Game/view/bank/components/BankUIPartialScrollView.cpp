#include "BankUIPartialScrollView.h"

BankUIPartialScrollView::BankUIPartialScrollView(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	
}

BankUIPartialScrollView* BankUIPartialScrollView::bankScrollViewWithCCRect(const CCRect& mRect)
{
    BankUIPartialScrollView *pScrollView = new BankUIPartialScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}