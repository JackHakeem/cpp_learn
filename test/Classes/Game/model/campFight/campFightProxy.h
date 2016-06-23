#ifndef _CAMPFIGHTPROXY_H_
#define _CAMPFIGHTPROXY_H_

#include "mvc/Proxy.h"
#include <vector>
#include "model/campFight/vo/campFightVo.h"
//#include "BaseType.h"

class CampFightProxy : public Proxy
{
public:
	/*enum
	{
	EQUIP_RANKING = 0,
	RENOWN_RANKING,
	CAPACITY_RANKING,
	PROCESS_RANKING,
	MAX_RANKING_TYPE,
	};*/
	CampFightProxy();
	~CampFightProxy();
	void UpdateCampFightInfo(TCampInfo* ice_, TCampInfo* fire_);
	void UpdateMyInfo(TMyCampFightInfo* m_);

	const TCampInfo* GetIceCampFightInfo(){return m_pIceCity;}
	const TCampInfo* GetFireCampFightInfo(){return m_pFireCity;}
	const TMyCampFightInfo* GetMyInfo(){return m_pMyInfo;}

	inline bool RemoveCampInfoCache(TCampInfo* c_);
	/*void updateRankList();
	void updateEquipments(int rankType, int playerId, const std::vector<EquipItemVo>& vo);

	int rankType;
	std::vector<RankItemVo> rankItems[MAX_RANKING_TYPE];
	std::map<int, std::vector<EquipItemVo> > equipments[MAX_RANKING_TYPE];
	int myRank[MAX_RANKING_TYPE];*/
private:
	TCampInfo* m_pIceCity;
	TCampInfo* m_pFireCity;
	TMyCampFightInfo* m_pMyInfo;
};
bool CampFightProxy::RemoveCampInfoCache(TCampInfo* c_)
{
	if (c_ == NULL)
	{
		return true;
	}
	try
	{
		for (uint32 i = 0; i != c_->members.size(); ++i)
		{
			if (c_->members[i])
			{
				delete c_->members[i];
				c_->members[i] = NULL;
			}
		}
		c_->members.clear();
		return true;
	}
	catch (...)
	{
		return false;
	}
}
#endif