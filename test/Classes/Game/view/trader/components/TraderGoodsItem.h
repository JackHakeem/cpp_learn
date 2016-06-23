#pragma once

#include "BaseType.h"
#include "cocos2d.h"
#include "model/trader/vo/TraderGoodsVo.h"
#include "CCUIBackground.h"
using namespace cocos2d;

class TraderGoodsItem:public LayerNode
{
public:
	TraderGoodsItem();
	~TraderGoodsItem();

	bool init();
	bool initVo(TraderGoodsVo* rankVo);


	void initView();


public:
	TraderGoodsVo* itemVo;
	CCLabelTTF* _nameEquipment;
	SpriteNode* _good;

};