#pragma once

#include "BaseType.h"
#include "mvc/Proxy.h"
#include "./vo/EggInfo.h"
#include "./vo/EggVo.h"


class SCMD401;
class SCMD40B;

class EggProxy : public Proxy
{
public:
	
	/** 许愿币数量 */
	int _currencyNum;
	/** 我的历史许愿奖励 */
	std::vector<EggInfo> _myRewards;
	/** 其他玩家的历史许愿奖励 */
	std::vector<EggInfo> _otherRewards;
	/** 心愿宝箱里的蛋蛋数组 */
	std::vector<EggInfo> _eggs;
	/** 心愿宝箱里的蛋蛋字典 */
	std::map<int, std::vector<EggInfo> > _eggDic;
	/** 心愿宝箱里的蛋蛋大奖*/
	std::vector<EggInfo> _prizeEggs;
	/** 心愿宝箱里的蛋蛋数 */
	int _eggNum;
	/** 心愿宝箱的页数 */
	int depotPage;
	/** 心愿宝箱每页的格子数 */
	int depotGrid;

	EggProxy()
	{
		_currencyNum = 0;
		_eggNum = 0;
		depotPage = 10;
		depotGrid = 30;
	}
	~EggProxy()
	{}
		
	/**
		* 初始化许愿币数量和历史奖励信息（包括自己的和玩家的）
		* @param param
		* 
		*/		
	void initReward(SCMD401* param);
		
	/**
		* 初始化心愿宝箱数据，存储宝箱里的所有蛋蛋
		* @param param
		* 
		*/		
	void initDepot(SCMD40B* param);

	/**
		* 根据宝箱的页码来获取本页蛋蛋的数组 
		* @param page	页码
		* @return 
		* 
		*/	
	std::vector<EggInfo>* getEggsByPage(int page);
		
	/* ------------------------------------- getter/setter ------------------------------------- */
		
	/** 许愿币数量 */
	int getcurrencyNum()
	{
		return _currencyNum;
	}
		
	/** 我的历史许愿奖励 */
	std::vector<EggInfo>& getmyRewards()
	{
		return _myRewards;
	}

	/** 其他玩家的历史许愿奖励 */
	std::vector<EggInfo>& getotherRewards()
	{
		return _otherRewards;
	}

	/** 心愿宝箱里的蛋蛋数 */
	int geteggNum()
	{
		return _eggNum;
	}

	/** 心愿宝箱里的蛋蛋数组 */
	std::vector<EggInfo> geteggs()
	{
		return _eggs;
	}

	/** 心愿宝箱里的蛋蛋大奖*/
	std::vector<EggInfo> getprizeEggs()
	{
		return _prizeEggs;
	}
};