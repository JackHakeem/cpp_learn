/****************************************************************************
 Copyright (c) 2011 4399
 Copyright (c) 2011 ำเฯในคื๗สา

 author	:zhangcheng
 email	:45612592@qq.com
 web	:http://45612592.qzone.qq.com
 data	:2011/11/19
 ****************************************************************************/

#ifndef __PACKETBUFFER_H__
#define __PACKETBUFFER_H__

#include <vector>
#include "Packet.h"

typedef std::vector<Packet*> packets;

class PacketBuffer
{

	enum Msg
	{
		SPT_SNAPSHOT = 0x1021

	};
private :
	Packet buf;
public:
	PacketBuffer();

	void push(const char * ba, uint32 nlen);

	packets getPackets();

	void clear();
};

#endif
