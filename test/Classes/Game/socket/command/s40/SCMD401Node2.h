#pragma once

#include "BaseType.h"
/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-����ʷ��¼
WMSG_EGG_HISTORY = 0x401
����� -> �ͻ���, ���ṹ:
Uint8		��Ը�Ҹ���
Uint16		���˼�¼��
	Uint8	����(1װ����/2Ӷ����/3��Դ��)
	Uint8	Ʒ��(1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ)
	Uint8	״̬(1�ѿ�/2δ��)
	Uint32	����ID(����װ��ID,Ӷ��ID,��ƷID)
	Uint32	��������(װ������,Ӷ������,��Ʒ����)
	Uint32	����
Uint16		������Ҽ�¼��
	String	�������
	Uint8	����(1װ����/2Ӷ����/3��Դ��)
	Uint8	Ʒ��(1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ)
	Uint8	״̬(1�ѿ�/2δ��)
	Uint32	����ID(����װ��ID,Ӷ��ID,��ƷID)
	Uint32	��������(װ������,Ӷ������,��Ʒ����)
	Uint32	����

 * @data 2012-3-26 ����03:26:08 
 * 
 */ 

struct SCMD401Node2
{
	SCMD401Node2()
	{
		a_name = "";
		b_type = 0;
		c_quality = 0;
		d_state = 0;
		e_goodsId = 0;
		f_goodsNum = 0;
		g_num = 0;
	}

	std::string a_name;
	int8 b_type;
	int8 c_quality;
	int8 d_state;
	int32 e_goodsId;
	int32 f_goodsNum;
	int32 g_num;
};