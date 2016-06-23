#pragma once

#include "PopContainer.h"
#include "LayerNode.h"
#include "model/gong/vo/GongRanking.h"
#include "socket/command/s44/SCMD44ANode.h"

class GongMBView:public PopContainer
{
public:
	GongMBView();
	~GongMBView();
	bool init();
	void update(std::string heroname, std::vector<SCMD44ANode>& mbNames);
	void clickClose(CCObject* pSender);
	void clickMB(CCObject* pSender);
public:

	enum
	{
		Tag_Label = 112,
	};

	LayerNode* _pContainer;
};