#include "GuildListenerMediator.h"
#include "manager/PopEventName.h"
#include "events/GameDispatcher.h"
#include "model/player/RoleManage.h"
#include "socket/network/GateServerSocket.h"
#include "socket/command/c1c/CCMD1C2.h"
#include "socket/command/c1c/CCMD1BE.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "control/guild/GuildChangeCommand.h"
#include "GuildMediator.h"
#include "manager/ViewManager.h"
#include "manager/GlobalManage.h"
#include "manager/LangManager.h"
#include "./components/MemberPanel.h"
#include "./components/GuildTabPanel.h"
#include "./components/PageNav.h"
#include "components/GuildEventConst.h"
#include "components/GuildDispatcher.h"
#include "socket/command/c1c/CCMD1C0.h"
#include "socket/command/c1b/CCMD1B5.h"
#include "socket/command/c1b/CCMD1B6.h"
#include "socket/command/c1b/CCMD1B9.h"
#include "socket/command/c1b/CCMD1BA.h"
#include "socket/command/c1b/CCMD1BB.h"
#include "socket/command/c1b/CCMD1BD.h"
#include "socket/command/c1c/CCMD1C4.h"
#include "socket/command/c1c/CCMD1C5.h"
#include "socket/command/c1c/CCMD1CA.h"
#include "socket/command/c1c/CCMD1CF.h"
#include "socket/command/c1c/CCMD1CC.h"
#include "socket/command/c20/CCMD208.h"
#include "socket/command/c1d/CCMD1D5.h"
#include "socket/command/c1d/CCMD1D1.h"
#include "socket/command/c1b/CCMD1B0.h"
#include "socket/command/c1b/CCMD1B3.h"
#include "socket/command/c1b/CCMD1B1.h"
#include "socket/command/c1e/CCMD1CE.h"
#include "model/guild/vo/EditGuildInfoVo.h"
#include "components/GuildInfoView.h"
#include "components/DonateView.h"

GuildListenerMediator* g_pGuildListenerMediator = 0;

static const int COST_SILVER = 150000;
static const int COST_GOLD = 20;

GuildListenerMediator::GuildListenerMediator()
{
	_view = 0;
	_preView = 0;

	GameDispatcher::getInstance()->addEventListener(
		PopEventName::SHOW_UI_GUILD, this, callfuncND_selector(GuildListenerMediator::popHandler) );

	g_pGuildListenerMediator = this;
	editViewListener(true);
}

GuildListenerMediator::~GuildListenerMediator()
{}

//主面板和公会列表的弹出控制
void GuildListenerMediator::popHandler( CCNode* n, void* data )
{
	if(g_pGlobalManage->isGuest)
	{
		//LangManager.alertShow("GLD001");
		LangManager::msgShow("GLD001");
		return;
	}
	
	int param = *(int*)data;
	if(param){
		popPreViewHandler(param);
		return;
	}
	int gId = RoleManage::Instance()->accountInfo()->guild;
	if(gId)
		popViewHandler(param);
	else
		popPreViewHandler(param);
}

void GuildListenerMediator::popPreViewHandler( int param1 )
{
	_preView = (GuildPreView*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_GuildPre);
	if(!_preView)
	{
		_preView = new GuildPreView();
		_preView->init();
		ViewManager::getInstance()->guildPreView = _preView;
		LayerManager::intervalLayer->addChild(
			_preView, IntervalLayer::IntervalLayerZ_GuildPre, IntervalLayer::IntervalLayerTAG_GuildPre);

		_preView->setIsVisible(false);
		_preView->release();
		
		preViewListener();
	}

	sendNotification(Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)_preView, GuildMediator::GUILD_PRE_POP);
}

void GuildListenerMediator::popViewHandler( int param )
{
	if (_view)
	{
		_view->release();
		_view = 0;
	}
	if(!_view)
	{
		_view = new GuildView();
		_view->init();
		ViewManager::getInstance()->guildView = _view;

		viewListener();
	}

	sendNotification(Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)_view, GuildMediator::GUILD_POP);
//	g_pGuildMediator->pop( _view );
}

void GuildListenerMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case GET_INITDATA:
		myGuildInfoHandler();//得到自身职位等信息(MemberVo)
		guildInfoHandler();//得到已加入的公会信息
		break;
	}
}

