#ifndef _RINGVO_H_
#define _RINGVO_H_

class RingVo
{
public:
	RingVo()
	{
		accountId = 0;
		roleId = 0;
		crystalLev = 0;
		pvpRankId = 0;
		pvpRankType = 0;
		awardNum = 0;
		std::string roleName = "";
	}

	int32 accountId;		//�˺�ID
	int32 roleId;			//Ӷ��ԭ��ID
	int32 crystalLev;		//ˮ���ȼ�
	int32 pvpRankId;		//��̨����
	int32 pvpRankType;		//��̨����
	int32 awardNum;			//��������
	std::string roleName;	//��ɫ��
};

#endif
