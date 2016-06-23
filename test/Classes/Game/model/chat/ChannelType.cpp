#include "ChannelType.h"
#include "utils/ValuesUtil.h"



ChannelType::ChannelType()
{


}

ChannelType::~ChannelType()
{}

uint32 ChannelType::stringToChannel(int name)//std::string
{
	switch(name)
	{
		case ALL_STRING:
			return ALL;
			break;
		case WORLD_STRING:
			return WORLD;
			break;
		case GUILD_STRING:
			return GUILD;
			break;
		case PRIVATE_STRING:
			return PRIVATE;
			break;
		case GM_STRING:
			return GM;
			break;
		case SYS_NOTICE_STRING:
			return SYS_NOTICE;
			break;
		case SYS_ACHIVE_STRING:
			return SYS_ACHIVE;
			break;
		case SYS_CHARGE_STRING:
			return SYS_CHARGE;
			break;
		default:		//其它情况为私聊
			return 99;
	}
}


std::string ChannelType::intFlagToStringName(int name)
{
	switch (name)
	{
		case ALL_STRING:
			return ValuesUtil::Instance()->getString("CHT025");
			break;
		case WORLD_STRING:
			return ValuesUtil::Instance()->getString("CHT026");
			break;
		case GUILD_STRING:
			return ValuesUtil::Instance()->getString("CHT027");
			break;
		case PRIVATE_STRING:
			return ValuesUtil::Instance()->getString("CHT028");
			break;
		case GM_STRING:
			return "GM";
			break;
		case SYS_NOTICE_STRING:
			return ValuesUtil::Instance()->getString("CHT054");
			break;
		case SYS_ACHIVE_STRING:
			return ValuesUtil::Instance()->getString("CHT055");
			break;
		case SYS_CHARGE_STRING:
			return ValuesUtil::Instance()->getString("CHT056");
			break;
		default:		//其它情况为私聊
			return "nothing name";		
	}
}