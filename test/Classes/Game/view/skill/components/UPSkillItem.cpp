#include "UPSkillItem.h"

UPSkillItem::UPSkillItem(int sitNum, int pageNum, UpGradeInfo *info, int pageSize)
{
	_info = 0;
	init();
	if (!_info)
	{
		_info = new UpGradeInfo();
		_info->id = info->id;
		_info->lev = info->lev;
	}
 	//memcpy((void *)&_info,(void *)info,sizeof(_info));
 	_sitNum = sitNum;

	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	if(info->id > 0 )
	{
		// grid
		SpriteNode * cell = new SpriteNode();
		cell->initWithSpriteFrameName("upskill/unlock.png");
		if (this->getChildByTag(TAG_CELL))
		{
			this->removeChildByTag(TAG_CELL,true);
		}
		this->addChild(cell, Z_ITEM,TAG_CELL);
		this->setContentSize(cell->getTexture()->getContentSize());
		cell->release();

		//hightlight		
// 		SpriteNode * light = new SpriteNode();
// 		light->initWithFile("assets/ui/upskill/select.png");
// 		if (this->getChildByTag(TAG_CELL))
// 		{
// 			this->removeChildByTag(TAG_CELL,true);
// 		}
// 		this->addChild(light, Z_ITEM+1,TAG_LIGHT);
// 		this->setContentSize(light->getTexture()->getContentSize());
// 		light->setIsVisible(false);
// 		light->release();

		// skill icon
		char path[64];
		SpriteNode * skill = new SpriteNode();
		//sprintf(path,"skill/%d.png",info->id);
		//skill->initWithSpriteFrameName(path);

		//LH20130110
		sprintf(path,"assets/icon/skill/%d.png" , info->id);
		skill->initWithFile(path);

		if (this->getChildByTag(TAG_ITEMICON))
		{
			this->removeChildByTag(TAG_ITEMICON,true);
		}
		this->addChild(skill, Z_ITEM+2,TAG_ITEMICON);
		skill->release();
	}
}

bool UPSkillItem::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}