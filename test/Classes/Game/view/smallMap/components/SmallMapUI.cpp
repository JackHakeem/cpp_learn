#include "SmallMapUI.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"

SmallMapUI::SmallMapUI()
{
}


void SmallMapUI::initWithParam(std::string name, CCPoint location)
{
	//configUI(name,location);
	//initTips();
}

void SmallMapUI::configUI(std::string name, CCPoint location)
{

}

void SmallMapUI::townMapClick(CCObject* pSender)
{
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_MAP, 0 );
}

CCNode * SmallMapUI::getNewHandItem( int btnId )
{
	return NULL;
}

SmallMapUI::~SmallMapUI()
{
	CCLog( "Release test. jae." );
}
