#pragma once

#include "BaseType.h"
#include "model/chat/ChatInfo.h"

class ChatInfo;
class ChatItem:public LayerNode
{
public:
	ChatItem();
	~ChatItem();

	bool init(ChatInfo& chatInfo);

public:
	ChatInfo m_chatInfo;
};