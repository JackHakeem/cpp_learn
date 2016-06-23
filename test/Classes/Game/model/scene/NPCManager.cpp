#include "NPCManager.h"
#include "CCPlatformMacros.h"

NPCManager::~NPCManager()
{
	MAPNPCVO::iterator it;

	for ( it = _npcDic.begin(); it != _npcDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_npcDic.clear();
}

void NPCManager::setNPC( NPCVo* pNPCVo )
{
	if (!pNPCVo) return;

	_npcDic.insert(  make_pair( pNPCVo->id, pNPCVo )  );

	MAPIDMAPITER it = m_mapIDMap.find( pNPCVo->GetmapId() );
	if ( it != m_mapIDMap.end() )
	{
		MAPIDVECTOR& mapIdVector = it->second;
		mapIdVector.push_back( pNPCVo->id );
	}
	else
	{
		MAPIDVECTOR mapIdVector;
		mapIdVector.push_back( pNPCVo->id );
		m_mapIDMap.insert( make_pair( pNPCVo->GetmapId(), mapIdVector ) );
	}
}

NPCVo* NPCManager::getNPC( int npcId )
{
	MAPNPCVOITER it = _npcDic.find( npcId );

	if ( it != _npcDic.end() )
	{
		return it->second;
	}
	return NULL;
}

MAPIDVECTOR NPCManager::getNpcsByMapId( int iMapID )
{
	std::vector<int> dt;
	MAPIDMAPITER it = m_mapIDMap.find( iMapID );
	if ( it != m_mapIDMap.end() )
	{
		return it->second;
	}
	else
	{
		return dt;
	}
}
