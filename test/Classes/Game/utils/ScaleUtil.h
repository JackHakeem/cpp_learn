#ifndef _SCALE_UTIL_H_
#define _SCALE_UTIL_H_

#include "cocos2d.h"
#include <cmath>
#include "utils/Singleton.h"
#include "GlobalScale.h"

USING_NS_CC;

#define STANDARD_WIDTH 960
#define STANDARD_HEIGHT 640
// Doyang 20121220 for 320x480 or 640x960
/*#define RESOLUTION_480X320 1
#define RESOLUTION_960X640 2

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define RESOLUTION_PIXELS RESOLUTION_480X320 //480X320
#else
#define RESOLUTION_PIXELS RESOLUTION_960X640 //480X320  960X640
#endif

#if (RESOLUTION_480X320 == RESOLUTION_PIXELS)
#define WIDTH 480 
#define HEIGHT 320 
#else
#define WIDTH 960 
#define HEIGHT 640 
#endif
*/
class ScaleUtil: public Singleton<ScaleUtil>
{
public:
	float _pixNum;

	ScaleUtil()
	{
//		if(CCDirector::sharedDirector()->getWinSize().width != 0)
//		{
//			_pixNum = CCDirector::sharedDirector()->getWinSizeInPixels().width / CCDirector::sharedDirector()->getWinSize().width;
//		}
//		else
//		{
//			_pixNum = 1.0f;
//		}
        
//		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//		float /*scaleFactor, */scaleFactorWidth, scaleFactorHeight;
//		CCSize winSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();
//        scaleFactorWidth = winSizePixels.width / winSize.width;
//		scaleFactorHeight = winSizePixels.height / winSize.height;
//        CCLog("pixel.width=%f,height=%f, scaleFactor width=%f,height=%f, content scale=%f", winSizePixels.width, winSizePixels.height, scaleFactorWidth, scaleFactorHeight, CCDirector::sharedDirector()->getContentScaleFactor());
//        _scaleFactoryOnAndroid = scaleFactorWidth;
//        if(scaleFactorWidth == scaleFactorHeight)
//        {
//            _scaleFactoryOnAndroid = scaleFactorWidth;
//        }
//        else 
//        {
//            _scaleFactoryOnAndroid = 0;
//        }
	}

	float pixNum()
	{
		return _pixNum;
	}

	enum NodeAlignment
	{
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER_TOP,
		CENTER_LEFT,
		CENTER_RIGHT,
		CENTER_BOTTOM,
		CENTER
	};




