#include "MailAttachItem.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "../MailMediator.h"
#include "control/AppFacade.h"
#include "manager/TouchLayerEnum.h"

#define Mail_FontSize (POSX(20))
#define Mail_Attach_Scale (0.7f)

MailAttachItem::MailAttachItem(MailContentVo contentVo)
{
	if (!CCLayer::init()) {return;	}
	_contentVo = contentVo;

	this->setIsRelativeAnchorPoint(true);
	
	
	CCSprite * pGrid = new CCSprite();
	pGrid->initWithSpriteFrameName("mail/grid.png");
	pGrid->setTag(TAG_Grid);
	this->addChild(pGrid,1);
	pGrid->release();

	this->setContentSize(pGrid->getContentSize());

	this->setScale(Mail_Attach_Scale);

}

MailAttachItem::~MailAttachItem()
{

}

void MailAttachItem::setItem(MailContentVo contentVo)
{
	_contentVo = contentVo;

	CCSprite * pGrid = (CCSprite *)this->getChildByTag(TAG_Grid);
	if (!pGrid){ return;	}

	CCSize size = pGrid->getContentSize();

	pGrid->removeAllChildrenWithCleanup(true);

	if ((!contentVo.attachId) || (contentVo.attachStatus == 2))
	{ 
		CCLabelTTF * pStatusText = new CCLabelTTF();
		pStatusText->initWithString(ValuesUtil::Instance()->getString("MAIL025").c_str(),
			CCSizeMake(POSX(90),POSX(30)),CCTextAlignmentLeft,
			"Arial",
			POSX(20)/Mail_Attach_Scale);
		pStatusText->setPosition(ccp(POSX(150),size.height/2+POSX(0)));
		pGrid->addChild(pStatusText,1);
		pStatusText->release();
		return;	
	}

	CCLabelTTF * pStatusText = new CCLabelTTF();
	pStatusText->initWithString("",CCSizeMake(POSX(90),POSX(30)),CCTextAlignmentLeft,"Arial",POSX(20)/Mail_Attach_Scale);
	pStatusText->setPosition(ccp(POSX(150),size.height/2+POSX(0)));
	pGrid->addChild(pStatusText,1);
	pStatusText->release();

	std::string strStatus("");
	if (contentVo.attachStatus == 0)
	{
		pStatusText->setString(ValuesUtil::Instance()->getString("MAIL024").c_str());
		pStatusText->setColor(ccc3(12,233,25));
	}
	else if (contentVo.attachStatus == 1)
	{
		pStatusText->setString(ValuesUtil::Instance()->getString("MAIL023").c_str());
		pStatusText->setColor(ccc3(233,25,12));
	}
	else if (contentVo.attachStatus == 2)
	{
		pStatusText->setString(ValuesUtil::Instance()->getString("MAIL025").c_str());
		pStatusText->setColor(ccc3(150,150,150));
		return;
	}

	// goods number
	CCLabelTTF * pNumText = new CCLabelTTF();
	char path[32] = {0};
	sprintf(path,ValuesUtil::Instance()->getString("MAIL028").c_str(),contentVo.goodsNum);
	pNumText->initWithString(path,CCSizeMake(POSX(240),POSX(30)),CCTextAlignmentLeft,"Arial",POSX(20)/Mail_Attach_Scale);	
	pNumText->setPosition(ccp(POSX(150),POSX(15)));
	pNumText->setColor(ccc3(12,233,25));
	pGrid->addChild(pNumText,1);
	pNumText->release();

	// image button
	char path1[64] = {0};
	//sprintf(path1,"goods/%d.png",contentVo.attachId);
	sprintf(path1,"assets/icon/goods/%d.png",contentVo.attachId);

	CCSprite * pTestSprite = new CCSprite();
	//bool  var = pTestSprite->initWithSpriteFrameName(path1);
	bool  var = pTestSprite->initWithFile(path1);
	if (!var)
	{
		memset(path1,0,sizeof(path1));
		sprintf(path1,"assets/icon/goods/unknown.png");
		CC_SAFE_DELETE(pTestSprite);
	}
	else
	{
		pTestSprite->release();
	}

	CCSprite* p1 = CCSprite::spriteWithFile(path1);
	CCSprite* p2 = CCSprite::spriteWithFile(path1);
	CCSprite* p3 = CCSprite::spriteWithFile(path1);
	CCMenuItemSprite * pItemImage = CCMenuItemImage::itemFromNormalSprite(
		p1,
		p2,
		p3,
		this,
		menu_selector(MailAttachItem::onGetAttach));
	CCMenu * pMenuItem = CCMenu::menuWithItem(pItemImage);
	pMenuItem->setTouchLayer(TLE::WindowLayer_MailView - 5);
	if (pMenuItem)
	{
		pMenuItem->setTag(TAG_ItemImage);
		pMenuItem->setPosition(ccp(size.width/2,size.height/2));
		pGrid->addChild(pMenuItem,0);
	}
//	pImageSprite->release();
}

void MailAttachItem::onGetAttach(CCObject * pSender)
{
	if (_contentVo.attachStatus == 2)
	{
		return;
	}

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->onGetAttachRequest(_contentVo.mailId);
	}
}