void GuildListenerMediator::preViewListener()
{
	if(!_preView)
	{
		return;
	}
	GuildDispatcher* _guildDispatcher = GuildDispatcher::getInstance();
	//_preView.addEventListener(GuildEventConst.GUILD_VIEW, guildInfoHandler);		// 查看公会信息

	_guildDispatcher->addEventListener(GuildEventConst::GUILD_GET_LIST,
		this, callfuncND_selector(GuildListenerMediator::guildListHandler) );       // 查看公会列表

	_guildDispatcher->addEventListener(GuildEventConst::GUILD_SEARCH,
		this, callfuncND_selector(GuildListenerMediator::guildSearchHandler) );     // 查找公会

	_guildDispatcher->addEventListener(GuildEventConst::APPLY_GUILD,
		this, callfuncND_selector(GuildListenerMediator::applyGuildHandler) );     // 入会申请

	_guildDispatcher->addEventListener(GuildEventConst::CREAT_GUILD,
		this, callfuncND_selector(GuildListenerMediator::creatGuildHandler) );     // 创建公会

	_guildDispatcher->addEventListener( GuildEventConst::OPEN_GUILD_INFO_VIEW,
		this, callfuncND_selector(GuildListenerMediator::openGuildInfoView) );
}

void GuildListenerMediator::viewListener()
{
	//开启主面板监听
	if(!_view) return;
	GuildDispatcher* _guildDispatcher = GuildDispatcher::getInstance();

	_guildDispatcher->addEventListener(GuildEventConst::REMOVE_GUILD,
		this, callfuncND_selector(GuildListenerMediator::disGuildHandler) );               	// 解散公会
	_guildDispatcher->addEventListener(GuildEventConst::REMOVE_GUILD_CANCEL,
		this, callfuncND_selector(GuildListenerMediator::disGuildCancelHandler) );		// 取消解散公会
	_guildDispatcher->addEventListener(GuildEventConst::UPDATE_EMBLEM,
		this, callfuncND_selector(GuildListenerMediator::updateEmblemHandler) );				// 军徽升级
	_guildDispatcher->addEventListener(GuildEventConst::EXIT_GUILD,
		this, callfuncND_selector(GuildListenerMediator::exitGuildHandler) );                	// 退出公会
	_guildDispatcher->addEventListener(GuildEventConst::GUILD_MEMBER_LIST,
		this, callfuncND_selector(GuildListenerMediator::memberListHandler) );        	// 查看成员列表
	_guildDispatcher->addEventListener(GuildEventConst::LEADER_SHIF,
		this, callfuncND_selector(GuildListenerMediator::appointmentHandler) );					// 转移会长
	_guildDispatcher->addEventListener(GuildEventConst::EXPEL_MEMBER,
		this, callfuncND_selector(GuildListenerMediator::expelMemberHandler) );				// 开除成员 
	_guildDispatcher->addEventListener(GuildEventConst::ADD_FRIEND,
		this, callfuncND_selector(GuildListenerMediator::addFriendHandler) );					// 加为好友	
	_guildDispatcher->addEventListener(GuildEventConst::INVITE_TEAM, 
		this, callfuncND_selector(GuildListenerMediator::inviteTeamHander) );					// 邀请组队	
	_guildDispatcher->addEventListener(GuildEventConst::GUILD_TECH_LIST,
		this, callfuncND_selector(GuildListenerMediator::tecListHandler) );             	// 查看科技列表
	_guildDispatcher->addEventListener(GuildEventConst::DEGAULT_TECH_CHANGE,
		this, callfuncND_selector(GuildListenerMediator::defaultTecEditHandler) ); 		// 修改默认科技
	_guildDispatcher->addEventListener(GuildEventConst::GUILD_APPLY_LIST,
		this, callfuncND_selector(GuildListenerMediator::applyListHandler) );          	// 查看入会申请列表
	_guildDispatcher->addEventListener(GuildEventConst::APPROVE_MEMBER,
		this, callfuncND_selector(GuildListenerMediator::approvalHandler) );					// 批准入会申请
	_guildDispatcher->addEventListener(GuildEventConst::REFUSE_MEMBER,
		this, callfuncND_selector(GuildListenerMediator::approvalHandler) );              	// 拒绝入会申请 
	_guildDispatcher->addEventListener(GuildEventConst::OPEN_DONATE_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popDonateViewHandler) );	//打开捐献银币窗口
	_guildDispatcher->addEventListener(GuildEventConst::POP_GUILD_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popGuildView) );	//关闭公会列表窗口
	_guildDispatcher->addEventListener(GuildEventConst::POP_PRE_GUILD_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popPreGuildView) );	//关闭公会列表窗口

	//_view.addEventListener(GuildEventConst.OPEN_EDIT_VIEW, popEditViewHandler);
	_guildDispatcher->addEventListener(GuildEventConst::OPEN_EDIT_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popEditViewHandler) );
}

