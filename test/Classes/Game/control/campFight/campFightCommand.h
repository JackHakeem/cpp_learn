#ifndef _CAMPFIGHTCOMMAND_H_
#define _CAMPFIGHTCOMMAND_H_

#include "mvc/SimpleCommand.h"
#include "model/campFight/campFightProxy.h"
//#include "view/campFight/CampFightMediator.h"
#include "socket/command/s45/SCMD45B.h"
#include "socket/command/s45/SCMD459.h"
//#include "model/ranking/RankingProxy.h"
//#include "socket/command/s25/SCMD25C.h"
//#include "socket/command/s25/SCMD25E.h"
//#include "model/ranking/vo/RankItemVo.h"

class CampFightCommand : public SimpleCommand
{
public:
	/*enum
	{
	REQUEST_RANKING_LIST = 0,
	UPDATE_RANKING_LIST,
	UPDATE_EQUIPS_INFO,
	REQUEST_SELECTED_EQUIP_INFO,
	};*/
	enum
	{
		UPDATE_CAMPFIGHT_INFO = 0,
		UPDATE_MY_INFO,
		CAMPFIGHTCOMMAN_END,
	};
public:
	CampFightCommand();
	~CampFightCommand();
	virtual void execute(int32 command, char* data);
private:
	//void updateRankingList(SCMD25C* packet);
	//void updateEquipsInfo(SCMD25E* packet);
	//void requestRankingList(int type);
	//void requestSelectedEquipInfo(int position);
	void UpdateCampFightInfo(SCMD45B* pPacket);
	void UpdateMyInfo(SCMD459* pPacket);
private:
	//RankingProxy* _pRankProxy;
	CampFightProxy*    m_pCampFightProxy;
	//CampFightMediator* m_pCampFightMediator;
};

#endif