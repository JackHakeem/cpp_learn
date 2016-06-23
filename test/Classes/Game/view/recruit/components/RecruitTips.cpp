#include "RecruitTips.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LangManager.h"
#include "../RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "RecruitView.h"

RecruitTips::RecruitTips()
{

}

RecruitTips::~RecruitTips()
{

}

bool RecruitTips::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCLayer* _pContainer = new CCLayer();
	_pContainer->setAnchorPoint(CCPointZero);
	_pContainer->setPosition(POS(ccp(0, 10), ScaleUtil::CENTER_TOP));
	this->addChild(_pContainer);
	
	RecruitMediator* pRecruitMediator =
		(RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	CCPoint cp = ccp( POSX(808-30+17), POSX(478+12) );//pRecruitMediator->_recruitView->m_locationInView;
	CCUIBackground* bg = new CCUIBackground();
	bg->initWithSpriteFrame("ui.png", ccp(cp.x-POSX(298), cp.y-POSX(150+17)), ccp(POSX(6),POSX(7)),
		CCSizeMake(POSX(298), POSX(150)));
	_pContainer->addChild(bg, 1);
	bg->release();
	
	string str = LangManager::getText("RCR043") + "\n"
		+ LangManager::getText("RCR044") + "\n" + LangManager::getText("RCR045");
	CCLabelTTF* _nameEquipment = CCLabelTTF::labelWithString( 
		str.c_str(),
		CCSizeMake( POSX(288), POSX(150) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_nameEquipment->setColor(  ccGREEN  );
	_nameEquipment->setAnchorPoint(CCPointZero);
	_nameEquipment->setPosition( ccp( cp.x-POSX(298), cp.y-POSX(150+17) ) );
	_pContainer->addChild( _nameEquipment, 2 );

	return true;
}

