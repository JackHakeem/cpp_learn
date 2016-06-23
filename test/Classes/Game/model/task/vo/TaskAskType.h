#ifndef _TASK_ASK_TYPE_H_
#define _TASK_ASK_TYPE_H_

class TaskAskType
{
public:
	enum
	{
		TASK_ASK_TYPE_KILL_MONSTER = 0,		// ɱ��ָ�������
		TASK_ASK_TYPE_FALL_ITEM,			// ɱ�ֵ���������Ʒ
		TASK_ASK_TYPE_TALK,					// �Ի�
		TASK_ASK_TYPE_USE_ITEM,				// ʹ����Ʒ
		TASK_ASK_TYPE_DRESS,				// ��װ��
		TASK_ASK_TYPE_NEED_ITEM,			// ��ɱ�ֻ����Ʒ���ﵽҪ�󣨲��۳���Ʒ��
		TASK_ASK_TYPE_GET_ITEM,				// ��ɱ�ֻ����Ʒ���ﵽҪ�󣨿۳���Ʒ��
		TASK_ASK_TYPE_BEHAVIOR,				// ������Ϊ����

		TASK_ASK_TYPE_CRYSTALUP,			// ����ȼ�����	

		TASK_ASK_TYPE_ACHIRVE_FORMATION,	// N�����͵���N��
		TASK_ASK_TYPE_ACHIRVE_PASSIVE_SKILL,// N���������ܵ���N��
		TASK_ASK_TYPE_KILL_GET_ITEM,		// ɱ�ֲ�ӵ����Ʒ(�����Ƿ��ǵ���)

	};
};
#endif