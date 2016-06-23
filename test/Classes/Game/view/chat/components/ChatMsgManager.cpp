#include "ChatMsgManager.h"
#include "model/chat/ChannelType.h"
#include "utils/ValuesUtil.h"

const int CHANNELMAXSIZE = 30;

ChatMsgManager::ChatMsgManager()
{}

ChatMsgManager::~ChatMsgManager()
{
	for (int i = 0; i < ChatMsgManagerChannelSize; i++)
	{
		messagesData[i].clear();
	}
}

bool ChatMsgManager::addMessage(ChatInfo* chatInfo)
{
	int channel = chatInfo->channel;
	if ((!chatInfo || channel >= ChatMsgManagerChannelSize || channel < 0)
		&& (channel != ChannelType::SYS_NOTICE)
		&& (channel != ChannelType::SYS_ACHIVE)
		&& (channel != ChannelType::SYS_CHARGE))
		return false;

	// LH // 特殊处理。把公告和成就,充值加入【全部】频道中
	if ((channel == ChannelType::SYS_NOTICE) 
		|| (channel == ChannelType::SYS_ACHIVE)
		|| (channel == ChannelType::SYS_CHARGE))
	{
		channel = 0; // 全部频道
	}
	messagesData[channel].push_back(*chatInfo);
	check(channel);
	if (channel != 0)
	{
		messagesData[0].push_back(*chatInfo);
		check(channel);
	}
	else
		return false;//不会进

	return true;
}

void ChatMsgManager::check(int32 channel)
{
	if (channel >= ChatMsgManagerChannelSize || channel < 0)
		return;

	int32 messageSize = messagesData[channel].size();
	int32 deleteSize = messageSize - CHANNELMAXSIZE;
	if (deleteSize > 0)
	{
		std::vector<ChatInfo>::iterator it = messagesData[channel].begin();
		while(deleteSize-- > 0)
		{
			it = messagesData[channel].erase(it);
		}
	}
}

std::list<std::string> ChatMsgManager::splitStringByCharacter( string o_str, string sCharacter )
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

MAPSTRCOLOR ChatMsgManager::getStringColorMapByType(int type, std::string strContent)
{
	MAPSTRCOLOR mapStrColor; 
	std::list<std::string> strList = splitStringByCharacter(strContent, "#");
	if (strList.empty())	{		return mapStrColor;	}	
	if (strList.front() == "")
	{
		strList.pop_front(); // skip first ""
		if (strList.empty())	{		return mapStrColor;	}
	}

	switch (type)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 20: // 公告 notice
		{
			// notice
			if (strList.size() == 1)
			{
				std::string strElem = strList.front();
				mapStrColor.insert(make_pair(strElem,ccc3(255,233,0)));
				strList.pop_front();
				if (strList.empty())	{	break;	}
			}
			else// hero rank
			{
				//2
				std::string strElem = strList.front();
				mapStrColor.insert(make_pair(strElem,ccc3(230,230,230)));
				strList.pop_front();
				if (strList.empty())	{	break;	}
				//3
				strElem = strList.front();
				mapStrColor.insert(make_pair(strElem,ccc3(0xff,0xd7,0x0))); // gold yellow
				strList.pop_front();
				if (strList.empty())	{	break;	}
				//4
				strElem = strList.front();
				ccColor3B color;
				if (strstr(strElem.c_str() , "1"))
				{
					color = ccc3(222,0,222);
				}
				else if (strstr(strElem.c_str() , "2"))
				{
					color = ccc3(0x1e,0x90,0xff);
				}
				else
				{
					color = ccc3(12,233,25);
				}
				mapStrColor.insert(make_pair(strElem,color));
				strList.pop_front();
				if (strList.empty())	{	break;	}
				//5
				strElem = strList.front();
				mapStrColor.insert(make_pair(strElem,color));
				strList.pop_front();
				if (strList.empty())	{	break;	}
			}
		}
		break;
	case 21: // 成就 achieve
		{
			//2
			std::string strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(230,230,230)));
			strList.pop_front();
			if (strList.empty())	{	break;	}
			//3
			strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(0xff,0xd7,0x0))); // gold yellow
			strList.pop_front();
			if (strList.empty())	{	break;	}
			//4
			strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(230,230,230)));
			strList.pop_front();
			if (strList.empty())	{	break;	}
			//5s
			strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(255,233,0)));
			strList.pop_front();
			if (strList.empty())	{	break;	}
		}
		break;
	case 22: // 充值 charge
		{
			//2
			std::string strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(230,230,230)));
			strList.pop_front();
			if (strList.empty())	{	break;	}
			//3
			strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(255,233,0))); 
			strList.pop_front();
			if (strList.empty())	{	break;	}
			//4
			strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(230,230,230)));
			strList.pop_front();
			if (strList.empty())	{	break;	}
			//5
			strElem = strList.front();
			mapStrColor.insert(make_pair(strElem,ccc3(0xff,0x14,0x93)));
			strList.pop_front();
			if (strList.empty())	{	break;	}
		}
		break;
	case 23:
		{

		}
		break;
	default:
		break;
	}
	return mapStrColor;
}

/*
void ChatMsgManager::addColorMessage(int type,MAPSTRCOLOR mapStrColor)
{
	std::map<int ,std::list< MAPSTRCOLOR>>::iterator iter = _messageDic.find(type);
	if (iter != _messageDic.end())
	{
		std::list< MAPSTRCOLOR> colorList = _messageDic.find(type)->second;
		colorList.push_back(mapStrColor);
	}
	else
	{
		std::list< MAPSTRCOLOR> colorList;
		colorList.push_back(mapStrColor);
		_messageDic.insert(make_pair(type,colorList));
	}
}
*/