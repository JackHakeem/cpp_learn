#ifndef _TASK_BEHAVIOR_TYPE_H_
#define _TASK_BEHAVIOR_TYPE_H_

class TaskBehaviorType
{
public:
	enum
	{
		TASK_BEHAVIOR_STRENGTHEN = 1,    	// ǿ��
		TASK_BEHAVIOR_STRENGTHEN_CD,		// ǿ����CD
		TASK_BEHAVIOR_RECRUIT,				// ��ļ
		TASK_BEHAVIOR_FORMATION,			// ����Ӷ������
		TASK_BEHAVIOR_PASSIV_SKILL,			// ������������
		TASK_BEHAVIOR_CRYSTAL,		     	// ˮ������
		TASK_BEHAVIOR_TRAIN,				// ѵ��
		TASK_BEHAVIOR_SPEEDUP,				// ͻ��
		TASK_BEHAVIOR_FOSTER,				// ����	
		TASK_BEHAVIOR_IMPOSE,				// ����
		TASK_BEHAVIOR_EQUIP_SKILL,			// װ������	
		TASK_BEHAVIOR_ADD_FRIEND,			// �Ӻ���

		TASK_BEHAVIOR_WIND_CRYSTAL,			// ��֮ˮ������
		//TASK_BEHAVIOR_MAINROLE_LV10 = 14,		// ����������10��
		TASK_BEHAVIOR_SUBMIT_ENT_TASK = 15,		// ���һ��ί������
		TASK_BEHAVIOR_INTO_GUILD,			// ����򴴽�һ������
		TASK_BEHAVIOR_BLESS_FRIEND,			// ף������
		TASK_BEHAVIOR_SUBMIT_DAYLYTARGET,	 // ���һ��ÿ��Ŀ��
		TASK_BEHAVIOR_COMPLET_STAR,			// (ÿ��Ŀ��)���һ����
		TASK_BEHAVIOR_JJC_FIGHT,			// ����һ�ξ�����ս��
		TASK_BEHAVIOR_RF_FIGHT,				// ����һ����Դ��ս��
		TASK_BEHAVIOR_DELEGATE,				// ���һ��ί��
		TASK_BEHAVIOR_TRADE,				// ����һ������
		TASK_BEHAVIOR_DUNGEON_FIGHT,		// ����һ�θ�����ս
		TASK_BEHAVIOR_GROUP_WAR,			// ����һ�ξ���ս
	};
};
#endif