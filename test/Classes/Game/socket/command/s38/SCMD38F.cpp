#include "SCMD38F.h"
#include "view/act/ActMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD38F::Read()
{
	short SCMD38FNodeNum = readShort();
	for (int i = 0; i < SCMD38FNodeNum; i++)
	{
		SCMD38FNode node;
		node.a_id = readUint();
		node.b_type = readByte();
		node.c_title = readString();
		node.d_content = readString();
		node.e_startTime = readUint();
		node.f_endTime = readUint();
		node.g_isShowTime = readUbyte();

		_arr.push_back(node);
	}
	return true;
}

int32 	SCMD38F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD38FHandler::Execute(this) ;
}


uint32 SCMD38FHandler::Execute(SCMD38F* pPacket)
{
	if (!pPacket) return 1;

	ActMediator* _actMediator = (ActMediator*)g_pFacade->retrieveMediator(AppFacade_Act_CHANGE);
	if (_actMediator)
		_actMediator->sockActInfo(pPacket);


	
	return 0;
}
