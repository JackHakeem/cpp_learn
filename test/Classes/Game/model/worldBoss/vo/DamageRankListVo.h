#pragma once

class DamageRankListVo
{
public:
	DamageRankListVo() : playerName("") , damage(0) , damagePercent(0)
	{

	}
	~DamageRankListVo(){};

public:
	/** // ������� */
	std::string playerName;		
	/** // �ۼ��˺��� */
	int damage;		
	/** // �ۼ��˺��ٷֱ�(0��100) */
	int damagePercent;

protected:
private:
};