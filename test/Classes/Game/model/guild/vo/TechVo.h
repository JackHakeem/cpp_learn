#ifndef _TechVo_H_
#define _TechVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"

class TechVo: public GuildVoBase
{
public:
	TechVo()
	{
		id = 0;
		name = "";
		level = 0;
		icon = "";
		des = "";
		progress = 0;
		moneyNeed = 0;
		moneyHave = 0;
		isDefault = false;
	}
	virtual  ~TechVo(){}
public:
	int id;  			// �Ƽ�Id
	string name; 	// �Ƽ�����
	int level ;  		// �Ƽ��ȼ� 
	string icon;		//�Ƽ�ͼ��
	string des;		//�Ƽ���������
	int progress;  	// ����
	int moneyNeed ; 	// ��Ҫ����
	int moneyHave ;  	// �������� 
	bool isDefault;	//�Ƿ�Ĭ�ϿƼ�
};

#endif