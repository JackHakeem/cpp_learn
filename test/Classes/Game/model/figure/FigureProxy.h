#ifndef HLQS_FigureProxy_H_
#define HLQS_FigureProxy_H_
#include "mvc/Proxy.h"
#include "model/figure/vo/WashVo.h"
#include "socket/command/s17/SCMD172.h"
#include "socket/command/s30/SCMD30E.h"
#include "cocos2d.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "../spirit/vo/LvSpiritVo.h"

class FigureProxy: public Proxy
{
public:
	bool _figureInfoInited;
	bool _equitInfoInited;
	std::map<int/*figure id*/, WashVo> _washValueCache;
	std::map<int, std::vector<LvSpiritVo> >_spDic;
public:
	FigureProxy();
	~FigureProxy();
	void setMerSpInfo(int id, std::vector<LvSpiritVo>& arr);
	void initMercBaseInfo();
	void updateEquitInfo(char* data);
	void updateEquipment(SCMD172* scmd172);
	void updateSkill(SCMD30E* scmd30e);
	GoodsInfo* goodsInfo(int figureId, int sitNum);
	void mercSkillExchange(int a_mercId, int a_skill, int b_mercId, int b_skill);
	bool isFigureInfoInit();
	bool isEquitInfoInit();
	void setDynamicInfo(int figureId, int sitNum);
	void setOtherDynamic(int figureId, int sitNum);
	void replaceWashValue(int figure, WashVo& washVo);
	void addWashValueCache(int figure, WashVo& washVo);
	void delWashValueCache(int figure);
	WashVo* getWashValueCache(int figure);
};

#endif