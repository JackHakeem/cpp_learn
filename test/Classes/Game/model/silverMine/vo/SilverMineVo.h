#pragma once

#include "BaseType.h"

class SilverMineVo
{
public:
	SilverMineVo():id(0), campId(0),online(0),isDouble(false)
	{
	}
	int id;				// ��ID
	int campId;	 		// ��ӪID
	int online;			// �ÿ�ǰ����� 
	bool isDouble;	// �Ƿ�˫���� 
};