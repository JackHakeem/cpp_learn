#ifndef HLQS_SkillCells_H_
#define HLQS_SkillCells_H_
#include "LayerNode.h"
#include "model/skill/vo/UpGradeInfo.h"

USING_NS_CC;
class SkillCells: public LayerNode
{
public:
	SkillCells();
	bool init();
	SkillCells(UpGradeInfo* info, int sitNum, int page = 0, std::string userName = "");
	void setActive(bool set, std::string userName = "");
public:
	UpGradeInfo* _myInfo;
	int _mySitNum;
	enum
	{
		RENDERZ_lable = 0,
	};
};
#endif