
#include "BattleLayer.h"
#include "model/battle/BattleProxy.h"
#include "utils/loader/AnimationManager.h"
#include "view/scene/components/BattlePlay.h"

static BattleLayer * m_pInstance;
CCSprite * sp[18];

BattleLayer * BattleLayer::getInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = BattleLayer::node();
        m_pInstance->setIsTouchEnabled(false);

    }

    return m_pInstance;
}


BattleLayer::BattleLayer()
{
    BattleLayer::generateFormationPos();

}

BattleLayer::~BattleLayer()
{
}

bool BattleLayer::init()
{
    if (!CCLayer::init())
	{
		return false;
	}
    
    CCSprite* sp1 = BattlePlay::getInstance()->getBattleSprite();
    this->addChild(sp1);
    
    for(int i = 0; i < 18; ++i)
    {
        sp[i] = NULL;
    }
    
	return true;
}

void BattleLayer::generateFormationPos()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center;
    center.x = screenSize.width/2;
    center.y = screenSize.height/2;
    float length = sqrt(screenSize.width*screenSize.width + screenSize.height * screenSize.height);
    float rateSin = ((float)screenSize.height)/length;
    float rateCos = ((float)screenSize.width)/length;

    formationPos[1].x = center.x + ((float)center.x)/5;
    formationPos[1].y = center.y + ((float)center.y)/5;
    formationPos[4].x = center.x + 2 * ((float)center.x)/5;
    formationPos[4].y = center.y + 2 * ((float)center.y)/5;
    formationPos[7].x = center.x + 3 * ((float)center.x)/5;
    formationPos[7].y = center.y + 3 * ((float)center.y)/5;
    
    formationPos[2].x = formationPos[1].x - rateSin * length/10;
    formationPos[2].y = formationPos[1].y + rateCos * length/10;
    formationPos[5].x = formationPos[2].x + ((float)center.x)/5;
    formationPos[5].y = formationPos[2].y + ((float)center.y)/5;
    formationPos[8].x = formationPos[5].x + ((float)center.x)/5;
    formationPos[8].y = formationPos[5].y + ((float)center.y)/5;
    
    formationPos[0].x = formationPos[1].x + rateSin * length/10;
    formationPos[0].y = formationPos[1].y - rateCos * length/10;
    formationPos[3].x = formationPos[0].x + ((float)center.x)/5;
    formationPos[3].y = formationPos[0].y + ((float)center.y)/5;
    formationPos[6].x = formationPos[3].x + ((float)center.x)/5;
    formationPos[6].y = formationPos[3].y + ((float)center.y)/5;

    formationPos[10].x = screenSize.width - formationPos[1].x;
    formationPos[10].y = screenSize.height - formationPos[1].y;
    formationPos[13].x = screenSize.width - formationPos[4].x;
    formationPos[13].y = screenSize.height - formationPos[4].y;
    formationPos[16].x = screenSize.width - formationPos[7].x;
    formationPos[16].y = screenSize.height - formationPos[7].y;
    
    formationPos[9].x = screenSize.width - formationPos[2].x;
    formationPos[9].y = screenSize.height - formationPos[2].y;
    formationPos[12].x = screenSize.width - formationPos[5].x;
    formationPos[12].y = screenSize.height - formationPos[5].y;
    formationPos[15].x = screenSize.width - formationPos[8].x;
    formationPos[15].y = screenSize.height - formationPos[8].y;
    
    formationPos[11].x = screenSize.width - formationPos[0].x;
    formationPos[11].y = screenSize.height - formationPos[0].y;
    formationPos[14].x = screenSize.width - formationPos[3].x;
    formationPos[14].y = screenSize.height - formationPos[3].y;
    formationPos[17].x = screenSize.width - formationPos[6].x;
    formationPos[17].y = screenSize.height - formationPos[6].y;
}



void BattleLayer::playStartAnimation()
{
    BattlePlay::getInstance()->m_battleLayer = BattleLayer::getInstance();
    BattlePlay::getInstance()->playBattleStart();
}

void BattleLayer::loadBgAnimation()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite * zhenfa1 = CCSprite::spriteWithFile("scene/battle/zhenfa.png");
    BattleLayer::getInstance()->addChild(zhenfa1,-95);
    zhenfa1->setPosition(ccp(formationPos[4].x, screenSize.height - formationPos[4].y));
    
    CCSprite * zhenfa2 = CCSprite::spriteWithFile("scene/battle/zhenfa.png");
    BattleLayer::getInstance()->addChild(zhenfa2,-95);
    zhenfa2->setPosition(ccp(formationPos[13].x, screenSize.height - formationPos[13].y));

}

