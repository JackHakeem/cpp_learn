#include "StepVo.h"


void StepVo::setTrigger( std::string triggerStr )
{
	if(triggerStr.empty()) return;
	trigger.clear();

	int pos1, pos2;
	pos1 = 0;
	pos2 = triggerStr.find('|');
	std::string usefulString;
	while(std::string::npos != pos2)
	{
		usefulString = triggerStr.substr(pos1, pos2 - pos1);
		trigger.push_back(usefulString);
		pos1 = pos2 + 1;
		pos2 = triggerStr.find('|',  pos1);
	}
	usefulString = triggerStr.substr(pos1);
	trigger.push_back(triggerStr.substr(pos1));
	//usefulString.~string();
}


void StepVo::setParam( std::string paramStr )
{
	if(paramStr.empty()) return;
	param.clear();

	int pos1, pos2;
	pos1 = 0;
	pos2 = paramStr.find('|');
	std::string usefulString;
	while(std::string::npos != pos2)
	{
		usefulString = paramStr.substr(pos1, pos2 - pos1);
		param.push_back(usefulString);
		pos1 = pos2 + 1;
		pos2 = paramStr.find('|',  pos1);
	}
	usefulString = paramStr.substr(pos1);
	param.push_back(usefulString);
	//usefulString.~string();
}
