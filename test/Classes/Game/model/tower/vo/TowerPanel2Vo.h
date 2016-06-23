#ifndef _TowerPanel2Vo_H_
#define _TowerPanel2Vo_H_

#include "BaseType.h"

class TowerPanel2Vo
{
public:
	TowerPanel2Vo()
	{
		freeTimes = 0;
		curFloor = 0;
		maxFloor = 0;

		nextMonster = "";
		inspire = 0;
		inspirePrac = 0;
		curIcons = "";
		nextIcons = "";
		showCurBoss = false;

	}
	~TowerPanel2Vo() {}

public:
	int freeTimes;
	int curFloor;
	int maxFloor;
	string nextMonster;
	int inspire;			//�����ļӳ�ֵ
	int inspirePrac; 	//�´�����������������ֵ
	string curIcons;
	string nextIcons;
	bool showCurBoss;
};
#endif