void GuildListenerMediator::editViewListener(bool start)
{
	//开启修改公会信息面板监听
//	if(!_editView)	return;
//	if(start)
		GuildDispatcher::getInstance()->addEventListener(
			GuildEventConst::EDIT_GUILD_NOTICE, this, callfuncND_selector(GuildListenerMediator::editGuildInfoHandler) );
	//else
	//	GuildDispatcher::getInstance()->removeEventListener(
	//		GuildEventConst::EDIT_GUILD_NOTICE);
}

void GuildListenerMediator::donateViewListener()
{
	//if(!_donateView) return;
	GuildDispatcher::getInstance()->addEventListener(
		GuildEventConst::DONATE_YB,this, callfuncND_selector(GuildListenerMediator::donateHandler) );
}


/** 弹出修改公会信息窗口 */		
void GuildListenerMediator::popEditViewHandler(CCNode *pNode, void *pData)
{
	sendNotification(Facade_Mediator,
		AppFacade_GUILD_CHANGE, (char*)pData, GuildMediator::OPEN_EDIT_VIEW);
	//this.sendNotification(GuildMediator.OPEN_EDIT_VIEW, {view: editView, VO: e.param as EditGuildInfoVo});
}

/** 弹出捐献银币窗口 */		
void GuildListenerMediator::popDonateViewHandler(CCNode *pNode, void *pData)
{
	//if(_donateView) _donateView.close();
	//_donateView = new DonateView(uint(e.param));
	//applyDonateViewData(null);	//向服务端请求捐献银币界面数据
	//_donateView.addEventListener(GuildEventConst.DONATE_MONEY, donateHandler);
}

void GuildListenerMediator::popGuildView(CCNode *pNode, void *pData)
{
	//if(_view && !_view.isPop)
	//{
	//	if(_editView) _editView.isPop = false;
	//	if(_donateView) _donateView.isPop = false;
	//}
}

void GuildListenerMediator::popPreGuildView(CCNode *pNode, void *pData)
{
	//			if(!_view || !_preView) return; 
	//			_view.isPop = !_preView.isPop;
	//			if(_view.isPop) _view.eventON();
}

/**================================接收相应服务端返回包时处理=====================================*/

//新建公会成功返回
void GuildListenerMediator::newGuildSuccessHandler( SCMD1B7* param )
{
	//if(_preView)
	//	_preView.isPop = false;

	RoleManage::Instance()->accountInfo()->guild = param->a_guildId;	//设置账号公会id

	int a = 0;
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, &a);	//打开公会面板
	myGuildInfoHandler();//请求自身的公会成员信息
	guildInfoHandler();//得到已加入的公会信息
}

//查看公会列表
void GuildListenerMediator::getGListHandler( SCMD1B2* param )
{
	sendNotification(Facade_Command, AppFacade_GUILD_START, (char*)param, GuildChangeCommand::CREATE_GUILD_LIST);

	//g_pGuildMediator->setGuildList( (char*)param );
}

////查找公会返回公会包
//private function getFGHandler(param:SCMD1B4)
//{
//	//暂不使用
//}
//返回入会申请列表
void GuildListenerMediator::getApListHandler( SCMD1BC* param )
{
	sendNotification(Facade_Command, AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_CHECK_LIST);
	//this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_CHECK_LIST);
	guildInfoHandler();//重新请求公会信息
}
//返回所查看的公会信息
void GuildListenerMediator::getGInfoHandler( SCMD1BF* param )
{
	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_GUILD_INIT_INFO);
}

//返回公会成员列表(分页)
void GuildListenerMediator::getMBListHandler( SCMD1C1* param )
{
	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_MEMBER_LIST);
	//this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_MEMBER_LIST);
	//			guildInfoHandler();//重新请求公会信息
}

