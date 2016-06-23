#ifndef _REWARD_ITEM_H_
#define _REWARD_ITEM_H_

#include "cocos2d.h"
#include "socket/command/s1e/SCMD1ED.h"
#include <vector>
#include "LayerNode.h"
#include "utils/TipBase.h"
#include "utils/TipHelps.h"

USING_NS_CC;

class RewardItem : public LayerNode, public TipBase 
{
public:
	struct Node 
	{
		unsigned short id;
		int num;
	};
public:
	RewardItem(std::vector<std::string> &list);
	~RewardItem();

	void initGoodsTipsInfo(int id);
	void onClickShowTips(CCObject * pSender);
	void timerStep();

public:
	std::vector<std::string> _NodeList;
	TipHelps *_pPopTip;
};
#endif