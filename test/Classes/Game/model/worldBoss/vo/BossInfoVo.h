#pragma once

class BossInfoVo
{
public:
	BossInfoVo() : maxHP(0) , currentHP(0) , totalDamageLow(0) , totalDamageHigh(0)
	{

	}
	~BossInfoVo(){};

public:
	/** ���Ѫ�� -1��ʾδ֪ */
	int maxHP;		
	/** ��ǰѪ��-1��ʾδ֪ 0��ʾBOSS���� */
	int currentHP;
	/** ��ǰ���˺�-��λ*/
	uint32 totalDamageLow;
	/** ��ǰ���˺�-��λ*/
	uint32 totalDamageHigh;

protected:
private:
};