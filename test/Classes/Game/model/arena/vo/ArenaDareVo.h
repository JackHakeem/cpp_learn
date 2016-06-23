#ifndef _ARENADAREVO_H_
#define _ARENADAREVO_H_

#include "BaseType.h"

class ArenaDareVo
{
public:
	ArenaDareVo()
	{
		accountId = 0;
		crystalLev = 0;
		roleId = 0;
		rankings = 0;
		std::string roleName = "";
		threat = 0;
	}

	int32 accountId;		//�˺�ID
	int32 crystalLev;		//ˮ���ȼ�
	int32 roleId;			//��ɫԭ��ID
	int32 rankings;			//��λ�ȼ�
	std::string roleName;	//��ɫ��
	int32 threat;			// ��в��		 
};

#endif
