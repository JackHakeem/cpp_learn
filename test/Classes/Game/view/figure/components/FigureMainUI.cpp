#include "FigureMainUI.h"

FigureMainUI::FigureMainUI()
{
	_btnCount = 0;
}

void FigureMainUI::addTabButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemImage * _btn = 0;
	switch (type)
	{
	case 0:
		_btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/figure/new/back.png", 
			"assets/ui/figure/new/back.png", 
			"assets/ui/figure/new/back.png",
			this, 
			selector);
		break;
	case 1:
		_btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/figure/new/tab1.png", 
			"assets/ui/figure/new/tab2.png", 
			"assets/ui/figure/new/tab2.png",
			this, 
			selector);
		break;
	case 2:
		_btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/pack/ui/btnClose", 
			"assets/ui/btnClose0.png", 
			"assets/ui/btnClose1.png", 
			this, 
			selector);
		break;
	default:
		_btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/figure/new/tab1.png", 
			"assets/ui/figure/new/tab2.png", 
			"assets/ui/figure/new/tab2.png",
			this, 
			selector);
		break;
	}	

	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, NULL);
	buttonMenu->setAnchorPoint(CCPointZero);
	buttonMenu->setIsRelativeAnchorPoint(true);
	_btn->setPosition(CCPointZero);
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();
	float _width = _winSize.width/7;
	buttonMenu->setPosition(ccp(_width*sitNum, _winSize.height-100));
	this->addChild(buttonMenu, TAG_TAB+sitNum);

	++_btnCount;
}

void FigureMainUI::addAllButtons()
{
	addTabButton(0, 0, this, menu_selector(FigureMainUI::clickButtonHandler0));
	addTabButton(1, 1, this, menu_selector(FigureMainUI::clickButtonHandler0));
	addTabButton(1, 2, this, menu_selector(FigureMainUI::clickButtonHandler0));
	addTabButton(1, 3, this, menu_selector(FigureMainUI::clickButtonHandler0));
	addTabButton(1, 4, this, menu_selector(FigureMainUI::clickButtonHandler0));
	addTabButton(0, 5, this, menu_selector(FigureMainUI::clickButtonHandler0));
	addTabButton(2, 6, this, menu_selector(FigureMainUI::clickButtonHandler0));
}

void FigureMainUI::keepButton2State()
{
	// add code here
}

void FigureMainUI::clickButtonHandler0(CCObject *pSender)
{
	this->setIsVisible(false);
	// add code here
}