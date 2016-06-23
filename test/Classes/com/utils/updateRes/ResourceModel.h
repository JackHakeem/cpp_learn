#ifndef DREAM_MODEL_RESOURCE_MODEL_H__
#define DREAM_MODEL_RESOURCE_MODEL_H__

#include <string>

#include "CCMutableArray.h"

namespace cocos2d
{
	class CCSpriteFrame;
	class CCAnimation;
}

struct AnimationResource
{
	std::string file;
	int nframes;
};

bool loadPvr(const AnimationResource &resource,
    cocos2d::CCMutableArray<cocos2d::CCSpriteFrame *> *frames);

cocos2d::CCAnimation *loadAnimation(const AnimationResource &resource, float delay);
cocos2d::CCAnimation *loadAnimation(const char *file, int nframes, float delay);

std::string pathForConfigure(const char *name);
std::string pathForAvatar(const char *name);
std::string pathForEffect(const char *name);
std::string pathForIcon(const char *name);
std::string pathForMonster(const char *name);
std::string pathForNPC(const char *name);
std::string pathForScene(const char *name);
std::string pathForSound(const char *name);
std::string pathForUI(const char *name);

#endif