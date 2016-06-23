#pragma once

#include "cocos2d.h"
#include "BaseType.h"

USING_NS_CC;

class LHMenuItemLabel : public cocos2d::CCMenuItemLabel
{
public:
    LHMenuItemLabel();
    virtual ~LHMenuItemLabel();

	bool initWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector , float fontSize , float strokeSize = 0 ,
		ccColor3B strokeColor = ccc3(0,0,0) , CCAction * pStrokeAction = 0 , bool bLine = false ,float lineSize = 0);
	CCRenderTexture * createStroke(CCLabelTTF* label ,   float size , ccColor3B color);

private:
	float  getTextWidth();

	CCLabelTTF * _pLabel;

public:
	CC_SYNTHESIZE(float , _lineSize , LineSize)
	CC_SYNTHESIZE(float , _fontSize , FontSize)
    CC_SYNTHESIZE(float , _strokeSize , StrokeSize)
	CC_SYNTHESIZE(ccColor3B , _strokeColor , StrokeColor)
};
