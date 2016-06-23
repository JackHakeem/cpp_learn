#pragma once

#include "PopContainer.h"
#include "LayerNode.h"
#include "model/gong/vo/GongRanking.h"

class GongRankingView:public PopContainer
{
public:
	GongRankingView();
	~GongRankingView();
	bool init();
	void update(int curwave, std::vector<GongRanking>& vGongRanking);
	void clickClose(CCObject* pSender);

public:
	LayerNode* _pContainer;

};