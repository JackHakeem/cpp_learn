
#ifndef _GuildVoBase_H_
#define _GuildVoBase_H_

class GuildVoBase
{
public:
	enum
	{
		GuildVoBase_GuildVoBase,
		GuildVoBase_MemberVo,
		GuildVoBase_ApplyVo,
		GuildVoBase_GuildInfoVo,

	};
	GuildVoBase()
	{
	}
	virtual ~GuildVoBase(){}
	virtual int getType() {return GuildVoBase_GuildVoBase;}
};

#endif