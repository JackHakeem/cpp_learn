#ifndef _UPGRADEPRETIP_H_
#define _UPGRADEPRETIP_H_
#include "BaseType.h"

class UpGradePreTip
{
public:
	UpGradePreTip();
	~UpGradePreTip();

public:
	int32 type;		
	int32 level;		
	std::string tip;	
};

#endif