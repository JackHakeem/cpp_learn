#include "Effect1.h"
#include "utils/loader/KKAnimationFactory.h"

Effect1::Effect1()
{
	sp = NULL;
	animation = NULL;
}

void Effect1::showEffect(std::string path, std::string frameName, float px, float py, CCLayer* parent)
{
	if(!sp)
		sp = CCSprite::spriteWithFile("");

	CCNode* node = sp->getParent();
	if(node)
		node->removeChild(sp, false);

	if(parent && sp->getParent() == NULL)
		parent->addChild(sp);

	animation = g_pKKAnimationFactory->registAni(path.c_str(), frameName.c_str(), 0, 0.1f);
	if(animation && sp)
		sp->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(animation)));
}