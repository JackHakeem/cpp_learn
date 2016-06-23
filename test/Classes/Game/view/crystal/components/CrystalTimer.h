#ifndef _CRYSTALTIMER_H_
#define _CRYSTALTIMER_H_

#include "cocos2d.h"
#include "model/crystal/vo/CrystalInfo.h"
#include "BaseType.h"
#include <map>

USING_NS_CC;

#define DELTATIME (1.0f)

class CrystalTimer : public LayerNode
{
public:
	CrystalTimer( CrystalInfo* info);
	~CrystalTimer();

	static CrystalTimer* CrystalTimerWithCrystalInfo( CrystalInfo* info);
	void update(CrystalInfo* info);
	void layout(ccTime dt = DELTATIME);
	void dispose();
	void reinit();
public:
	CrystalInfo* _info;
	CCLabelTTF* _tfText;
	CCLabelTTF* _pDesText;

	enum
	{
		TAG_DES = 101,
		TAG_TIMER = 102,
	};
};

#endif