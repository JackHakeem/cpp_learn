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

 * @data 2012-3-26 ����03:25:47 
 * 
 */ 

struct SCMD401Node1
{
	SCMD401Node1()
	{
		memset(this, 0, sizeof(SCMD401Node1));
	}

	int8 a_type;
	int8 b_quality;
	int8 c_state;
	int32 d_goodsId;
	int32 e_goodsNum;
	int32 f_num;
};