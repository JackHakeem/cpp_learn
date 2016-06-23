//#include "Poco/Platform_WIN32.h"
//#include "Poco/Net/Socket.h"
//#include "Poco/Net/StreamSocket.h"
//#include "Poco/Net/NetException.h"
#include "cocos_socket.h"
#include "GateServerSocket.h"
#include "Packet.h"
#include "manager/ConnectionManager.h"



//using Poco::Net::Socket;
//
//using Poco::Net::StreamSocket;
//using Poco::Net::SocketAddress;
//using Poco::Net::ConnectionRefusedException;
//using Poco::Timespan;
using namespace cocos2d;


GateServerSocket* GateServerSocket::s_NetWorkModule = NULL;
//StreamSocket g_gatess;
cocos_socket_t g_gatess;

const int time_out = 5000;

GateServerSocket::GateServerSocket(void)
{
	s_NetWorkModule = NULL;
	m_bConnect = false;
	m_refHandler = 0;
}

GateServerSocket::~GateServerSocket(void)
{
}

GateServerSocket* GateServerSocket::getInstance( void )
{
	if (!s_NetWorkModule)
	{
		s_NetWorkModule = new GateServerSocket();
	}

	return s_NetWorkModule;
}

bool GateServerSocket::connect( const std::string& host, unsigned short port )
{
	//Doyang 20120725
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(GateServerSocket::recv), this);

	sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(host.c_str());
	server.sin_port = htons(port);

	g_gatess = cocos_socket(AF_INET, SOCK_STREAM, 0);
    //Doyang 20120814
    int timeOut = 1000;
    int noSigPipe = 1;
    setsockopt(g_gatess, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeOut, sizeof(int));
    setsockopt(g_gatess, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeOut, sizeof(int));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    setsockopt(g_gatess, SOL_SOCKET, SO_NOSIGPIPE, &noSigPipe, sizeof(noSigPipe));
#endif
	int didConnect = cocos_connect(g_gatess, (struct sockaddr *)&server, sizeof(sockaddr_in));
	if (didConnect != 0)
	{
		CCLog("Connect Error!");
		m_bConnect = false;
		return false;
	}
	
	m_bConnect = true;
	cocos_set_nonblocking(g_gatess);


	/*try
	{
	g_gatess.connect(SocketAddress(host, port));
	m_bConnect = true;
	}
	catch (ConnectionRefusedException&)
	{
	m_bConnect = false;
	return false;
	}*/

	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(GateServerSocket::recv), this, 0.1f, false);
	//schedule(schedule_selector(CNetWork::recv), 0.1f);
	ConnectionManager::Instance()->setGateSocket(g_gatess);

	return true;
}

void GateServerSocket::recv( float dt )
{
	if (!m_bConnect)
	{
		return;
	}

	//int waitResult = cocos_waitfor_readable(g_gatess, time_out);
	//if(waitResult == 1)
	//{
	//	// ok.


	//}
	//else 
	//{
	//	// error.
	//}

	/*Timespan timeout;

	g_gatess.poll(timeout, Socket::SELECT_READ);

	if (!g_gatess.available())
	{
		return;
	}*/

	/*Socket::SocketList readList;
	Socket::SocketList writeList;
	Socket::SocketList exceptList;

	readList.push_back(g_gatess);

	int ii = Socket::select(readList, writeList, exceptList, timeout);
	if (!ii)
	{
		return;
		}*/
	char ba[QYMAXLEN] = {0};
	int n = cocos_recv(g_gatess, ba, QYMAXLEN, 0);

	//int n = g_gatess.receiveBytes(ba, QYMAXLEN);

	if (n == 0 && errno != EINTR) // 0821
	{
		ConnectionManager::Instance()->didDisConnet();
		return;
	}

	if(n < 0 && ((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)))
	{
		//ConnectionManager::Instance()->didDisConnet();
		return;
	}

	g_packetBuffer.push(ba, n);

	packets ps = g_packetBuffer.getPackets();

	for( int i=0; i < ps.size(); i++ )
	{
		Packet *packet = ps[i];

		/*if(packet->m_state == false)
			continue;*/

		packet->Execute();
		delete packet;
	}
	g_packetBuffer.clear();
}

void GateServerSocket::sendMessage( Packet *packet )
{
	if (m_bConnect == false)
	{
		return;
	}

	//把成员变量写入缓存
	packet->Write();
	//编码发送
	char* ba = packet->encode();
	//g_gatess.sendBytes(ba, packet->m_nLen+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH);
    int sendResult;
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendResult = cocos_send(g_gatess, ba, packet->m_nLen+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH, 0);
//#else
//    sendResult = cocos_send_n(g_gatess, ba, packet->m_nLen+ENGINE_HEAD_LENGTH+PACKET_TYPE_LENGTH);
//#endif

	delete ba;
}

void GateServerSocket::registerScriptHandler( int refHandler )
{
	m_refHandler = refHandler;
}

void GateServerSocket::destroyInstance( void )
{
	if ( s_NetWorkModule && s_NetWorkModule->getParent() )
	{
		s_NetWorkModule->removeFromParentAndCleanup(true);
	}

	CC_SAFE_DELETE( s_NetWorkModule );
}
