#include "DungeonGUAMonsterInfoItem.h"
//#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "KKLabelTTF.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"

DungeonGUAMonsterInfoItem::DungeonGUAMonsterInfoItem()
{
}

DungeonGUAMonsterInfoItem::~DungeonGUAMonsterInfoItem()
{}

bool DungeonGUAMonsterInfoItem::init(std::string value, int guanIndex)
{
	if (!LayerNode::init())
		return false;


	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(20, 24.0f, CCSizeMake(400, 120));
	
	//第N关
	{
		char str[10];
		sprintf(str, ValuesUtil::Instance()->getString("GUA010").c_str(), guanIndex);
		std::string showstr1 = str;
		kkttf->add(showstr1, ccc3(241, 216, 35));
	}
	//怪物名 
	kkttf->add(value, ccc3(230, 230, 216));

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
    kkttf->release();


	return true;
}

