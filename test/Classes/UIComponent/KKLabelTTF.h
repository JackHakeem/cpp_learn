#pragma once

#include "cocos2d.h"
USING_NS_CC;



class KKLabelTTF : public cocos2d::CCLayer
{
public:
    KKLabelTTF();
    ~KKLabelTTF();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(float fontSize, float rowHeight, CCSize size);//字体大小  行高 显示框框大小
    virtual void add(std::string& value, cocos2d::ccColor3B color, bool isBtn=false);
    
public:
    float m_fFontSize;
    CCSize m_vFrameSize;
    float m_fCurLabelPixelWidth;
	float m_fCurMAXLabelPixelWidth;
	float m_fCurTotleLabelPixelWidth;
    int m_iCurTag;
    int m_iRow;
    //float m_fRowHeight;
    float m_fFontRealHeight;
};
