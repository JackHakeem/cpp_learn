#ifndef _SkillPic_H_
#define _SkillPic_H_

#include "cocos2d.h"
#include "model/skill/vo/SkillVo.h"
using namespace cocos2d;

class SkillPic : public CCSprite
{
public:
	SkillPic();
	bool initSkillPic( int skillId );
	void GreyandNewtip( string tips );
public:
	int _skillId;
	SkillVo* _skillVo;

};

#endif