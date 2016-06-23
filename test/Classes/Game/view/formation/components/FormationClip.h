#ifndef _FORMATIONCLIP_H_
#define _FORMATIONCLIP_H_
#include "model/formation/vo/FormationInfo.h"

 /*
 On the right side of the formation list
 Here and flash code is different because we need change, the right only show the name of the formation
 */

class FormationClip : public SpriteNode
{
public:
 
	FormationInfo* info;
	bool _isWatch;

	void setActive(bool b);

public :
	FormationClip(int sitNum , /* LevSkillVo vo, */FormationInfo* info);
	//~FormationClip();

};

#endif