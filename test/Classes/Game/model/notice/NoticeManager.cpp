#include "NoticeManager.h"
#include "NoticeType.h"
#include "manager/TimerManage.h"
#include "manager/CDManage.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"


const ccColor3B COLOR_NAME = ccc3(255, 153, 0);
const ccColor3B COLOR_GREEN = ccc3(57, 255, 11);
const ccColor3B COLOR_RED = ccc3(255, 0, 0);
const ccColor3B COLOR_YELLOW = ccc3(255, 255, 0);
const ccColor3B COLOR_ORANGE = ccc3(255, 204, 0);
const ccColor3B COLOR_DEL = ccc3(255, 90, 0);
const ccColor3B COLOR_NORMAL = ccc3(255, 255, 255);

NoticeManager* g_pNoticeManager = 0;


		

NoticeManager::NoticeManager()
{
	totlecountSit = 0;
}

NoticeManager::~NoticeManager()
{
	_noteDic.clear();
}

bool NoticeManager::init()
{
	if (!LayerNode::init())
		return false;

	_noteDic[ADD_FRI] = &_freiendArr;
	/*
	_noteDic[FARM_FIGHT_NOTE] = _farmArr;
	_noteDic[TRADER_NOTE] = _traderArr;
	_noteDic[AREANA_NOTE] = _arenaArr;		
	_noteDic[PK_NOTE] = _pkArr;	
	_noteDic[ARMY_NOTE] = _armyArr;
	*/
    return false;
}

NoticeManager::NoteElmArr* NoticeManager::getArrByType(int type)
{
	std::map<int, NoticeManager::NoteElmArr*>::iterator it;
	if ((it = _noteDic.find(type)) != _noteDic.end())
	{
		return it->second;
	}

	return 0;
}

void NoticeManager::delItemStr(int type, int sit)
{
	std::map<int, NoticeManager::NoteElmArr*>::iterator it;
	if ((it = _noteDic.find(type)) != _noteDic.end())
	{
		NoticeManager::NoteElmArr* itemarr = it->second;
		if (itemarr)
		{
			NoticeManager::NoteElmArr::iterator it2;
			for (it2 = itemarr->begin(); it2 != itemarr->end(); it2++)
			{
				if (it2->sit == sit)
				{
					itemarr->erase(it2);
					return;
				}
			}
		}
	}
}

void NoticeManager::noticeBuilder(std::string name, int type, char* obj, int silver, int gold, int farmType, int payoff)
{
	NM_ELM_INFO string;
	
	string.data[0] = TimerManage::formatServerTimeToDate(CDManage::Instance()->getServerTime());
	string.color_data[0] = COLOR_NORMAL;
	switch (type)
	{
	case ADD_FRI:
		{
			char data1[20];
			sprintf(data1, "[%s]", name.c_str());
			string.data[1] = data1;
			string.color_data[1] = COLOR_NAME;

			string.data[6] = name;

			char data2[10];
			sprintf(data2, ValuesUtil::Instance()->getString("NTC005").c_str(), silver);
			string.data[2] = data2;
			string.color_data[2] = COLOR_GREEN;

			string.data[3] = ValuesUtil::Instance()->getString("NTC004");
			string.color_data[3] = COLOR_NORMAL;

			char data4[20];
			sprintf(data4, "%s", ValuesUtil::Instance()->getString("NTC002").c_str());
			string.data[4] = data4;
			string.color_data[4] = COLOR_ORANGE;

			char data5[20];
			sprintf(data5, "%s", ValuesUtil::Instance()->getString("NTC003").c_str());
			string.data[5] = data5;
			string.color_data[5] = COLOR_DEL;
			
			string.sit = totlecountSit++;
			_freiendArr.push_back(string);
		}
		break;
	}
}
