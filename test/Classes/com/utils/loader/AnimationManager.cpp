
#include "AnimationManager.h"
#include "BaseType.h"
#include "utils/loader/KKAnimationFactory.h"

static AnimationManager * g_pAnimationManager = 0;

AnimationManager::AnimationManager()
{
    
}

AnimationManager::~AnimationManager()
{
    SAFE_DELETE(g_pAnimationManager);
}

AnimationManager * AnimationManager::getInstance()
{
    if(!g_pAnimationManager)
    {
        g_pAnimationManager = new AnimationManager();
    }
    return g_pAnimationManager;
}


CCAnimation * AnimationManager::getAction(int n_ID)
{
    switch (n_ID)
    {
        case 1001:
            //            ca1001->setTag(1001);

            //return g_pKKAnimationFactory->registAni("role/warrior/stand-7.plist", "role/warrior/stand-7-%d.png", 10, 0.1f);
			return g_pKKAnimationFactory->registModelAnimation("assets/res/1/stand1-7.plist", "1/stand-7-%d.png", 10, 0.2f);
            break;
        case 1002:
            //            ca1002->setTag(1002);

            //return g_pKKAnimationFactory->registAni("role/warrior/attack-7.plist", "role/warrior/attack-7-%d.png", 9, 0.1f);
			return g_pKKAnimationFactory->registModelAnimation("assets/res/1/model-1.plist", "1/attack-7-%d.png", 10, 0.2f);
            break;
		case 1003:
			return g_pKKAnimationFactory->registModelAnimation("assets/res/1/model-1.plist", "1/hit-7-%d.png", 10, 0.2f);
			break;

		case 2001:
            //return g_pKKAnimationFactory->registAni("role/npc/fushihun-stand-1.plist", "role/npc/fushihun-stand-1.png", 8, 0.1f);
			return g_pKKAnimationFactory->registModelAnimation("assets/res/202/model-202.plist", "202/stand-1-%d.png", 10, 0.2f);
            break;

		case 2002:
			//return g_pKKAnimationFactory->registAni("role/npc/fushihun-stand-1.plist", "role/npc/fushihun-stand-1.png", 8, 0.1f);
			return g_pKKAnimationFactory->registModelAnimation("assets/res/202/model-202.plist", "202/attack-1-%d.png", 10, 0.2f);
			break;

		case 2003:
			//return g_pKKAnimationFactory->registAni("role/npc/fushihun-stand-1.plist", "role/npc/fushihun-stand-1.png", 8, 0.1f);
			return g_pKKAnimationFactory->registModelAnimation("assets/res/202/model-202.plist", "202/hit-7-%d.png", 10, 0.2f);
			break;

        default:
			//            ca1001->setTag(1001);
			return g_pKKAnimationFactory->registModelAnimation("assets/res/1/model-1.plist", "1/stand-7-%d.png", 10, 0.2f);
            break;
    }
}

string AnimationManager::getPicture(int n_ID)
{
    switch (n_ID)
    {
        case 1001:
            return ("role/npc/fushihun-stand-1.png");
            break;
        case 1002:
            return ("role/warrior/attack-7.png");
            break;
        default:
            return ("role/warrior/attack-7.png");
            break;
    }
}


CCAnimation *anim1 = 0;//CCAnimate::actionWithAnimation(AnimationManager::getAction(1001));
CCAnimation *anim2 = 0;//CCAnimate::actionWithAnimation(AnimationManager::getAction(1002));