//返回所查看的成员信息
void GuildListenerMediator::getMBInfoHandler( SCMD1C3* param )
{
	std::list<SCMD1C3::SCMD1C3Node> arr = param->c_nodeArr;
	if ( arr.size() > 0 )
	{
		std::list<SCMD1C3::SCMD1C3Node>::iterator it = arr.begin();
		SCMD1C3::SCMD1C3Node node = *it;

		if ( node.c_pName == RoleManage::Instance()->accountInfo()->name )
		{
			if ( param->b_page == 0 )
			{
				sendNotification(Facade_Command,
					AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_MY_GUILD_INFO);
				//this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_MY_GUILD_INFO);
				return;
			}
			
		}		
	}

	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_SEARCH_MEMBER_LIST);
	//if(node && node.c_pName == RoleManage.getInstance().accountInfo.name && param.b_page.value == 0)
	//	this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_MY_GUILD_INFO);
	//else 
	//	this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_SEARCH_MEMBER_LIST);
}

//返回查看的科技列表包
void GuildListenerMediator::getTEListHandler( SCMD1C6* param )
{
	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_TECH_LIST);
	guildInfoHandler();//重新请求公会信息
}

//公会操作响应码
void GuildListenerMediator::oprateHandler( SCMD1C7* param )
{
	switch(param->a)
	{
	case 105:		//创建公会成功
		RoleManage::Instance()->accountInfo()->guild = 1;
		guildInfoHandler();
		LangManager::msgShow("GLD002");
		break;
	case 151:		//要创建的公会名字已存在
		//LangManager.alertShow("GLD003");
		LangManager::msgShow("GLD003");
		break;
	case 152:		//创建公会的银币不足
		LangManager::msgShow("GLD004");
		break;
	case 161:
		{
			CCMD1BE cmd;
			GateServerSocket::getInstance()->sendMessage(&cmd);//CMSG_COMMU_GUILD_INFO
			LangManager::msgShow("GLD005");
		}
		break;
	case 162:		//升级军徽失败
		LangManager::msgShow("GLD006");
		break;
	case 166:		//捐献成功，请求更新后的科技列表
		donateSuccess();
		break;
	case 167:		//超过捐献上限
		LangManager::msgShow("GLD007");
		break;
	case 171:		//任命职务成功，刷新成员列表
		appointSuccess();
		myGuildInfoHandler();	//更新自己的信息
		break;
	case 172:		//官员人数满
		LangManager::msgShow("GLD008");
		break;
	case 173:		//副会长人数满
		LangManager::msgShow("GLD009");
		break;
	case 174:		//任命对象不存在,可能已被删除
		LangManager::msgShow("GLD010");
		break;
	case 175:		//距离上次转移会长不足三天
		LangManager::msgShow("GLD011");
		break;
	case 176:		//新建三天内不能转移
		LangManager::msgShow("GLD012");
		break;
	case 186:		//被所在公会踢出
		expelledMember(LangManager::getText("GLD013"));
		break;
	case 200:
		LangManager::msgShow("GLD014");
		guildInfoHandler();
		break;
	case 201:
		LangManager::msgShow("GLD015");
		break;
	case 202:
		LangManager::msgShow("GLD016");
		guildInfoHandler();
		break;
	case 203:
		LangManager::msgShow("GLD017");
		break;
	case 220://不能再申请了
		LangManager::msgShow("GLD018");
		break;
	case 221:
		expelledMember(LangManager::getText("GLD019"));
		break;
	}
}

//入会申请审批结果（以下三种状态都会发给会长）
void GuildListenerMediator::getApplyHandler(SCMD1CB* param)
{
	switch(param->b_retNum)
	{
	case 0:
		//申请入会被通过（如果申请者在线，也发给申请者）
		if( _view  && _view->getisPop())
		{
			//如果是审核者，向服务端请求新的审核列表
			CCMD1BB cmd;
			cmd.a_page = 1;//_view.curPage
			GateServerSocket::getInstance()->sendMessage(&cmd);
			//_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_APPLY_LIST, new Int16(_view.curPage));
		}
		else if (!_view || (_view && !_view->getisPop()))
		{
			//如果我是申请者，更新我的公会信息，并通知我已入会
			RoleManage::Instance()->accountInfo()->guild = param->a_guildId;
			myGuildInfoHandler();
			LangManager::msgShow("GLD020");
			_preView = (GuildPreView*)LayerManager::intervalLayer->getChildByTag(
				IntervalLayer::IntervalLayerTAG_GuildPre);
			if(_preView && _preView->getIsVisible())
			{
				_preView->dispear(0);
			}
			int a = 0;
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, &a);	//打开公会面板
		}
		break;
	case 1:		//公会人数已满
		LangManager::msgShow("GLD021");
		break;
	case 2:		//对方已加入其他公会
		{
			//LangManager.alertShow("GLD022");
			LangManager::msgShow("GLD022");

			CCMD1BB cmd;
			cmd.a_page = 1;//_view.curPage
			GateServerSocket::getInstance()->sendMessage(&cmd);//CMSG_COMMU_GUILD_APPLY_LIST
		}
		break;
	}
} 

