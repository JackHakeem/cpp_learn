#pragma once

#include "BaseType.h"
#include "KKUIListView/KKCCUIListView.h"

class ChatInfo;
class ChatItem;
USING_NS_CC;
class ChatPopContainer:public LayerNode,/*PopContainer, */KKCCUIListViewAdapter, KKCCUIListViewItemActionListener
{
public:
	enum
	{
		SEND_CHAT_MESSAGE = 200,
	};
	enum
	{
		ChatPopContainerZ_channelBtnLabel,
		ChatPopContainerZ_bg1,
		ChatPopContainerZ_bg2,
		ChatPopContainerZ_btnLookChannel,
		ChatPopContainerZ_btnChangeChannel,
		ChatPopContainerZ_insertBG,
		ChatPopContainerZ_btnSend,
		ChatPopContainerZ_CCMenu,
		ChatPopContainerZ_btnClose,
		ChatPopContainerZ_popChannels,
		ChatPopContainerZ_KKListView,
		ChatPopContainerZ_TextFieldTTF,
	};

	enum
	{
		ChatPopContainerTAG_channelBtnLabel,//频道列表按钮文字
		ChatPopContainerTAG_bg1,
		ChatPopContainerTAG_bg2,
		ChatPopContainerTAG_btnLookChannel_1,
		ChatPopContainerTAG_btnLookChannel_2,
		ChatPopContainerTAG_btnLookChannel_3,
		ChatPopContainerTAG_btnChangeChannel,
		ChatPopContainerTAG_insertBG,
		ChatPopContainerTAG_btnSend,
		ChatPopContainerTAG_CCMenu,
		ChatPopContainerTAG_btnClose,
		ChatPopContainerTAG_popChannels,
		ChatPopContainerTAG_KKListView,
		ChatPopContainerTAG_TextFieldTTF,
	};

	ChatPopContainer();
	~ChatPopContainer();

	bool init();
	void loginTip(std::string msg);
	void setPrivateChat(std::string pmName);
	void setChannelBtnLabelColor();
	void onChannelChange(CCObject* pSender);
	void onPopChannels(CCObject* pSender);
	void onChannelBtnClick(CCObject* pSender);
	void addChatRecord(ChatInfo* chatInfo);
	void addChatRecord(std::vector<ChatInfo>& vChatInfo);
	void reinitChatRecord(std::vector<ChatInfo>& vChatInfo);
	void clickCloseHandler(CCObject* pSender);
	void clearCacheNodes();
	void sendMessage(CCObject* pSender);
	void setPrivateChatOK(CCObject* pSender);
	void setPrivateChatCancel(CCObject* pSender);
	void systemTip(ChatInfo* value);
	void sendCDStep(float dt);
	static ChatItem* chatItemFactory(ChatInfo* chatInfo);
public:
	virtual std::vector<LayerNode*>* getViewList();
	void onItemClickListener(LayerNode *itemCell, int position);
public:
	int32 _channelBtnLabelType;
	int32 _curChannel;

	KKCCUIListView* _pKKListView;

	std::vector<LayerNode*> _cacheNodes;
	CCLabelTTF* _channelBtnLabel;


	float _CDCounter;
	bool _canSend;

	CCMenuItemSprite* _pActiveChannelBtn;
	
};