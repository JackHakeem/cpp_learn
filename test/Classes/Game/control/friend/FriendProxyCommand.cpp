#include "FriendProxyCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "socket/network/GateServerSocket.h"
#include "model/friend/FriendProxy.h"
#include "model/friend/vo/FriendInfoVo.h"
#include "model/friend/vo/RequestAddInVo.h"
#include "view/friend/FriendMediator.h"
#include "view/friend/FriendListenerMediator.h"
#include "socket/command/c20/CCMD200.h"
#include "socket/command/c20/CCMD204.h"
#include "socket/command/c20/CCMD206.h"
#include "socket/command/c20/CCMD208.h"
#include "socket/command/c20/CCMD20A.h"
#include "socket/command/c20/CCMD20c.h"
#include "socket/command/c21/CCMD210.h"
#include "socket/command/c21/CCMD212.h"
#include "socket/command/c21/CCMD217.h"
#include "socket/command/c21/CCMD21c.h"
#include "socket/command/c21/CCMD21CNode.h"
#include "manager/LangManager.h"
#include "socket/command/s20/SCMD201.h"
#include "socket/command/s20/SCMD205.h"
#include "socket/command/s20/SCMD207.h"
#include "socket/command/s21/SCMD213.h"
#include "socket/command/s21/SCMD216.h"
#include "socket/command/s21/SCMD219.h"

FriendProxyCommand::FriendProxyCommand()
{
	_friendProxy = 0;
}

void FriendProxyCommand::execute(int32 command, char* data)
{
	_friendProxy = (FriendProxy*)g_pFacade->retrieveProxy(AppFacade_Friend_PROXY_CHANGE);

	switch(command)
	{
	case CREATE_FRIENDS_LIST://��װ�����б�
		updateFList((SCMD201*)data);
		break;
	case CREATE_LATER_LIST:
		updateLList((SCMD213*)data);
		break;
	case CREATE_RECOMMEND_LIST://��װ�Ƽ������б�
		updateRList((SCMD205*)data);
		break;
	case CREATE_BLACK_LIST://��װ�������б�
		updateBList((SCMD207*)data);
		break;
	case ADD_LATER_LIST://���췢��˽��ʱ����, ���������ϵ��
		requestForPlayInfo(*(std::string*)data);
		break;
	case CHANGE_LIST_INDEX://�л��б�
		changeListIndex(*(uint32*)data);
		break;
	case CHANGE_LIST_PAGE://��ҳ
		changeListPage(*(uint32*)data);
		break;
	case PAGE_CHANGE_DERECT://ָ��ĳ�б��´�����ҳ��
		setPageDerect(data);
		break;
	case REQUEST_FRIENDS_LIST://��������б�
		requestForFList(*(uint32*)data);
		break;
	case REQUEST_RECOMMEND_LIST://�����Ƽ������б�
		requestForREList(*(uint32*)data);
		break;
	case REQUEST_BLACK_LIST://����������б�
		requestForBList(*(uint32*)data);
		break;
	case ADD_FRIEND://��Ӻ�������
		requestForAddF(*(std::string*)data);
		break;
	case DELETE_FRIEND://ɾ����������
		requestForDELF(*(std::string*)data);
		break;
	case MOVE_TO_BLACK://�Ƶ�������
		requestForMTB(*(std::string*)data);
		break;
	case UPDATE_CURRENT_LIST://����ǰ�б�
		requestForCurrentList();
		break;
	case CHECK_REQUEST://�����������
		checkAddReqHandler(data);
		break;
	case RECEIVE_REQUEST://���պ�������
		receiveRequest((SCMD216*)data);
		break;
	case BLESS_INFO:
		blessInfoHandler((SCMD219*)data);
		break;
	case QUICK_ADD_RECOMMEND_FRIENDS:
		quickAddRecFriHandler();
		break;
	case MOVE_FRIEND_OUT:
		moveOutOfCurrentList(data);
		break;
	case REQUEST_FOR_CHAT://��������
		requestForChat(*(int32*)data);
		break;
	case REQUEST_FOR_TROOP://�������
//					requestForTroop(notification.getBody() as int);
		break;
	default:
		break;
	}

}



