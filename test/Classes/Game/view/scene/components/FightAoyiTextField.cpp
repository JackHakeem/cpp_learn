#include "FightAoyiTextField.h"
#include "utils/ScaleUtil.h"
#include "utils/effect/FightEffectGroup.h"
#include "view/scene/components/LiveThing.h"

const float origonY = 70.0f;
const float FontSize = 30.0f;

FightAoyiTextField::FightAoyiTextField()
{
	m_fStepCounter = 0.0f;
	m_iStepState = StepState_idle;
	m_iStepTotalCounter = 0;
	m_fTotalActionCount = 0.0f;
}

FightAoyiTextField::~FightAoyiTextField()
{}

bool FightAoyiTextField::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setPosition(ccp(0, 0));
	schedule (schedule_selector(FightAoyiTextField::step), 0.01f);
	return true;
}

bool FightAoyiTextField::createTxt(int skillId)
{
	if(skillId==1){//反击
		return false;//getMCNameEffect(sp,"Repel",100, 20, null, 0.1);
	}



	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/fight/skill/res_fight_skill.plist");
	char str[100];
	sprintf(str, "fight/skill/%d.png", skillId);
	//Begin Kenfly 20121108 : modify and bugfix
	CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
	if (NULL == pFrame)
		return false;

	SpriteNode* sp = new SpriteNode();
	if (!sp->initWithSpriteFrame(pFrame))
	{
		return false;
	}

	//SpriteNode* sp = new SpriteNode();
	//if (!sp->initWithSpriteFrameName(str))
	//{
	//	return false;
	//}

	//End Kenfly 20121108

	this->addChild(sp, 1, 0);
	sp->release();
	sp->setPosition(ccp(POSX(0), POSX(origonY)));
	
	//std::string preName = skillName;
	//
	//
	////
	//CCLabelTTF* pLabel = CCLabelTTF::labelWithString(preName.c_str(), CCSizeMake(POSX(300), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
	//pLabel->setPosition(ccp(POSX(0), POSX(origonY)));
	//this->addChild(pLabel, FightAoyiTextFieldZ_label, FightAoyiTextFieldTAG_label);
	//pLabel->setColor(ccc3(254, 189, 0));		
	
	this->setIsVisible(false);

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/fight/skill/res_fight_skill.plist");//kevinshit
	//if (CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/fight/skill/res_fight_skill.pvr.ccz"))
	//{
	//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/fight/skill/res_fight_skill.pvr.ccz");
	//}
	return true;
}

void FightAoyiTextField::doAction()
{
	SpriteNode *labelValue = (SpriteNode*)this->getChildByTag(0);
	if (!labelValue)
		return;

	changeStepState(StepState_rising);
	this->setIsVisible(true);

	{
		m_fTotalActionCount = 0.0f;
		//labelValue->setPosition(ccp(480, 320));
		labelValue->setOpacity(0);
		labelValue->setScale(0.1f);
		
		CCActionInterval*  actionFadeIn = cocos2d::CCFadeTo::actionWithDuration(0.2f, 255);//淡入
		CCActionInterval*  actionScaleTo = cocos2d::CCScaleTo::actionWithDuration(0.2f, 1.0f, 1.0f);//变大
		CCActionInterval*  actionBy = CCMoveBy::actionWithDuration(0.2f, ccp(0, POSX(110.0f)));//位移
	//	CCActionInterval* move_ease_in = (CCActionInterval*)CCEaseIn::actionWithAction(actionBy, POSX(4.0f));
		CCFiniteTimeAction* actionFstStage = CCSpawn::actions(actionFadeIn, actionScaleTo, actionBy, NULL);
		m_fTotalActionCount += 0.2f;

		CCActionInterval*  actionInterStage = CCMoveBy::actionWithDuration(0.4f, ccp(0, 0));//位移
		m_fTotalActionCount += 0.4f;

		CCActionInterval*  actionFadeOut2 = cocos2d::CCFadeOut::actionWithDuration(0.4f);//淡出
		CCActionInterval*  actionBy2 = CCMoveBy::actionWithDuration(0.4f, ccp(0, POSX(10.0f)));//位移
		CCFiniteTimeAction* actionSecStage = CCSpawn::actions(actionFadeOut2, actionBy2, NULL);
		m_fTotalActionCount += 0.4f;

		CCFiniteTimeAction* actionDst = CCSequence::actions(actionFstStage, actionInterStage, actionSecStage, NULL);
		labelValue->runAction(actionDst);		
	}

}
//
//void FightAoyiTextField::doAction()
//{
//	changeStepState(StepState_rising);
//	this->setIsVisible(true);
//
//	LiveThing* spParent = (LiveThing*)this->getParent();
//	if (spParent->getChildByTag(LiveThing::TAG_BLOOD))
//	{
//		spParent->getChildByTag(LiveThing::TAG_BLOOD)->setIsVisible(false);
//	}
//}


void FightAoyiTextField::changeStepState(int stepState)//keving
{
	m_fStepCounter = 0.0f;
	m_iStepTotalCounter = 0;
	m_iStepState = stepState;
}

void FightAoyiTextField::step(ccTime dt)//keving
{
	switch (m_iStepState)
	{
	case StepState_idle:
		{}
		break;
	case StepState_rising:
		{
			m_fStepCounter += dt;
			if (m_fStepCounter>=m_fTotalActionCount)
			{
				CCNode* sp = this->getParent();
				if (sp)
				{
					unschedule (schedule_selector(FightAoyiTextField::step));
					this->removeFromParentAndCleanup(true);
					CCLog("FightAoyiTextField remove");				
					return;					
				}
			}
		}
		break;
	default:
		break;
	}
}