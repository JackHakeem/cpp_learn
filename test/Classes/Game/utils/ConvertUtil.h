#ifndef _CONVERT_UTIL_H_
#define _CONVERT_UTIL_H_
#include "cocos2d.h"

USING_NS_CC;

class ConvertUtil
{

public:
	static CCPoint convertToScreenPos(CCNode *pNode, bool isPixels = false)
	{
		CCPoint convertResult = CCPointZero;
		while(pNode != NULL)
		{
			if(isPixels)
			{
				convertResult = ccpAdd(convertResult,
					pNode->boundingBoxInPixels().origin);
			}
			else
			{
				convertResult = ccpAdd(convertResult,
					pNode->boundingBox().origin);
			}
			pNode = pNode->getParent();
		}
		
		return convertResult;
	}
};
#endif