#include "SCMD2B1.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2B1::Read()
{
	a_event1isFound = readByte();
	b_event1Item1 = readByte();
	c_event1Item2 = readByte();
	d_event1Name = readString();
	e_event2isFound = readByte();
	f_event2Item1 = readByte();
	g_event2Item2 = readByte();
	h_event2Item3 = readByte();
	i_event2Name = readString();
	j_event3isFound = readByte();
	k_event3Item1 = readByte();
	l_event3Item2 = readByte();
	m_event3Item3 = readByte();
	n_event3Item4 = readByte();
	o_event3Name = readString();
	return true;
}


int32 	SCMD2B1::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B1Handler::Execute(this) ;
}


uint32 SCMD2B1Handler::Execute(SCMD2B1* pPacket)
{
	if (!pPacket) return 1;

	//add code here

	return 0;
}