#pragma once
#include "mvc/Mediator.h"

class SCMD28B;
class SCMD19A;
class SCMD19B;

class BroadcastMediator : public Mediator
{
public:
	BroadcastMediator();
	~BroadcastMediator();
	virtual void handleNotification( int M2Vcmd, char* data );

	void sockSysBroadcastRecived(SCMD19A * data);
	void sockSysNoticeRecived(SCMD19B * data);
	void sockHeroNoticeRecived(SCMD28B * data);

	void heroBroadcast(SCMD28B *data);


public:
	std::list<std::string> splitStringByCharacter( string o_str, string sCharacter );
	int string2Int(std::string str);
public:
	enum
	{
		BROADCAST_ACHIVE		= 1,		//1 �C �ɾ�
		BROADCAST_RESPONSE		= 2,		//2 �C ʹ��
		BROADCAST_OBJECTS		= 3,		//3 �C ��Ʒ
		BROADCAST_ARENA_WINS	= 4,		//4 �C ��������ʤ
		BROADCAST_FIRST_FIN	= 5,		//5 �C �׸����
		BROADCAST_EQUIP_GIVE	= 6,		//6  - ��ɫ��������Ʒ����(������Ƭ)
		BROADCAST_EQUIP_MAKE	= 7,		//7  - ��ɫ��������Ʒ�ϳ�
		BROADCAST_PAOSHANG		= 8,		//8  - ���̴�ɣ����¼�
		BROADCAST_JIESHANG		= 9,		//9  - ���̴󱩻�
		BROADCAST_TONGSHANG	= 10,	//10 - ͨ�̴󱩻�
		BROADCAST_FIRST_CHARGE	= 11,	//11 - �׳�
		BROADCAST_WORLD_BOSS	= 12,	//12 - ����Boss
		BROADCAST_ARENA_TOP10	= 13,	//13 - ������ǰ10������ս
	};
protected:
private:
};