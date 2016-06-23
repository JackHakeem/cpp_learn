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
		BROADCAST_ACHIVE		= 1,		//1 – 成就
		BROADCAST_RESPONSE		= 2,		//2 – 使命
		BROADCAST_OBJECTS		= 3,		//3 – 物品
		BROADCAST_ARENA_WINS	= 4,		//4 – 竞技场连胜
		BROADCAST_FIRST_FIN	= 5,		//5 – 首个完成
		BROADCAST_EQUIP_GIVE	= 6,		//6  - 紫色或以上物品掉落(包括碎片)
		BROADCAST_EQUIP_MAKE	= 7,		//7  - 紫色或以上物品合成
		BROADCAST_PAOSHANG		= 8,		//8  - 跑商达成３星事件
		BROADCAST_JIESHANG		= 9,		//9  - 劫商大暴击
		BROADCAST_TONGSHANG	= 10,	//10 - 通商大暴击
		BROADCAST_FIRST_CHARGE	= 11,	//11 - 首充
		BROADCAST_WORLD_BOSS	= 12,	//12 - 世界Boss
		BROADCAST_ARENA_TOP10	= 13,	//13 - 竞技场前10名争夺战
	};
protected:
private:
};