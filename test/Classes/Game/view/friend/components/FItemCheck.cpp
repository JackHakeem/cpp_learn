#include "FItemCheck.h"
#include "FListItem.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "CCUIBackground.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"

const float w_frame = 240.0f;
const float h_frame = 300.0f;

FItemCheck::FItemCheck()
{

}

FItemCheck::~FItemCheck()
{}

bool FItemCheck::initWithParam(FListItem* target, int32 btnCategory)
{
	if (!target || !LayerNode::init())
		return false;

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//
	CCUIBackground* frame = new CCUIBackground();
	frame->initWithSpriteFrame("popuibg/bg1.png", ccp(0,0), ccp(0,0), CCSizeMake(POSX(w_frame), POSX(h_frame)));
	this->addChild(frame, FItemCheckZ_frame, FItemCheckTAG_frame);
	//Doyang 20120712
	frame->release();
	//
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	this->setPosition(ccp((screenSize.width-POSX(w_frame))/2, (screenSize.height-POSX(h_frame))/2));

	//
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(FItemCheck::clickCloseHandler) );//-_btnClose->getContentSize().width/2
		_btnClose->setPosition( ccp(POSX(w_frame-10), POSX(h_frame-10/*-_btnClose->getContentSize().height/2*/)) );

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);

		this->addChild(buttonMenu, FItemCheckZ_btn_X, FItemCheckTAG_btn_X);
	}

	float yoffset = POSX(-10.0f);
	float yinterval = POSX(8.0f);
	if (btnCategory == 0)
	{
		//_btn_info 11
		/*
		{
			CCMenuItemImage *_btn_check = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/friend/check0.png", 
				"assets/ui/friend/check1.png", 
				target, 
				menu_selector(FListItem::applyRemove) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) + yoffset )));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI011").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			if (target->_friendInfo.OF)
			{
				buttonMenu->setIsVisible(false);
			}
		}
		*/
		//_btn_info 12
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,  
				target, 
				menu_selector(FListItem::privateChat) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 2 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI012").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			if (target->_friendInfo.OF)
			{
				//buttonMenu->setIsVisible(false);
			}
		}	
		//_btn_info 13
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				target, 
				menu_selector(FListItem::delPlayer) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 3 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI013").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

		}	
		//_btn_info 14
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				target, 
				menu_selector(FListItem::moveToBlack) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 4 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI014").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

		}	
	}
	else if (btnCategory == 2)
	{
		//_btn_info 11
		/*
		{
			CCMenuItemImage *_btn_check = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/friend/check0.png", 
				"assets/ui/friend/check1.png", 
				target, 
				menu_selector(FListItem::applyRemove) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI011").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			if (target->_friendInfo.OF)
			{
				buttonMenu->setIsVisible(false);
			}
		}
		*/
		//_btn_info 12
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				target, 
				menu_selector(FListItem::privateChat) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 2 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI012").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			
			if (target->_friendInfo.OF)
			{
				buttonMenu->setIsVisible(false);
			}
		}	
		//_btn_info 07
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				target, 
				menu_selector(FListItem::addPlayer) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 3 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI007").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			if (target->_friendInfo.OF)
			{
				buttonMenu->setIsVisible(false);
			}
		}	
		//_btn_info 15
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,  
				target, 
				menu_selector(FListItem::moveFriendOut) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 4 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI015").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(
				buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));
		}	
	}
	else if (btnCategory == 3)
	{
		//_btn_info 11
		/*
		{
			CCMenuItemImage *_btn_check = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/friend/check0.png", 
				"assets/ui/friend/check1.png", 
				target, 
				menu_selector(FListItem::applyRemove) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) + yoffset )));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI011").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			if (target->_friendInfo.OF)
			{
				buttonMenu->setIsVisible(false);
			}
		}
		*/
		//_btn_info 12
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				target, 
				menu_selector(FListItem::privateChat) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 2 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI012").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

			
			if (target->_friendInfo.OF)
			{
				buttonMenu->setIsVisible(false);
			}
		}
		//_btn_info 14
		{

			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				target, 
				menu_selector(FListItem::moveToBlack) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 3 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();	
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI014").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

		}	
		//_btn_info 07
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return false;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,  
				target, 
				menu_selector(FListItem::addPlayer) );
			_btn_check->setPosition(ccp(
				POSX(w_frame) - _btn_check->getContentSize().width,
				POSX(h_frame) - ((_btn_check->getContentSize().height + yinterval) * 4 + yoffset)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_btn_check, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::TipsLayer_FriendCheck);
			this->addChild(buttonMenu, FItemCheckZ_btn_0, FItemCheckTAG_btn_0);
			buttonMenu->release();
		
			CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI007").c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
			pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_check->getContentSize().width/2, 
				buttonMenu->getPosition().y + _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn, 2);
			pLable_btn->setColor(ccc3(254, 189, 0));

		}
	}

	return true;
}

void FItemCheck::clickCloseHandler(CCObject* pSender)
{
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);
}