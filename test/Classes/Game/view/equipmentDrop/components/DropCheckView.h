#pragma once

#include "EqCreate.h"

class CustomComboBox;
class GoodsBasic;
class EqItem;

class DropCheckView:public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	enum
	{

		DropCheckViewZ_blackBG,
		DropCheckViewZ_bg1,
		DropCheckViewZ_bg2,
		DropCheckViewZ_levComboBox,
		DropCheckViewZ_typeComboBox,
		DropCheckViewZ_direct,
		DropCheckViewZ_ListView,
		DropCheckViewZ_btnX,
		DropCheckViewZ_title,

	};
	enum
	{
		DropCheckViewTAG_blackBG,
		DropCheckViewTAG_bg1,
		DropCheckViewTAG_bg2,
		DropCheckViewTAG_levComboBox,
		DropCheckViewTAG_typeComboBox,
		DropCheckViewTAG_direct1,
		DropCheckViewTAG_direct2,
		DropCheckViewTAG_direct3,
		DropCheckViewTAG_direct4,
		DropCheckViewTAG_ListView,
		DropCheckViewTAG_btnX,
		DropCheckViewTAG_title,
	};
public:
	DropCheckView();
	bool init();

	void setDefaultEqs(int lev, int typeIndex);
	void startListener();
	int getIndexByCrastalLev(int lev);
	void getEquips(int lev, int typeIndex, std::vector<GoodsBasic*>& dstEQ);
	void createEqList(int lev, int typeIndex);

	void buildItems();
	virtual int getCount();
	virtual LayerNode * getView( int position );
	void levSelectHandler(CCNode *pNode, void *pData);
	void typeSelectHandler(CCNode *pNode, void *pData);

	//void onEnter();
	void onExit();
	//bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onItemClickListener(LayerNode *itemCell, int position);
	void dispear(CCObject* pSender);
public:
	int _curLevIndex;		//等级索引
	int _curTypeIndex;		//类型索引
	CustomComboBox* _levComboBox;
	CustomComboBox* _typeComboBox;
	std::vector<GoodsBasic*> m_dstEQ;
	std::vector<EqItem*> m_dstEQItem;
	EqCreate* _pListView;
};