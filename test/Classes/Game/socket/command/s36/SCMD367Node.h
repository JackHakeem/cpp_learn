#pragma once
/**
 * ����ս�����������
	Uint8	������0-9��
	Uint32	���ID
	String	�������
	Uint32	�ɼ�������
 */
#include "BaseType.h"

struct SCMD367Node
{
	SCMD367Node()
	{
		a_rank = 0;
		b_playerId = 0;
		c_playerName = "";
		d_silver = 0;
	}
	int8 a_rank;
	uint32 b_playerId;
	std::string c_playerName;
	uint32 d_silver;
};