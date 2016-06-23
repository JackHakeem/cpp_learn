#include "FormationSprite.h"
#include "utils/ScaleUtil.h"

USING_NS_CC;

const int TAG_HIGH_LIGHT = 3001;

void FormationSprite::setIsHighLight( bool isHighLight )
{
	CCSprite *pHighLightSprite = NULL;
	if((pHighLightSprite = (CCSprite *)this->getChildByTag(TAG_HIGH_LIGHT)) == NULL)
	{
		float scale = this->getContentSize().height / POSX(98);
		CCSprite *pHighLightSprite = new CCSprite();
		pHighLightSprite->initWithSpriteFrameName("formation/formation_ontouch.png");
		pHighLightSprite->setScale(scale/* / CCDirector::sharedDirector()->getContentScaleFactor()*/);
		pHighLightSprite->setPosition(ccp(POSX(-4), POSX(-4)));
		pHighLightSprite->setAnchorPoint(CCPointZero);
		this->addChild(pHighLightSprite, 1, TAG_HIGH_LIGHT);//Doyang
		pHighLightSprite->release();
	}

	if(pHighLightSprite)
	{
		pHighLightSprite->setIsVisible(isHighLight);
	}
}

FormationSprite* FormationSprite::spriteWithFile( const char *pszFileName )
{
	FormationSprite *pobSprite = new FormationSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		//pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

FormationSprite* FormationSprite::spriteWithSpriteFrameName( const char *frameName )
{

	FormationSprite *pobSprite = new FormationSprite();
	if (pobSprite && pobSprite->initWithSpriteFrameName(frameName))
	{
		//pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

