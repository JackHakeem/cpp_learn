#include "FightSpecialFontField.h"
#include "utils/ScaleUtil.h"
#include "utils/effect/FightEffectGroup.h"
#include "view/scene/components/LiveThing.h"

const float origonY = 70.0f;
const float FontSize = 30.0f;

FightSpecialFontField::FightSpecialFontField()
{
    m_iStyle = 0;
	m_fStepCounter = 0.0f;
	m_iStepState = StepState_idle;
	m_iStepTotalCounter = 0;
    m_fTotalActionCount = 0;
}

FightSpecialFontField::~FightSpecialFontField()
{}

bool FightSpecialFontField::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setPosition(ccp(0, 0));
	schedule (schedule_selector(FightSpecialFontField::step), 0.01f);
	return true;
}

bool FightSpecialFontField::createTxt(int style)
{
	std::string str = "assets/ui/fight/fonts/baojibg.png";
	switch(style)
	{
	case BAOJI:
		str = "assets/ui/fight/fonts/baoji.png";
		break;
	case FANJI:
		str = "assets/ui/fight/fonts/fanji.png";
		break;
	case NUQI:
		str = "assets/ui/fight/fonts/nuqi.png";
		break;
	case SHANBI:
		str = "assets/ui/fight/fonts/shanbi.png";
		break;
	}
    m_iStyle = style;
	//
	SpriteNode* sp = new SpriteNode();
	if (!sp->initWithFile(str.c_str()))
	{
		return false;
	}
	this->addChild(sp, 1, 0);
	sp->release();
	sp->setPosition(ccp(POSX(0), POSX(origonY)));

	/*CCLabelTTF* pLabel = CCLabelTTF::labelWithString(str.c_str(), CCSizeMake(POSX(300), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabel->setPosition(ccp(POSX(10), POSX(origonY)));
	this->addChild(pLabel, FightSpecialFontFieldZ_label, FightSpecialFontFieldTAG_label);
	pLabel->setColor(ccc3(254, 189, 0));*/		
	
	this->setIsVisible(false);
	return true;
}


void FightSpecialFontField::doAction()
{
	SpriteNode *labelValue = (SpriteNode*)this->getChildByTag(0);
	if (!labelValue)
		return;
    
	changeStepState(StepState_rising);
	this->setIsVisible(true);
    
    if (m_iStyle == BAOJI)
    {
		m_fTotalActionCount = 0.0f;
		//labelValue->setPosition(ccp(480, 320));
		labelValue->setOpacity(0);
		labelValue->setScale(0.1f);
		
		CCActionInterval*  actionFadeIn = cocos2d::CCFadeTo::actionWithDuration(0.4f, 255);//淡入
		CCActionInterval*  actionScaleTo = cocos2d::CCScaleTo::actionWithDuration(0.4f, 2.0f, 2.0f);//变大

		CCFiniteTimeAction* actionFstStage = CCSpawn::actions(actionFadeIn, actionScaleTo, NULL);
		m_fTotalActionCount += 0.4f;
        
		CCActionInterval*  actionInterStage = CCMoveBy::actionWithDuration(0.3f, ccp(0, 0));//位移
		m_fTotalActionCount += 0.3f;
        
		CCActionInterval*  actionFadeOut2 = cocos2d::CCFadeOut::actionWithDuration(0.3f);//淡出
		CCActionInterval*  actionScaleTo2 = cocos2d::CCScaleTo::actionWithDuration(0.3f, 0.1f, 0.1f);
		CCFiniteTimeAction* actionSecStage = CCSpawn::actions(actionFadeOut2, actionScaleTo2, NULL);
		m_fTotalActionCount += 0.3f;
        
		CCFiniteTimeAction* actionDst = CCSequence::actions(actionFstStage, actionInterStage, actionSecStage, NULL);
		labelValue->runAction(actionDst);
    }
    else
	{
		m_fTotalActionCount = 0.0f;
		//labelValue->setPosition(ccp(480, 320));
		labelValue->setOpacity(0);
		labelValue->setScale(0.1f);
		
		CCActionInterval*  actionFadeIn = cocos2d::CCFadeTo::actionWithDuration(0.4f, 255);//淡入
		CCActionInterval*  actionScaleTo = cocos2d::CCScaleTo::actionWithDuration(0.4f, 1.1f, 1.1f);//变大
		CCActionInterval*  actionBy = CCMoveBy::actionWithDuration(0.4f, ccp(0, POSX(70.0f)));//位移
		//CCActionInterval* move_ease_in = (CCActionInterval*)CCEaseIn::actionWithAction(actionBy, POSX(4.0f));
		CCFiniteTimeAction* actionFstStage = CCSpawn::actions(actionFadeIn, actionScaleTo, actionBy, NULL);
		m_fTotalActionCount += 0.4f;
        
		CCActionInterval*  actionInterStage = CCMoveBy::actionWithDuration(0.3f, ccp(0, 0));//位移
		m_fTotalActionCount += 0.3f;
        
		CCActionInterval*  actionFadeOut2 = cocos2d::CCFadeOut::actionWithDuration(0.3f);//淡出
		CCActionInterval*  actionBy2 = CCMoveBy::actionWithDuration(0.3f, ccp(0, POSX(-10.0f)));//位移
		CCFiniteTimeAction* actionSecStage = CCSpawn::actions(actionFadeOut2, actionBy2, NULL);
		m_fTotalActionCount += 0.3f;
        
		CCFiniteTimeAction* actionDst = CCSequence::actions(actionFstStage, actionInterStage, actionSecStage, NULL);
		labelValue->runAction(actionDst);
	}

    LiveThing* spParent = (LiveThing*)this->getParent();
    if (spParent)
    {
        if (spParent->getChildByTag(LiveThing::TAG_BLOOD))
        {
            spParent->getChildByTag(LiveThing::TAG_BLOOD)->setIsVisible(false);
        }
    }
}


void FightSpecialFontField::changeStepState(int stepState)//keving
{
	m_fStepCounter = 0.0f;
	m_iStepTotalCounter = 0;
	m_iStepState = stepState;
}

void FightSpecialFontField::step(ccTime dt)//keving
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
                    LiveThing* spParent = (LiveThing*)this->getParent();
                    if (spParent->getChildByTag(LiveThing::TAG_BLOOD))
                    {
                        spParent->getChildByTag(LiveThing::TAG_BLOOD)->setIsVisible(true);//kevinchange0811
                    }
                    
                    changeStepState(StepState_idle);
					unschedule (schedule_selector(FightSpecialFontField::step));
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