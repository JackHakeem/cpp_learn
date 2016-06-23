#include "SCMD16F.h"
#include "control/AppFacade.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"

bool	SCMD16F::Read()
{
	a_locationType = readByte();
	b_sitNum = readByte();
	c_roleId = readUint();
	d_strength = readByte();
	e_stamina = readShort();
	f_wrist = readShort();
	g_intellect = readShort();

	return true;
}

int32 	SCMD16F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD16FHandler::Execute(this) ;
}


uint32 SCMD16FHandler::Execute(SCMD16F* pPacket)
{
	if (!pPacket) return 1;
	
	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator( AppFacade_MainUIMediator );
	if ( mUImediator )
		mUImediator->updateGoodsDynamic( pPacket );

	return 0;
}