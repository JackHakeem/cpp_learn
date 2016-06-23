#ifndef _TRAINVO_H_
#define _TRAINVO_H_
#include "utils/Timer.h"

class TrainVo
{
public:
	TrainVo()
	{
	};
	~TrainVo(){};

public:
	int mercId; 	/**role ID*/
	Number train_time; 	/**Training over time*/
	int mode; 	 	/**The current training mode*/
};

#endif