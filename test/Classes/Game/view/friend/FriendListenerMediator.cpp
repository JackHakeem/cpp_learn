#include "FriendListenerMediator.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "view/friend/components/FriendView.h"
#include "manager/ViewManager.h"
#include "control/AppFacade.h"
#include "FriendMediator.h"
#include "socket/command/c20/CCMD200.h"
#include "socket/command/s20/SCMD201.h"
#include "socket/command/s20/SCMD209.h"
#include "socket/command/s20/SCMD20b.h"
#include "socket/command/s20/SCMD20d.h"
#include "socket/command/s20/SCMD20F.h"
#include "socket/command/s21/SCMD211.h"
#include "socket/command/s21/SCMD216.h"
#include "control/friend/FriendProxyCommand.h"
#include "socket/network/GateServerSocket.h"
#include "view/friend/components/FriendEventConst.h"
#include "components/FriendView.h"
#include "control/AppFacade.h"
#include "model/friend/vo/RequestAddInVo.h"
#include "model/notice/NoticeManager.h"
#include "view/noticeCenter/MsgMediator.h"

FriendListenerMediator::FriendListenerMediator()
{
	_view = 0;
	_gameDispatcher = GameDispatcher::getInstance();
	_gameDispatcher->addEventListener(PopEventName::SHOW_UI_FRIEND, this, callfuncND_selector(FriendListenerMediator::popHandler));

}

void FriendListenerMediator::popHandler(CCObject* pSender)
{
	//if(GlobalManage.getInstance().isGuest){
	//	Alert.show("游客无法使用好友功能，请先注册帐号！");
	//	return;
	//}
	_viewType=1;
	loadReportSource();	
}

void FriendListenerMediator::loadReportSource()
{
	popControl();
}

void FriendListenerMediator::popControl()
{
	switch(_viewType)
	{
	case 1:
		popView();
		break;
	case 2:
		popRequestTip();
		break;
	case 3:
		//popRequestBlessTip(_obj as SCMD21A);
		break;
	default:
		break;
	}
}

void FriendListenerMediator::popView()
{
	_view = 0;
	if (!_view)
	{
		_view = new FriendView();
		_view->init();
		viewListener();
		ViewManager::getInstance()->friendView = _view;
	}

	sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, (char*)_view, FriendMediator::FRI_POP);
}

void FriendListenerMediator::popRequestTip()
{
	RequestAddInVo* info = _obj;

	struct sdata
	{
		std::string name;
		int type;
	};
	sdata d;
	d.name = info->name;
	d.type = 0;

	g_pNoticeManager->noticeBuilder(info->name, NoticeManager::ADD_FRI,(char*)&d,info->mainLev);
	sendNotification(Facade_Mediator, AppFacade_Notice, 0, MsgMediator::NEW_FRIEND_MSG);
}

void FriendListenerMediator::changeListHandler(CCNode* n, void* data)//列表发生改变时，发起一个Command
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::CHANGE_LIST_INDEX);	
}

void FriendListenerMediator::deleteFriendHandler(CCNode* n, void* data)//删除好友，发起一个Command
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::DELETE_FRIEND);	
}

void FriendListenerMediator::moveToBlackHandler(CCNode* n, void* data)
{//移除好友到黑名单，发起一个Command
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::MOVE_TO_BLACK);
}

void FriendListenerMediator::quickAddRecFriHandler(CCNode* n, void* data)
{//一键添加推荐好友列表，发起一个Command
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::QUICK_ADD_RECOMMEND_FRIENDS);	
}


void FriendListenerMediator::addFriendHandler(CCNode* n, void* data)
{//添加好友，发起一个Command
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::ADD_FRIEND);
}

void FriendListenerMediator::changePageHandler(CCNode* n, void* data)
{//翻页时，发起一个Command //uint32 data
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::CHANGE_LIST_PAGE);
}

