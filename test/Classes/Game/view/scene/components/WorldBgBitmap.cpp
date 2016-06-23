#include "WorldBgBitmap.h"

WorldBgBitmap::WorldBgBitmap()
{
	_mapSprite = NULL;
}

void WorldBgBitmap::load(CCLayer* layer, CCPoint pos)
{
	_mapSprite = CCSprite::spriteWithFile(_rootPath.c_str());
	if(_mapSprite && _mapSprite->getParent() == NULL)
		addChild(_mapSprite);
}

void WorldBgBitmap::dispose()
{
	BgBitmap::dispose();

	if(_mapSprite && _mapSprite->getParent() == this)
	{
		removeChild(_mapSprite, true);
	}
	CCTextureCache::sharedTextureCache()->removeTextureForKey(_rootPath.c_str());
}