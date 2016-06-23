#include "SCMD421.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD421::Read()
{
	b_remainFreeCount = readByte();
	a_remainTaskCount = readByte();
	c_taskCount = readShort();
	for(uint16 i=0; i<c_taskCount; ++i)
	{
		SCMD421Node node;
		node.a_taskId = readByte();
		node.b_quality = readByte();
		node.c_count = readByte();
		node.d_finishCount = readByte();
		node.e_taskType = readByte();
		node.f_monsterGroup = readInt();
		node.g_hasAccepted = readByte();

		uint16 awardSize = readShort();
		for(uint16 j=0; j<awardSize; ++j)
		{
			SCMD421Node2 node2;
			node2.a_goodsId = readInt();
			node2.b_goodsNum = readInt();
			node.h_awardList.push_back(node2);
		}
		d_nodeList.push_back(node);
	}
	return true;
}

int32 SCMD421::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD421Handler::Execute(this);
}

uint32 SCMD421Handler::Execute( SCMD421* pPacket )
{
	DailyTaskExProxy* pProxy = (DailyTaskExProxy *) g_pFacade->retrieveProxy(AppFacade_DAILY_TASK_EX_PROXY);
	pProxy->onDailyTaskExChanged(pPacket);
	return 0;
}
