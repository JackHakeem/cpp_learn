//#include "Poco/Platform_WIN32.h"
//#include "Poco/Net/Socket.h"
//#include "Poco/Net/StreamSocket.h"
//#include "Poco/Net/NetException.h"
#include "cocos_socket.h"
#include "GameServerSocket.h"
#include "Packet.h"
#include "manager/LayerManager.h"
//#include "Poco/Net/HTTPClientSession.h"
#include "manager/ConnectionManager.h"
#include "manager/GlobalManage.h"


//using Poco::Net::Socket;
//
//using Poco::Net::StreamSocket;
//using Poco::Net::SocketAddress;
//using Poco::Net::ConnectionRefusedException;
//using Poco::Timespan;
using namespace cocos2d;


GameServerSocket* GameServerSocket::s_NetWorkModule = NULL;
//StreamSocket g_gamess;
cocos_socket_t g_gamess;


GameServerSocket::GameServerSocket(void)
{
	s_NetWorkModule = NULL;
	m_bConnect = false;
	m_refHandler = 0;
	m_bHasRun = false;
}

GameServerSocket::~GameServerSocket(void)
{
}

GameServerSocket* GameServerSocket::getInstance( void )
{
	if (!s_NetWorkModule)
	{
		s_NetWorkModule = new GameServerSocket();
	}

	return s_NetWorkModule;
}

bool GameServerSocket::connect( const std::string& host, unsigned short port )
{
	//Doyang 20120725
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(GameServerSocket::recv), this);

	sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(host.c_str());
	server.sin_port = htons(port);

	g_gamess = cocos_socket(AF_INET, SOCK_STREAM, 0);
	/*
    //Doyang 20120814
    int timeOut = 1000;
    setsockopt(g_gamess, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeOut, sizeof(int));
	setsockopt(g_gamess, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeOut, sizeof(int));
	*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int noSigPipe = 1;
    setsockopt(g_gamess, SOL_SOCKET, SO_NOSIGPIPE, &noSigPipe, sizeof(noSigPipe));
#endif
	int didConnect = cocos_connect(g_gamess, (struct sockaddr *)&server, sizeof(sockaddr_in));
	if (didConnect != 0)
	{
		CCLog("Connect Error!");
		m_bConnect = false;
		return false;
	}

	m_bConnect = true;
	cocos_set_nonblocking(g_gamess);
	/*try
	{
		g_gamess.connect(SocketAddress(host, port));
		m_bConnect = true;
	}
	catch (ConnectionRefusedException&)
	{
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(GameServerSocket::recv), this);
		m_bConnect = false;
		return false;
	}*/

	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(GameServerSocket::recv), this, 0.1f, false);
	//schedule(schedule_selector(CNetWork::recv), 0.1f);
	ConnectionManager::Instance()->setGameSocket(g_gamess);

	return true;
}

void GameServerSocket::recv( float dt )
{
	if (!m_bConnect)
	{
		return;
	}

	char ba[QYMAXLEN] = {0};
	int n = cocos_recv(g_gamess, ba, QYMAXLEN, 0);
	//int n = g_gamess.receiveBytes(ba, QYMAXLEN);
	if (n == 0 && errno != EINTR)
	{
		ConnectionManager::Instance()->didDisConnet();
		return;
	}

	if (n < 0)
	{
		int en = errno;
		//CCLog("errno=%d", en);

		switch (errno)
		{
		case EINTR:
			return;
			break;
		case EWOULDBLOCK:
			return;
			break;
//		case EAGAIN:
//			return;
//			break;
		default:
			{
			//	int en = errno;
		//		CCLog("errno=%d", en);
			}
			break;
		}

	}

	//if(((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)) && n < 0)
	//{
	//	//ConnectionManager::Instance()->didDisConnet();
	//	return;
	//}

	g_packetBuffer.push(ba, n);
	
	if (m_bHasRun)
	{
		return;
	}
	if (m_ps.size()<=0)
	{
		m_ps = g_packetBuffer.getPackets();
		g_packetBuffer.clear();
	}
	
	for( int i=0; i < m_ps.size(); i++ )
	{
		Packet *packet = m_ps[i];

		if (packet->m_nLen > QYMAXLEN)
		{
			packet = 0;
			continue;
		}		

        //PacketID_t id = packet->getPacketID();
        if (packet->m_nLen <= 0)
        {
            continue;
        }
		//if (id == WMSG_WORLD_BATTLE_FINISH)
		//{
		//	continue;
		//}
		
        
        packet->Execute();
        

		if ( LayerManager::loadingPic )
			LayerManager::loadingPic->releaseLock( packet->getPacketID() );

		delete packet;
	} 
	m_ps.clear();
}

void GameServerSocket::sendMessage( Packet *packet )
{
	CCLog("Send packet %x", packet->getPacketID());
	if (m_bConnect == false)
	{
		return;
	}
	//把成员变量写入缓存
	packet->Write();
	//编码发送
	char* ba = packet->encode();
	//g_gamess.sendBytes(ba, packet->m_nLen+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH);
    int sendResult;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendResult = cocos_send(g_gamess, ba, packet->m_nLen+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH, 0);
//#else
//    sendResult = cocos_send_n(g_gamess, ba, packet->m_nLen+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH);
//#endif
	delete ba;
}

void GameServerSocket::registerScriptHandler( int refHandler )
{
	m_refHandler = refHandler;
}

void GameServerSocket::destroyInstance( void )
{
	if ( s_NetWorkModule && s_NetWorkModule->getParent() )
	{
		s_NetWorkModule->removeFromParentAndCleanup(true);
	}
	
	CC_SAFE_DELETE( s_NetWorkModule );
}

void GameServerSocket::visit()
{
	if (g_pGlobalManage->m_bLoadingOver )
	{
		m_bHasRun = false;

		return CCNode::visit();
	}
	//////

	
	packets ps = g_packetBuffer.getPackets();
	for( int i=0; i < ps.size(); i++ )
	{
		m_ps.push_back( ps[i] );
	}	
	g_packetBuffer.clear(); 

	if ( m_ps.size() <= 0 )
	{
		m_bHasRun = true;
		m_ps = g_packetBuffer.getPackets();
		g_packetBuffer.clear();
	}	

	//for( int i=0; i < m_ps.size(); i++ )
	if (m_ps.size()>0)
	{
		int i = 0;
		Packet *packet = m_ps[i];
		if (packet->m_nLen > QYMAXLEN)
		{
			packet = 0;
			m_ps.erase( m_ps.begin() );
			return CCNode::visit();
		}

		packet->Execute();

		if ( LayerManager::loadingPic )
			LayerManager::loadingPic->releaseLock( packet->getPacketID() );

		delete packet;
		m_ps.erase( m_ps.begin() );
	}

	/////

	CCNode::visit();
}
