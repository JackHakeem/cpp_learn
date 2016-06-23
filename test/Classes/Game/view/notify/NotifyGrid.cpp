#include "NotifyGrid.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

#define SIZE_GRID CCSizeMake(POSX(60) , POSX(60))

NotifyGrid::NotifyGrid() : _type(-1)
{
	
}

NotifyGrid::NotifyGrid(int type)
{
	_type = type;
	init();
}

NotifyGrid::~NotifyGrid()
{

}

bool NotifyGrid::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setIsTouchEnabled(false);

	loadItem();

	return true;
}

void NotifyGrid::loadItem()
{
	// back
	CCUIBackground * pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("popuibg/bg1.png" , CCPointZero , CCPointZero , SIZE_GRID , 255);
	pBack->setPosition(CCPointZero);
	this->addChild(pBack , 0);
	pBack->release();

	_size = SIZE_GRID;
	this->setContentSize(_size);

	// text
	CCLabelTTF * pLabTxt = new CCLabelTTF();
	char path[32] = {0};
	sprintf(path , "TIP00%d" , _type+1);
	pLabTxt->initWithString(ValuesUtil::Instance()->getString(path).c_str() , CCSizeMake(POSX(32) , POSX(32)) , CCTextAlignmentCenter , "Arial" , POSX(30));
	pLabTxt->setPosition(ccp(_size.width/2 , _size.height/2));
	pLabTxt->setColor(ccc3(233,233,25));
	pBack->addChild(pLabTxt , 0);

	CCFiniteTimeAction * pFadeTo1 = CCFadeTo::actionWithDuration(0.5f , 128);
	CCFiniteTimeAction * pFadeTo2 = CCFadeTo::actionWithDuration(0.5f , 255);
	CCAction * pAction  = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeTo1 , pFadeTo2 ));
	pLabTxt->runAction(pAction);
}

