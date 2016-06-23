#ifndef _RobPanel_H_
#define _RobPanel_H_

#include "BaseType.h"
#include "PopContainer.h"
#include "model/trader/vo/CityPriceVo.h"
#include "model/trader/vo/BankGridVo.h"
#include "model/trader/vo/TraderEventVo.h"
#include "model/player/RoleManage.h"
#include "TraderGoodsItem.h"
#include "utils/BitmapMovieClip.h"

class CustomCD;

class RobPanel : public PopContainer
{
public:
	RobPanel();
	~RobPanel();

public:
	bool init();
	LAYER_NODE_FUNC(RobPanel);
	virtual void clickCloseHandler( CCObject* pSender );
	void robthatsonofbitch( CCObject* pSender );
	void updateData();
	void updateGetInfo( int sil, int pop, int beated, int buyTokenCnt );
	void buyTradeToken(CCObject* obj);
	void cdChangedHandler( CCNode* n, void* data );
	void isLockHandler( int type );

	enum
	{
		ROB_THAT_SON_OF_BITCH,
	};
public:
	CCLayer* pInnerLayer;

	int _id;
	CCLabelTTF* statusTxt;
	CCMenu* robBtn;
	int _tokenNum;
	int _lv;
	string _name;
	int _request;
	BitmapMovieClip* roleMovieClip;

	CCLabelTTF* _buyTokenBtnTxt;

	CCLabelTTF* _freeTokenTxt;

	CCLabelTTF* _robGetSil;
	CCLabelTTF* _robGetPop;
	int _beated;
	CustomCD* _cd;
	CCMenuItemSprite * _robBtnImg;
};

#endif