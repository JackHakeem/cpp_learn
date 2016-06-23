#pragma once

#include "cocos2d.h"
#include "BaseType.h"

USING_NS_CC;

class LHLabelTTF : public cocos2d::CCLabelTTF
{
public:
    LHLabelTTF();
    virtual ~LHLabelTTF();

	virtual void setString(const char *str);
	bool initWithString(char * str , const CCSize & size , CCTextAlignment aliment ,  const char * fontName , 
		float fontSize , float strokeSize = 0 , ccColor3B strokecolor = ccc3(0,0,0), CCAction * pStrokeAction = 0 , bool bLine = false, float lineSizee = 0);
	CCRenderTexture * createStroke(CCLabelTTF* label ,   float size , ccColor3B color);

private:
	float  getTextWidth();
	char * _str;

public:
	CC_SYNTHESIZE(float , _lineSize , LineSize)
	CC_SYNTHESIZE(float , _fontSize , FontSize)
    CC_SYNTHESIZE(float , _strokeSize , StrokeSize)
	CC_SYNTHESIZE(ccColor3B , _strokeColor , StrokeColor)
};
