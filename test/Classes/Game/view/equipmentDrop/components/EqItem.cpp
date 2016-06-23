#include "EqItem.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "utils/ColorUtil.h"
#include "model/config/ConfigManager.h"
#include "manager/LangManager.h"
#include "model/appoint/AppointManager.h"
#include "model/scene/MonsterManager.h"
#include "model/scene/SceneManager.h"
#include "view/task/components/TaskType.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsToolTips.h"
#include "model/com/GoodsDynamicManager.h"
#include "utils/TipHelps.h"
#include "model/backpack/vo/GoodsInfo.h"

const float w_frame = 815-155;
const float h_frame = 564-525;
const float FontSize = 30.0f;

EqItem::EqItem()
{
	_goods = 0;
	_txtName = 0;
	_txtFrom = 0;
	_txtMonster = 0;
	_type = 0;
	myTip = 0;
	memset(_dropInfo, 0, sizeof(_dropInfo));
}

EqItem::~EqItem()
{
	if (myInfo)
	{
		delete myInfo;
		myInfo = 0;
	}
	if (myTip)
	{
		delete myTip;
		myTip = 0;
	}
}

CCSize EqItem::getSrcContentSize()
{
    CCSize size = CCSizeMake(POSX(400), 0);
	return size;
}

bool EqItem::init(GoodsBasic* goods)
{
	if (!LayerNode::init())
		return false;

	//
	_goods = goods;
	//
	this->setvisibleSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_6.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(w_frame), POSX(h_frame)));
	this->addChild(_bg1, EqItemZ_bg1, EqItemTAG_bg1);
	_bg1->release();

	//
	float offsetY = POSX(6.0f);
	//_txtName
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(250), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(10, offsetY));
		this->addChild(pLabel, 0);
		pLabel->setColor(ccc3(254, 189, 0));	
        pLabel->setAnchorPoint(ccp(0, 0));

		_txtName = pLabel;
	}
	//_txtFrom
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(365-170+35), offsetY));
		this->addChild(pLabel, 0);
		pLabel->setColor(ccc3(254, 189, 0));	
        pLabel->setAnchorPoint(ccp(0, 0));

		_txtFrom = pLabel;
	}
	//_txtMonster
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(600-170+35), offsetY));
		this->addChild(pLabel, 0);
		pLabel->setColor(ccc3(254, 189, 0));	
        pLabel->setAnchorPoint(ccp(0, 0));

		_txtMonster = pLabel;
	}
	//
	setDropInfo();
	//
	//设置TIPS
	if (!myTip)
	{
		myTip = new TipHelps();
	}
	myTip->init(true, TipConst::SHOP);
	myTip->setToolTips(this, this);

	//
	GoodsInfo* info = new GoodsInfo();
	/*info->sitGrid = goodInfo->a_sitGrid;
	info->id = goodInfo->b_id;*/
	info->goodId = goods->goodId;
	/*info->number = goodInfo->d_number;
	info->strengthen = goodInfo->e_superLv;
	info->stamina = goodInfo->f_stamina;
	info->wrist = goodInfo->g_wrist;
	info->intellect = goodInfo->h_intellect;*/
	//info->explain = 0;
	info->name = goods->goodName;
	info->type = 9;
	info->equip_type = goods->equip_type;
	info->quality = goods->quality; 
	info->explain = GoodsToolTips::getExplain(goods,true);

	this->myInfo = info;
	return true;
}


void EqItem::setDropInfo()
{
	cocos2d::ccColor3B _txtName_textColor = ColorUtil::getGoodColor(_goods->quality);
	_txtName->setColor(_txtName_textColor);
	_txtName->setString(_goods->goodName.c_str());

	vector<std::string> _dropInfoArr;
	ConfigManager::splitStringByCharacterEx(_goods->drop_from, "|", _dropInfoArr);

	//for (int i = 0 ; i < splitStr.size(); i++)
	if (_dropInfoArr.size() >= 2)
	{
		int sceneId = atoi(_dropInfoArr[0].c_str());
		if (sceneId == 1)//委托
		{
			_type = 1;
			_txtFrom->setString(ValuesUtil::Instance()->getString("EQD004").c_str());//"EQD004"
			char strTxtMonster[50];
			sprintf(strTxtMonster, ValuesUtil::Instance()->getString("EQD001").c_str(), _dropInfoArr[1].c_str());
			_txtMonster->setString(strTxtMonster);
			strcpy(_dropInfo, "");
		}else if (sceneId == 2)//淘宝
		{
			_type = 2;
			_txtFrom->setString(ValuesUtil::Instance()->getString("EQD005").c_str());
			int traderType = _goods->equip_type == 4?1:0;//1，披风商人；0，戒指商人 
			std::string strTxtMonster = AppointManager::Instance()->getTraderVoByLev(traderType, atoi(_dropInfoArr[1].c_str()))->name;
			_txtMonster->setString(strTxtMonster.c_str());
			strcpy(_dropInfo, "");
		}else if (sceneId > 1050 && sceneId < 1200)//推图
		{
			std::list<GMProgressVo*> arr = MonsterManager::Instance()->getGroupMonsterByMapId(sceneId);
			int progress = atoi(_dropInfoArr[1].c_str());
			for (std::list<GMProgressVo*>::iterator it = arr.begin(); it != arr.end(); it++)
			{
				GMProgressVo* vo = *it;
				if(vo->id == progress)
				{
					NPCVo* monsterGroup = MonsterManager::Instance()->getMonsterGroup(vo->mgId);
					_txtMonster->setString(monsterGroup->name.c_str());
					break;
				}
			}
			_type = 4;
			_txtFrom->setString(SceneManager::Instance()->getSceneDic(sceneId)->name.c_str());
			
			char str_dropInfo[100];
			sprintf(str_dropInfo, "%d,%d,%d", TaskType::MONSTER, sceneId, progress);
			strcpy(_dropInfo, str_dropInfo);
		}
		else//副本
		{
			_type = 4;
			_txtFrom->setString(SceneManager::Instance()->getSceneDic(sceneId)->name.c_str());
			std::string str_txtMonster = (atoi(_dropInfoArr[1].c_str())==0)?
											ValuesUtil::Instance()->getString("EQD006"):
											ValuesUtil::Instance()->getString("EQD007");
			_txtMonster->setString(str_txtMonster.c_str());

			char str_dropInfo[100];
			sprintf(str_dropInfo, "%d,%d,%d", TaskType::SCENE, sceneId, 0);
			strcpy(_dropInfo, str_dropInfo);		
		}
	}
}