#include "MailView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "MailScrollView.h"
#include "manager/PopEventName.h"
#include "model/mail/MailConst.h"
#include "control/AppFacade.h"
#include "model/mail/MailProxy.h"
#include "MailItem.h"
#include "utils/ValuesUtil.h"
#include "../MailMediator.h"
#include "manager/TouchLayerEnum.h"
#include "MailAttachItem.h"
#include "TextFieldTTF.h"
#include "Message.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "MailTextFieldTTF.h"

#define Mail_Scroll_View_width (POSX(360))
#define Mail_Scroll_View_Height (POSX(450))

#define Mail_WriteRead_View_width (POSX(500))
#define Mail_WriteRead_View_Height (POSX(450))

#define Mail_NameTile_TextFeild_width (POSX(460))
#define Mail_NameTile_TextFeild_height (POSX(40))

#define Mail_Content_TextFeild_width (POSX(460))
#define Mail_Content_TextFeild_height (POSX(250))

#define Mail_Content_Pos (ccp(Mail_WriteRead_View_width/2,0.208f * Mail_WriteRead_View_Height + Mail_Content_TextFeild_height/2-POSX(10)))

#define MAX_ROW_NUM (6)

#define FONT_SIZE (POSX(24))

MailView::MailView()
{
	_winSize = CCDirector::sharedDirector()->getWinSize();
	_listPos = ccp(POSX(960) * 0.23f,POSX(640) * 0.48f);
	_writeReadPos = ccp(POSX(960) * 0.62f, POSX(640) * 0.48f);
	_curMailTab = MailConst::MAIL_TYPE_ALL;
	_curMailId = 0;
	_curPage = 1;
	_isDeleteAll = false;
	_isTabClick = false;
}

MailView::~MailView()
{

}

bool MailView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	
	initView();
	

	return true;
}

void MailView::initView()
{
	this->setIsTouchEnabled(true);
	
	this->setContentSize(_winSize);
	this->setPopContentSize(this->getContentSize());
	
	key = PopEventName::MAIL;

	loadBackGround();
	loadTabButton();
	loadMailListPanel();
	loadWritePanel();
	loadReadPanel();
	loadButtons();
}

void MailView::loadBackGround()
{
	CCSize size = this->getContentSize();
	
	// contaiter
	CCLayer * pContainer = new CCLayer();
	pContainer->init();
	pContainer->setContentSize(CCSizeMake(POSX(960),POSX(640)));
	pContainer->setPosition(POS(ccp(0,12.0f), ScaleUtil::CENTER_TOP));
	pContainer->setAnchorPoint(CCPointZero);
	pContainer->setIsRelativeAnchorPoint(true);
	pContainer->setTag(TAG_Container);
	this->addChild(pContainer,Z_Back);
	pContainer->release();
	
	// mail list background
	CCUIBackground * pListBackGround = new CCUIBackground();
	pListBackGround->initWithSpriteFrame("mail/bg2.png",
		ccp(0,0),
		ccp(0,0),
		CCSizeMake(Mail_Scroll_View_width,Mail_Scroll_View_Height),
		200);
	CCPoint posList = ccp(_listPos.x-Mail_Scroll_View_width/2,_listPos.y-Mail_Scroll_View_Height/2);
	pListBackGround->setPosition(posList);
	pContainer->addChild(pListBackGround,Z_Back);
	pListBackGround->release();

	// read write background
	CCUIBackground * pWriteReadBackGround = new CCUIBackground();
	pWriteReadBackGround->initWithSpriteFrame("mail/bg2.png",
		ccp(0,0),
		ccp(0,0),
		CCSizeMake(Mail_WriteRead_View_width,Mail_WriteRead_View_Height),
		200);
	CCPoint posReadWritePanel = ccp(_writeReadPos.x-Mail_Scroll_View_width/2,_writeReadPos.y-Mail_Scroll_View_Height/2);
	pWriteReadBackGround->setPosition(posReadWritePanel);
	pContainer->addChild(pWriteReadBackGround,Z_Back);
	pWriteReadBackGround->release();
}

