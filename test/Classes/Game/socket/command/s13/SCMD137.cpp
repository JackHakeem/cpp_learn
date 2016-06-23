#include "SCMD137.h"
#include "socket/network/GameServerSocket.h"
#include "view/report/ReportMediator.h"
#include "manager/GlobalManage.h"

bool SCMD137::Read()
{
    a_groupId = readInt();
    int16 b_SCMD137NodeNum = readShort();
    for (int i = 0; i < b_SCMD137NodeNum; ++i)
    {
        SCMD137Node newnode;

		newnode.a_battleId1 = readUint();
        newnode.b_battleId2 = readUint();
        newnode.c_acountId = readInt();
        newnode.d_lev = readByte();
        newnode.e_playerName = readString();

		b_SCMD137Node.push_back(newnode);
    }

    return true;
}

int32 SCMD137::Execute()
{
    if (! Read())
    {
        return 1;
    }

    return SCMD137Handler::Execute(this);
}

uint32 SCMD137Handler::Execute(SCMD137* pPacket)
{
    if (! pPacket) return 1;

 //   ReportMediator* rm = (ReportMediator*)g_pFacade->retrieveMediator(AppFacade_Report_CHANGE);

 //   if (rm)
	//{
 //       rm->sockReportList(pPacket);
	//}

	g_pReportMediator->sockReportList(pPacket);
	return 0;
}

