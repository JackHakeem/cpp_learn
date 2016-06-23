#include "TrainManager.h"
#include "CCPlatformMacros.h"
#include "view/train/TrainViewMediator.h"

//const int TrainManager::BUY_SIT_VIP[ TrainManager::TRAIN_MAX ]  = { 0, 0, 0, 3, 5, 7, 9, 10 };
const int TrainManager::BUY_SIT_VIP[ TrainManager::TRAIN_MAX ]  = { 0, 0, 0, 2, 6, 8, 10, 10 };
const int TrainManager::BUY_SIT_GOLD[ TrainManager::TRAIN_MAX ] = { 0, 0, 100, 200, 300, 400, 500, 600 };

TrainManager::TrainManager()
{
	_roleMange = RoleManage::Instance();
	_trainLim = 3;	    // Cap on the number of training
	_trainNum = 0;      // The current number of training

	m_iTimeOffset = 0;
}

TrainManager::~TrainManager()
{
	std::map< int, SpeedupVo* >::iterator it;
	for ( it = _speedupDic.begin(); it != _speedupDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
}

/**
* Initial training list
* @ param array training list
*/
void TrainManager::initTrainList( std::list<TrainVo *> Array )
{
	std::list<TrainVo *>::iterator it = Array.begin();
	int count = 0;
	while( it != Array.end() )
	{
		TrainVo* pTemp = *it;

		_trainDic.insert( make_pair( pTemp->mercId, pTemp ) );

		++it;
		++count;
	}

	if ( count > 0 )
	{
		setTrainNum( count );
	}
}

/**
* Save training
* @ param id mercenaries only id
* @ param mode training mode
* @ param time over time
*/
void TrainManager::beginTrain( int id, int mode, Number time )
{
	std::map<int, TrainVo*>::iterator it = _trainDic.find( id );
	if ( it != _trainDic.end() )
	{
		return;
	}
	TrainVo* trainVo = new TrainVo();
	trainVo->mercId = id;
	trainVo->mode = mode;
	trainVo->train_time = time;
	_trainDic.insert( make_pair( id, trainVo ) );
	setTrainNum(_trainNum+1);
}
		
/**
* Exit training
*/
void TrainManager::abortTrain( int mercId )
{
	std::map<int, TrainVo*>::iterator it = _trainDic.find( mercId );
	if( it != _trainDic.end() )
	{
		TrainVo* trainVo = it->second;
		CC_SAFE_DELETE( trainVo );
		_trainDic.erase( it );
		setTrainNum(_trainNum-1);
	}
}

/**
* According to MercId get TrainVo
* @ param mercId
*/
TrainVo* TrainManager::getVoByMercId( int mercId )
{
	std::map<int, TrainVo*>::iterator it = _trainDic.find( mercId );
	if ( it != _trainDic.end() )
	{
		return it->second; 
	}
	return NULL;
}

std::map<int, TrainVo*>* TrainManager::getTrainDic()
{
	return &_trainDic;
}

int TrainManager::getTrainLim()
{
	return _trainLim;
}

void TrainManager::setTrainLim( int lim )
{
	_trainLim = lim;
}

int TrainManager::getTrainNum()
{
	return _trainNum;
}

void TrainManager::setTrainNum( int num ) 
{
	if ( num != _trainNum )
	{
		_trainNum = num;

		// Temporary in this simulation protected reliably against detective events
		TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
		if ( pMediator && pMediator->_trainView  )
		{
			pMediator->_trainView->updateTrainNumTips( _trainNum, _trainLim );
		}
	}
}

Number TrainManager::getSpeedupByCrystal( int clevel )
{
	std::map< int, SpeedupVo* >::iterator it = _speedupDic.find( clevel );
	if( it != _speedupDic.end() )
	{
		return it->second->speedup;
	}

	return 0;
}

void TrainManager::setSpeedupDic( std::map< int, SpeedupVo* >& speedDic )
{
	_speedupDic = speedDic;
}
