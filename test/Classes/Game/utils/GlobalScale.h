#ifndef _GLOBAL_SCALE_H_
#define _GLOBAL_SCALE_H_

#include "cocos2d.h"
#include <cmath>
#include "utils/Singleton.h"

USING_NS_CC;

class GlobalScale: public Singleton<GlobalScale>
{
public:
	float _pixNum;

	GlobalScale()
	{
		_standardWidth = 960;
		_standardHeight = 640;
		_scaleFromStandard = 1;
	}

	int _standardWidth, _standardHeight;
    	float _scaleFromStandard;


	void setStandard(int standardWidth, int standardHeight, float scale)
	{
		_standardWidth = standardWidth;
		_standardHeight = standardHeight;
		_scaleFromStandard =  scale;
	}

	float getScaleFromStandard()
	{
		return _scaleFromStandard;
	}

	int getStandardWidth()
	{
		return _standardWidth;
	}

	int getStandardHeight()
	{
		return _standardHeight;
	}
};

#endif
