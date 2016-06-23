#include "MeltingTips.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"

MeltingTips::MeltingTips()
{

}

MeltingTips::~MeltingTips()
{

}

bool MeltingTips::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCLayer* _pContainer = new CCLayer();
	_pContainer->setAnchorPoint(CCPointZero);
	_pContainer->setPosition(POS(ccp(0, 10), ScaleUtil::CENTER_TOP));
	this->addChild(_pContainer);

	CCUIBackground* bg = new CCUIBackground();
	bg->initWithSpriteFrame("ui.png", ccp(POSX(515), POSX(330)), ccp(POSX(6),POSX(7)),
		CCSizeMake(POSX(298), POSX(150)));
	_pContainer->addChild(bg, 1);
	bg->release();

	CCLabelTTF* _nameEquipment = CCLabelTTF::labelWithString( 
		ValuesUtil::Instance()->getString("STG102").c_str(),
		CCSizeMake( POSX(288), POSX(18*5) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_nameEquipment->setColor(  ccGREEN  );
	_nameEquipment->setAnchorPoint(CCPointZero);
	_nameEquipment->setPosition( ccp( POSX(515+5), POSX(330+(150-18*4-15)) ) );
	_pContainer->addChild( _nameEquipment, 2 );

	_nameEquipment = CCLabelTTF::labelWithString( 
		ValuesUtil::Instance()->getString("STG103").c_str(),
		CCSizeMake( POSX(288), POSX(18*3) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_nameEquipment->setColor(  ccGREEN  );
	_nameEquipment->setAnchorPoint(CCPointZero);
	_nameEquipment->setPosition( ccp( POSX(515+5), POSX(330+(150-18*6-25)) ) );
	_pContainer->addChild( _nameEquipment, 2 );

	return true;
}

