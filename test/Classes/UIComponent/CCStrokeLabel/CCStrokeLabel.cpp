#include "CCStrokeLabel.h"

#include "cocos2d.h"

using namespace cocos2d;

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <tr1/unordered_set>
#include <tr1/functional>

#include "events/GameDispatcher.h"
using namespace std::tr1::placeholders;

class CCStrokeLabelManager : public CCNode
{
public:
	enum
	{
		kCCEnterBackground = 90000,
		kCCEnterForeground
	};
    void registerStrokeLabel(CCStrokeLabel *obj);
    void unregisterStrokeLabel(CCStrokeLabel *obj);

    static CCStrokeLabelManager &sharedManager();
private:
    CCStrokeLabelManager();
    std::tr1::unordered_set<CCStrokeLabel *> m_objs;
    void didEnterBackground(CCNode* pSender, void* data);
    void didEnterForeground(CCNode* pSender, void* data);
};

CCStrokeLabelManager &CCStrokeLabelManager::sharedManager()
{
    static CCStrokeLabelManager theManager;
    return theManager;
}

CCStrokeLabelManager::CCStrokeLabelManager()
{
	GameDispatcher::getInstance()->addEventListener(
		kCCEnterForeground,
		this,
		callfuncND_selector(CCStrokeLabelManager::didEnterForeground));
	GameDispatcher::getInstance()->addEventListener(
		kCCEnterBackground,
		this,
		callfuncND_selector(CCStrokeLabelManager::didEnterBackground));
}

void CCStrokeLabelManager::registerStrokeLabel(CCStrokeLabel *obj)
{
    m_objs.insert(obj);
}

void CCStrokeLabelManager::unregisterStrokeLabel(CCStrokeLabel *obj)
{
    m_objs.erase(obj);
}

void CCStrokeLabelManager::didEnterBackground(CCNode* pSender, void* data)
{
    std::tr1::unordered_set<CCStrokeLabel *>::iterator iter = m_objs.begin();
    for(; iter != m_objs.end(); ++iter)
    {
        (*iter)->didEnterBackground();
    }
}

void CCStrokeLabelManager::didEnterForeground(CCNode* pSender, void* data)
{
    std::tr1::unordered_set<CCStrokeLabel *>::iterator iter = m_objs.begin();
    for(; iter != m_objs.end(); ++iter)
    {
        (*iter)->didEnterForeground();
    }

}

void CCStrokeLabel::didEnterBackground()
{
	if (m_renderTexture != NULL)
	{
		removeChild(m_renderTexture,true);
	}
	m_renderTexture = NULL;
}

void CCStrokeLabel::didEnterForeground()
{
	if (m_renderTexture != NULL)
	{
		removeChild(m_renderTexture,true);
	}
	m_renderTexture = NULL;
    init();
}

#endif

CCStrokeLabel::CCStrokeLabel() : m_renderTexture(NULL), m_strokeSize(1.0)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CCStrokeLabelManager::sharedManager().registerStrokeLabel(this);
#endif
    //reinit();
}

CCStrokeLabel::~CCStrokeLabel()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CCStrokeLabelManager::sharedManager().unregisterStrokeLabel(this);
#endif
}

/** creates a CCLabelTTF from a fontname, alignment, dimension and font size */
CCStrokeLabel * CCStrokeLabel::labelWithString(const char *label, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
	CCStrokeLabel *pRet = new CCStrokeLabel();
	if(pRet && pRet->initWithString(label, dimensions, alignment, fontName, fontSize))
	{
		//pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
/** creates a CCLabelTTF from a fontname and font size */
CCStrokeLabel * CCStrokeLabel::labelWithString(const char *label, const char *fontName, float fontSize)
{
	CCStrokeLabel *pRet = new CCStrokeLabel();
	if(pRet && pRet->initWithString(label, fontName, fontSize))
	{
		//pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}


void CCStrokeLabel::setString(const char *label)
{
	CCLabelTTF::setString(label);

	reinit();
	//setStroke(m_strokeSize, m_strokeColor);
	//setStroke(1,ccc3(4,21,2));
}

void CCStrokeLabel::setStroke(float size, ccColor3B color)
{
	float m_lineWidth =1.0;

	m_strokeSize = size;
	m_strokeColor = color;

	ccColor3B m_lineColor = color;

	if (m_renderTexture != NULL)
	{
		removeChild(m_renderTexture,true);
	}



	CCSize labelSize = getTexture()->getContentSize();

	CCPoint labelAnchorPoint = getAnchorPoint();

	int w = labelSize.width+m_lineWidth*2;

	int h = labelSize.height+m_lineWidth*2;

	CCRenderTexture* renderRexture = CCRenderTexture::renderTextureWithWidthAndHeight(w,h);



	CCPoint originalPos = getPosition();

	ccColor3B originalColor = getColor();

	setColor(m_lineColor);

	ccBlendFunc originalBlend =getBlendFunc();
	ccBlendFunc blendFunc3 = { GL_SRC_ALPHA, GL_ONE };
	setBlendFunc(blendFunc3);



	float moveX = labelSize.width* (labelAnchorPoint.x-0.5);

	float moveY = labelSize.height* (labelAnchorPoint.y-0.5);



	float X = labelSize.width*0.5 + m_lineWidth + moveX;

	float Y = labelSize.height*0.5+ m_lineWidth + moveY;



	CCPoint position = CCPointMake(X,Y);



	renderRexture->begin();

	for (int i=0; i<360; i+=30)

	{

		setPosition(CCPointMake(position.x + sin(CC_DEGREES_TO_RADIANS(i))*m_lineWidth,position.y+cos(CC_DEGREES_TO_RADIANS(i))*m_lineWidth));

		visit();

	}



	renderRexture->end();

	setAnchorPoint(labelAnchorPoint);

	setPosition(originalPos);

	setColor(originalColor);

	setBlendFunc(originalBlend);



	CCPoint strokePosition = CCPointMake(labelSize.width/2,labelSize.height/2);

	renderRexture->setPosition(strokePosition);

	addChild(renderRexture,-1);

	m_renderTexture = renderRexture;
}

void CCStrokeLabel::reinit()
{
	if(NULL != m_renderTexture)
	{
		setStroke(m_strokeSize, m_strokeColor);
	}
}
