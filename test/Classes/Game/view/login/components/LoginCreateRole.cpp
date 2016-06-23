#include "LoginCreateRole.h"
#include "utils/ScaleUtil.h"
#include "BaseType.h"
#include "LoginView.h"
#include "utils/ValuesUtil.h"
#include "socket/network/GateServerSocket.h"
#include "LoginManage.h"
#include "manager/NameManager.h"
#include "LoginTxt.h"
#include "manager/sound/SoundManager.h"
#include "TextFieldTTF.h"
#include "utils/Timer.h"

LoginCreateRole::LoginCreateRole()
{
	//_pHightLight = 0;
	_nSelectModel = 1;
	_curSelectSex = 2;
}

bool LoginCreateRole::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_create_role.plist");

	loadItems();
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_create_role.plist");

	return true;
}

std::string LoginCreateRole::initName()
{
	srand(Timer::millisecondNow());
	unsigned int tag = 5 - (rand()%9)%6;
	unsigned int roleId = ( 1 + 4*(tag%3)) + tag/3;
	
	if (roleId%2 == 0)
	{
		_curSelectSex = 2;
	}
	else
	{
		_curSelectSex = 1;
	}

	// switch
	if (roleId == 5){roleId = 9;}
	else if (roleId == 9){roleId = 5;}
	else if (roleId == 10){roleId = 6;}
	else if (roleId == 6){roleId = 10;}

	g_pLoginManage->setRoleID(roleId);

	CCNode * pGridSprite = (CCNode *)this->getChildByTag(TAG_SPRITE_MODEL+tag);
	if (pGridSprite)
	{
		CCPoint spritePoint = getScreenPos(pGridSprite);
		if (this->getChildByTag(TAG_SPRITE_HIGHLIGHT))
		{
			this->getChildByTag(TAG_SPRITE_HIGHLIGHT)->setIsVisible(true);
			this->getChildByTag(TAG_SPRITE_HIGHLIGHT)->setPosition(spritePoint);
		}
	}

	return Namemanager::Instance()->randomName(_curSelectSex);
}