void MailView::loadTabButton()
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	// all mails
	CCMenuItemSprite * pAllMailItem = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/button2_normal.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		this,
		menu_selector(MailView::onAllMailTabClick));
	pAllMailItem->setTag(TAG_MenuItemImage);
	CCMenu * pALLMailBtn = CCMenu::menuWithItem(pAllMailItem);
	CCPoint tabAllMailPos = ccp(POSX(960) * 0.2f,POSX(640)-POSX(50));
	pALLMailBtn->setTouchLayer(TLE::WindowLayer_MailView);
	pALLMailBtn->setPosition(tabAllMailPos);
	pALLMailBtn->setTag(TAG_Button_Menu_AllMail);
	pContainer->addChild(pALLMailBtn,Z_Tab_Btn);

	CCLabelTTF * pAllMailText = new CCLabelTTF();// static text
	pAllMailText->initWithString(ValuesUtil::Instance()->getString("MAIL002").c_str(),
		CCSizeMake(POSX(90),POSX(28)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pAllMailText->setPosition(tabAllMailPos);
	pAllMailText->setColor(ccc3(233,233,25));
	pContainer->addChild(pAllMailText,Z_Tab_Btn+1);
	pAllMailText->release();

	// sys mails
	CCMenuItemSprite * pSysMailItem = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/button2_normal.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		this,
		menu_selector(MailView::onSysMailTabClick));
	pSysMailItem->setTag(TAG_MenuItemImage);
	CCMenu * pSysMailBtn = CCMenu::menuWithItem(pSysMailItem);
	CCPoint tabSysMailPos = ccp(POSX(960) * 0.4f,POSX(640)-POSX(50));
	pSysMailBtn->setPosition(tabSysMailPos);
	pSysMailBtn->setTouchLayer(TLE::WindowLayer_MailView);
	pSysMailBtn->setTag(TAG_Button_Menu_SysMail);
	pContainer->addChild(pSysMailBtn,Z_Tab_Btn);

	CCLabelTTF * pSysMailText = new CCLabelTTF();// static text
	pSysMailText->initWithString(ValuesUtil::Instance()->getString("MAIL003").c_str(),
		CCSizeMake(POSX(90),POSX(28)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pSysMailText->setPosition(tabSysMailPos);
	pSysMailText->setColor(ccc3(233,233,25));
	pContainer->addChild(pSysMailText,Z_Tab_Btn+1);
	pSysMailText->release();

	// player mails
	CCMenuItemSprite * pPlayerMailItem = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/button2_normal.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		this,
		menu_selector(MailView::onPlayerMailTabClick));
	pPlayerMailItem->setTag(TAG_MenuItemImage);
	CCMenu * pPlayerMailBtn = CCMenu::menuWithItem(pPlayerMailItem);
	CCPoint tabPlayerMailPos = ccp(POSX(960) * 0.6f,POSX(640)-POSX(50));
	pPlayerMailBtn->setPosition(tabPlayerMailPos);
	pPlayerMailBtn->setTouchLayer(TLE::WindowLayer_MailView);
	pPlayerMailBtn->setTag(TAG_Button_Menu_PlayerMail);
	pContainer->addChild(pPlayerMailBtn,Z_Tab_Btn);

	CCLabelTTF * pPlayerMailText = new CCLabelTTF();// static text
	pPlayerMailText->initWithString(ValuesUtil::Instance()->getString("MAIL004").c_str(),
		CCSizeMake(POSX(90),POSX(28)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pPlayerMailText->setPosition(tabPlayerMailPos);
	pPlayerMailText->setColor(ccc3(233,233,25));
	pContainer->addChild(pPlayerMailText,Z_Tab_Btn+1);
	pPlayerMailText->release();
}

void MailView::loadMailListPanel()
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	// all mail scroll view
	CCPoint pos;
	pos.x = _listPos.x - Mail_Scroll_View_width/2;
	pos.y = _listPos.y - Mail_Scroll_View_Height/2;
	MailScrollView * pAllMailScrollView = MailScrollView::scrollViewWithCCRect(CCRectMake(pos.x,pos.y,Mail_Scroll_View_width,Mail_Scroll_View_Height));
	pAllMailScrollView->setTag(TAG_AllMail_ScrollView);
	pAllMailScrollView->m_pri = TLE::WindowLayer_MailView;
	pContainer->addChild(pAllMailScrollView,Z_Scroll);
	pAllMailScrollView->release();
	
	// sys mail scroll view
	pos.x = _listPos.x - Mail_Scroll_View_width/2;
	pos.y = _listPos.y - Mail_Scroll_View_Height/2;
	MailScrollView * pSysMailScrollView = MailScrollView::scrollViewWithCCRect(CCRectMake(pos.x,pos.y,Mail_Scroll_View_width,Mail_Scroll_View_Height));
	pSysMailScrollView->setTag(TAG_SysMail_ScrollView);
	pSysMailScrollView->m_pri = TLE::WindowLayer_MailView;
	pSysMailScrollView->setIsVisible(false);
	pContainer->addChild(pSysMailScrollView,Z_Scroll);
	pSysMailScrollView->release();

	// player mail scroll view
	pos.x = _listPos.x - Mail_Scroll_View_width/2;
	pos.y = _listPos.y - Mail_Scroll_View_Height/2;
	MailScrollView * pPlayerMailScrollView = MailScrollView::scrollViewWithCCRect(CCRectMake(pos.x,pos.y,Mail_Scroll_View_width,Mail_Scroll_View_Height));
	pPlayerMailScrollView->setTag(TAG_PlayerMail_ScrollView);
	pPlayerMailScrollView->m_pri = TLE::WindowLayer_MailView;
	pPlayerMailScrollView->setIsVisible(false);
	pContainer->addChild(pPlayerMailScrollView,Z_Scroll);
	pPlayerMailScrollView->release();

	// hight light sprite
	CCUIBackground * pHightLight = new CCUIBackground();
	pHightLight->initWithSpriteFrame("mail/light.png",CCPointZero,CCPointZero,CCSizeMake(POSX(310),POSX(70)),250);
	pHightLight->setTag(TAG_HightLight);
	pHightLight->setIsVisible(false);
	pContainer->addChild(pHightLight,Z_Scroll+1);
	pHightLight->release();
}

void MailView::loadWritePanel()
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	// WritePanel
	CCLayer * pMailWriteLayer = new CCLayer();
	pMailWriteLayer->init();
	pMailWriteLayer->setContentSize(CCSizeMake(Mail_WriteRead_View_width,Mail_WriteRead_View_Height));
	pMailWriteLayer->setIsRelativeAnchorPoint(true);
	pMailWriteLayer->setPosition(ccp(_writeReadPos.x+POSX(70),_writeReadPos.y));
	pMailWriteLayer->setTag(TAG_Write_ContentLayer);
	pMailWriteLayer->setIsVisible(false);
	pContainer->addChild(pMailWriteLayer,Z_ContentLayer);
	pMailWriteLayer->release();

	// 收件人
	CCLabelTTF * pRecvText = new CCLabelTTF();// static text
	pRecvText->initWithString(ValuesUtil::Instance()->getString("MAIL017").c_str(),
		CCSizeMake(POSX(120),POSX(28)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pRecvText->setColor(ccc3(233,133,25));
	pRecvText->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(70),
		0.88f * Mail_WriteRead_View_Height + POSX(15)));
	pMailWriteLayer->addChild(pRecvText,Z_Back+1);
	pRecvText->release();

	CCUIBackground * pNameBackGround = new CCUIBackground(); // input background
	pNameBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_NameTile_TextFeild_width, Mail_NameTile_TextFeild_height),225);
	pNameBackGround->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2,
		0.88f * Mail_WriteRead_View_Height));
	pMailWriteLayer->addChild(pNameBackGround,Z_Back);
	pNameBackGround->release();
	
	// input FeildTTF
	TextFieldTTF * pNameInputFeild = new TextFieldTTF(); // input
	pNameInputFeild->setString("");
	pNameInputFeild->setContentSize(CCSizeMake(POSX(240),POSX(30)));
	pNameInputFeild->setTag(TAG_Name_TextFeild);
	pNameInputFeild->setAnchorPoint(ccp(POSX(0),POSX(0)));
	pNameInputFeild->setIsCanBeTouched(false);
	pNameInputFeild->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(450),
		0.88f * Mail_WriteRead_View_Height + POSX(17)));
	pMailWriteLayer->addChild(pNameInputFeild,Z_Back+3);
	pNameInputFeild->release();	

	// 邮件主题
	CCLabelTTF * pMailTitleText = new CCLabelTTF();// static text
	pMailTitleText->initWithString(ValuesUtil::Instance()->getString("MAIL020").c_str(),
		CCSizeMake(POSX(150),POSX(28)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pMailTitleText->setColor(ccc3(233,133,25));
	pMailTitleText->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(85),
		0.78f * Mail_WriteRead_View_Height + POSX(15)));
	pMailWriteLayer->addChild(pMailTitleText,Z_Back+1);
	pMailTitleText->release();

	CCUIBackground * pTitleBackGround = new CCUIBackground(); // input background
	pTitleBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_NameTile_TextFeild_width,Mail_NameTile_TextFeild_height),225);
	pTitleBackGround->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2,
		0.78f * Mail_WriteRead_View_Height));
	pMailWriteLayer->addChild(pTitleBackGround,Z_Back);
	pTitleBackGround->release();

	// input
	TextFieldTTF * pTitleInputFeild = new TextFieldTTF(); // input
	pTitleInputFeild->setString("");
	pTitleInputFeild->setContentSize(CCSizeMake(POSX(240),POSX(30)));
	pTitleInputFeild->setTag(TAG_Title_TextFeild);
	pTitleInputFeild->setAnchorPoint(ccp(POSX(0),POSX(0)));
	pTitleInputFeild->setIsCanBeTouched(false);
	pTitleInputFeild->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(450),
		0.78f * Mail_WriteRead_View_Height + POSX(17)));
	pMailWriteLayer->addChild(pTitleInputFeild,Z_Back+3);
	pTitleInputFeild->release();

	// 邮件正文
	CCUIBackground * pContentBackGround = new CCUIBackground(); // input background
	pContentBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_Content_TextFeild_width, Mail_Content_TextFeild_height),225);
	pContentBackGround->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2,
		(0.208f) * Mail_WriteRead_View_Height));
	pMailWriteLayer->addChild(pContentBackGround,Z_Back);
	pContentBackGround->release();

	
	// input
	MailTextFieldTTF * pContentInputFeild = new MailTextFieldTTF(); // input
	pContentInputFeild->setString("");
	pContentInputFeild->setTag(TAG_Content_TextFeild);
	pContentInputFeild->setAnchorPoint(ccp(POSX(0),POSX(0)));
	pContentInputFeild->setIsCanBeTouched(false);
	pContentInputFeild->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(232),
		/*0.620f * Mail_WriteRead_View_Height +*/ Mail_WriteRead_View_Height/2));
	pMailWriteLayer->addChild(pContentInputFeild,Z_Back+3);
	pContentInputFeild->release();

	// 按钮
	// send mail

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pSendMailItemImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(MailView::onSendMail));
			CCMenu * pSendMailMenu = CCMenu::menuWithItem(pSendMailItemImg);
			pSendMailMenu->setTouchLayer(TLE::WindowLayer_MailView-5);
			pSendMailMenu->setTag(TAG_Button_Menu_Write);
			pSendMailMenu->setPosition(ccp(Mail_WriteRead_View_width/1.8f, 0.121f * Mail_WriteRead_View_Height));
			pMailWriteLayer->addChild(pSendMailMenu);
		}
	}

	CCLabelTTF * pSendMailText = new CCLabelTTF();
	pSendMailText->initWithString(ValuesUtil::Instance()->getString("MAIL014").c_str(),
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pSendMailText->setPosition(ccp(Mail_WriteRead_View_width/1.8f, 0.121f * Mail_WriteRead_View_Height));
	pMailWriteLayer->addChild(pSendMailText,Z_Tab_Btn);
	pSendMailText->release();

	// return mail
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pReturnMailItemImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(MailView::onReturn));
			CCMenu * pReturnMailMenu = CCMenu::menuWithItem(pReturnMailItemImg);
			pReturnMailMenu->setTouchLayer(TLE::WindowLayer_MailView-5);
			pReturnMailMenu->setPosition(ccp(Mail_WriteRead_View_width/1.2f, 0.121f * Mail_WriteRead_View_Height));
			pReturnMailMenu->setTag(TAG_Button_Menu_Return);
			pMailWriteLayer->addChild(pReturnMailMenu);
		}
	}

	CCLabelTTF * pReturnMailText = new CCLabelTTF();
	pReturnMailText->initWithString(ValuesUtil::Instance()->getString("MAIL015").c_str(),
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pReturnMailText->setPosition(ccp(Mail_WriteRead_View_width/1.2f, 0.121f * Mail_WriteRead_View_Height));
	pMailWriteLayer->addChild(pReturnMailText,Z_Tab_Btn);
	pReturnMailText->release();
}

