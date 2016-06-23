#include "EggCommand.h"
#include "model/egg/EggProxy.h"
#include "socket/command/s40/SCMD401.h"
#include "socket/command/s40/SCMD40B.h"

EggCommand::EggCommand()
{}
	
EggCommand::~EggCommand()
{}


void EggCommand::execute( int32 command, char* data )
{
	_eggProxy = (EggProxy*)g_pFacade->retrieveProxy( AppFacade_EGG_CHANGE );
	
	switch( command )
	{
	case HISTORY_RESULT:
		_eggProxy->initReward((SCMD401*)data);
		break;
	case DEPOT_RESULT:
		_eggProxy->initDepot((SCMD40B*)data);
		break;
	}
}