#ifndef _NPCVO_H 
#define _NPCVO_H 

#include "BaseType.h"
#include "LiveThingVo.h"
#include "model/formation/vo/FormationInfo.h"

class NPCVo : public LiveThingVo
{
public:
	NPCVo()
	{
		action = 0;
		typeId = 0;
		_resId = 0;
		realm = 0;
		icon = 0;
		otherInfos = 0;
		forInfo="";
		groupLev=0;
		GroupExp = 0;
		DropGoods = 0;
		_range = 1;
	    speed = 200;
		_isMonster = false;
		arraySeat = 0;
	}
	~NPCVo(){}

	int action;
	int typeId;

	int _resId;

public:
	int getResId(){	return _resId; }
	void setResId( int value ) { _resId = value; }

	uint realm;

	int speed; // 200

	uint icon;	//Display icon (0: no 1: have may meet task 2: have unfinished task 3: may submit task 4: a task dialogue 5: ore 6: fishing 7: by browsing...)
	int otherInfos;
	int groupLev;
	std::string forInfo;  //Formation information
	int _range;
	int arraySeat;//kevine
//private:
//	int _range;// = 1;
//public:
//	int getRange(){	return _range; }
//	void setRange( int value ){ _range = value; }
public:
	int GroupExp;         //experience
	int DropGoods;     //Item drop
	bool _isMonster;
};

#endif
