#include "SCMD37C.h"
#include "socket/network/GameServerSocket.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"

bool	SCMD37C::Read()
{
	a_consume = readInt();
	b_totalPage = readByte();
	c_curPage = readByte();
	int16 rooms = readShort();
	for(int16 i=0; i<rooms; ++i)
	{
		SCMD37CNode node;
		node.a_roomId = readInt();
		node.b_captainName = readString();
		node.c_careerId = readByte();
		node.d_lev = readByte();
		node.e_maxNum = readByte();
		node.f_curNum = readByte();
		d_rooms.push_back(node);
	}
	return true;
}

int32 	SCMD37C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD37CHandler::Execute(this) ;
}


uint32 SCMD37CHandler::Execute(SCMD37C* pPacket)
{
	if (!pPacket) return 1;

	// Doyang 20121024
	// Temp to do
	if(pPacket->a_consume > 0){
		int energy = RoleManage::Instance()->accountInfo()->energy();
		if(pPacket->a_consume > energy){
			LangManager::msgShow("TEM015");
		}
	}

	return 0;
}