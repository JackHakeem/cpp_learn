#pragma once

#include "LayerNode.h"

class SCMD13D;
class SCMD419;

class DungeonGUAMsgItem:public LayerNode
{
public:
	DungeonGUAMsgItem();
	~DungeonGUAMsgItem();

	static DungeonGUAMsgItem* itemFactory(SCMD13D* pPacket, int type, int guanIndex=-1);
	static DungeonGUAMsgItem* itemFactory(SCMD419* pPacket, int type, int guanIndex=-1);
	static DungeonGUAMsgItem* itemRoundFactory(int round);
	static DungeonGUAMsgItem* itemStrFactory(char* content, ccColor3B color , float width = 400, float size = 20.0f);
	static DungeonGUAMsgItem* lineFactory();
	bool init(SCMD13D* packet, int type);
	bool init(SCMD419* packet, int type);
	bool init();
	bool init(char* content, ccColor3B color , float width = 400, float size = 20.0f);
	bool initline();

public:
	int m_iGuanIndex;
	int m_iRound;
};