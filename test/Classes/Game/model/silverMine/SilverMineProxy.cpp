#include "SilverMineProxy.h"

SilverMineProxy::SilverMineProxy()
{
	isInMine = false;
	_campId = -1;  // 阵营ID 有效值 0，1, 2 
	_moveCD = 0;	// 行动CD 单位秒
	_inActionCD = false;
	 _digCD = 0;	// 挖矿CD 单位秒
	_inDigCD = false;
	_mineID  = 0;		// 当前所在矿ID
	_onMine  = 0;		// 当前所在银矿人数
	_winRow  = 0;		// 连胜次数
	_attPlus = 0;		// 鼓舞攻击加成
	_defPlus = 0;		// 鼓舞防御加成 
	//	 _mineArr:Array = [];  // 银矿数组
	_token0 = 0;   // 令牌0
	_token1 = 0;   // 令牌1 
}

SilverMineProxy::~SilverMineProxy()
{}