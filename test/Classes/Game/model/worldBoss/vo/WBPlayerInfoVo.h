#pragma once

class WBPlayerInfoVo
{
public:
	WBPlayerInfoVo()
	{
		awardList.clear();
	}
	~WBPlayerInfoVo(){};

public:
	// 实时数据
	/** 我的累计伤害  */
	int damage;
	/** 复活CD,时间戳,到此时间后才可移动 */
	int deathCD;
	/** 鼓舞次数  */
	int boostNum;
	/** 我的累计奖励  */
	std::list<SCMD2C8::SCMD2C8Node> awardList;

protected:
private:
};