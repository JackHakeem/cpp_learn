#include "DungeonGUAMsgItem.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s41/SCMD419.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "model/player/RoleManage.h"
#include "KKLabelTTF.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"

const float fontSize = 20.0f;
const float rowSize = 25.0f;

DungeonGUAMsgItem::DungeonGUAMsgItem()
{
	m_iGuanIndex = 0;
}

DungeonGUAMsgItem::~DungeonGUAMsgItem()
{}

DungeonGUAMsgItem* DungeonGUAMsgItem::itemFactory(SCMD419* pPacket, int type, int guanIndex)
{
	DungeonGUAMsgItem* node = new DungeonGUAMsgItem();
	if (guanIndex != -1)
		node->m_iGuanIndex = guanIndex;
	node->init(pPacket, type);

	return node;
}


DungeonGUAMsgItem* DungeonGUAMsgItem::itemFactory(SCMD13D* pPacket, int type, int guanIndex)
{
	DungeonGUAMsgItem* node = new DungeonGUAMsgItem();
	if (guanIndex != -1)
		node->m_iGuanIndex = guanIndex;
	node->init(pPacket, type);

	return node;
}


DungeonGUAMsgItem* DungeonGUAMsgItem::itemRoundFactory(int round)
{
	DungeonGUAMsgItem* node = new DungeonGUAMsgItem();
	node->m_iRound = round;
	node->init();

	return node;
}

DungeonGUAMsgItem* DungeonGUAMsgItem::itemStrFactory(char* content, 
						ccColor3B color , float width,float size)
{
	DungeonGUAMsgItem* node = new DungeonGUAMsgItem();
	node->init(content,color,width,size);

	return node;
}

DungeonGUAMsgItem* DungeonGUAMsgItem::lineFactory()
{
	DungeonGUAMsgItem* node = new DungeonGUAMsgItem();
	node->initline();

	return node;
}

