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
		/**��ս��/������*/
		TOKEN_FIGHT = 0,
		/**PK��/������*/
		TOKEN_PK = 1,
		/**��Դ��*/
		TOKEN_FARM = 2,
		/**������*/
		TOKEN_COPY = 3,
		/**������*/
		TOKEN_TRADE = 4,	
	};

	void updateToken( int type , int num );
	int getNum(int type);

private:
	std::map<int, int> _tokenNumDic;
};

#endif