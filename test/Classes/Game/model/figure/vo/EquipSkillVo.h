#ifndef HLQS_EquipSkillVo_H_
#define HLQS_EquipSkillVo_H_

#include "model/skill/vo/UpGradeInfo.h"

class EquipSkillVo
{
public:
	std::map<int, UpGradeInfo> m_upGrades;

public:
	EquipSkillVo();
	int setIndex(int index, UpGradeInfo goodsInfo);
	UpGradeInfo* getIndex(int index);
	std::map<int, UpGradeInfo>* getAll();
};

#endif