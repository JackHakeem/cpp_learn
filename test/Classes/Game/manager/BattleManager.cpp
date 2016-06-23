//
//  BattleManager.cpp
//  HLQS_IPAD
//
//  Created by hui long on 12-3-1.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "BattleManager.h"
#include "socket/command/c11/CCMD11E.h"
#include "socket/command/c13/CCMD138.h"
#include "socket/network/GameServerSocket.h"

BattleManager* g_pBattleManager = 0;

BattleManager::BattleManager()
{}

BattleManager::~BattleManager()
{}

void BattleManager::sendBattleRequestHandler()
{
	CCMD11E* s = new CCMD11E();
	if (s)
	{
	
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
        {
            CCLog("BattleManager::sendBattleRequestHandler()::Send 0x11E Lvguai fatghting start");
			pSocket->sendMessage(s);
        }
	}
	SAFE_DELETE(s);
}

void BattleManager::sendBattleStopHandler(int type)
{
	CCMD138* s = new CCMD138(type);
	if (s)
	{
	
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
        {
            CCLog("Send 0x138 fighting result notice");
			pSocket->sendMessage(s);
        }
	}
	SAFE_DELETE(s);
}