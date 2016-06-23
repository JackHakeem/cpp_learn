#include "ChatMediator.h"
#include "control/AppFacade.h"

#include "manager/ViewManager.h"
#include "mvc/Facade.h"

#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"

#include "socket/network/GameServerSocket.h"
#include "events/GameDispatcher.h"
#include "manager/PopManage.h"
#include "manager/GlobalManage.h"

#include "utils/ValuesUtil.h"
#include "components/ChatView.h"
#include "components/ChatPopContainer.h"
#include "model/chat/ChannelType.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/chat/ChatInfo.h"
#include "events/GameDispatcher.h"

#include "components/ChatMsgManager.h"
#include "socket/command/c19/CCMD190.h"
#include "socket/command/c19/CCMD192.h"
#include "socket/command/c19/CCMD196.h"
#include "socket/network/GateServerSocket.h"
#include "manager/LangManager.h"
#include "components/ChatView.h"

ChatMediator::ChatMediator()
{
	_dispatcher = 0;
	_chatPopContainer = 0;
	_gmView = 0;
	_pmView = 0;
	_isInFight = false;	//防止重复战斗
	//_bankProxy = (BankProxy*)g_pFacade->retrieveProxy(AppFacade_BANK_PROXY_CHANGE);

	_dispatcher = GameDispatcher::getInstance();
	//_dispatcher->addEventListener(GameDispatcher::BANK_CHANGE, this, callfuncND_selector(BankMediator::packChange));
	//_dispatcher->addEventListener(PopEventName::SHOW_UI_BANK, this, callfuncND_selector(BankMediator::bankPopHandle));
}

/*
void BankMediator::initWorldBag(char* data)
{
	sendNotification(Facade_Command, AppFacade_BAG_PROXY_CHANGE, data, BagProxyCommand::CREATE_GOODS_LIST);//这里要通知控制层处理
}
*/
void ChatMediator::handleNotification(int M2Vcmd, char* data)
{
	//switch(M2Vcmd)
	//{
	//case CREATE_LIST:
	//	createList();
	//	//bagPop();//kktest
	//	break;
	//case BANK_ITEM_UPDATE:
	//	bankUpdate(data);
	//	break;
	//case BANK_ITEM_TIP_UPDATE:
	//	updateTip( data );
	//	break;
	//case BANK_CLOSE:
	//	break;
	//default:
	//	break;
	//}
}


void ChatMediator::showChatViewHandler()
{
	startUpChatView();
}

/* 添加聊天窗口到界面 */		
void ChatMediator::startUpChatView()
{
	_chatPopContainer = (ChatPopContainer*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chat);
	if (!_chatPopContainer)
	{
		_chatPopContainer = new ChatPopContainer();
		_chatPopContainer->init();
		LayerManager::intervalLayer->addChild(_chatPopContainer, IntervalLayer::IntervalLayerZ_chat, IntervalLayer::IntervalLayerTAG_chat);
		_chatPopContainer->release();

		_dispatcher->addEventListener(GameDispatcher::PRIVATE_CHAT, this, callfuncND_selector(ChatMediator::pmChat));		//私聊接口（需传入聊天对象）
		_chatPopContainer->addEventListener(ChatPopContainer::SEND_CHAT_MESSAGE, this,callfuncND_selector(ChatMediator::sendMessage));
	}	
	else
	{
		_chatPopContainer->release();
		return;
	};

	addLoginTip();	//添加登录成功后健康游戏忠告

	if (_chatPopContainer)
	{
		_chatPopContainer->reinitChatRecord(ChatMsgManager::Instance()->messagesData[ChannelType::ALL]);
	}
}

/**
	* 登录提示 
	*/		
void ChatMediator::addLoginTip()
{
	std::string loginTip = ValuesUtil::Instance()->getString("CHT001");
	if(_chatPopContainer) 
		_chatPopContainer->loginTip(loginTip);
}

/* 私聊接口 */
void ChatMediator::pmChat(CCNode* n, void* data)
{
	std::string param = *(std::string*)data;
	_chatPopContainer->setPrivateChat(param);	//e.param 为私聊对象
}

/* 世界聊天  */		
void ChatMediator::onWorldChat(SCMD191* param)
{
	struct vdata
	{
		int32 a_id;
		std::string b_name;
		std::string c_content;
		std::string d_data;
		int8 d_line;
		std::string f_toName;
		int8 e_accountType;
	};
	vdata d;
	d.a_id = param->a_id;
	d.b_name = param->b_name;
	d.c_content = param->c_content;
	d.d_data = param->d_line;
	d.f_toName = "";
	d.d_line = param->d_line;
	d.e_accountType = param->e_accountType;

	CCLog("chat content : %s" , param->c_content.c_str());
	CCLog("chat data : %s" , param->d_data.c_str());

	chatResponse(ChannelType::WORLD, (char*)&d);
}
		

