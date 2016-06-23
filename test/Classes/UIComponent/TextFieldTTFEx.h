#pragma once

#include "BaseType.h"


class KKTextFieldTTFEx: public CCTextFieldTTF
{
public:
    static KKTextFieldTTFEx * textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    bool initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
protected:
    virtual void insertText(const char * text, int len);
    CC_PROPERTY(bool, _emojiRefuse, EmojiRefuse);
};
//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayerEx for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayerEx : public LayerNode, public CCIMEDelegate
{
public:
    KeyboardNotificationLayerEx();

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
    void setEmojiRefuse(bool value);

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
    bool m_bEmojiRefuse;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFEx for test TextFieldTTFEx default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFEx : public KeyboardNotificationLayerEx
{
public:
	TextFieldTTFEx();
    // KeyboardNotificationLayerEx
    virtual std::string subtitle();
	virtual void onClickTrackNode(bool bClicked);

	void setFieldSize(CCSize size); // LH0720
	
    // CCLayer
    virtual void onEnter();

public:
	
};