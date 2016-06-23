#include "TextInputConfirm.h"
#include "Alert.h"
#include "utils/ValuesUtil.h"

TextInputConfirm::TextInputConfirm()
{}

TextInputConfirm::~TextInputConfirm()
{}

bool TextInputConfirm::initWithParam(std::string str, CCObject* target, SEL_MenuHandler selector, SEL_MenuHandler selector2)
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





	m_alert->addButton(ValuesUtil::Instance()->getString("CF001").c_str(), target, selector);
	m_alert->addButton(ValuesUtil::Instance()->getString("CF002").c_str(), target, selector2);
	m_alert->centerShowTextInput();
	this->setContentSize(m_alert->getContentSize());
	return true;
}

void TextInputConfirm::handleCancel(CCObject* pSender)
{
	if (this->getParent())
		this->getParent()->removeChild(this, true);
}

const char* TextInputConfirm::getString()
{
	const char* s = m_alert->getString();
	return s;
}