#include "PacketBuffer.h"
#include "socket/message/MessageFactoryManager.h"


PacketBuffer::PacketBuffer()
{

}

void PacketBuffer::push( const char * ba, uint32 nlen )
{
	buf.writeBytes(ba, nlen);
	buf.m_nCursor=0;
}

packets PacketBuffer::getPackets()
{
	packets ps;

	while( buf.m_nLen - buf.m_nCursor >= ENGINE_HEAD_LENGTH )
	{	
		uint16 len = buf.readShort();				
		len = len - ENGINE_HEAD_LENGTH;

		if( buf.m_nLen < len )
		{
			buf.m_nCursor = buf.m_nCursor - 4;
			return ps;
		}

		uint16 packetType = buf.readUshort();
		len = len - PACKET_TYPE_LENGTH;
	

		cocos2d::CCLog("packetid:%x len:%d", packetType, len);
		
		
		//PT_SNAPSHOT
		//Packet *packet=NULL;

		if( packetType == SPT_SNAPSHOT )
		{
		/*	uint16 cb = buf.readUshort();
			len = len - 2;
			if( cb > 0 )
			{ 
				uint32 lastSTPacket = 0;
				for( int32 i = 0; i < cb; i++ )
				{
					uint16 subLen = buf.readUshort();
					subLen = subLen - 2;
					uint16 subType = 0;
					if( subLen <= buf.m_nLen )
					{
						subType = buf.readUshort();
						subLen = subLen - PACKET_TYPE_LENGTH;

						packet = new Packet(subType);
						if( subLen > 0 )
						{
							buf.readBytes(packet, 0, subLen);	
						}

						ps.push_back( packet );
						lastSTPacket = subType;
					}
					else
					{
						return ps;
					}
				}
			}
			else
			{
			}*/
		}
		else
		{
		//	CCLog("packetType %d", packetType);
			Packet* packet = g_pMessageFactoryManager->CreateMessage(packetType);
			if (packet)
			{
				if( len > 0 )
				{
					buf.readBytes( packet, 0, len );
				}
                packet->m_nLen = len;
				ps.push_back( packet );
			}
			else
			{
				//防止还没建立协议但是服务器把协议传过来了吧之后的略过了
				Packet* packet = new Packet();
				if( len > 0 )
				{
					buf.readBytes( packet, 0, len );
				}
                packet->m_nLen = len;
				ps.push_back( packet );
				//KK
				cocos2d::CCLog("packetid:%x len:%d  :handle protocol function find not found!!", packetType, len);

			}
		}
	}
	return ps;
}

void PacketBuffer::clear()
{
	buf.m_nCursor = 0;
	buf.m_nLen = 0;
}