void MailView::loadReadPanel()
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	// ReadPanel
	CCLayer * pMailReadLayer = new CCLayer();
	pMailReadLayer->init();
	pMailReadLayer->setContentSize(CCSizeMake(Mail_WriteRead_View_width,Mail_WriteRead_View_Height));
	pMailReadLayer->setIsRelativeAnchorPoint(true);
	pMailReadLayer->setPosition(ccp(_writeReadPos.x+POSX(70),_writeReadPos.y));
	pMailReadLayer->setTag(TAG_Read_ContentLayer);
	pMailReadLayer->setIsVisible(true);
	pContainer->addChild(pMailReadLayer,Z_ContentLayer);
	pMailReadLayer->release();

	//发件人
	CCLabelTTF * pSenderText = new CCLabelTTF();// static text
	pSenderText->initWithString(ValuesUtil::Instance()->getString("MAIL018").c_str(),
		CCSizeMake(POSX(120),POSX(28)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pSenderText->setColor(ccc3(233,133,25));
	pSenderText->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(70),
		0.88f * Mail_WriteRead_View_Height + POSX(15)));
	pMailReadLayer->addChild(pSenderText,Z_Back+1);
	pSenderText->release();

	CCUIBackground * pNameBackGround = new CCUIBackground(); // show background
	pNameBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_NameTile_TextFeild_width * 0.60f, Mail_NameTile_TextFeild_height),225);
 	pNameBackGround->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2,
 		0.88f * Mail_WriteRead_View_Height));
	pMailReadLayer->addChild(pNameBackGround,Z_Back);
	pNameBackGround->release();

	CCLabelTTF * pSenderName = new CCLabelTTF();
	pSenderName->initWithString(ValuesUtil::Instance()->getString("?").c_str(),
		CCSizeMake(POSX(200),POSX(30)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pSenderName->setTag(TAG_Name_TextFeild);
	pSenderName->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2+POSX(200),
		0.88f * Mail_WriteRead_View_Height + POSX(15)));
	pMailReadLayer->addChild(pSenderName,Z_Back+1);
	pSenderName->release();

	//发件日期
	/*
	CCLabelTTF * pSenderDate = new CCLabelTTF();// static text
	pSenderDate->initWithString(ValuesUtil::Instance()->getString("MAIL019").c_str(),
		CCSizeMake(POSX(120),POSX(28)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pSenderDate->setColor(ccc3(233,133,25));
	pSenderDate->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(70),
		0.88f * Mail_WriteRead_View_Height + POSX(15)));
	pMailReadLayer->addChild(pSenderDate,Z_Back+1);
	pSenderDate->release();
	*/

	CCUIBackground * pDateBackGround = new CCUIBackground(); // show background
	pDateBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_NameTile_TextFeild_width * 0.39f, Mail_NameTile_TextFeild_height),225);
	pDateBackGround->setPosition(ccp(
		Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + Mail_NameTile_TextFeild_width * 0.61f,
		0.88f * Mail_WriteRead_View_Height));
	pMailReadLayer->addChild(pDateBackGround,Z_Back);
	pDateBackGround->release();

	CCLabelTTF * pSenderDateText = new CCLabelTTF();
	pSenderDateText->initWithString(ValuesUtil::Instance()->getString("").c_str(),
		CCSizeMake(POSX(280),POSX(30)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE-6);
	pSenderDateText->setTag(TAG_Date_TextFeild);
	pSenderDateText->setPosition(ccp(
		Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + Mail_NameTile_TextFeild_width * 0.69f +POSX(110),
		0.88f * Mail_WriteRead_View_Height + POSX(15)));
	pMailReadLayer->addChild(pSenderDateText,Z_Back+1);
	pSenderDateText->release();

	// 邮件主题
	CCLabelTTF * pMailTitleText = new CCLabelTTF();// static text
	pMailTitleText->initWithString(ValuesUtil::Instance()->getString("MAIL020").c_str(),
		CCSizeMake(POSX(150),POSX(28)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pMailTitleText->setColor(ccc3(233,133,25));
	pMailTitleText->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2 + POSX(85),
		0.78f * Mail_WriteRead_View_Height + POSX(15)));
	pMailReadLayer->addChild(pMailTitleText,Z_Back+1);
	pMailTitleText->release();

	CCUIBackground * pTitleBackGround = new CCUIBackground(); // input background
	pTitleBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_NameTile_TextFeild_width,Mail_NameTile_TextFeild_height),225);
	pTitleBackGround->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2,
		0.78f * Mail_WriteRead_View_Height));
	pMailReadLayer->addChild(pTitleBackGround,Z_Back);
	pTitleBackGround->release();

	CCLabelTTF * pMailTile = new CCLabelTTF();
	pMailTile->initWithString(ValuesUtil::Instance()->getString("?").c_str(),
		CCSizeMake(POSX(300),POSX(30)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pMailTile->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2+POSX(275),
		0.78f * Mail_WriteRead_View_Height + POSX(15)));
	pMailTile->setTag(TAG_Title_TextFeild);
	pMailReadLayer->addChild(pMailTile,Z_Back+1);
	pMailTile->release();

	// 邮件正文
	CCUIBackground * pContentBackGround = new CCUIBackground(); // input background
	pContentBackGround->initWithSpriteFrame("mail/input1.png",ccp(0,0),ccp(0,0),
		CCSizeMake(Mail_Content_TextFeild_width, Mail_Content_TextFeild_height),225);
	pContentBackGround->setPosition(ccp(Mail_WriteRead_View_width/2-Mail_NameTile_TextFeild_width/2,
		(0.208f) * Mail_WriteRead_View_Height));
	pMailReadLayer->addChild(pContentBackGround,Z_Back);
	pContentBackGround->release();

	CCLabelTTF * pMailContent = new CCLabelTTF();
	pMailContent->initWithString(ValuesUtil::Instance()->getString("?").c_str(),
		CCSizeMake(Mail_Content_TextFeild_width-POSX(20),Mail_Content_TextFeild_height),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pMailContent->setPosition(Mail_Content_Pos);
	pMailContent->setAnchorPoint(ccp(0.5,0.5));
	pMailContent->setTag(TAG_Content_TextFeild);
	pMailReadLayer->addChild(pMailContent,Z_Back);
	pMailContent->release();

	// 附件
	CCLabelTTF * pMailAttach = new CCLabelTTF();
	pMailAttach->initWithString(ValuesUtil::Instance()->getString("MAIL016").c_str(),
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentLeft,
		"Arial",
		FONT_SIZE);
	pMailAttach->setPosition(ccp(Mail_WriteRead_View_width*0.3f, 0.150f * Mail_WriteRead_View_Height));
	pMailAttach->setAnchorPoint(ccp(0.5,0.5));
	pMailAttach->setTag(TAG_Content_TextFeild);
	pMailReadLayer->addChild(pMailAttach,Z_Back);
	pMailAttach->release();

	MailContentVo contentVo;
	MailAttachItem * pAttachItem = new MailAttachItem(contentVo);
	pAttachItem->setPosition(ccp(Mail_WriteRead_View_width/5.0f, 0.185f * Mail_WriteRead_View_Height));
	pAttachItem->setTag(TAG_Button_Menu_Attach);
	pMailReadLayer->addChild(pAttachItem);
	pAttachItem->release();


	// 按钮
	// delete mail
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pDelMailItemImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(MailView::onDeleteConfirm));
			pDelMailItemImg->setTag(TAG_BtnImage_DelSingle);
			CCMenu * pDelMailMenu = CCMenu::menuWithItem(pDelMailItemImg);
			pDelMailMenu->setPosition(ccp(Mail_WriteRead_View_width/1.8f, 0.121f * Mail_WriteRead_View_Height));
			pDelMailMenu->setTouchLayer(TLE::WindowLayer_MailView-5);
			pDelMailMenu->setTag(TAG_Button_Menu_Write);
			pMailReadLayer->addChild(pDelMailMenu);
		}
	}

	CCLabelTTF * pDelMailText = new CCLabelTTF();
	pDelMailText->initWithString(ValuesUtil::Instance()->getString("MAIL012").c_str(),
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pDelMailText->setPosition(ccp(Mail_WriteRead_View_width/1.8f, 0.121f * Mail_WriteRead_View_Height));
	pMailReadLayer->addChild(pDelMailText,Z_Tab_Btn);
	pDelMailText->release();

	// reply mail
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pReplyMailItemImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(MailView::onReplyMail));
			CCMenu * pReplyMailMenu = CCMenu::menuWithItem(pReplyMailItemImg);
			pReplyMailMenu->setPosition(ccp(Mail_WriteRead_View_width/1.2f, 0.121f * Mail_WriteRead_View_Height));
			pReplyMailMenu->setTouchLayer(TLE::WindowLayer_MailView-5);
			pReplyMailMenu->setTag(TAG_Button_Menu_Write);
			pMailReadLayer->addChild(pReplyMailMenu);
		}
	}

	CCLabelTTF * pReplyMailText = new CCLabelTTF();
	pReplyMailText->initWithString(ValuesUtil::Instance()->getString("MAIL013").c_str(),
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pReplyMailText->setPosition(ccp(Mail_WriteRead_View_width/1.2f, 0.121f * Mail_WriteRead_View_Height));
	pMailReadLayer->addChild(pReplyMailText,Z_Tab_Btn);
	pReplyMailText->release();
}

