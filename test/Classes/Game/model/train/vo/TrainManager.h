#ifndef _TRAINMANAGER_H_
#define _TRAINMANAGER_H_

#include "model/player/RoleManage.h"
#include "utils/Singleton.h"
#include "TrainVo.h"
#include "BaseType.h"
#include "model/skill/vo/SpeedupVo.h"

class TrainManager : public Singleton<TrainManager>
{
public:
	TrainManager();
	~TrainManager();

	TrainVo* getVoByMercId( int mercId );
	std::map<int, TrainVo*>* getTrainDic();	
public:
	static const int TRAIN_MAX = 8;
	static const int BUY_SIT_VIP[ 8 ];
	static const int BUY_SIT_GOLD[ 8 ];

private:
	RoleManage* _roleMange;
	std::map< int, SpeedupVo* > _speedupDic;
public:

	CC_PROPERTY( int, _trainLim, TrainLim )				// Cap on the number of training
		
	CC_PROPERTY( int, _trainNum, TrainNum )				// The current number of training

public:
	std::map<int, TrainVo*> _trainDic;  // The only ID for key mercenaries are training Object
	void initTrainList( std::list<TrainVo *> Array );

	void setSpeedupDic( std::map< int, SpeedupVo* >& speedDic );

	void beginTrain( int id, int mode, Number time );	// Save training
	void abortTrain( int mercId );
	Number getSpeedupByCrystal( int clevel );

	Number m_iTimeOffset;
};

#endif 