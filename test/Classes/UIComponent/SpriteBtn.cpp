#include "SpriteBtn.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"

CCMenuItemSprite* SpriteBtnFactory::make(const char* name, float w, float h, CCObject* target, SEL_MenuHandler selector)
{
	//CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(0, 0), ccp(0,0), CCSizeMake(POSX(w), POSX(h)));
	//this->addChild(_bg1, PopUIBgZ_bg1, PopUIBgTAG_bg1);
	_bg1->setContentSize(CCSizeMake(POSX(w+62/2), POSX(h+62/2)));

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg1.png", ccp(0, 0), ccp(0,0), CCSizeMake(POSX(w), POSX(h)));
	_bg2->setContentSize(CCSizeMake(POSX(w+62/2), POSX(h+62/2)));

	CCMenuItemSprite* dst = CCMenuItemImage::itemFromNormalSprite(_bg1, _bg2, 0, target, selector);
	_bg1->release();
	_bg2->release();

	if (name)
	{
		CCLabelTTF* pLable_name = CCLabelTTF::labelWithString(name, CCSizeMake(POSX(200), POSX(35)),CCTextAlignmentCenter, "Arial", POSX(35));
		pLable_name->setPosition(ccp(_bg1->getContentSize().width/2, _bg1->getContentSize().height/2));//_bg1->getContentSize().width
		pLable_name->setColor(ccc3(254, 189, 0));	
		dst->addChild(pLable_name, 0, 0);
	}

	return dst;
}