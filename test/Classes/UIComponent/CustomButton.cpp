#include "CustomButton.h"
#include "BaseType.h"

CustomButton::CustomButton(std::string path0,std::string path1,std::string text,ccColor3B &color,CCObject * pSender,SEL_MenuHandler selector)
{
	if (!init())	{return;}
	
	addButton(path0,path1,text,color,this,selector);
}

bool CustomButton::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
    return true;
}

void CustomButton::addButton(std::string path0,std::string path1,std::string text,ccColor3B &color,CCObject * pSender,SEL_MenuHandler selector)
{
	CCMenuItemImage *_pMenuImg = CCMenuItemImage::itemFromNormalImage(
		path0.c_str(), 
		path1.c_str(), 
		pSender, 
		selector);
	_pBtnMenu = CCMenu::menuWithItem(_pMenuImg);
	CCSize sz = _pMenuImg->getContentSize();
	_pBtnMenu->setContentSize(_pMenuImg->getContentSize());

	_pBtnText = CCLabelTTF::labelWithString(text.c_str(),CCSizeMake(sz.width,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
	_pBtnText->setPosition(_pBtnMenu->getPosition());

	this->addChild(_pBtnMenu,Z_BTN,TAG_BTN);
	this->addChild(_pBtnText,Z_TXT,TAG_TXT);
	this->setContentSize(sz);
}
