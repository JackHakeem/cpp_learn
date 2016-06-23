#include "LeftChatContainer.h"
#include "../LiveThing.h"
#include "utils/ScaleUtil.h"
#include "StoryChatUIPrintView.h"
#include "model/player/RoleManage.h"

LeftChatContainer::LeftChatContainer()
{
	//_pBack = 0;
}

LeftChatContainer::~LeftChatContainer()
{

}

bool LeftChatContainer::init()
{
	if (!ChatContainer::init())
	{
		return false;
	}
	return true;
}


void LeftChatContainer::loadBackGround()
{
	//Doyang 20120712
	CCSprite *pBackground = (CCSprite *) this->getChildByTag(TAG_BG);
	if(!pBackground)
	{
		pBackground = new CCSprite();
		if(pBackground && pBackground->initWithSpriteFrameName("rightpanel.png"))
		{
			pBackground->setFlipX(true);
			this->setContentSize(pBackground->getContentSize());
			this->addChild(pBackground, Z_BG, TAG_BG);
			pBackground->release();
		}
		else
		{
			CC_SAFE_DELETE(pBackground);
		}
	}


	//this->setContentSize(pBackground->getContentSize());
	//if (!_pBack)
	//{
	//	_pBack = CCSprite::spriteWithFile("assets/ui/figure/leftpanel.png");
	//	if (_pBack)
	//	{
	//		//_pBack->setAnchorPoint(CCPointZero);
	//		_pBack->setIsRelativeAnchorPoint(true);
	//		if (this->getChildByTag(TAG_BG))
	//		{
	//			this->removeChildByTag(TAG_BG,true);
	//		}
	//		this->addChild(_pBack,Z_BG,TAG_BG);
	//		this->setContentSize(_pBack->getContentSize());
	//	}
	//}
}

void LeftChatContainer::loadIcon(int id)
{
	/*char path[32];
	sprintf(path,"assets/res/%d/head.png",id);
	CCSprite * pHeadSprite = CCSprite::spriteWithFile(path);
	if (!pHeadSprite){return;}
	pHeadSprite->setScale(0.7);
	pHeadSprite->setAnchorPoint(CCPointZero);
	pHeadSprite->setIsRelativeAnchorPoint(true);
	pHeadSprite->setPosition(ccp(POSX(0),POSX(10)));
	if (_pBack->getChildByTag(TAG_ICON))
	{
	_pBack->removeChildByTag(TAG_ICON,true);
	}
	_pBack->addChild(pHeadSprite,Z_ICON,TAG_ICON);*/
}

void LeftChatContainer::loadName(std::string szName)
{
	//std::string szNameEx("");
	//szNameEx.append("[").append(szName).append("]");
	//CCLabelTTF * pNameText = CCLabelTTF::labelWithString(szNameEx.c_str(),CCSizeMake(POSX(200),POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(28));
	////pNameText->setAnchorPoint(CCPointZero);
	////pNameText->setIsRelativeAnchorPoint(true);
	//pNameText->setColor(ccc3(255,215,0));
	//pNameText->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height-POSX(30)));
	//if (_pBack->getChildByTag(TAG_NAME))
	//{
	//	_pBack->removeChildByTag(TAG_NAME,true);
	//}
	//_pBack->addChild(pNameText,Z_NAME,TAG_NAME);
}

void LeftChatContainer::loadContent(std::string szContent)
{
	if (!this->getChildByTag(TAG_CONTENT))
	{
		/*
		CCLabelTTF * pContentText = CCLabelTTF::labelWithString(szContent.c_str(),CCSizeMake(POSX(300),POSX(150)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(28));
		//pContentText->setAnchorPoint(CCPointZero);
		pContentText->setIsRelativeAnchorPoint(true);
		pContentText->setColor(ccc3(255,255,255));
		pContentText->setPosition(ccp(POSX(0),POSX(25)));
		this->addChild(pContentText,Z_CONTENT,TAG_CONTENT);
		*/
		
		//StoryChatUIPrintView * pPrintView = new StoryChatUIPrintView();
		//pPrintView = (StoryChatUIPrintView *)pPrintView->initUIPrintViewWithCCRect(CCRectMake(0,0,POSX(350),POSX(150)),szContent,0.1f,POSX(28.0f));

		//CCUIPrintView * pPrintViewBase = CCUIPrintView::initUIPrintViewWithCCRect(CCRectMake(0,0,POSX(350),POSX(150)),szContent,0.1f,POSX(28.0f));
		//StoryChatUIPrintView * pPrintView = (StoryChatUIPrintView *)pPrintViewBase;

        CCRect tmpRect = CCRectMake(0,0,POSX(400),POSX(180));
        float time = 0.01f;
        
#if (CC_TARGET_PLATFORM  == CC_PLATFORM_ANDROID)
        time = 0.02f;
#else
        time = 0.01f;
#endif
		StoryChatUIPrintView * pPrintView = StoryChatUIPrintView::initUIPrintViewWithCCRect(tmpRect,szContent, time, POSX(28.0f));
		if (pPrintView)
		{
			pPrintView->setTag(TAG_CONTENT);
			pPrintView->setFontSize(POSX(28.0f));
			pPrintView->setPosition(ccp(POSX(0),POSX(35)));
			this->addChild(pPrintView,Z_CONTENT);
			pPrintView->run();
			pPrintView->release();
		}
		
	}
	else
	{
		/*
		CCLabelTTF * pContentText = (CCLabelTTF *)this->getChildByTag(TAG_CONTENT);
		if (pContentText)
		{
			pContentText->setString(szContent.c_str());
		}
		*/
		
		StoryChatUIPrintView * pPrintView = (StoryChatUIPrintView *)this->getChildByTag(TAG_CONTENT);
		pPrintView->setPrintString(szContent);
		pPrintView->run();
		
	}
}

void LeftChatContainer::showContent(struct _VOICE_* _voice)
{
	//ChatContainer::loadBackGround();
	loadBackGround();
	//loadIcon(_voice->id);
	//loadName(_voice->name);
	char path[512] = {0};
	sprintf(path,_voice->content.c_str(),RoleManage::Instance()->accountInfo()->name.c_str());
	loadContent(path);
}