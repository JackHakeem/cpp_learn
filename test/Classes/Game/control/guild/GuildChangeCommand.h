#ifndef _GuildChangeCommand_H_
#define _GuildChangeCommand_H_

#include "mvc/SimpleCommand.h"
#include "model/recruit/RecruitProxy.h"
#include "model/skill/SkillProxy.h"
#include "model/player/RoleManage.h"

class GuildChangeCommand:public SimpleCommand
{
public:
	enum 
	{
		CREATE_GUILD_LIST, //创建公会列表
		GET_MY_GUILD_INFO,
		GET_GUILD_INIT_INFO,
		GET_MEMBER_LIST,
		GET_TECH_LIST, 
		GET_CHECK_LIST,
		GET_SEARCH_MEMBER_LIST,
		GUILD_TIPS,
	};

public:
	GuildChangeCommand();
	~GuildChangeCommand();

	virtual void execute(int32 command, char* data);
	void updateGuildList( char* data );
	void setDefaultVO( char* data );
	string getDutyString( int duty );
	void updateSearMemList( char* data );
	void updateMemberList( char* data );
	void updateTechList( char* data );
	void setInitGuildText( char* data );
	void updateCheckList( char* data );
	void showGuildTip( char* data );
};

#endif