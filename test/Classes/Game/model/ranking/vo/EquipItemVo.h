#ifndef _EQUIPITEMVO_H_
#define _EQUIPITEMVO_H_

#include <string>

struct EquipItemVo
{
	/** װ��ԭ��ID */
    int id;
	/** װ������*/
	std::string name;
	/** ǿ���ȼ� */
    int lev;
	/** װ������ */
    int type;
	/** װ��Ʒ�� */
    int quality;
	/** ��Ʒ��ʾ */
	int stamina;
	int wrist;
	int intellect;
};

#endif