//收到服务端返回退出公会结果包
void GuildListenerMediator::exitGuildReturnHandler(SCMD1CD* param)
{
	if(param->a_flag == 0)
	{
		//成功退出公会
		expelledMember(LangManager::getText("GLD023"));
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, &a);
	}
	else if(param->a_flag == 1)
	{
		LangManager::msgShow("GLD024");
		//LangManager.alertShow("GLD024");
	}
}

//接收今日捐献上限、已捐献数
void GuildListenerMediator::receiveDonateData( SCMD1D6* param )
{
	DonateView* _donateView = (DonateView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview);
	if (!_donateView) return;
	_donateView->setdonateMax(param->a_limit);
	_donateView->setdonated(param->b_donate);
	_donateView->update();
	_donateView->setIsVisible(true);
}

//公会操作相关提示
void GuildListenerMediator::showGuildTip(SCMD1B8* param)
{
	sendNotification( Facade_Command, AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GUILD_TIPS );
}

/**===================================处理客户端操作==================================*/

//取回自己的公会信息
void GuildListenerMediator::openGuildInfoView(CCNode *pNode, void *pData)
{
	GuildInfoView* _infoView = new GuildInfoView(*(GuildInfoVo*)pData);
	_infoView->init();
	LayerManager::intervalLayer->addChild(
		_infoView, IntervalLayer::IntervalLayerZ_guild_info, IntervalLayer::IntervalLayerTAG_guild_info);
	_infoView->release();

}

//取回自己的公会信息
void GuildListenerMediator::myGuildInfoHandler()
{
	CCMD1C2 param;
	param.a_pName = RoleManage::Instance()->accountInfo()->name;
	param.b_code = 0;
	param.c_type = 0;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_MEMBER_INFO
}

//修改公会信息
void GuildListenerMediator::editGuildInfoHandler(CCNode *pNode, void *pData)
{
	EditGuildInfoVo& vo = *(EditGuildInfoVo*)pData;
	CCMD1CE param;
	param.b_qqGP = vo.qq;
	param.c_notice = vo.notice;
	param.d_intr = vo.intro;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_ALTER_INFO
	sendNotification( Facade_Mediator, AppFacade_GUILD_START, (char*)&vo, GuildMediator::GUILD_INFO_EDIT );
	guildInfoHandler();
}

