#include "RoleListView.h"
#include "model/player/RoleManage.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "TrainRoleItem.h"
#include "manager/ViewManager.h"
#include "../TrainViewMediator.h"


RoleListView::RoleListView(const CCRect& mRect) : _rect(mRect)
{
	setOnItemActionListener(this);
}

RoleListView* RoleListView::listViewWithCCRect( const CCRect& mRect, bool isHorizontal )
{
	RoleListView *pListView = new RoleListView(mRect);
	if(pListView)
	{
		pListView->setIsLockHorizontal(isHorizontal);
		pListView->setRect(mRect);
		pListView->init();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

int RoleListView::getCount()
{
	return RoleManage::Instance()->_mercListEx.size() - 1;
}

LayerNode * RoleListView::getView( int position )
{
	setOnItemActionListener(this);

	int id = 0;
	int acctId = 0;
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* mercMap = RoleManage::Instance()->mercListEx();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = mercMap->begin();
	int count = 0;
	for(iter ; iter != mercMap->end() ; iter++)
	{
		if (iter->second.playerBaseInfo.isRole)
		{
			continue; 
		}
		if (count == position)
		{
			id = iter->second.playerBaseInfo.cloth;
			acctId = iter->first.id;
			break;
		}
		++count;		
	}
	TrainRoleItem * pItem = new TrainRoleItem(id , acctId);

	CCSize size = pItem->getContentSize();

	LayerNode * pLayer = new LayerNode();
	pLayer->init();
	pLayer->setContentSize(size);
	pLayer->setvisibleSize(size);
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setTag(position);
	pLayer->addChild(pItem, 0 , Tag_ListItem);
	pItem->release();
	

	return pLayer;
}

void RoleListView::resetView()
{
	CCMutableArray<LayerNode *>* listChilds = this->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator iter;
	for(iter = listChilds->begin(); iter != listChilds->end(); iter++)
	{
		LayerNode *pChildLayer = (LayerNode *) *iter;
		if(!pChildLayer)
			continue;

		if ( pChildLayer->getParent() )
		{
			pChildLayer->removeFromParentAndCleanup(true);
		}

		pChildLayer->release();
	}

	setAdapter(this);
}

void RoleListView::showHighLight(LayerNode *itemCell)
{
	if (!itemCell)
	{
		return;
	}

	CCLayerColor * pContentLayer = getContentLayer();
	if (pContentLayer)
	{
		if (!pContentLayer->getChildByTag(Tag_HighLight))
		{
			CCUIBackground *pHighLightSprite = new CCUIBackground();
			pHighLightSprite->initWithSpriteFrame( "train/gold_back.png",	ccp(POSX(0) , POSX(0)), CCPointZero, itemCell->getContentSize() );
			pContentLayer->addChild( pHighLightSprite, 5, Tag_HighLight );
			pHighLightSprite->release();	
		}
		pContentLayer->getChildByTag(Tag_HighLight)->setPosition(itemCell->getPosition());
	}
}

void RoleListView::showIsTrained(int id)
{
	CCMutableArray<LayerNode *>* listChilds = this->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator iter;
	for(iter = listChilds->begin(); iter != listChilds->end(); iter++)
	{
		LayerNode *pChildLayer = (LayerNode *) *iter;
		if(!pChildLayer)
			continue;
		TrainRoleItem * pItem = (TrainRoleItem *)pChildLayer->getChildByTag(Tag_ListItem);
		if (pItem->getAcountId() == id)
		{
			pItem->showIsTrained(id);
			break;
		}
	}
}

void RoleListView::onItemClickListener( LayerNode *itemCell, int position )
{
	if (!itemCell)
	{
		return;
	}

	TrainRoleItem * pItem = (TrainRoleItem *)itemCell->getChildByTag(Tag_ListItem);
	if (pItem && ViewManager::getInstance()->trainView)
	{
		ViewManager::getInstance()->trainView->setMercId(pItem->getAcountId());
		// update 
		TrainViewMediator* pMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
		pMeditor->selectMercHandler(pItem->getAcountId());
	}

	// light
	showHighLight(itemCell);
}

void RoleListView::onItemTouchListener( LayerNode *itemCell, int position )
{

}

void RoleListView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{

}
