#include "SCMD109.h"
#include "manager/CDManage.h"

bool SCMD109::Read()
{
	a_time = readUint();

	return true;
}


int32 	SCMD109::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD109Handler::Execute(this) ;
}


uint32 SCMD109Handler::Execute(SCMD109* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	CDManage::Instance()->serverTimer( pPacket->a_time );

	return 0;
}