//用户发起新建公会请求
void GuildListenerMediator::creatGuildHandler(CCNode *pNode, void *pData)
{
	//协议号:CMSG_COMMU_GUILD_NEW = 0x1B0
	if(RoleManage::Instance()->roleLev() < 15){
		//LangManager.alertShow("GLD025");
		LangManager::msgShow("GLD025");
		return;
	}
	if(RoleManage::Instance()->accountInfo()->gold() < /*CreateGuild.*/COST_GOLD){
		//LangManager.alertShow("GLD026", CreateGuild.COST_GOLD);
		char txt[128];
		sprintf( txt, ValuesUtil::Instance()->getString( "GLD026" ).c_str(), COST_GOLD );
		Message::Instance()->show( string(txt), ValuesUtil::Instance()->getColor("GLD026"), 3 );
		return;
	}
	if(RoleManage::Instance()->accountInfo()->silver() < /*CreateGuild.*/COST_SILVER){
		//LangManager.alertShow("GLD027", CreateGuild.COST_SILVER);
		char txt[128];
		sprintf( txt, ValuesUtil::Instance()->getString( "GLD027" ).c_str(), COST_SILVER );
		Message::Instance()->show( string(txt), ValuesUtil::Instance()->getColor("GLD026"), 3 );
		return;
	}
	string tmp = (char*)pData;
	string str = tmp.substr(0,1);
	if(str.length() == 0){
		//LangManager.alertShow("GLD028");
		LangManager::msgShow("GLD028");
		return;
	}
	if(str == " "){
		//LangManager.alertShow("GLD029");
		LangManager::msgShow("GLD029");
		return;
	}
	CCMD1B0 param;
	param.a_name = tmp;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_NEW
}
//用户发起查看公会列表请求
void GuildListenerMediator::guildListHandler(CCNode *pNode, void *pData)
{
	CCMD1B1 param;
	param.a_page = *(int16*)pData;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_GET_LIST
} 
//用户发起查找公会请求
void GuildListenerMediator::guildSearchHandler(CCNode *pNode, void *pData)
{
	struct Node
	{
		string name;
		int page;
	} obj;
	obj = *(Node*)pData;
	CCMD1B3 param;
	param.a_guildName = obj.name;
	param.b_page = *(int16*)obj.page;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_FIND
} 
//用户发起的解散公会请求
void GuildListenerMediator::disGuildHandler(CCNode *pNode, void *pData)
{
	CCMD1B5 cmd;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_DISSOLVE
}
//用户发起的取消解散公会请求
void GuildListenerMediator::disGuildCancelHandler(CCNode *pNode, void *pData)
{
	CCMD1B6 cmd;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_DISSOLVE_CANCEL
}
//用户发起任命成员请求
void GuildListenerMediator::appointmentHandler(CCNode *pNode, void *pData)
{
	CCMD1B9* cmd = (CCMD1B9*)pData;
	GateServerSocket::getInstance()->sendMessage(cmd);	//CMSG_COMMU_GUILD_NOMINATE
} 
//用户发起入会请求
void GuildListenerMediator::applyGuildHandler(CCNode *pNode, void *pData)
{
	CCMD1BA cmd;
	cmd.a_guildName = (char*)pData;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_APPLY
	//_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_APPLY, event.param);
}  
//用户发起查看入会申请列表请求
void GuildListenerMediator::applyListHandler(CCNode *pNode, void *pData)
{
	CCMD1BB cmd;
	cmd.a_page = *(int16*)pData;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_APPLY_LIST
}
//用户发起审批入会请求
void GuildListenerMediator::approvalHandler(CCNode *pNode, void *pData)
{
	CCMD1BD* cmd = (CCMD1BD*)pData;
	GateServerSocket::getInstance()->sendMessage(cmd);	//SocketCMDConst.CMSG_COMMU_GUILD_APPLY_HANDLE
}

//用户发起查看公会信息请求
void GuildListenerMediator::guildInfoHandler()
{
	CCMD1BE cmd;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//SocketCMDConst.CMSG_COMMU_GUILD_INFO
}

