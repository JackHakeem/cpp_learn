#include "model/figure/FigureProxy.h"
#include "model/figure/EquipmentManager.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/skill/vo/SkillType.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"
#include "model/backpack/GoodsManager.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/figure/FigureMediator.h"
#include "../skill/SkillProxy.h"
#include "manager/ViewManager.h"

FigureProxy::FigureProxy()
{
	_figureInfoInited = 0;
	_equitInfoInited = 0;
}

void FigureProxy::setMerSpInfo(int id, std::vector<LvSpiritVo>& arr)
{
	_spDic[id] = arr;
}

void FigureProxy::initMercBaseInfo()
{
	_figureInfoInited = true;
}

void FigureProxy::updateEquitInfo(char* data)
{
	if(!data)
		return;

	EquipmentManager::Instance()->createEquipment(data);
	_equitInfoInited = true;
	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, data, FigureMediator::UPDATE_EQUIP_INFO);
}

void FigureProxy::updateEquipment(SCMD172* scmd172)
{
	if(!scmd172)
		return;

	EquipmentManager::Instance()->updateEquipment(scmd172);
	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)scmd172, FigureMediator::EQUIP_UPDATE);
	//sendNotification(FigureMediator.EQUIP_UPDATE,{fid:param.a_figureId,grid:param.b_sitGrid.value});
}

void FigureProxy::updateSkill(SCMD30E* scmd30e)
{
	if(!scmd30e)
		return;

	CCLog("release gua here? line:56 %d file: %s", __LINE__, __FILE__);

	PlayerInfoVo* mercInfo = RoleManage::Instance()->getMercenary(scmd30e->b_merId);
	if(!mercInfo)
		return;

	if(	scmd30e->c_skillRank == SkillType::PASSVIE)
	{
		mercInfo->playerBaseInfo.skill3 = scmd30e->d_skillId;
	}
	else if(scmd30e->c_skillRank == SkillType::SKILL)
	{
		mercInfo->playerBaseInfo.skill1 = scmd30e->d_skillId;
	}
	
	RoleManage::Instance()->updateMercenaryEx(scmd30e->b_merId , mercInfo);

	/*SkillView * sv = ViewManager::getInstance()->_skillView;
	if (sv)
	{
		sv->addSkillCellAndItem();
	}*/

	if(g_pFacade)
	{
		SkillProxy* skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
		skillProxy->exchangeSkill(scmd30e->b_merId, scmd30e->c_skillRank, scmd30e->d_skillId, scmd30e->e_exSkillId);
	}
}

GoodsInfo* FigureProxy::goodsInfo(int figureId, int sitNum)
{
	return EquipmentManager::Instance()->getEquip(figureId,sitNum);
}


void FigureProxy::mercSkillExchange(int a_mercId, int a_skill, int b_mercId, int b_skill)
{
	PlayerInfoVo* mercInfo = RoleManage::Instance()->getMercenary(a_mercId);
	if(mercInfo == NULL)
		return;
	mercInfo->playerBaseInfo.skill3 = a_skill;
	RoleManage::Instance()->updateMercenaryEx(a_mercId , mercInfo);

	mercInfo = RoleManage::Instance()->getMercenary(b_mercId);
	if(mercInfo == NULL)
		return;
	mercInfo->playerBaseInfo.skill3 = b_skill;
	RoleManage::Instance()->updateMercenaryEx(b_mercId , mercInfo);

	//SkillView * sv = ViewManager::getInstance()->_skillView;
	//if (sv)
	//{
	//	sv->addSkillCellAndItem();;
	//}

	SkillProxy* skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
	if(skillProxy)
	{
		skillProxy->exchangeSkill(a_mercId, SkillType::PASSVIE, a_skill, 0);
		skillProxy->exchangeSkill(b_mercId, SkillType::PASSVIE, b_skill, 0);
	}
}

bool FigureProxy::isFigureInfoInit()
{
	return _figureInfoInited;
}

bool FigureProxy::isEquitInfoInit()
{
	return _equitInfoInited;
}

/**
*Characters equipment dynamic information updates
* @param figureId
* @param sitNum
* 
*/	

