#ifndef _NEWHAND_CONST_H_
#define _NEWHAND_CONST_H_
#include "manager/CDManage.h"
#include "BaseType.h"
#include "utils/Singleton.h"

USING_NS_CC;

class NewhandConst : public Singleton<NewhandConst>
{
public:
	enum
	{
		//���ֽ׶ο����ĸ��ֹ���
		ENABLE_TRAIN_CD 		= 51,//ѵ��cd
		ENABLE_STRENG_CD	 	= 55,//ǿ��cd
		ENABLE_WASH 			= 70, //����������ť����
		ENABLE_IDENTIFY 		= 75, //����������ť����
		ENABLE_RECRUIT 			= 71, //����Ӷ����ļ
		ENABLE_Appoint 			= 72, //����ί�ɺ���
		ENABLE_TRADER  			= 74, ///��������
		ENABLE_SPIRIT  			= 76, ///�������
		ENABLE_TRAIN  			= 77, ///����ѵ��tab��ť

		//���������ĸ����¼�
		EVENT_OPEN_GIFT  							= 101, //�����
		EVENT_TRIAN_SELECT 						 	= 102, //ѡ��ѵ������
		EVENT_TRIAN_START   						= 103, //��ʼѵ��
		EVENT_CRY_WIND  							= 104, //������֮ˮ��
		EVENT_OPEN_PASSIVE  						= 105, //�򿪱��������б�
		EVENT_OPEN_WASH 							= 106, //��ϴ���Դ���
		EVENT_WASH_TYPE 							= 107, //��ǿϴ���Է�ʽ
		EVENT_OPEN_ARENA 							= 108, //�򿪾�����
		EVENT_OPEN_FARM 							= 109, //�򿪾�����
		EVENT_DEPLOY_MV_ROLE_SIT					= 110, //����--��������λ�ö�������
		EVENT_DEPLOY_OP_ROLE_SIT 					= 111, //����--��������λ�ò���
		EVENT_DEPLOY_MV_CHANGE_TYPE 				= 113, //����--�������Ͷ�������
		EVENT_DEPLOY_OP_CHANGE_TYPE 				= 115, //����--�������Ͳ���
		EVENT_DEPLOY_OP_ACTIVE 						= 117, //����--�������Ͳ���
		EVENT_STRENG_SELECT_MERC 					= 119, //ǿ��--ѡ��������
		EVENT_STRENG_SELECT_EQUIP 					= 121, //ǿ��--ѡ������Ʒ
		EVENT_MAP_AWARD_POP 						= 122, //ͨ�ؽ���--�������
		EVENT_MAP_AWARD_GET 						= 123, //ͨ�ؽ���--��ȡ����


		EVENT_LEVY_GET										= 201, // ��ȡ�ͽ����
		EVENT_ORE_OVER										= 203, // ˮ��԰�ӹ����
		EVENT_ARENA_OVER									= 205, // ��������һ�����
		EVENT_TRAIN_OVER									= 207, // ѵ�����

		EVENT_GOLDLEVY_GET							= 501, // �����������
		EVENT_ENTRANCE_OVER							= 502, // ������������
		EVENT_CHALLEGE_COPY_OVER			= 503, // ��ս����������
		EVENT_TAOFA_OVER									= 504, // �ַ�������
		EVENT_EGG_OVER										= 510, // ��Ը�����
		EVENT_DAILYTASK_OVER						= 515, // �ճ��������

		EVENT_FRIEND_OVER								= 803, // ����������
		EVENT_UPFORMATION_OVER				= 806, // ��ϰ�������
		EVENT_GUILD_OVER									= 809, // �����������
		EVENT_PEIYANG_OVER								= 812, // �����������

		//���������ĸ���λ�ñ��
		LOC_POP = 10,//���ֵ����򣬶Ի���
		LOC_TASK = 11,//����׷����
		LOC_MAIN = 12,//������
		LOC_CD = 13,//cd��
		LOC_SEC = 14,//�ε���
		LOC_MAP = 15,//С��ͼ��ť
		LOC_WORLD = 16,//��ͼ���
		LOC_CHILD = 17,//�ӵ�ͼ���
		LOC_DEFAULT = 18, // Default loc should init a CCPoint.
		LOC_VSCROLL = 19, // Default loc should init a CCPoint.


		//����Ϊ�����������ֶ���ı�ţ�����������!
		ITEM_COM_WIN			= 0,//������ʱ������
		ITEM_BAG_CLOSE 			= 1,//�رձ�����ť
		ITEM_FIGURE_CLOSE 		= 2,//�رս�ɫ��ť
		ITEM_WORLD_MAP 			= 3,//�����ͼ��ť
		ITEM_STRENG_UP 			= 4,//ǿ����ť
		ITEM_RECRUIT 			= 5,//��ļ
		ITEM_FORMATION_HEAD 	= 6,//����ͷ��
		ITEM_FORMATION_SIT6 	= 7,//����λ��
		ITEM_TRAIN_START 		= 8,//��ʼѵ��
		ITEM_TRAIN_EXP 			= 9,//ͻ�ɰ�ť
		ITEM_PASSIVE_PIC 		= 13,//��������
		ITEM_PASSIVE_LIST 		= 14,//���������б�
		ITEM_LEVY 				= 15,//��ȡ��ť
		ITEM_UPSKILL 			= 16,//����������ť
		ITEM_WASH 				= 17,//ϴ���԰�ť
		ITEM_OPEN_GIFT 			= 18,//�����
		ITEM_PUT_ON 			= 19,//����װ��

		ITEM_CRYSTAL_UP 		= 10,//ˮ��������ť
		ITEM_CRYSTAL_WIND 		= 11,//��֮ˮ��
		ITEM_CRYSTAL_CLOSE 		= 12,//�ر�ˮ��
		ITEM_CRYSTAL_FIRE 		= 20,//��֮ˮ��
		ITEM_CRYSTAL_EARTH 		= 21,//��֮ˮ��
		ITEM_CRYSTAL_WATER 		= 22,//ˮ֮ˮ��

		ITEM_DEPLOY_IMD 		= 23,//��������ť
		ITEM_FORMATION_SIT5 	= 24,//����λ��
		ITEM_FORMATION_CLIP13 	= 25,//������ͼ��
		ITEM_FORMATION_ACTIVE 	= 26,//�������Ͱ�ť

		ITEM_MAP_AWARD_BTN 		= 31,//��ȡͨ�ؽ�����ť

		ITEM_TRAIN_CLOSE 		= 81,//�ر�ѵ����ť
		ITEM_STRENG_CLOSE 		= 82,//�ر�ǿ����ť
		ITEM_FRIEND_CLOSE 		= 83,//�رպ��Ѱ�ť
		ITEM_FORMATION_CLOSE 	= 84,//�رղ���ť
	};

	int getCDType(int value)
	{
		switch(value){
		case 50: return CDManage::CRYSTAL_0;
		case 51: return CDManage::TRAINING;
		case 52: return CDManage::BLESSING;
		case 53: return CDManage::FIGHT;
		case 54: return CDManage::COLLECTION;
		case 55: return CDManage::STRENGTHEN;
		default: return -1;
		}
	}

	std::map<int, CCNode *> _itemDic;

	void registerItem(int id, CCNode *pNode)
	{
		_itemDic.insert(make_pair(id, pNode));
	}

	CCNode *getItem(int id)
	{
		std::map<int, CCNode *>::iterator it = _itemDic.find(id);
		if(it != _itemDic.end())
		{
			CCNode *pNode = it->second;
			return pNode;
		}
		return NULL;
	}
};
#endif