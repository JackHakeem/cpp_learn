#include "ImageContain.h"

ImageContain::ImageContain()
{
	init();
}

bool ImageContain::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
    
    return true;
}

void ImageContain::clear()
{
	this->removeAllChildrenWithCleanup(true);
}