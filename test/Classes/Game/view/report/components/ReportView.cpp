#include "ReportView.h"
#include "manager/PopEventName.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/LayerManager.h"
#include "KKLabelTTF.h"
#include "Confirm.h"
#include "manager/LangManager.h"

#define LEFT_MID_X (280.0f)
#define RIGHT_MID_X (680.0f)
#define REPORTVIEW_SIZE ccp( POSX(960.0f), POSX(640.0))
#define REPORTVIEW_POSITION ccp( POSX(960.0f / 2.0f), POSX(640.0f / 2.0f))

#define REPORT_BTN_COLOR ccc3(250, 210, 40)
#define CLOSE_BTN_POSITION ccp(POSX(900), POSX(600))
#define PAGE_UP_BTN_POSITION ccp(POSX(145), POSX(65))
#define PAGE_DOWN_BTN_POSITION ccp(POSX(820), POSX(80))

ReportView::ReportView()
{
    _curPage = 0;

	_container = 0;

	dispatcher = 0;

	_pLeftPage = _pRightPage = 0;

	canTurnPage = true;
}

bool ReportView::init()
{
    if (! LayerNode::init())
    {
        return false;
    }
	// initialization dispatcher
	dispatcher = GameDispatcher::getInstance();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->key = PopEventName::REPORT;
	this->setNeedBg(NeedBg_NO);
    this->setContentSize(winSize);
    this->setPopContentSize(this->getContentSize());

	this->setIsNeedClose(false);
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjectionDefault); //in order to play the page flip action.

	do
	{
		_container = new LayerNode();
		CC_BREAK_IF(! _container);

		this->addChild(_container, 0);
		_container->setAnchorPoint(CCPointZero);
		_container->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		_container->release();

		//Begin : init background
		CCSprite* pBg = CCSprite::spriteWithFile("assets/ui/report/report_background.png");
		CC_BREAK_IF(! pBg);
		_container->addChild(pBg, 0, TAG_BACKGROUND);
		pBg->setPosition(REPORTVIEW_POSITION);
	
		//End : init background 

		//Begin : add Left page node
		_pLeftPage = new CCNode();
		CC_BREAK_IF(! _pLeftPage);
		_container->addChild(_pLeftPage, 50);
		_pLeftPage->setPosition(ccp(POSX(LEFT_MID_X), POSX(0)));
		_pLeftPage->release();
		//End : add Left page node

		//Begin : add Right page node
		_pRightPage = new CCNode();
		CC_BREAK_IF(! _pRightPage);
		_container->addChild(_pRightPage, 50);
		_pRightPage->setPosition(ccp(POSX(RIGHT_MID_X), POSX(0)));
		_pRightPage->release();
		//End : add Right page node

		//Begin : init button
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CC_BREAK_IF(! pNormalSprite);
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CC_BREAK_IF(! pPressedSprite);
		CCMenuItemSprite* pCloseItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(ReportView::onClose)
			);

		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setPosition(CLOSE_BTN_POSITION);

		CCMenuItem* pPageUpItem = CCMenuItem::itemWithTarget(this, menu_selector(ReportView::onPageUp));
		CC_BREAK_IF(! pPageUpItem);
		pPageUpItem->setContentSize(CCSizeMake(POSX(150), POSX(150)));
		pPageUpItem->setPosition(PAGE_UP_BTN_POSITION);

		CCMenuItem* pPageDownItem = CCMenuItem::itemWithTarget(this, menu_selector(ReportView::onPageDown));
		CC_BREAK_IF(! pPageDownItem);
		pPageDownItem->setContentSize(CCSizeMake(POSX(150), POSX(150)));
		pPageDownItem->setPosition(PAGE_DOWN_BTN_POSITION);
		//End : init button

		//add normal menu
		CCMenu* pNormalMenu = CCMenu::menuWithItems(pCloseItem, pPageUpItem, pPageDownItem, 0);
		CC_BREAK_IF(! pNormalMenu);
		pNormalMenu->setAnchorPoint(CCPointZero);
		pNormalMenu->setPosition(CCPointZero);
		pNormalMenu->setTouchLayer(TLE::WindowLayer_Report - 1);
		_container->addChild(pNormalMenu, 10);
		
	} while(0);
   
    return true;
}

void ReportView::updateReportList(const std::vector<ReportHeadVo>& vec)
{
	do 
	{
		CC_BREAK_IF(vec.empty());

		for(int i = 0; i < datas.monsters.size(); ++i)
		{
			if (datas.monsters[i].mgId == vec[0].groupId)
			{
				datas.monsters[i].reportList = vec;
				if (i == _curPage * 2 || i == _curPage * 2 + 1)
					updateView();
				break;
			}
		}
	} while (0);
}

