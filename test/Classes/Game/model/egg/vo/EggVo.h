#pragma once

#include "BaseType.h"

struct EggVo
{
	EggVo()
	{
		type = 0;
		smallType = 0;
		quality = 0;
		tips = "";
	}

	int32 type;			// ������(1װ����2Ӷ����3��Դ��)
	int32 smallType;		// ��Դ��С��(1���2����3����4����5����6ħʯ)
	int32 quality;		// Ʒ��(1��2��3��4��101��102С)
	std::string tips;		// �ͻ���������������tips
};