#include "FormationInfo.h"


FormationInfo::FormationInfo()
{
	id = 0;
	lev = 0;
	active = false;
}

FormationInfo::~FormationInfo()
{
	figuresMap.clear();
	
}
