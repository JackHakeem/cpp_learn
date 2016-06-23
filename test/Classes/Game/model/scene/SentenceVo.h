#ifndef _SENTENCEVO_H
#define _SENTENCEVO_H

class SentenceVo
{
public:
	SentenceVo(){}
	~SentenceVo(){}

	int id;
	int type;
	std::string content;
	int mapId;
	int otherInfo;           //The progress of the boss
};

#endif

