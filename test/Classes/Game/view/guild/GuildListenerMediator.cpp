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

//�����͹����б�ĵ�������
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
		myGuildInfoHandler();//�õ�����ְλ����Ϣ(MemberVo)
		guildInfoHandler();//�õ��Ѽ���Ĺ�����Ϣ
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
	//_preView.addEventListener(GuildEventConst.GUILD_VIEW, guildInfoHandler);		// �鿴������Ϣ

	_guildDispatcher->addEventListener(GuildEventConst::GUILD_GET_LIST,
		this, callfuncND_selector(GuildListenerMediator::guildListHandler) );       // �鿴�����б�

	_guildDispatcher->addEventListener(GuildEventConst::GUILD_SEARCH,
		this, callfuncND_selector(GuildListenerMediator::guildSearchHandler) );     // ���ҹ���

	_guildDispatcher->addEventListener(GuildEventConst::APPLY_GUILD,
		this, callfuncND_selector(GuildListenerMediator::applyGuildHandler) );     // �������

	_guildDispatcher->addEventListener(GuildEventConst::CREAT_GUILD,
		this, callfuncND_selector(GuildListenerMediator::creatGuildHandler) );     // ��������

	_guildDispatcher->addEventListener( GuildEventConst::OPEN_GUILD_INFO_VIEW,
		this, callfuncND_selector(GuildListenerMediator::openGuildInfoView) );
}

void GuildListenerMediator::viewListener()
{
	//������������
	if(!_view) return;
	GuildDispatcher* _guildDispatcher = GuildDispatcher::getInstance();

	_guildDispatcher->addEventListener(GuildEventConst::REMOVE_GUILD,
		this, callfuncND_selector(GuildListenerMediator::disGuildHandler) );               	// ��ɢ����
	_guildDispatcher->addEventListener(GuildEventConst::REMOVE_GUILD_CANCEL,
		this, callfuncND_selector(GuildListenerMediator::disGuildCancelHandler) );		// ȡ����ɢ����
	_guildDispatcher->addEventListener(GuildEventConst::UPDATE_EMBLEM,
		this, callfuncND_selector(GuildListenerMediator::updateEmblemHandler) );				// ��������
	_guildDispatcher->addEventListener(GuildEventConst::EXIT_GUILD,
		this, callfuncND_selector(GuildListenerMediator::exitGuildHandler) );                	// �˳�����
	_guildDispatcher->addEventListener(GuildEventConst::GUILD_MEMBER_LIST,
		this, callfuncND_selector(GuildListenerMediator::memberListHandler) );        	// �鿴��Ա�б�
	_guildDispatcher->addEventListener(GuildEventConst::LEADER_SHIF,
		this, callfuncND_selector(GuildListenerMediator::appointmentHandler) );					// ת�ƻ᳤
	_guildDispatcher->addEventListener(GuildEventConst::EXPEL_MEMBER,
		this, callfuncND_selector(GuildListenerMediator::expelMemberHandler) );				// ������Ա 
	_guildDispatcher->addEventListener(GuildEventConst::ADD_FRIEND,
		this, callfuncND_selector(GuildListenerMediator::addFriendHandler) );					// ��Ϊ����	
	_guildDispatcher->addEventListener(GuildEventConst::INVITE_TEAM, 
		this, callfuncND_selector(GuildListenerMediator::inviteTeamHander) );					// �������	
	_guildDispatcher->addEventListener(GuildEventConst::GUILD_TECH_LIST,
		this, callfuncND_selector(GuildListenerMediator::tecListHandler) );             	// �鿴�Ƽ��б�
	_guildDispatcher->addEventListener(GuildEventConst::DEGAULT_TECH_CHANGE,
		this, callfuncND_selector(GuildListenerMediator::defaultTecEditHandler) ); 		// �޸�Ĭ�ϿƼ�
	_guildDispatcher->addEventListener(GuildEventConst::GUILD_APPLY_LIST,
		this, callfuncND_selector(GuildListenerMediator::applyListHandler) );          	// �鿴��������б�
	_guildDispatcher->addEventListener(GuildEventConst::APPROVE_MEMBER,
		this, callfuncND_selector(GuildListenerMediator::approvalHandler) );					// ��׼�������
	_guildDispatcher->addEventListener(GuildEventConst::REFUSE_MEMBER,
		this, callfuncND_selector(GuildListenerMediator::approvalHandler) );              	// �ܾ�������� 
	_guildDispatcher->addEventListener(GuildEventConst::OPEN_DONATE_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popDonateViewHandler) );	//�򿪾������Ҵ���
	_guildDispatcher->addEventListener(GuildEventConst::POP_GUILD_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popGuildView) );	//�رչ����б���
	_guildDispatcher->addEventListener(GuildEventConst::POP_PRE_GUILD_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popPreGuildView) );	//�رչ����б���

	//_view.addEventListener(GuildEventConst.OPEN_EDIT_VIEW, popEditViewHandler);
	_guildDispatcher->addEventListener(GuildEventConst::OPEN_EDIT_VIEW,
		this, callfuncND_selector(GuildListenerMediator::popEditViewHandler) );
}

