#ifndef _OBJECT_GLOW_H_
#define _OBJECT_GLOW_H_
#include "cocos2d.h"
#include "LeadArrow.h"

USING_NS_CC;

class ObjectGlow
{
public:

	enum ObjectParentType
	{
		TYPE_1 = 0,
		TYPE_2,
		TYPE_3,
		TYPE_4,
	};

	enum ArrowPositionType
	{
		POS_ARROW_REC_TASK,
		POS_ARROW_CAN_TASK,
	};
	ObjectGlow(CCNode *pObject, int loc_type, CCNode *pObjectParent,
		int arrow_dir, string info, bool isFlyEff, CCPoint arrowPos);

	~ObjectGlow() {}

	void initFilter(int type = 0);
	void paintToRoot(CCNode *pParentNode);
	void drawLeadArrow(int loc_type, CCNode *pObjectParent, int arrow_dir, string info);
	int *getCoordinate(int loc_type, CCNode *pObjectParent, int arrow_dir);
	void stopAndClear();
	CCNode *_pObject;
	int _loc_type;
	//CCNode *_pObjectParent;
	int _arraw_dir;
	string _info;
	bool _isFlyEff;
	//ObjectParentType _type;
	CCPoint _arrowPos;

	CCNode *_pRect;
	LeadArrow *_pLead;
};
#endif