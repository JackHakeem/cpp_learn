#pragma once

#include "BaseType.h"
/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-�ֿ�
WMSG_EGG_DEPOT = 0x40B
����� ->�ͻ���, ���ṹ:
Uint16		����
	Uint8	����(1װ����/2Ӷ����/3��Դ��)
	Uint8	Ʒ��(1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ)
	Uint8	״̬(1�ѿ�/2δ��)
	Uint32	����ID(����װ��ID,Ӷ��ID,��ƷID)
	Uint32	��������(װ������,Ӷ������,��Ʒ����)
	Uint32	�ѵ���

 * @data 2012-3-26 ����03:46:12 
 * 
 */ 

struct SCMD40BNode
{
	SCMD40BNode()
	{
		memset(this, 0, sizeof(SCMD40BNode));
	}

	int8 a_type;
	int8 b_quailty;
	int8 c_state;
	int32 d_goodsId;
	int32 e_goodsNum;
	int32 f_num;
};