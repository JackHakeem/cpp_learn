#ifndef HLQS_BuffStateVo_H_
#define HLQS_BuffStateVo_H_

class BuffStateVo
{
public:
	const static int BATTLE_STATUS_NORMAL			= 0;		// normal
	const static int BATTLE_STATUS_DIZZY			= 1;		// dizzy
	const static int BATTLE_STATUS_DEAD				= 2;		// die
	const static int BATTLE_STATUS_TRAP				= 3;		// Cast trap
	const static int BATTLE_STATUS_COUNTER			= 4;		// Counterattack client to use
	const static int BATTLE_STATUS_DODGE			= 5;		// Dodge the client to use

public:
	BuffStateVo();
};

#endif