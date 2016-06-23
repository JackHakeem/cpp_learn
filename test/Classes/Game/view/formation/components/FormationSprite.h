#ifndef _FORMATION_SPRITE_H_
#define _FORMATION_SPRITE_H_
#include "SpriteNode.h"
#include "model/player/vo/PlayerInfoVo.h"

class FormationSprite : public SpriteNode
{
public:
	FormationSprite()
	{
		_isHighLight = false;
		_pInfo = 0;
		_pHighLightSprite = 0;
	}
	~FormationSprite()
	{
		if(_pHighLightSprite)
		{
			_pHighLightSprite->release();
		}
		//this->release();
	}

    PlayerInfoVo *_pInfo;

	static FormationSprite* spriteWithFile(const char *pszFileName);
	static FormationSprite* spriteWithSpriteFrameName(const char *frameName);
	void setIsHighLight(bool isHighLight);

private:
	bool _isHighLight;
	CCSprite *_pHighLightSprite;
	
};
#endif