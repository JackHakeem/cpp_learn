#include "FightSkillTextField.h"
#include "utils/ScaleUtil.h"
#include "utils/effect/FightEffectGroup.h"
#include "view/scene/components/LiveThing.h"

const float origonY = 70.0f;
const float FontSize = 40.0f;

FightSkillTextField::FightSkillTextField()
{
	m_fStepCounter = 0.0f;
	m_iStepState = StepState_idle;
	m_iStepTotalCounter = 0;
	m_fTotalActionCount = 0.0f;
}

FightSkillTextField::~FightSkillTextField()
{}

bool FightSkillTextField::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setPosition(ccp(0, 0));
	schedule (schedule_selector(FightSkillTextField::step), 0.01f);
	return true;
}

bool FightSkillTextField::createTxt(std::string skillName, int skillId)
{
	if(skillId==1){//反击
		return false;//getMCNameEffect(sp,"Repel",100, 20, null, 0.1);
	}

	std::string preName = skillName;
	
	
	//
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(preName.c_str(), CCSizeMake(POSX(300), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabel->setPosition(ccp(POSX(10), POSX(origonY)));
	this->addChild(pLabel, FightSkillTextFieldZ_label, FightSkillTextFieldTAG_label);
	pLabel->setColor(ccc3(254, 189, 0));		
	
	this->setIsVisible(false);
	return true;
}


void FightSkillTextField::doAction()
{
	SpriteNode *labelValue = (SpriteNode*)this->getChildByTag(FightSkillTextFieldTAG_label);
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
		//CCActionInterval* move_ease_in = (CCActionInterval*)CCEaseIn::actionWithAction(actionBy, POSX(4.0f));
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
//void FightSkillTextField::doAction()
//{
//	changeStepState(StepState_rising);
//	this->setIsVisible(true);
//
//
//	LiveThing* spParent = (LiveThing*)this->getParent();
//	if (spParent)
//	{
//		if (spParent->getChildByTag(LiveThing::TAG_BLOOD))
//		{
//			spParent->getChildByTag(LiveThing::TAG_BLOOD)->setIsVisible(false);
//		}
//	}
//}


void FightSkillTextField::changeStepState(int stepState)//keving
{
	m_fStepCounter = 0.0f;
	m_iStepTotalCounter = 0;
	m_iStepState = stepState;
}

void FightSkillTextField::step(ccTime dt)//keving
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
					unschedule (schedule_selector(FightSkillTextField::step));
					this->removeFromParentAndCleanup(true);
					CCLog("FightSkillTextField remove");				
					return;					
				}
			}
		}
		break;
	default:
		break;
	}
}