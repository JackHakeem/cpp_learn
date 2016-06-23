#ifndef _ITEM_H_
#define _ITEM_H_
#include "model/scene/vo/ItemVo.h"
#include "utils/BitmapMovieClip.h"
#include "events/GameDispatcher.h"
#include "Element.h"
#include "cocos2d.h"

USING_NS_CC;

class Item : public Element
{
public:
	Item(ItemVo &itemVo);
	
	void showRes();
	virtual void layout(ccTime dt = 1.0f);
	virtual void updateAction(bool repeat = true);
	virtual void setGlow(bool bValue);
	virtual bool isHit();
	virtual bool hitTest(CCPoint point);
	virtual void dispose();
public:
	std::string _assetURL;
	ItemVo _itemVo;
	BitmapMovieClip * itemMovieClip;
	//TextField * _nameTxt;
	CCLabelTTF * _nameTxt;
	GameDispatcher * dispatcher;
};

#endif