void MailView::loadButtons()
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	// delete all mail
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pDelAllMailItemImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(MailView::onDeleteConfirm));
			pDelAllMailItemImg->setTag(TAG_BtnImage_DelAll);
			CCMenu * pDelAllMailMenu = CCMenu::menuWithItem(pDelAllMailItemImg);
			pDelAllMailMenu->setTouchLayer(TLE::WindowLayer_MailView-5);
			pDelAllMailMenu->setPosition(ccp(_listPos.x-POSX(80),_listPos.y-Mail_Scroll_View_Height/2-POSX(30)));
			pDelAllMailMenu->setTag(TAG_Button_Menu_DelAllMail);
			pContainer->addChild(pDelAllMailMenu);
		}
	}

	CCLabelTTF * pDelAllMailText = new CCLabelTTF();
	pDelAllMailText->initWithString(ValuesUtil::Instance()->getString("MAIL008").c_str(),
		CCSizeMake(POSX(120),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pDelAllMailText->setPosition(ccp(_listPos.x-POSX(80),_listPos.y-Mail_Scroll_View_Height/2-POSX(30)));
	pContainer->addChild(pDelAllMailText,Z_Tab_Btn);
	pDelAllMailText->release();

	// write mail
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return;
	}	
	CCMenuItemSprite *pWriteMailItemImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		this,
		menu_selector(MailView::onWriteMail));
	CCMenu * pWriteMailMenu = CCMenu::menuWithItem(pWriteMailItemImg);
	pWriteMailMenu->setTouchLayer(TLE::WindowLayer_MailView-5);
	pWriteMailMenu->setTag(TAG_Button_Menu_Write);
	pWriteMailMenu->setPosition(ccp(_writeReadPos.x-Mail_Scroll_View_width/2+pWriteMailItemImg->getContentSize().width/2,
		_listPos.y-Mail_Scroll_View_Height/2-POSX(30)));
	pContainer->addChild(pWriteMailMenu);

	CCLabelTTF * pWriteMailText = new CCLabelTTF();
	pWriteMailText->initWithString(ValuesUtil::Instance()->getString("MAIL009").c_str(),
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE);
	pWriteMailText->setPosition(ccp(_writeReadPos.x-Mail_Scroll_View_width/2+pWriteMailItemImg->getContentSize().width/2,
		_listPos.y-Mail_Scroll_View_Height/2-POSX(30)));
	pContainer->addChild(pWriteMailText,Z_Tab_Btn);
	pWriteMailText->release();

	// page text
	CCLabelTTF * pPageText = new CCLabelTTF();
	pPageText->initWithString("0/0",
		CCSizeMake(POSX(90),POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		FONT_SIZE+3);
	pPageText->setTag(TAG_Page_LabelText);
	pPageText->setColor(ccc3(12,233,25));
	pPageText->setPosition(ccp(_listPos.x+POSX(80),_listPos.y-Mail_Scroll_View_Height/2-POSX(30)));
	pContainer->addChild(pPageText,Z_Tab_Btn);
	pPageText->release();
}

