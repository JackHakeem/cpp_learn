/****************************************************************************
 Copyright (c) 2011 4399
 Copyright (c) 2011 ำเฯในคื๗สา

 author	:zhangcheng
 email	:45612592@qq.com
 web	:http://45612592.qzone.qq.com
 data	:2011/11/19
 ****************************************************************************/

#ifndef _GATESERVERSOCKET_H_
#define _GATESERVERSOCKET_H_


#include "BaseType.h"
#include "PacketBuffer.h"
#include <string>
#include "manager/LayerManager.h"

class Packet;
class GameServerSocket: public cocos2d::CCNode//cocos2d::SelectorProtocol//cocos2d::CCLayer//
{
public:
	GameServerSocket(void);
	static GameServerSocket *s_NetWorkModule;
	bool m_bConnect;
	int  m_refHandler;

	void recv(float dt);

public:
	static GameServerSocket* getInstance(void);
	static void destroyInstance(void);
	void sendMessage(Packet *packet);
	bool connect(const std::string& host, unsigned short port);	
	void registerScriptHandler( int refHandler );

	void visit();

	virtual ~GameServerSocket(void);
	PacketBuffer g_packetBuffer;

	packets m_ps;
	bool m_bHasRun;
};

#endif//_LUA_NETWORK_H
