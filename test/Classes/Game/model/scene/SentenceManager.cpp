#include "SentenceManager.h"

SentenceManager::SentenceManager()
{

}

SentenceManager::~SentenceManager()
{
}

void SentenceManager::setSentence( SentenceVo* pSentenceVo )
{
	if ( !pSentenceVo )
	{
		return;
	}

	_sentenceDic.insert( make_pair( pSentenceVo->mapId, npcPair( pSentenceVo->otherInfo, pSentenceVo->content ) )  );

	CC_SAFE_DELETE( pSentenceVo );
}

std::string SentenceManager::getSentence( int iMapID, int iNPCID )
{
	std::pair<mapIDPair::iterator, mapIDPair::iterator> range;
	range = _sentenceDic.equal_range(iMapID);

	mapIDPair::iterator it;
	
	for ( it = range.first; it != range.second; ++it )
	{
		 if ( iNPCID == it->second.first )
		 {
			 return it->second.second;
		 }
	}
	 return "";
}