/* 公会聊天 */	
void ChatMediator::onGuildChat(SCMD193* param)
{
	struct vdata
	{
		int32 a_id;
		std::string b_name;
		std::string c_content;
		std::string d_data;
		int8 d_line;
		std::string f_toName;
		int8 e_accountType;
	};
	vdata d;
	d.a_id = param->a_id;
	d.b_name = param->b_name;
	d.c_content = param->c_content;
	d.d_data = param->d_line;
	d.f_toName = "";
	d.d_line = param->d_line;
	d.e_accountType = param->e_accountType;

	chatResponse(ChannelType::GUILD, (char*)&d);
}

ChatPopContainer* ChatMediator::getThisView()
{
	ChatPopContainer* chatPopContainer = (ChatPopContainer*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chat);
	if (chatPopContainer)
	{		
		return chatPopContainer;
	}

	return 0;
}
		
/* 私人聊天  */	
void ChatMediator::onPrivateChat(SCMD197* param)
{
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	bool self = (info->name == param->b_fromName);
	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = ChannelType::PRIVATE;
	msgInfo.fromId = param->a_fromId;
	msgInfo.fromName = param->b_fromName;
	msgInfo.content = param->c_content;
	msgInfo.data = param->d_data;
	msgInfo.line = param->d_line;
	msgInfo.isPerson = true;
	msgInfo.isSelf = self;
	msgInfo.toId = param->e_toId;
	msgInfo.toName = param->f_toName;
	msgInfo.isGM = (param->g_accountType==3);

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面


	if (getThisView())
	{
		_chatPopContainer->addChatRecord(&msgInfo);
	}
	//receiveTip(ChannelType.PRIVATE);
	//分发到主界面聊天泡泡
    if (!LayerManager::sceneUILayer)
        return;

	
	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->addChatRecord(&msgInfo);
	}
	
}

/**
	* 向服务器端提取不同频道的聊天信息 
	* @param channel 消息频道
	* @param cmd 消息包(SCMD191, SCMD193)
	*/		
void ChatMediator::chatResponse(uint32 channel, char* cmd)
{
	if (!cmd) return;
	struct vdata
	{
		int32 a_id;
		std::string b_name;
		std::string c_content;
		std::string d_data;
		int8 d_line;
		std::string f_toName;
		int8 e_accountType;
	};
	vdata d = *(vdata*)cmd;
	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = channel;
	msgInfo.fromId = d.a_id;
	msgInfo.fromName = d.b_name;
	msgInfo.content = d.c_content;
	msgInfo.data = d.d_data;
	msgInfo.line = d.d_line;
	msgInfo.isGM = (d.e_accountType==3);

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面
	if (_chatPopContainer)
	{
		_chatPopContainer->addChatRecord(&msgInfo);
	}
	//分发到主界面聊天泡泡
    if (!LayerManager::sceneUILayer)
        return;


	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->addChatRecord(&msgInfo);
	}
	
	
//	receiveTip(channel);
}

/**
	* 聊天异常 
	*/		
void ChatMediator::onChatError(SCMD199* param)
{
	if (!param)
		return;

	std::string s = "";
	switch(param->a_err)
	{
		case 41:
			{
				s = ValuesUtil::Instance()->getString("CHT010");
				//_chatPopContainer->setPrivateChat(ChannelType::intFlagToStringName(ChannelType::WORLD_STRING));
				
				//_chatView->systemTip(s, LangManager.getText("CHT014"), ChannelType.PRIVATE);
				//return;
			}
			break;
		case 42:
			s = ValuesUtil::Instance()->getString("CHT011");
			//LangManager::msgShow("CHT011");
			break;
		case 43:
			s = ValuesUtil::Instance()->getString("CHT012");
			//LangManager::msgShow("CHT012");
			break;
		case 44:
			s = ValuesUtil::Instance()->getString("CHT013");
			//LangManager::msgShow("CHT013");
			break;
	}


	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = ChannelType::ALL;
	msgInfo.content = s;

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面
	if (_chatPopContainer)
	{
		_chatPopContainer->systemTip(&msgInfo);
	}
	//分发到主界面聊天泡泡
    if (!LayerManager::sceneUILayer)
        return;

	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->systemTip(&msgInfo);
	}
	
}

