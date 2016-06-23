#include "BankItemInfoShow.h"
#include "BankGoods.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "BankView.h"
#include "manager/PopManage.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

BankItemInfoShow::BankItemInfoShow()
{
	m_alert = 0;
	dieCount = 0.0f;
}


bool BankItemInfoShow::initWithBankGoods(BankGoods* pBankGoods, BankView* bankView)
{
	//
	if (!pBankGoods || !bankView || !pBankGoods->myInfo)
		return false;
	//
	dieCount = 0.0f;
	//
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	m_alert->initWithParam(CCRectMake(0, 0, 0, 0), true);
	this->addChild(m_alert);
	//
	schedule(schedule_selector(BankItemInfoShow::tick));
	//
	GoodsInfo* goodInfo = pBankGoods->myInfo;
	SUBGOODSTIPS& explainTips = goodInfo->explain;

	/*
	if (goodInfo->type == 3)
	{//碎片
		//info->explain = GoodsToolTips::getExplain(goodBasic,false,info->number);
	}
	else if (g_pGoodsDynamicManager->getGoodsDynamic(info->id) != 0)
	{
		info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, g_pGoodsDynamicManager->getGoodsDynamic(info->id));
	}
	else if (goodBasic->type == 2)//装备
	{
		GoodsDynamic* dynamic = g_pGoodsDynamicManager->createDynamic(info, goodBasic);
		if (!dynamic)
		{
			cocos2d::CCLog("!dynamic   BagProxy::updateGoodList");
		}
		info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, dynamic);
	}
	else
	{
		info->explain = GoodsToolTips::getDefaultExplain(goodBasic, info->id, 0);
	}
	*/

	//Ãû×Ö
	UTF8(explainTips.goodName);
	m_alert->addStr(explainTips.goodName, explainTips.color_goodName);
	//Equipment type
	UTF8(explainTips.equiTypeArr);
	m_alert->addStr(explainTips.equiTypeArr, ccc3(255,225,135));
	//Improved level
	if (goodInfo->strengthen>0)
	{
		char str[30];
		sprintf(str, ValuesUtil::Instance()->getString("BB003").c_str(), goodInfo->strengthen);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,225,135));
	}
	else
	{
		std::string tmpstr = ValuesUtil::Instance()->getString("BB004").c_str();
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,225,135));
	}
	//hp
	if (explainTips.hp[1]>0)
	{
		char str[40];
		int subvalue = explainTips.hp[0] - explainTips.hp[1];
		if (subvalue < 0) subvalue = 0;
		sprintf(str, ValuesUtil::Instance()->getString("BB005").c_str(), explainTips.hp[1], subvalue);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(0,225,0));
	}
	//att
	if (explainTips.att[1]>0)
	{
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString("BB006").c_str(), explainTips.att[1], explainTips.att[0] - explainTips.att[1]);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(0,225,0));
	}
	//def
	if (explainTips.def[1]>0)
	{
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString("BB007").c_str(), explainTips.def[1], explainTips.def[0] - explainTips.def[1]);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(0,225,0));
	}
	//magicAtt
	if (explainTips.magicAtt[1]>0)
	{
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString("BB008").c_str(), explainTips.magicAtt[1], explainTips.magicAtt[0] - explainTips.magicAtt[1]);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(0,225,0));
	}
	//magicDef
	if (explainTips.magicDef[1]>0)
	{
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString("BB009").c_str(), explainTips.magicDef[1], explainTips.magicDef[0] - explainTips.magicDef[1]);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(0,225,0));
	}
	//Wear demand
	{
		std::string tmpstr = ValuesUtil::Instance()->getString("BB010").c_str();
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,255,255));
	}
	//Level
	{
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString("BB011").c_str(), explainTips.needLevel);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,225,255));
	}
	//professional
	{
		std::string tmpstr = explainTips.needCareer;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,225,255));
	}
	if (explainTips.quality < 4)//Below the purple quality
	{
		std::string tmpstr = ValuesUtil::Instance()->getString("BB012").c_str();
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,102,0));//
	}
	else
	{
		if (!(explainTips.u_stamina > 0 || explainTips.u_stamina > 0 || explainTips.v_wrist > 0))
		{
			std::string tmpstr = ValuesUtil::Instance()->getString("BB012").c_str();
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(255,102,0));
		}
		if (explainTips.u_stamina > 0)
		{
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString("BB013").c_str(), explainTips.u_stamina);
			std::string tmpstr = str;
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(0,174,255));
		}
		if (explainTips.v_wrist > 0)
		{
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString("BB014").c_str(), explainTips.v_wrist);
			std::string tmpstr = str;
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(0,174,255));
		}
		if (explainTips.w_intellect > 0)
		{
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString("BB015").c_str(), explainTips.w_intellect);
			std::string tmpstr = str;
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(0,174,255));			
		}
	}
	//intro
	{
		std::string tmpstr = explainTips.intro;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,204,0));
	}
	//Sale price
	{
		char str[30];
		sprintf(str, ValuesUtil::Instance()->getString("BB016").c_str(), explainTips.s_sell_price);
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,255,255));
	}
	//The current equipment
	if (explainTips.roleName.size() > 1)
	{
		char str[30];
		sprintf(str, ValuesUtil::Instance()->getString("BB017").c_str(), explainTips.roleName.c_str());
		std::string tmpstr = str;
		UTF8(tmpstr);
		m_alert->addStr(tmpstr, ccc3(255,102,0));
	}

	//Typesetting shows
	m_alert->show();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint bagGoodsPos = pBankGoods->getPosition();
	CCPoint __containerPosition = bankView->getPosition();
	CCPoint p = ccp(bagGoodsPos.x+__containerPosition.x, bagGoodsPos.y+__containerPosition.y);

	CCSize bagGoodsSize = pBankGoods->getContentSize();

	CCSize bgSize = m_alert->getContentSize();


	if (g_pPopManage->getCurPopNum() > 1)
	{
	if (p.x > winSize.width/2)
	{//Items on the right
			this->setPosition(ccp(POSX(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width+4),  POSX(p.y-m_alert->getContentSize().height+40)));
		}
		else
		{//显示在右
			this->setPosition(ccp(POSX(p.x+bagGoodsSize.width/2),  POSX(p.y-m_alert->getContentSize().height+40)));
		}
	}
	else
	{
		if (p.x > winSize.width/2)
		{//物品在右边
			//this->setPosition(ccp(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width+4,  p.y-m_alert->getContentSize().height+40));
			//float disx = winSize.width - p.x - bagGoodsSize.width;
			if (winSize.width - p.x - bagGoodsSize.width/2 > bgSize.width)
			{//显示在右边
				this->setPosition(ccp(POSX(p.x+bagGoodsSize.width/2),  POSX(p.y-m_alert->getContentSize().height+40)));
			}else
			{//显示在左边
				this->setPosition(ccp(POSX(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width+4),  POSX(p.y-m_alert->getContentSize().height+40)));
			}
		}
		else
		{//物品在左边
			//this->setPosition(ccp(p.x+bagGoodsSize.width/2,  p.y-m_alert->getContentSize().height+40));
			if (p.x > bgSize.width)//winSize.width - 
			{//显示在左边
				this->setPosition(ccp(POSX(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width+4),  POSX(p.y-m_alert->getContentSize().height+40)));
			}else
			{//显示在右边			
				this->setPosition(ccp(POSX(p.x+bagGoodsSize.width/2),  POSX(p.y-m_alert->getContentSize().height+40)));
			}
		}	
	}
	return true;
}

void BankItemInfoShow::tick(ccTime dt)
{
	if (dieCount > 3.0f)//three seconds
	{
		this->getParent()->removeChild(this, true);
		return;
	}
	else
	{
		dieCount += dt;
	}
}

void BankItemInfoShow::clickhandle(CCObject* pSender)
{
	return;
}

