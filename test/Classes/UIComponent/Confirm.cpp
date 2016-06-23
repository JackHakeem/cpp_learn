#include "Confirm.h"
#include "Alert.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"

Confirm::Confirm()
{}

Confirm::~Confirm()
{}

bool Confirm::initWithParam(std::string str, CCObject* target, SEL_MenuHandler selector, SEL_MenuHandler selector2, string confirmStr )
{
	if (!LayerNode::init())
		return false;
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	else
		this->addChild(m_alert);

	CCSize winsize = CCDirector::sharedDirector()->getWinSize(); 


//	CCPoint pos = convertToNodeSpace(ccp(winsize.width/2, winsize.height/2));
	this->setPosition(ccp(winsize.width/2, winsize.height/2));
	//名字
	std::string explain = str;
	UTF8(explain);
	m_alert->addStr(explain, ccc3(254, 189, 0));

	if ( confirmStr == "" )
	{
		m_alert->addButton(ValuesUtil::Instance()->getString("CF001").c_str(), target, selector);
	} 
	else
	{
		m_alert->addButton( confirmStr.c_str(), target, selector );
	}
	m_alert->addButton(ValuesUtil::Instance()->getString("CF002").c_str(), target, selector2);
	m_alert->centerShow();

	this->setIsTouchEnabled(true);
	return true;
}

void Confirm::handleCancel(CCObject* pSender)
{
	if (this->getParent())
		this->getParent()->removeChild(this, true);
}

void Confirm::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::PreTipsLayer, true);
	CCLayer::onEnter();
}

void Confirm::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

//CCRect Confirm::rect()
//{
//	CCSize s = this->getContentSize();
//	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
//}
//
//bool Confirm::containsTouchLocation(CCTouch* touch)
//{
//	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
//}

bool Confirm::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
//	if ( !containsTouchLocation(touch) ) return false;

	return true;
}