void LoginCreateRole::loadItems()
{
	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	// Hight light
	CCSprite * pHightLight = new CCSprite();
	if (pHightLight)
	{
		if (pHightLight->initWithSpriteFrameName("upskill/select.png"))
		{
            pHightLight->setTag(TAG_SPRITE_HIGHLIGHT);
            pHightLight->setIsVisible(false);
			this->addChild(pHightLight,1);
		}
		pHightLight->release();
	}

	// Add frame background.
	CCSprite *pCreateRoleBackgroundSprite = new CCSprite();
	if( pCreateRoleBackgroundSprite)
	{
		if (pCreateRoleBackgroundSprite->initWithSpriteFrameName( "login/bg_create_role.png" ))
		{
			pCreateRoleBackgroundSprite->setAnchorPoint(CCPointZero);
			pCreateRoleBackgroundSprite->setPosition(POS(ccp(92, 85), ScaleUtil::CENTER));
			pCreateRoleBackgroundSprite->setOpacity(225);
            pCreateRoleBackgroundSprite->setTag(TAG_Login_Creat_RoleBg);
			this->addChild(pCreateRoleBackgroundSprite);
		}
		pCreateRoleBackgroundSprite->release();
	}

	// Add career name
	for (int i = 0;i<3;i++)
	{
		std::string szName("");
		switch (i)
		{
		case 0:
			szName = "CAR1";
			break;
		case 1:
			szName = "CAR2";
			break;
		case 2:
			szName = "CAR32";
			break;
		}
		
		CCLabelTTF * pCareerLab = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString(szName).c_str(),
			CCSizeMake(POSX(100),POSX(30)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(28));
		pCareerLab->setPosition(POS(ccp(285+(i%3)*200, 430), ScaleUtil::CENTER));
		pCareerLab->setAnchorPoint(ccp(0.5,0.5));
		this->addChild(pCareerLab);

		switch (i)
		{
		case 0:
			pCareerLab->setColor(ccc3(255,200,0));			
			break;
		case 1:
			pCareerLab->setColor(ccc3(12,233,100));
			break;
		case 2:
			pCareerLab->setColor(ccc3(253,1,137));
			break;
		}
	}

	// Add sex icon
	CCSprite * pFemaleSexSprite = new CCSprite;
	if (pFemaleSexSprite)
	{
		if (pFemaleSexSprite->initWithSpriteFrameName("friend/1.png"))
		{
			//Doyang 20120822
			pFemaleSexSprite->setPosition(POS(ccp(165, 260), ScaleUtil::CENTER));
			pFemaleSexSprite->setAnchorPoint(ccp(0.5,0.5));
            pFemaleSexSprite->setTag(TAG_Login_Creat_Friend1);
			this->addChild(pFemaleSexSprite);
		}
		pFemaleSexSprite->release();
	}

	CCSprite * pMaleSexSprite = new CCSprite;
	if (pMaleSexSprite)
	{
		if (pMaleSexSprite->initWithSpriteFrameName("friend/2.png"))
		{
			//Doyang 20120822
			pMaleSexSprite->setPosition(POS(ccp(165, 370), ScaleUtil::CENTER));
			pMaleSexSprite->setAnchorPoint(ccp(0.5,0.5));
            pMaleSexSprite->setTag(TAG_Login_Creat_Friend2);
			this->addChild(pMaleSexSprite);
		}
		pMaleSexSprite->release();
	}

	// Add grid and role head icon
	for (int i = 0;i<6;i++)
	{
		CCSprite * pGridSprite = new CCSprite();
		pGridSprite->initWithSpriteFrameName("pack/lock.png");
		//Doyang 20120822
		pGridSprite->setPosition(POS(ccp(285+(i%3)*200,/*435*/360-(i/3)*110), ScaleUtil::CENTER));
		pGridSprite->setAnchorPoint(ccp(0.5,0.5));
		this->addChild(pGridSprite,0,TAG_SPRITE_MODEL+i);

		int index = (int)std::pow(2.0f,i%3) + ((int)(i/3))*5;
		char path[64];
		sprintf(path,"assets/icon/head/%d.png",index);
		CCSprite* p1 = CCSprite::spriteWithFile(path);
		CCSprite* p2 = CCSprite::spriteWithFile(path);
		CCMenuItemSprite * pMenuHeadItem = CCMenuItemImage::itemFromNormalSprite(
			p1,
			p2,
			this,menu_selector(LoginCreateRole::onSelectModel));
		//CCSprite * pHeadSprite = CCSprite::spriteWithFile(path);
		CCSize size = pGridSprite->getContentSize();
		CCPoint pos = ccp(POSX(size.width/2),POSX(size.height/2));
		//pHeadSprite->setPosition(pos);
		CCMenu * pMenuHead = CCMenu::menuWithItems(pMenuHeadItem,0);

		pMenuHead->setPosition(ccp(size.width/2,size.height/2));
		pMenuHeadItem->setTag(i);
		//pMenuHeadItem->setPosition(pos);
		pGridSprite->addChild(pMenuHead,0,0);

		pGridSprite->release();
		//pMenuHeadItem->setScale((float)(size.width-6)/pMenuHeadItem->getContentSize().width);
	}

	// Add name input
	CCLabelTTF* pRoleNameLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG019").c_str(),
		CCSizeMake(POSX(160), POSX(30)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pRoleNameLabel->setColor(ccc3(255, 215, 10));
	pRoleNameLabel->setAnchorPoint(CCPointZero);
	pRoleNameLabel->setIsRelativeAnchorPoint(true);
	pRoleNameLabel->setPosition( POS(ccp(194, 475), ScaleUtil::CENTER) );
	this->addChild(pRoleNameLabel);
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_input.plist");

	CCSprite *pRoleNameBackgroundSprite = new CCSprite();
	if(pRoleNameBackgroundSprite)
	{
		if (pRoleNameBackgroundSprite->initWithSpriteFrameName("login/login_input.png"))
		{

			pRoleNameBackgroundSprite->setAnchorPoint(CCPointZero);
			pRoleNameBackgroundSprite->setPosition(POS(ccp(334, 469), ScaleUtil::CENTER));
			pRoleNameBackgroundSprite->setScaleX(0.8);
			pRoleNameBackgroundSprite->setTag(TAG_SPRITE_INPUT);
			this->addChild(pRoleNameBackgroundSprite);
		}		
		pRoleNameBackgroundSprite->release();
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_input.plist");
	
	TextFieldTTF * pTextField = new TextFieldTTF();
	pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
	pTextField->setString(initName().c_str());
   
//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
	//pTextField->setUp(this,POSX(100));
	this->addChild(pTextField,Z_SPRITE_INPUT);
	pTextField->setPosition(POS(ccp(536+110, 490), ScaleUtil::CENTER));
    pTextField->setEmojiRefuse(true);
	//pTextField->m_pUpMoveNode = this;kevink

	pTextField->detachWithIME();
	
	/*
	CCTextFieldTTF *pRoleNameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
		CCSizeMake(POSX(380), POSX(35)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	if(pRoleNameTextField)
	{
		pRoleNameTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
		pRoleNameTextField->setAnchorPoint(CCPointZero);
		pRoleNameTextField->setPosition(POS(ccp(336, 191), ScaleUtil::CENTER));
		pRoleNameTextField->attachWithIME();
		pRoleNameTextField->setString(initName().c_str());
		pRoleNameTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		this->addChild(pRoleNameTextField);
	}
	*/

	// Add random name generator button.
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("login/btn_random_name.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("login/btn_random_name.png");
	if(pNormalSprite && pPressedSprite)
	{
		CCMenuItemSprite *pNameGeneratorMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(LoginCreateRole::onNameGeneratorMenuClick));
		pNameGeneratorMenuItem->setAnchorPoint(CCPointZero);
		pNameGeneratorMenuItem->setScale(2.0f);
		pNameGeneratorMenuItem->setPosition( POS(ccp(675, 458), ScaleUtil::CENTER) );
		CCMenu* pNameGeneratorMenu = CCMenu::menuWithItems(pNameGeneratorMenuItem, NULL);
		CCSize menuSize = pNameGeneratorMenu->getContentSize();
		pNameGeneratorMenu->setContentSize(CCSizeMake(menuSize.width*2,menuSize.height*2));
		pNameGeneratorMenu->setPosition( CCPointZero );
		pNameGeneratorMenu->setTouchLayer(-2000);
		this->addChild(pNameGeneratorMenu,Z_SPRITE_RANDOM_BTN);
	}

	/*
	// slip txt
	LoginTxt * pLoginTxt = LoginTxt::Instance();
	pLoginTxt->setPosition(POS(ccp(POSX(240), POSX(80)), ScaleUtil::CENTER));
	pLoginTxt->setIsVisible(true); // hide
	this->addChild(pLoginTxt);
	pLoginTxt->start();
	*/
	// Add enter game button.
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pEnterGameMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
			menu_selector(LoginCreateRole::onEnterGameMenuClick));
	//pEnterGameMenuItem->setAnchorPoint(CCPointZero);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pEnterGameMenuItem->setScale(1.5f);
#else
	pEnterGameMenuItem->setScale(1.5f);
#endif
		pEnterGameMenuItem->setPosition( POS(ccp(480, 130), ScaleUtil::CENTER) );
		CCMenu* pEnterGameMenu = CCMenu::menuWithItems(pEnterGameMenuItem, NULL);
		pEnterGameMenu->setPosition( CCPointZero );
		this->addChild(pEnterGameMenu);

		CCLabelTTF* pTitleLabelEnterGame = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG020").c_str(),
			CCSizeMake(POSX(128), POSX(32)), 
			CCTextAlignmentLeft, 
			g_sSimHeiFont, 
			POSX(32));
		pTitleLabelEnterGame->setColor(ccc3(255, 255, 0));
		//pTitleLabelEnterGame->setAnchorPoint(CCPointZero);
		pTitleLabelEnterGame->setIsRelativeAnchorPoint(true);
		pTitleLabelEnterGame->setPosition( POS(ccp(480, 130), ScaleUtil::CENTER) );
		this->addChild(pTitleLabelEnterGame);
		}
		
	}
}

