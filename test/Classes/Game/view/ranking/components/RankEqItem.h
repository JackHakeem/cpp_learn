#ifndef _RANKEQITEM_H_
#define _RANKEQITEM_H_
#include "LayerNode.h"
#include "utils/TipBase.h"
#include "model/ranking/vo/EquipItemVo.h"

class TipHelps;

class RankEqItem : public LayerNode, public TipBase
{
public:
    RankEqItem();
    ~RankEqItem();

    virtual bool init(const EquipItemVo& equip);

public:
	void onClickItem(cocos2d::CCObject* node);

	TipHelps* myTip;
};

#endif
