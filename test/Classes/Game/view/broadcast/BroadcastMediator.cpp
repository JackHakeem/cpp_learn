
#include "BroadcastMediator.h"
#include "socket/command/s19/SCMD19A.h"
#include "control/AppFacade.h"
#include "socket/command/s19/SCMD19B.h"
#include "socket/command/s28/SCMD28B.h"
#include "components/NoticeBanner.h"
#include "../chat/ChatMediator.h"
#include "utils/ValuesUtil.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
#include "../notify/NotifyManager.h"
#include "../notify/NotifyType.h"
#include "manager/ViewManager.h"

BroadcastMediator::BroadcastMediator()
{
	if (!g_pSysNotice)
	{
		g_pSysNotice = new NoticeBanner();
	}
}

BroadcastMediator::~BroadcastMediator()
{

}

void BroadcastMediator::handleNotification( int M2Vcmd, char* data )
{
	SCMD19A * pScmd = (SCMD19A *)data;
	std::string strContent("");

	switch(M2Vcmd)
	{
	case BROADCAST_ACHIVE:		//1 – 成就（聊天框）
		{
			std::string strContent("");
			//2
			strContent.append(ValuesUtil::Instance()->getString("CST502"));
			//3
			char path[128] = {0};
			sprintf(path,ValuesUtil::Instance()->getString("CST503").c_str(),pScmd->c_name.c_str());
			strContent.append(path);
			//4
			strContent.append(ValuesUtil::Instance()->getString("CST504"));
			//5
			sprintf(path,ValuesUtil::Instance()->getString("CST505").c_str(),pScmd->d_content.c_str());
			strContent.append(path);

			ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
			if (pChatMediator)
			{
				pChatMediator->SystemAchiveCast(strContent);
			}
		}
		break;
	case BROADCAST_RESPONSE	:		//2 – 使命（横幅）
		{
			/*
			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST521").c_str() , ccc3(12,233,25)));
			//2
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST522").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
			//3
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST523").c_str() , ccc3(255,255,255)));
			//4
		
			char path2[512] = {0};
			sprintf(path2,ValuesUtil::Instance()->getString("CST524").c_str(),	pScmd->d_content.c_str());

			strColorMap.insert(make_pair(path2 , ccc3(255,233,25)));
			//
			g_pSysNotice->addNormalMessage(strColorMap,1);
			*/
		}
		break;
	case BROADCAST_OBJECTS:		//3 – 物品 (帐号ID,物品编号,世界物品编号,物品强化等级)
		{
			std::list<std::string> strList = splitStringByCharacter( pScmd->d_content, ",");
			strList.pop_front();
			int itemIndex = string2Int(strList.front());
			strList.pop_front();
			int itemWorldIndex = string2Int(strList.front());

			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST561").c_str() , ccc3(255,0,255)));
			//2
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST562").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
			//3
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST563").c_str() , ccc3(255,255,255)));

			//4
			std::string strGoods("?");
			GoodsBasic * pGoodsBase = g_pGoodsManager->getBasicGood(itemIndex);
			if (pGoodsBase)
			{
				strGoods = pGoodsBase->goodName;
			}
			ccColor3B color = ccc3(255,0,255);
			if (pGoodsBase)
			{
				color = ColorUtil::getGoodColor(pGoodsBase->quality);
			}
			char path2[512] = {0};
			sprintf(path2,ValuesUtil::Instance()->getString("CST565").c_str(),strGoods.c_str());
			strColorMap.insert(make_pair(path2 , color));
			//5
			//std::string strObj = itemWorldIndex ? ValuesUtil::Instance()->getString("CST601") : ValuesUtil::Instance()->getString("CST602");
			//strColorMap.insert(make_pair(strObj , ccc3(255,255,255)));
			//
			g_pSysNotice->addNormalMessage(strColorMap,1);
		}
		break;
	case BROADCAST_ARENA_WINS:	//4 – 竞技场连胜（横幅）
		{
			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST541").c_str() , ccc3(255,0,0)));
			//2
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST542").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
			//3
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST543").c_str() , ccc3(255,255,255)));
			//4
			char path2[512] = {0};
			sprintf(path2,ValuesUtil::Instance()->getString("CST544").c_str(),pScmd->d_content.c_str());
			strColorMap.insert(make_pair(path2 , ccc3(255,255,0)));
			//5
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST545").c_str() , ccc3(255,255,255)));
			//
			g_pSysNotice->addNormalMessage(strColorMap,1);
		}
		break;
	case BROADCAST_FIRST_FIN:		//5 – 首个完成
		{

		}
		break;
	case BROADCAST_EQUIP_GIVE:		//6  - 紫色或以上物品掉落(包括碎片)	[帐号ID，物品编号,世界物品编号，强化等级(为0)];（横幅）
		{
			std::list<std::string> strList = splitStringByCharacter( pScmd->d_content, ",");
			strList.pop_front();
			int itemIndex = string2Int(strList.front());
			strList.pop_front();
			int itemWorldIndex = string2Int(strList.front());

			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST561").c_str() , ccc3(255,0,0)));
			//2
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST562").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
			//3
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST563").c_str() , ccc3(255,255,255)));
			
			//4
			std::string strGoods("?");
			GoodsBasic * pGoodsBase = g_pGoodsManager->getBasicGood(itemIndex);
			if (pGoodsBase)
			{
				strGoods = pGoodsBase->goodName;
			}
			ccColor3B color = ccc3(255,0,255);
			if (pGoodsBase)
			{
				color = ColorUtil::getGoodColor(pGoodsBase->quality);
			}
			char path2[512] = {0};
			sprintf(path2,ValuesUtil::Instance()->getString("CST564").c_str(),strGoods.c_str());
			strColorMap.insert(make_pair(path2 , color));
			//5
			//std::string strObj = itemWorldIndex ? ValuesUtil::Instance()->getString("CST601") : ValuesUtil::Instance()->getString("CST602");
			//strColorMap.insert(make_pair(strObj , ccc3(255,255,255)));
			//
			g_pSysNotice->addNormalMessage(strColorMap,1);
		}
		break;
	case BROADCAST_EQUIP_MAKE:	//7  - 紫色或以上物品合成		[帐号ID，物品编号,世界物品编号(不为0)，强化等级(为0)];（横幅）
		{
			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST571").c_str() , ccc3(255,0,255)));
			//2
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST572").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
			//3
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST573").c_str() , ccc3(255,255,255)));
			//4
			std::list<std::string> strList = splitStringByCharacter( pScmd->d_content, ",");
			strList.pop_front();
			int itemIndex = string2Int(strList.front());

			std::string strGoods("?");
			GoodsBasic * pGoodsBase = g_pGoodsManager->getBasicGood(itemIndex);
			if (pGoodsBase)
			{
				strGoods = pGoodsBase->goodName;
			}
			ccColor3B color = ccc3(255,0,255);
			if (pGoodsBase)
			{
				color = ColorUtil::getGoodColor(pGoodsBase->quality);
			}
			char path2[512] = {0};
			sprintf(path2,ValuesUtil::Instance()->getString("CST574").c_str(),strGoods.c_str());
			
			strColorMap.insert(make_pair(path2 , color));
			//
			g_pSysNotice->addNormalMessage(strColorMap,1);
		}
		break;
	case BROADCAST_PAOSHANG	:		//8  - 跑商达成３星事件（聊天框）
		{

		}
		break;
	case BROADCAST_JIESHANG:	//9  - 劫商大暴击（聊天框）
		{

		}
		break;
	case BROADCAST_TONGSHANG:	//10 – 通商大暴击（聊天框）
		{

		}
		break;
	case BROADCAST_FIRST_CHARGE:	//11 - 首充（横幅+聊天框）
		{
			std::map<std::string,ccColor3B> strColorMap;
			std::string strContent("");
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST581").c_str() , ccc3(233,133,25)));
			//2
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST582").c_str() , ccc3(233,233,233)));
			strContent.append(ValuesUtil::Instance()->getString("CST582"));
			//3
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST583").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
			strContent.append(path1);
			//4
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST584").c_str() , ccc3(233,233,233)));
			strContent.append(ValuesUtil::Instance()->getString("CST584"));
			//5
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST585").c_str() , ccc3(233,0,0)));
			strContent.append(ValuesUtil::Instance()->getString("CST585"));
			//
			g_pSysNotice->addPriorityMessage(strColorMap,1);


			ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
			if (pChatMediator)
			{
				pChatMediator->SystemChargeCast(strContent);
			}
		}

		break;
	case BROADCAST_WORLD_BOSS:	//12 - 世界Boss（横幅）
		{

		}
		break;
	case BROADCAST_ARENA_TOP10:	//13 - 竞技场前10名争夺战
		{
			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST591").c_str() , ccc3(255,0,0)));
			//2
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST592").c_str() , ccc3(255,255,255)));
			//3
			char path1[512] = {0};
			sprintf(path1,ValuesUtil::Instance()->getString("CST593").c_str(),pScmd->c_name.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(240,0,240)));
			//4
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST594").c_str() , ccc3(255,255,255)));
			//5
			char path2[512] = {0};
			sprintf(path2,ValuesUtil::Instance()->getString("CST595").c_str(),pScmd->d_content.c_str());
			strColorMap.insert(make_pair(path1 , ccc3(0x1e,0x90,0xff)));
			//
			g_pSysNotice->addNormalMessage(strColorMap,1);
		}
		break;
	}
}

