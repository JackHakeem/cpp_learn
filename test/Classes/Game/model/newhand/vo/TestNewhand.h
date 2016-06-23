#ifndef _TEST_NEWHAND_H_
#define _TEST_NEWHAND_H_
#include "ScriptVo.h"

class TestNewhand
{
public:
	TestNewhand(string type, ScriptVo *pScript, int id)
	{
		this->pScript = pScript;
		this->type = type;
		this->id = id;
		/*this->evtId = evtId;
		this->lev = lev;*/
	}
	~TestNewhand() 
	{
	}

	struct CrystalParam
	{
		int type;
		int lev;
	};

public:
	string type;
	ScriptVo *pScript;
	int id;
};
#endif