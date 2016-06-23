#pragma once

#include "BaseType.h"
#include "model/egg/vo/EggInfo.h"

class KKLabelTTF;
class RewardPanel:public LayerNode
{
public:
	RewardPanel();
	~RewardPanel();

	bool init();
	void updateContianer(std::vector<EggInfo> arr);
	void txtContent(KKLabelTTF* pkk, int state, int goodsId, int type, int quality, int goodsNum, std::string name="");

	LayerNode* _paneContianer;
};