#include "DungeonGUAMonsterInfoLayer.h"
//#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "DungeonGUAMonsterInfoItem.h"

DungeonGUAMonsterInfoLayer::DungeonGUAMonsterInfoLayer()
{
	_pListView = 0;
}

DungeonGUAMonsterInfoLayer::~DungeonGUAMonsterInfoLayer()
{
	_scrollPaneContent.clear();
}

bool DungeonGUAMonsterInfoLayer::init(std::vector<std::string> values, CCPoint offset)
{
	if (!LayerNode::init())
		return false;

	//list
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(520.0f), POSX(640-454), POSX(910-500), POSX(454-310)), false);
	_pListView->setIsRelativeAnchorPoint(true);
    _pListView->setAnchorPoint(ccp(0,0));
	_pListView->setSpacingVertical(0);

	_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pListView->getPosition(), ccp(offset.x, offset.y)));
	_pListView->setOnItemActionListener(this);
	this->addChild(_pListView, 0, 0);
	_pListView->release();

	//create 
	for (int i = 0; i < values.size(); i++)
	{
		DungeonGUAMonsterInfoItem* newitem = new DungeonGUAMonsterInfoItem();
		newitem->init(values[i], i+1);
		_scrollPaneContent.push_back(newitem);
	}

	updateRes();

	for (int i = 0; i < _scrollPaneContent.size(); i++)
	{
		_scrollPaneContent[i]->release();
	}

	return true;
}


void DungeonGUAMonsterInfoLayer::updateRes()
{
	_pListView->setAdapter(this);
}

int DungeonGUAMonsterInfoLayer::getCount()
{
	return _scrollPaneContent.size();
}

LayerNode * DungeonGUAMonsterInfoLayer::getView( int position )
{
	if (position >= 0 && position < _scrollPaneContent.size())
		return (LayerNode*)_scrollPaneContent[position];
	else
		return 0;
}