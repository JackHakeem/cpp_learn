#pragma once

#include "BaseType.h"
#include "KKUIListView/KKCCUIListView.h"
#include "model/chat/ChatInfo.h"

USING_NS_CC;
class SceneChatItem;
class ChatView:public LayerNode, KKCCUIListViewAdapter, KKCCUIListViewItemActionListener
{
public:
	enum
	{
		ChatViewZ_channelBtnLabel,
		ChatViewZ_bg1,
		ChatViewZ_KKListView,
	};

	enum
	{
		ChatViewTAG_channelBtnLabel,//频道列表按钮文字
		ChatViewTAG_bg1,
		ChatViewTAG_KKListView,

	};

	ChatView();
	~ChatView();

	bool init();
	void addChatRecord(std::vector<ChatInfo>& vChatInfo);
	void addChatRecord(ChatInfo* chatInfo);
	void systemTip(ChatInfo* chatInfo);
	void clearCacheNodes();
public:
	virtual std::vector<LayerNode*>* getViewList();
	static SceneChatItem* chatItemFactory(ChatInfo* chatInfo);
public:
	int32 _channelBtnLabelType;
	int32 _curChannel;

	KKCCUIListView* _pKKListView;

	std::vector<LayerNode*> _cacheNodes;
	CCLabelTTF* _channelBtnLabel;
	bool _hide;
};