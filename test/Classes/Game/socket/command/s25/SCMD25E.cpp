#include "SCMD25E.h"
#include "view/ranking/RankingMediator.h"

bool SCMD25E::Read()
{
    a_type = readByte();
    b_player = readInt();
	
    int cnt = readShort();

    for (int i = 0; i < cnt; ++i)
    {
        SCMD25ENode node;
        node.a_id = readShort();
        node.b_lev = readByte();
        node.c_stamina = readShort();
        node.d_wrist = readShort();
        node.e_intellect = readShort();

        c_equips.push_back(node);
    }
	return true;
}

int32 SCMD25E::Execute()
{
    if (! Read())
    {
        return 1;
    }

    return SCMD25EHandler::Execute(this);
}

uint32 SCMD25EHandler::Execute(SCMD25E* pPacket)
{
    if (! pPacket)
        return 1;
	RankingMediator* p = (RankingMediator*)g_pFacade->retrieveMediator(AppFacade_Ranking_Mediator);
	if (p)
		p->updateEuiqpments(pPacket);
    return 0;
}
