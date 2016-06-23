#include "TrainCommand.h"
#include "socket/command/s35/SCMD352.h"
#include "model/train/vo/TrainVo.h"
#include "socket/command/s35/SCMD35A.h"
#include "socket/command/s35/SCMD358.h"
#include "manager/LangManager.h"
#include "manager/CDManage.h"
#include "view/train/TrainViewMediator.h"
#include "mvc/Facade.h"

TrainCommand::TrainCommand()
{
	_trainProxy = (TrainProxy*)g_pFacade->retrieveProxy( AppFacade_TRAIN_PROXY_CHANGE );
	_trainManager = TrainManager::Instance();
}

void TrainCommand::execute( int32 command, char* data )
{
	//_trainProxy = (TrainProxy*)g_pFacade->retrieveProxy( TRAIN_PROXY_CHANGE );
	switch(command)
	{
	case INIT_TRAIN_LIST:
		initTrainList( data );
		break;
	case START_TRAINNING:
		startTraining( data );
		break;
	case END_TRAINNING:
		endTraining( data );
		break;
	case CHANGE_MODE:
		//changeMode( data );
		break;
	case RAPIC_LEAP:
		rapicLeap( data );
		break;
	}
}

/** 
*Processing training package to return to the list
* @param obj SCMD352
*/ 
void TrainCommand::initTrainList( char* data )
{
	SCMD352* param = (SCMD352*)data;
	_trainProxy->_rapicGold = param->a_goldPrice;
	if ( param->b_players.size() > 0 )
	{
		std::list<TrainVo *> tranList;
		std::list<SCMD352::SCMD352Node>::iterator it = param->b_players.begin();
		while ( it != param->b_players.end() )
		{
			SCMD352::SCMD352Node node = *it;
			TrainVo* vo = new TrainVo();
			vo->mercId = node.a_playerId;
			vo->mode = node.b_mode;

			Number server_time = CDManage::Instance()->getServerTime();
			Number tTime = (Number)node.c_time;
			vo->train_time = tTime*1000;
			if( (Number)server_time <= vo->train_time )
				tranList.push_back( vo );
			it++;


		}

		_trainManager->initTrainList( tranList );
	}
}
		
/**
* Processing started training return to pack
* @param obj
*/ 
void TrainCommand::startTraining( char* data )
{
	SCMD35A* param = (SCMD35A*)data;
	Number severTime = CDManage::Instance()->getServerTime();
	if( time == 0 || severTime*0.001f >= (Number)param->b_time )
	{
		// request lose
		//string mercName = RoleManage.getInstance().getMercenary(param.a_playerId).playerBaseInfo.name;
		//_msgManage.showMsg(MsgManage.SYSTEM_MSG, "T0015", mercName);
		LangManager::msgShow( "T0015" );
	}
	else
	{
		int mode = 0;   // Began training mode for 0 normal mode
		Number tTime = (Number)param->b_time;
		Number msTime = tTime*1000;  	// Conversion for milliseconds

		////special count for correct time by Jae!!!
		//Number nb = msTime - severTime;
		//Number num = nb*0.001f;
		//Number timeArray[7] = { 8, 24, 24, 36, 48, 60, 72};
		//TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator(
		//	AppFacade_TRAIN_PROXY_CHANGE );
		//if ( pMediator && pMediator->_trainView  )
		//{
		//	Number hours = timeArray[pMediator->_trainView->m_selectTimeIndex];
		//	TrainManager::Instance()->m_iTimeOffset = hours*60*60-num;
		//}

		_trainManager->beginTrain( param->a_playerId, mode, msTime );
		_trainProxy->beginTraining( data, true );
	}
}
		
/** 
* Processing end to return to training package
* @param obj
*/
void TrainCommand::endTraining( char* data )
{
	//var param:SCMD358 = obj as SCMD358;
	SCMD358* param = (SCMD358*)data;
	if ( param->b_result == 1 )
	{
		_trainManager->abortTrain( param->a_playerId );
		_trainProxy->endTraining( data, false );
		
	}
	//if(param.b_result.value == 1){
	//	_trainManager.abortTrain(param.a_playerId);
	//	_trainProxy.endTraining([param.a_playerId], false);
	//}else{
	//	var mercName:String = RoleManage.getInstance().getMercenary(param.a_playerId).playerBaseInfo.name;
	//	_msgManage.showMsg(MsgManage.SYSTEM_MSG, "T0016", mercName);
	//}
}
		
/**
* Deal with sudden fly back to bag
* @param obj
*/
void TrainCommand::rapicLeap( char* data )
{
	_trainProxy->rapicLeap(data);
	//var param:SCMD35C = obj as SCMD35C;
	//_trainProxy.rapicLeap(param.a_playerId, param.b_rapidExp, param.c_goldPrice.value, param.d_critExp);
}

