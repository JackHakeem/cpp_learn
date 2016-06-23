#ifndef _MessageItem_H_
#define _MessageItem_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "LHLabelTTF.h"
using namespace cocos2d;

class MessageItem : public LHLabelTTF
{
public:
	MessageItem();
	~MessageItem();

public:
	static MessageItem* MessageItemWithString( string msg );
	void onTime( float dt );
private:

};

#endif