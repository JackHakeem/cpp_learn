#pragma once

#include "BaseType.h"

struct EggInfo
{
	EggInfo()
	{
		eggId = 0;
		type = 0;
		quality = 0;
		state = 0;
		goodsId = 0;
		goodsNum = 0;
		num = 0;
		name = "";
	}

	int32 eggId;			// ����Id������˵���ͻ���Ҫ�Լ����ݷ���˴�����������������Ϊ������Id��
	int32 type;			// �������ͣ�1װ����/2Ӷ����/3��Դ����
	int32 quality;		// ����Ʒ�ʣ�1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ��
	int32 state;			// ����״̬��1�ѿ�/2δ����
	int32 goodsId;		// ��Ʒԭ��Id
	int32 goodsNum;		// ��Ʒ����
	int32 num;			// ��Ʒ�ѵ���
	std::string name;	// �����������ʼ�����������ʷ������Ϣ��ʱ���õ���	
};