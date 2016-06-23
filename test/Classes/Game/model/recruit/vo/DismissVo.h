#ifndef _DISSMISSVO_H_
#define _DISSMISSVO_H_

#include "BaseType.h"

class DismissVo
{
public:
	int id;		// ID
	int mercId;	// ID
	int level;		// 
	int strength;	// 
	int intellect;  // 
	int stamina;    // Tige 
	int exp;		// 
	int skill;		// Equipment Zhudong skill
	int reborn;     // reborn times
	int maxhp;		//    

public:
	DismissVo()
	{
		memset( this, 0, sizeof( DismissVo ) );
		exp = 0;
	}
};

#endif