#include "NewEAlert.h"
#include "manager/LayerManager.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "utils/ValuesUtil.h"
#include "events/GameDispatcher.h"
#include "manager/sound/SoundManager.h"
#include "Message.h"

const float FontSize = 30.0f;
const float FontSize2 = 20.0f;
const float weight = 500.0f;
const float height = 240.0f;

NewEAlert::NewEAlert()
{}

NewEAlert::~NewEAlert()
{}

void NewEAlert::show(std::string title, 
	std::string content, 
	std::string btnName, 
	std::string pic_url, 
	int pic_sit, 
	CCObject* target, SEL_MenuHandler fun,
	char*	param, 
	bool isModel)
{
	//delete
	NewEAlert* oldTar = (NewEAlert*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
	if (oldTar)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_NewEAlert, true);
	//new
	NewEAlert* newTar = new NewEAlert();
	newTar->init();
	LayerManager::tipsLayer->addChild(newTar, TipsLayer::TipsLayerZ_NewEAlert, TipsLayer::TipsLayerTAG_NewEAlert);
	//bg 0
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("ui.png", ccp(0, 0), ccp(POSX(6), POSX(7)), CCSizeMake(POSX(weight), POSX(height)));
	newTar->addChild(_bg1, 0, 0);

	//title
	{
		char str[100];
		sprintf(str, "%s", title.c_str());
		CCLabelTTF* htmlText = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(weight), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		htmlText->setPosition(ccp(POSX(weight/2), POSX(200)));
		htmlText->setColor(ccc3(101, 255, 0));
		newTar->addChild(htmlText, 1, 2);		
	}
	//content
	{
		char str[100];
		sprintf(str, "%s", content.c_str());
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(weight*2/3), POSX(FontSize*5)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(weight*2/3), POSX(130)));
		pLable_1->setColor(ccc3(255, 255, 255));
		newTar->addChild(pLable_1, 1, 3);		
	}
	//btnName
	{
		CCMenuItemSprite *_btnConfirm = 0;
		if (target)
		{//for gift frame
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(pNormalSprite && pPressedSprite)
			{
				_btnConfirm = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					target, 
					fun);
				_btnConfirm->setPosition(ccp(POSX(weight/2), POSX(50)));
			}
		}
		else
		{//for new equip frame
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(pNormalSprite && pPressedSprite)
			{
				_btnConfirm = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					newTar, 
					menu_selector(NewEAlert::clickClose) );
				_btnConfirm->setPosition(ccp(POSX(weight/2), POSX(50)));
			}
		}

		if (param)
		{
			_btnConfirm->setTag(*(int *)param);
		}

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnConfirm, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer-1);
		newTar->addChild(buttonMenu, 1, 3);	



		char str[100];
		sprintf(str, "%s", btnName.c_str());
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(weight), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLable_1->setPosition(ccp(_btnConfirm->getContentSize().width/2-POSX(4), _btnConfirm->getContentSize().height/2));
		pLable_1->setColor(ccc3(254, 189, 0));
		_btnConfirm->addChild(pLable_1, 1, 0);		
	}
	//
	{
		SpriteNode* unlock = new SpriteNode();
		unlock->initWithSpriteFrameName("pack/unlock.png");
		float32 unwidth = /*unlock->getTexture()->getContentSize().width*/POSX(98);
		float32 unheight = /*unlock->getTexture()->getContentSize().height*/POSX(98);
		newTar->addChild(unlock, 1, 4);	
		unlock->setPosition(ccp(unwidth/2+POSX(20),POSX(height)-unheight/2-POSX(40)));
		unlock->release();

		char itemroad[70];
		sprintf(itemroad, "%s", pic_url.c_str());
		SpriteNode* item = new SpriteNode();
		bool var = item->initWithFile(itemroad);
		if (!var)
		{
			item->initWithFile("assets/icon/goods/unknown.png");
		}
		
		//float32 itemwidth = item->getTexture()->getContentSize().width;
		//float32 itemheight = item->getTexture()->getContentSize().height;
		item->setPosition(ccp(unwidth/2+POSX(20),POSX(height)-unheight/2-POSX(40)));
		newTar->addChild(item, 2, 5);		
		item->release();
	}

	newTar->setPosition(ccp(POSX((960-weight)/2), POSX((640-height)/2)));
}

void NewEAlert::clickClose(CCObject* pSender)
{
	//

	//close
	NewEAlert* oldTar = (NewEAlert*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
	if (oldTar)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_NewEAlert, true);
	}

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::NEW_ALERT_CLOSE, NULL);

	SoundManager::Instance()->playButtonEffectSound();
}

void NewEAlert::showAutoEquip(GoodsBasic* goodBasic, int mercId, int sitGrid)
{
	std::string title = ValuesUtil::Instance()->getString("BAG006");
	std::string content = ValuesUtil::Instance()->getString("BAG007");
	std::string btnName = ValuesUtil::Instance()->getString("BAG008");
	
	char pic_url[100];
	sprintf(pic_url, "assets/icon/goods/%d.png", goodBasic->goodId);

	show(title, content, btnName, pic_url, 1);
//	var tipText:String = GoodsToolTips.getExplain(goodBasic);
//	var myTip:TipHelps = new TipHelps(true,TipConst.NORMAL);
//	myTip.setToolTips(_skin["_Goods"], tipText);
			
}
