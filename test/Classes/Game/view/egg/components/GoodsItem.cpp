#include "GoodsItem.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "ChangeSmallType.h"
#include "model/egg/EggManager.h"
#include "ChangeKey.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"
#include "view/egg/EggMediator.h"
#include "model/config/ConfigManager.h"
#include "utils/TipHelps.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/config/ConfigManager.h"
#include "ChangeQuality.h"

const float FontSize = 20.0f;

GoodsItem::GoodsItem()
{
	_dispatcher = GameDispatcher::getInstance();
	_itemType = 1;// 物品框的类型，区分是宝箱里的还是大奖区的（1宝箱，2大奖区）
	_clickNum = 0;
	_eggId = 0;
	_eggName = "";
	_type = 0;		
	_smallType = 0;	
	_state = 0;		
	_quality = 0;	
	_num = 0;		
	_goodsId = 0;	
	_goodsNum = 0;	
	
	_isSelect = 0;	
	_clickNum = 0;	
	_pic = 0;
	_icon = 0;
	_tips = 0;
}

GoodsItem::~GoodsItem()
{}

bool GoodsItem::init()
{
	if (!LayerNode::init())
		return false;
	
	//_icon
	{
		LayerNode* layer = new LayerNode();
		layer->init();
		this->addChild(layer, 0);
		layer->release();
		_icon = layer;
	}
	//_txtNum
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(500), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(60), POSX(10)));
		_icon->addChild(pLabel, 4);
		pLabel->setColor(ccc3(254, 255, 255));	

		_txtNum = pLabel;
	}
	//item_bg_70.png
	//{
	//	SpriteNode* sp = new SpriteNode();
	//	sp->initWithFile("assets/ui/egg/item_bg_70.png");
	//	sp->setAnchorPoint(ccp(0, 0));
	//	_icon->addChild(sp, 0);
	//	sp->release();
	//	_frameContentSize = sp->getContentSize();
	//}

	return true;
}

/** 把蛋蛋放到格子里 */
void GoodsItem::addGoods(EggInfo egg)
{
	_eggId = egg.eggId;
	_type = egg.type;
	_state = egg.state;
	_quality = egg.quality;
	_num = egg.num;
	_goodsId = egg.goodsId;
	_goodsNum = egg.goodsNum;
	_smallType = _type == 3 ? ChangeSmallType::smallType(_goodsId):0;
	_eggName = EggManager::Instance()->getEggTips(_type,_smallType,_quality);//.split("|")[0];

	vector<std::string> mapStr;// = splitStringByCharacter( strTemp, "|" );
	ConfigManager::splitStringByCharacterEx( _eggName, "|" , mapStr);
	if (mapStr.size() > 0)
		_eggName = mapStr[0];

	setIcon(_state,_type,_smallType,_quality);
//	setTips(_state,_type,_smallType,_quality);
	setNum(_num);
	if(_type == 1)
	{
	//	__skin["_fmQuality"].gotoAndStop(_quality+1);
	}else{
//		__skin["_fmQuality"].gotoAndStop(ChangeQuality.getQuality(_type + "_" + _quality)+1);
	}
//	this.addEventListener(MouseEvent.CLICK,onClickHandler);
}

void GoodsItem::setNum(int num)
{
	if(num > 1 && _txtNum)
	{
		char str[10];
		sprintf(str, "%d", num);
		_txtNum->setString(str);
	}
}

/**
	* 设置蛋蛋的显示icon，分为已开和未开两种 
	* @param state		蛋蛋状态（1已开/2未开）
	* @param type		蛋蛋类型（1装备蛋/2佣兵蛋/3资源蛋）
	* @param smallType	蛋蛋小类（物品蛋和佣兵蛋为0，资源蛋为物品Id）
	* @param quality	蛋蛋品质（1小/2大/3蓝色/4紫色/5橙色/6红色）
	*/		
void GoodsItem::setIcon(int state, int type, int smallType, int quality)
{
	char str[20];
	sprintf(str, "%d_%d_%d_%d", state, type, smallType, quality);

	int goodsId = ChangeKey::getGoodsId(str);
	if (goodsId == -1)
		return;

	char path[50];
	sprintf(path, "assets/icon/goods/%d.png", goodsId);

	//_pic
	{
		//CCSprite* p1 = CCSprite::spriteWithSpriteFrameName(path);
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			path,//"assets/ui/egg/item.png",
			path,//"assets/ui/egg/item2.png",
			this, 
			menu_selector(GoodsItem::onTimer) );//menu_selector(0)
		_btn->setPosition(ccp(POSX(0), POSX(0)));
		_btn->setAnchorPoint(ccp(0, 0));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( ccp( POSX(7/2.0f), POSX(7/2.0f)) );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_egg);
		_icon->addChild(buttonMenu, 2);

	}
	
	//_pic = new SpriteNode();
	//_pic->initWithFile(path);
	//_icon->addChild(_pic, 1);
	//_pic->release();
}

/**
	* 洗礼后更改物品 
	* @param goodsId
	* @param goodsNum
	* 
	*/		
void GoodsItem::updateGoods(int goodsId, int goodsNum)
{
	_goodsId = goodsId;
	_goodsNum = goodsNum;
}

