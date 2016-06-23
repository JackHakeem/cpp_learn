#ifndef _TRAINPROXY_H_
#define _TRAINPROXY_H_

#include "vo/TrainManager.h"
#include "mvc/Proxy.h"
/*id:0, silver:0, gold:0, desc:8 hours*/
struct TimeInitStruct		  
{
	int id;
	int silver;
	int gold;
	std::string desc;
	TimeInitStruct()
	{
		id = 0;
		silver = 0;
		gold = 0;
		desc = "";
	}
};
						
struct ModeInitStruct		 //id:0, silver:0, gold:0,  desc:"Normal mode"
{
	int id;
	int silver;
	int gold;
	std::string descMode;
	std::string descPercent;
	std::string descGold;
	ModeInitStruct()
	{
		id = 0;
		silver = 0;
		gold = 0;
		descMode = "";
		descPercent = "";
		descGold = "";
	}
};

class TrainProxy: public Proxy
{
public:
	TrainProxy();
	~TrainProxy();
public:
	int getEndGold();
	void setRapicGold( int value );
	int getRapicGold();
	vector<TimeInitStruct> getTimeList();
	TimeInitStruct getTimeObj( int id );
	void beginTraining( char* mercs, bool flag );
	ModeInitStruct* getModeTextList();// Get training mode array
	vector<ModeInitStruct> getModeList();	//According to the VIP level for training mode array
	ModeInitStruct* getModeObj( int mode );
	void endTraining( char* data, bool flag );
	void rapicLeap( char* data/*mercId:int, rapicExp:int, rapicGold:int=0, critExp:int=0*/ );
	Number getPracticeDemand( int clevel );
	Number getExpAdded( int hLevel, int yLevel, int yanLevel );

public:
	TimeInitStruct _timeList[ 7 ];
	ModeInitStruct _modeList[ 5 ];
public:
	int _rapicGold;				// Gold axon number gold buckle fly
	int _endGold;				// Training for gold buckle end suspended buckle of gold

	TrainManager* _trainManager;
};

#endif