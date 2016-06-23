#ifndef _STRENGPANEL_H_
#define _STRENGPANEL_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "StrengCreateBagListView.h"
#include "CCUIBackground.h"
#include "StrengCreate.h"
using namespace cocos2d;

class StrengFigureCreate;
class EquipmentVo;
class StrengGoods;
class FigureItem;
class GoodsInfo;
 
class StrengPanel : public CCLayer
{
public:
	StrengPanel();
	~StrengPanel();

public:

	bool init();
	LAYER_NODE_FUNC(StrengPanel);
	void figureSelectHandler( FigureItem* item );
	void bagClickHandler( CCObject* pObject = 0 );
	bool creatRoleEquipmentList( int id );
	vector<GoodsInfo*> sortedArr( EquipmentVo* roleEquipment );
	void creatBagEquipmentList(  std::map<int32, GoodsInfo*>* bagDictionary );
	void viewEquipmentInfo( int id, int goodID );
	void viewEquipmentDynamicInfo( int id, int goodID );
	string stringStrengAfter( int goodID, int lev );
	void sendSocket( int strengtype );
	void playStrengEffect( bool isCrit = false );
	void onEnterFrame();
	void updateTip( uint id );
	void updateStriengPropAtFirst( int Prob = 100 );
	void updateStrengProp( int Prob,int Trend );
	void clear();
	void CDchange( int show );
	void openStreng( int cdState );		// first time open board
	FigureItem* figureItem();
	void initView();
	void initButton();
	void btnHasVisble( bool upVis = true, bool downVis = true );	// btn show
	void onClickStrengUp(CCObject* pSender);
	void onClickStrengDown(CCObject* pSender);
	void strengLevLow();
	void btnEnable( CCMenu* btn, bool enabled );
	CCNode *getNewHandItem(int id);
	void clickCombox( CCObject* pSender );
	void directClickHandler( CCObject* pObj );
	void directRightClickHandler( CCObject* pObj );
	void setAttriVisible( bool bVar );
	void PlayEffectComplete( CCNode* pnode );
	void lockBtnStrengUp(ccTime dt);
	void lockBtnStrengDown(ccTime dt);
	static const int _pagesize = 5;
	
	//private var _toolTips:TipHelps;
public:
	int _CDState;

	StrengFigureCreate* _figureCreate;

	StrengCreate* _strengCreate;
	StrengCreateBagListView* _strengCreateBag;
	CCUIBackground* m_selectedSpriteImage;

	// equip info
	CCSprite* _pic;					// icon
	CCLabelTTF* _sItemsName;		// name
	CCLabelTTF* _txtLevel;			// level
	CCLabelTTF* _sItemsAttribute;	// attr

	CCLabelTTF* _txtTime;			// change per time
	CCLabelTTF* _txtTrend;			// change trend:update or decrese
	CCLabelTTF* _mcVIP;				// VIP

	CCLabelTTF* _txtRate;			// success rate
	//CCLabelTTF* _buyRate;			// buy rate
	CCLabelTTF* _comCheckBox;			//spend gold buy rate

	CCLabelTTF* _CD;				// CD

	CCMenu*		_btnStrengUp;
	CCMenuItemSprite* _StrengUpItem;
	CCMenu*		_btnStrengDown;
	CCMenuItemSprite* _StrengDownItem;

	CCLabelTTF* _sBtInfo;			// btn detail info

	CCSprite*	_rateBar;			// rate bar
	
	StrengGoods* _curStrengGoods;	//_curStrengGoods

	int _curStrengProb;				//_curStrengProb
	int _curStrengLev;				//_curStrengLev

	FigureItem* _item;

	CCSprite* m_spCombox;
	CCMenu* m_MenuCombox;
	bool m_bShowBag;

	int m_vipLv;
};

#endif