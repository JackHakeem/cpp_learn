#include "model/figure/EquipmentManager.h"
#include "socket/command/s30/SCMD30A.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/player/RoleManage.h"
#include "model/com/vo/GoodsDynamic.h"

EquipmentManager::EquipmentManager()
{
}

/**
* @param figure_id
* 
*/

void EquipmentManager::deleteEquipment(int figure_id)
{
	std::map<int, EquipmentVo>::iterator iter = _playerEquipment.find(figure_id);
	if(iter != _playerEquipment.end())
		_playerEquipment.erase(iter);
}

/**
* @param id ½ÇÉ«id
* @return EquipmentVo
* 
*/
EquipmentVo* EquipmentManager::getEquipment(int figure_id)
{
	std::map<int, EquipmentVo>::iterator iter = _playerEquipment.find(figure_id);
	if(iter == _playerEquipment.end())
		return NULL;

	return &(iter->second);
}

/**
* @param id
* @return int
* 
*/
// jae amended.5.30
int EquipmentManager::getEquipmentNum(int figure_id)
{
	std::map<int, EquipmentVo>::iterator iter = _playerEquipment.find(figure_id);
	if(iter == _playerEquipment.end())
		return 0;

	//return iter->second.m_equipments.size();
	EquipmentVo& vo = iter->second;
	int num = 0;
	for( int i = 1; i<=6; i++ )
	{
		GoodsInfo* pInfo = vo.getIndex(i);
		if ( !pInfo ) continue;
		if( pInfo->id != 0 ) num++;
	}
	return num;
}

/**
* @return 
* 
*/

GoodsInfo* EquipmentManager::getEquip(int id, int grid)
{
	std::map<int, EquipmentVo>::iterator iter = _playerEquipment.find(id);
	if(iter == _playerEquipment.end())
		return NULL;
	return iter->second.getIndex(grid);
}

void EquipmentManager::createEquipment(char* data)
{
	if(!data)
		return;

	int i = 0;
	EquipmentVo equipVo;
	std::vector<SCMD30ANode>* a_eqpList = (std::vector<SCMD30ANode>*)data;
	std::vector<SCMD30ANode>::iterator iter = a_eqpList->begin();
	
	for(; iter != a_eqpList->end(); ++iter)
	{
		GoodsInfo goodsInfo;
		goodsInfo.id = iter->c_eqpId;
		goodsInfo.goodId = iter->d_eqpGoodsId;
		goodsInfo.sitGrid = iter->b_sitGrid;
		goodsInfo.strengthen = iter->e_superLv;
		goodsInfo.stamina = iter->f_stamina;
		goodsInfo.wrist = iter->g_wrist;
		goodsInfo.intellect = iter->h_intellect;
		goodsInfo.number = 1;

		if(i % 7 == 6)
		{
			_playerEquipment[iter->a_figureId] = equipVo;
		}

		if(iter->d_eqpGoodsId != 0)
		{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
			GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(iter->d_eqpGoodsId);
			
			if(!goodBasic)
			{
				++i;
				continue;
			}

			goodsInfo.name = goodBasic->goodName;
			goodsInfo.type = goodBasic->type;
			goodsInfo.equip_type = goodBasic->equip_type;
			goodsInfo.quality = goodBasic->quality;

			GoodsDynamic* dynamic = NULL;
			if(goodsInfo.equip_type == 7)
			{
				//dynamic = g_pGoodsDynamicManager->createSpiritDynamic(&goodsInfo, goodBasic, iter->l_blue, iter->m_purple, iter->n_red);
			}
			else
			{
				if(g_pGoodsDynamicManager)
					dynamic = g_pGoodsDynamicManager->createDynamic(&goodsInfo, goodBasic);
			}

			if(!dynamic)
			{
				++i;
				continue;
			}

			PlayerInfoVo* info = RoleManage::Instance()->getMercenary(iter->a_figureId);
			if(!info)
			{
				++i;
				continue;
			}

			std::string name = info->playerBaseInfo.name;
			goodsInfo.explain = GoodsToolTips::getGoodsTooltips(goodBasic, dynamic, &name);
		}
		equipVo.setIndex(goodsInfo.sitGrid ,goodsInfo);
		++i;
	}
}

