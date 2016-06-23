#include "SceneChatItem.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "model/player/RoleManage.h"
#include "KKLabelTTF.h"
#include "ChatMsgManager.h"

const float FontSize = 20.0f;
const int ContentFontsMax = 40;
SceneChatItem::SceneChatItem()
{}

SceneChatItem::~SceneChatItem()
{}

bool SceneChatItem::init(ChatInfo& chatInfo)
{
	bool testLayerFlag = false;
	static int iflag = 0;
	if (!LayerNode::init())
		return false;
    
	m_chatInfo = chatInfo;
	
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));
    
	float itemHeight = 0;
    
	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(FontSize, 26.0f, CCSizeMake(/*260*/560 - 200, /*220*/90));
    
	//内容
	int contentRow = (m_chatInfo.content.size() < POSX(27*3))?1:2;
	//float nameFontSize = m_chatInfo.fromName.size()/3;
    
	float yUpAll = (contentRow==1)?0.0f:0.0f;
    
	itemHeight += contentRow*(FontSize/2)-FontSize;
	if (contentRow==1)
	{
		itemHeight+=FontSize;
	}
	//私聊名 世界 
	{
        
		std::string showstr1 = "";
		ccColor3B useColor;
		if (m_chatInfo.isPerson)
		{
			showstr1 = ValuesUtil::Instance()->getString("CHT046");
			useColor = ccc3(255, 68, 255);//淡紫
		}
		else
		{
			switch (m_chatInfo.channel)
			{
                case 1://世界
                    showstr1 = ValuesUtil::Instance()->getString("CHT044");
                    useColor = ccc3(51, 233, 242);//浅蓝
                    break;
				case 2://军团
					showstr1 = ValuesUtil::Instance()->getString("CHT045");
					useColor = ccc3(115, 226, 82);//绿色
					break;
                case 0://系统
                    showstr1 = ValuesUtil::Instance()->getString("CHT050");
                    useColor = ccc3(115, 226, 82);//绿色
                    break;
				case 20://公告
					showstr1 = ValuesUtil::Instance()->getString("CHT054");
					useColor = ccc3(12, 233, 25);//绿色
					break;
				case 21://成就
					showstr1 = ValuesUtil::Instance()->getString("CHT055");
					useColor = ccc3(255, 0, 0);//红色
					break;
				case 22://充值
					showstr1 = ValuesUtil::Instance()->getString("CHT056");
					useColor = ccc3(255, 0, 255);//紫色
					break;
                default://其他，公会GM等等还没做
                    showstr1 = ValuesUtil::Instance()->getString("CHT050");
                    useColor = ccc3(255, 255, 255);//白色
                    break;
			}
		}
        
		char showstr2[20];
		sprintf(showstr2, "[%s]:", showstr1.c_str());
		std::string showstr3 = showstr2;
		kkttf->add(showstr3, useColor);
	}
	//名字
	if (m_chatInfo.fromName.size() > 0)
	{
		CCLabelTTF* label=0;
		char showstr1[50];
		if (m_chatInfo.isPerson)
		{//你对谁说  谁对你说
			if (m_chatInfo.fromId == RoleManage::Instance()->_accountInfo.accountId)
			{//你对谁说
				
				sprintf(showstr1, ValuesUtil::Instance()->getString("CHT051").c_str(), m_chatInfo.toName.c_str());
                
			}
			else
			{//谁对你说
				sprintf(showstr1, ValuesUtil::Instance()->getString("CHT052").c_str(), m_chatInfo.fromName.c_str());
			}
		}
		else
		{//非私聊
			sprintf(showstr1, "%s:", m_chatInfo.fromName.c_str());
		}
		std::string showstr3 = showstr1;
		kkttf->add(showstr3, ccc3(235, 224, 86));
		//label = CCLabelTTF::labelWithString(showstr1, 
		//	CCSizeMake(POSX(860), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		//		
		//label->setColor(ccc3(235, 224, 86));//淡黄色
		//label->setAnchorPoint(ccp(0, 0));
		//label->setPosition(ccp(POSX(70), POSX(itemHeight+FontSize+contentRow*(FontSize/2))));	//每加一行内容，就要上升0.5行FontSize值
		//this->addChild(label, 1);	
	}
    
	{//-m_chatInfo.fromName.size()/3  FontSize*(ContentFontsMax)
		//CCLabelTTF* label = CCLabelTTF::labelWithString(m_chatInfo.content.c_str(), 
		//	CCSizeMake(POSX(ContentFontsMax*20.0f), POSX(FontSize*2)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		//label->setColor(ccc3(255, 255, 255));
		//label->setAnchorPoint(ccp(0.5, 0.5));
		//int ssize = m_chatInfo.content.size();
		//CCSize cc = label->getTexture()->getContentSize();
		//if (m_chatInfo.content.size() < 27*3)
		//	label->setPosition(ccp(POSX(960/2-30.0f), POSX(10.0f+itemHeight+contentRow*(FontSize/2))));//+nameFontSize*20.0f
		//else
		//	label->setPosition(ccp(POSX(960/2-30.0f), POSX(itemHeight+contentRow*(FontSize/2))));	//+nameFontSize*20.0f
		//this->addChild(label, 1);

		ccColor3B color1 = ccc3(255, 255, 255);
		switch(m_chatInfo.channel)
		{
		case 0:
			color1 = ccc3(255, 255, 255);
			kkttf->add(m_chatInfo.content, color1);
			break;
		case 1:
			color1 = ccc3(255, 255, 255);
			kkttf->add(m_chatInfo.content, color1);
			break;
		case 20:
			{
				MAPSTRCOLOR mapStrColor = ChatMsgManager::Instance()->getStringColorMapByType(20,chatInfo.content);
				MAPSTRCOLOR::iterator iter = mapStrColor.begin();
				for (; iter != mapStrColor.end(); iter++)
				{
					int len = iter->first.length();
					std::string strElem = iter->first.substr(1,len-1);
					kkttf->add(strElem, iter->second);
				}				
			}
			break;
		case 21:
			{
				MAPSTRCOLOR mapStrColor = ChatMsgManager::Instance()->getStringColorMapByType(21,chatInfo.content);
				MAPSTRCOLOR::iterator iter = mapStrColor.begin();
				for (; iter != mapStrColor.end(); iter++)
				{
					int len = iter->first.length();
					std::string strElem = iter->first.substr(1,len-1);
					kkttf->add(strElem, iter->second);
				}				
			}
			break;
		case 22:
			{
				MAPSTRCOLOR mapStrColor = ChatMsgManager::Instance()->getStringColorMapByType(22,chatInfo.content);
				MAPSTRCOLOR::iterator iter = mapStrColor.begin();
				for (; iter != mapStrColor.end(); iter++)
				{
					int len = iter->first.length();
					std::string strElem = iter->first.substr(1,len-1);
					kkttf->add(strElem, iter->second);
				}	
			}
			break;
		default:
			color1 = ccc3(255, 255, 255);
			kkttf->add(m_chatInfo.content, color1);
			break;
		}


	}
	//测试用颜色层
	if (testLayerFlag)
	{
		CCLayerColor* contentLayer = 0;
		if (iflag == 1)
		{
			contentLayer = CCLayerColor::layerWithColorWidthHeight(
                                                                   ccc4(250, 0, 0, 200), 
                                                                   POSX(860), 
                                                                   POSX(FontSize*(3)));
			iflag = 2;
		}	
		else
		{
			contentLayer = CCLayerColor::layerWithColorWidthHeight(
                                                                   ccc4(0, 255, 0, 200), 
                                                                   POSX(860), 
                                                                   POSX(FontSize*(3)));	
			iflag = 1;
		}
        
		contentLayer->setAnchorPoint(ccp(0,0));
		contentLayer->setIsRelativeAnchorPoint(true);
		this->addChild(contentLayer, 0);		
	}
    
	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight)); // 
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    
	kkttf->release();//jae0813
	return true;
}

