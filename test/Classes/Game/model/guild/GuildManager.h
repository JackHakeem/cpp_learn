#ifndef _GuildManager_H_
#define _GuildManager_H_

#include "BaseType.h"
#include "utils/Singleton.h"
#include "vo/GuildLevInfo.h"

class GuildManager : public Singleton<GuildManager>
{
public:
	GuildManager();
	~GuildManager();
public:
	GuildLevInfo* allocVo(){ return new GuildLevInfo(); };

	void setGuildLevInfos( GuildLevInfo* info );
	GuildLevInfo* getGuildLevInfo( int lev );
	uint getNeedGold( int lev );
	uint getIncMember( int lev );
private:
	map<int , GuildLevInfo*> _guildLevDic;
};

#endif