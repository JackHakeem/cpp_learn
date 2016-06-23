#ifndef _MELTINGPANEL_H_
#define _MELTINGPANEL_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "CCUIBackground.h"
using namespace cocos2d;

class StrengCreate;
class EquipmentVo;
class GoodsInfo;
class MeltingBagCreate;

class MeltingPanel : public CCLayer
{
public:
	MeltingPanel();
	~MeltingPanel();

public:

	bool init();
	LAYER_NODE_FUNC(MeltingPanel);
	void initView();
	void createMeltingList( std::map<int32, GoodsInfo*> goodDic );
	void createBagList( int page );
	void dragGrid( GoodsInfo* info, int sitNum, int page, int type );
	void updateRate( int id1, int id2, int id3, int vip = 0 );
	void updateSparInfo( int num );
	void roleVipLev( int lev );
	void clear();
	virtual void setIsVisible( bool bIsVisible ); 

	int getSparNum();
	void grid1ClickHandler(CCObject * obj);
	void grid2ClickHandler(CCObject * obj);
	void grid3ClickHandler(CCObject * obj);
private:
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void meltingHandler( CCObject* pSender );
	void meltingHelpHandler( CCObject* pSender );
	void onClickHandler( int radioNo );
	void gridClick( int type );
	void meltingOkFunction(CCObject* dt);
	void meltingCancelFunction(CCObject* dt);
public:
	//CCLayer* _icon1;	// first melting grid
	//CCLayer* _icon2;	// second
	//CCLayer* _icon3;	// third

	CCLabelTTF* _sparInfo;		//spar info
	//private var _explain:MovieClip;		//melting explain
	CCLabelTTF* _bagProp;

	//private var _ef:MovieClip;				//action
	CCMenu* _meltingBtn;	//melting btn
	CCLabelTTF* _sparNumText;	//spar count get if success
	CCLabelTTF* _rateText;		//rate txt
	int _sparNum;				//spar num

	//private var _mcPay:MovieClip;			//vip区域
	//private var _radio1:CustomCheckBox;	//黄金熔炼
	//private var _radio2:CustomCheckBox;	//白金熔炼
	//private var _radio3:CustomCheckBox;	//至尊熔炼
	CCLabelTTF* _radioText1;		//_radio1文本
	CCLabelTTF* _radioText2;		//_radio2文本
	CCLabelTTF* _radioText3;		//_radio3文本
	int _vipLevel;			//选择的vip等级

	int _goodsId1;				//熔炼物品1
	int _goodsId2;				//熔炼物品2
	int _goodsId3;				//熔炼物品3
	int _sit1;
	int _sit2;
	int _sit3;
	int _page1;
	int _page2;
	int _page3;
	GoodsInfo* _goodsInfo1;
	GoodsInfo* _goodsInfo2;
	GoodsInfo* _goodsInfo3;

	int _materialsNum;						// melting material num

	int _roleVipLev;						// cur vip lev
	int _crystalLev;			// mingzhishuijing lev
	//private var _arr:Array;
	int _goldNum;

	CCUIBackground* _bgEquip;
	CCUIBackground* _bgEquipInfo;
	MeltingBagCreate* bagCreate;

	CCMenu* _menuGrid1;
	CCMenu* _menuGrid2;
	CCMenu* _menuGrid3;
	CCSprite* _gridSelect1;
	CCSprite* _gridSelect2;
	CCSprite* _gridSelect3;
	//private var _toolTips:TipHelps;
	//private var _toolTips1:TipHelps;
	//private var _toolTips2:TipHelps;
	//private var _toolTips3:TipHelps;
	int _curPage;			// 背包当前页
	vector<GoodsInfo*> _goodsArr;
	//public var isDispaly:Boolean = false;

	int m_canGetSpar;
	int m_canGetExtraSpar;
	int m_returnPrice;
};

#endif