/*
#include "SceneChatItem.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "model/player/RoleManage.h"
#include "KKLabelTTF.h"

const float FontSize = 20.0f;
const int ContentFontsMax = 16;
SceneChatItem::SceneChatItem()
{}

SceneChatItem::~SceneChatItem()
{}

bool SceneChatItem::init(ChatInfo& chatInfo)
{
	bool testLayerFlag = false;
	static int iflag = 0;
	if (!LayerNode::init())
		return false;

	m_chatInfo = chatInfo;

	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	float itemHeight = 0;
    
    KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(FontSize, 26.0f, CCSizeMake(320, 120));

	int onerow = POSX(17);
	//内容
	int contentRow = (m_chatInfo.content.size() < onerow*3)?1:2;
	if (m_chatInfo.content.size() > POSX(63))
		contentRow = 3;
	float nameFontSize = m_chatInfo.fromName.size()/3;

	float yUpAll = (contentRow==1)?0.0f:0.0f;

	itemHeight += contentRow*(FontSize/2)-FontSize;
	if (contentRow==1)
	{
		itemHeight+=FontSize;
	}
	//私聊名 世界 
	{

		std::string showstr1 = "";
		ccColor3B useColor;
		if (m_chatInfo.isPerson)
		{
			showstr1 = ValuesUtil::Instance()->getString("CHT046");
			useColor = ccc3(255, 68, 255);//淡紫
		}
		else
		{
			switch (m_chatInfo.channel)
			{
			case 1://世界
				showstr1 = ValuesUtil::Instance()->getString("CHT044");
				useColor = ccc3(51, 233, 242);//浅蓝
				break;
			case 0://系统
				showstr1 = ValuesUtil::Instance()->getString("CHT050");
				useColor = ccc3(115, 226, 82);//绿色
				break;
			default://其他，公会GM等等还没做
				showstr1 = ValuesUtil::Instance()->getString("CHT050");
				useColor = ccc3(255, 255, 255);//白色
				break;
			}
		}
        char showstr2[20];
		sprintf(showstr2, "[%s]:", showstr1.c_str());
		std::string showstr3 = showstr2;
		kkttf->add(showstr3, useColor);
	}
	//名字
	if (m_chatInfo.fromName.size() > 0)
	{
		CCLabelTTF* label=0;
		char showstr1[50];
		if (m_chatInfo.isPerson)
		{//你对谁说  谁对你说
			if (m_chatInfo.fromId == RoleManage::Instance()->_accountInfo.accountId)
			{//你对谁说
				
				sprintf(showstr1, ValuesUtil::Instance()->getString("CHT051").c_str(), m_chatInfo.toName.c_str());

			}
			else
			{//谁对你说
				sprintf(showstr1, ValuesUtil::Instance()->getString("CHT052").c_str(), m_chatInfo.fromName.c_str());
			}
		}
		else
		{//非私聊
			sprintf(showstr1, "%s:", m_chatInfo.fromName.c_str());
		}
        std::string showstr3 = showstr1;
		kkttf->add(showstr3, ccc3(235, 224, 86));
	}

	{//-m_chatInfo.fromName.size()/3  FontSize*(ContentFontsMax)

        kkttf->add(m_chatInfo.content, ccc3(255, 255, 255));
	}
	//测试用颜色层
	if (testLayerFlag)
	{
		CCLayerColor* contentLayer = 0;
		if (iflag == 1)
		{
			contentLayer = CCLayerColor::layerWithColorWidthHeight(
			ccc4(250, 0, 0, 200), 
			POSX(860), 
			POSX(FontSize*(3)));
			iflag = 2;
		}	
		else
		{
			contentLayer = CCLayerColor::layerWithColorWidthHeight(
			ccc4(0, 255, 0, 200), 
			POSX(860), 
			POSX(FontSize*(3)));	
			iflag = 1;
		}

		contentLayer->setAnchorPoint(ccp(0,0));
		contentLayer->setIsRelativeAnchorPoint(true);
		this->addChild(contentLayer, 0);		
	}

//	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), POSX(kkttf->m_fFontRealHeight*(kkttf->m_iRow+1))));
	this->setvisibleSize(this->getContentSize());

	return true;
}
*/