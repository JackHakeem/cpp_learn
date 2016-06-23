#include "ChatContainer.h"
#include "../LiveThing.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"

ChatContainer::ChatContainer()
{

}

ChatContainer::~ChatContainer()
{

}

bool ChatContainer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}

void ChatContainer::loadBackGround()
{
// 	CCUIBackground * pBackGround = new CCUIBackground();
// 	pBackGround->initWithSpriteFrame("ui.png",ccp(0,0),ccp(0,0),CCSizeMake(POSX(340),POSX(190)));
// 	pBackGround->setAnchorPoint(ccp(0,0));
// 	pBackGround->setIsRelativeAnchorPoint(true);
// 	if (this->getChildByTag(TAG_BG))
// 	{
// 		this->removeChildByTag(TAG_BG,true);
// 	}
// 	this->addChild(pBackGround,Z_BG,TAG_BG);
// 	this->setContentSize(pBackGround->getContentSize());
}

void ChatContainer::showContent(struct _VOICE_ *_voice)
{
	
}

void ChatContainer::dispose()
{
	//_timerManage.remove(dd);

	if (this->getParent())
	{
		this->getParent()->removeChild(this,true);
	}
	//faceRegExp = null;
	//_txt = null;
	//shapeContainer = null;
	//spriteContainer = null;
}