#include "MeltingBagCreate.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "MeltingBagGoods.h"
#include "utils/ScaleUtil.h"

MeltingBagCreate::MeltingBagCreate()
{
	_meltingCreate = 0;
}

MeltingBagCreate::~MeltingBagCreate()
{

}

bool MeltingBagCreate::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}

void MeltingBagCreate::clearEquipment()
{
	//remove list
	std::vector<LayerNode *>::iterator listItemIt;
	for(listItemIt = _listViewItemsList.begin();
		listItemIt != _listViewItemsList.end();
		++listItemIt)
	{
		LayerNode *tmp = (LayerNode *) *listItemIt;
		if(tmp && tmp->getParent())
		{
			tmp->removeAllChildrenWithCleanup(true);
			tmp->removeFromParentAndCleanup(true);
			tmp->release();
		}
	}
	_listViewItemsList.clear();
	if ( _meltingCreate )
	{
		_meltingCreate->setAdapter(this);
	}
	_meltingGoodsDic.clear();
}

/**
* create Melting Bag
* @param goodArr
* @param pageo
* 
*/		
void MeltingBagCreate::createMeltingBag( vector<GoodsInfo*> goodsArr, int page )
{
	//remove list
	clearEquipment();

	buildBagGoods( goodsArr, page );
}
		
/**
* buildBagGoods
* @param goodArr
* @param page
* 
*/		
void MeltingBagCreate::buildBagGoods( vector<GoodsInfo*> goodsArr, int page )
{
	MeltingBagGoods* meltingGoods;
	int length = goodsArr.size();

	int rowCnt = (length%3)==0?(length/3) : (length/3+1);
	for ( int i = 0; i < rowCnt; i++ )
	{
		LayerNode* pLayerNode = new LayerNode;
		pLayerNode->init();
		pLayerNode->setAnchorPoint(CCPointZero);

		pLayerNode->setContentSize( CCSizeMake( POSX(340), POSX(104) ) );
		pLayerNode->setvisibleSize( CCSizeMake( POSX(340), POSX(104) ) );

		pLayerNode->setPosition( ccp(0, POSX(323-110*i)) );
		//CCLayerColor* pLayer = CCLayerColor::layerWithColorWidthHeight( ccc4(0,0,255,100), POSX(346), POSX(104) );
		//pLayerNode->addChild(pLayer);

		_listViewItemsList.push_back( pLayerNode );
	}

	for ( uint i = 0; i < length; i++ )
	{
		GoodsInfo* goodsInfo = goodsArr[i];
		LayerNode* pLayerNode = _listViewItemsList[i/3];
				
		CCRect rect( POSX(18 + (i%3)*105), POSX(1), POSX(98), POSX(98) );
		meltingGoods = MeltingBagGoods::MeltingBagGoodsWithRect( rect );
		meltingGoods->initMeltingBagGoodsVo( goodsInfo, i );
		pLayerNode->addChild(meltingGoods);
		meltingGoods->release();
		meltingGoods->setTag(i%3);

		_meltingGoodsDic.insert( make_pair( i, meltingGoods ) );
	}

	//add new list
	CCSize listSize = CCSizeMake(POSX(340), POSX(440));
	CCRect listRect = CCRectMake(POSX(19),
		POSX(31),
		listSize.width,
		listSize.height );
	if(!_meltingCreate)
	{
		_meltingCreate = MeltingUIListView::listViewWithCCRect(listRect, false);
		_meltingCreate->setAnchorPoint(CCPointZero);
		_meltingCreate->setHeaderSize( POSX(16) );
		//_meltingCreate->setFooterSize( POSX(11) );
		_meltingCreate->setSpacingVertical(POSX(3));
		_meltingCreate->setWorldSpaceLeftBottomPoint(
			ccp(  this->getParent()->getParent()->getPosition().x + this->getParent()->getPosition().x
			+ this->getPosition().x + listRect.origin.x, 
			this->getParent()->getParent()->getPosition().y + this->getParent()->getPosition().y
			+ this->getPosition().y + listRect.origin.y  )
			);
		_meltingCreate->setOnItemActionListener(this);
		this->addChild(_meltingCreate, 100);
		_meltingCreate->release(); // Kenfly 20130125
	}
	_meltingCreate->setAdapter(this);
}
/**
* update Goods pos when drag or double-click 
* @param info
* @param sitNum
* @param page
* @param type
* 
*/		
void MeltingBagCreate::updateGoods( GoodsInfo* info, int sitNum, int page, int type )
{
	if( !info )	return;
	MeltingBagGoods* good = getMeltingGoods( sitNum + (page -1)*24 );
	if( !good )	return;

	if( type == 1)
	{ // +
		good->_myInfo->number++;
		if( good->_myInfo->type == 3 )
		{					
			good->setIcon( true );				
			good->setNum( good->_myInfo->number );
		}
		if( good->_myInfo->type == 2 )
		{
			good->setIcon(true);
		}
	}
	if(type == 2)
	{ // -
		good->_myInfo->number--; 
		if( good->_myInfo->type == 3 )
		{
			if( good->_myInfo->number == 0 )
			{
				good->setIcon(false);
			}	
			good->setNum( good->_myInfo->number );
		}
		if( good->_myInfo->type == 2 )
		{
			good->setIcon(false);
		}
	}
}	
		
MeltingBagGoods* MeltingBagCreate::getMeltingGoods( int index )
{
	std::map<int, MeltingBagGoods*>::iterator it = _meltingGoodsDic.find( index );
	if ( it != _meltingGoodsDic.end() )
	{
		return it->second;
	}
	return 0;
}

int MeltingBagCreate::getCount()
{
	return _listViewItemsList.size();
}

LayerNode * MeltingBagCreate::getView( int position )
{
	return _listViewItemsList[position];
}

void MeltingBagCreate::onItemClickListener( LayerNode *itemCell, int position )
{
	//StrengGoods* pStrengGoods = (StrengGoods*)itemCell;
	//if ( pStrengGoods )
	//{
	//	struct sdata
	//	{
	//		int UseType;
	//		StrengGoodsVo* sdataStrengGoodsVo;
	//	} s;
	//	s.UseType = 6;	// {UseType:6/* 6 Check prop when click */
	//	s.sdataStrengGoodsVo = pStrengGoods->_equpInfo;
	//	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
	//}
}