void MailView::setMailListContent(int mailtype)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	MailScrollView * pMailScrollView = 0;
	switch(mailtype)
	{
	case (MailConst::MAIL_TYPE_ALL):
		pMailScrollView = (MailScrollView *)pContainer->getChildByTag(TAG_AllMail_ScrollView);
		break;
	case (MailConst::MAIL_TYPE_SYSTEM):
		pMailScrollView = (MailScrollView *)pContainer->getChildByTag(TAG_SysMail_ScrollView);
		break;
	case (MailConst::MAIL_TYPE_PLAYER):
		pMailScrollView = (MailScrollView *)pContainer->getChildByTag(TAG_PlayerMail_ScrollView);
		break;
	}
	if (!pMailScrollView)	{return;	}

	pMailScrollView->setCurScreen(pMailScrollView->currentScreen);

	MailProxy * pMailProxy = (MailProxy *)g_pFacade->retrieveProxy(AppFacade_Mail_Proxy);
	if (!pMailProxy)	{return;	}

	std::list<MailHeadVo> * headList = pMailProxy->getHeadListByType(mailtype);
	if (!headList || headList->empty())
	{
		if (pMailScrollView->getContentLayer())
		{
			pMailScrollView->getContentLayer()->removeAllChildrenWithCleanup(true);
			pMailScrollView->currentScreen = 0;
			pMailScrollView->totalScreens = 0;
		}

		setPageText(0,0);

		MailContentVo contentVo;
		resetReadPanel(contentVo);
		return;	
	}

	std::list<MailHeadVo>::iterator iter = headList->begin();
	int curListpages = ceil((float)headList->size()/MAX_ROW_NUM);

	if (pMailScrollView->getContentLayer())
	{
		pMailScrollView->getContentLayer()->removeAllChildrenWithCleanup(true);
		pMailScrollView->currentScreen = 0;
		pMailScrollView->totalScreens = 0;
	}

	for (int page= 0; page< curListpages; page++)
	{
		if (iter == headList->end())	{break;	}
		CCLayer * pScrollLayer = pMailScrollView->addLayerByTag(page);
		for (int i = 0; i< MAX_ROW_NUM ; i++)
		{
			if (iter == headList->end()){break;	}

			MailItem * pMailItem = new MailItem(*iter);

			pMailItem->setTag(i%MAX_ROW_NUM);
			CCSize size = pMailScrollView->getContentSize();
			pMailItem->setPosition(ccp(size.width/2,size.height * (11.0f-i*2.0f)/12.0f));
			pScrollLayer->addChild(pMailItem,0);
			pMailItem->release();

			++iter;
		}
	}

	if (!_isTabClick)
	{
		for (int i = 1;i<_curPage;i++)
		{
			pMailScrollView->moveToNextPage();
		}
	}
	else
	{
		MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
		if (pMailMediator)
		{
			pMailMediator->_curPage = 1;
		}
		setCurPage(1);

		_isTabClick = false;
	}

	setPageText(pMailScrollView->currentScreen,pMailScrollView->totalScreens);
}

