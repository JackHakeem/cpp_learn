#include "ImageTxt.h"
#include "utils/ScaleUtil.h"
#include "utils/effect/FightEffectGroup.h"
#include "view/scene/components/LiveThing.h"
#include "utils/ValuesUtil.h"

const float origonY = 70.0f;

ImageTxt::ImageTxt()
{
    m_spSeat = 0;
    m_bIscrit = false;
	m_fStepCounter = 0.0f;
	m_iStepState = StepState_idle;
	m_iStepTotalCounter = 0;
	m_fTotalActionCount = 0.0f;
}

ImageTxt::~ImageTxt()
{}

bool ImageTxt::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setPosition(ccp(0, 0));
	schedule (schedule_selector(ImageTxt::step), 0.01f);
	return true;
}

void ImageTxt::createTxt(int type, int seat, int value, bool iscrit)
{
    m_bIscrit = iscrit;
    m_spSeat = seat;
	std::string preName = "";
	if (type == BLOOD_DOWN)
	{
		preName = "assets/ui/fight/fonts/mydamage.fnt";
	}
	else if (type == BLOOD_UP)
	{
		preName = "assets/ui/fight/fonts/addbleed.fnt";
	}
	else if(type == MP_UP){
		preName = "assets/ui/fight/fonts/addire.fnt";
	}
		
	char toChar[30];
    
    if (type == MP_UP)
        sprintf(toChar, "%s+%d", ValuesUtil::Instance()->getString("FT012").c_str(), value);
    else if (value<0 && m_bIscrit)
        sprintf(toChar, "%s%d", ValuesUtil::Instance()->getString("FT011").c_str(), value);
	else if (value<0)
		sprintf(toChar, "%d", value);
	else
		sprintf(toChar, "+%d", value);
	//
	CCLabelBMFont *labelValue = CCLabelBMFont::labelWithString(toChar, preName.c_str());
	addChild(labelValue, ImageTxtZ_labelValue, ImageTxtTAG_labelValue);
	labelValue->setPosition( ccp(0, POSX(origonY)) );
    
	this->setIsVisible(false);


}

