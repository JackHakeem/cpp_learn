#include "SkillTipsTool.h"

SkillTipsTool::SkillTipsTool()
{
}

SUBSKILLTIPS* SkillTipsTool::getSkillTips(UpGradeInfo* info, int style, std::string* userName)
{
	if (info->subTips)
		SAFE_DELETE(info->subTips);

	info->subTips = 0;

	SUBSKILLTIPS* newrnt = new SUBSKILLTIPS();
	if (!newrnt)
		return 0;

	newrnt->name = info->name;
	newrnt->color_name = ccc3(255,255,255);
	newrnt->rank = info->rank;
	newrnt->lev = info->lev;
	newrnt->needLevel = info->needLevel;
	newrnt->icon = info->icon;
	newrnt->desc = info->desc;
	newrnt->style = style;


	return newrnt;
}
