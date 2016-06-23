#ifndef HLQS_SkillTipsTool_H_
#define HLQS_SkillTipsTool_H_

#include "BaseType.h"
#include "vo/UpGradeInfo.h"

class SkillTipsTool
{
public:
	SkillTipsTool();
	~SkillTipsTool();
public:
	static SUBSKILLTIPS* getSkillTips(UpGradeInfo* info, int style, std::string* userName);
};

#endif