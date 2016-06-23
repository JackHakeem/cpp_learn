#pragma once

#include "BaseType.h"

class ChannelType
{
public:
	ChannelType();
	~ChannelType();
	static uint32 stringToChannel(int name);
	static std::string intFlagToStringName(int name);

public:
	//int ALL;//=0;
	//int ALL_STRING;// =LangManager.getText("CHT025");
	//	
	//int WORLD;//=1;
	//int WORLD_STRING;//=LangManager.getText("CHT026");
	//int WORLD_SHORTCUT;//="(/w)";
	//	
	//int GUILD;//:int=2;
	//int GUILD_STRING;//=LangManager.getText("CHT027");
	//int GUILD_SHORTCUT;//="(/g)";
	//	
	//int PRIVATE;//:int = 3;
	//int PRIVATE_STRING;//=LangManager.getText("CHT028");
	//int PRIVATE_SHORTCUT;//="(/r)";

	//int GM;//=4;
	//int GM_STRING;//="GM";
	static const int ALL=0;
	static const int ALL_STRING = 1000;//ValuesUtil::Instance()->getString("CHT025");//LangManager.getText("CHT025");
	
	static const int WORLD=1;
	static const int WORLD_STRING = 2000;//ValuesUtil::Instance()->getString("CHT026");//LangManager.getText("CHT026");
	static const int WORLD_SHORTCUT =2001;//"(/w)";
	
	static const int GUILD=2;
	static const int GUILD_STRING=3000;//ValuesUtil::Instance()->getString("CHT027");//LangManager.getText("CHT027");
	static const int GUILD_SHORTCUT=3001;//"(/g)";
		
	static const int PRIVATE = 3;
	static const int PRIVATE_STRING=4000;//ValuesUtil::Instance()->getString("CHT028");//LangManager.getText("CHT028");
	static const int PRIVATE_SHORTCUT=4001;//"(/r)";

	static const int GM=4;
	static const int GM_STRING=5000;//"GM";
	
	static const int SYS_NOTICE=20;
	static const int SYS_NOTICE_STRING=21000;

	static const int SYS_ACHIVE=21;
	static const int SYS_ACHIVE_STRING=22000;

	static const int SYS_CHARGE=22;
	static const int SYS_CHARGE_STRING=23000;
};