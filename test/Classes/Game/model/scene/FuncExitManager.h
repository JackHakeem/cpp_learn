#ifndef HLQS_FuncExitManager_H_
#define HLQS_FuncExitManager_H_
#include "utils/Singleton.h"
#include "vo/FuncExitVo.h"
#include "cocos2d.h"
USING_NS_CC;

class FuncExitManager: public Singleton<FuncExitManager>
{
public:
	FuncExitManager();
	void setFuncExit(FuncExitVo* vo);
	FuncExitVo* getFuncExit(int type, int lev);
	void dispose();

public:
	const static int TYPE_FIGHT = 1;
	const static int TYPE_RECRUIT = 2;
	std::vector<FuncExitVo> _typeDic;
};

#endif