void ImageTxt::doAction()
{
	CCLabelBMFont *labelValue = (CCLabelBMFont*)this->getChildByTag(ImageTxtTAG_labelValue);
	if (!labelValue)
		return;

	changeStepState(StepState_rising);
	this->setIsVisible(true);

    
    if (m_bIscrit)
	{
		m_fTotalActionCount = 0.0f;
		//labelValue->setPosition(ccp(480, 320));
		labelValue->setOpacity(0);
		labelValue->setScale(0.1f);
		
        float scaleto = m_bIscrit?2.2f:1.4f;
        float actionFstStageTime = m_bIscrit?0.3f:0.4f;
		CCActionInterval*  actionFadeIn = cocos2d::CCFadeTo::actionWithDuration(actionFstStageTime, 255);//淡入
		CCActionInterval*  actionScaleTo = cocos2d::CCScaleTo::actionWithDuration(actionFstStageTime, scaleto, scaleto);//变大
		CCActionInterval*  actionBy = CCMoveBy::actionWithDuration(actionFstStageTime, ccp(0, m_bIscrit?POSX(100.0f):POSX(70.0f)));//位移
		//CCActionInterval* move_ease_in = (CCActionInterval*)CCEaseIn::actionWithAction(actionBy, POSX(4.0f));
		CCFiniteTimeAction* actionFstStage = CCSpawn::actions(actionFadeIn, actionScaleTo, actionBy, NULL);
		m_fTotalActionCount += actionFstStageTime;

		CCActionInterval*  actionInterStage = CCMoveBy::actionWithDuration(0.4f, ccp(0, 0));//位移
		m_fTotalActionCount += 0.4f;

		CCActionInterval*  actionFadeOut2 = cocos2d::CCFadeOut::actionWithDuration(0.3f);//淡出
		CCActionInterval*  actionBy2 = CCMoveBy::actionWithDuration(0.3f, ccp(0, POSX(8.0f)));//位移
		CCFiniteTimeAction* actionSecStage = CCSpawn::actions(actionFadeOut2, actionBy2, NULL);
		m_fTotalActionCount += 0.3f;

		CCFiniteTimeAction* actionDst = CCSequence::actions(actionFstStage, actionInterStage, actionSecStage, NULL);
		labelValue->runAction(actionDst);		
	}
    else
    {
  //      CCPoint JumpPosBy = ccp(0,0);//(m_spSeat>=9)?ccp(POSX(-50-CCRANDOM_0_1()*30), 0):ccp(POSX(50+CCRANDOM_0_1()*30), 0);
  //      m_fTotalActionCount = 0.0f;

		//labelValue->setOpacity(255);
		//labelValue->setScale(1.2f);
  //      //jump
  //      CCActionInterval*  actionFstStage = CCJumpBy::actionWithDuration(0.8, JumpPosBy, POSX(180), 1);
  //      //fade out
  //      CCActionInterval*  actionScaleWait2 = cocos2d::CCScaleTo::actionWithDuration(0.6, 1.4);
  //      CCActionInterval*  actionFadeOut2 = cocos2d::CCFadeOut::actionWithDuration(0.3f);
  //      CCFiniteTimeAction* actionSecStage = CCSequence::actions(actionScaleWait2, actionFadeOut2, NULL);
  //      
  //      
  //      CCFiniteTimeAction* actionDst = CCSpawn::actions(actionFstStage,  actionSecStage, NULL);

		//labelValue->runAction(actionDst);
  //      m_fTotalActionCount += 0.8f;
		m_fTotalActionCount = 0.0f;
		CCActionInterval*  actionFstUpMove = CCMoveBy::actionWithDuration(0.5, ccp(0, 70));
		CCActionInterval* actionFstUpStage = (CCActionInterval*)CCEaseOut::actionWithAction(actionFstUpMove, POSX(4.0f));
		m_fTotalActionCount += 0.5f;

		CCActionInterval*  actionSecDownMove = CCMoveBy::actionWithDuration(0.3, ccp(0, -6));
		m_fTotalActionCount += 0.3f;

		CCFiniteTimeAction* actionDst = CCSequence::actions(actionFstUpStage, actionSecDownMove, NULL);
		labelValue->runAction(actionDst);
    }
}


void ImageTxt::changeStepState(int stepState)//keving
{
	m_fStepCounter = 0.0f;
	m_iStepTotalCounter = 0;
	m_iStepState = stepState;
}

void ImageTxt::step(ccTime dt)//keving
{
	switch (m_iStepState)
	{
	case StepState_idle:
		{}
		break;
	case StepState_rising:
		{
			m_fStepCounter += dt;
			if (m_fStepCounter > m_fTotalActionCount)
			{
				CCNode* sp = this->getParent();
				if (sp)
				{
					unschedule (schedule_selector(ImageTxt::step));
					this->removeFromParentAndCleanup(true);
					CCLog("ImageTxt remove");				
					return;					
				}
			}
		}
		break;
	default:
		break;
	}
}

//m_fStepCounter += dt;
//if (m_fStepCounter>=0.01f)
//{
//	m_fStepCounter = 0.0f;
//	if (m_iStepTotalCounter < 10)//上升
//		this->setPosition(ccpAdd(this->getPosition(), ccp(0, POSX(8.0f))));
//	else//空中保持
//	{
//		//this->setPosition(ccpAdd(this->getPosition(), ccp(0, POSX(0.0f))));
//	}
//		
//	m_iStepTotalCounter++;
//}
//
//if (m_iStepTotalCounter >= 40)
//{
//	LiveThing* spParent = (LiveThing*)this->getParent();
//	if (spParent)
//	{
//		//spParent->_pHPLayer->setIsVisible(true); // L.H.
//	}

//	changeStepState(StepState_idle);
//	FightEffectGroup::Instance()->completeOneAction();


//	CCNode* sp = this->getParent();
//	if (sp)
//	{
//		int tag = this->getTag();
//		LayerNode* txt = (LayerNode*)sp->getChildByTag(tag);
//		if (txt && (txt->getMyFocusGID() == this->getMyFocusGID()))
//		{
//			sp->removeChildByTag(tag, true);
//			CCLog("ImageTxt remove");
//			return;					
//		}
//	}
//}