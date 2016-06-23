#ifndef HLQS_OnlineRewardVo_H_
#define HLQS_OnlineRewardVo_H_
#include "cocos2d.h"

class OnlineRewardVo
{
public:
	OnlineRewardVo() : _id(0) , _dayNums(0)
	{
		goodsList.clear();
	};
	~OnlineRewardVo(){};

public:
	int _id;
	int _dayNums;
//	std::map<int , int> _list;	
	std::vector<std::string> goodsList;
};

#endif