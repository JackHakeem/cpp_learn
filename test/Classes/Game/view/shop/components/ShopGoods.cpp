#include "ShopGoods.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ValuesUtil.h"
#include "utils/TipHelps.h"
#include "model/com/GoodsToolTips.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

ShopGoods::ShopGoods()
{
	//_myInfo = 0;
	_mySitNum = 0;
	m_page = 0;
	myTip = 0;
}

ShopGoods::~ShopGoods()
{
	if (myTip)
	{
		SAFE_DELETE(myTip);
	}
  //  SAFE_DELETE(myInfo->explain)
    SAFE_DELETE(myInfo)
}

CCPoint ShopGoods::getBgPos()
{
	return this->getPosition();
}

CCPoint ShopGoods::getItemBgPos()
{
	CCNode* bg = this->getChildByTag(RENDERTAG_itembg);
	if (bg)
		return ccpAdd(bg->getPosition(), this->getPosition());
	else
		return ccp(0, 0);
}

bool ShopGoods::initWithParam(ShopGoodsVo* info, int32 sitNum, int32 pageNum)
{
	if (!LayerNode::init())
		return false;

	//
	this->setContentSize(CCSizeMake(POSX(206), POSX(110)));
	
	//
	_myInfo = *info;
	_mySitNum = sitNum;
	m_page = pageNum;
	dispatcher = GameDispatcher::getInstance();	

	if (!myInfo)
		myInfo = new GoodsInfo();

	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(info->goodsid);
	myInfo->explain = GoodsToolTips::getExplain(goodBasic,true);
	//if (!myInfo->explain)
	//	return false;

	if (_myInfo.goodsid != 0)
	{
		//
		CCUIBackground* bg = new CCUIBackground();
		float bg_x = (sitNum%2) ? 12 : 12+206;
		float bg_y = 500 - (sitNum/2+1)*(110 + 3) - 6;
		this->setPosition(ccp(POSX(bg_x), POSX(bg_y)));
		bg->initWithSpriteFrame("ui2.png", ccp(0, 0), ccp(0,0), this->getContentSize());//CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
		this->addChild(bg, RENDERZ_bg, RENDERTAG_bg);
		bg->release();
		//
		SpriteNode* unlock = new SpriteNode();
		unlock->initWithSpriteFrameName("pack/unlock.png");
		float32 width = /*unlock->getTexture()->getContentSize().width*/POSX(98);
		//float32 height = unlock->getTexture()->getContentSize().height;
		this->addChild(unlock, RENDERZ_itembg, RENDERTAG_itembg);	
		//this->setContentSize(unlock->getTexture()->getContentSize());
		float unlock_x = (sitNum%2) ? POSX(12) + width/2 + POSX(6) : POSX(12+206) + width/2 + POSX(6);
		float unlock_y = POSX(500 - (sitNum/2+1)*(110 + 3) + 50);
		unlock->setPosition(ccp(unlock_x - this->getPosition().x, unlock_y - this->getPosition().y));
		unlock->release();
		//
		char itemroad[70];
		//sprintf(itemroad, "goods/%d.png", _myInfo.goodsid);
		sprintf(itemroad, "assets/icon/goods/%d.png", _myInfo.goodsid); // LH20130110
		SpriteNode* item = new SpriteNode();
		//item->initWithSpriteFrameName(itemroad);
		bool var = item->initWithFile(itemroad);
		if (!var)
		{
			item->initWithFile("assets/icon/goods/unknown.png");
		}
		//float32 itemwidth = item->getTexture()->getContentSize().width;
		//float32 itemheight = item->getTexture()->getContentSize().height;
		this->addChild(item, RENDERZ_item, RENDERTAG_item);		
		item->setPosition(ccp(unlock->getPosition().x, unlock->getPosition().y));
		item->release();
		//
		int32 fontsize = _myInfo.name.size()>=5?20:20;
		CCLabelTTF* pLableName = CCLabelTTF::labelWithString(_myInfo.name.c_str(), 
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter, 
			"Arial", 
			POSX(fontsize));
		pLableName->setPosition(ccp(unlock->getPosition().x+width, unlock->getPosition().y+POSX(30)));
		this->addChild(pLableName, RENDERZ_ttfname, RENDERTAG_ttfname);
		pLableName->setColor(ccc3(255, 244, 212));
		//
		char strprice[20];
        sprintf(strprice, "%d", _myInfo.price);
//		itoa(_myInfo.price, strprice, 10);
		strcat(strprice, ValuesUtil::Instance()->getString("BB002").c_str());
		std::string destpricestr = strprice;
		UTF8(destpricestr);
		//strprice += _myInfo->price;
		CCLabelTTF* pLablePrice = CCLabelTTF::labelWithString(destpricestr.c_str(), 
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter, 
			"Arial", 
			POSX(20));
		pLablePrice->setPosition(ccp(unlock->getPosition().x+width, unlock->getPosition().y+POSX(6)));
		this->addChild(pLablePrice, RENDERZ_ttfname, RENDERTAG_ttfname);
		pLablePrice->setColor(ccc3(254, 189, 0));
		//
		//CCMenuItemImage *newButton = new CCMenuItemImage();
		//if (newButton)
		{
			
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite *newButton = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,  menu_selector(ShopGoods::buy));
				newButton->setPosition(ccp(0,0));
				newButton->setScaleX(0.7f);
				newButton->setScaleY(0.7f);
				CCMenu *pMenu = CCMenu::menuWithItems(newButton, NULL);
            
				pMenu->setPosition(ccp(unlock->getPosition().x+ width, unlock->getPosition().y-POSX(30)));
				pMenu->setTouchLayer(TLE::WindowLayer_Shop-1);
				this->addChild(pMenu, RENDERZ_buttonmenu, RENDERTAG_buttonmenu);

				CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SHOP001").c_str(), 
					CCSizeMake(POSX(200), POSX(20)),
					CCTextAlignmentCenter, 
					"Arial", POSX(20));
				pLable_btn->setPosition(ccp(newButton->getContentSize().width/2, 
					newButton->getContentSize().height/2));
				newButton->addChild(pLable_btn, 2);
				pLable_btn->setColor(ccc3(254, 189, 0));
				pLable_btn->setScale(1.3f);
			}
			
		}
	}

	//ижии??TIPS
	if (!myTip)
	{
		myTip = new TipHelps();
	}
	myTip->init(true, TipConst::SHOP);
	myTip->setToolTips(this, this);
	//

	return true;
}
	
void ShopGoods::buy(CCObject* pSender)
{
	struct sdata
	{
		int32 UseType;
		int32 id;
		std::string name;
		int32 price;
	};
	sdata d;
	d.UseType = 1;
	d.id = _myInfo.goodsid;
	d.name = _myInfo.name;
	d.price = _myInfo.price;
	dispatcher->dispatchEvent(GameDispatcher::SHOP_VIEW_CLICK, &d);

//	VIEW_CLICK, {UseType:1/** 1 */, id:sid, name:name,price:price}));
	return;
}

CCSize ShopGoods::getSrcContentSize()
{
	CCSize size = CCSizeMake(0, this->getContentSize().height*2);
    return size;
}