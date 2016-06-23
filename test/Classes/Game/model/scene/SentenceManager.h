#ifndef _SENTENCEMANAGER_H_
#define _SENTENCEMANAGER_H_

#include "utils/Singleton.h"
#include "BaseType.h"
#include "SentenceVo.h"

typedef pair<int, std::string> npcPair;
typedef multimap<int, npcPair> mapIDPair;

class SentenceManager : public Singleton<SentenceManager>
{
public:
	SentenceManager();
	~SentenceManager();

	SentenceVo* allocVo() { return new SentenceVo(); };

	void setSentence( SentenceVo* pSentenceVo );
	std::string getSentence( int iMapID, int iNPCID );

private:
	mapIDPair _sentenceDic;
};

#endif