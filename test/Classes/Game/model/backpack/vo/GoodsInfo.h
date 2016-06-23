#ifndef _GOODSINFO_H_
#define _GOODSINFO_H_
#include "BaseType.h"	
#include "model/com/GoodsToolTips.h"

class GoodsInfo
{
public:
	GoodsInfo()
	{
		id = 0;			//��ƷΨһ���
		goodId = 0;		//����ID ��Ʒ���
		sitGrid = 0;		//��������
		name = "";		//����
		type = 0;		//���� 	2 
		subtype = 0;		//������
		equip_type = 0;	//(װ����λ�� ͷ.��...))
		number = 0;		//����
		quality = 0;		//Ʒ��
		strengthen = 0;	//ǿ����
		holds = 0;		//����
		//explain = 0;	//˵�� kkk
		stamina = 0;		//ħ�������
		wrist = 0;			//ħ��������
		intellect = 0;		//ħ��������
	}
	~GoodsInfo()
	{
        //SAFE_DELETE( explain );
	}
	uint32 id; // items only Numbers
	int32 goodId; // type ID items Numbers
	int32 sitGrid; // grid coordinates
	std::string name; // name
	int32 type; // type 2
	int32 subtype; // child type
	int32 equip_type; // (equipment position. A head...) )
	int32 number; // quantity
	int32 quality; // quality
	int32 strengthen; // strengthen number
	int32 holds; // make hole number
	SUBGOODSTIPS explain; // that//kkk
	int32 stamina; // enchantment physical number
	int32 wrist; // enchantment number of achievement
	int32 intellect; // enchantment number of achievement
};

#endif