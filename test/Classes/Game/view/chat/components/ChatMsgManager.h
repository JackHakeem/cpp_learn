#pragma once

#include "utils/Singleton.h"
#include "BaseType.h"
#include "model/chat/ChatInfo.h"

typedef std::map<std::string,ccColor3B> MAPSTRCOLOR;

const int ChatMsgManagerChannelSize = 5;

class ChatMsgManager: public Singleton<ChatMsgManager>
{
public:
	ChatMsgManager();
	~ChatMsgManager();

	bool addMessage(ChatInfo* chatInfo);
	void check(int32 channel);
public:
	std::vector<ChatInfo> messagesData[ChatMsgManagerChannelSize];

	/*
			messagesData[ChannelType.ALL] = [];
			messagesData[ChannelType.WORLD] = [];
			messagesData[ChannelType.GUILD] = [];
			messagesData[ChannelType.PRIVATE] = [];
			messagesData[ChannelType.GM] = [];
	*/


public: // LH20120820 for multiple  color
	std::list<std::string> splitStringByCharacter( string o_str, string sCharacter );
	MAPSTRCOLOR getStringColorMapByType(int type, std::string strContent);
	//void addColorMessage(int type,MAPSTRCOLOR mapStrColor);

	//std::map<int /*type*/,std::list< MAPSTRCOLOR>> _messageDic;
};

