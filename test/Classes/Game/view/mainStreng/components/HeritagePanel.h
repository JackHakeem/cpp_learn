#ifndef _HeritagePanel_H_
#define _HeritagePanel_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "CCUIBackground.h"
#include "HeritageCreate.h"
#include "FigureItem.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "utils/TipHelps.h"
#include "utils/TipBase.h"
using namespace cocos2d;

class HeritagePanel : public LayerNode, public TipBase
{
public:
	HeritagePanel();
	~HeritagePanel();

public:
	bool init();
	LAYER_NODE_FUNC(HeritagePanel);
	void creatEquipmentList( std::map<int32, GoodsInfo*>* bagDictionary );
	void openStreng( int cdState );		// first time open board
	void initView();
	void initButton();
	void onClickStrengUp(CCObject* obj);
	void dragGrid( GoodsInfo* info, int type = 0, HeritageGoods* good = 0 );
	void grid1ClickHandler( CCObject* obj );
	void grid2ClickHandler( CCObject* obj );
	void clear();
	void refreshBeHeritageGoods( GoodsInfo* info );

	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void update( ccTime dt );

	void gridClick( int param1 );
	void refreshHeritageGoods( GoodsInfo* goodsInfo2 );
	CCSize getSrcContentSize();
	void onClickCancel(CCObject* obj);
	void caculateCost();
	void updateTip( uint32 id );
	void refreshWithoutOne( int32 goodId );
	void okFunction( CCObject* pObject );
	void cancelFunction( CCObject* pObject );
	CCAction * getAction();
	void fadeAct();
	void StopfadeAct();
public:
	HeritageCreate* _strengCreate;

	CCMenuItemSprite* _StrengUpItem;
	CCMenu* _btnStrengUp;

	SpriteNode* _unlockHtg;
	SpriteNode* _unlockBeHtg;
	SpriteNode* _unlockNew;

	CCSprite* _picHtg;
	CCSprite* _picBeHtg;
	CCSprite* _picNew;

	GoodsInfo* _goodsInfo1;
	GoodsInfo* _goodsInfo2;
	GoodsInfo* _goodsInfo3;

	CCMenu* _menuGrid1;
	CCMenu* _menuGrid2;

	CCSprite* _gridSelect1;
	CCSprite* _gridSelect2;

	CCLabelTTF* _radioText1;
	CCLabelTTF* _radioText2;

	CCLabelTTF* _goldTxt;

	int _materialsNum;
	int _cost;
	TipHelps* _tips;

	CCLabelTTF* _pGoldSpd;
	int m_strengUplev;

	float m_fStep;
	bool m_bDraded;
	int m_iClickPos;
};

#endif