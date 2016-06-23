#include "FormationClip.h"
#include "manager/ViewManager.h"

FormationClip::FormationClip( int sitNum , FormationInfo* info ): info(0), _isWatch(false)
{

	        this->info=info;
			//int forId=info->id;
			 
		
}

// LH0713LEAK
// FormationClip::~FormationClip()
// {
// 	CC_SAFE_DELETE(info);
// }

void FormationClip::setActive( bool b )
{
	  this->setIsVisible(b);
}
