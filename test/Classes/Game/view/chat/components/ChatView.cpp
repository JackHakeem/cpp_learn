#include "ChatView.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"
#include "model/chat/ChannelType.h"
#include "CCUIBackground.h"

#include "ChatMsgManager.h"
#include "ChatPopContainer.h"
#include "SceneChatItem.h"

const float FontSize = 30.0f;

ChatView::ChatView():_hide(false)
{
}

ChatView::~ChatView()
{}

bool ChatView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame(/*"chat/chat_0.png"*/"ui2.png", ccp(POSX(/*0*/2), POSX(/*90*//*-10*/2)),ccp(0,0),
		CCSizeMake(POSX(/*300*/600 + 88 - 200),POSX(/*300-55*//*160-55*/160-73)), 255);
	this->addChild(_bg1, ChatViewZ_bg1, ChatViewTAG_bg1);
	_bg1->release();
	

	
	//list
	_pKKListView = KKCCUIListView::listViewWithCCRect(CCRectMake(POSX(/*4*/94), POSX(/*116*//*16*/8), POSX(/*280*/580 - 200), POSX(/*270-55*/130-55)), 5);
	_pKKListView->setIsRelativeAnchorPoint(true);
	_pKKListView->m_pri = TLE::WindowLayer_ChatPopContainer;
    _pKKListView->setAnchorPoint(ccp(0,0));
	_pKKListView->setSpacingVertical(0);
	_pKKListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pKKListView->getPosition(), ccp(0, 0)));
	_pKKListView->setOnItemActionListener(this);
	_pKKListView->setIsTouchEnabled(false);
	_pKKListView->setVisitType(1);
	this->addChild(_pKKListView, ChatViewZ_KKListView, ChatViewTAG_KKListView);
	//Doyang
	_pKKListView->release();
    
    /*
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //list
	_pKKListView = KKCCUIListView::listViewWithCCRect(CCRectMake(POSX(4), POSX(116), winSize.width - POSX(24 * 2), 
                                                                 winSize.height - POSX(80 * 2)), 4);
	_pKKListView->setIsRelativeAnchorPoint(true);
	_pKKListView->m_pri = TLE::WindowLayer_ChatPopContainer;
    _pKKListView->setAnchorPoint(ccp(0,0));
	_pKKListView->setSpacingVertical(0);
	_pKKListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pKKListView->getPosition(), ccp(0, 0)));
	_pKKListView->setIsTouchEnabled(false);
	this->addChild(_pKKListView, ChatViewZ_KKListView, ChatViewTAG_KKListView);
	
    //Doyang 20120717
	_pKKListView->release();
     */
	return true;
}

SceneChatItem* ChatView::chatItemFactory(ChatInfo* chatInfo)
{
	if (!chatInfo)
		return 0;
	SceneChatItem* newItem = new SceneChatItem();
	newItem->init(*chatInfo);
	return newItem;
}

std::vector<LayerNode*>* ChatView::getViewList()
{
	return &_cacheNodes;
}

void ChatView::addChatRecord(std::vector<ChatInfo>& vChatInfo)
{
//	int curChannel = ChannelType::stringToChannel(_channelBtnLabelType);
	for (int i = 0; i < vChatInfo.size(); i++)
	{
		
		/*if ( !(vChatInfo[i].channel == 3 && _curChannel == 3) &&
			!(vChatInfo[i].channel == 1 && _curChannel == 1) &&
			!(_curChannel == 0))
		{
			continue;
		}	*/


		SceneChatItem* newNode = ChatView::chatItemFactory(&vChatInfo[i]);
		if (newNode)
		{
			_cacheNodes.push_back((LayerNode*)newNode);
			//newNode->release();
		}
	
	}
	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void ChatView::systemTip(ChatInfo* chatInfo)
{
	if (!chatInfo)
		return;

	SceneChatItem* newNode = ChatView::chatItemFactory(chatInfo);
	if (newNode)
	{
		_cacheNodes.push_back((LayerNode*)newNode);	
		//newNode->release();
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}


void ChatView::addChatRecord(ChatInfo* chatInfo)
{
	if (!chatInfo)
		return;
	int curChannel = ChannelType::stringToChannel(_channelBtnLabelType);
	/*if ( !(chatInfo->channel == 3 && _curChannel == 3) &&
		!(chatInfo->channel == 1 && _curChannel == 1) &&
		!(_curChannel == 0))
	{
		return;
	}	*/

	SceneChatItem* newNode = ChatView::chatItemFactory(chatInfo);
	if (newNode)
	{
		_cacheNodes.push_back((LayerNode*)newNode);	
		//newNode->release();
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void ChatView::clearCacheNodes()
{
	for (int i = 0; i < _cacheNodes.size(); i++)
	{
		_cacheNodes[i]->release();
	}
	_cacheNodes.clear();
}