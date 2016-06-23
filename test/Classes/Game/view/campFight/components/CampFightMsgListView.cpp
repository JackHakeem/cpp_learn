#include "CampFightMsgListView.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "MsgItem.h"

CCFMsgListView::CCFMsgListView()
{
	m_lsItems.clear();
	m_pListView = NULL;
}
CCFMsgListView::~CCFMsgListView()
{
	ClearCacheItems();
}
bool CCFMsgListView::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		//it is container iself 
		CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(
			ccc4(0, 255, 0, 255), POSX(279), POSX(168));
		pTestLayer->setPosition(ccp(POSX(0),POSX(0)));
		pTestLayer->setAnchorPoint(CCPointZero);
		pTestLayer->setIsRelativeAnchorPoint(true);
		this->addChild(pTestLayer);

		this->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER_TOP));
		this->setAnchorPoint(CCPointZero);

		if (!m_pListView)
		{
			m_pListView = KKCCUIListView::listViewWithCCRect(CCRectMake(POSX(5), POSX(5), POSX(270), 
				POSX(160)), 30);
			m_pListView->setIsRelativeAnchorPoint(true);
			m_pListView->m_pri = TLE::WindowLayer_campFight;
			m_pListView->setAnchorPoint(ccp(0,0));
			m_pListView->setSpacingVertical(0);
			m_pListView->setWorldSpaceLeftBottomPoint(ccp(POSX(347), POSX(256)));
			//m_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(m_pListView->getPosition(), this->getPosition()));
			m_pListView->setOnItemActionListener(this);
			this->addChild(m_pListView, 1);
			m_pListView->release();
		}
		AddRecords("XXXXXX");
		return true;
	} while (0);
	return false;
}
void CCFMsgListView::AddRecords(std::string str)
{
	CMsgItem* pmsgItem = new CMsgItem();
	char msg[1024];
	sprintf(msg,"%d",str.c_str());
	if (!pmsgItem || !pmsgItem->init(msg,ccc3(255, 215, 0)))
	{
		return;
	}
	if (m_pListView && m_pListView->add(this))
		ClearCacheItems();//把内容成功全部加进去，再CLEAR
}
void CCFMsgListView::ClearCacheItems()
{
	for (int i = 0; i < m_lsItems.size(); i++)
	{
		if (!m_lsItems[i])
		{
			continue;
		}
		m_lsItems[i]->release();
	}
	m_lsItems.clear();	
}