#include "MailTextFieldTTF.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

LHKeyboardNotificationLayer::LHKeyboardNotificationLayer()
: m_pTrackNode(0),m_pUpMoveNode(0)
{
    setIsTouchEnabled(true);
	m_UpMoveDis = 0.0f;
    m_pri = -1500;
	setEmptyStr(false);
	setIsCanBeTouched(true);
}

void LHKeyboardNotificationLayer::setUp(CCNode * pUpMoveNode, float UpMoveDis)
{
	m_pUpMoveNode = pUpMoveNode;
	m_UpMoveDis = UpMoveDis;
}

void LHKeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_pri, false);
}

void LHKeyboardNotificationLayer::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
	if (getEmptyStr())
		setString("");
    if (m_pUpMoveNode)
	{
		//oldPos = m_pUpMoveNode->getPosition();
		m_pUpMoveNode->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(0, 0)));
	}
/*
	CCNode* p = this->getChildByTag(1000);
	if (p)
	{
		p->removeFromParentAndCleanup(true);
	}
 */
	//CCTextFieldTTF *pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(ValuesUtil::Instance()->getString("INPUT001").c_str(),
	//	CCSizeMake(POSX(600), POSX(60)),
	//	CCTextAlignmentLeft,
	//	"Arial",
	//	POSX(20));
	//if(pTextField)
	//{
	//	if (m_s.size() > 0)
	//		pTextField->setString(m_s.c_str());
	////	pTextField->setContentSize(CCSizeMake((380), (40)));
	//	//pTextField->setAnchorPoint(CCPointZero);
	//	//pTextField->setPosition(ccp(226, 376));
	//	//pTextField->attachWithIME();

	//	this->addChild(pTextField, 0, 1000);
	//}

}


void LHKeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! m_pTrackNode)
    {
        return;
    }

    CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
        rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! CCRect::CCRectIntersectsRect(rectTracked, info.end))
    {
        return;
    }

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = CCRect::CCRectGetMaxY(info.end) - CCRect::CCRectGetMinY(rectTracked);
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

    // move all the children node of KeyboardNotificationLayer
    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
       // node->setPosition(pos);kevinchange
    }


}

// CCLayer function

bool LHKeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!getIsCanBeTouched())
	{
		return false;
	}

    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->locationInView(pTouch->view());	
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
	//
	CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(CCRect::CCRectContainsPoint(rect, point));
    CCLOG("----------------------------------");


    return true;
}

void LHKeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	return;

    if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->locationInView(pTouch->view());	
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);

    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }

    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(CCRect::CCRectContainsPoint(rect, point));
    CCLOG("----------------------------------");
}

//CC_PROPERTY(bool, emptyStr, EmptyStr);
void LHKeyboardNotificationLayer::setEmptyStr(bool value)
{
	emptyStr = value;
}

bool LHKeyboardNotificationLayer::getEmptyStr()
{
	return emptyStr;
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTF
//////////////////////////////////////////////////////////////////////////
MailTextFieldTTF::MailTextFieldTTF()
{
	m_s = "";
}

std::string MailTextFieldTTF::subtitle()
{
    return "TextFieldTTF with default behavior test";
}

void MailTextFieldTTF::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTF:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
        
        if (m_pUpMoveNode)
        {
            oldPos = m_pUpMoveNode->getPosition();
            m_pUpMoveNode->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(m_pUpMoveNode->getPosition().x, m_UpMoveDis)));
        }
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTF:CCTextFieldTTF detachWithIME");
   //     pTextField->detachWithIME();
    }
}

void LHKeyboardNotificationLayer::setString(std::string s)
{
	if (m_pTrackNode)
		((CCTextFieldTTF*)m_pTrackNode)->setString(s.c_str());

	m_s = s;
}

std::string LHKeyboardNotificationLayer::getString()
{
	if (m_pTrackNode)
		return ((CCTextFieldTTF*)m_pTrackNode)->getString();
	return "";
}

void MailTextFieldTTF::onEnter()
{
    LHKeyboardNotificationLayer::onEnter();

    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	/*
    CCTextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(ValuesUtil::Instance()->getString("INPUT001").c_str(),//"<input player name>"
        "Arial", 20);
    addChild(pTextField);
	*/

    
    if (this->getChildByTag(1000))
	{
		return;
	}
	    
    CCTextFieldTTF *pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(ValuesUtil::Instance()->getString("INPUT001").c_str(),
		CCSizeMake(POSX(440),POSX(230)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(24));
	if(pTextField)
	{
		//pTextField->setDelegate(this);
		if (m_s.size() > 0)
			pTextField->setString(m_s.c_str());
	//	pTextField->setContentSize(CCSizeMake((380), (40)));
		//pTextField->setAnchorPoint(CCPointZero);
		//pTextField->setPosition(ccp(226, 376));
		//pTextField->attachWithIME();

		this->addChild(pTextField, 0, 1000);
		//pTextField->setColor(ccc3(22,22,222));
	}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
	// so we had to set a higher position to make it visable
	//pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
//	pTextField->setPosition(ccp(s.width / 2, s.height / 2));
#endif

    m_pTrackNode = pTextField;
	
}

bool MailTextFieldTTF::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen)
{
	// if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
	if (pSender->getCharCount() > 5)
	{
		return true;
	}

	CCTextFieldDelegate::onTextFieldInsertText(pSender,text,nLen);
}
