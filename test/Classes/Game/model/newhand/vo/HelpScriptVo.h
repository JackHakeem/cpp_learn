#ifndef _HELP_SCRIPT_VO_H_
#define _HELP_SCRIPT_VO_H_

#include "BaseType.h"

class HelpScriptVo
{
public:
	HelpScriptVo() : id(0) , type("") , processid(0) , bodyid(0) , title("") , content("") , btntxt("") , isBtnShow(0) , newhandid(0) , isIgnore(1) , AutoPop(0)
	{
		action.clear();
	}
	~HelpScriptVo() {}

public:
	int id;
	std::string type;
	int processid;
	int bodyid;
	std::string title;
	std::string content;
	std::string btntxt;
	int isBtnShow;
	int newhandid;
	std::vector<int> action;
	int isIgnore;
	int AutoPop;
};
#endif