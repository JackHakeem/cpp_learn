#pragma once

class DamageRankListVo
{
public:
	DamageRankListVo() : playerName("") , damage(0) , damagePercent(0)
	{

	}
	~DamageRankListVo(){};

public:
	/** // 玩家名字 */
	std::string playerName;		
	/** // 累计伤害量 */
	int damage;		
	/** // 累计伤害百分比(0～100) */
	int damagePercent;

protected:
private:
};