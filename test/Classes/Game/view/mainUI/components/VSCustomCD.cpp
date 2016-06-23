#include "VSCustomCD.h"
#include "manager/CDManage.h"
#include "view/notify/NotifyType.h"
#include "view/notify/NotifyManager.h"
#include "manager/ViewManager.h"
#include "PopContainer.h"
#include "view/levy/components/LevyView.h"
#include "view/arena/components/ArenaUI.h"

VSCustomCD::VSCustomCD( int type ) : CustomCD(type)
{
	setIsCDReady(true);
}

VSCustomCD::~VSCustomCD()
{

}

void VSCustomCD::CDCallback()
{
#if CC_NEW_VSCROLLUI_OPEN
	VScrollUI * pVSrollUI = ViewManager::getInstance()->_pVScrollUI;
	if (!pVSrollUI)
	{
		return;
	}

	int type = getType();
	bool isReady = CDManage::Instance()->getCDReady(type);
	int tag = ((CCNode *)this)->getTag() - VScrollUI::Tag_ItemCDText;
	if (tag <= 0)
	{
		return;
	}
	
	if (isReady)
	{
		pVSrollUI->_cd[tag] = 1;
	}
	else
	{
		pVSrollUI->_cd[tag] = 0;
	}
	
	//pVSrollUI->updateCDICon();

#else
	if (getIsCDReady())
	{
		return;
	}
	else
	{
		setIsCDReady(true);
	}

	ViewManager * pViewMgr = ViewManager::getInstance();
	int type = getType();
	int notifyType = -1;
	switch (type)
	{
	case CDManage::COLLECTION:
		{
			if (pViewMgr && pViewMgr->levyView
				&& pViewMgr->levyView->getisPop())
			{
				return;
			}

			notifyType = NotifyType::NType_Levy;
		}
		break;
	case CDManage::STRENGTHEN:
		{
			if (pViewMgr && pViewMgr->_mainStrengView
				&& pViewMgr->_mainStrengView->getisPop())
			{
				return;
			}

			notifyType = NotifyType::NType_Strength;
		}
		break;
	case CDManage::TRAINING:
		{
			if (pViewMgr && pViewMgr->trainView
				&& pViewMgr->trainView->getisPop())
			{
				return;
			}
			notifyType = NotifyType::NType_Train;
		}
		break;
	case CDManage::APPOINT:
		{
			if (pViewMgr && pViewMgr->_appointView
				&& pViewMgr->_appointView->getisPop())
			{
				return;
			}
			notifyType = NotifyType::NType_Appoint;
		}
		break;
	case CDManage::ARENA_CD:
		{
			if (pViewMgr && pViewMgr->arenaUI
				&& pViewMgr->arenaUI->getisPop())
			{
				return;
			}
			notifyType = NotifyType::NType_Arena;
		}
		break;
	default:
		break;
	}
	NotifyManager::Instance()->addNotification(notifyType);
#endif
	
}