void ChatMediator::specialSystemTips()
{
	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = ChannelType::ALL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	msgInfo.content = ValuesUtil::Instance()->getString("CHT0531");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    msgInfo.content = ValuesUtil::Instance()->getString("CHT0532");
#else
    msgInfo.content = ValuesUtil::Instance()->getString("CHT0531");
#endif

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面
	if (_chatPopContainer)
	{
		_chatPopContainer->systemTip(&msgInfo);
	}
	//分发到主界面聊天泡泡
    if (!LayerManager::sceneUILayer)
        return;

	
	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->systemTip(&msgInfo);
	}
	
}

// 公告
void ChatMediator::SystemNoticeCast(std::string content)
{
	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = ChannelType::SYS_NOTICE;
	msgInfo.content = content;
	msgInfo.isGM = true;

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面
	if (_chatPopContainer)
	{
		_chatPopContainer->systemTip(&msgInfo);
	}
	//分发到主界面聊天泡泡
	if (!LayerManager::sceneUILayer)
		return;

	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->systemTip(&msgInfo);
	}
	
}

// 成就
void ChatMediator::SystemAchiveCast(std::string content)
{
	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = ChannelType::SYS_ACHIVE;
	msgInfo.content = content;
	msgInfo.isGM = true;

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面
	if (_chatPopContainer)
	{
		_chatPopContainer->systemTip(&msgInfo);
	}
	//分发到主界面聊天泡泡
	if (!LayerManager::sceneUILayer)
		return;

	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->systemTip(&msgInfo);
	}
	
}

//充值
void ChatMediator::SystemChargeCast(std::string content)
{
	ChatInfo msgInfo = ChatInfo();
	msgInfo.channel = ChannelType::SYS_CHARGE;
	msgInfo.content = content;
	msgInfo.isGM = true;

	ChatMsgManager::Instance()->addMessage(&msgInfo);
	//分发到聊天界面
	if (_chatPopContainer)
	{
		_chatPopContainer->systemTip(&msgInfo);
	}
	//分发到主界面聊天泡泡
	if (!LayerManager::sceneUILayer)
		return;


	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		chatview->systemTip(&msgInfo);
	}
	
}

		/**
		 * 检测客户端命令，用于测试，测试完毕后第一行 return false; 关闭
		 * @param content 消息内容
		 */		
		//private function clientCmd(content:String):Boolean{
		//	return false;	//关闭所有客户端命令
		//	var msg:String = "";
		//	switch(content){
		//		case "#clear":
		//			if(_chatView) _chatView.textPanel.clearMessage(false);
		//			return true;
		//		case "#clearall":
		//			if(_chatView) _chatView.textPanel.clearMessage(true);
		//			return true;
		//		case "#fcm":
		//			GlobalManage.getInstance().isFCM = !GlobalManage.getInstance().isFCM;
		//			var isFCM:Boolean = GlobalManage.getInstance().isFCM; 
		//			_chatView.systemTip(isFCM ? "防沉迷已开启" : "防沉迷已关闭", "提示");
		//			return true;
		//	}
		//	if(content.length>8 && content.substr(0, 8) == "#notice "){
		//		msg = content.substr(8);
		//		Message.show(msg, 0xFF0000);
		//		return true;
		//	}
		//	return false;
		//}


/**
	* 向服务器端发送聊天信息 
	* @param e
	*/		
void ChatMediator::sendMessage(CCNode* n, void* data)
{
	struct MSGOBJ
	{
		std::string name;
		int32 channel;
		std::string msg;
		std::string data;
	};
	MSGOBJ eparam = *(MSGOBJ*)data;
	std::string content = eparam.msg;

	//if(clientCmd(content)) return;
	switch(eparam.channel)
	{
	case ChannelType::WORLD:
		{
			CCMD190* cmd1 = new CCMD190();
			if (cmd1)
			{
				cmd1->a_content = eparam.msg;
				cmd1->b_data = eparam.data;
				GateServerSocket* pSocket = GateServerSocket::getInstance();
				pSocket->sendMessage(cmd1);	
			}
					
			SAFE_DELETE(cmd1);
		}
		break;
	case ChannelType::GUILD:
		{
			CCMD192* cmd1 = new CCMD192();
			if (cmd1)
			{
				cmd1->a_content = eparam.msg;
				cmd1->b_data = eparam.data;
				GateServerSocket* pSocket = GateServerSocket::getInstance();
				pSocket->sendMessage(cmd1);	
			}
					
			SAFE_DELETE(cmd1);
		}
		break;
	default://私聊
		{
			CCMD196* cmd3 = new CCMD196();
			if (cmd3)
			{
				cmd3->a_name = eparam.name;
				cmd3->b_content = eparam.msg;
				cmd3->c_data = eparam.data;
				GateServerSocket* pSocket = GateServerSocket::getInstance();
				pSocket->sendMessage(cmd3);	
			}
					
			SAFE_DELETE(cmd3);		
		}
	break;
	}
}