bool DungeonGUAMsgItem::initline()
{
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(fontSize, rowSize, CCSizeMake(400, 50));
	
	//第N轮战斗
	{
		std::string showstr1 = "           ";
	
		kkttf->add(showstr1, ccc3(255,255,255));
	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    kkttf->release();

	return true;	
}



bool DungeonGUAMsgItem::init(char* content, ccColor3B color , float width, float size)
{
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(size, rowSize, CCSizeMake(/*400*/width, 20));
	
	//第N轮战斗
	{
		std::string showstr1 = "";
		showstr1 = content;

		kkttf->add(showstr1, color);
	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    kkttf->release();

	return true;	
}

bool DungeonGUAMsgItem::init()
{
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(fontSize, rowSize, CCSizeMake(400, 50));
	
	//第N轮战斗
	{
		std::string showstr1 = "";
		char str[20];
		sprintf(str, ValuesUtil::Instance()->getString("GUA021").c_str(), m_iRound);
		showstr1 = str;
		 
		kkttf->add(showstr1, ccc3(250, 254, 200));

		//showstr1 = "                                           ";
		//kkttf->add(showstr1, ccc3(250, 254, 200));
	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    kkttf->release();

	return true;	
}

bool DungeonGUAMsgItem::init(SCMD419* packet, int type)
{
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(fontSize, rowSize, CCSizeMake(400, 50));
	
	//第N关 
	if (type == 0)
	{
		std::string showstr1 = "";
		char str[20];
		sprintf(str, ValuesUtil::Instance()->getString("GUA026").c_str(), m_iGuanIndex);
		showstr1 = str;

		kkttf->add(showstr1, ccc3(242, 203, 83));

	}
	//每个人+经验
	else if (type == 1)
	{
		int addexp = -1;
		//if(plusexp>0) {log name}
		for (std::list<SCMD419::SCMD419Node2>::iterator it = packet->_exps.begin(); it != packet->_exps.end(); it++)
		{
			SCMD419::SCMD419Node2& node = *it;
			if (node._plusExp <= 0)
				continue;

			if (addexp == -1)
				addexp = node._plusExp;

			PlayerInfoVo *pPlayerInfo = RoleManage::Instance()->getMercenary(node._id);
			if (!pPlayerInfo || pPlayerInfo->playerBaseInfo.name.size() <= 0)
				continue;

			char str[50];
			sprintf(str, "%s ", pPlayerInfo->playerBaseInfo.name.c_str());
			std::string showstr1 = str;
			kkttf->add(showstr1, ccc3(251, 251, 251));
		}
		//addexp
		if (addexp > 0)
		{
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString("GUA027").c_str(), addexp);
			std::string showstr2 = str;
			kkttf->add(showstr2, ccc3(23, 250, 12));
		}
	}
	//加物品
	else if (type == 2)
	{
		int itemcount = 0;
		for (std::list<SCMD419::SCMD419Node>::iterator it = packet->_rewards.begin(); it != packet->_rewards.end(); it++)
		{
			SCMD419::SCMD419Node node = *it;
			//if (node._goodsId != 3 )
			{
				itemcount++;
			}
		}
		if (itemcount > 0)
		{
			{
				char str[40];
				sprintf(str, ValuesUtil::Instance()->getString("GUA028").c_str());
				std::string showstr1 = str;
				kkttf->add(showstr1, ccc3(242, 203, 83));		
			}

			for (std::list<SCMD419::SCMD419Node>::iterator it = packet->_rewards.begin(); it != packet->_rewards.end(); it++)
			{
				SCMD419::SCMD419Node node = *it;
				if (node._goodsId >= 100 )
				{
					GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( node._goodsId );
					if (goodBasic)
					{
						char str[40];
						sprintf(str, ValuesUtil::Instance()->getString("GUA018").c_str(), goodBasic->goodName.c_str());
						std::string showstr1 = str;
						kkttf->add(showstr1, ColorUtil::getGoodColor(goodBasic->quality));				
					}			
				}
				else if (node._goodsId == 1)
				{
					char str[40];
					sprintf(str, "%s%d", ValuesUtil::Instance()->getString("WBS116").c_str(), node._goodsNum);
					std::string showstr1 = str;
					kkttf->add(showstr1, ccc3(0, 255, 255));		
				}
				else if (node._goodsId == 3)
				{
					char str[40];
					sprintf(str, "%s%d", ValuesUtil::Instance()->getString("WBS118").c_str(), node._goodsNum);
					std::string showstr1 = str;
					kkttf->add(showstr1, ccc3(0, 255, 200));		
				}
			}
				
		}
		else
		{
			kkttf->release();
			return false;
		}


	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    kkttf->release();

	return true;
}

bool DungeonGUAMsgItem::init(SCMD13D* packet, int type)
{
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(fontSize, rowSize, CCSizeMake(400, 50));
	
	//第N关 
	if (type == 0)
	{
		std::string showstr1 = "";
		char str[20];
		sprintf(str, ValuesUtil::Instance()->getString("GUA026").c_str(), m_iGuanIndex);
		showstr1 = str;

		kkttf->add(showstr1, ccc3(242, 203, 83));

	}
	//每个人+经验
	else if (type == 1)
	{
		int addexp = -1;
		//if(plusexp>0) {log name}
		for (std::list<SCMD13D::SCMD13DNode2>::iterator it = packet->_exps.begin(); it != packet->_exps.end(); it++)
		{
			SCMD13D::SCMD13DNode2& node = *it;
			if (node._plusExp <= 0)
				continue;

			if (addexp == -1)
				addexp = node._plusExp;

			PlayerInfoVo *pPlayerInfo = RoleManage::Instance()->getMercenary(node._id);
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString("GUA017").c_str(), pPlayerInfo->playerBaseInfo.name.c_str());
			std::string showstr1 = str;
			kkttf->add(showstr1, ccc3(251, 251, 251));
		}
		//addexp
		if (addexp > 0)
		{
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString("GUA027").c_str(), addexp);
			std::string showstr2 = str;
			kkttf->add(showstr2, ccc3(23, 250, 12));
		}
	}
	//加物品
	else if (type == 2)
	{
		int itemcount = 0;
		for (std::list<SCMD13D::SCMD13DNode>::iterator it = packet->_rewards.begin(); it != packet->_rewards.end(); it++)
		{
			SCMD13D::SCMD13DNode node = *it;
			//if (node._goodsId != 3 )
			{
				itemcount++;
			}
		}
		if (itemcount > 0)
		{
			{
				char str[40];
				sprintf(str, ValuesUtil::Instance()->getString("GUA028").c_str());
				std::string showstr1 = str;
				kkttf->add(showstr1, ccc3(242, 203, 83));		
			}

			for (std::list<SCMD13D::SCMD13DNode>::iterator it = packet->_rewards.begin(); it != packet->_rewards.end(); it++)
			{
				SCMD13D::SCMD13DNode node = *it;
				if (node._goodsId >= 100 )
				{
					GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( node._goodsId );
					if (goodBasic)
					{
						char str[40];
						sprintf(str, ValuesUtil::Instance()->getString("GUA018").c_str(), goodBasic->goodName.c_str());
						std::string showstr1 = str;
						kkttf->add(showstr1, ColorUtil::getGoodColor(goodBasic->quality));				
					}			
				}
				else if (node._goodsId == 1)
				{
					char str[40];
					sprintf(str, "%s%d", ValuesUtil::Instance()->getString("WBS116").c_str(), node._goodsNum);
					std::string showstr1 = str;
					kkttf->add(showstr1, ccc3(0, 255, 255));		
				}
				else if (node._goodsId == 3)
				{
					char str[40];
					sprintf(str, "%s%d", ValuesUtil::Instance()->getString("WBS118").c_str(), node._goodsNum);
					std::string showstr1 = str;
					kkttf->add(showstr1, ccc3(0, 255, 200));		
				}
			}
				
		}
		else
		{
			kkttf->release();
			return false;
		}


	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    kkttf->release();

	return true;
}