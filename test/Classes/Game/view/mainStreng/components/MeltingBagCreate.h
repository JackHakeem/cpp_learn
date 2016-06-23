/**
 *  goods zuhelan
 */
#ifndef _MeltingBagCREATE_H_
#define _MeltingBagCREATE_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "utils/Singleton.h"
#include "MeltingUIListView.h"

using namespace cocos2d;

class GoodsInfo;
class MeltingBagGoods;

class MeltingBagCreate : public CCLayer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	MeltingBagCreate();
	~MeltingBagCreate();

public:

	bool init();
	LAYER_NODE_FUNC(MeltingBagCreate);
	
	// Listview adapter
	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemClickListener( LayerNode *itemCell, int position );
public:
	void createMeltingBag( vector<GoodsInfo*> goodsArr, int page );
	void buildBagGoods( vector<GoodsInfo*> goodsArr, int page );
	void updateGoods( GoodsInfo* info, int sitNum, int page, int type );
	MeltingBagGoods* getMeltingGoods( int index );
	void clearEquipment();

	MeltingUIListView* _meltingCreate;
	std::vector<LayerNode *> _listViewItemsList;
	std::map< int, MeltingBagGoods* > _meltingGoodsDic;
};

#endif