//用户发起查看成员列表请求
void GuildListenerMediator::memberListHandler(CCNode *pNode, void *pData)
{
	struct sdata
	{
		uint page;
		int type;

	};
	sdata d = *(sdata*)pData;

	if(d.page != 0)
	{
		CCMD1C0 param;
		param.a_displayType = d.type;
		param.b_memberPage = d.page;
		GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_MEMBER_LIST
	}
} 
//用户发起查看成员信息请求
void GuildListenerMediator::memberInfoHandler(CCNode *pNode, void *pData)
{
	struct Node
	{
		string name;
		int page;
		int type;
	} obj;
	obj = *(Node*)pData;

	CCMD1C2 param;
	param.a_pName = obj.name;
	param.b_code = obj.page;
	param.c_type = obj.type;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_MEMBER_INFO
} 
//用户发起修改默认科技请求
void GuildListenerMediator::defaultTecEditHandler(CCNode *pNode, void *pData)
{
	CCMD1C4* param = (CCMD1C4*)pData;
	GateServerSocket::getInstance()->sendMessage( param );//CMSG_COMMU_GUILD_DEFAULT_TECH
}
//用户发起查看科技列表请求
void GuildListenerMediator::tecListHandler(CCNode *pNode, void *pData)
{
// 	var obj:Object = event.param as Object;
// 	if(obj && obj.page){
	CCMD1C5 param;
	param.a_page = *(int*)pData;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_TECH_LIST
// 	}
}      
//用户发起踢出成员请求
void GuildListenerMediator::expelMemberHandler(CCNode *pNode, void *pData)
{
	CCMD1CA* cmd = (CCMD1CA*)pData;
	GateServerSocket::getInstance()->sendMessage( cmd );//CMSG_COMMU_GUILD_KICK_MEMBER
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_KICK_MEMBER, param);
}
//用户发起升级军徽请求
void GuildListenerMediator::updateEmblemHandler(CCNode *pNode, void *pData)
{
	CCMD1CF param;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_FLAG_UPDATE
}
//用户发起修改公会信息请求
void GuildListenerMediator::editGuildHandler(CCNode *pNode, void *pData)
{
	struct Node
	{
		string b_qqGP;
		string c_notice;
		string d_intr;
	};
	Node obj = *(Node*)pData;
	CCMD1CE cmd;
	cmd.b_qqGP = obj.b_qqGP;
	cmd.c_notice = obj.c_notice;
	cmd.d_intr = obj.d_intr;
	GateServerSocket::getInstance()->sendMessage( &cmd );//CMSG_COMMU_GUILD_ALTER_INFO

}
//用户发起退出公会请求
void GuildListenerMediator::exitGuildHandler(CCNode *pNode, void *pData)
{
	CCMD1CC param;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_QUIT
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_QUIT);
}
// 用户发起加为好友请求
void GuildListenerMediator::addFriendHandler(CCNode *pNode, void *pData)
{
	CCMD208 param;
	param.a_name = *(char*)pData;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_FRIENDS_ADD_FRIEND
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_FRIENDS_ADD_FRIEND, event.param as String);
}
// 用户发起邀请组队请求
void GuildListenerMediator::inviteTeamHander(CCNode *pNode, void *pData)
{
	//			sendNotification(TeamMediator.TEAM_INVITE, int(event.param));
}
// 请求捐献银币界面数据
void GuildListenerMediator::applyDonateViewData(CCNode *pNode, void *pData)
{
	CCMD1D5 param;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_DONATE_REQ
}
// 用户发起捐献银币请求
void GuildListenerMediator::donateHandler(CCNode *pNode, void *pData)
{
	CCMD1D1* param = (CCMD1D1*)pData;
	GateServerSocket::getInstance()->sendMessage( param );//CMSG_COMMU_GUILD_DONATE
// 	var param:CCMD1D1 = event.param as CCMD1D1;
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_DONATE, param);
}


/**===================================公会操作响应码处理====================================*/

//成员职务任免成功
void GuildListenerMediator::appointSuccess()
{
	if(!_view)
		return;
	int duty = _view->_myMemberInfo.dutyValue();	//获取信息更新前的职务
	CCMD1C0 cmd116;
	//if(_view && _view.tabPanel){
		int type116 = 1;	//_view.tabPanel.memOFContr;
		int page116 = _view->_tabPanel->_memberPanel->_pageNav->_curPage;
	//}
	cmd116.a_displayType = type116;
	cmd116.b_memberPage = page116;
	GateServerSocket::getInstance()->sendMessage(&cmd116);//CMSG_COMMU_GUILD_MEMBER_LIST
	if(duty == 4)	//职务变更前是会长
		LangManager::msgShow("GLD030");
	else
		LangManager::msgShow("GLD031");
}

//捐献成功，请求更新后的科技列表
void GuildListenerMediator::donateSuccess()
{
	CCMD1C5 cmd113;
	cmd113.a_page = 1;
	GateServerSocket::getInstance()->sendMessage(&cmd113);//CMSG_COMMU_GUILD_TECH_LIST
}

//被所在公会开除或退出公会
void GuildListenerMediator::expelledMember( string alertStr )
{
	RoleManage::Instance()->accountInfo()->guild = 0;
	RoleManage::Instance()->roleInfo()->playerBaseInfo.guildName("");
	myGuildInfoHandler();
	closeAllView();
	//sendNotification(GuildMediator.CLOSE_ALL_VIEW);
	//Alert.show(alertStr);
}

void GuildListenerMediator::closeAllView()
{
	//if(_view){
	//	_view.close();
	//	_view = null;
	//}
	//if(_preView){
	//	_preView.close();
	//	_preView = null;
	//}
	//if(_editView){
	//	_editView.close();
	//	_editView = null;
	//}
	//if(_donateView){
	//	_donateView.close();
	//	_donateView = null;
	//}
}