void ReportView::showPage(CCNode* pPage, int pageNum, bool bShowBtn)
{
	do 
	{
		CC_BREAK_IF(! pPage || datas.monsters.size() <= pageNum);

		pPage->removeAllChildrenWithCleanup(true);

		//Begin : show map data
		{
			CCSize csBt( POSX(400), POSX(70) );
			//LayerNode* pData = (LayerNode*)_container->getChildByTag(TAG_MAP_DATA);
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(datas.mapName.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(40) );
			pPage->addChild(pLabel);
			pLabel->setColor(ccc3(0, 208, 255));
			pLabel->setPosition(ccp(0, POSX(500)));
		}

		//End : show map data

		//Begin : show monster data
		{
			CCSize csBt( POSX(300), POSX(50) );
			std::string name = datas.monsters[pageNum].name;
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(name.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(30) );
			pPage->addChild(pLabel);
			pLabel->setColor(ccc3(255, 184, 0));
			pLabel->setPosition( ccp( 0, POSX(450)) );
		}
		//End : show monster data

		//Begin : show report list
		{
			ValuesUtil *pVU = ValuesUtil::Instance();
			CC_BREAK_IF(! pVU);
			const std::vector<ReportHeadVo>& vec = datas.monsters[pageNum].reportList;
			CC_BREAK_IF(vec.size() < 1);
			{
				CCSize cstxt(POSX(300), POSX(50));
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(pVU->getString("RPO003").c_str(), cstxt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
				if (txtLabel)
				{
					pPage->addChild(txtLabel);
					txtLabel->setColor(ccc3(0, 220, 0));
					txtLabel->setPosition(ccp(0, POSX(385)));
				}

				CCSize csname(POSX(200), POSX(50));
				CCLabelTTF* nameLabel = CCLabelTTF::labelWithString(vec[0].name.c_str(), csname, CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
				if(nameLabel)
				{
					pPage->addChild(nameLabel);
					nameLabel->setColor(ccc3(255, 255, 255));
					nameLabel->setPosition(ccp(-POSX(50), POSX(350)));
				}

				CCSize cslev(POSX(100), POSX(50));
				char tmplev[20];
				sprintf(tmplev, "%d", vec[0].lev);
				CCLabelTTF* levLabel = CCLabelTTF::labelWithString(tmplev, cslev, CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
				if (levLabel)
				{
					pPage->addChild(levLabel, 0);
					levLabel->setColor(ccc3(255, 255, 255));
					levLabel->setPosition(ccp(+POSX(100), POSX(350)));
				}

				//add report button 
				CCLabelTTF* pLabel = CCLabelTTF::labelWithString(pVU->getString("RPO006").c_str(), g_sSimHeiFont, POSX(30));
				if(pLabel)
				{
					CCMenuItemLabel* pReportItem = CCMenuItemLabel::itemWithLabel(pLabel, this, menu_selector(ReportView::onReportFirst));
					if (pReportItem)
					{
						pReportItem->setColor(REPORT_BTN_COLOR);
						pReportItem->setPosition(ccp(POSX(0), POSX(300)));
						pReportItem->setTag(pageNum);
						CCMenu* pMenu = CCMenu::menuWithItems(pReportItem, NULL);
						pMenu->setTouchLayer(TLE::WindowLayer_Report - 1);
						pPage->addChild(pMenu, 5);
						pMenu->setAnchorPoint(CCPointZero);
						pMenu->setPosition(CCPointZero);
						
					}
				}
			}

			CC_BREAK_IF(vec.size() < 3);
			{
				CCSize cstxt(POSX(400), POSX(50));
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(pVU->getString("RPO005").c_str(), cstxt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
				if (txtLabel)
				{
					pPage->addChild(txtLabel, 0);
					txtLabel->setColor(ccc3(0, 220, 0));
					txtLabel->setPosition(ccp(POSX(0), POSX(250)));
				}

				CCSize csname(POSX(200), POSX(50));
				CCLabelTTF* nameLabel = CCLabelTTF::labelWithString(vec[2].name.c_str(), csname, CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
				if (nameLabel)
				{
					pPage->addChild(nameLabel, 0);
					nameLabel->setColor(ccc3(255, 255, 255));
					nameLabel->setPosition(ccp(POSX(0) - POSX(50), POSX(220)));
				}

				CCSize cslev(POSX(100), POSX(50));
				char tmplev[20];
				sprintf(tmplev, "%d", vec[2].lev);
				CCLabelTTF* levLabel = CCLabelTTF::labelWithString(tmplev, cslev, CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
				if (levLabel)
				{
					pPage->addChild(levLabel, 0);
					levLabel->setColor(ccc3(255, 255, 255));
					levLabel->setPosition(ccp(POSX(0) + POSX(100), POSX(220)));
				}

				CCLabelTTF* pLabel = CCLabelTTF::labelWithString(pVU->getString("RPO006").c_str(), g_sSimHeiFont, POSX(30));
				if(pLabel)
				{
					CCMenuItemLabel* pReportItem = CCMenuItemLabel::itemWithLabel(pLabel, this, menu_selector(ReportView::onReportThird));
					if (pReportItem)
					{
						pReportItem->setColor(REPORT_BTN_COLOR);
						pReportItem->setPosition(ccp(POSX(0), POSX(170)));
						pReportItem->setTag(pageNum);
						CCMenu* pMenu = CCMenu::menuWithItems(pReportItem, NULL);
						pMenu->setTouchLayer(TLE::WindowLayer_Report - 1);
						pPage->addChild(pMenu, 500);
						pMenu->setPosition(CCPointZero);
						pMenu->setAnchorPoint(CCPointZero);
					}
				}
			}
		}
		//End : show report list

		//Begin : show page button
		CC_BREAK_IF(! bShowBtn);
		if (pageNum % 2 == 0 && pageNum - 1 >= 0)
		{
			CCSprite* pSprite = CCSprite::spriteWithFile("assets/ui/report/click_page_up.png");
			if (pSprite)
			{
				pPage->addChild(pSprite);
				pSprite->setPosition(ccp(PAGE_UP_BTN_POSITION.x - POSX(LEFT_MID_X), PAGE_UP_BTN_POSITION.y));
			}
		}
		if (pageNum % 2 == 1 && pageNum + 1 < datas.monsters.size())
		{
			CCSprite* pSprite = CCSprite::spriteWithFile("assets/ui/report/click_page_up.png");
			if (pSprite != NULL)
			{
				pSprite->setFlipX(true);
				pPage->addChild(pSprite);
				pSprite->setPosition(ccp(PAGE_DOWN_BTN_POSITION.x - POSX(RIGHT_MID_X), PAGE_DOWN_BTN_POSITION.y));
			}
		}
		//End : show page button
	} while (0);
}

void ReportView::updateView()
{
	int lpage = _curPage * 2;
	int rpage = _curPage * 2 + 1;

	if (datas.monsters.size() > lpage)
	{
		showPage(_pLeftPage, lpage, true);
		if (datas.monsters[lpage].reportList.empty())
		{
			int mgId = datas.monsters[lpage].mgId;
			dispatcher->dispatchEvent(GameDispatcher::APPLY_REPORT_LIST, (char*)&mgId);
		}
	}
	if (datas.monsters.size() > rpage)
	{
		showPage(_pRightPage, rpage, true);
		if (datas.monsters[rpage].reportList.empty())
		{
			int mgId = datas.monsters[rpage].mgId;
			dispatcher->dispatchEvent(GameDispatcher::APPLY_REPORT_LIST, (char*)&mgId);
		}
	}
	//get next page info
	lpage = (_curPage + 1) * 2;
	rpage = (_curPage + 1) * 2 + 1;

	if (datas.monsters.size() > lpage)
	{
		if (datas.monsters[lpage].reportList.empty())
		{
			int mgId = datas.monsters[lpage].mgId;
			dispatcher->dispatchEvent(GameDispatcher::APPLY_REPORT_LIST, (char*)&mgId);
		}
	}
	if (datas.monsters.size() > rpage)
	{
		if (datas.monsters[rpage].reportList.empty())
		{
			int mgId = datas.monsters[rpage].mgId;
			dispatcher->dispatchEvent(GameDispatcher::APPLY_REPORT_LIST, (char*)&mgId);
		}
	}
}

void ReportView::onReportFirst(CCObject* pSender)
{
	do 
	{
		CC_BREAK_IF(! pSender);
		int tag = ((CCNode*)pSender)->getTag();
		CC_BREAK_IF(datas.monsters.size() <= tag || datas.monsters[tag].reportList.size() < 1);

		ReportHeadVo vo = datas.monsters[tag].reportList[0];

		CC_BREAK_IF(! dispatcher);
		dispatcher->dispatchEvent(GameDispatcher::SELECT_REPORT, (char*)&vo);
	} while (0);
}

void ReportView::onReportThird(CCObject* pSender)
{
	do 
	{
		CC_BREAK_IF(! pSender);
		int tag = ((CCNode*)pSender)->getTag();
		CC_BREAK_IF(datas.monsters.size() <= tag || datas.monsters[tag].reportList.size() < 3);

		ReportHeadVo vo = datas.monsters[tag].reportList[2];

		CC_BREAK_IF(! dispatcher);
		dispatcher->dispatchEvent(GameDispatcher::SELECT_REPORT, (char*)&vo);
	} while (0);
}

void ReportView::onPageUp(CCObject* pSender)
{
	do 
	{
		CC_BREAK_IF(! canTurnPage);
		CC_BREAK_IF(_curPage - 1 < 0);
		int pageNum = _curPage * 2;
		_curPage--;

		CCSprite* pBg = (CCSprite*)_container->getChildByTag(TAG_BACKGROUND);
		CC_BREAK_IF(! pBg);
		CCTexture2D* texture = pBg->getTexture();
		CC_BREAK_IF(! texture);
		CCSprite* pSprite = CCSprite::spriteWithTexture(texture, CCRectMake(POSX(82), POSX(20), POSX(406), POSX(604)));
		CC_BREAK_IF(! pSprite);
		_container->addChild(pSprite, 50, pageNum);
		pSprite->setPosition(ccp(POSX(488), POSX(320)));
		pSprite->setAnchorPoint(ccp(1.0f, 0.5f));

		CCNode* pPage = new CCNode();
		showPage(pPage, pageNum);
		pPage->setPosition(ccp(POSX(LEFT_MID_X - 82), POSX(-20)));
		pSprite->addChild(pPage, 10);
		pPage->release();

		showPage(_pLeftPage, _curPage * 2, true);

		CCActionInterval* pOrbitAction = CCOrbitCamera::actionWithDuration(0.5f, 0.1f, 0, -2.0f, -88.0f, 0, 0);
		CCAction* pAction = CCSequence::actions(
			pOrbitAction,
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(ReportView::pageUpCallback)),
			NULL
			);
		pSprite->runAction(pAction);
		canTurnPage = false;
	} while (0);

	
}

void ReportView::onPageDown(CCObject* pSender)
{
	do 
	{
		CC_BREAK_IF(! canTurnPage);
		CC_BREAK_IF((_curPage + 1) * 2 >= datas.monsters.size());
		int pageNum = _curPage* 2 + 1;
		_curPage++;

		CCSprite* pBg = (CCSprite*)_container->getChildByTag(TAG_BACKGROUND);
		CC_BREAK_IF(! pBg);
		CCTexture2D* texture = pBg->getTexture();
		CC_BREAK_IF(! texture);
		CCSprite* pSprite = CCSprite::spriteWithTexture(texture, CCRectMake(POSX(488), POSX(20), POSX(406), POSX(604)));
		CC_BREAK_IF(! pSprite);
		pSprite->setPosition(ccp(POSX(488), POSX(320)));
		_container->addChild(pSprite, 50, pageNum);
		pSprite->setAnchorPoint(ccp(0.0f, 0.5f));

		CCNode* pPage = new CCNode();
		showPage(pPage, pageNum);
		pSprite->addChild(pPage, 10);
		pPage->setPosition(ccp(POSX(RIGHT_MID_X - 488), POSX(-20)));
		pPage->release();

		if (_curPage * 2 + 1 < datas.monsters.size())
			showPage(_pRightPage, _curPage * 2 + 1, true);
		else
			_pRightPage->removeAllChildrenWithCleanup(true);

		CCActionInterval* pOrbitAction = CCOrbitCamera::actionWithDuration(0.5f, 0.1f, 0, 2.0f, 88.0f, 0, 0);
		CCAction* pAction = CCSequence::actions(
			pOrbitAction,
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(ReportView::pagetDownCallback)),
			NULL
			);
		pSprite->runAction(pAction);
		canTurnPage = false;

		//get next page info
		int lpage = (_curPage + 1) * 2;
		int rpage = (_curPage + 1) * 2 + 1;

		if (datas.monsters.size() > lpage)
		{
			if (datas.monsters[lpage].reportList.empty())
			{
				int mgId = datas.monsters[lpage].mgId;
				dispatcher->dispatchEvent(GameDispatcher::APPLY_REPORT_LIST, (char*)&mgId);
			}
		}
		if (datas.monsters.size() > rpage)
		{
			if (datas.monsters[rpage].reportList.empty())
			{
				int mgId = datas.monsters[rpage].mgId;
				dispatcher->dispatchEvent(GameDispatcher::APPLY_REPORT_LIST, (char*)&mgId);
			}
		}
	} while (0);
}

void ReportView::pageUpCallback(CCNode* pNode)
{
	canTurnPage = true;
	do 
	{
		CC_BREAK_IF(! pNode);
		int pageNum = pNode->getTag() - 1;
		pNode->removeFromParentAndCleanup(true);

		CCSprite* pBg = (CCSprite*)_container->getChildByTag(TAG_BACKGROUND);
		CC_BREAK_IF(! pBg);
		CCTexture2D* texture = pBg->getTexture();
		CC_BREAK_IF(! texture);

		CCSprite* pSprite = CCSprite::spriteWithTexture(texture, CCRectMake(POSX(488), POSX(20), POSX(406), POSX(604)));
		CC_BREAK_IF(! pSprite);
		CCNode* pPage = new CCNode();
		showPage(pPage, pageNum);
		pPage->setPosition(ccp(POSX(RIGHT_MID_X - 488), POSX(-20)));

		_container->addChild(pSprite, 50, pageNum);
		pSprite->setAnchorPoint(ccp(0.0f, 0.5f));
		pSprite->setPosition(ccp(POSX(488), POSX(320)));
		pSprite->addChild(pPage);
		pPage->release();

		CCActionInterval* pOrbitAction = CCOrbitCamera::actionWithDuration(0.5f, 0.1f, 0, 90, -88, 0, 0);
		CCActionInterval* pFadeout = CCFadeOut::actionWithDuration(0.2f);
		CCAction* pAction = CCSequence::actions(
			pOrbitAction,
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(ReportView::pageUpCompleteHandle)),
			NULL
			);
		
		pSprite->runAction(pAction);
	} while (0);
}

void ReportView::pagetDownCallback(CCNode* pNode)
{
	canTurnPage = true;
	do 
	{
		CC_BREAK_IF(! pNode);
		int pageNum = pNode->getTag() + 1;
		pNode->removeFromParentAndCleanup(true);

		CCSprite* pBg = (CCSprite*)_container->getChildByTag(TAG_BACKGROUND);
		CC_BREAK_IF(! pBg);
		CCTexture2D* texture = pBg->getTexture();
		CC_BREAK_IF(! texture);

		CCSprite* pSprite = CCSprite::spriteWithTexture(texture, CCRectMake(POSX(82), POSX(20), POSX(406), POSX(604)));
		CC_BREAK_IF(! pSprite);
		CCNode* pPage = new CCNode();
		showPage(pPage, pageNum);
		pPage->setPosition(ccp(POSX(LEFT_MID_X - 82), POSX(-20)));

		_container->addChild(pSprite, 50, pageNum);
		pSprite->setAnchorPoint(ccp(1.0f, 0.5f));
		pSprite->setPosition(ccp(POSX(488), POSX(320)));
		pSprite->addChild(pPage);
		pPage->release();

		CCActionInterval* pOrbitAction = CCOrbitCamera::actionWithDuration(0.5f, 0.1f, 0, -90, 88, 0, 0);
		CCActionInterval* pFadeout = CCFadeOut::actionWithDuration(0.2f);
		CCAction* pAction = CCSequence::actions(
			pOrbitAction,
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(ReportView::pageDownCompleteHandel)),
			NULL
			);

		pSprite->runAction(pAction);
	} while (0);
}

void ReportView::pageUpCompleteHandle(CCNode* pNode)
{
	do 
	{
		CC_BREAK_IF(! pNode);
		int pageNum = pNode->getTag();
		pNode->removeFromParentAndCleanup(true);
		showPage(_pRightPage, pageNum, true);
	} while (0);
}

void ReportView::pageDownCompleteHandel(CCNode* pNode)
{
	do 
	{
		CC_BREAK_IF(! pNode);
		int pageNum = pNode->getTag();
		pNode->removeFromParentAndCleanup(true);
		showPage(_pLeftPage,  pageNum, true);
	} while (0);
}

void ReportView::clickCloseHandler(CCObject* pSender)
{
	onClose(0);
}

void ReportView::onClose(CCObject* pSender)
{
	this->setisPop(false);
	CCDirector::sharedDirector()->setProjection(CCDirectorProjection2D);
}
