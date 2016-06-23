#include "FuncExitManager.h"

FuncExitManager::FuncExitManager()
{
}

void FuncExitManager::setFuncExit(FuncExitVo* vo)
{
	_typeDic.push_back(*vo);
}


FuncExitVo* FuncExitManager::getFuncExit(int type, int lev)
{
	std::vector<FuncExitVo>::iterator iter =  _typeDic.begin();
	for(; iter != _typeDic.end(); ++iter)
	{
		if((*iter).lev == lev && (*iter).type == type)
			return &(*iter);
	}

	return NULL;
}

void FuncExitManager::dispose()
{
	_typeDic.clear();
}