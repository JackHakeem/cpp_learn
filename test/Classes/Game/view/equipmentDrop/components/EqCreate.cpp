#include "EqCreate.h"

EqCreate* EqCreate::listViewWithCCRect(const CCRect& mRect, bool isHorizontal){
	EqCreate *pListView = new EqCreate();
	if(pListView)
	{
		pListView->setIsLockHorizontal(isHorizontal);
		pListView->setRect(mRect);
		pListView->init();
		//pListView->autorelease(); kevin modified
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}