void BroadcastMediator::sockSysBroadcastRecived(SCMD19A * data)
{
	sendNotification(Facade_Mediator,AppFacade_BroadCast_Mediator,(char *)data,data->a_type);
}

void BroadcastMediator::sockSysNoticeRecived(SCMD19B * data)
{
	int type = data->b_type;

// low // type for showing location
	int typelow = type & 0x0f;
	switch (typelow)
	{
	case 1:	// 1 = 屏幕上方横幅
		{
			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST701").c_str() , ccc3(12,233,25)));
			//2
			std::string strContent = "#1" + data->c_content;
			strColorMap.insert(make_pair(strContent.c_str() , ccc3(255,255,255)));
			g_pSysNotice->addNormalMessage(strColorMap,data->a_times);
		}
		break;
	case 2:	// 2 = 聊天框
		{
			int times = data->a_times;
			std::string strContent = "#2" + data->c_content;
			while (times)
			{
				ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
				if (pChatMediator)
				{
					pChatMediator->SystemNoticeCast(strContent);
				}
				--times;
			}
		}
		break;
	case 3:	//3 = 屏幕上方横幅+ 聊天框
		{
			// 横幅
			std::map<std::string,ccColor3B> strColorMap;
			//1
			strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST701").c_str() , ccc3(255,133,0)));
			//2
			std::string strContent = "#2" + data->c_content;
			strColorMap.insert(make_pair(strContent.c_str() , ccc3(255,255,255)));
			g_pSysNotice->addNormalMessage(strColorMap,data->a_times);

			// 聊天框
			int times = data->a_times;
			strContent = "#2" + data->c_content;
			while (times)
			{
				ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
				if (pChatMediator)
				{
					pChatMediator->SystemNoticeCast(strContent);
				}
				--times;
			}
		}
	case 4:	//4 = 弹出式	
		{
			
		}
		break;
	default:
		break;
	}

	// high  // type for activity's type,such as world boss or sliver battle...
	int typeHigh = type>>4;
	switch (typeHigh)
	{
	case 0:	// 1 = normal sys notice
		{

		}
		break;
	case 1:	// 1 = world boss
		{
			if ((ViewManager::getInstance()->dungeonEntrysView 
				&& !ViewManager::getInstance()->dungeonEntrysView->getisPop()
				&& (RoleManage::Instance()->roleInfo()->playerBaseInfo.GetmapId() != 1208))
				|| (!ViewManager::getInstance()->dungeonEntrysView))
			{
				if (RoleManage::Instance()->roleLev() >= 40)
				{
					NotifyManager::Instance()->addNotification(NotifyType::NType_WorldBoss);
				}
			}
		}
		break;
	case 2:	// 2 = sliver battle
		{
			if ((ViewManager::getInstance()->dungeonEntrysView 
				&& !ViewManager::getInstance()->dungeonEntrysView->getisPop()
				&& LayerManager::silverMineLayer
				&& !LayerManager::silverMineLayer->getChildByTag(1))
				|| (!ViewManager::getInstance()->dungeonEntrysView ))
			{
				if (RoleManage::Instance()->roleLev() >= 40)
				{
					NotifyManager::Instance()->addNotification(NotifyType::NType_Sliver);
				}
			}
		}
		break;
	case 3:	//3 = other
		{
			
		}
	default:
		break;
	}
}

