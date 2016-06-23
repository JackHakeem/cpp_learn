#include "TouchCityNode.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"

TouchCityNode::TouchCityNode()
{
	_nodeId = 0;
	_isFocused = false;
}

TouchCityNode::TouchCityNode(int id)
{
	_nodeId = id;
	_isFocused = false;
}

void TouchCityNode::setSpriteIcon(bool open, bool isFocused)
{
	_isFocused = open;
	CCSprite* sp = CCSprite::spriteWithSpriteFrameName("entrance/h_copylist.png");
	if(sp)
	{
		sp->setIsVisible(_isFocused);
		addChild(sp, 0, NODE_FOCUSED);
		sp->setAnchorPoint(CCPointZero);
		CCSize size = sp->getContentSize();
		sp->setPosition(ccp(POSX(113) - size.width / 2, POSX(56) - size.height / 2));
	}

	if(open)
	{
		CCUIBackground* kuang = new CCUIBackground();
		kuang->initWithSpriteFrame("ui2.png", ccp(0, 0), ccp(0, 0), CCSizeMake(POSX(KUANG_W), POSX(KUANG_H)));
		addChild(kuang);
		//Doyang 20120712
		kuang->release();
		kuang->setPosition(ccp(POSX(113 - KUANG_W / 2), POSX(56 - KUANG_H / 2)));

		char tmp[64] = {0};
		std::string s = "entrance/storyMap%d.png";
		sprintf(tmp, s.c_str(), _nodeId);

		CCSprite* bt = CCSprite::spriteWithSpriteFrameName(tmp);
		if(bt)
		{
			addChild(bt, 1, 1);
			bt->setAnchorPoint(CCPointZero);
			CCSize size = bt->getContentSize();
			bt->setPosition(ccp(POSX(113) - size.width / 2, POSX(56) - size.height / 2));
		}
	}
	else
	{
		std::string s = "entrance/city2.png";
		CCSprite* bt = CCSprite::spriteWithSpriteFrameName(s.c_str());
		if(bt)
		{
			addChild(bt, 1, 1);
			bt->setAnchorPoint(CCPointZero);
			CCSize size = bt->getContentSize();
			bt->setPosition(ccp(POSX(113) - size.width / 2, POSX(56) - size.height / 2));
		}
	}
}