#include "PoolView.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "view/egg/EggMediator.h"
#include "events/GameDispatcher.h"
#include "RewardPanel.h"
#include "ShowItem.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Connect91Handler.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#endif
const float FontSize = 20.0f;
const float FontSize2 = 24.0f;

bool PoolView::init()
{
	if (!LayerNode::init())
		return false;

	key = 0;
	setNeedBg(NeedBg_NO);

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 0);
		_pContainer->release();
	}

	//title
	{
		//title_1
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/title_1.png");
			_pContainer->addChild(sp, 1);
			sp->setPosition(ccp(POSX(475), POSX(640-27)));
			sp->release();
		}
		//title_2
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/title_2.png");
			_pContainer->addChild(sp, 1);
			sp->setPosition(ccp(POSX(475+110), POSX(640-27)));
			sp->release();
		}
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/title_2.png");
			sp->setFlipY(false);
			sp->setFlipX(true);
			_pContainer->addChild(sp, 1);
			sp->setPosition(ccp(POSX(475-110), POSX(640-27)));
			sp->release();
			
		}
		//title_5.png		
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/title_5.png");
			_pContainer->addChild(sp, 1);
			sp->setPosition(ccp(POSX(125), POSX(640-102)));
			sp->release();
		}
		//title_7.png	
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/title_7.png");
			_pContainer->addChild(sp, 2);
			sp->setPosition(ccp(POSX(125), POSX(640-102)));
			sp->release();
		}
	}
	//main_bg.png
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/main_bg.png");
		_pContainer->addChild(sp, 0);
		sp->setPosition(ccp(POSX(-5), POSX(-10)));
		sp->setAnchorPoint(ccp(0, 0));
		sp->release();
	}
	//water_frame.png
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithFile("assets/ui/egg/water_frame.png", ccp(POSX(28), POSX(640-500)), ccp(0,0), CCSizeMake(POSX(602-28), POSX(500-125)));
		_pContainer->addChild(bg, 1);
		bg->release();	
	}


	//title_3.png心想事成
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/title_3.png");
		_pContainer->addChild(sp, 2);
		sp->setPosition(ccp(POSX(774), POSX(640-130)));
		sp->release();
	}
	//gold_line.png心想事成
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/gold_line.png");
		_pContainer->addChild(sp, 2);
		sp->setPosition(ccp(POSX(774), POSX(640-148)));
		sp->release();
	}
	//water_frame.png for 心想事成
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithFile("assets/ui/egg/water_frame.png", ccp(POSX(610), POSX(640-250)), ccp(0,0), CCSizeMake(POSX(934-610), POSX(250-108)));
		_pContainer->addChild(bg, 1);
		bg->release();	
	}
	//water_frame_bg.png for 心想事成
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithFile("assets/ui/egg/water_frame_bg.png", ccp(POSX(612), POSX(640-250)), ccp(0,0), CCSizeMake(POSX(932-612), POSX(250-108)));
		_pContainer->addChild(bg, 0);
		bg->release();	
	}
	//title_4.png神之恩宠
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/title_4.png");
		_pContainer->addChild(sp, 2);
		sp->setPosition(ccp(POSX(774), POSX(640-284)));
		sp->release();
	}
	//gold_line.png神之恩宠
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/gold_line.png");
		_pContainer->addChild(sp, 2);
		sp->setPosition(ccp(POSX(774), POSX(640-302)));
		sp->release();
	}
	//water_frame.png for 神之恩宠
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithFile("assets/ui/egg/water_frame.png", ccp(POSX(610), POSX(640-498)), ccp(0,0), CCSizeMake(POSX(934-610), POSX(498-260)));
		_pContainer->addChild(bg, 1);
		bg->release();	
	}
	//water_frame_bg.png for 神之恩宠
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithFile("assets/ui/egg/water_frame_bg.png", ccp(POSX(612), POSX(640-500)), ccp(0,0), CCSizeMake(POSX(932-612), POSX(500-260)));
		_pContainer->addChild(bg, 0);
		bg->release();	
	}


	/** 剩余金币*/
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(400), POSX(FontSize2)), CCTextAlignmentLeft, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(POSX(608), POSX(640-610)));
		pLabel->setAnchorPoint(ccp(0, 0));
		_pContainer->addChild(pLabel, 3);
		pLabel->setColor(ccc3(248, 231, 22));	

		_txtGold = pLabel;
	}
	//X
	{
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/popuibg/btn_close_normal.png", 
			"assets/ui/popuibg/btn_close_pressed.png", 
			this, 
			menu_selector(PoolView::close) );
		_btn->setPosition(ccp(POSX(928), POSX(640-28)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_egg);
		_pContainer->addChild(buttonMenu);	
	}
	//item_bg
	{
		//item_bg_98.png
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_98.png");
			sp->setPosition(ccp(POSX(225), POSX(640-315)));
			_pContainer->addChild(sp, 2);
			sp->release();
			sp->setScale(1.2f);
		}
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_98.png");
			sp->setPosition(ccp(POSX(370), POSX(640-315)));
			_pContainer->addChild(sp, 2);
			sp->release();
			sp->setScale(1.2f);
		}
		//item_bg_70.png
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(190), POSX(640-185)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(412), POSX(640-185)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}

		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(105), POSX(640-262)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(497), POSX(640-262)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}

		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(105), POSX(640-360)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(497), POSX(640-360)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}

		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(190), POSX(640-444)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/egg/item_bg_70.png");
			sp->setPosition(ccp(POSX(412), POSX(640-444)));
			_pContainer->addChild(sp, 2);
			sp->release();
		}
	}
	//心愿宝箱_bagMc
	{
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/_btnReward_0.png", 
			"assets/ui/egg/_btnReward_1.png", 
			this, 
			menu_selector(PoolView::bagHandler) );
		_btn->setPosition(ccp(POSX(865), POSX(640-555)));//要配

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_egg);
		_pContainer->addChild(buttonMenu, 1);	