void BroadcastMediator::sockHeroNoticeRecived(SCMD28B * data)
{
	std::list<SCMD28B::SCMD28BNode> heros = data->heros;
	std::list<SCMD28B::SCMD28BNode>::iterator iter = heros.begin();
	int index = 0;
	for (;iter != heros.end();iter++)
	{
		ccColor3B color;
		switch(index)
		{
		case 0:
			color = ccc3(222,0,222);
			break;
		case 1:
			color = ccc3(0x1e,0x90,0xff);
			break;
		case 2:
			color = ccc3(0x32,0xcd,0x32);
			break;
		}
		// 横幅
		std::map<std::string,ccColor3B> strColorMap;
		std::string strContent("");
		//1
		strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST222").c_str() , ccc3(255,255,255)));
		strContent.append(ValuesUtil::Instance()->getString("CST222"));
		//2
		strColorMap.insert(make_pair(ValuesUtil::Instance()->getString("CST223").c_str() , ccc3(255,0,0)));
		strContent.append(ValuesUtil::Instance()->getString("CST223"));
		//3
		char path1[512] = {0};
		sprintf(path1,ValuesUtil::Instance()->getString("CST224").c_str(),index+1);
		strColorMap.insert(make_pair(path1 , ccc3(255,233,0)));
		strContent.append(path1);
		//4
		char path2[512] = {0};
		sprintf(path2,ValuesUtil::Instance()->getString("CST225").c_str(),iter->b_name.c_str());
		strColorMap.insert(make_pair(path2 , color));
		strContent.append(path2);
		//
		g_pSysNotice->addPriorityMessage(strColorMap,1);

		// 聊天框
		ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
		if (pChatMediator)
		{
			pChatMediator->SystemNoticeCast(strContent);
		}

		++index;
	}
}

std::list<std::string> BroadcastMediator::splitStringByCharacter( string o_str, string sCharacter )
{
	std::list<std::string> str_list; // 存放分割后的字符串
	int comma_n = 0;
	do
	{
		std::string tmp_s = "";
		comma_n = o_str.find( sCharacter );
		if( -1 == comma_n )
		{
			tmp_s = o_str.substr( 0, o_str.length() );
			str_list.push_back( tmp_s );
			break;
		}
		tmp_s = o_str.substr( 0, comma_n );
		o_str.erase( 0, comma_n+1 );
		str_list.push_back( tmp_s );
	}
	while(true);
	return str_list;
}

int BroadcastMediator::string2Int(std::string str)
{
	std::string strTmp = str;
	int len = strTmp.length();
	if (!len)	{	return (-1);}

	bool isNegative = false;

	if (strTmp[0] == '-')
	{
		isNegative = true;
		strTmp.substr(1,strTmp.length()-1);
	}

	len = strTmp.length();
	int result = 0;
	for (int i = 0;i < len;i++)
	{
		result = result * 10 + ( strTmp[i] - '0');
	}

	if (isNegative)
	{
		result = (-1) * result;
	}
	return result;
}
