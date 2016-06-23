#ifndef _IMAGE_MANAGER_H_ 
#define _IMAGE_MANAGER_H_

#include "BaseType.h"
#include "utils/Singleton.h"

USING_NS_CC;

class ImageManager : public Singleton<ImageManager>
{
public:
	ImageManager();
	virtual ~ImageManager(){}

	static CCSprite * getRealSpriteFromImagePath(char * path);
	
public:
};

#endif