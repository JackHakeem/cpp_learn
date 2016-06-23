#include "HeroRankItem.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"

const float FontSize = 30.0f;

HeroRankItem::HeroRankItem()
{}

HeroRankItem::~HeroRankItem()
{

}

bool HeroRankItem::init(HeroRankVo info)
{
	if (!LayerNode::init())
		return false;

	_heroRankVo = info;

	//CCUIBackground* _bg1 = new CCUIBackground();
	//_bg1->initWithFile("assets/ui/popuibg/bg1.png", ccp(0, 0), ccp(0, 0), CCSizeMake(POSX(POSX(580), POSX(40)));
	//this->addChild(_bg1, HeroRankItemZ_bg, HeroRankItemTAG_bg);

	this->setvisibleSize(CCSizeMake(POSX(580), POSX(50)));
	this->setContentSize(CCSizeMake(POSX(580), POSX(50)));

	float height_offset = 25.0f;
	{
		char str[30];
		sprintf(str, "%d", _heroRankVo.rank);
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(60), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(50), POSX(height_offset)));
		pLable_1->setColor(initColor());
		this->addChild(pLable_1, HeroRankItemZ_rank, HeroRankItemTAG_rank);		
	}
	{
		char str[30];
		if (_heroRankVo.name == "")
		{
			_heroRankVo.name = ValuesUtil::Instance()->getString("JJC034");
		}
		sprintf(str, "%s", _heroRankVo.name.c_str());
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(330), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(350), POSX(height_offset)));
		pLable_1->setColor(initColor());
		this->addChild(pLable_1, HeroRankItemZ_name, HeroRankItemTAG_name);		
	}
	{
		char str[30];
		sprintf(str, "%d", _heroRankVo.lev);
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(80), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(500), POSX(height_offset)));
		pLable_1->setColor(initColor());
		this->addChild(pLable_1, HeroRankItemZ_lv, HeroRankItemTAG_lv);		
	}

	return true;
}

cocos2d::ccColor3B HeroRankItem::initColor()
{
	cocos2d::ccColor3B rnt;
	int rank = _heroRankVo.rank;
	switch(rank){
		case 1:
			rnt = ccc3(182, 7, 234);
			break;
		case 2:
			rnt = ccc3(30, 144, 255);
			break;
		case 3:
			rnt = ccc3(0, 255, 0);
			break;
		default:
			rnt = ccc3(255, 243, 195);
			break;
	}
	return rnt;
}