#include "GuildMediator.h"
#include "manager/PopEventName.h"
#include "events/GameDispatcher.h"
#include "model/player/RoleManage.h"
#include "socket/network/GateServerSocket.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "model/guild/vo/MemberVo.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "GuildListenerMediator.h"
#include "model/guild/vo/EditGuildInfoVo.h"

GuildMediator* g_pGuildMediator = 0;

GuildMediator::GuildMediator()
{
	_view = 0;
	_preView = 0;

	g_pGuildMediator = this;
}

void GuildMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case GUILD_POP:
		pop((GuildView*)data);
		break;
	case GUILD_PRE_POP:
		prePop(data);
		break;
	case GUILD_MY_INFO:
		{
			MemberVo* info = (MemberVo*)data;
			setDefaultVO(info);
		}
		break;
	case GUILD_INIT_INFO:
		setGuildInfo(data);
		break;
	case OPEN_EDIT_VIEW:
		editInit(data);
		break;
	case SET_GUILD_LIST:
		setGuildList(data);
		break;
	case SET_PANEL_LIST:
		setPanelList(data);
		break;
	case GUILD_INFO_EDIT:
		editMainPanelInfo(data);
		break;
	case CLOSE_ALL_VIEW:
		closeAllView();
		break;
	}
}

//设置除公会以外的列表
void GuildMediator::setPanelList(char* data)
{
	if (!data)
		return;

	struct Node
	{
		int page;
		int max;
	};

	struct NodeStruct
	{
		Node headNode;
		std::list<GuildVoBase*> nodeArray;
		int panelIndex;
	};
	NodeStruct* obj = (NodeStruct*)data;

	if(_view && obj->panelIndex == _view->getpanelIndex())
	{
		_view->setPage(obj->headNode.max, obj->headNode.page);
		_view->updateList(obj->nodeArray);		
	}
}

//弹出主面板
void GuildMediator::pop( GuildView* view )
{
	if(view)
	{
		_view = view;
	}
	else
	{
		return;
	}

	_view->setisPop( !_view->getisPop() );
	if(!_view->gethasInit())
	{
		_view->eventON();
	}	
	if(_view->getisPop())
	{
		_view->release();
		sendNotification( Facade_Mediator,
			AppFacade_GUILD_START, 0, GuildListenerMediator::GET_INITDATA );

		if ( _preView )
		{
			_preView->dispear(0);
			_preView = 0;
		}		
	}

}

//修改完公会信息后重设主面板信息
void GuildMediator::editMainPanelInfo( char* data )
{
	EditGuildInfoVo* vo = (EditGuildInfoVo*)data;
	//if(_view)
	//	_view->setEditedInfo(vo);
}

//公会列表面板
void GuildMediator::prePop(char* data)
{
	if(data)
	{
		_preView = (GuildPreView*)data;
	}
	else
	{
		return;
	}

	if(_view)
		_preView->sethasGuild(true);
	else
		_preView->sethasGuild(false);

	if (_view && !_view->getisPop())
		_preView->sethasGuild(false);

	_preView->setIsVisible(!_preView->getIsVisible());
	if(_preView->getIsVisible())
		_preView->onInit();
	else
	{
		_preView->dispear(0);
		_preView = 0;
	}
}

//修改信息面板，需要初始化
void GuildMediator::editInit( char* arg )
{
	//editPop(_editView);
	//if(arg.VO && arg.VO is EditGuildInfoVo){
	//	var vo:EditGuildInfoVo = arg.VO as EditGuildInfoVo;
	//	if(_editView)
	//		_editView.setPanelText(vo.qq, vo.notice, vo.intro);
	//}
}

//void GuildMediator::editPop( GuildEditView* editView )
//{
//	if(_editView) _editView.isPop = false;
//	if(editView) _editView = editView;
//	_editView.isPop = true;
//}

//设置自身成员信息
void GuildMediator::setDefaultVO( MemberVo* info )
{
	if(_view)
		_view->setmyMemberInfo(*info);
}

//初始化公会信息
void GuildMediator::setGuildInfo( char* data )
{
	guildInfo = *(GuildInfoVo*)data;
	if(_view)
		_view->setguildInfo(guildInfo);
}

//设置公会列表
void GuildMediator::setGuildList(char* data)
{
	struct Node
	{
		int page;
		int max;
	};
	struct NodeStruct
	{
		Node headNode;
		std::list<GuildVoBase*> nodeArray;
	} nodeStruct;
	nodeStruct = *(NodeStruct*)data;

	if(_preView)
	{
		_preView->setPage(nodeStruct.headNode.max, nodeStruct.headNode.page);
		_preView->updateList( nodeStruct.nodeArray );
	}
}

GuildMediator::~GuildMediator()
{

}

void GuildMediator::closeAllView()
{

}
