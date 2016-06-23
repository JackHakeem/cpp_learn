#include "MessageItem.h"
#include "view/scene/components/MainScene.h"
#include "utils/ScaleUtil.h"
#include "Message.h"

MessageItem::MessageItem()
{
}

MessageItem::~MessageItem()
{

}

MessageItem* MessageItem::MessageItemWithString( string msg )
{
	MessageItem* pMessageItem = new MessageItem;
	//pMessageItem->initWithString( msg.c_str(), g_sSimHeiFont, POSX(24) );
	pMessageItem->initWithString( (char *)msg.c_str(), CCSizeMake(POSX(960) , POSX(25)) , CCTextAlignmentCenter , "Arial" , POSX(24) , POSX(1) <1 ? 1 : POSX(1)  ,ccc3(0,0,0));
	return pMessageItem;
}

void MessageItem::onTime( float dt )
{
	CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(MessageItem::onTime), this );
	if ( this && this->getParent() )
	{
		Message::Instance()->_msgList.removeObject( this, true );
		this->removeFromParentAndCleanup( true );
	}
}
