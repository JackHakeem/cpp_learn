#ifndef _TrainRole_ITEM_H_
#define _TrainRole_ITEM_H_

#include "cocos2d.h"

USING_NS_CC;

class TrainRoleItem : public CCLayer
{
public:
	TrainRoleItem(int id, int acctId);
	~TrainRoleItem();

public:

	void showIsTrained(int accountID);
	void setIsTrained(bool var);
	void updateLevelLabel(int level);
	

public:

	enum
	{
		Tag_IsTrainedBg = 100,
		Tag_IsTrainedGou,
		Tag_LevelLabel = 110,
	};

	CC_SYNTHESIZE(int , _merhId , MerhId);
	CC_SYNTHESIZE(int , _acountId , AcountId);

};
#endif