void GuildListenerMediator::editViewListener(bool start)
{
	//�����޸Ĺ�����Ϣ������
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


/** �����޸Ĺ�����Ϣ���� */		
void GuildListenerMediator::popEditViewHandler(CCNode *pNode, void *pData)
{
	sendNotification(Facade_Mediator,
		AppFacade_GUILD_CHANGE, (char*)pData, GuildMediator::OPEN_EDIT_VIEW);
	//this.sendNotification(GuildMediator.OPEN_EDIT_VIEW, {view: editView, VO: e.param as EditGuildInfoVo});
}

/** �����������Ҵ��� */		
void GuildListenerMediator::popDonateViewHandler(CCNode *pNode, void *pData)
{
	//if(_donateView) _donateView.close();
	//_donateView = new DonateView(uint(e.param));
	//applyDonateViewData(null);	//����������������ҽ�������
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

/**================================������Ӧ����˷��ذ�ʱ����=====================================*/

//�½�����ɹ�����
void GuildListenerMediator::newGuildSuccessHandler( SCMD1B7* param )
{
	//if(_preView)
	//	_preView.isPop = false;

	RoleManage::Instance()->accountInfo()->guild = param->a_guildId;	//�����˺Ź���id

	int a = 0;
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, &a);	//�򿪹������
	myGuildInfoHandler();//��������Ĺ����Ա��Ϣ
	guildInfoHandler();//�õ��Ѽ���Ĺ�����Ϣ
}

//�鿴�����б�
void GuildListenerMediator::getGListHandler( SCMD1B2* param )
{
	sendNotification(Facade_Command, AppFacade_GUILD_START, (char*)param, GuildChangeCommand::CREATE_GUILD_LIST);

	//g_pGuildMediator->setGuildList( (char*)param );
}

////���ҹ��᷵�ع����
//private function getFGHandler(param:SCMD1B4)
//{
//	//�ݲ�ʹ��
//}
//������������б�
void GuildListenerMediator::getApListHandler( SCMD1BC* param )
{
	sendNotification(Facade_Command, AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_CHECK_LIST);
	//this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_CHECK_LIST);
	guildInfoHandler();//�������󹫻���Ϣ
}
//�������鿴�Ĺ�����Ϣ
void GuildListenerMediator::getGInfoHandler( SCMD1BF* param )
{
	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_GUILD_INIT_INFO);
}

//���ع����Ա�б�(��ҳ)
void GuildListenerMediator::getMBListHandler( SCMD1C1* param )
{
	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_MEMBER_LIST);
	//this.sendNotification(AppFacade.GUILD_START, param,GuildChangeCommand.GET_MEMBER_LIST);
	//			guildInfoHandler();//�������󹫻���Ϣ
}

//�������鿴�ĳ�Ա��Ϣ
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

//���ز鿴�ĿƼ��б��
void GuildListenerMediator::getTEListHandler( SCMD1C6* param )
{
	sendNotification(Facade_Command,
		AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GET_TECH_LIST);
	guildInfoHandler();//�������󹫻���Ϣ
}

//���������Ӧ��
void GuildListenerMediator::oprateHandler( SCMD1C7* param )
{
	switch(param->a)
	{
	case 105:		//��������ɹ�
		RoleManage::Instance()->accountInfo()->guild = 1;
		guildInfoHandler();
		LangManager::msgShow("GLD002");
		break;
	case 151:		//Ҫ�����Ĺ��������Ѵ���
		//LangManager.alertShow("GLD003");
		LangManager::msgShow("GLD003");
		break;
	case 152:		//������������Ҳ���
		LangManager::msgShow("GLD004");
		break;
	case 161:
		{
			CCMD1BE cmd;
			GateServerSocket::getInstance()->sendMessage(&cmd);//CMSG_COMMU_GUILD_INFO
			LangManager::msgShow("GLD005");
		}
		break;
	case 162:		//��������ʧ��
		LangManager::msgShow("GLD006");
		break;
	case 166:		//���׳ɹ���������º�ĿƼ��б�
		donateSuccess();
		break;
	case 167:		//������������
		LangManager::msgShow("GLD007");
		break;
	case 171:		//����ְ��ɹ���ˢ�³�Ա�б�
		appointSuccess();
		myGuildInfoHandler();	//�����Լ�����Ϣ
		break;
	case 172:		//��Ա������
		LangManager::msgShow("GLD008");
		break;
	case 173:		//���᳤������
		LangManager::msgShow("GLD009");
		break;
	case 174:		//�������󲻴���,�����ѱ�ɾ��
		LangManager::msgShow("GLD010");
		break;
	case 175:		//�����ϴ�ת�ƻ᳤��������
		LangManager::msgShow("GLD011");
		break;
	case 176:		//�½������ڲ���ת��
		LangManager::msgShow("GLD012");
		break;
	case 186:		//�����ڹ����߳�
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
	case 220://������������
		LangManager::msgShow("GLD018");
		break;
	case 221:
		expelledMember(LangManager::getText("GLD019"));
		break;
	}
}