void MailView::onAllMailTabClick(CCObject * pSender)
{
	_curMailTab = MailConst::MAIL_TYPE_ALL;
	
	_isTabClick = true;

	requestMailCount(MailConst::MAIL_TYPE_ALL);
	//resetScrollPage(MailConst::MAIL_TYPE_ALL);
	//setMailListContent(MailConst::MAIL_TYPE_ALL);
	MailContentVo contentVo;
	resetReadPanel(contentVo);

	bool state[3] = {false,true,true};
	setTabBtnAndScrollState(state);

	showHightLight(false,CCPointZero);
}

void MailView::onSysMailTabClick(CCObject * pSender)
{
	_curMailTab = MailConst::MAIL_TYPE_SYSTEM;
	
	_isTabClick = true;

	requestMailCount(MailConst::MAIL_TYPE_SYSTEM);
	//resetScrollPage(MailConst::MAIL_TYPE_SYSTEM);
	//setMailListContent(MailConst::MAIL_TYPE_SYSTEM);
	MailContentVo contentVo;
	resetReadPanel(contentVo);

	bool state[3] = {true,false,true};
	setTabBtnAndScrollState(state);

	showHightLight(false,CCPointZero);
}

void MailView::onPlayerMailTabClick(CCObject * pSender)
{
	_curMailTab = MailConst::MAIL_TYPE_PLAYER;

	_isTabClick = true;

	requestMailCount(MailConst::MAIL_TYPE_PLAYER);
	//resetScrollPage(MailConst::MAIL_TYPE_PLAYER);
	//setMailListContent(MailConst::MAIL_TYPE_PLAYER);
	MailContentVo contentVo;
	resetReadPanel(contentVo);

	bool state[3] = {true,true,false};
	setTabBtnAndScrollState(state);

	showHightLight(false,CCPointZero);
}

void MailView::requestMailCount(int type)
{
	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->_curMailType = type;
		pMailMediator->requestMailList();
	}
}

void MailView::requestMailList(int type)
{
	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->_curMailType = type;
		pMailMediator->requestMailList();
	}
}

void MailView::onWriteMail(CCObject * pSender)
{
	enableInput(true,true,true);

	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}
	pWriteMailLayer->setIsVisible(true);
	pWriteMailLayer->setIsTouchEnabled(true);

	CCLayer * pReadMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Read_ContentLayer);
	if (!pReadMailLayer)	{return;}
	pReadMailLayer->setIsVisible(false);	
	pReadMailLayer->setIsTouchEnabled(false);

	MailContentVo contentVo;
	resetWritePanel(contentVo);
}

void MailView::onDeleteAllMails(CCObject * pSender)
{
	MailProxy * pMailProxy = (MailProxy *)g_pFacade->retrieveProxy(AppFacade_Mail_Proxy);
	if (!pMailProxy){return;}
	std::list<uint> mailIdList;
	std::list<MailHeadVo> * pHeadList = pMailProxy->getHeadListByType(MailConst::MAIL_TYPE_ALL);
	if (!pHeadList || pHeadList->empty()) {	return;	}

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		std::list<MailHeadVo>::iterator iter;
		for (iter = pHeadList->begin(); iter != pHeadList->end(); iter++)
		{
			mailIdList.push_back(iter->mailId);
		}
		pMailMediator->onMailDeleteClick(mailIdList);
	}
}

void MailView::onDeleteMail(CCObject * pSender)
{
	if (!_curMailId)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL032"),ccc3(233,12,25),1.0f);
		return;
	}
	MailProxy * pMailProxy = (MailProxy *)g_pFacade->retrieveProxy(AppFacade_Mail_Proxy);
	if (!pMailProxy){return;}
	std::list<uint> mailIdList;
	std::list<MailHeadVo> * pHeadList = pMailProxy->getHeadListByType(MailConst::MAIL_TYPE_ALL);
	if (!pHeadList || pHeadList->empty()) {	return;	}

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		std::list<MailHeadVo>::iterator iter;
		for (iter = pHeadList->begin(); iter != pHeadList->end(); iter++)
		{
			if (iter->mailId == _curMailId)
			{
				mailIdList.push_back(iter->mailId);
				break;
			}
		}
		pMailMediator->onMailDeleteClick(mailIdList);
	}
}

