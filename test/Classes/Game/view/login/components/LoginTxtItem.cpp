#include "LoginTxtItem.h"
#include "utils/ScaleUtil.h"

LoginTxtItem::LoginTxtItem()
{
	init();
}

LoginTxtItem::~LoginTxtItem()
{

}

bool LoginTxtItem::init()
{
	if (!CCLabelTTF::init())
	{
		return false;
	}

	//

	return true;
}

LoginTxtItem* LoginTxtItem::ItemWithString( std::string msg, ccColor3B color, int fontsize )
{
	LoginTxtItem* pLoginTxtItem = new LoginTxtItem();
	pLoginTxtItem->initWithString( msg.c_str(),CCSizeMake(POSX(200),POSX(120)),CCTextAlignmentLeft, g_sSimHeiFont, fontsize );
	pLoginTxtItem->setColor(color);
	return pLoginTxtItem;
}

void LoginTxtItem::onTime( float dt )
{
	if ( this && this->getParent() )
	{
		this->getParent()->removeChild(this, true );
	}
	//CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(LoginTxtItem::onTime), this );
}