void EquipmentManager::createOtherEquipment(char* data)
{
	if(!data)
		return;

	int i = 0;
	EquipmentVo equipVo;
	std::vector<SCMD30ANode>* a_eqpList = (std::vector<SCMD30ANode>*)data;
	if(!a_eqpList)
		return;

	std::vector<SCMD30ANode>::iterator iter = a_eqpList->begin();
	
	for(; iter != a_eqpList->end(); ++iter)
	{
		GoodsInfo goodsInfo;
		goodsInfo.id = iter->c_eqpId;
		goodsInfo.goodId = iter->d_eqpGoodsId;
		goodsInfo.sitGrid = iter->b_sitGrid;
		goodsInfo.strengthen = iter->e_superLv;
		goodsInfo.stamina = iter->f_stamina;
		goodsInfo.wrist = iter->g_wrist;
		goodsInfo.intellect = iter->h_intellect;
		goodsInfo.number = 1;

		if(iter->d_eqpGoodsId != 0)
		{
			GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(iter->d_eqpGoodsId);
			if(!goodBasic)
				continue;

			goodsInfo.name = goodBasic->goodName;
			goodsInfo.type = goodBasic->type;
			goodsInfo.equip_type = goodBasic->equip_type;
			goodsInfo.quality = goodBasic->quality;

			GoodsDynamic* dynamic = NULL;
			if(goodsInfo.equip_type == 7)
			{
				//dynamic = g_pGoodsDynamicManager->createSpiritDynamic(&goodsInfo, goodBasic, iter->l_blue, iter->m_purple, iter->n_red);
			}
			else
			{
				if(g_pGoodsDynamicManager)
					dynamic = g_pGoodsDynamicManager->createDynamic(&goodsInfo, goodBasic);
			}

			if(!dynamic)
				continue;

			goodsInfo.explain = GoodsToolTips::getGoodsTooltips(goodBasic, dynamic);
		}

		equipVo.setIndex(goodsInfo.sitGrid ,goodsInfo);
		if(i % 7 == 6)
		{
			_playerEquipment[iter->a_figureId] = equipVo;
		}
		i++;
	}
}

void EquipmentManager::updateEquipment(SCMD172* scmd172)
{
	if(!scmd172)
		return;

	EquipmentVo* equipVo = getEquipment(scmd172->a_figureId);
	if(!equipVo)
		return;
	int sitGrid = scmd172->b_sitGrid;
	GoodsInfo goodsInfo;
	goodsInfo.id = scmd172->c_eqpId;
	goodsInfo.goodId = scmd172->d_eqpGoodsId;
	goodsInfo.sitGrid = sitGrid;
	goodsInfo.number = 1;

	if(scmd172->d_eqpGoodsId !=0)
	{
		GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(scmd172->d_eqpGoodsId);
		if(!goodBasic)
			return;

		goodsInfo.name = goodBasic->goodName;
		goodsInfo.type = goodBasic->type;
		goodsInfo.equip_type = goodBasic->equip_type;
		goodsInfo.quality = goodBasic->quality;
		PlayerInfoVo* mercObjectVo = RoleManage::Instance()->getMercenary(scmd172->a_figureId);
		if(!mercObjectVo)
			return;

		std::string name = mercObjectVo->playerBaseInfo.name;
		//goodsInfo.explain = GoodsToolTips::getDefaultExplain(goodBasic,scmd172->c_eqpId, &(mercObjectVo->playerBaseInfo.name));

		if(scmd172->c_eqpId !=0)
		{
			GoodsDynamic* goodDynamic=g_pGoodsDynamicManager->getGoodsDynamic(scmd172->c_eqpId);
			if(goodDynamic)
			{
				goodsInfo.strengthen = goodDynamic->e_strengthen;
				goodsInfo.explain = GoodsToolTips::getGoodsTooltips(goodBasic, goodDynamic, &name);
			}
			else
			{
				goodsInfo.explain = GoodsToolTips::getDefaultExplain(goodBasic, scmd172->c_eqpId, &name);
			}
		}
	}
	equipVo->setIndex(sitGrid, goodsInfo);
}

EquipmentManager::~EquipmentManager()
{
	std::map< int, EquipmentVo >::iterator it;
	for ( it = _playerEquipment.begin(); it != _playerEquipment.end(); it++ )
	{
		//CC_SAFE_DELETE( it->second.e );
        EquipmentVo& vo = it->second;
        std::map<int, GoodsInfo>::iterator it2;
        for ( it2 = vo.m_equipments.begin(); it2 != vo.m_equipments.end(); it2++ )
        {
           // CC_SAFE_DELETE( it2->second.explain );
        }
        vo.m_equipments.clear();
	}
	_playerEquipment.clear();
}
