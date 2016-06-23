#include "TrainTime.h"
#include "utils/ValuesUtil.h"
#include "manager/TimerManage.h"
#include "model/train/vo/TrainManager.h"
#include "utils/ScaleUtil.h"
#include "manager/CDManage.h"
#include "../TrainViewMediator.h"

TrainTime::TrainTime( TrainVo* trainVo )
{
	_trainVo = trainVo;

	TimerManage::Instance()->add( 1.0f, schedule_selector(TrainTime::layout), this );

	// train time
	_tf = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(200), POSX(35) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(31) );
	_tf->setAnchorPoint( CCPointZero );
	_tf->setColor( ccc3(40, 201, 254) );
	addChild( _tf );

	//CCLayerColor* p = CCLayerColor::layerWithColorWidthHeight( ccc4(0,0,255,100), POSX(200), POSX(35) );
	//addChild(p);
}

TrainTime* TrainTime::TrainTimeWithTrainVo( TrainVo* trainVo )
{
	if ( !trainVo )
	{
		return 0;
	}
	
	TrainTime* pTrainTime = new TrainTime( trainVo );
	return pTrainTime;
}

TrainTime::~TrainTime()
{

}

void TrainTime::update( TrainVo* trainVo )
{
	_trainVo = trainVo;
	TimerManage::Instance()->remove( schedule_selector(TrainTime::layout), this );
	TimerManage::Instance()->add( 1.0f, schedule_selector(TrainTime::layout), this );
	layout();
}

void TrainTime::reinit()
{
	TimerManage::Instance()->remove( schedule_selector(TrainTime::layout), this );
	TimerManage::Instance()->add( 1.0f, schedule_selector(TrainTime::layout), this );
}

void TrainTime::layout( ccTime dt )
{
	if( !_trainVo ) return ;

	Number msTime = CDManage::Instance()->getServerTime();
	if( _trainVo->train_time <= msTime/**0.001f*/ )
	{
		// train time end 
		_tf->setString("");
		dispose();
		//this.dispatchEvent(new ParamEvent(TIME_END, _trainVo));
		TrainViewMediator* pMediator = (TrainViewMediator*)g_pFacade->retrieveMediator(AppFacade_TRAIN_PROXY_CHANGE);
		pMediator->trainTimeEndHandler( _trainVo->mercId );
	}
	else
	{
		Number bTime = _trainVo->train_time*0.001;
		string str = formatData( bTime, msTime*0.001 );
		_tf->setString( str.c_str() );
	}
}

void TrainTime::dispose()
{
	TimerManage::Instance()->remove( schedule_selector(TrainTime::layout), this );
}

string TrainTime::formatData( Number timer1, Number serTimer )
{
	if ( timer1 < serTimer )
	{
		return "00:00:00";
	}
	Number num = timer1 - serTimer;

	//num += TrainManager::Instance()->m_iTimeOffset;

	Number hour = num/3600;
	int minute = ( num/60 )%60;
	int second = num%60;
	
	char timeStr[28];
	sprintf( timeStr, "%d", hour );
	string sHour = TimerManage::formatTime( timeStr );

	sprintf( timeStr, "%d", minute );
	string sMinute = TimerManage::formatTime( timeStr );

	sprintf( timeStr, "%d", second );
	string sSecond = TimerManage::formatTime( timeStr );

	return sHour.append( ":" ).append( sMinute ).append( ":" ).append( sSecond );
}