void GoodsItem::onTimer(CCObject* pSender)
{
	//_tips->rollOverHander();
	//return;
	//
	if(_type == 3){//资源蛋
		if(RoleManage::Instance()->roleInfo()->playerBaseInfo.lev() < 50 && _goodsId == 7){
			LangManager::msgShow("EGG028");
		}else{
			if(_num == 1){//资源蛋堆叠数有1个时，双击直接拾取
				struct sdata
				{
					int eggId;
					int num;
				};
				sdata d;
				d.eggId = _eggId;
				d.num = 1;
				_dispatcher->dispatchEvent(EggMediator::GET_EGG, &d);
			}else if(_num > 1){//资源蛋堆叠数有多个时，打开数量选择框
				struct sdata
				{
					int eggId;
					std::string name;
					int num;
				};
				sdata d;
				d.eggId = _eggId;
				d.name = _eggName;
				d.num = _num;
				_dispatcher->dispatchEvent(PopEventName::SHOW_UI_EGG_NUMBOX, &d);
			}
		}
	}else{//装备蛋和佣兵蛋
		if(_state == 2){//如果蛋蛋还没有打开，那么发送开蛋的消息
			_dispatcher->dispatchEvent(EggMediator::OPEN_EGG, &_eggId);
		}else if(_state == 1){//如果蛋蛋已经打开，那么打开洗礼框
				struct sdata
				{
					int eggId;
					int goodsId;
					int goodsNum;
				};
				sdata d;
				d.eggId = _eggId;
				d.goodsId = _goodsId;
				d.goodsNum = _goodsNum;
			_dispatcher->dispatchEvent(PopEventName::SHOW_UI_EGG_WASH, &d);
		}
	}	
}


/**
	* 设置tips 
	* @param state		蛋蛋状态（1已开/2未开）
	* @param type		蛋蛋类型（1装备蛋/2佣兵蛋/3资源蛋）
	* @param smallType	蛋蛋小类（物品蛋和佣兵蛋为0，资源蛋为物品Id）
	* @param quality	蛋蛋品质（1小/2大/3蓝色/4紫色/5橙色/6红色）
	* 
	*/		
void GoodsItem::setTips(int state, int type, int smallType, int quality)
{
	//??TIPS
	if (!_tips)
	{
		_tips = new TipHelps();
	}
	_tips->init(true, TipConst::BANK);
	
	//

	GoodsBasic* goods = new GoodsBasic();

	goods->level = 1;
	goods->career_id = 127;//设置成礼包的type

	char str[20];
	sprintf(str, "%d_%d_%d_%d", state, type, smallType, quality);
	goods->goodId = ChangeKey::getGoodsId(str);

	goods->goodName = EggManager::Instance()->getEggTips(type,smallType,quality);//EggManager.getInstance().getEggTips(type,smallType,quality).split("|")[0];
	vector<std::string> mapStr;
	ConfigManager::splitStringByCharacterEx( goods->goodName, "|" , mapStr);
	if (mapStr.size() > 1)
	{
		goods->goodName = mapStr[0];
		goods->intro = mapStr[1];
	}


	// 以下代码 为品质转换/Users/longhui/newsvn/hlqs/trunk/HLQS/HLQS/Classes/Game/view/mainUI/components/SecNavigate.h
	if(type == 1){
		goods->quality = quality;
	}else{
		char str[20];
		sprintf(str, "%d_%d", type, quality);
		goods->quality = ChangeQuality::getQuality(str);
	}
	//_tips.setToolTips(this,GoodsToolTips.getDefaultExplain(goods));
	//if (!this->myInfo)
	//	this->myInfo = new GoodsInfo();
	//this->myInfo->explain = GoodsToolTips::getDefaultExplain(goodBasic, info->id, 0);

	GoodsInfo* info = new GoodsInfo();
	/*info->sitGrid = goodInfo->a_sitGrid;
	info->id = goodInfo->b_id;*/
	info->goodId = goods->goodId;//prototype ID
	/*info->number = goodInfo->d_number;
	info->strengthen = goodInfo->e_superLv;
	info->stamina = goodInfo->f_stamina;
	info->wrist = goodInfo->g_wrist;
	info->intellect = goodInfo->h_intellect;*/
	//info->explain = 0;
	info->name = goods->goodName ;
	info->type = goods->type;
	info->equip_type = goods->equip_type;
	info->quality = goods->quality; 
	if (goods->type == 3)
	{//fragments
		info->explain = GoodsToolTips::getExplain(goods, false, 1);
		// Add count
		char pCount[10];
		sprintf(pCount, "%d", 1);
		CCLabelTTF *pCountLabel = CCLabelTTF::labelWithString(
			pCount,
			CCSizeMake(POSX(20), POSX(20)),
			CCTextAlignmentLeft,
			"Arial",
			POSX(20));
		pCountLabel->setColor(ccc3(255, 255, 255));
		pCountLabel->setAnchorPoint(CCPointZero);
		pCountLabel->setPosition(ccp(POSX(74), POSX(4)));
		this->addChild(pCountLabel);
	}
	else
	{
		info->explain = GoodsToolTips::getDefaultExplain(goods, info->id, 0);
	}

	this->myInfo = info;
	_tips->setToolTips(this, this);





}