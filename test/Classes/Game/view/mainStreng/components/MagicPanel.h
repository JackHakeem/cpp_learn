#ifndef _MAGICPANEL_H_
#define _MAGICPANEL_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "StrengFigureCreate.h"
#include "view/mainStreng/components/StrengGoods.h"
#include "UIListView/CCUIListView.h"
#include "CCUIBackground.h"
using namespace cocos2d;

class GoodsInfo;
class GoodsBasic;
class GoodsDynamic;
class EquipmentVo;
class FigureItem;

class MagicPanel : public CCLayer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:             
	MagicPanel();
	~MagicPanel();

public:
	bool init();
	LAYER_NODE_FUNC(MagicPanel);

	void openMagic();
	bool creatRoleEquipmentList( int id );
	vector<GoodsInfo*> sortedArr( EquipmentVo* roleEquipment );
	void creatBagEquipmentList( std::map<int32, GoodsInfo*>* bagDictionary );
	void viewEquipmentInfo( int id, int goodID );
	void viewEquipmentDynamicInfo( GoodsBasic* goodsBasic, GoodsDynamic* goodsDynamic );
	void roleVipLev( int lev );
	void crystalLev( int lev );
	FigureItem* figureItem();
	void clear();
	void updateSparInfo( int num );
	void figureSelectHandler( FigureItem* item );
	void bagClickHandler( CCObject* pSender );
	void gridClickHandler( CCObject* pSender );
	void onClickHandler( CCObject* pSender );
	void updateTip( uint id );

	void directClickHandler( CCObject* pObj );
	void directRightClickHandler( CCObject* pObj );

	// Listview adapter
	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemClickListener( LayerNode *itemCell, int position );
	StrengGoods* getStrengGoods( int id );
	void clearEquipment();
	void lockBtn(ccTime dt);
public:
	CCUIBackground* _bgEquip;
	CCLabelTTF* _sparInfo;		//魔晶石信息
	//private var _explain:MovieClip;		//魔化说明
	CCLabelTTF* _equipName;
	CCMenuItemSprite* _MagicItem;
	CCMenu* _btnMagic;	//魔化按钮
	CCSprite* _fangkuang;
	CCSprite* _pic;

	CCSprite*_gridSelect;
	
	//private var _ef1:MovieClip;			//动画1
	//private var _ef2:MovieClip;			//动画2

	int _roleVipLev;		//角色vip等级
	int _magicLev;			//魔之水晶等级
	CCLabelTTF* _comCheckBox;
	CCLabelTTF* _costText;
	CCLabelTTF* _attribute1;		
	CCLabelTTF* _attribute2;		
	CCLabelTTF* _attribute3;
	StrengGoods* _curMagicGoods;
	int _curId;
	int _curGoodsId;
	StrengFigureCreate* _figureCreate;

	CCUIListView* _magicCreate;
	std::vector<LayerNode *> _listViewItemsList;
	std::map<int, StrengGoods*> _goodsDic;

	FigureItem* _item;
	int _sparNum;

	bool m_bShowBag;
	CCUIBackground* m_selectedSpriteImage;
};

#endif