#ifndef _STUNTS_LAYER_H_ 
#define _STUNTS_LAYER_H_

#ifndef _INCLUDE_COCOS2D_H_ 
#define _INCLUDE_COCOS2D_H_
#include "cocos2d.h"
#endif
#include "LayerNode.h"

USING_NS_CC;

class StuntsLayer : public LayerNode
{
public:
	StuntsLayer();
	~StuntsLayer(){}

	enum
	{
		TAG_BACKGROUND = 0,

		TAG_STUNTS = 101,

		TAG_Skill_HightLight = 201,
	};

public:
	virtual bool init();
	void LoadBackGround();
	void LoadItems();
	void setHighLight(CCPoint pos ,bool bVar);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

public:
	CCSize _layerSize;
};

#endif // _STUNTS_LAYER_H_