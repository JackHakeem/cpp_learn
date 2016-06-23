#ifndef _STEP_VO_H_
#define _STEP_VO_H_

#include "BaseType.h"

class StepVo
{
public:
	StepVo() {}
	~StepVo() 
	{
		
		trigger.clear();


		param.clear();
	}


	int id;
	std::vector<std::string> trigger;
	int btnId;
	int btnSit;
	std::vector<std::string> param;
	string info;

	void setTrigger(std::string triggerStr);
	void setParam(std::string paramStr);
};


#endif