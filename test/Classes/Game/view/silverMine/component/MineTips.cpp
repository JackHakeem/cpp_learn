#include "MineTips.h"
#include "MineView.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/CDManage.h"
#include "manager/TimerManage.h"
#include "MineRank.h"
#include "manager/LayerManager.h"
#include "model/silverMine/SilverConst.h"

const float FontSize2 = 20.0f;

MineTips::MineTips()
{
	pContainer = 0;
}

MineTips::~MineTips()
{

}

void MineTips::close(CCObject* pSender)
{
	MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

void MineTips::confirm(CCObject* pSender)
{
	if (!pContainer)
		return;

	switch (m_type)
	{
	case baijin:
		{
			int i = 2;
			pContainer->dispatchEvent(SilverConst::DIG_MINE, &i);
		}
		break;
	case huangjin:
		{
			int i = 1;
			pContainer->dispatchEvent(SilverConst::DIG_MINE, &i);
		}
		break;
	case guwu_gold:
		{
			int i = 0;
			pContainer->dispatchEvent(SilverConst::DO_INSPIRE, &i);		
		}
		break;
	case guwu_lilian:
		{
			int i = 1;
			pContainer->dispatchEvent(SilverConst::DO_INSPIRE, &i);	
		}
		break;
	default:
		break;
	}


	MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}

}

void MineTips::cancel(CCObject* pSender)
{
	MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

bool MineTips::init(int type, MineView* pContainer)
{
	if (!LayerNode::init())
		return false;

	this->pContainer = pContainer;
	m_type = type;


	//m_bg1
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame("ui2.png", ccp(POSX(240), POSX(640-500)),ccp(6,7),
			CCSizeMake(POSX(960-240*2), POSX(500-70)));
		this->addChild(_bg1, 0);
		_bg1->release();
	}
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	this->addChild(blackBG, -1);
	blackBG->setPosition(ccp(0, 0));
	////close
	//{
	//	CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
	//		"assets/ui/popuibg/btn_close_normal.png", 
	//		"assets/ui/popuibg/btn_close_pressed.png", 
	//		this, 
	//		menu_selector(MineTips::close) );
	//	_btn->setPosition(ccp(POSX(960-240), POSX(570)));
	//	_btn->setTag(0);

	//	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
	//	buttonMenu->setPosition( CCPointZero );
	//	buttonMenu->setTouchLayer(TLE::IntervalLayer_silvermine_rank);
	//	this->addChild(buttonMenu);	
	//}
	//confirm
	
		
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(MineTips::confirm) );
			_btn->setPosition(ccp(POSX(480-140), POSX(640-420)));
			_btn->setTag(0);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::IntervalLayer_silvermine_rank-1);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM075").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}
	}
	//cancel
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite, 
				this, 
				menu_selector(MineTips::cancel) );
			_btn->setPosition(ccp(POSX(480+140), POSX(640-420)));
			_btn->setTag(0);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::IntervalLayer_silvermine_rank-1);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM076").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}
	}
	


	switch (m_type)
	{
	case baijin:
		{
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM065").c_str(), CCSizeMake(POSX(400), POSX(40.0f)), CCTextAlignmentCenter, "Arial", POSX(40.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(500)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(240, 210, 68));	
			}
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM066").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(400)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 255, 255));	
			}
			//注:确定后,再次使用,不再进行确认
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM067").c_str(), CCSizeMake(POSX(400), POSX(30.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(300)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 0, 0));	
			}
		}
		break;
	case huangjin:
		{
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM068").c_str(), CCSizeMake(POSX(400), POSX(40.0f)), CCTextAlignmentCenter, "Arial", POSX(40.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(500)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(240, 210, 68));	
			}
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM069").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(400)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 255, 255));	
			}
			//注:确定后,再次使用,不再进行确认
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM067").c_str(), CCSizeMake(POSX(400), POSX(30.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(300)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 0, 0));	
			}
		}
		break;
	case guwu_gold:
		{
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM070").c_str(), CCSizeMake(POSX(400), POSX(40.0f)), CCTextAlignmentCenter, "Arial", POSX(40.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(500)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(240, 210, 68));	
			}
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM071").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(400)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 255, 255));	
			}
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM072").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(350)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 255, 255));	
			}
			//注:确定后,再次使用,不再进行确认
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM067").c_str(), CCSizeMake(POSX(400), POSX(30.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(270)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 0, 0));	
			}
		}
		break;
	case guwu_lilian:
		{
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM073").c_str(), CCSizeMake(POSX(400), POSX(40.0f)), CCTextAlignmentCenter, "Arial", POSX(40.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(500)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(240, 210, 68));	
			}
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM074").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(400)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 255, 255));	
			}
			//
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM072").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(350)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 255, 255));	
			}
			//注:确定后,再次使用,不再进行确认
			{
				CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM067").c_str(), CCSizeMake(POSX(400), POSX(30.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
				_txt->setPosition(ccp(POSX(960/2), POSX(270)));
				this->addChild(_txt, 2);
				_txt->setColor(ccc3(255, 0, 0));	
			}
		}
		break;
	default:
		break;
	}

	return true;
}
