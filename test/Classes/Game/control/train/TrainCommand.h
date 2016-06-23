#ifndef _TRAINCOMMAND_H_
#define _TRAINCOMMAND_H_

#include "mvc/SimpleCommand.h"
#include "model/train/TrainProxy.h"



class TrainCommand:public SimpleCommand
{
public:
	enum 
	{
		INIT_TRAIN_LIST, 
		START_TRAINNING,
		END_TRAINNING,
		CHANGE_MODE,
		RAPIC_LEAP,
	};

public:
	TrainCommand();
	~TrainCommand(){}
	virtual void execute(int32 command, char* data);
	void initTrainList( char* data );
	void startTraining( char* data );
	void endTraining( char* data );
	void rapicLeap( char* data );
private:
	TrainProxy* _trainProxy;
	TrainManager* _trainManager;
};

#endif