/*		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD003").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));*/		
	}
	//许愿按钮
	{
		std::string strbtn[3] = 
		{
			ValuesUtil::Instance()->getString("EGG031"),
			ValuesUtil::Instance()->getString("EGG032"),
			ValuesUtil::Instance()->getString("EGG033"),
		};

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_egg);
		_pContainer->addChild(buttonMenu, 2);	
		buttonMenu->release();

		for (int i = 0; i < 3; i++)
		{	
			CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/egg/button3_0.png", 
				"assets/ui/egg/button3_1.png",
				"assets/ui/button2.png",
				this, 
				menu_selector(PoolView::plegeHandler) );
			_btn->setPosition(ccp(POSX(112+i*200), POSX(640-553)));//要配
			_btn->setTag(i);

			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(strbtn[i].c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));
	
		}	

		//[10金币] [95金币]  [450金币]
		std::string strbtnlabel[3] = 
		{
			ValuesUtil::Instance()->getString("EGG020"),
			ValuesUtil::Instance()->getString("EGG021"),
			ValuesUtil::Instance()->getString("EGG022"),
		};

		for (int i = 0; i < 3; i++)
		{
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(strbtnlabel[i].c_str(), CCSizeMake(POSX(200), POSX(30.0f)), CCTextAlignmentCenter, "Arial", POSX(26.0f));
			pLabel->setPosition(ccp(POSX(112+i*200), POSX(640-600)));
			_pContainer->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(254, 255, 91));	
		}

	}
	//_txtCapacity 心愿宝箱数量
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(300), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(POSX(778), POSX(640-85)));
		_pContainer->addChild(pLabel, 3);
		pLabel->setColor(ccc3(254, 189, 0));	

		_txtCapacity = pLabel;
	}
	//_btnPay快速充值按钮
	{
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/btn_rank_pressed.png", 
			"assets/ui/egg/btn_rank_pressed.png",
			"assets/ui/egg/btn_rank_pressed.png",
			this, 
			menu_selector(PoolView::payHandler) );
		_btn->setPosition(ccp(POSX(702), POSX(640-550)));
		_btn->setScaleX(1.2f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_egg);
		_pContainer->addChild(buttonMenu, 1);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG034").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(0, 0, 0));
		pLabel->setScaleX(0.8f);
	}
	//
	_myRewardPanel = new RewardPanel();
	_myRewardPanel->init();
	_pContainer->addChild(_myRewardPanel, 6);
	_myRewardPanel->release();
	_myRewardPanel->setPosition(ccp(POSX(700), POSX(640-179)));
	
	//
	_otherRewardPanel = new RewardPanel();
	_otherRewardPanel->init();
	_pContainer->addChild(_otherRewardPanel, 6);
	_otherRewardPanel->release();
	_otherRewardPanel->setPosition(ccp(POSX(626), POSX(640-335)));
	return true;
}

/** 充值*/
void PoolView::payHandler(CCObject* pSender)
{
	//var name:String = GameManager.getInstance().parameters.accname;
	//var payUrl:String = ConfigManager.payUrl;
	//if(ConfigManager.needName){
	//	payUrl += "&username=" + name;
	//}
	//navigateToURL(new URLRequest(payUrl),"_blank");
	//ExternalInterface.call("function goBack({this.parent.window.history.back();}");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    /*	LangManager::msgShow("TMP001");
     return;*/
    callExcharge(1000);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [[Connect91Handler sharedTo91] buyGold:1000];
#endif
}

/** 许愿 */
void PoolView::plegeHandler(CCObject* pSender)
{
	int tag = ((CCNode*)pSender)->getTag();
	switch(tag){
		case 0://1
			{
				struct sdata
				{
					int type;
					int times;
				};
				sdata d;
				d.type = _type;
				d.times = plegeNum[0];
				_dispatcher->dispatchEvent(EggMediator::PLEGE_EGG, &d);
			}
			break;
		case 1://10
			{
				struct sdata
				{
					int type;
					int times;
				};
				sdata d;
				d.type = _type;
				d.times = plegeNum[1];
				_dispatcher->dispatchEvent(EggMediator::PLEGE_EGG, &d);
			}
			break;
		case 2://50
			{
				struct sdata
				{
					int type;
					int times;
				};
				sdata d;
				d.type = _type;
				d.times = plegeNum[2];
				_dispatcher->dispatchEvent(EggMediator::PLEGE_EGG, &d);
			}
			break;
	}
}