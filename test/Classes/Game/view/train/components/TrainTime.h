#ifndef __TRAINTIME_H_
#define __TRAINTIME_H_

#include "cocos2d.h"
#include "model/train/vo/TrainVo.h"
using namespace cocos2d;

class TrainTime : public CCNode
{
public:
	TrainTime( TrainVo* trainVo );
	~TrainTime();
	
	static TrainTime* TrainTimeWithTrainVo( TrainVo* trainVo );
	void update( TrainVo* trainVo );
	void layout( ccTime dt = 1.0f );
	void dispose();
	void reinit();
	string formatData( Number timer1, Number serTimer );
public:
	TrainVo* _trainVo;
	CCLabelTTF* _tf;
};

#endif