void MailView::onReplyMail(CCObject * pSender)
{
	enableInput(true,true,true);

	if (!_curMailId)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL033"),ccc3(233,12,25),1.0f);
		return;
	}

	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}
	pWriteMailLayer->setIsVisible(true);
	pWriteMailLayer->setIsTouchEnabled(true);

	MailContentVo contentVo;

	MailProxy * pMailProxy = (MailProxy *)g_pFacade->retrieveProxy(AppFacade_Mail_Proxy);
	if (!pMailProxy){return;}
	std::list<MailHeadVo> * pHeadList = pMailProxy->getHeadListByType(_curMailTab);
	TextFieldTTF * pNameInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Name_TextFeild);
	std::list<MailHeadVo>::iterator iter;
	for (iter = pHeadList->begin(); iter != pHeadList->end(); iter++)
	{
		if (iter->mailId == _curMailId)
		{
			if (pNameInput)
			{
				contentVo.senderName = iter->senderName;
			}
			break;
		}
	}
	resetWritePanel(contentVo);

	CCLayer * pReadMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Read_ContentLayer);
	if (!pReadMailLayer)	{return;}
	pReadMailLayer->setIsVisible(false);
	pReadMailLayer->setIsTouchEnabled(false);
}

void MailView::onSendMail(CCObject * pSender)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}

	std::string strName("");
	std::string strTitle("");
	std::string strContent("");
	TextFieldTTF * pNameInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Name_TextFeild);
	if (pNameInput)
	{
		CCTextFieldTTF *pNameCCTextField = (CCTextFieldTTF*)pNameInput->m_pTrackNode;
		strName = pNameCCTextField->getString();		
		//strName = pNameInput->getString();
		if (strName.empty())
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL036"),ccc3(233,12,25),1.0f);
			return;
		}
	}
	TextFieldTTF * pTitleInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Title_TextFeild);
	if (pTitleInput)
	{
		CCTextFieldTTF *pTitleCCTextField = (CCTextFieldTTF*)pTitleInput->m_pTrackNode;
		if (pTitleCCTextField)
		{
			strTitle = pTitleCCTextField->getString();
		}
		//strTitle = pTitleInput->getString();
	}
	MailTextFieldTTF * pContentInput = (MailTextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Content_TextFeild);
	if (pContentInput)
	{
		CCTextFieldTTF *pContentCCTextField = (CCTextFieldTTF*)pContentInput->m_pTrackNode;
		if (pContentCCTextField)
		{
			strContent = pContentCCTextField->getString();
		}
		//strContent = pContentInput->getString();
	}
	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->onSendMailClick(strName,strTitle,strContent);
	}
}

void MailView::onReturn(CCObject * pSender)
{
	enableInput(false,false,false);

	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}
	pWriteMailLayer->setIsVisible(false);
	pWriteMailLayer->setIsTouchEnabled(false);

	CCLayer * pReadMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Read_ContentLayer);
	if (!pReadMailLayer)	{return;}
	pReadMailLayer->setIsVisible(true);
	pReadMailLayer->setIsTouchEnabled(true);
}

void MailView::onDeleteConfirm(CCObject * pSender)
{
	// set var
	CCMenuItemSprite * pItemImage = (CCMenuItemSprite *)pSender;
	if (pItemImage->getTag() == TAG_BtnImage_DelAll)
	{
		_isDeleteAll = true;
	}
	else if(pItemImage->getTag() == TAG_BtnImage_DelSingle)
	{
		_isDeleteAll = false;
	}

	// confirm
	Confirm * _confirmBuy = new Confirm();
	_confirmBuy->initWithParam(
		ValuesUtil::Instance()->getString("MAIL035").c_str(),
		this,
		menu_selector(MailView::onDeleteOK),
		menu_selector(MailView::onClickCancel));
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	_confirmBuy->release();
}

void MailView::onDeleteOK(CCObject * pSender)
{
	if (_isDeleteAll)
	{
		onDeleteAllMails(0);
	}
	else
	{
		onDeleteMail(0);
	}
	//
	onClickCancel(0);
}

void MailView::onClickCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}

void MailView::enableButton(int tag, bool var)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCMenu * pMenuBtn = (CCMenu *)pContainer->getChildByTag(tag);
	if (pMenuBtn)
	{
		CCMenuItemImage* pBtnImage = (CCMenuItemImage*)pMenuBtn->getChildByTag( TAG_MenuItemImage );
		if(pBtnImage)
		{
			pBtnImage->setIsEnabled(var);
		}
	}
}

void MailView::setTabBtnAndScrollState(bool a[])
{
	if (sizeof(a)/sizeof(bool) < 3)
	{
		return;
	}
	enableButton(TAG_Button_Menu_AllMail,a[0]);
	enableButton(TAG_Button_Menu_SysMail,a[1]);
	enableButton(TAG_Button_Menu_PlayerMail,a[2]);

	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	MailScrollView * pMailScrollView0 = (MailScrollView *)pContainer->getChildByTag(TAG_AllMail_ScrollView);
	if (pMailScrollView0)
	{
		pMailScrollView0->setIsVisible(!a[0]);
		pMailScrollView0->setIsTouchEnabled(!a[0]);
	}
	MailScrollView * pMailScrollView1 = (MailScrollView *)pContainer->getChildByTag(TAG_SysMail_ScrollView);
	if (pMailScrollView1)
	{
		pMailScrollView1->setIsVisible(!a[1]);
		pMailScrollView1->setIsTouchEnabled(!a[1]);
	}
	MailScrollView * pMailScrollView2 = (MailScrollView *)pContainer->getChildByTag(TAG_PlayerMail_ScrollView);
	if (pMailScrollView2)
	{
		pMailScrollView2->setIsVisible(!a[2]);
		pMailScrollView2->setIsTouchEnabled(!a[2]);
	}
}

void MailView::enableInput(bool var1,bool var2,bool var3)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}
	
	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}

	TextFieldTTF * pNameInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Name_TextFeild);
	if (pNameInput)
	{
		pNameInput->setIsTouchEnabled(var1);
		pNameInput->setIsCanBeTouched(var1);
	}
	TextFieldTTF * pTitleInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Title_TextFeild);
	if (pTitleInput)
	{
		pTitleInput->setIsTouchEnabled(var2);
		pTitleInput->setIsCanBeTouched(var2);
	}
	MailTextFieldTTF * pContentInput = (MailTextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Content_TextFeild);
	if (pContentInput)
	{
		pContentInput->setIsTouchEnabled(var3);
		pContentInput->setIsCanBeTouched(var3);
	}
}

