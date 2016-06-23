#include "StarRecord.h"
#include "events/GameDispatcher.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "ArenaUI.h"
#include "socket/command/s36/SCMD361.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"


const float FontSize = 18.0f;

StarRecord::StarRecord()
{}

StarRecord::~StarRecord()
{}

bool StarRecord::initWithParam(ArenaUI* pContainer)
{
	if (!LayerNode::init())
		return false;
	_pContainer = pContainer;

	return true;
}

// 战斗结果（<0:失败，>0胜利）
void StarRecord::update(std::vector<int>& arr)
{
	this->removeAllChildrenWithCleanup(true);

	int arrsize = arr.size();
	for (int i = 0; i < 5; i++)
	{
		SpriteNode* sp = new SpriteNode();
		if (i < arrsize)
		{
			if (arr[i]<0)
				sp->initWithSpriteFrameName("arena/16.png");
			else
				sp->initWithSpriteFrameName("arena/3.png");
		}
		else
		{
			sp->initWithSpriteFrameName("arena/2.png");
		}

		sp->setPosition(ccp(POSX(65) + (POSX(64 - 10))*i, POSX(640-525)));

		this->addChild(sp, StarRecordZ_s0+i, StarRecordTAG_s0+i);

		sp->release(); //LH0714
	}

	//str_0
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(StarRecordTAG_str_0);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC017").c_str(), CCSizeMake(POSX(300), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-570)));
			this->addChild(pLabel, StarRecordZ_str_0, StarRecordTAG_str_0);
			pLabel->setColor(ccc3(55, 21, 0));
		}
	}
	//str_1
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(StarRecordTAG_str_1);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC018").c_str(), CCSizeMake(POSX(300), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-590)));
			this->addChild(pLabel, StarRecordZ_str_1, StarRecordTAG_str_1);
			pLabel->setColor(ccc3(55, 21, 0));
		}
	}
}