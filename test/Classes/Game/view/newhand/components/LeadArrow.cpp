#include "LeadArrow.h"
#include "utils/ScaleUtil.h"
#include "model/newhand/NewhandManager.h"
#include "CCUIBackground.h"

#define DIR_MOVING_TIME (0.4f)

LeadArrow::LeadArrow( int arrow_dir, int x, int y, string info )
{
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setAnchorPoint(CCPointZero);
	this->setPosition(ccp(x, y));
	int style = arrow_dir / 10;
	if(style == 1)
	{
		//普通样式，tip框+箭头
		createTipStyle(arrow_dir % 10, info);
	}
	else if(style == 2)
	{
		//只有一个Go的样式
		createGoStyle(arrow_dir % 10);
	}
	else if(style == 3)
	{
		//布阵专用样式
		createSingleArrowStyle(arrow_dir % 10, info);
	}
}

void LeadArrow::createTipStyle( int arrow_dir, string info )
{
	CCLabelTTF *_tip = NULL;
	CCSprite *_arrow = NULL;
	CCAction *_action = NULL;
	CCUIBackground * pback = 0;
	int /*arrowX, arrowY, */arrowRotation = 0, arrowScaleX = 1;

	float width = POSX(160);
	float fontSize = POSX(22);
	int lineNum = getLineNum(info,fontSize , width) + 1;

	//Doyang 20120723
	//Finger special...
	ScriptVo *pScript = NewhandManager::Instance()->_pCurScript;
	if(pScript && (pScript->id == 3107 || pScript->id == 2307 || pScript->id == 1117))
	{
		this->setPosition(POS(ccp(820, 470), ScaleUtil::CENTER));

		if (info != "")
		{
			_tip = CCLabelTTF::labelWithString(info.c_str(), CCSizeMake(width , POSX(24) *lineNum ) , CCTextAlignmentLeft ,"Arial", fontSize);
			//_tip->setAnchorPoint(CCPointZero);
			_tip->setPosition(ccp(0, POSX(-50)));
			this->addChild(_tip,2);

			// info background

			CCSize size = _tip->getContentSize();
			CCPoint pos = _tip->getPosition();
			pback = new CCUIBackground();
			pback->initWithSpriteFrame("ui4.png" , CCPointZero , CCPointZero , CCSizeMake(size.width + POSX(20) , size.height /*  + POSX(30)*/) , 255);		
			pback->setPosition(ccp(pos.x - size.width /2 - POSX(10) , pos.y  - size.height/2 ));
			this->addChild(pback,0);
			pback->release();

			/*
			CCSprite * pLeaderHead = new CCSprite();
			pLeaderHead->initWithFile("assets/icon/head/12.png");
			pLeaderHead->setPosition(pback->getPosition());
			this->addChild(pLeaderHead,1);
			pLeaderHead->release();
			*/
		}

		_arrow = CCSprite::spriteWithSpriteFrameName("newhand/finger.png");
		/*CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(0.3, ccp(POSX(40), POSX(-40)));
		CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(0.3, ccp(POSX(60), POSX(-40)));*/
		CCFadeIn *fadeInAction = CCFadeIn::actionWithDuration(0.3);
		CCFadeOut *fadeOutAction = CCFadeOut::actionWithDuration(0.3);
		_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(fadeInAction, fadeOutAction));
		_arrow->setRotation(arrowRotation);
		_arrow->setScaleX(arrowScaleX);
		_arrow->setAnchorPoint(CCPointZero);
		_arrow->setPosition(ccp(0, POSX(-20)));
		this->addChild(_arrow);
		if(_action)
			_arrow->runAction(_action);

		/*char p[20] = "newhand_finger";
		CCAnimation *pAnimation = NULL;
		pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(p);
		if(pAnimation == NULL)
		{
			CCMutableArray<CCSpriteFrame*> *pAnimFrames = new CCMutableArray<CCSpriteFrame*>(2);
			CCTexture2D *pFingerArrowTexture1 = CCTextureCache::sharedTextureCache()->addImage("assets/ui/newhand/point_finger_1.png");
			CCSpriteFrame *pFingerArrow1 = CCSpriteFrame::frameWithTexture(pFingerArrowTexture1,
				CCRectMake(0, 0, pFingerArrowTexture1->getContentSize().width, pFingerArrowTexture1->getContentSize().height));
			pAnimFrames->addObject(pFingerArrow1);
			CCTexture2D *pFingerArrowTexture2 = CCTextureCache::sharedTextureCache()->addImage("assets/ui/newhand/point_finger_2.png");
			CCSpriteFrame *pFingerArrow2 = CCSpriteFrame::frameWithTexture(pFingerArrowTexture2,
				CCRectMake(0, 0, pFingerArrowTexture2->getContentSize().width, pFingerArrowTexture2->getContentSize().height));
			pAnimFrames->addObject(pFingerArrow2);
			pAnimation = CCAnimation::animationWithFrames(pAnimFrames, 0.5f);
			CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, p);
		}

		CCSprite *pFingerArrowSprite = CCSprite::spriteWithFile("assets/ui/newhand/point_finger_2.png");
		pFingerArrowSprite->setAnchorPoint(CCPointZero);
		pFingerArrowSprite->setPosition(ccp(POSX(-80), 0));
		this->addChild(pFingerArrowSprite);
		if(pAnimation)
			pFingerArrowSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(pAnimation)));*/
		return;
	}

	if(!_arrow)
	{
		if(info != "")
		{
			_tip = CCLabelTTF::labelWithString(info.c_str(),CCSizeMake(width , POSX(24) * lineNum) , CCTextAlignmentLeft,"Arial", fontSize);
			_tip->setPosition(ccp(0, 0 ));
			this->addChild(_tip, 2);

			// info background
			CCSize size = _tip->getContentSize();
			CCPoint pos = _tip->getPosition();
			pback = new CCUIBackground();
			pback->initWithSpriteFrame("ui.png" , CCPointZero , CCPointZero , CCSizeMake(size.width + POSX(20), size.height /* + POSX(20)*/) , 255);			
			pback->setPosition(ccp(pos.x - size.width/2 -POSX(10), pos.y - size.height/2));
			this->addChild(pback,0);
			pback->release();

			/*
			CCSprite * pLeaderHead = new CCSprite();
			pLeaderHead->initWithFile("assets/icon/head/12.png");
			pLeaderHead->setPosition(pback->getPosition());
			this->addChild(pLeaderHead,1);
			pLeaderHead->release();
			*/

			//_arrow = Reflection.createInstance("lead_arrow");
			_arrow = CCSprite::spriteWithSpriteFrameName("newhand/point_up.png");
		}
		else
		{
			_arrow = CCSprite::spriteWithSpriteFrameName("newhand/point_right.png");
			//_arrow = Reflection.createInstance("lead_leadArrow")
		}
	}

	switch(arrow_dir)
	{
	case 1:
		{
//			arrowX = 165;
//			arrowY = 20;
//			if(info == ""){
////				arrowX -= 30;
////				arrowY -= 7;
//			}
			CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(-10), 0));
			CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(10), 0));
			_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));

			if (_tip)
			{
				_tip->setPosition(ccp((-1) * width/2 + POSX(10), POSX(0)));
				if (pback)
				{
					CCSize size = _tip->getContentSize();
					CCPoint pos = _tip->getPosition();
					pback->setPosition(ccp(pos.x - size.width /2 - POSX(10) , pos.y  - size.height/2));
				}
			}

		}
		break;
	case 2:
		{
			arrowRotation = 90;
//			arrowX = 155;
//			arrowY = 49;
			CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(0, POSX(-10)));
			CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(0, POSX(10)));
			_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));
		}
		break;
	case 3:
		{
			arrowRotation = 225;
			//		arrowX = 10;
			//		arrowY = 20;
			CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(-5), POSX(5)));
			CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(5), POSX(-5)));
			_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));

			if (_tip)
			{
				_tip->setPosition(ccp(width/2 - POSX(10), POSX(0)));
				if (pback)
				{
					CCSize size = _tip->getContentSize();
					CCPoint pos = _tip->getPosition();
					pback->setPosition(ccp(pos.x - size.width /2 - POSX(10) , pos.y  - size.height/2));
				}
			}
		}
		break;
	case 4:
		{
			arrowRotation = 270;
			//		arrowX = 20;
			//		arrowY = 20;

			CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(0), POSX(10)));
			CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(0), POSX(-10)));
			_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));

			if (_tip)
			{
				_tip->setPosition(ccp(POSX(0), (-1) * lineNum * fontSize / 2 + POSX(0)));
				if (pback)
				{
					CCSize size = _tip->getContentSize();
					CCPoint pos = _tip->getPosition();
					pback->setPosition(ccp(pos.x - size.width /2 - POSX(10)  , pos.y  - size.height/2));
				}
			}
		}
		
		break;

	case 5:
		{
			arrowScaleX = -1;
			arrowRotation = 90;
			//		arrowX = 160;
			//		arrowY = 20;
			CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(15), POSX(-45)));
			CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(15), POSX(-65)));
			_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));

			if (_tip)
			{
				_tip->setPosition(ccp(POSX(0), (-1) * lineNum * fontSize / 2 + POSX(-20)));
				if (pback)
				{
					CCSize size = _tip->getContentSize();
					CCPoint pos = _tip->getPosition();
					pback->setPosition(ccp(pos.x - size.width /2 - POSX(10)  , pos.y  - size.height/2));
				}
			}

