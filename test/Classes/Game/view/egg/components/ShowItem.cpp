#include "ShowItem.h"
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

ShowItem::ShowItem()
{
	_tips = 0;
}

ShowItem::~ShowItem()
{
	if (myInfo)
		delete myInfo;
	if (_tips)
		delete _tips;
}

bool ShowItem::init(std::string picpath)
{
	if (!LayerNode::init())
		return false;
	
	CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
		picpath.c_str(), 
		picpath.c_str(), 
		this, 
		menu_selector(ShowItem::onTimer) );
	_btn->setPosition(ccp(POSX(0), POSX(0)));

	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
	buttonMenu->setPosition( CCPointZero );
	buttonMenu->setTouchLayer(TLE::WindowLayer_egg);
	this->addChild(buttonMenu);	
	_btn->setScale(0.9f);
	
	return true;
}


void ShowItem::onTimer(CCObject* pSender)
{
	if (_tips)
		_tips->rollOverHander();
}


/**
	* ����tips 
	* @param state		����״̬��1�ѿ�/2δ����
	* @param type		�������ͣ�1װ����/2Ӷ����/3��Դ����
	* @param smallType	����С�ࣨ��Ʒ����Ӷ����Ϊ0����Դ��Ϊ��ƷId��
	* @param quality	����Ʒ�ʣ�1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ��
	* 
	*/		
void ShowItem::getEggExplain(int type, int smallType, int quality)
{
	//??TIPS
	if (!_tips)
	{
		_tips = new TipHelps();
	}
	_tips->init(true, TipConst::BANK);
	

	GoodsBasic* goods = new GoodsBasic();

	GoodsInfo* info = new GoodsInfo();
	goods->level = 1;
	goods->career_id = 127;
	char str[20];
	
	if(type == 3){
		sprintf(str, "2_%d_%d_%d",  type, smallType, quality);
		goods->goodId = ChangeKey::getGoodsId(str);
	}else{
		sprintf(str, "1_%d_%d_%d",  type, smallType, quality);
		goods->goodId = ChangeKey::getGoodsId(str);
	}
	goods->goodName = EggManager::Instance()->getEggTips(type,smallType,quality);//EggManager.getInstance().getEggTips(type,smallType,quality).split("|")[0];
	vector<std::string> mapStr;
	ConfigManager::splitStringByCharacterEx( goods->goodName, "|" , mapStr);
	if (mapStr.size() > 1)
	{
		goods->goodName = mapStr[0];
		goods->intro = mapStr[1];
	}

	// ���´��� ΪƷ��ת��
	if(type == 1){
		goods->quality = quality;
	}else if(type == 2){
		if(quality == 101){
			goods->quality = 6;
		}else{
			goods->quality = 4;
		}
	}else{
		if(quality == 101){
			goods->quality = 4;
		}else{
			goods->quality = 3;
		}
	}

	info->explain = GoodsToolTips::getDefaultExplain(goods, info->id, 0);
	
	this->myInfo = info;
	_tips->setToolTips(this, this);
	delete goods;
}