/**���º����б�*/
void FriendProxyCommand::updateFList(SCMD201* param)
{
	static bool isFirstOpen = true;
	if (!param || !_friendProxy) return;
	if(_friendProxy->getlistNum() != 0)
		return;
	_friendProxy->resetCurrentList();

	std::list<SCMD201Node>::iterator node;
	for (node = param->c_nodeArr.begin(); node != param->c_nodeArr.end(); node++)
	{
		FriendInfoVo info;
		info.id = node->a_ID;
		info.avatarID = node->b_hiredID;
		info.blessDisable = node->f_fCrystal;
		info.name = node->c_name;
		info.level = node->d_mainLev;
		info.OF = node->e_offLine;
		_friendProxy->addLinkHuman(info);
	}
	struct sdata
	{
		int32 max;
		int32 page;
	};
	sdata head;
	head.max = param->a_total;
	head.page = param->b_page;
	sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, (char*)&head, FriendMediator::UPDATE_LIST );

	if (isFirstOpen && param->c_nodeArr.size()==0)
	{
		//��һ�δ����û���Ѿ�Ҫ��ʾ����Ӻ������Ӻ���
		LangManager::msgShow("FRI019");
	}

	isFirstOpen = false;
}

/**�����½���ϵ���б�*/
void FriendProxyCommand::updateLList(SCMD213* param)
{
	FriendInfoVo fInfo;
	fInfo.avatarID = param->c_avatarId;
	fInfo.id = param->a_playerId;
	fInfo.name = param->b_name;
	fInfo.level = param->d_mainCyLev;
	_friendProxy->addLater(fInfo);
	if (_friendProxy->getlistNum() == 1)
	{
		struct sdata
		{
			int32 max;
			int32 page;
		};
		sdata d;
		d.max = ceil(_friendProxy->totalNum()/10.0f);
		d.page = _friendProxy->getpage();
		sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, (char*)&d, FriendMediator::UPDATE_LIST );
	}
}

/**�����Ƽ������б�*/
void FriendProxyCommand::updateRList(SCMD205* param)
{
	if(_friendProxy->getlistNum() != 2)
		return;
	
	_friendProxy->resetCurrentList();


	std::list<SCMD205Node>::iterator node;
	for (node = param->c_nodeArr.begin(); node != param->c_nodeArr.end(); node++)
	{
		FriendInfoVo info;
		info.id = node->a_ID;
		info.avatarID = node->b_hiredID;
		info.name = node->c_name;
		info.level = node->d_mainLev;
		_friendProxy->addLinkHuman(info);
	}

	struct sdata
	{
		int32 max;
		int32 page;
	};
	sdata head;
	head.max = param->a_total;
	head.page = param->b_page;
	sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, (char*)&head, FriendMediator::UPDATE_LIST );
}

/**���º������б�*/
void FriendProxyCommand::updateBList(SCMD207* param)
{
	if(_friendProxy->getlistNum() != 3)
		return;
	_friendProxy->resetCurrentList();

	std::list<SCMD207Node>::iterator node;
	for (node = param->c_nodeArr.begin(); node != param->c_nodeArr.end(); node++)
	{
		FriendInfoVo info;
		info.id = node->a_ID;
		info.avatarID = node->d_hiredID;
		info.name = node->b_name;
		info.level = node->c_mainLev;
		info.OF = node->f_offLine;
		_friendProxy->addLinkHuman(info);
	}

	struct sdata
	{
		int32 max;
		int32 page;
	};
	sdata head;
	head.max = param->a_total;
	head.page = param->b_page;
	sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, (char*)&head, FriendMediator::UPDATE_LIST );
}

/**�л��б�*/
void FriendProxyCommand::changeListIndex(uint32 index)
{
	_friendProxy->setpage(1);//��ԭ��ǰҳ��
	_friendProxy->setlistNum(index);
	switch(index){
		case 0:
			requestForFList(_friendProxy->getpage());
			break;
		case 1:
			requestForLater(_friendProxy->getpage());
			break;
		case 2:
			requestForREList(_friendProxy->getpage());
			break;
		case 3:
			requestForBList(_friendProxy->getpage());
			break;
	}
}