void BattleLayer::startBattleAnimation()
{
    m_AnimationList.clear();
    m_AnimationParaList.clear();
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    BattleProxy * bp = BattleProxy::getInstance();
    CCLOG("Fighting scene ID %d",bp->a_BattleId_132);
    CCLOG("huihe %d",bp->b_round+1);   
    for(int i = 0; i<bp->SCMD132Node1Num; i++)
    {
        BattleProxy::SCMD132Node1 n1= bp->c_Actions.front();

        AnimationPara a;
        a.pos = n1.a_attackId-1;
        a.skill = n1.c_skill;
        //AnimationList.push_back(anim1);
        //m_AnimationList.push_back(anim1);
        m_AnimationList.push_back(anim2);
        m_AnimationParaList.push_back(a);
        CCLog("-------level 1 pos:%d, skill:%d, hp:%d",a.pos,a.skill, a.hp);
        for(int j = 0; j<bp->SCMD132Node2Num; j++)
        {
            BattleProxy::SCMD132Node2 n2 = n1.g_hiteds.front();

            
            AnimationPara b;
            b.pos = n2.a_hitedId-1;
            b.skill = 1002;
            //m_AnimationList.push_back(anim1);

            m_AnimationList.push_back(anim2);
            m_AnimationParaList.push_back(b);
            CCLog("-------level 2 pos:%d, skill: %d, hp: %d",b.pos,b.skill, b.hp);
            for(int k = 0; k<bp->SCMD132Node3Num; k++)

            {
               
                BattleProxy::SCMD132Node3 n3 = n2.h_hiteds.front();

                AnimationPara c;
                c.pos = n3.a_hitedId-1;
                c.skill = 1002;
                //m_AnimationList.push_back(anim1);

                m_AnimationList.push_back(anim2);
                m_AnimationParaList.push_back(c);
                CCLog("-------level 3 pos:%d, skill: %d, hp: %d",c.pos,c.skill, c.hp);
                n2.h_hiteds.pop_front();
            }
            
            n1.g_hiteds.pop_front();
        }
        
        bp->c_Actions.pop_front();
    }

    CCLog("Push data to list animation size:%d, para size:%d", m_AnimationList.size(), m_AnimationParaList.size());
    // buff
    for(int i = 0; i<bp->SCMD132Node4Num; i++)
    {
        for(int j = 0; j<bp->SCMD132Node5Num;j++)
        {
            
        }
    }
    
    CCLog("---------Set check battle action true");
    BattlePlay::getInstance()->setCheckBattleAction(true);
    
}
void BattleLayer::endBattleAnimation()
{

    BattleLayer::getInstance()->removeAllChildrenWithCleanup(true);
}

void BattleLayer::loadSpriteAnimation()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    BattleProxy * bp = BattleProxy::getInstance();

    for (int i = 0; i < bp->getInstance()->d_SCMD131NodeNum; i++)
	{
        int pos = bp->d_SCMD131Node.front().b_station;
        sp[pos-1] = CCSprite::spriteWithFile(AnimationManager::getPicture(1001).c_str());
        CCAction * ca = CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(AnimationManager::getAction(1001)));
        ca->setTag(1001);
        sp[pos-1] ->runAction(ca);
        
        BattleLayer::getInstance()->addChild(sp[pos-1],-94,pos);        
        bp->d_SCMD131Node.pop_front();
		sp[pos-1]->setPosition(ccp(formationPos[pos-1].x,screenSize.height - formationPos[pos-1].y)) ;
	}


    for (int j = 9; j < 18; j++)
	{
        sp[j] = CCSprite::spriteWithFile(AnimationManager::getPicture(1003).c_str());
        CCAction * ca = CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(AnimationManager::getAction(1003)));
        ca->setTag(1003);
        sp[j] ->runAction(ca);
        
        BattleLayer::getInstance()->addChild(sp[j],-94);        
       	sp[j]->setPosition(ccp(formationPos[j].x,screenSize.height - formationPos[j].y)) ;
	}
    


    CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
                                                                       "CloseNormal.png",
                                                                       "CloseSelected.png",
                                                                       BattleLayer::getInstance(),
                                                                       menu_selector(BattleLayer::menuCloseCallback));
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
	// create menu, it's an autorelease object

	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	BattleLayer::getInstance()->addChild(pMenu, 1);
}

void BattleLayer::menuCloseCallback(CCObject* pSender)
{
    //	CCDirector::sharedDirector()->end();

    endBattleAnimation();
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //	exit(0);
    //#endif

}

std::list<CCAnimation *>* BattleLayer::getAnimationList()
{
    return &m_AnimationList;
}

std::list<AnimationPara>* BattleLayer::getAnimationParaList()
{
    return &m_AnimationParaList;
}