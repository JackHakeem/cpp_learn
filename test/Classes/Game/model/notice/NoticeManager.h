#pragma once

#include "BaseType.h"

enum NM_ELM_FLAG
{
	
};

struct NM_ELM_INFO
{
	int sit;
	std::string data[8];
	cocos2d::ccColor3B color_data[8];

};

class NoticeManager : public LayerNode
{
public:
	enum
	{
		ADD_FRI =1,
		BLESS_FRI =6,
		AREANA_NOTE =4,
		FARM_FIGHT_NOTE =2,
		PK_NOTE =5,
		TRADER_NOTE =3,
		ARMY_NOTE =7,
		CLOSE_NOTE =99,
	};
public:
	NoticeManager();
	~NoticeManager();
	
	bool init();
public:
	void noticeBuilder(std::string name,int type, char* obj=0, int silver=0, int gold= 0,int farmType=0,int payoff=0);


public:
	typedef	std::vector<NM_ELM_INFO> NoteElmArr;

	NoticeManager::NoteElmArr* getArrByType(int type);
	void delItemStr(int type, int sit);

	int newTotleCountSit() {return totlecountSit++;}
public:
	NoteElmArr _freiendArr;//好友信息
	NoteElmArr _arenaArr;   //竞技场
	std::map<int, NoticeManager::NoteElmArr*> _noteDic;
	int totlecountSit;
};

extern NoticeManager* g_pNoticeManager;