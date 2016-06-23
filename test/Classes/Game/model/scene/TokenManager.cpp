#include "TokenManager.h"

TokenManager::TokenManager()
{

}

TokenManager::~TokenManager()
{

}

void TokenManager::updateToken( int type , int num )
{
	std::map<int, int>::iterator it = _tokenNumDic.find(type);
	if ( it == _tokenNumDic.end() )
	{
		_tokenNumDic.insert( std::make_pair(type, num) );
	}
	else
	{
		it->second = num;
	}
}

int TokenManager::getNum(int type)
{
	std::map<int, int>::iterator it = _tokenNumDic.find(type);
	if (it!=_tokenNumDic.end())
	{
		return it->second;
	}
	return 0;
}

