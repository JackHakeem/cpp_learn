#include "model/figure/vo/EquipSkillVo.h"

EquipSkillVo::EquipSkillVo()
{
}

int EquipSkillVo::setIndex(int index, UpGradeInfo upGrade)
{
	if(m_upGrades.find(index) != m_upGrades.end())
		return -1;
	m_upGrades.insert(make_pair(index, upGrade));
	return 0;
}

UpGradeInfo* EquipSkillVo::getIndex(int index)
{
	std::map<int, UpGradeInfo>::iterator iter = m_upGrades.find(index);
	if(iter == m_upGrades.end())
		return NULL;
	return &(iter->second);
}

std::map<int, UpGradeInfo>* EquipSkillVo::getAll()
{
	return &m_upGrades;
}