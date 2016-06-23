#include "EggProxy.h"
#include "socket/command/s40/SCMD401.h"
#include "socket/command/s40/SCMD40B.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

void EggProxy::initReward(SCMD401* param)
{
	//许愿币数量
	_currencyNum = param->a_num;
			
	_myRewards.clear();
	_otherRewards.clear();
			
	//自己的历史许愿记录
	std::vector<SCMD401Node1>& myEggs = param->b_myReward;
	int myEggsLen = myEggs.size();
	for(int i = 0; i < myEggsLen; i++)
	{
		SCMD401Node1 node1 = myEggs[i];
		EggInfo myEgg;
		myEgg.eggId = i + 1;
		myEgg.type = node1.a_type;
		myEgg.quality = node1.b_quality;
		myEgg.state = node1.c_state;
		myEgg.goodsId = node1.d_goodsId;
		myEgg.goodsNum = node1.e_goodsNum;
		myEgg.num = node1.f_num;
		_myRewards.push_back(myEgg);
	}

	//玩家的历史许愿记录
	std::vector<SCMD401Node2> otherEggs = param->c_otherReward;
	int otherEggLen = otherEggs.size();
	for(int j = 0; j < otherEggLen; j++)
	{
		SCMD401Node2 node2 = otherEggs[j];
		EggInfo otheEgg;
		otheEgg.eggId = j + 1;
		otheEgg.name = node2.a_name;
		otheEgg.type = node2.b_type;
		otheEgg.quality = node2.c_quality;
		otheEgg.state = node2.d_state;
		otheEgg.goodsId = node2.e_goodsId;
		otheEgg.goodsNum = node2.f_goodsNum;
		otheEgg.num = node2.g_num;
		_otherRewards.push_back(otheEgg);
	}
			
	/** 数据初始化完成后，给Mediator派发消息 */
	sendNotification(Facade_Mediator, AppFacade_EGG_CHANGE, (char *)0, EggMediator::REWARD_HISTORY);
}

void EggProxy::initDepot(SCMD40B* param)
{
	//蛋蛋数量
	_eggNum = param->a_eggs.size();
			
	_eggs.clear();
	_prizeEggs.clear();
			
	
	for(int index = 1;index <= depotPage; index++)
	{
		_eggDic[index].clear();
	}
	_eggDic.clear();
			
	std::vector<SCMD40BNode> eggs = param->a_eggs;
	int len = eggs.size();
	for(int i = 0; i < len; i++)
	{
		SCMD40BNode node = eggs[i];
		EggInfo egg;
		egg.eggId = i + 1;
		egg.type = node.a_type;
		egg.quality = node.b_quailty;
		egg.state = node.c_state;
		egg.goodsId = node.d_goodsId;
		egg.goodsNum = node.e_goodsNum;
		egg.num = node.f_num;
		_eggs.push_back(egg);
				
		int key = int(i / depotGrid) + 1;
		if(key <= depotPage){
			_eggDic[key].push_back(egg);
		}
		if(egg.type != 3){
			_prizeEggs.push_back(egg);
		}
	}

	sendNotification(Facade_Mediator, AppFacade_EGG_CHANGE, (char *)0, EggMediator::DEPOT_INFO);
}

std::vector<EggInfo>* EggProxy::getEggsByPage(int page)
{
	if (_eggDic.find(page) != _eggDic.end())
		return &_eggDic[page];
	
	return 0;
}
