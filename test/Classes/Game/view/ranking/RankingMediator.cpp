#include "RankingMediator.h"
#include "manager/PopManage.h"
#include "control/ranking/RankingCommand.h"
#include "components/RankingListView.h"

RankingMediator::RankingMediator()
{
    _pRankingView = 0;

    GameDispatcher* _dispatcher = GameDispatcher::getInstance();
	if (_dispatcher)
		_dispatcher->addEventListener(PopEventName::SHOW_UI_RANKING, this, callfuncND_selector(RankingMediator::popRankingView));
}

RankingMediator::~RankingMediator()
{
	GameDispatcher* _dispatcher = GameDispatcher::getInstance();
	if (_dispatcher)
		_dispatcher->removeEventListener(PopEventName::SHOW_UI_RANKING);
	stopViewListener();
}

void RankingMediator::handleNotification(int M2Vcmd, char* data)
{
	if (! _pRankingView)
		return;

	switch (M2Vcmd)
	{
	case UPDATE_RANK_LIST:
		_pRankingView->updateRankList(*((std::vector<RankItemVo>*)data));
		break;
	case UPDATE_EQUIPMENTS:
		_pRankingView->updateEquipments(*((std::vector<EquipItemVo>*)data));
		break;
	case UPDATE_MY_RANK:
		_pRankingView->updateMyRank(*((int*)data));
		break;
	}
}

void RankingMediator::popRankingView()
{
    if (! _pRankingView)
    {
        _pRankingView = new RankingView();
		startViewListener();  //it is better to be in front of init()
        if (! _pRankingView->init())
		{
			CC_SAFE_DELETE(_pRankingView);
			stopViewListener();
		}
    }
	_pRankingView->popUpView();
}

void RankingMediator::updateRankingList(SCMD25C* packet)
{
	sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)packet, RankingCommand::UPDATE_RANKING_LIST);
}

void RankingMediator::updateEuiqpments(SCMD25E* packet)
{
	sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)packet, RankingCommand::UPDATE_EQUIPS_INFO);
}

void RankingMediator::startViewListener()
{
	if (_pRankingView)
	{
		_pRankingView->addEventListener(RankingView::REQUEST_RANKING_LIST, this, callfuncND_selector(RankingMediator::onRequestRankingList));
		_pRankingView->addEventListener(RankingView::REQUEST_EQUIP_INFO, this, callfuncND_selector(RankingMediator::onRequestEquipInfo));
	}   
}

void RankingMediator::stopViewListener()
{
	if (_pRankingView)
	{
		_pRankingView->removeEventListener(RankingView::REQUEST_RANKING_LIST, this, callfuncND_selector(RankingMediator::onRequestRankingList));
	}   
}

void RankingMediator::onRequestRankingList(CCNode* target, void* data)
{
	sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)data, RankingCommand::REQUEST_RANKING_LIST);
}

void RankingMediator::onRequestEquipInfo(CCNode* target, void* data)
{
	sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)data, RankingCommand::REQUEST_SELECTED_EQUIP_INFO);
}