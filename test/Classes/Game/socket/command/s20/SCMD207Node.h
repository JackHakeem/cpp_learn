#ifndef _SCMD207NODE_H_
#define _SCMD207NODE_H_

#include "BaseType.h"
	/**
	 *�鿴�������б�
	GMSG_COMMU_FRIENDS_BLACK_LIST = 0x207 (),			
	�����->�ͻ���, ���ṹ
	Short��				��ҳ��,
	Short��				��ǰҳ��,
	Short��				��ҳ�����,
		Int��			���ID,	
		String��		�������,
		Short��			ˮ���ȼ�,
		Short��			�������ɫӶ��ID,
		Byte��			����״̬		0 �C ���� / 1 �C ����  
	 * @author bobolive
	 * 
	 */	
struct SCMD207Node
{
	SCMD207Node()
	{
		a_ID = 0;
		b_name = "";
		c_mainLev = 0;
		d_hiredID = 0;
		f_offLine = 0;
	}

	int32 a_ID;
	/**��������*/
	std::string b_name;
	/**������֮ˮ���ȼ�*/
	int8 c_mainLev;
	int16 d_hiredID;
	int8 f_offLine;
};

#endif