void LoginCreateRole::onSelectModel(CCObject * pSender)
{
	CCMenuItemImage * pMenuItem = (CCMenuItemImage *)pSender;
	int tag = pMenuItem->getTag();
	int roleId = ( tag%3 + 1 + 3*(tag%3)) + tag/3;
	if (roleId%2 == 0)
	{
		_curSelectSex = 2;
	}
	else
	{
		_curSelectSex = 1;
	}

	// switch
	if (roleId == 5){roleId = 9;}
	else if (roleId == 9){roleId = 5;}
	else if (roleId == 10){roleId = 6;}
	else if (roleId == 6){roleId = 10;}
	
	g_pLoginManage->setRoleID(roleId);

	CCNode * pGridSprite = (CCNode *)this->getChildByTag(TAG_SPRITE_MODEL+tag);
	if (!pGridSprite)	{return;}
	CCPoint spritePoint = getScreenPos(pGridSprite);
	if (this->getChildByTag(TAG_SPRITE_HIGHLIGHT))
	{
		this->getChildByTag(TAG_SPRITE_HIGHLIGHT)->setIsVisible(true);
		this->getChildByTag(TAG_SPRITE_HIGHLIGHT)->setPosition(spritePoint);
	}

	//onNameGeneratorMenuClick(0);
}

