#ifndef _RecruitType_H_
#define _RecruitType_H_

class RecruitType
{
public:
	enum
	{
		ROOKIE = 1,			// never
		DISMISS = 2,		// ever
		ALL = 0,			// all can 

		STORY_MERC = 1,		// juqing
		FAME_MERC = 2,		// mingsheng 
		ALL_STROY_FAME = 0,	// all 
	};
};

#endif