#ifndef _RANKITEMVO_H_
#define _RANKITEMVO_H_

#include <string>

struct RankItemVo
{
	RankItemVo()
	{
		trend = 1;
	}
	/** �������� */
	int type;
	/** ������� */
	int rank;
	/** ���ID */
	int playerId;
	/** ����ԭ��ID */
	int roleId;
	/** ���ǵȼ� */
	int lev;
	/** ������� */
	std::string name;
	/** ������(���޼��빫�ᣬ��Ϊ�մ�) */
	std::string guild;
	/** װ������ / ������� / ս���� */
	int grade;
	/** ���� */
	int trend;
};

#endif
