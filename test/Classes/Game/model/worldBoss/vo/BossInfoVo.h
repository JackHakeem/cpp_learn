#pragma once

class BossInfoVo
{
public:
	BossInfoVo() : maxHP(0) , currentHP(0) , totalDamageLow(0) , totalDamageHigh(0)
	{

	}
	~BossInfoVo(){};

public:
	/** 最大血量 -1表示未知 */
	int maxHP;		
	/** 当前血量-1表示未知 0表示BOSS已死 */
	int currentHP;
	/** 当前总伤害-低位*/
	uint32 totalDamageLow;
	/** 当前总伤害-高位*/
	uint32 totalDamageHigh;

protected:
private:
};