//������������������������״̬���ᷢ���᳤��
void GuildListenerMediator::getApplyHandler(SCMD1CB* param)
{
	switch(param->b_retNum)
	{
	case 0:
		//������ᱻͨ����������������ߣ�Ҳ���������ߣ�
		if( _view  && _view->getisPop())
		{
			//���������ߣ������������µ�����б�
			CCMD1BB cmd;
			cmd.a_page = 1;//_view.curPage
			GateServerSocket::getInstance()->sendMessage(&cmd);
			//_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_APPLY_LIST, new Int16(_view.curPage));
		}
		else if (!_view || (_view && !_view->getisPop()))
		{
			//������������ߣ������ҵĹ�����Ϣ����֪ͨ�������
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
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, &a);	//�򿪹������
		}
		break;
	case 1:		//������������
		LangManager::msgShow("GLD021");
		break;
	case 2:		//�Է��Ѽ�����������
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

//�յ�����˷����˳���������
void GuildListenerMediator::exitGuildReturnHandler(SCMD1CD* param)
{
	if(param->a_flag == 0)
	{
		//�ɹ��˳�����
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

//���ս��վ������ޡ��Ѿ�����
void GuildListenerMediator::receiveDonateData( SCMD1D6* param )
{
	DonateView* _donateView = (DonateView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview);
	if (!_donateView) return;
	_donateView->setdonateMax(param->a_limit);
	_donateView->setdonated(param->b_donate);
	_donateView->update();
	_donateView->setIsVisible(true);
}

//������������ʾ
void GuildListenerMediator::showGuildTip(SCMD1B8* param)
{
	sendNotification( Facade_Command, AppFacade_GUILD_START, (char*)param, GuildChangeCommand::GUILD_TIPS );
}

/**===================================����ͻ��˲���==================================*/

//ȡ���Լ��Ĺ�����Ϣ
void GuildListenerMediator::openGuildInfoView(CCNode *pNode, void *pData)
{
	GuildInfoView* _infoView = new GuildInfoView(*(GuildInfoVo*)pData);
	_infoView->init();
	LayerManager::intervalLayer->addChild(
		_infoView, IntervalLayer::IntervalLayerZ_guild_info, IntervalLayer::IntervalLayerTAG_guild_info);
	_infoView->release();

}

//ȡ���Լ��Ĺ�����Ϣ
void GuildListenerMediator::myGuildInfoHandler()
{
	CCMD1C2 param;
	param.a_pName = RoleManage::Instance()->accountInfo()->name;
	param.b_code = 0;
	param.c_type = 0;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_MEMBER_INFO
}

//�޸Ĺ�����Ϣ
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

//�û������½���������
void GuildListenerMediator::creatGuildHandler(CCNode *pNode, void *pData)
{
	//Э���:CMSG_COMMU_GUILD_NEW = 0x1B0
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
//�û�����鿴�����б�����
void GuildListenerMediator::guildListHandler(CCNode *pNode, void *pData)
{
	CCMD1B1 param;
	param.a_page = *(int16*)pData;
	GateServerSocket::getInstance()->sendMessage(&param);//CMSG_COMMU_GUILD_GET_LIST
} 
//�û�������ҹ�������
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
//�û�����Ľ�ɢ��������
void GuildListenerMediator::disGuildHandler(CCNode *pNode, void *pData)
{
	CCMD1B5 cmd;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_DISSOLVE
}
//�û������ȡ����ɢ��������
void GuildListenerMediator::disGuildCancelHandler(CCNode *pNode, void *pData)
{
	CCMD1B6 cmd;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_DISSOLVE_CANCEL
}
//�û�����������Ա����
void GuildListenerMediator::appointmentHandler(CCNode *pNode, void *pData)
{
	CCMD1B9* cmd = (CCMD1B9*)pData;
	GateServerSocket::getInstance()->sendMessage(cmd);	//CMSG_COMMU_GUILD_NOMINATE
} 
//�û������������
void GuildListenerMediator::applyGuildHandler(CCNode *pNode, void *pData)
{
	CCMD1BA cmd;
	cmd.a_guildName = (char*)pData;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_APPLY
	//_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_APPLY, event.param);
}  
//�û�����鿴��������б�����
void GuildListenerMediator::applyListHandler(CCNode *pNode, void *pData)
{
	CCMD1BB cmd;
	cmd.a_page = *(int16*)pData;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//CMSG_COMMU_GUILD_APPLY_LIST
}
//�û����������������
void GuildListenerMediator::approvalHandler(CCNode *pNode, void *pData)
{
	CCMD1BD* cmd = (CCMD1BD*)pData;
	GateServerSocket::getInstance()->sendMessage(cmd);	//SocketCMDConst.CMSG_COMMU_GUILD_APPLY_HANDLE
}

//�û�����鿴������Ϣ����
void GuildListenerMediator::guildInfoHandler()
{
	CCMD1BE cmd;
	GateServerSocket::getInstance()->sendMessage(&cmd);	//SocketCMDConst.CMSG_COMMU_GUILD_INFO
}

//�û�����鿴��Ա�б�����
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
//�û�����鿴��Ա��Ϣ����
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
//�û������޸�Ĭ�ϿƼ�����
void GuildListenerMediator::defaultTecEditHandler(CCNode *pNode, void *pData)
{
	CCMD1C4* param = (CCMD1C4*)pData;
	GateServerSocket::getInstance()->sendMessage( param );//CMSG_COMMU_GUILD_DEFAULT_TECH
}
//�û�����鿴�Ƽ��б�����
void GuildListenerMediator::tecListHandler(CCNode *pNode, void *pData)
{
// 	var obj:Object = event.param as Object;
// 	if(obj && obj.page){
	CCMD1C5 param;
	param.a_page = *(int*)pData;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_TECH_LIST
// 	}
}      
//�û������߳���Ա����
void GuildListenerMediator::expelMemberHandler(CCNode *pNode, void *pData)
{
	CCMD1CA* cmd = (CCMD1CA*)pData;
	GateServerSocket::getInstance()->sendMessage( cmd );//CMSG_COMMU_GUILD_KICK_MEMBER
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_KICK_MEMBER, param);
}
//�û�����������������
void GuildListenerMediator::updateEmblemHandler(CCNode *pNode, void *pData)
{
	CCMD1CF param;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_FLAG_UPDATE
}
//�û������޸Ĺ�����Ϣ����
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
//�û������˳���������
void GuildListenerMediator::exitGuildHandler(CCNode *pNode, void *pData)
{
	CCMD1CC param;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_QUIT
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_QUIT);
}
// �û������Ϊ��������
void GuildListenerMediator::addFriendHandler(CCNode *pNode, void *pData)
{
	CCMD208 param;
	param.a_name = *(char*)pData;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_FRIENDS_ADD_FRIEND
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_FRIENDS_ADD_FRIEND, event.param as String);
}
// �û����������������
void GuildListenerMediator::inviteTeamHander(CCNode *pNode, void *pData)
{
	//			sendNotification(TeamMediator.TEAM_INVITE, int(event.param));
}
// ����������ҽ�������
void GuildListenerMediator::applyDonateViewData(CCNode *pNode, void *pData)
{
	CCMD1D5 param;
	GateServerSocket::getInstance()->sendMessage( &param );//CMSG_COMMU_GUILD_DONATE_REQ
}
// �û����������������
void GuildListenerMediator::donateHandler(CCNode *pNode, void *pData)
{
	CCMD1D1* param = (CCMD1D1*)pData;
	GateServerSocket::getInstance()->sendMessage( param );//CMSG_COMMU_GUILD_DONATE
// 	var param:CCMD1D1 = event.param as CCMD1D1;
// 	_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_GUILD_DONATE, param);
}


/**===================================���������Ӧ�봦��====================================*/

//��Աְ������ɹ�
void GuildListenerMediator::appointSuccess()
{
	if(!_view)
		return;
	int duty = _view->_myMemberInfo.dutyValue();	//��ȡ��Ϣ����ǰ��ְ��
	CCMD1C0 cmd116;
	//if(_view && _view.tabPanel){
		int type116 = 1;	//_view.tabPanel.memOFContr;
		int page116 = _view->_tabPanel->_memberPanel->_pageNav->_curPage;
	//}
	cmd116.a_displayType = type116;
	cmd116.b_memberPage = page116;
	GateServerSocket::getInstance()->sendMessage(&cmd116);//CMSG_COMMU_GUILD_MEMBER_LIST
	if(duty == 4)	//ְ����ǰ�ǻ᳤
		LangManager::msgShow("GLD030");
	else
		LangManager::msgShow("GLD031");
}

//���׳ɹ���������º�ĿƼ��б�
void GuildListenerMediator::donateSuccess()
{
	CCMD1C5 cmd113;
	cmd113.a_page = 1;
	GateServerSocket::getInstance()->sendMessage(&cmd113);//CMSG_COMMU_GUILD_TECH_LIST
}

//�����ڹ��Ὺ�����˳�����
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