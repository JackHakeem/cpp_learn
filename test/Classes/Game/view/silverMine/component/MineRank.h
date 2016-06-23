#pragma once

#include "LayerNode.h"
#include "socket/command/s36/SCMD367Node.h"

class MineRank:public LayerNode
{
public:
	MineRank();
	~MineRank();

	bool init();
	void updateRank(std::list<SCMD367Node>&  arr);
	void close(CCObject* pSender);
	void updateSilver(int silver);
public:
	vector<LayerNode*> itemarr;
	CCLabelTTF* _txtOwn;
};