/**�򿪺���������忪��*/
void FriendProxyCommand::receiveRequest(SCMD216* param)
{
	RequestAddInVo info;
	info.ID = param->a_ID;
	info.hiredID = param->c_hiredID;
	info.name = param->b_name;
	info.mainLev = param->d_mainLev;
	sendNotification(Facade_Mediator, AppFacade_OPEN_FRIENDS_COMMAND, (char*)&info, FriendListenerMediator::OPEN_REQ_PANEL );
}

/**��ҳ*/
void FriendProxyCommand::changeListPage(uint32 page)
{
	_friendProxy->setpage(page);//�п��ܳ�����
	switch(_friendProxy->getlistNum())
	{
		case 0:
			requestForFList(page);
			break;
		case 1:
			requestForLater(page);
			break;
		case 2:
			requestForREList(page);
			break;
		case 3:
			requestForBList(page);
			break;
	}
}

/**
	* ���µ�ǰ�б� 
	* 
	*/		
void FriendProxyCommand::requestForCurrentList()
{
	switch(_friendProxy->getlistNum()){
		case 0:
			requestForFList(_friendProxy->getpage());
			break;
		case 1:
			requestForLater(_friendProxy->getpage());
			break;
		case 2:
			requestForREList(_friendProxy->getpage());
			break;
		case 3:
			requestForBList(_friendProxy->getpage());
			break;
	}
}

/**���Ͳ鿴�����б�����*/
void FriendProxyCommand::requestForFList(uint32 page)
{
	CCMD200* param = new CCMD200();
	if (param)
	{
		param->a_page = page;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD200");
	}
	SAFE_DELETE(param);
}

/**���Ͳ鿴�����ϵ������,���ش���ֱ�ӷ���*/
void FriendProxyCommand::requestForLater(uint32 page)
{
	struct sdata
	{
		int32 max;
		int32 page;
	};
	sdata d;
	d.max = ceil(_friendProxy->totalNum()/10.0f);
	d.page = _friendProxy->getpage();
	sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, (char*)&d, FriendMediator::UPDATE_LIST );
}

/**���Ͳ鿴�Ƽ������б�����*/
void FriendProxyCommand::requestForREList(uint32 page)
{
	CCMD204* param = new CCMD204();
	if (param)
	{
		param->a_page = page;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD204");
	}
	SAFE_DELETE(param);
}

/**���Ͳ鿴�������б�����*/
void FriendProxyCommand::requestForBList(uint32 page)
{
	CCMD206* param = new CCMD206();
	if (param)
	{
		param->a_page = page;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD206");
	}
	SAFE_DELETE(param);
}

/**���������ϵ��ʱ�������������ϵ�˵���ϸ��Ϣ*/
void FriendProxyCommand::requestForPlayInfo(std::string name)
{
	CCMD212* param = new CCMD212();
	if (param)
	{
		param->a_name = name;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD212");
	}
	SAFE_DELETE(param);
}

/**������Ӻ�������*/
void FriendProxyCommand::requestForAddF(std::string name)
{
	CCMD208* param = new CCMD208();
	if (param)
	{
		param->a_name = name;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD208");
	}
	SAFE_DELETE(param);

	LangManager::msgShow("FRI018");
}

/**������Ͻ�������*/
void FriendProxyCommand::requestForMTB(std::string name)
{	
	CCMD20c* param = new CCMD20c();
	if (param)
	{
		param->a_name = name;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD20c");
	}
	SAFE_DELETE(param);

	if(_friendProxy->getlistNum() == 1)
	{
		_friendProxy->deleteHumanByName(name);
		requestForLater();
	}	
}

