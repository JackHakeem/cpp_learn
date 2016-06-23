#ifndef HLQS_UPSkillItem_H_
#define HLQS_UPSkillItem_H_
#include "model/skill/vo/UpGradeInfo.h"
#include "LayerNode.h"

USING_NS_CC;

class UPSkillItem: public LayerNode
{
public:
	virtual ~UPSkillItem(){ CC_SAFE_DELETE(_info);}
	UPSkillItem(int sitNum=1, int pageNum=1, UpGradeInfo *info=0, int pageSize =20);
	bool init();
public:
	enum
	{
		Z_ITEM = 0
	};
	enum
	{
		TAG_CELL=0,
		TAG_LIGHT,
		TAG_ITEMICON
	};
	int _sitNum;
	UpGradeInfo * _info;

};

#endif