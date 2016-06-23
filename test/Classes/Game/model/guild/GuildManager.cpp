#include "GuildManager.h"
#include "vo/GuildLevInfo.h"

GuildManager::GuildManager()
{

}

void GuildManager::setGuildLevInfos( GuildLevInfo* info )
{
	if ( !info )
	{
		return;
	}

	_guildLevDic.insert( make_pair( (int)info->lev, info ) );
}

GuildLevInfo* GuildManager::getGuildLevInfo( int lev )
{
	map<int , GuildLevInfo*>::iterator it = _guildLevDic.find(lev);
	if ( it != _guildLevDic.end() )
	{
		return it->second;
	}

	return 0;
}

uint GuildManager::getNeedGold( int lev )
{
	map<int , GuildLevInfo*>::iterator it = _guildLevDic.find(lev);
	if ( it != _guildLevDic.end() )
	{
		GuildLevInfo* vo = it->second;
		return vo->needGold;
	}

	return 0;
}

uint GuildManager::getIncMember( int lev )
{
	map<int , GuildLevInfo*>::iterator it = _guildLevDic.find(lev);
	if ( it != _guildLevDic.end() )
	{
		GuildLevInfo* vo = it->second;
		return vo->incMember;
	}

	return 0;
}


GuildManager::~GuildManager()
{
	map<int, GuildLevInfo*>::iterator it;
	for ( it = _guildLevDic.begin(); it != _guildLevDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_guildLevDic.clear();
}

