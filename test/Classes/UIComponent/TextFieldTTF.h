#pragma once

#include "BaseType.h"


class KKTextFieldTTF: public CCTextFieldTTF
{
public:
    static KKTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    bool initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
protected:
    virtual void insertText(const char * text, int len);
	void deleteBackward();
public:
    void setString(const char *text);
    
    CC_PROPERTY(bool, _emojiRefuse, EmojiRefuse);
	bool m_isNumber;
	int m_numberCount;
	int m_banjiaoCount;
	int m_banjiaoCountMax;
};
//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public LayerNode, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

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
	void setIsNumber(bool value, int numberCount)
	{
		m_isNumber = value;
		m_numberCount = numberCount;
	}
public:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
	CCNode * m_pUpMoveNode;
	CCPoint oldPos;
	float m_UpMoveDis;
    int m_pri;
    std::string m_s;
    bool m_bEmojiRefuse;
	CCSize m_frame;
	bool m_isNumber;
	int m_numberCount;
	int m_banjiaoCountMax;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTF for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTF : public KeyboardNotificationLayer
{
public:
	TextFieldTTF();
    // KeyboardNotificationLayer
    virtual std::string subtitle();
	virtual void onClickTrackNode(bool bClicked);

	void setFieldSize(CCSize size); // LH0720
	
    // CCLayer
    virtual void onEnter();

public:
	
};