/**����ϵ�˴ӵ�ǰ�б����Ƴ�*/
void FriendProxyCommand::moveOutOfCurrentList(char* obj)
{
	if(!obj)
		return;
	
	struct sdata
	{
		std::string name;
		int32 position;
	};
	sdata* d;
	d = (sdata*)obj;

	std::string name = d->name;//��ɫ����
	//int32 position = d->position;//��ɫ���б��е�����
	switch(_friendProxy->getlistNum())
	{
	case 1://��ǰΪ�����ϵ���б�
		break;
	case 3://��ǰΪ�������б�
		{
			CCMD210* param = new CCMD210();
			if (param)
			{
				param->a_name = name;
			
				GateServerSocket* pSocket = GateServerSocket::getInstance();
				if (pSocket)
					pSocket->sendMessage(param);

				cocos2d::CCLog("send: CCMD210");
			}
			SAFE_DELETE(param);
		}
		break;
	}
}

/**ɾ����������*/
void FriendProxyCommand::requestForDELF(std::string name)
{
	CCMD20A* param = new CCMD20A();
	if (param)
	{
		param->a_delName = name;
			
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD20A");
	}
	SAFE_DELETE(param);
}

/**
	* �����������Ļذ� 
	* @param obj
	* 
	*/		
void FriendProxyCommand::checkAddReqHandler(char* obj)
{
	if(obj)
	{
		struct sdata 
		{
			std::string name;
			int8 type;
		};
		sdata* sobj = (sdata*)obj;


		CCMD217* param = new CCMD217();
		if (param)
		{
			param->a_name = sobj->name;
			param->b_type = sobj->type;
			GateServerSocket* pSocket = GateServerSocket::getInstance();
			if (pSocket)
				pSocket->sendMessage(param);

			cocos2d::CCLog("send: CCMD217");
		}
		SAFE_DELETE(param);
	}
}

/**
	* �õ����ص�ף����Ϣ 
	* @param param
	* 
	*/		
void FriendProxyCommand::blessInfoHandler(SCMD219* params)
{
	BlessInfoVo info;
	info.limit = params->a_limit;
	info.hasBlessNum = params->b_hasBlessNum;
	info.hasBlessedNum = params->c_hasBlessedNum;

	_friendProxy->setblessInfo(info);

	struct sdata
	{
		int32 max;
		int32 page;
	};
	sdata d;
	d.max = ceil(_friendProxy->totalNum()/10.0f);
	d.page = _friendProxy->getpage();
	sendNotification(Facade_Mediator, AppFacade_Friend_PROXY_CHANGE, 0, FriendMediator::MY_BLESS_INFO );

}

	

/**
	* ��ҷ���һ����ӡ����� 
	* 
	*/		
void FriendProxyCommand::quickAddRecFriHandler()
{
	CCMD21c* param = new CCMD21c();
	if (param)
	{
		std::list<int> ids = _friendProxy->currentIds();
		for (std::list<int>::iterator nodeValue = ids.begin(); nodeValue != ids.end(); nodeValue++)
		{
			CCMD21CNode node;
			node.a_recommendId = *nodeValue;
			param->a_listNode.push_back(node);
		}
		
		GateServerSocket* pSocket = GateServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(param);

		cocos2d::CCLog("send: CCMD21c");
	}
	SAFE_DELETE(param);	

	LangManager::msgShow("FRI018");
}

/**
	* ������������ 
	* @param id
	* 
	*/			
void FriendProxyCommand::requestForChat(int32 id)
{
			
}

		/**
		 * ����������� 
		 * @param id
		 * 
		 */			
//		private function requestForTroop(id:int):void{
//			sendNotification(TeamMediator.TEAM_INVITE, id);
//		}

/**
	* �ظ�ָ�����б���´�����ҳ 
	* @param obj
	* 
	*/		
void FriendProxyCommand::setPageDerect(char* obj)
{
	if(obj)
	{
		struct sdata
		{
			uint32 index;
			uint32 page;
		};
		sdata d = *(sdata*)obj;

		_friendProxy->setDerectPage(d.index, d.page);
	}
}


/*
		private function get socket():GateServerSocket{
			if(!_socket)
				_socket = GateServerSocket.getInstance();
			return _socket;
		}
		*/
