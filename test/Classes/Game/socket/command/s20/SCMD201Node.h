#ifndef _SCMD201NODE_H_
#define _SCMD201NODE_H_

#include "BaseType.h"
	/**
	 * GMSG_COMMU_FRIENDS_LIST = 0x201 (),			
	 �����->�ͻ���, ���ṹ
	 Short��				��ҳ��,
	 Short��				��ǰҳ��,
	 Short��				��ҳ�����,
		 Int��			���ID,
		 Short��			�������ɫӶ��ID,
		 String��		�������,
		 Byte��			��֮ˮ���ȼ�,
		 Byte��			����״̬		0 �C ���� / 1 �C ���� 
		 Byte��			�ܷ�ף����־	0 �C ���� / 1 �C ����
	 * @author bobolive
	 * 
	 */	
struct SCMD201Node
{
	SCMD201Node()
	{
		a_ID = 0;
		b_hiredID = 0;
		c_name = "";
		d_mainLev = 0;
		e_offLine = 0;
		f_fCrystal = 0;
	}

	int32 a_ID;
	int16 b_hiredID;
	/**��������*/
	std::string c_name;
	/**������֮ˮ���ȼ�*/
	int8 d_mainLev;
	int8 e_offLine;
	/**��֮ˮ���ȼ��Ƿ�ﵽף��Ҫ��*/
	int8 f_fCrystal;
};

#endif