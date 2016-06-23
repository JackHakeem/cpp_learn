#include "SCMD443.h"
#include "socket/network/GameServerSocket.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/scene/SceneMediator.h"

bool	SCMD443::Read()
{
	a_wave = readUint();
	b_servertime = readUint();
	short c_monsterInfoNum = readShort();
	for (int i = 0; i < c_monsterInfoNum; i++)
	{
		uint8 monsterState = readByte();
		c_monsterInfo.push_back(monsterState);
	}

	return true;
}

int32 	SCMD443::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD443Handler::Execute(this) ;
}


uint32 SCMD443Handler::Execute(SCMD443* pPacket)
{
	if (!pPacket) return 1;

	SceneMediator* m = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	if (m)
	{
		for (int i = 0; i < pPacket->c_monsterInfo.size(); i++)
		{
			int index = 9001 + i;
			if (pPacket->c_monsterInfo[i] == 0)
			{			
				m->showNPC((char*)&index, false);
			}
			else
			{
				m->showNPC((char*)&index, true);
				cocos2d::ccColor3B namecolor;
				switch (pPacket->c_monsterInfo[i])
				{
				case 1://blue
					namecolor = ccc3(85,67,248);
					break;
				case 2://purple
					namecolor = ccc3(168,13,251);
					break;
				case 3://orange
					namecolor = ccc3(255,175,9);
					break;
				case 4://red
					namecolor = ccc3(248,52,18);
					break;
				default:
					namecolor = ccc3(248,248,248);
					break;
				}
				m->NPCColor((char*)&index, namecolor);
			}
		}	
	}

	{
		Number openTime = pPacket->b_servertime;

		time_t pTimeT = (time_t)openTime;
		struct tm* pTm = localtime(&pTimeT);

		if ( !pTm )
		{
			return 1;
		}
	
		int year = pTm->tm_year + 1900;	//Local time
		int month = pTm->tm_mon + 1;
		int day = pTm->tm_mday;
		int hour = pTm->tm_hour;
		int minute = pTm->tm_min;
		int second = pTm->tm_sec;
		char shows[150];
		sprintf(shows, "GONG servertime %d-%02d-%02d  %02d:%02d~%02d:%02d",  year, month, day, hour, minute,
			hour, minute+30);

		//LangManager::msgStr(shows);
	}

	return 0;
}