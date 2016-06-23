#include "StoryChatUIPrintView.h"
#include "../../SceneStoryMediator.h"

StoryChatUIPrintView::StoryChatUIPrintView()
{

}

StoryChatUIPrintView::~StoryChatUIPrintView()
{

}

StoryChatUIPrintView * StoryChatUIPrintView::initUIPrintViewWithCCRect(CCRect rect,std::string strText,float time,float fontsize)
{
	StoryChatUIPrintView * pPrintView = new StoryChatUIPrintView();
	if (pPrintView && pPrintView->init())
	{
		pPrintView->setPrintRect(rect);
		pPrintView->setDeltaTime(time);
		pPrintView->setFontSize(fontsize);
		pPrintView->setPrintString(strText);
		pPrintView->loadItems();
		//pPrintView->run();
		return pPrintView;
	}
	CC_SAFE_DELETE(pPrintView);
	return 0;
}

void StoryChatUIPrintView::callBackFun()
{
	SceneStoryMediator * pStoryMediator = (SceneStoryMediator *)g_pFacade->retrieveMediator(AppFacade_SCENESTORY_PROXY_CHANGE);
	if (pStoryMediator && pStoryMediator->getStoryScene())
	{
		pStoryMediator->getStoryScene()->setIsTouchEnabled(true);
	}
}