#include "TipsEquipCanvas.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "manager/PopManage.h"
#include "utils/ValuesUtil.h"
#include "utils/TipHelps.h"
#include "utils/TipBase.h"
#include "events/GameDispatcher.h"
#include "view/backpack/components/BagGoods.h"
#include "view/bank/components/BankGoods.h"
#include "manager/OverPanelManage.h"
#include "manager/PopManage.h"
#include "model/com/GoodsDynamicManager.h"

TipsEquipCanvas* g_pTipsEquipCanvas = 0;

//#include "chineseMessage.h"

TipsEquipCanvas::TipsEquipCanvas()
{
	m_alert = 0;
	dieCount = 0.0f;
	_dispatcher = 0;
}


bool TipsEquipCanvas::displayTip(CCPoint coordinate, TipBase* tips, int32 type, char* param, TipBase* otherTips)//BagGoods* pBagGoods, BagView* bagView
{
	if (!tips || !tips->myInfo)
		return false;

	g_pOverPanelManage->_pCurBagGoods = (BagGoods *)tips;
	//
	dieCount = 0.0f;
	//
	//
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	m_alert->initWithParam(CCRectMake(0, 0, 0, 0), true);
	this->addChild(m_alert);
	m_alert->release(); // Kenfly 20120204
	//
	schedule(schedule_selector(TipsEquipCanvas::tick));
	//
	GoodsInfo* goodInfo = tips->myInfo;
	SUBGOODSTIPS& explainTips = goodInfo->explain;
	//if (!explainTips)
	//	return false;

	if (goodInfo->type == 3)
	{//碎片
		//名字
		UTF8(explainTips.goodName);
		m_alert->addStr(explainTips.goodName, explainTips.color_goodName);
		//
		//穿戴需求
		{
			std::string tmpstr = ValuesUtil::Instance()->getString("BB010").c_str();
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(255,255,255));
		}
		//等级
		{
			char str[40];
			sprintf(str, ValuesUtil::Instance()->getString("BB011").c_str(), explainTips.needLevel);
			std::string tmpstr = str;
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(255,225,255));
		}
		//职业
		{
			std::string tmpstr = explainTips.needCareer;
			UTF8(tmpstr);
			m_alert->addStr(tmpstr, ccc3(255,225,255));
		}


		//info->explain = GoodsToolTips::getExplain(goodBasic,false,info->number);
	}
	else if (g_pGoodsDynamicManager->getGoodsDynamic(goodInfo->id) != 0)
	{
				//名字
				UTF8(explainTips.goodName);
				m_alert->addStr(explainTips.goodName, explainTips.color_goodName);
				//装备类型
				UTF8(explainTips.equiTypeArr);
				m_alert->addStr(explainTips.equiTypeArr, ccc3(255,225,135));
				//强化等级
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
					sprintf(str, ValuesUtil::Instance()->getString("BB005").c_str(), explainTips.hp[1], explainTips.hp[0] - explainTips.hp[1]);
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
				//穿戴需求
				{
					std::string tmpstr = ValuesUtil::Instance()->getString("BB010").c_str();
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
				//等级
				{
					char str[40];
					sprintf(str, ValuesUtil::Instance()->getString("BB011").c_str(), explainTips.needLevel);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,225,255));
				}
				//职业
				{
					std::string tmpstr = explainTips.needCareer;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,225,255));
				}
				if (explainTips.quality < 4)//低于紫色品?
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
				//出售价格
				{
					char str[30];
					sprintf(str, ValuesUtil::Instance()->getString("BB016").c_str(), explainTips.s_sell_price);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
				//当前装备
				if (explainTips.roleName.size() > 1)
				{
					char str[30];
					sprintf(str, ValuesUtil::Instance()->getString("BB017").c_str(), explainTips.roleName.c_str());
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,102,0));
				}
		//info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, g_pGoodsDynamicManager->getGoodsDynamic(info->id));
	}
	else if (goodInfo->type == 2)//装备
	{
				//名字
				UTF8(explainTips.goodName);
				m_alert->addStr(explainTips.goodName, explainTips.color_goodName);
				//装备类型
				UTF8(explainTips.equiTypeArr);
				m_alert->addStr(explainTips.equiTypeArr, ccc3(255,225,135));
				//强化等级
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
					sprintf(str, ValuesUtil::Instance()->getString("BB005").c_str(), explainTips.hp[1], explainTips.hp[0] - explainTips.hp[1]);
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
				//穿戴需求
				{
					std::string tmpstr = ValuesUtil::Instance()->getString("BB010").c_str();
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
				//等级
				{
					char str[40];
					sprintf(str, ValuesUtil::Instance()->getString("BB011").c_str(), explainTips.needLevel);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,225,255));
				}
				//职业
				{
					std::string tmpstr = explainTips.needCareer;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,225,255));
				}
				if (explainTips.quality < 4)//低于紫色品?
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
				//出售价格
				{
					char str[30];
					sprintf(str, ValuesUtil::Instance()->getString("BB016").c_str(), explainTips.s_sell_price);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
				//当前装备
				if (explainTips.roleName.size() > 1)
				{
					char str[30];
					sprintf(str, ValuesUtil::Instance()->getString("BB017").c_str(), explainTips.roleName.c_str());
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,102,0));
				}
				//GoodsDynamic* dynamic = g_pGoodsDynamicManager->createDynamic(info, goodBasic);
				//if (!dynamic)
				//{
				//	cocos2d::CCLog("!dynamic   BagProxy::updateGoodList");
				//}
				//info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, dynamic);
	}
	else if (type == TipConst::SHOP || goodInfo->type == 3)
	{
				//info->explain = GoodsToolTips::getDefaultExplain(goodBasic, info->id, 0);
				//名字
				UTF8(explainTips.goodName);
				m_alert->addStr(explainTips.goodName, explainTips.color_goodName);
				//
				if (explainTips.chipNum > 0)
				{
					char showchip[20];
					sprintf(showchip, "%d/%d", explainTips.chipNum, clipNeedNum[explainTips.quality]);
					std::string showstr = showchip;
					m_alert->addStr(showstr, ccc3(255,225,135));				
				}
				
				//装备类型
				if(goodInfo->equip_type>=1 && goodInfo->equip_type<=6) 
				{
					UTF8(explainTips.equiTypeArr);
					m_alert->addStr(explainTips.equiTypeArr, ccc3(255,225,135));
				}

				
				//hp
				if (explainTips.hp[1]>0)
				{
					char str[40];
					sprintf(str, ValuesUtil::Instance()->getString("BB005").c_str(), explainTips.hp[1], explainTips.hp[0] - explainTips.hp[1]);
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
				//穿戴需求
				{
					std::string tmpstr = ValuesUtil::Instance()->getString("BB010").c_str();
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
				//等级
				{
					char str[40];
					sprintf(str, ValuesUtil::Instance()->getString("BB011").c_str(), explainTips.needLevel);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,225,255));
				}
				//职业
				{
					std::string tmpstr = explainTips.needCareer;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,225,255));
				}
				
				//intro
				{
					std::string tmpstr = explainTips.intro;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,204,0));
				}
				//出售价格(装备掉落界面)else购买价格
				if (goodInfo->type == 9)
				{
					char str[30];
					sprintf(str, ValuesUtil::Instance()->getString("BB016").c_str(), explainTips.s_sell_price);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
				else
				{
					char str[30];
					sprintf(str, ValuesUtil::Instance()->getString("BB018").c_str(), explainTips.shopPrice);
					std::string tmpstr = str;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,255,255));
				}
	}
	else
	{
				//名字
				UTF8(explainTips.goodName);
				m_alert->addStr(explainTips.goodName, explainTips.color_goodName);
				//
				//intro
				{
					std::string tmpstr = explainTips.intro;
					UTF8(tmpstr);
					m_alert->addStr(tmpstr, ccc3(255,204,0));
				}
	}


	//add button
	switch(type)
	{
	case TipConst::BACKPACK:
		{
			BagGoods* pBagGoods = (BagGoods*)tips;
            
            //Doyang 20120718
            if(!pBagGoods)
            {
                break;
            }
            int goodInfotype = goodInfo->type;
            if (pBagGoods && (goodInfotype == 1 || goodInfotype == 21))
			{//present
				m_alert->addButton(ValuesUtil::Instance()->getString("TP005").c_str(), pBagGoods, menu_selector(BagGoods::OnTimer));
			}
			else if (pBagGoods && (goodInfotype >=6 && goodInfotype <=15))
			{//present
				m_alert->addButton(ValuesUtil::Instance()->getString("TP005").c_str(), pBagGoods, menu_selector(BagGoods::OnTimer));
			}

			if (g_pPopManage->popList[PopEventName::BANK])
			{//bank is opening
				g_pOverPanelManage->sitGrid = pBagGoods->getTag();
				m_alert->addButton(ValuesUtil::Instance()->getString("TP003").c_str(), g_pOverPanelManage, menu_selector(OverPanelManage::buttonBagToBank));

			}

			g_pOverPanelManage->UseType = 3;
			g_pOverPanelManage->sitGrid = pBagGoods->getTag();

			//if (goodInfo->type != 1 && goodInfo->type != 21)
			//	m_alert->addButton(ValuesUtil::Instance()->getString("TP001").c_str(), g_pOverPanelManage, menu_selector(OverPanelManage::throwGoods));
			
			if (pBagGoods->myInfo->type == 2 && 
				!g_pPopManage->popList[PopEventName::BANK] &&
				!g_pPopManage->popList[PopEventName::SHOP])
			{
				m_alert->addButton(ValuesUtil::Instance()->getString("TP002").c_str(), g_pOverPanelManage, menu_selector(OverPanelManage::putOnEquipment_forBtn));
			}

			if (g_pPopManage->popList[PopEventName::SHOP])
			{
				m_alert->addButton(ValuesUtil::Instance()->getString("TP007").c_str(), g_pOverPanelManage, menu_selector(OverPanelManage::sellGoods));
			}
		}
		break;
	case TipConst::BANK:
		{
			BankGoods* pBankGoods = (BankGoods*)tips;
			if (g_pPopManage->popList[PopEventName::BAG])
			{//bag is opening
				g_pOverPanelManage->sitGrid = pBankGoods->getTag();
				m_alert->addButton(ValuesUtil::Instance()->getString("TP004").c_str(), g_pOverPanelManage, menu_selector(OverPanelManage::buttonBankToBag));
			}
		}
		break;
	case TipConst::SHOP:
		{
			//m_alert->addButton("装备", g_pOverPanelManage, menu_selector(OverPanelManage::throwGoods));
		}
		break;
	case TipConst::EQUIPMENT:
		{
			g_pOverPanelManage->sitGrid = tips->myInfo->sitGrid;
			m_alert->addButton(ValuesUtil::Instance()->getString("TP006").c_str(), g_pOverPanelManage, menu_selector(OverPanelManage::putDownEquipment));
		}
		break;
	default:
		break;
	}

	//排版显示
	m_alert->show();
	//设置本宽高
	this->setContentSize(m_alert->getBgSize());

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint p = coordinate;

	CCSize bagGoodsSize = tips->getSrcContentSize();

	CCSize bgSize = m_alert->getContentSize();

	if (g_pPopManage->getCurPopNum() > 1)
	{
		if (p.x > winSize.width/2)
		{//显示在左
			this->setPosition(ccp(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width,  p.y-m_alert->getContentSize().height+bagGoodsSize.height/2));
			//this->setPosition(ccp(p.x-m_alert->getContentSize().width,  p.y-m_alert->getContentSize().height+bagGoodsSize.height/2));
		}
		else
		{//显示在右
			this->setPosition(ccp(p.x+bagGoodsSize.width/2,  p.y-m_alert->getContentSize().height+50));
		}
	}
	else
	{
		if (p.x > winSize.width/2)
		{//物品在右边
			if (winSize.width - p.x - bagGoodsSize.width/2 > bgSize.width)
			{//显示在右边
				this->setPosition(ccp(p.x+bagGoodsSize.width/2,  p.y-m_alert->getContentSize().height+bagGoodsSize.height/2));
			}else
			{//显示在左边
				this->setPosition(ccp(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width+4,  p.y-m_alert->getContentSize().height+bagGoodsSize.height/2));
			}
		}
		else
		{//物品在左边
			if (p.x > bgSize.width)
			{//显示在左边
				this->setPosition(ccp(p.x-bagGoodsSize.width/2-m_alert->getContentSize().width+4,  p.y-m_alert->getContentSize().height+bagGoodsSize.height/2));
			}else
			{//显示在右边			
				this->setPosition(ccp(p.x+bagGoodsSize.width/2,  p.y-m_alert->getContentSize().height+bagGoodsSize.height/2));
			}
		}	
	}

	if (this->getPosition().y < 55)
	{
		float disy = 55 - this->getPosition().y;
		this->setPosition(ccp(this->getPosition().x, this->getPosition().y+disy));
	}

	return true;
}

void TipsEquipCanvas::tick(ccTime dt)
{
	if (dieCount > 3.0f)//三秒
	{
		//this->getParent()->removeChild(this, true);
		return;
	}
	else
	{
		dieCount += dt;
	}
}

void TipsEquipCanvas::clickhandle(CCObject* pSender)
{
	return;
}

