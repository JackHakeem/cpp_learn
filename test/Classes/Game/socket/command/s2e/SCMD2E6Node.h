#pragma once
#include "BaseType.h"
/**
 * ������Ӫ��Ϣ���飺
	Uint32	����ID
	Uint32  ��ǰ����� 
	int8	��ǰռ����ӪID��-1���տ�0~2����ӪID��
	uint8	�Ƿ�˫����0����1���ǣ�
 */

class SCMD2E6Node
{
public:
	SCMD2E6Node()
	{
		memset(this, 0, sizeof(SCMD2E6Node));
	}
	uint32 a_mineId;
	uint32 b_online;
	int8 c_mineType;
	int8 d_isDouble;
};