void FigureProxy::setDynamicInfo(int figureId, int sitNum)
{
	GoodsInfo* info = goodsInfo(figureId, sitNum);
	if(info == NULL)
		return;

	if(!g_pGoodsDynamicManager)
		return;

	GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic(info->id);
	if(goodsDynamic == NULL)
		return;

	PlayerInfoVo* mercObjectVo= RoleManage::Instance()->getMercenary(figureId);
	if(!mercObjectVo)
		return;

	//Doyang 20120716
	//CC_SAFE_DELETE(info->explain); kevinchange0811

	info->explain = GoodsToolTips::getGoodsTooltips(g_pGoodsManager->getBasicGood(info->goodId),
													goodsDynamic , &(mercObjectVo->playerBaseInfo.name));

	struct Data
	{
		int figureId;
		int sitGrid;
	};
	Data data;
	data.figureId = figureId;
	data.sitGrid = info->sitGrid;
	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)(&data), FigureMediator::EQUIPMENT_ITEM_TIP_UPDATE);
}

void FigureProxy::setOtherDynamic(int figureId, int sitNum)
{
	GoodsInfo* info = goodsInfo(figureId, sitNum);
	if(info == NULL || g_pGoodsManager == NULL || g_pGoodsDynamicManager == NULL)
		return;

	GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic(info->id);
	if(goodsDynamic == NULL)
		return;
	info->explain = GoodsToolTips::getGoodsTooltips(g_pGoodsManager->getBasicGood(info->goodId),
													goodsDynamic);

	struct Data
	{
		int figureId;
		int sitGrid;
	};
	Data data;
	data.figureId = figureId;
	data.sitGrid = info->sitGrid;

	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)(&data), FigureMediator::OTHER_ITEM_TIP_UPDATE);
	//sendNotification(OtherFigureMediator.OTHER_ITEM_TIP_UPDATE, {fid:figureId,grid:info.sitGrid});
}

/**
*Replace a person's attribute values
* @param figure
* @param value
* 
*/

void FigureProxy::replaceWashValue(int figure, WashVo& washVo)
{
	delWashValueCache(figure);
	PlayerInfoVo* info = RoleManage::Instance()->getMercenary(figure);
	if(!info)
		return;

	info->figureBaseInfo.strength = washVo.strength;
	info->figureBaseInfo.stamina = washVo.stamina;
	info->figureBaseInfo.intellect = washVo.intellect;

	RoleManage::Instance()->updateMercenaryEx(figure , info);

	struct cmd
	{
		int figure;
		WashVo* washVo;
		cmd()
		{
			figure = 0;
			washVo = NULL;
		}
	};

	cmd cmd1;
	cmd1.figure = figure;
	cmd1.washVo = &washVo;
	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)(&cmd1), FigureMediator::SAVE_WASH_VALUE);
	//this.sendNotification(FigureMediator.SAVE_WASH_VALUE,  {id:figure, vo:value});
}

void FigureProxy::addWashValueCache(int figure, WashVo& washVo)
{
	_washValueCache[figure] = washVo;
	struct cmd
	{
		int figure;
		WashVo* washVo;
		cmd()
		{
			figure = 0;
			washVo = NULL;
		}
	};

	cmd cmd1;
	cmd1.figure = figure;
	cmd1.washVo = &washVo;

	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)(&cmd1), FigureMediator::REFRESH_WASH_VALUE);
	//sendNotification(FigureMediator.REFRESH_WASH_VALUE, {id:figure, vo:value});
}


void FigureProxy::delWashValueCache(int figure)
{
	std::map<int, WashVo>::iterator iter =  _washValueCache.find(figure);
	if(iter != _washValueCache.end())
		_washValueCache.erase(iter);
}

WashVo* FigureProxy::getWashValueCache(int figure)
{
	std::map<int, WashVo>::iterator iter =  _washValueCache.find(figure);
	if(iter != _washValueCache.end())
		return &(iter->second);
    return 0;
}

FigureProxy::~FigureProxy()
{
	_washValueCache.clear();
	_spDic.clear();
}
