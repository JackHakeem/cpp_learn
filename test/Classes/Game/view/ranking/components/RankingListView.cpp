#include "RankingListView.h"
#include "BaseType.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

#define TAG_CELL_HIGHLIGHT 1001

RankingListView::RankingListView()
{
	_pListView = 0;

	_pSelectedItem = 0;
}

RankingListView::~RankingListView()
{
	removeAllItems();
}

bool RankingListView::init()
{
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		this->setContentSize(CCSizeMake(POSX(480), POSX(400)));

		//Begin : add background
		CCUIBackground* pBg = new CCUIBackground();
		pBg->initWithSpriteFrame("ui2.png", ccp(POSX(8), POSX(22)), CCPointZero, this->getContentSize());
		pBg->setAnchorPoint(CCPointZero);
		pBg->setPosition(CCPointZero);
		this->addChild(pBg);
		pBg->release();
		//End

		_pListView = CCUIListView::listViewWithCCRect(CCRectMake(
			POSX(27),
			POSX(24),
			POSX(480),
			POSX(380)),
			false);
		_pListView->setAnchorPoint(CCPointZero);
		_pListView->setSpacingVertical(POSX(8));
		_pListView->setAdapter(this);
        _pListView->setIsRelativeAnchorPoint(true);
        _pListView->setOnItemActionListener(this);
		_pListView->m_pri = TLE::WindowLayer_PurchaseView;
		_pListView->setPosition(ccp(POSX(15), POSX(5)));
		this->addChild(_pListView);
        _pListView->release();

		return true;
	} while (0);

	return false;
}

int RankingListView::getCount()
{
	return _itemList.size();
}

LayerNode* RankingListView::getView(int position)
{
	return _itemList[position];
}

void RankingListView::onItemClickListener(LayerNode* item, int position)
{
	do 
	{
		CC_BREAK_IF(!item || item == _pSelectedItem);

		//remove hightlight
		if (_pSelectedItem)
		{
			CCNode* pSprite = _pSelectedItem->getChildByTag(TAG_CELL_HIGHLIGHT);
			if (pSprite)
				_pSelectedItem->removeChild(pSprite, true);
		}
		_pSelectedItem = item;

		//add hightlight

		CCUIBackground* pHightLightSp = new CCUIBackground();
		pHightLightSp->initWithSpriteFrame("train/gold_back.png", ccp(0, POSX(2)), CCPointZero, _pSelectedItem->getContentSize());
		_pSelectedItem->addChild(pHightLightSp, 0, TAG_CELL_HIGHLIGHT);
		pHightLightSp->release();
		dispatchEvent(RANK_ITEM_SELECTED, &position);
	} while (0);

}

void RankingListView::addItem(LayerNode* item)
{
	if (! item)
		return;

	item->retain();

	_itemList.push_back(item);
}

void RankingListView::refresh()
{
	//set Visiable rect
	const int parentNum = 4;
	int curNum = 0;
	CCPoint pos = CCPointZero;
	CCNode* pParent = _pListView;
	while(pParent && curNum != parentNum)
	{
		pos.x += pParent->getPosition().x;
		pos.y += pParent->getPosition().y;
		pParent = pParent->getParent();
		++curNum;
	}
	_pListView->setWorldSpaceLeftBottomPoint(pos);

	_pListView->setAdapter(this);
	CCMutableArray<LayerNode *>* pLayerItems = _pListView->getChilds();
	if (pLayerItems)
	{
		LayerNode* firstItem = pLayerItems->getObjectAtIndex(0);
		onItemClickListener(firstItem, 0);
	}
}

void RankingListView::removeAllItems()
{
	for (int i = 0; i < _itemList.size(); ++i)
		_itemList[i]->release();
	_itemList.clear();
}