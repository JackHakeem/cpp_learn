#ifndef HLQS_Effect1_H_
#define HLQS_Effect1_H_
#include "BaseType.h"

class Effect1
{
public:
	Effect1();
	void showEffect(std::string path, std::string frameName, float px, float py, CCLayer* parent);
public:
	std::string _assetURL;
	float _px;
	float _py;
	CCSprite* sp;
	CCAnimation* animation;
};

#endif