// 			if (_arrow)
// 			{
// 				CCPoint pos = _arrow->getPosition();
// 				_arrow->setPosition(ccp(pos.x + POSX(20) , pos.y - POSX(15)));
// 			}
		}
		
		break;

	case 6:
		{
			arrowRotation = 180;
			CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(-10), POSX(0)));
			CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(DIR_MOVING_TIME, ccp(POSX(10), POSX(0)));
			_action = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));

			if (_tip)
			{
				_tip->setPosition(ccp(width/2 - POSX(10), (-1) * lineNum * fontSize / 2 + POSX(0)));
				if (pback)
				{
					CCSize size = _tip->getContentSize();
					CCPoint pos = _tip->getPosition();
					pback->setPosition(ccp(pos.x - size.width /2 - POSX(10) , pos.y  - size.height/2));
				}
			}
			if(_arrow)
			{
				_arrow->setFlipY(true);
			}
		}
		
		break;
	default:
		break;
	} 

	if(!_arrow)
		return;

	_arrow->setRotation(arrowRotation);
	_arrow->setScaleX(arrowScaleX);
	_arrow->setAnchorPoint(CCPointZero);
	_arrow->setPosition(CCPointZero);
	this->addChild(_arrow);
	if(_action)
		_arrow->runAction(_action);

}

