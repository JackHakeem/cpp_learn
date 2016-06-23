#include "RenownPanel.h"
#include "RankingListView.h"
#include "FigureItemView.h"
#include "UIListView/CCUIListView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "utils/ColorUtil.h"
#include "BaseType.h"


RenownPanel::RenownPanel()
{
	_pListView = 0;
	_pFigureView = 0;
	_pMyRankLabel = 0;
	_pListData = 0;

	_curSelectedItem = -1;
}

RenownPanel::~RenownPanel()
{
	stopListener();
}

bool RenownPanel::init()
{
	do 
	{
		CC_BREAK_IF(! RankingPanel::init());
		this->setContentSize(CCSizeMake(POSX(890), POSX(500)));
		////Begin : add background
		//CCUIBackground* pBg = new CCUIBackground();
		//pBg->initWithSpriteFrame("ui2.png", ccp(POSX(8), POSX(22)), CCPointZero, this->getContentSize());
		//pBg->setAnchorPoint(CCPointZero);
		//pBg->setPosition(CCPointZero);
		//this->addChild(pBg);
		//pBg->release();
		//End
		ValuesUtil *pVU = ValuesUtil::Instance();
		CC_BREAK_IF(! pVU);
		
		//Begin : add left background
		CCUIBackground* pLeftBg = new CCUIBackground();
		pLeftBg->initWithSpriteFrame("ui2.png", ccp(POSX(8), POSX(22)), CCPointZero, CCSizeMake(POSX(500), POSX(480)));
		pLeftBg->setAnchorPoint(CCPointZero);
		pLeftBg->setPosition(ccp(POSX(10), POSX(10)));
		this->addChild(pLeftBg);
		pLeftBg->release();
		//End

		CCLabelTTF* pRankLabel = CCLabelTTF::labelWithString(pVU->getString("RK003").c_str(), CCSizeMake(POSX(200), POSX(26)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(26));
		CCLabelTTF* pRoleLabel = CCLabelTTF::labelWithString(pVU->getString("RK004").c_str(), CCSizeMake(POSX(200), POSX(26)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(26));
		CCLabelTTF* pFightLabel = CCLabelTTF::labelWithString(pVU->getString("RK006").c_str(), CCSizeMake(POSX(200), POSX(26)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(26));
		CC_BREAK_IF(! pRankLabel || ! pRoleLabel || ! pFightLabel);
		pRankLabel->setColor(ccORANGE);
		pRoleLabel->setColor(ccORANGE);
		pFightLabel->setColor(ccORANGE);
		pRankLabel->setPosition(ccp(POSX(100), POSX(470)));
		pRoleLabel->setPosition(ccp(POSX(250), POSX(470)));
		pFightLabel->setPosition(ccp(POSX(400), POSX(470)));
		this->addChild(pRankLabel);
		this->addChild(pRoleLabel);
		this->addChild(pFightLabel);

		//Begin : add list view
		_pListView = new RankingListView();
		CC_BREAK_IF(! _pListView || ! _pListView->init());
		_pListView->setAnchorPoint(CCPointZero);
		_pListView->setPosition(ccp(POSX(20), POSX(50)));
		this->addChild(_pListView);
		_pListView->release();
		//End

		//Begin : add figure view
		_pFigureView = new FigureItemView();
		CC_BREAK_IF(! _pFigureView || ! _pFigureView->init());
		_pFigureView->setAnchorPoint(CCPointZero);
		_pFigureView->setPosition(ccp(POSX(510), POSX(10)));
		this->addChild(_pFigureView);
		_pFigureView->release();

		startListener();
		return true;
	} while (0);

	return false;
}

void RenownPanel::updateRankList(const std::vector<RankItemVo>& array)
{
	do 
	{
		CC_BREAK_IF(! _pListView);
		_pListView->removeAllItems();

		_pListData = &array;

		ccColor3B color[4] = {
			ccc3(211, 215, 145),
			ccc3(94, 27, 99),
			ccc3(36, 95, 153),
			ccc3(5, 225, 3)
		};
		std::vector<RankItemVo>::const_iterator ix;
		for (ix = array.begin(); ix != array.end(); ++ix)
		{
			LayerNode* item = new LayerNode();
			item->setContentSize(CCSizeMake(POSX(450), POSX(40)));
			item->setvisibleSize(CCSizeMake(POSX(450), POSX(40)));

			int colorIndex = ix->rank;
			if (colorIndex > 3)
				colorIndex = 0;
			//add Background
			CCUIBackground* pBg = new CCUIBackground();
			pBg->initWithSpriteFrame("ui2.png", CCPointZero, CCPointZero, item->getContentSize());
			pBg->setAnchorPoint(CCPointZero);
			pBg->setPosition(CCPointZero);
			item->addChild(pBg);
			pBg->release();

			char msg[10] = "\0";
			sprintf(msg, "%d", ix->rank);
			CCLabelTTF* pRankLabel = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(100), POSX(40)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			if (pRankLabel)
			{
				pRankLabel->setPosition(ccp(POSX(40), POSX(20)));
				pRankLabel->setColor(color[colorIndex]);
				item->addChild(pRankLabel);
			}

			CCLabelTTF* pNameLabel = CCLabelTTF::labelWithString(ix->name.c_str(), CCSizeMake(POSX(200), POSX(40)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			if (pNameLabel)
			{
				pNameLabel->setPosition(ccp(POSX(190), POSX(20)));
				pNameLabel->setColor(color[colorIndex]);
				item->addChild(pNameLabel);
			}

			sprintf(msg, "%d", ix->grade);
			CCLabelTTF* pFightLabel = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(200), POSX(40)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			if (pFightLabel)
			{
				pFightLabel->setPosition(ccp(POSX(340), POSX(20)));
				pFightLabel->setColor(color[colorIndex]);
				item->addChild(pFightLabel);
			}

			_pListView->addItem(item);
			item->release();
		}
		_pListView->refresh();
	} while (0);
}

void RenownPanel::updateMyRank(int rank)
{
	do 
	{
		ValuesUtil *pVU = ValuesUtil::Instance();
		CC_BREAK_IF(! pVU);

		if (NULL == _pMyRankLabel)
		{
			_pMyRankLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(400), POSX(25)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			_pMyRankLabel->setPosition(ccp(POSX(250), POSX(32)));
			_pMyRankLabel->setColor(ccORANGE);
			this->addChild(_pMyRankLabel);
		}
		CC_BREAK_IF(! _pMyRankLabel);

		char str[50] = "\0";
		if (rank != 0 && _pListView && rank < _pListView->getCount())
			sprintf(str, pVU->getString("RK007").c_str(), rank);
		else
			sprintf(str, pVU->getString("RK008").c_str(), _pListView->getCount());

		_pMyRankLabel->setString(str);
	} while (0);
}

void RenownPanel::updateFigureData(const RankItemVo& data)
{
	_pFigureView->updateFigureData(data);
}

void RenownPanel::updateEquipments(const std::vector<EquipItemVo>& array)
{
	_pFigureView->updateEquipments(array);
}

void RenownPanel::startListener()
{
	if (_pListView)
		_pListView->addEventListener(RankingListView::RANK_ITEM_SELECTED, this, callfuncND_selector(RenownPanel::onListItemSelected));
}

void RenownPanel::stopListener()
{
    if (_pListView)
		_pListView->removeEventListener(RankingListView::RANK_ITEM_SELECTED, this, callfuncND_selector(RenownPanel::onListItemSelected));
}

void RenownPanel::onListItemSelected(cocos2d::CCNode* node, void* data)
{
	do 
	{
		CC_BREAK_IF(! data || !_pListData || ! _pFigureView);
		int pos = *((int*)data);
		CC_BREAK_IF(_curSelectedItem == pos);
		const std::vector<RankItemVo> array = (*_pListData);

		CC_BREAK_IF(pos > array.size());
		_pFigureView->updateFigureData(array[pos]);
	} while (0);

	dispatchEvent(RANK_ITEM_SELECTED, data);
}

