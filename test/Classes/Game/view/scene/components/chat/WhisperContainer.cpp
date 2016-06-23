#include "WhisperContainer.h"
#include "../LiveThing.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"

WhisperContainer::WhisperContainer()
{

}

WhisperContainer::~WhisperContainer()
{

}

void WhisperContainer::loadBackGround()
{
	// Doyang 20120712
	CCUIBackground * pBackGround = (CCUIBackground *) this->getChildByTag(TAG_BG);
	if(!pBackGround)
	{
		pBackGround = new CCUIBackground();

		if(pBackGround && pBackGround->initWithSpriteFrame("ui.png",ccp(0,0),ccp(0,0),CCSizeMake(POSX(300), POSX(180))))
		{
			this->addChild(pBackGround, Z_BG, TAG_BG);
			this->setContentSize(pBackGround->getContentSize());
			pBackGround->release();
		}
		else
		{
			CC_SAFE_DELETE(pBackGround);
		}
	}
	//pBackGround->setAnchorPoint(ccp(0,0));
	/*pBackGround->setIsRelativeAnchorPoint(true);
	if (this->getChildByTag(TAG_BG))
	{
	this->removeChildByTag(TAG_BG,true);
	}*/
}

void WhisperContainer::loadContent(std::string szContent)
{
	CCLabelTTF * pContentText = CCLabelTTF::labelWithString(szContent.c_str(),CCSizeMake(180,100),CCTextAlignmentLeft,g_sSimHeiFont,POSX(28));
	//pContentText->setAnchorPoint(CCPointZero);
	pContentText->setIsRelativeAnchorPoint(true);
	pContentText->setColor(ccc3(255,255,255));
	pContentText->setPosition(ccp(POSX(0),POSX(0)));
	if (this->getChildByTag(TAG_CONTENT))
	{
		this->removeChildByTag(TAG_CONTENT,true);
	}
	this->addChild(pContentText,Z_CONTENT,TAG_CONTENT);
}

void WhisperContainer::showContent(struct _VOICE_* _voice)
{
	loadBackGround();
	loadContent(_voice->content);
}