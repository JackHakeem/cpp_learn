#ifndef _SCMD205NODE_H_
#define _SCMD205NODE_H_

#include "BaseType.h"
/**
	 *�鿴�Ƽ������б�
	GMSG_COMMU_FRIENDS_SAME_LEVEL = 0x205 (),			
	�����->�ͻ���, ���ṹ
	Short��				��ҳ����
	Short��				��ǰҳ�룬
	Short��				�����,
		Int��			���ID,	
	    Short��			�������ɫӶ��ID,
		String��		�������,
		byte��			ˮ���ȼ�, 
	 * @author bobolive
	 * 
	 */	
struct SCMD205Node
{
	SCMD205Node()
	{
		a_ID = 0;
		b_hiredID = 0;
		c_name = "";
		d_mainLev = 0;
	}
	int32 a_ID;
	int16 b_hiredID;
	std::string c_name;
	/**��֮ˮ���ȼ�*/
	int8 d_mainLev;
};

#endif