#ifndef _GuildLevInfo_H_
#define _GuildLevInfo_H_

#include "BaseType.h"

class GuildLevInfo
{
public:
	GuildLevInfo()
	{
		lev = 0;
		needGold = 0;
		incMember = 0;
	}
	~GuildLevInfo(){}
public:
	uint lev;				//���ᵱǰ�ȼ�
	uint needGold;			//��������
	uint incMember;			//�������ӵ���������
};

#endif