void LoginCreateRole::onNameGeneratorMenuClick(CCObject *pSender)
{
	std::string randName = Namemanager::Instance()->randomName(_curSelectSex);
	TextFieldTTF * pRoleNameTextField = (TextFieldTTF *)this->getChildByTag(LoginView::TEXTFIELD_ROLECREATE);
	if (pRoleNameTextField)
	{
		CCTextFieldTTF *pRoleNameCCTextField = (CCTextFieldTTF*)pRoleNameTextField->m_pTrackNode;
		pRoleNameCCTextField->setString(randName.c_str());
	}
	g_pLoginManage->setRoleName(randName);

	SoundManager::Instance()->playButtonEffectSound();
}

void LoginCreateRole::onEnterGameMenuClick(CCObject *pSender)
{
	TextFieldTTF *pRoleNameTextField = (TextFieldTTF *)this->getChildByTag(LoginView::TEXTFIELD_ROLECREATE);
	if(pRoleNameTextField)
	{
		CCTextFieldTTF *pRoleNameCCTextField = (CCTextFieldTTF*)pRoleNameTextField->m_pTrackNode;
		std::string szRoleName = pRoleNameCCTextField->getString();
		if (szRoleName.length()<1||szRoleName.length()>21)	
		{
			CCMessageBox(ValuesUtil::Instance()->getString("LG036").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
			return;
		}
		if (strstr(szRoleName.c_str() , " "))
		{
			CCMessageBox(ValuesUtil::Instance()->getString("LG037").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
			return;
		}
		
		g_pLoginManage->setRoleName(szRoleName);
	}
	// send role create msg
	g_pLoginManage->createHandler(0);

	SoundManager::Instance()->playButtonEffectSound();

}

LoginCreateRole::~LoginCreateRole()
{
 //	CCSprite* pSpriteBg = (CCSprite*)this->getChildByTag( TAG_Login_Creat_RoleBg );
 //	if ( pSpriteBg )
 //	{
 //		CCTexture2D* pTex = pSpriteBg->getTexture();
 //		pSpriteBg->removeFromParentAndCleanup(true);
 //		CCTextureCache::sharedTextureCache()->removeTexture(pTex);
 //	}
 //	
 //	CCSprite* pS1 = (CCSprite*)this->getChildByTag(TAG_Login_Creat_Friend1);
 //	if (pS1)
 //	{
 //		CCTexture2D* pTex = pS1->getTexture();
 //		pS1->removeFromParentAndCleanup(true);
 //		CCTextureCache::sharedTextureCache()->removeTexture(pTex);
 //	}
 //
 //	pS1 = (CCSprite*)this->getChildByTag(TAG_Login_Creat_Friend2);
 //	if (pS1)
 //	{
 //		CCTexture2D* pTex = pS1->getTexture();
 //		pS1->removeFromParentAndCleanup(true);
 //		CCTextureCache::sharedTextureCache()->removeTexture(pTex);
 //	}

	//for (int i = 0;i<6;i++)
	//{
	//	CCSprite * pGridSprite = (CCSprite *)this->getChildByTag(TAG_SPRITE_MODEL+i);
	//	if (pGridSprite)
	//	{
	//		CCTexture2D * pTex = pGridSprite->getTexture();
	//		pGridSprite->removeFromParentAndCleanup(true);
	//		CCTextureCache::sharedTextureCache()->removeTexture(pTex);
	//	}
	//}

	//CCSprite * pInputSprite = (CCSprite *)this->getChildByTag(TAG_SPRITE_INPUT);
	//if (pInputSprite)
	//{
	//	CCTexture2D * pTexture = pInputSprite->getTexture();
	//	pInputSprite->removeFromParentAndCleanup(true);
	//	CCTextureCache::sharedTextureCache()->removeTexture(pTexture);
	//}
	
	this->removeAllChildrenWithCleanup(true);

	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_create_role.pvr.ccz");

	CCTexture2D* pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/res_login_input.pvr.ccz");
	if (pText && (pText->retainCount()==1))
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_input.pvr.ccz");
}
