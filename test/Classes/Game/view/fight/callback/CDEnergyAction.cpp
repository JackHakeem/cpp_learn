#include "CDEnergyAction.h"
#include "manager/LangManager.h"
#include "manager/CDManage.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "view/mainUI/MainUIMediator.h"
#include "control/AppFacade.h"
#include "manager/CDManage.h"

void CDEnergyAction::doAction()
{
	int cdType = CDManage::Instance()->getLockBytype(CDManage::FIGHT);
	if(cdType == 1){
		//LangManager::msgShow("SCE038");
		Confirm* pConfirm = new Confirm();
		std::string stdstr = LangManager::getText( "SCE038");
		std::string strConfirm = LangManager::getText( "SCE039");
		pConfirm->initWithParam(stdstr.c_str(), this, menu_selector(CDEnergyAction::okFunction), menu_selector(CDEnergyAction::cancelFunction), "");

		if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
		{
			LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
		}

		LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);

		pConfirm->release();

	}

}

void CDEnergyAction::delAction( IAction* action )
{
}

void CDEnergyAction::okFunction( CCObject *pSender )
{
	CCNode* pConfirm = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
    
}

void CDEnergyAction::cancelFunction( CCObject *pSender )
{
	CCNode* pConfirm = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}
