#pragma once

#include "BaseType.h"
#include "model/chat/ChatInfo.h"

class ChatInfo;
class SceneChatItem:public LayerNode
{
public:
	SceneChatItem();
	~SceneChatItem();

	bool init(ChatInfo& chatInfo);

public:
	ChatInfo m_chatInfo;
};