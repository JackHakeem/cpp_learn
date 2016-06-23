#ifndef _MyRobPanel_H_
#define _MyRobPanel_H_

#include "BaseType.h"
#include "PopContainer.h"
#include "model/trader/vo/CityPriceVo.h"
#include "model/trader/vo/BankGridVo.h"
#include "model/trader/vo/TraderEventVo.h"
#include "model/player/RoleManage.h"
#include "TraderGoodsItem.h"
#include "utils/BitmapMovieClip.h"

class MyRobPanel : public PopContainer
{
public:
	MyRobPanel();
	~MyRobPanel();

public:
	bool init();
	LAYER_NODE_FUNC(MyRobPanel);
	virtual void clickCloseHandler( CCObject* pSender );
	void updateData();

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


	CCLabelTTF* _PosTxt;
	CCLabelTTF* _awardTxt;
	CCLabelTTF* _robInfo1Txt;
	CCLabelTTF* _robInfo2Txt;

};

#endif