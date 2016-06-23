#pragma once

#include "BaseType.h"

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class LHKeyboardNotificationLayer : public LayerNode, public CCIMEDelegate
{
public:
    LHKeyboardNotificationLayer();

    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
	
    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void setUp(CCNode * pUpMoveNode, float UpMoveDis);
    void setString(std::string s);
	std::string getString();

	CC_PROPERTY(bool, emptyStr, EmptyStr);
	CC_SYNTHESIZE(bool,_isCanBeTouched, IsCanBeTouched);
public:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
	CCNode * m_pUpMoveNode;
	CCPoint oldPos;
	float m_UpMoveDis;
    int m_pri;
    std::string m_s;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTF for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class MailTextFieldTTF : public LHKeyboardNotificationLayer,public CCTextFieldDelegate
{
public:
	MailTextFieldTTF();
    // KeyboardNotificationLayer
    virtual std::string subtitle();
	virtual void onClickTrackNode(bool bClicked);
	virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);

		 
    // CCLayer
    virtual void onEnter();

public:

};