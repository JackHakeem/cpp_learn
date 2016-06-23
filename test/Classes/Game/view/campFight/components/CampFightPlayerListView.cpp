#include "CampFightPlayerListView.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "events/GameDispatcher.h"

#define TAG_CELL_HIGHLIGHT 1001

CCFPlayerListView::CCFPlayerListView()
{
	m_lsItems.clear();
	m_pListView = NULL;
	m_pSelectedItem = NULL;
	m_camp = CAMP_ICE;
}
CCFPlayerListView::~CCFPlayerListView()
{

}
bool CCFPlayerListView::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		/*
		CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(
			ccc4(0, 0, 255, 255), POSX(190), POSX(350));
		pTestLayer->setPosition(ccp(POSX(0),POSX(72)));
		pTestLayer->setAnchorPoint(CCPointZero);
		pTestLayer->setIsRelativeAnchorPoint(true);
		this->addChild(pTestLayer);
		*/
		this->setContentSize( CCSizeMake(POSX(190), POSX(350)) );
		//new add
		//this->setPopContentSize(this->getContentSize());
		this->setPosition(CCPointZero);
		///
		if (!m_pListView)
		{
			m_pListView = CCUIListView::listViewWithCCRect(CCRectMake(
				POSX(1),
				POSX(1),
				POSX(190),
				POSX(350)),
				false);
			m_pListView->setAnchorPoint(CCPointZero);
			m_pListView->setSpacingVertical(POSX(8));
			m_pListView->setAdapter(this);
			m_pListView->setIsRelativeAnchorPoint(true);
			m_pListView->setOnItemActionListener(this);
			m_pListView->m_pri = TLE::WindowLayer_PurchaseView;
			m_pListView->setPosition(CCPointZero);//ccp(POSX(10),POSX(72))
			if (m_camp == CAMP_ICE)
			{
				m_pListView->setWorldSpaceLeftBottomPoint(ccp(POSX(144), POSX(130)));
			}
			else
			{
				m_pListView->setWorldSpaceLeftBottomPoint(ccp(POSX(627), POSX(130)));
			}
			m_pListView->setHeaderSize(POSX(13));
			this->addChild(m_pListView);
			
			/*if (m_pListView->getParent()->getParent())
			{
				m_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(m_pListView->getParent()->getParent()->getPosition(),
					ccpAdd(m_pListView->getPosition(), m_pListView->getParent()->getPosition())
					));
			}*/
			m_pListView->release();
		}
		return true;
	} while (0);
	return false;
}
int CCFPlayerListView::getCount()
{
	return m_lsItems.size();
}
LayerNode* CCFPlayerListView::getView(int position)
{
	return m_lsItems[position];
}
void CCFPlayerListView::onItemClickListener(LayerNode* item, int position)
{
	do 
	{
		CC_BREAK_IF(!item || item == m_pSelectedItem);

		//remove hightlight
		if (m_pSelectedItem)
		{
			CCNode* pSprite = m_pSelectedItem->getChildByTag(TAG_CELL_HIGHLIGHT);
			if (pSprite)
				m_pSelectedItem->removeChild(pSprite, true);
		}
		m_pSelectedItem = item;

		//add hightlight

		CCUIBackground* pHightLightSp = new CCUIBackground();
		pHightLightSp->initWithSpriteFrame("train/gold_back.png", ccp(0, POSX(2)), 
			CCPointZero, m_pSelectedItem->getContentSize());
		m_pSelectedItem->addChild(pHightLightSp, 0, TAG_CELL_HIGHLIGHT);
		pHightLightSp->release();
		dispatchEvent(GameDispatcher::MSG_SELECT_CAMPFIGHT_PLAYER_ITEM, &position);
	} while (0);
}
void CCFPlayerListView::AddItem(LayerNode* item)
{
	if (! item)
		return;

	//item->retain();

	m_lsItems.push_back(item);
}
void CCFPlayerListView::Refresh()
{
	//set Visiable rect
	/*const int parentNum = 4;
	int curNum = 0;
	CCPoint pos = CCPointZero;
	CCNode* pParent = m_pListView;
	while(pParent && curNum != parentNum)
	{
	pos.x += pParent->getPosition().x;
	pos.y += pParent->getPosition().y;
	pParent = pParent->getParent();
	++curNum;
	}
	m_pListView->setWorldSpaceLeftBottomPoint(pos);
	*/
	m_pListView->setAdapter(this);
	/*CCMutableArray<LayerNode *>* pLayerItems = m_pListView->getChilds();
	if (pLayerItems)
	{
	LayerNode* firstItem = pLayerItems->getObjectAtIndex(0);
	onItemClickListener(firstItem, 0);
	}*/
}
void CCFPlayerListView::RemoveAllItems()
{
	for (int i = 0; i < m_lsItems.size(); ++i)
		m_lsItems[i]->release();
	m_lsItems.clear();
}