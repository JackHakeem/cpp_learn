#ifndef DREAM_WIDGET_STROKE_LABEL_H__
#define DREAM_WIDGET_STROKE_LABEL_H__

#include "CCNode.h"
#include <string>

#include "CCPlatformConfig.h"
#include "CCLabelTTF.h"
#include "cocos2d.h"

USING_NS_CC;

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
class CCStrokeLabelManager;
#endif

class CCStrokeLabel : public CCLabelTTF
{
public:
	CCStrokeLabel();
	~CCStrokeLabel();

	/** creates a CCLabelTTF from a fontname, alignment, dimension and font size */
	static CCStrokeLabel * labelWithString(const char *label, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
	/** creates a CCLabelTTF from a fontname and font size */
	static CCStrokeLabel * labelWithString(const char *label, const char *fontName, float fontSize);

	virtual void setString(const char *label);

	void setStroke(float size,ccColor3B color);

private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    friend class CCStrokeLabelManager;
    void didEnterBackground();
    void didEnterForeground();
#endif
	void reinit();
	float m_strokeSize;
	ccColor3B m_strokeColor;
	CCRenderTexture* m_renderTexture;
};

#endif
