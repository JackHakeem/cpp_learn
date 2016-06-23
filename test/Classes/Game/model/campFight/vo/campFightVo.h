#ifndef _CAMPFIGHTVO_H_
#define _CAMPFIGHTVO_H_
#include "string.h"
#include "vector"

enum CampType
{
	ICE_CAMP = 0,
	FIRE_CAMP =1,
	NONE,
};

struct TCFPlayerInfo
{
	uint32 accountId;
	std::string name;
	uint16 contiWinTms;
	TCFPlayerInfo(uint32 a_, std::string n_, uint16 c_)
		:accountId(a_),name(n_),contiWinTms(c_){}
	~TCFPlayerInfo(){}
};

typedef std::vector< TCFPlayerInfo* > vecCFPlayerInfo;

struct TCampInfo
{
	vecCFPlayerInfo members;
	uint32 scores;
};
struct TMyCampFightInfo
{
	uint16 score;
	uint16 hisConstiWinTims;
	uint16 sumPop;
	uint32 sumSilver;
	uint8  state;
	uint32 times; //剩余时间 30s校对一次
};
#endif