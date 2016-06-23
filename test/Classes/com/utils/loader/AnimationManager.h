//
//  Animation.h
//  HLQS_IPAD
//
//  Created by hui long on 12-3-2.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_IPAD_Animation_h
#define HLQS_IPAD_Animation_h
#include "cocos2d.h"
using namespace cocos2d;

class AnimationManager
{
private:
    AnimationManager();
    ~AnimationManager();
public:
    AnimationManager * getInstance();
    static CCAnimation * getAction(int n_ID);
    static string getPicture(int n_ID);
};

extern CCAnimation *anim1;
extern CCAnimation *anim2;

#endif