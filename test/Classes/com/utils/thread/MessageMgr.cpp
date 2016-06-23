#include "MessageMgr.h"
#include "../../../Game/events/GameDispatcher.h"

MessageMgr::MessageMgr()
{
	start();
}

MessageMgr::~MessageMgr()
{

}

void MessageMgr::start()
{
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(MessageMgr::my_thread),this,0.1f,false);
}

void MessageMgr::stop()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(MessageMgr::my_thread),this);
}

void MessageMgr::sendMessage(int msgType , void * data)
{
	MessageMgr::Msg msg;
	msg.msgType = msgType;
	msg.data = data;
	_messageQuene.push_back(msg);
}

void MessageMgr::handlerMessage(int msgType , void * data)
{
	GameDispatcher::getInstance()->dispatchEvent(msgType , data);
}

void MessageMgr::my_thread(ccTime dt)
{
	if (!_messageQuene.empty())
	{
		MessageMgr::Msg msg = _messageQuene.front();
		handlerMessage(msg.msgType , msg.data);
		_messageQuene.pop_front();
	}
}