	static float convertNewPoint(float x)
	{
//		float newX = x / CCDirector::sharedDirector()->getContentScaleFactor();
		float newX = x / GlobalScale::Instance()->getScaleFromStandard();

		float scale = 1.0f;
		if(480 == GlobalScale::Instance()->getStandardWidth())
		{
			scale = 2.0f;
		}
		newX /= scale;
/*#if (RESOLUTION_480X320 == RESOLUTION_PIXELS)
		newX /= 2.0f;
#endif*/
		return newX;
	}
	static CCPoint convertNewPoint( CCPoint POINT_960_640, NodeAlignment alignment )
	{
		CCPoint truePoint;

/*#if (RESOLUTION_480X320 == RESOLUTION_PIXELS)
		POINT_960_640.x /= 2.0f;
		POINT_960_640.y /= 2.0f;
#endif*/
		
		float scale = 1.0f;
		if(480 == GlobalScale::Instance()->getStandardWidth())
		{
			scale = 2.0f;
		}
		POINT_960_640.x /= scale;
		POINT_960_640.y /= scale;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		
		float scaleFactor = 1;

#else
		float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

#endif
//		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float EXPAND_WIDTH = abs(CCDirector::sharedDirector()->getWinSize().width - GlobalScale::Instance()->getStandardWidth() / scaleFactor);
		float EXPAND_HEIGHT = abs(CCDirector::sharedDirector()->getWinSize().height - GlobalScale::Instance()->getStandardHeight() / scaleFactor);

		switch(alignment)
		{
		case CENTER_TOP:
			truePoint.x = POINT_960_640.x / scaleFactor + EXPAND_WIDTH / 2;
			truePoint.y = POINT_960_640.y / scaleFactor + EXPAND_HEIGHT;
			break;

		case CENTER_LEFT:
			truePoint.x = POINT_960_640.x / scaleFactor;
			truePoint.y = POINT_960_640.y / scaleFactor + EXPAND_HEIGHT / 2;
			break;

		case CENTER_RIGHT:
			truePoint.x = POINT_960_640.x / scaleFactor + EXPAND_WIDTH;
			truePoint.y = POINT_960_640.y / scaleFactor + EXPAND_HEIGHT / 2;
			break;

		case CENTER_BOTTOM:
			truePoint.x = POINT_960_640.x / scaleFactor + EXPAND_WIDTH / 2;
			truePoint.y = POINT_960_640.y / scaleFactor;
			break;

		case TOP_LEFT:
			truePoint.x = POINT_960_640.x / scaleFactor;
			truePoint.y = POINT_960_640.y / scaleFactor + EXPAND_HEIGHT;
			break;

		case TOP_RIGHT:
			truePoint.x = POINT_960_640.x / scaleFactor + EXPAND_WIDTH;
			truePoint.y = POINT_960_640.y / scaleFactor + EXPAND_HEIGHT;
			break;

		case BOTTOM_LEFT:
			truePoint.x = POINT_960_640.x / scaleFactor;
			truePoint.y = POINT_960_640.y / scaleFactor;
			break;

		case BOTTOM_RIGHT:
			truePoint.x = POINT_960_640.x / scaleFactor + EXPAND_WIDTH;
			truePoint.y = POINT_960_640.y / scaleFactor;
			break;

		default:
			truePoint.x = POINT_960_640.x / scaleFactor + EXPAND_WIDTH / 2;
			truePoint.y = POINT_960_640.y / scaleFactor + EXPAND_HEIGHT / 2;
			break;
		}
		return truePoint;
	}

    static float convertPointToPixels(float point)
    {
        float result = 0;
        
        
        return result;
    }
    
    float _scaleFactory;
    
    float _scaleFactoryOnAndroid;
    
	void init(int screenWidth, int screenHeight, int winWidth, int winHeight)
	{
		float /*scaleFactor, */scaleFactorWidth, scaleFactorHeight;
		/*_standardWidth = standardWidth;
		_standardHeight = standardHeight;
		_scaleFromStandard = STANDARD_WIDTH / _standardWidth;*/

		scaleFactorWidth = GlobalScale::Instance()->getStandardWidth() / winWidth;
		scaleFactorHeight = GlobalScale::Instance()->getStandardHeight() / winHeight;

		if(GlobalScale::Instance()->getStandardHeight() / scaleFactorWidth < winHeight)
		{
			_scaleFactory = scaleFactorWidth;
		}
		else
		{
			_scaleFactory = scaleFactorHeight;
		}
        
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        
        _scaleFactoryOnAndroid = _screenWidth / winWidth;
        CCLog("-----------------screen.width=%f,height=%f,win.width=%f,height=%f,_scaleFactoryOnAndroid=%f", screenWidth, screenHeight, winWidth, winHeight, _scaleFactoryOnAndroid);

	}
    
    float _screenWidth, _screenHeight;

    
    float getScaleFactoryOnAndroid()
	{
		return _scaleFactoryOnAndroid;
	}
    
    float getScaleFactory()
	{
		return _scaleFactory;
	}
};

#define POS(point, align) ScaleUtil::convertNewPoint(point, align)
#define POSX(x) ScaleUtil::convertNewPoint(x)
#define SCALE 1//(1 / ScaleUtil::getScaleFactory())

#endif
