#include "campFightProxy.h"
#include "view/campFight/CampFightMediator.h"

CampFightProxy::CampFightProxy()
{
	m_pIceCity = NULL;
	m_pFireCity = NULL;
	m_pMyInfo = NULL;
}
CampFightProxy::~CampFightProxy()
{
	RemoveCampInfoCache(m_pIceCity);
	RemoveCampInfoCache(m_pFireCity);
}
void CampFightProxy::UpdateCampFightInfo(TCampInfo* ice_, TCampInfo* fire_)
{
	if (RemoveCampInfoCache(m_pIceCity))
	{
		m_pIceCity = ice_;
	}
	if (RemoveCampInfoCache(m_pFireCity))
	{
		m_pFireCity = fire_;
	}
	//通知mediater数据更新完毕
	sendNotification(Facade_Mediator, AppFacade_CampFight_Mediator, 
		NULL, CampFightMediator::UPDATE_CAMPFIGHT);
}
void CampFightProxy::UpdateMyInfo(TMyCampFightInfo* m_)
{
	m_pMyInfo->hisConstiWinTims = m_->hisConstiWinTims;
	m_pMyInfo->score = m_->score;
	m_pMyInfo->state = m_->state;
	m_pMyInfo->sumPop = m_->sumPop;
	m_pMyInfo->times = m_->times;
	//通知mediater数据更新完毕
	sendNotification(Facade_Mediator, AppFacade_CampFight_Mediator, 
		NULL, CampFightMediator::UPDATE_MY_INFO_VIEW);
}