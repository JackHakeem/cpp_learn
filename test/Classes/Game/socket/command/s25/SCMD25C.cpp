#include "SCMD25C.h"
#include "view/ranking/RankingMediator.h"


bool SCMD25C::Read()
{
    a_type = readByte();
    b_myRank = readShort();
    c_num = readShort();
    d_begin = readShort();

	int cnt = readShort();
    for (int i = 0; i < cnt; ++i)
    {
        SCMD25CNode node;
        node.a_rank = readShort();
        node.b_playerId = readInt();
        node.c_name = readString();
        node.d_guild = readString();
        node.e_grade = readInt();
        node.f_lev = readByte();
        node.g_roleId = readInt();
        node.h_trend = readShort();

        e_ranks.push_back(node);
    }
	return true;
}

int32 SCMD25C::Execute()
{
    if (! Read())
    {
        return 1;
    }

    return SCMD25CHandler::Execute(this);
}

uint32 SCMD25CHandler::Execute(SCMD25C* pPacket)
{
    if (! pPacket)
        return 1;
	RankingMediator* p = (RankingMediator*)g_pFacade->retrieveMediator(AppFacade_Ranking_Mediator);
	if (p)
		p->updateRankingList(pPacket);
    return 0;
}
