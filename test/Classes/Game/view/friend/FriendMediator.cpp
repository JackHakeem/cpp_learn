#include "FriendMediator.h"
#include "view/friend/components/FriendView.h"
#include "model/friend/FriendProxy.h"
#include "events/GameDispatcher.h"
#include "FriendListenerMediator.h"
#include "control/AppFacade.h"

FriendMediator::FriendMediator()
{
	viewON = false;
	_view = 0;
	_proxy = 0;
	_dispatcher = GameDispatcher::getInstance();
}

FriendMediator::~FriendMediator()
{}

void FriendMediator::handleNotification(int M2Vcmd, char* data)
{
	FriendProxy* _friProxy =  (FriendProxy*)g_pFacade->retrieveProxy(AppFacade_Friend_PROXY_CHANGE);
	_proxy = _friProxy;
	switch(M2Vcmd)
	{
	case FRI_POP:
		if (data)
		{
			pop((FriendView*)data);

		}
		break;
	case UPDATE_LIST:
		if (data)
			updateList(data);
		break;
	case MY_BLESS_INFO:
		break;
	default:
		break;
	}
}

void FriendMediator::pop(FriendView* view)
{
	if (view)
	{
		_view = view;
		viewON = true;

		_view->setisPop(true);
	}
	else if (!view)
	{
		viewON = false;
		return;
	}
	if (_view->getisPop())
	{
		_view->release();
	}
	//_view.setHead(_proxy.myInfo);
	if (_view->getisPop() && !_view->hasInit)
	{
		sendNotification(Facade_Mediator, AppFacade_OPEN_FRIENDS_COMMAND,
			0, FriendListenerMediator::GET_FRIENDSLIST);
	}
}

void FriendMediator::updateList(char* obj)
{
	struct sdata
	{
		int32 max;
		int32 page;
	};
	sdata* head = (sdata*)obj;
	
	if (viewON)
	{
		if (obj && _view)
		{
			_view->setPage(head->max ? head->max : 1, head->page ? head->page : 1);
			_view->updateList(&(_proxy->_currentList),head->page ? head->page : 1);
			_view->_pageNum = head->page;
		}
	}
}
