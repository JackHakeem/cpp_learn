#include "SkillCells.h"

SkillCells::SkillCells()
{
	_myInfo = NULL;
	_mySitNum = 0;
}

bool SkillCells::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
    return true;
}

SkillCells::SkillCells(UpGradeInfo* info, int sitNum, int page, std::string userName)
{
	_myInfo = info;
	_mySitNum = sitNum;

	float width = 0.0f;
	float height = 0.0f;

	//int col = (sitNum - page*15) % 5;
	//int row = (sitNum - page*15) / 5;

	if(_myInfo->id != 0 )
	{
		SpriteNode* skill = new SpriteNode();
		//char buf[] = "assets/icon/skills/%d.png";
		char buf[] = "pack/unlock.png";
		char path[64];
		//sprintf(path, buf, info->id);
		sprintf(path, buf, 622);
		skill->initWithSpriteFrameName(path);
//		width = skill->getTexture()->getContentSize().width;
//		height = skill->getTexture()->getContentSize().height;

		if(_myInfo->lev == 0)
		{
			//setPicGray();
		}

		this->addChild(skill);
		this->setContentSize(skill->getTexture()->getContentSize());
		skill->release();
		int row = sitNum % 3;//
		int col = sitNum % 2;//
		this->setPosition(ccp(col * 220 + 110, 465 - row * 110));

	}

	if (_myInfo->active)
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("E", "Arial", 30);
		//pLabel->setPosition(ccp((winSizePixels.width - m_viewSize.width)/ 2.0f + 300, (winSizePixels.height - m_viewSize.height) / 2.0f + 40));
		this->addChild(pLabel, RENDERZ_lable);
		pLabel->release();
	}
}

void SkillCells::setActive(bool set, std::string userName)
{
	_myInfo->active = set;

	CCNode* node = this->getChildByTag(RENDERZ_lable);
	if(set && (!node))
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("E", "Arial", 30);
		//pLabel->setPosition(ccp((winSizePixels.width - m_viewSize.width)/ 2.0f + 300, (winSizePixels.height - m_viewSize.height) / 2.0f + 40));
		this->addChild(pLabel, RENDERZ_lable);
		pLabel->release();
	}
	else if((!set) && node)
	{
		this->removeChild(node, true);
	}
}