void LeadArrow::createGoStyle( int arrow_dir )
{
	CCSprite *_arrow;
	_arrow = CCSprite::spriteWithFile("assets/ui/newhand/point_left.png");
	int arrowX = 0, arrowY = 0, arrowRotation = 0, arrowScaleX = 1;
	switch(arrow_dir){
	case 2:
		arrowRotation = 90;
		break;
	case 3:
		arrowScaleX = -1;
		arrowRotation = 28;
		break;
	case 4:
		arrowRotation = 270;
		break;
	}
	_arrow->setRotation(arrowRotation);
	_arrow->setScaleX(arrowScaleX);
	_arrow->setAnchorPoint(CCPointZero);
	_arrow->setPosition(ccp(arrowX, arrowY));
	this->addChild(_arrow);
}

void LeadArrow::createSingleArrowStyle( int arrow_dir, string info )
{
	//CCLabelTTF *_tip = CCLabelTTF::labelWithString(info.c_str(), "Arial", 20);

	//info = info.replace(/#l/ig, "<font color='#FFCC00'>");
	//		info = info.replace(/#r/ig, "</font>");
	//		_tip = Reflection.createInstance("lead_tip");
	//		_arrow = Reflection.createInstance("lead_deployArrow");
	//		/*switch(arrow_dir){
	//			case 2:
	//				break;
	//		}*/
	//		this.addChild(_arrow);
	//		this.addChild(_tip);
	//		_tip.x = -_tip.width - 40;
	//		_tip.y = 0;
	//		_tip["_txtCont"].htmlText = info;
	//		_tip["_txtCont"].mouseEnabled = false;
}

int LeadArrow::getLineNum(std::string strText, float fontSize , float lineWidth)
{
	if (strText.empty())
	{
		return 0 ;
	}
	
	int lineNum = 1;
	float sumWidth = 0;
	int widthByte = 0;
	int lineByte = 0;
	int beginPos = 0;
	int pos = beginPos;
	int length = strText.length();
	std::string strtmp("");
	while (sumWidth < length)
	{
		while (((widthByte * fontSize/2.0f) < lineWidth) && (pos < length))
		{
			if (strText[pos] & 0x80)
			{
				widthByte += 3;
				pos += 3;
			}
			else
			{
				widthByte += 1;
				pos += 1;
			}
		}
		strtmp = strText; 
		std::string str = strtmp.substr(beginPos,widthByte);

		beginPos += widthByte;
		pos = beginPos;

		sumWidth += widthByte;
		widthByte = 0;

		++lineNum;
	}

	return lineNum;
}