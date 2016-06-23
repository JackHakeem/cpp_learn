#ifndef _FIGUREITEMVIEW_H_
#define _FIGUREITEMVIEW_H_


#include "CCLayer.h"
#include "BaseType.h"
#include "model/ranking/vo/EquipItemVo.h"
#include "model/ranking/vo/RankItemVo.h"

class FigureItemView : public cocos2d::CCLayer
{
public:
    FigureItemView();
    ~FigureItemView();

    virtual bool init();

    void updateEquipments(const std::vector<EquipItemVo>& equips);

	void updateFigureData(const RankItemVo& data);

	void updateRoleModel(const RankItemVo& data);

	void updateRoleData(const RankItemVo& data);

private:

	cocos2d::CCNode* _pRoleData;
	cocos2d::CCNode* _pRoleModel;
	cocos2d::CCNode* _pRoleEquip;
};

#endif 

