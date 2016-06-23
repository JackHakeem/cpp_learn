#ifndef _SOCKET_INCLUDE__
#define _SOCKET_INCLUDE__
#include "socket/network/cocos_socket.h"
#endif

#include "ConnectionManager.h"
#include "MessageInfoBox.h"
#include "utils/ValuesUtil.h"
#include "LoginManage.h"
#include "socket/network/GateServerSocket.h"
#include "LayerManager.h"

#define MAX_RETRY_COUNT (20)
#define MAX_DIS_COUNT (20)
#define DELTA_CHECK_TIME (5.0f)

ConnectionManager::ConnectionManager()
{
	_nCount = 0;
	_nCountDisCon = 0;
	_isConnect = true;
}

void ConnectionManager::CheckStep(ccTime dt)
{
	int ret = ConnectionCheck(10);
	if (ret == -1)
	{
		++_nCount;
		if (_nCount >= MAX_RETRY_COUNT)
		{
			MessageInfoBox::Instance()->show(
				ValuesUtil::Instance()->getString("WLC003"),
				ccc3(255,12,12),
				menu_selector(ConnectionManager::ReConnect),
				ValuesUtil::Instance()->getString("LG038"));
			--_nCount;
			//stop();
		}		
	}
	else
	{
		_nCount = 0;
	}
}

int ConnectionManager::ConnectionCheck(int millisecond)
{
	
	//int socket = getGateSocket();
	int socket = getGameSocket();

	fd_set readable;
	FD_ZERO(&readable);
	FD_SET(socket, &readable);

	timeval timeout;
	timeout.tv_sec = millisecond / 1000;
	timeout.tv_usec = (millisecond % 1000) * 1000;

	//cocos_set_nonblocking(socket);
	//int ret = cocos_waitfor_readable(socket,millisecond);
	int ret1 = select(socket+1, &readable, NULL, NULL, &timeout);
	char buf[128];
	int ret2 = cocos_recv(socket, buf,1,0);
	if ((ret1 == 1)&&(ret2 <= 0)&&(errno != EINTR))
	{
		return -1;
	}
	return 0;
}

void ConnectionManager::ReConnect(CCObject * pSender)
{
	// add code here
	//
	/*
	MessageInfoBox::Instance()->clickClose(0);
	*/
	
	_nCount = 0;


	if(g_pLoginManage)
	{
		//Doyang 20120725
		if(g_pLoginManage)
		{
			g_pLoginManage->_ignoreSoketsList[LoginManage::IS_SCMD107] = true;
		}
		bool result = GateServerSocket::getInstance()->connect(g_pLoginManage->getServIPAddr(), g_pLoginManage->getServIPPort());//"113.107.110.141", 83     115.238.73.228 121   
		if (result)
		{
			_isConnect = true;
			CCLog(">Connect to GateServer succ");
			//Message::Instance()->show(ValuesUtil::Instance()->getString("LG024"),ccc3(12,233,25),0.5);
			g_pLoginManage->gSocketConnectHandler();
		}
		else
		{
			CCLog(">Connect GateServer fail");
			CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
			//MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("LG023"),ccc3(12,233,25));
			//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::GATE_SERVER_CONNECT_FAILED, NULL);
		}
	}
}

void ConnectionManager::run()
{
	//CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(ConnectionManager::CheckStep),this,DELTA_CHECK_TIME,false);
}

void ConnectionManager::stop()
{
	//CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(ConnectionManager::CheckStep),this);
}

void ConnectionManager::didDisConnet()
{
	if(!_isConnect)
	{
		return;
	}
	_nCount ++;
	if(_nCount > MAX_RETRY_COUNT)
	{
		_isConnect = false;

		/*
		MessageInfoBox::Instance()->show(
			ValuesUtil::Instance()->getString("WLC003"),
			ccc3(255,12,12),
			menu_selector(ConnectionManager::onDisConnectMenuClick));
			*/
		/*
		MessageInfoBox::Instance()->show(
			ValuesUtil::Instance()->getString("WLC003"),
			ccc3(255,12,12),
			menu_selector(ConnectionManager::ReConnect),
			ValuesUtil::Instance()->getString("LG038"));
			*/

		ReConnect(0);

		_nCount = 0;

		++_nCountDisCon;
		if (_nCountDisCon > MAX_DIS_COUNT)
		{
			_nCountDisCon = 0;

			MessageInfoBox::Instance()->show(
				ValuesUtil::Instance()->getString("WLC003"),
				ccc3(255,12,12),
				menu_selector(ConnectionManager::onDisConnectMenuClick));

		}
		
	}	
}

//Doyang 20120814
void ConnectionManager::onDisConnectMenuClick(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
