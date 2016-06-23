#include "FormationLoader.h"

FormationLoader::FormationLoader()
{
	_sp = NULL;
	_x = 0;
	_y = 0;
	_scaleX = 0;
	_scaleY = 0;
}

void FormationLoader::load(std::string& url)
{
	_url = url;
	strategyA(url);
}

void FormationLoader::load( int id )
{
	char path[128] = {0};
	sprintf(path, "assets/ui/fight/formation/%d.png", id);
	if(!_sp)
	{
		//Begin Kenfly 20121107 : modify, load async
		//typedef struct  
		//{
		//	std::string plistName;
		//	std::string framesName;
		//} FramesInfo;
		//FramesInfo* pData = new FramesInfo();
		//pData->plistName = plistStr;
		//pData->framesName = pngStr;

		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFileAsync(plistStr, this, callfuncOD_selector(FormationLoader::loadCallback), (void*)pData);

		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(path);
		if (pTexture)
		{
			_sp = CCSprite::spriteWithTexture(pTexture);
			if (_sp && _sp->getParent() == NULL)
			{
				_sp->setScale(0.9);
				addChild(_sp);
			}
		}
		CCTextureCache::sharedTextureCache()->removeTextureForKey(path);
		//End Kenfly 20121107
	}
}

void FormationLoader::strategyA(std::string& url)
{
	if(!_sp)
	{
		_sp = CCSprite::spriteWithFile(url.c_str());
      //  _sp->setOpacity(200);
        _sp->setScale(0.9);
		if(_sp && _sp->getParent() == NULL)
			addChild(_sp);
	}
}

void FormationLoader::strategyB(std::string& url)
{

}

void FormationLoader::dispose()
{
	if(_sp && _sp->getParent() == this)
		this->removeChild(_sp, true);

	_sp = NULL;
}

//Begin Kenfly 20121107 : load async
void FormationLoader::loadCallback(CCObject* object, void* pData)
{
	do 
	{
		CC_BREAK_IF(NULL == pData);
		typedef struct  
		{
			std::string plistName;
			std::string framesName;
		} FramesInfo;

		FramesInfo* data = (FramesInfo*)pData;

		_sp = CCSprite::spriteWithSpriteFrameName(data->framesName.c_str());
		if(_sp && _sp->getParent() == NULL)
		{
			_sp->setScale(0.9);
			addChild(_sp);
		}
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(data->plistName.c_str());
		CC_SAFE_DELETE(data);
	} while (0);
}
//End Kenfly 20121107