void FriendListenerMediator::moveFriendOutHandler(CCNode* n, void* data)
{//把联系人从当前列表移除，发起一个Command
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::MOVE_FRIEND_OUT);
}
//
/**
* 开启视图监听 
* 
*/		
void FriendListenerMediator::viewListener()
{
	if(!_view)
		return;

	_view->addEventListener(FriendView::CHANGE_LIST, this, callfuncND_selector(FriendListenerMediator::changeListHandler));//切换列表
	_view->addEventListener(FriendEventConst::QUICK_ADD_RECOMMEND_FRIENDS, this, callfuncND_selector(FriendListenerMediator::quickAddRecFriHandler));
	_view->addEventListener(FriendEventConst::ADD_FRIEND, this, callfuncND_selector(FriendListenerMediator::addFriendHandler));//添加好友
	_view->addEventListener(FriendView::CHANGE_PAGE, this, callfuncND_selector(FriendListenerMediator::changePageHandler));//翻页
	_view->addEventListener(FriendEventConst::DEL_FRIEND, this, callfuncND_selector(FriendListenerMediator::deleteFriendHandler));//删除好友
	_view->addEventListener(FriendEventConst::MOVE_TO_BLACK, this, callfuncND_selector(FriendListenerMediator::moveToBlackHandler));//从好友列表移到黑名单
	_view->addEventListener(FriendEventConst::MOVE_FRIEND_OUT, this, callfuncND_selector(FriendListenerMediator::moveFriendOutHandler));//把联系人从当前列表移除

	/*
	_view->addEventListener(FriendEventConst::MOVE_FRIEND_OUT, moveFriendOutHandler);//把联系人从当前列表移除
	_view->addEventListener(FriendEventConst::AGREE_FRIEND, checkAddReqHandler);//同意好友请求
	_view->addEventListener(FriendEventConst::REFUSE_FRIEND, checkAddReqHandler);//拒绝好友请求
	_view->addEventListener(FriendEventConst::QUICK_ADD_RECOMMEND_FRIENDS, quickAddRecFriHandler);//祝福好友
	_view->addEventListener(FriendEventConst::FRIEND_INFO, infoFriHandler);//祝福好友
	_view->addEventListener(FriendEventConst::FRIEND_BLESS, blessFriHandler);//祝福好友
	_view->addEventListener(FriendEventConst::FRIEND_CHAT, chatHandler);//发起聊天
	_view->addEventListener(FriendEventConst::FRIEND_TROOP, troopHandler);//发起组队请求
	_view->addEventListener(FriendEventConst::FRIEND_PK, pkHandler);
	_view->addEventListener(FriendView::ASK_ROBOT, askRobotHandler);
	_view->addEventListener(FriendView::SEND_ROBOT, sendRobotHandler);
	*/
}


void FriendListenerMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case GET_FRIENDSLIST://得到第一页好友列表
		requestForFriendList((PlayerBaseVo*)data);
		break;
	case OPEN_REQ_PANEL:
		openRequstTip((RequestAddInVo*)data);
		break;
	default:
		break;
	}
}

void FriendListenerMediator::openRequstTip(RequestAddInVo* obj)
{
	_viewType=2;
	_obj=obj;
	popControl();
	//loadReportSource();			
}

void FriendListenerMediator::requestForFriendList(PlayerBaseVo* vo)
{
	//请求自身祝福信息
	//_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_FRIENDS_BLESS_NUM);	

	CCMD200* param = new CCMD200();
	if (param)
	{
		param->a_page = (int16)1;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD200 page 1");
	}
	SAFE_DELETE(param);
}

void FriendListenerMediator::receiveFList(SCMD201* param)
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)param, FriendProxyCommand::CREATE_FRIENDS_LIST);
}

void FriendListenerMediator::receiveRList(SCMD205* param)
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)param, FriendProxyCommand::CREATE_RECOMMEND_LIST);
}

void FriendListenerMediator::receiveBList(SCMD207* param)
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)param, FriendProxyCommand::CREATE_BLACK_LIST);
}

void FriendListenerMediator::receiveDFSuccess(SCMD20b* param)
{
	//if(param.b_delName!=_roleManager.roleInfo.playerBaseInfo.name){
	//		Message.show(LangManager.getText("FRD029",param.b_delName));	
	//}
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, 0, FriendProxyCommand::UPDATE_CURRENT_LIST);
}

//从黑名单列表中删除玩家 成功 的返回包
void FriendListenerMediator::receiveDBFLSuccess(SCMD211* param)
{
	//Message.show(LangManager.getText("FRD031",param.b_name));	
	//sendNotification(AppFacade.OPEN_FRIENDS_COMMAND, null, FriendProxyCommand.UPDATE_CURRENT_LIST);
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, 0, FriendProxyCommand::UPDATE_CURRENT_LIST);
}

//收到把好友移至黑名单操作 成功 的返回包
void FriendListenerMediator::receiveMBSuccess(SCMD20d* param)
{
//	Message.show(LangManager.getText("FRD030",param.b_name));	
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, 0, FriendProxyCommand::UPDATE_CURRENT_LIST);
}

//收到把非好友拖到黑名单 成功 的返回包
void FriendListenerMediator::receiveDBSuccess(SCMD20F* param)
{
	//Message.show(LangManager.getText("FRD030",param.b_name));	
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, 0, FriendProxyCommand::UPDATE_CURRENT_LIST);
}

//收到添加好友请求 成功 的返回包
void FriendListenerMediator::receiveRQSuccess(SCMD209* param)
{
	//var obj:Object = {index: 0, page: 1}
	//Message.show(LangManager.getText("FRD028",param.b_name));	
	struct sdata
	{
		int32 index;
		int32 page;
	};
	sdata d;
	d.index = 0;
	d.page = 1;
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)&d, FriendProxyCommand::PAGE_CHANGE_DERECT);
	//sendNotification(AppFacade.OPEN_FRIENDS_COMMAND, &d, FriendProxyCommand.PAGE_CHANGE_DERECT);
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, 0, FriendProxyCommand::UPDATE_CURRENT_LIST);
	//sendNotification(AppFacade.OPEN_FRIENDS_COMMAND, null, FriendProxyCommand.UPDATE_CURRENT_LIST);
}

//其它玩家的添加好友请求
void FriendListenerMediator::receiveAddFriendRQ(SCMD216* param)
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)param, FriendProxyCommand::RECEIVE_REQUEST);
}