void MailView::resetWritePanel(MailContentVo contentVo)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}
	TextFieldTTF * pNameInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Name_TextFeild);
	if (pNameInput)
	{
		pNameInput->setString(contentVo.senderName.c_str());
	}
	TextFieldTTF * pTitleInput = (TextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Title_TextFeild);
	if (pTitleInput)
	{
		pTitleInput->setString(contentVo.mailTitle.c_str());
	}
	MailTextFieldTTF * pContentInput = (MailTextFieldTTF *)pWriteMailLayer->getChildByTag(TAG_Content_TextFeild);
	if (pContentInput)
	{
		pContentInput->setString(contentVo.mailContent.c_str());
	}
}

void MailView::resetReadPanel(MailContentVo contentVo)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pReadMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Read_ContentLayer);
	if (!pReadMailLayer)	{return;}
	CCLabelTTF * pNameInput = (CCLabelTTF *)pReadMailLayer->getChildByTag(TAG_Name_TextFeild);
	if (pNameInput)
	{
		pNameInput->setString(contentVo.senderName.c_str());
	}
	CCLabelTTF * pDateInput = (CCLabelTTF *)pReadMailLayer->getChildByTag(TAG_Date_TextFeild);
	if (pDateInput)
	{
		if (contentVo.sendTime)
		{
			std::string szDate = TimerManage::formatServerTimeToDate(contentVo.sendTime);
			//std::string szDate = getTimeStringByMili((const time_t *)&contentVo.sendTime);
			pDateInput->setString(szDate.c_str());
		}
		else
		{
			pDateInput->setString("");
		}
	}
	CCLabelTTF * pTitleInput = (CCLabelTTF *)pReadMailLayer->getChildByTag(TAG_Title_TextFeild);
	if (pTitleInput)
	{
		pTitleInput->setString(contentVo.mailTitle.c_str());
	}
	CCLabelTTF * pContentInput = (CCLabelTTF *)pReadMailLayer->getChildByTag(TAG_Content_TextFeild);
	if (pContentInput)
	{
		pContentInput->setString(contentVo.mailContent.c_str());
// 		CCRect rect = pContentInput->getTextureRect();
// 		CCPoint pos = Mail_Content_Pos;
// 		pContentInput->setPosition(ccp(pos.x , pos.y + Mail_Content_TextFeild_height/2 - rect.size.height/2));
	}

	// set attach
	MailAttachItem * pAttachItem = (MailAttachItem *)pReadMailLayer->getChildByTag(TAG_Button_Menu_Attach);
	if (pAttachItem)
	{
		pAttachItem->setItem(contentVo);
	}

	if ((contentVo.senderName == "") && (contentVo.mailTitle == "") && (contentVo.mailContent == ""))
	{
		setMailId(0);
	}
}

void MailView::resetScrollPage(int mailtype)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	MailScrollView * pMailScrollView = 0;
	switch(mailtype)
	{
	case (MailConst::MAIL_TYPE_ALL):
		pMailScrollView = (MailScrollView *)pContainer->getChildByTag(TAG_AllMail_ScrollView);
		break;
	case (MailConst::MAIL_TYPE_SYSTEM):
		pMailScrollView = (MailScrollView *)pContainer->getChildByTag(TAG_SysMail_ScrollView);
		break;
	case (MailConst::MAIL_TYPE_PLAYER):
		pMailScrollView = (MailScrollView *)pContainer->getChildByTag(TAG_PlayerMail_ScrollView);
		break;
	}
	if (!pMailScrollView)	{return;	}
	if (pMailScrollView->totalScreens > 1)
	{
		if (pMailScrollView->currentScreen > 1)
		{
			for (int i = pMailScrollView->currentScreen;i>1;i--)
			{
				pMailScrollView->moveToPreviousPage();
			}
			pMailScrollView->currentScreen = 1;
		}
	}	
}

void MailView::setMailId(uint32 mailId)
{
	_curMailId = mailId;
}

void MailView::setCurPage(uint32 page)
{
	_curPage = page;
}

void MailView::setPageText(int curPage,int totalPage)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLabelTTF * pPageText = (CCLabelTTF *)pContainer->getChildByTag(TAG_Page_LabelText);
	if (pPageText)
	{
		char path[32] = {0};
		sprintf(path, "%d/%d",curPage,totalPage);
		pPageText->setString(path);
	}
}

void MailView::showReadLayer()
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCLayer * pWriteMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Write_ContentLayer);
	if (!pWriteMailLayer)	{return;}
	pWriteMailLayer->setIsVisible(false);
	pWriteMailLayer->setIsTouchEnabled(false);

	CCLayer * pReadMailLayer = (CCLayer *)pContainer->getChildByTag(TAG_Read_ContentLayer);
	if (!pReadMailLayer)	{return;}
	pReadMailLayer->setIsVisible(true);	
	pReadMailLayer->setIsTouchEnabled(true);
}

void MailView::showHightLight(bool var,CCPoint pos)
{
	CCLayer * pContainer = (CCLayer *)this->getChildByTag(TAG_Container);
	if (!pContainer)	{return;	}

	CCUIBackground * pHightLight = (CCUIBackground *)pContainer->getChildByTag(TAG_HightLight);
	if (pHightLight)
	{
		pHightLight->setPosition(ccp(pos.x-POSX(114),pos.y+POSX(48)));
		pHightLight->setIsVisible(var);
	}	
}

std::string MailView::getTimeStringByMili(const time_t * time)
{
	std::string szDate("");
	struct tm * stTime = localtime(time); 
	int year = stTime->tm_year + 1900;
	int month = stTime->tm_mon + 1;
	int day = stTime->tm_mday;
	int hour = stTime->tm_hour;
	int min = stTime->tm_min;
	char path[256] = {0};
	sprintf(path,"%d/%d/%d %d:%d", year,month,day,hour,min);
	szDate = path;

	return szDate;
}
