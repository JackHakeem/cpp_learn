#ifndef _TokenManager_H_
#define _TokenManager_H_

#include "utils/Singleton.h"
#include "BaseType.h"
#include "SentenceVo.h"


class TokenManager : public Singleton<TokenManager>
{
public:
	TokenManager();
	~TokenManager();

	enum
	{
		/**征战令/怪物令*/
		TOKEN_FIGHT = 0,
		/**PK令/竞技令*/
		TOKEN_PK = 1,
		/**资源令*/
		TOKEN_FARM = 2,
		/**副本令*/
		TOKEN_COPY = 3,
		/**劫商令*/
		TOKEN_TRADE = 4,	
	};

	void updateToken( int type , int num );
	int getNum(int type);

private:
	std::map<int, int> _tokenNumDic;
};

#endif