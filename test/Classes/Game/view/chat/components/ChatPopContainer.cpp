#include "ChatPopContainer.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"
#include "model/chat/ChannelType.h"
#include "CCUIBackground.h"
#include "ChannelBtnClickLayer.h"
#include "manager/ViewManager.h"
#include "model/chat/ChatInfo.h"
#include "ChatMsgManager.h"
#include "ChatItem.h"
#include "TextFieldTTF.h"
#include "manager/LangManager.h"
#include "TextInputConfirm.h"
#include "model/player/RoleManage.h"
#include "view/scene/SceneStoryMediator.h"
#include "view/chat/ChatMediator.h"

const float FontSize = 40.0f;
const float FontSize2 = 30.0f;
const float FontSize3 = 20.0f;
const int TAG_PARENT_LAYER = 1001;
ChatPopContainer::ChatPopContainer()
{
	_channelBtnLabelType = ChannelType::ALL_STRING;
	_curChannel = 0;
	_pKKListView = 0;
	_CDCounter = 0;
	_canSend = true;
	_pActiveChannelBtn = 0;
}

ChatPopContainer::~ChatPopContainer()
{
	for (int i = 0 ; i < _cacheNodes.size(); i++)
	{
		_cacheNodes[i]->release();
	}
	_cacheNodes.clear();
}

bool ChatPopContainer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//Init key
	//key = 0;//PopEventName::BANK;
	_CDCounter = 0.0f;
	_canSend = true;
	_channelBtnLabelType = ChannelType::ALL_STRING;

	/*this->setContentSize(CCSizeMake(POSX(960), POSX(640)));
	this->setPopContentSize(CCSizeMake(POSX(960), POSX(640)));*/

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//this->setContentSize(winSize);
	//this->setPopContentSize(winSize);

	//Doyang 
	CCLayer *pParentLayer = new CCLayer();
	if(!pParentLayer || !pParentLayer->init())
	{
		return false;
	}
	pParentLayer->setContentSize(this->getContentSize());
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setPosition(POS(CCPointZero, ScaleUtil::BOTTOM_LEFT));
	this->addChild(pParentLayer, 0, TAG_PARENT_LAYER);
	pParentLayer->release();

	//if (this->getChildByTag(ChatPopContainerTAG_bg1))
	//{
	//	return false;//kevint
	//}
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_6.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		winSize);
	pParentLayer->addChild(_bg1, ChatPopContainerZ_bg1, ChatPopContainerTAG_bg1);
	_bg1->release();
	//
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(20), POSX(74)),ccp(0,0),
		CCSizeMake(winSize.width - POSX(20 * 2), winSize.height - POSX(74 * 2)));
	pParentLayer->addChild(_bg2, ChatPopContainerZ_bg2, ChatPopContainerTAG_bg2);
	_bg2->release();
	//ChatPopContainerTAG_btnLookChannel_1~3
	
	CCLayer *pTopLayer = new CCLayer();
	if(!pTopLayer || !pTopLayer->init())
	{
		return false;
	}
	pTopLayer->setContentSize(CCSizeMake(winSize.width, POSX(74)));
	pTopLayer->setPosition(POS(ccp(0, 566), ScaleUtil::CENTER_TOP));
	pTopLayer->setAnchorPoint(CCPointZero);
	pParentLayer->addChild(pTopLayer, 1000);
	pTopLayer->release();

	for (int i = 3; i >= 0; i--)
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_4.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_3.png");
		CCSprite *pSelectedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_3.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			pSelectedSprite,
            this, 
            menu_selector(ChatPopContainer::onChannelChange) );

        //if (i != 2)
        //{
        //    _btn = CCMenuItemImage::itemFromNormalImage(
        //                                                "assets/ui/chat/chat_4.png",
        //                                                "assets/ui/chat/chat_3.png",
        //                                                "assets/ui/chat/chat_3.png", 
        //                                                this, 
        //                                                menu_selector(ChatPopContainer::onChannelChange) );
        //}
        //else
        //{
        //    _btn = CCMenuItemImage::itemFromNormalImage(
        //                                                "assets/ui/chat/chat_4.png",
        //                                                "assets/ui/chat/chat_4.png",
        //                                                "assets/ui/chat/chat_4.png", 
        //                                                this, 
        //                                                menu_selector(ChatPopContainer::onChannelChange) );
        //}

		
		//if (i == 2) _btn->setIsEnabled(false);//暂时军团没开放

		_btn->setPosition(ccp(POSX(192+i*200), /*POSX(600)*/POSX(34)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		_btn->setTag(i);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_chat-1);
		pTopLayer->addChild(buttonMenu, ChatPopContainerZ_btnLookChannel, ChatPopContainerTAG_btnLookChannel_1+i);

		int indexstr = 43;
		char str[10];
		sprintf(str, "CHT0%d", indexstr+i);
		std::string loginTip = ValuesUtil::Instance()->getString(str);

		CCLabelTTF* label = CCLabelTTF::labelWithString(loginTip.c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		_btn->addChild(label, 0, 1);
		label->setColor(ccc3(254, 189, 0));
		label->setPosition(ccp(POSX(84), POSX(34)));

		_pActiveChannelBtn = _btn;
	}
	_pActiveChannelBtn->setIsEnabled(false);

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(ChatPopContainer::onChannelBtnClick) );

		_btn->setScaleX(1.6f);//迎合名字长度
		_btn->setPosition(ccp(POSX(126), POSX(40)));
		_btn->setTag(0);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_chat-1);
		pParentLayer->addChild(buttonMenu, ChatPopContainerZ_btnChangeChannel, ChatPopContainerTAG_btnChangeChannel);
		//白三角
		SpriteNode* sanjiao = new SpriteNode();
		sanjiao->initWithSpriteFrameName("chat/chat_8.png");
		sanjiao->setPosition(ccp(POSX(96), POSX(30)));
		sanjiao->setScaleX(0.7f);
		_btn->addChild(sanjiao, 0, 1);
		sanjiao->release();
		//世界
		CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT044").c_str(), 
			CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pParentLayer->addChild(label, 128, 2000);
		label->setColor(ccc3(255, 255, 255));
		label->setPosition(ccp(POSX(40+56), POSX(30+10)));
		//
		_channelBtnLabel = label;
		setChannelBtnLabelColor();
	}
	//ChatPopContainerTAG_insertBG
	{
		CCUIBackground* _insertBG = new CCUIBackground();
		_insertBG->initWithSpriteFrame("chat/chat_2.png", ccp(POSX(228), POSX(15)),ccp(0,0),
			CCSizeMake(POSX(540),POSX(45)));
		pParentLayer->addChild(_insertBG, ChatPopContainerZ_insertBG, ChatPopContainerTAG_insertBG);
		_insertBG->release();		
	}
	//ChatPopContainerTAG_btnSend
	{

		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(ChatPopContainer::sendMessage) );//假

			_btn->setPosition(ccp(winSize.width - POSX(100), POSX(40)));

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::IntervalLayer_chat-1);
			pParentLayer->addChild(buttonMenu, ChatPopContainerZ_btnSend, ChatPopContainerTAG_btnSend);
			//发送
			CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT047").c_str(), 
				CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			_btn->addChild(label, 0, 1);
			label->setColor(ccc3(255, 255, 255));
			label->setPosition(ccp(POSX(60), POSX(25)));
		}
		
	}
	//Close button
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(ChatPopContainer::clickCloseHandler) );
		_btnClose->setPosition( /*ccp(POSX(914), POSX(600))*/ccp(winSize.width - POSX(40), winSize.height - POSX(40)) );

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_chat-1);
		pParentLayer->addChild(buttonMenu, ChatPopContainerZ_btnClose, ChatPopContainerTAG_btnClose);
	}

	//

	//list
	_pKKListView = KKCCUIListView::listViewWithCCRect(CCRectMake(POSX(24), POSX(80), winSize.width - POSX(24 * 2), 
		winSize.height - POSX(80 * 2)), 30);
	_pKKListView->setIsRelativeAnchorPoint(true);
	_pKKListView->m_pri = TLE::IntervalLayer_chat;
    _pKKListView->setAnchorPoint(ccp(0,0));
	_pKKListView->setSpacingVertical(0);
	_pKKListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pKKListView->getPosition(), ccp(0, 0)));
	_pKKListView->setOnItemActionListener(this);
	pParentLayer->addChild(_pKKListView, ChatPopContainerZ_KKListView, ChatPopContainerTAG_KKListView);
	
//Doyang 20120717
	_pKKListView->release();
	//
	TextFieldTTF * pTextField = new TextFieldTTF();
	//pTextField->setString("input");
    pTextField->m_pri = TLE::IntervalLayer_chat-1;
	pParentLayer->addChild(pTextField, ChatPopContainerZ_TextFieldTTF,ChatPopContainerTAG_TextFieldTTF);
	pTextField->release();
	pTextField->setPosition(ccp(POSX(530), POSX(40)));
	//pTextField->setEmptyStr(true);
    pTextField->setUp(this, POSX(380));
	pTextField->detachWithIME();
	//

	schedule (schedule_selector (ChatPopContainer::sendCDStep), 0.6f);

	return true;
}

void ChatPopContainer::sendCDStep(float dt)
{
	if (_canSend)
		return;

	_CDCounter += dt;
	if (_CDCounter >= 2.0f)
	{
		_CDCounter = 0.0f;
		_canSend = true;
	}
}

void ChatPopContainer::clearCacheNodes()
{
	for (int i = 0; i < _cacheNodes.size(); i++)
	{
		_cacheNodes[i]->release();
	}
	_cacheNodes.clear();
}

void ChatPopContainer::reinitChatRecord(std::vector<ChatInfo>& vChatInfo)
{
	//清理
	_pKKListView->cleanLayer();
	//重新加入
	int curChannel = ChannelType::stringToChannel(_channelBtnLabelType);
	
	for (int i = 0; i < vChatInfo.size(); i++)
	{
		if ( !(vChatInfo[i].channel == 3 && _curChannel == 3) &&
			!(vChatInfo[i].channel == 2 && _curChannel == 2) &&
			!(vChatInfo[i].channel == 1 && _curChannel == 1) &&
			!(_curChannel == 0))
		{
			continue;
		}


		ChatItem* newNode = ChatPopContainer::chatItemFactory(&vChatInfo[i]);
		if (newNode)
		{
			_cacheNodes.push_back(newNode);
			//newNode->release();
		}
	
	}
	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void ChatPopContainer::addChatRecord(std::vector<ChatInfo>& vChatInfo)
{
	for (int i = 0; i < vChatInfo.size(); i++)
	{
		
		if ( !(vChatInfo[i].channel == 3 && _curChannel == 3) &&
			!(vChatInfo[i].channel == 32 && _curChannel == 2) &&
			!(vChatInfo[i].channel == 1 && _curChannel == 1) &&
			!(_curChannel == 0))
		{
			continue;
		}	


		ChatItem* newNode = ChatPopContainer::chatItemFactory(&vChatInfo[i]);
		if (newNode)
		{
			_cacheNodes.push_back(newNode);
			//newNode->release();
		}
	
	}
	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void ChatPopContainer::addChatRecord(ChatInfo* chatInfo)
{
	if (!chatInfo)
		return;

	if ( !(chatInfo->channel == 3 && _curChannel == 3) &&
		!(chatInfo->channel == 2 && _curChannel == 2) &&
		!(chatInfo->channel == 1 && _curChannel == 1) &&
		!(_curChannel == 0))
	{
		return;
	}	

	ChatItem* newNode = ChatPopContainer::chatItemFactory(chatInfo);
	if (newNode)
	{
		_cacheNodes.push_back(newNode);	
		//newNode->release();
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR

}

//添加频道弹出列表
void ChatPopContainer::onChannelBtnClick(CCObject* pSender)
{
	ChannelBtnClickLayer* tar = (ChannelBtnClickLayer*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_popChannels);
	if (!tar)
	{
		tar = new ChannelBtnClickLayer();
		tar->initWithParam(
			this, menu_selector(ChatPopContainer::onPopChannels), 
			this, menu_selector(ChatPopContainer::onPopChannels) );

		LayerManager::tipsLayer->addChild(tar, 0, TipsLayer::TipsLayerTAG_popChannels);
	}

}

/**
*  登录提示
* @param msg
*/		
void ChatPopContainer::loginTip(std::string msg)
{
	//_textPanel.loginTip(msg);
}
		

/**
* 初始化私聊信息 
* @param pmName 私聊对象
*/		
void ChatPopContainer::setPrivateChat(std::string pmName)
{
	if(pmName == "") return;
	//if(stage) stage.focus = _inputTextField;
	std::string selfName = RoleManage::Instance()->_accountInfo.name;
	if(pmName == selfName)
	{
		LangManager::msgShow("CHT011");
		return;
	}


	if (_channelBtnLabel && _channelBtnLabel->getParent())
	{
		_channelBtnLabelType = ChannelType::PRIVATE_STRING;
		//if (pmName.size() > 9)
		//	_channelBtnLabel->m_fFontSize = 14.0f;
		_channelBtnLabel->setString(pmName.c_str());//pmName.c_str()ValuesUtil::Instance()->getString("CHT046").c_str()
		setChannelBtnLabelColor();	
	}
			
}

/* 设置弹出菜单按钮字体颜色 */
void ChatPopContainer::setChannelBtnLabelColor()
{
	if (!_channelBtnLabel || !_channelBtnLabel->getParent())
		return;

	switch(_channelBtnLabelType)
	{
		case ChannelType::ALL_STRING:
			_channelBtnLabel->setColor(ccc3(255, 235, 157));//蓝色
			break;
		case ChannelType::WORLD_STRING:
			_channelBtnLabel->setColor(ccc3(255, 235, 157));//蓝色
			break;
		case ChannelType::GUILD_STRING:
			_channelBtnLabel->setColor(ccc3(255, 153, 51));//黄色
			break;
		case ChannelType::SYS_NOTICE_STRING:
			_channelBtnLabel->setColor(ccc3(233,133,25));//橙色
			break;
		case ChannelType::SYS_ACHIVE_STRING:
			_channelBtnLabel->setColor(ccc3(200,200,255));//红色
			break;
		default:
			_channelBtnLabel->setColor(ccc3(255, 51, 252));//紫色
			break;
	}
}
		
/**
	* 频道改变事件 
	* @param e
	*/		
void ChatPopContainer::onChannelChange(CCObject* pSender)
{
	int eparam = ((CCNode*)pSender)->getTag();
    
    //if (ChatPopContainerTAG_btnLookChannel_1+2 == eparam)
    //    return;// jun tuan hu lue
    
	if (_curChannel == eparam)
	{
		return;//已经选择了查看这个频道了
	}
	switch(eparam)
	{
		case 0://全部			
			_curChannel = 0;
			this->reinitChatRecord(ChatMsgManager::Instance()->messagesData[_curChannel]);
			//_textPanel.switchChannel(ChannelType.ALL);
			break;
		case 1://世界
			_curChannel = 1;
			this->reinitChatRecord(ChatMsgManager::Instance()->messagesData[_curChannel]);
			//_textPanel.switchChannel(ChannelType.WORLD);
			//_channelBtnLabel.text = ChannelType.WORLD_STRING;
			break;
		case 2://公会 还没做BTN
			//_curChannel = 2;
			_curChannel = 2;
			this->reinitChatRecord(ChatMsgManager::Instance()->messagesData[_curChannel]);
			//LangManager::msgShow("CHT048");
            //return;
			//_textPanel.switchChannel(ChannelType.GUILD);
			//_channelBtnLabel.text = ChannelType.GUILD_STRING;
			break;
		case 3://私聊
			_curChannel = 3;
			this->reinitChatRecord(ChatMsgManager::Instance()->messagesData[_curChannel]);
			//_textPanel.switchChannel(ChannelType.PRIVATE);
			break;

		
		case 4://弹出GM面板 还没做BTN
			LangManager::msgShow("CHT048");
			//channelBar.setIndex(_curChannel);
			//_dispatcher.dispatchEvent(new Event(PopEventName.SHOW_UI_GM));
			break;
		case 20://弹出历史公告面板 还没做BTN
			
			break;
		case 21://弹出成就面板 还没做BTN
			
			break;
		case 22://弹出充值面板 还没做BTN

			break;
	}

	//使当前所在频道按钮不可按（第三态），表示正在使用
       
	if (_pActiveChannelBtn)
		_pActiveChannelBtn->setIsEnabled(true);
	_pActiveChannelBtn = (CCMenuItemImage*)pSender;
	_pActiveChannelBtn->setIsEnabled(false);
	//setChannelBtnLabelColor();
}

/**
	* 弹出频道列表 
	* @param e
	*/		
void ChatPopContainer::onPopChannels(CCObject* pSender)
{
	int eparam = ((CCNode*)pSender)->getTag();
	
	switch(eparam)
	{
		case 1:
			_channelBtnLabelType = ChannelType::WORLD_STRING;
			//换字为：世界 和字体颜色
			if (_channelBtnLabel && _channelBtnLabel->getParent())
			{
				_channelBtnLabel->setString(ValuesUtil::Instance()->getString("CHT044").c_str());//pmName.c_str()ValuesUtil::Instance()->getString("CHT046").c_str()
				setChannelBtnLabelColor();	
			}
			break;
		case 2:
			_channelBtnLabelType = ChannelType::GUILD_STRING;
			//换字为：世界 和字体颜色
			if (_channelBtnLabel && _channelBtnLabel->getParent())
			{
				_channelBtnLabel->setString(ValuesUtil::Instance()->getString("CHT045").c_str());
				setChannelBtnLabelColor();	
			}
			break;
		case 3:	//打开私聊查找对象窗口
			{
				//加入名字输入框
				TextInputConfirm* pConfirm = (TextInputConfirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_textInputConfirm);
				if (pConfirm)
					pConfirm->removeFromParentAndCleanup(true);
				pConfirm = new TextInputConfirm();
				pConfirm->initWithParam(ValuesUtil::Instance()->getString("CHT049").c_str(), 
					this, 
					menu_selector(ChatPopContainer::setPrivateChatOK), 
					menu_selector(ChatPopContainer::setPrivateChatCancel));
				LayerManager::tipsLayer->addChild(pConfirm, TipsLayer::TipsLayerZ_textInputConfirm,TipsLayer::TipsLayerTAG_textInputConfirm);
				pConfirm->release();
			}
			
			
			break;
	}
	//setChannelBtnLabelColor();
	ChannelBtnClickLayer* popChannels = (ChannelBtnClickLayer*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_popChannels);
	if (popChannels)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_popChannels, true);
}

/**
	* 初始化私聊信息 
	* @param pmName 私聊对象
	*/		
void ChatPopContainer::setPrivateChatOK(CCObject* pSender)
{//_pmName

	TextInputConfirm* pConfirm = (TextInputConfirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_textInputConfirm);
	if (pConfirm)
	{
		std::string pmName = pConfirm->getString();
		std::string selfName = RoleManage::Instance()->_accountInfo.name;
		if(pmName == selfName){
			LangManager::msgShow("CHT011");
			return;
		}

		if (pmName.size() == 0)
		{
			LangManager::msgShow( "FRI016" );
			return;
		}
		//
		setPrivateChat(pmName);
	}

	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;


	/*
	if(!pmName) return;
	if(stage) stage.focus = _inputTextField;
	var selfName:String = RoleManage.getInstance().accountInfo.name;
	if(pmName == selfName){
		LangManager.msgShow("CHT011");
		return;
	}
	_channelBtnLabel.text = pmName;
	setChannelBtnLabelColor();
	*/
}

void ChatPopContainer::setPrivateChatCancel(CCObject* pSender)
{
	TextInputConfirm* pConfirm = (TextInputConfirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_textInputConfirm);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}

std::vector<LayerNode*>* ChatPopContainer::getViewList()
{
	return &_cacheNodes;
}

void ChatPopContainer::clickCloseHandler(CCObject* pSender)
{
	//
	_pKKListView->cleanLayer();
	this->removeAllChildrenWithCleanup(true);
	//close
	ChatPopContainer* _chatPopContainer = (ChatPopContainer*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chat);
	if (_chatPopContainer)
	{		
		LayerManager::intervalLayer->removeChildByTag(IntervalLayer::IntervalLayerTAG_chat, true);
	}	
	//
	ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	pChatMediator->_chatPopContainer = 0;
}

ChatItem* ChatPopContainer::chatItemFactory(ChatInfo* chatInfo)
{
	if (!chatInfo)
		return 0;
	ChatItem* newItem = new ChatItem();
	newItem->init(*chatInfo);
	return newItem;
}

/**
	* 发送聊天信息并进行验证
	* @param e
	*/
void ChatPopContainer::sendMessage(CCObject* pSender)
{
	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}

	//频繁发送客户端拦截提示 begin
	if(_canSend == false)
	{
		ChatInfo msgInfo = ChatInfo();
		msgInfo.channel = ChannelType::ALL;
		msgInfo.content =  ValuesUtil::Instance()->getString("CHT013");

		ChatMsgManager::Instance()->addMessage(&msgInfo);

		ChatPopContainer* getisPop = (ChatPopContainer*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chat);
		if (getisPop)
		{		
			systemTip(&msgInfo);
		}

		return;
	}
	//
	AccountInfoVo info = RoleManage::Instance()->_accountInfo;
	if (_channelBtnLabelType == ChannelType::GUILD_STRING && info.guild == 0)
	{
		ChatInfo msgInfo = ChatInfo();
		msgInfo.channel = ChannelType::ALL;
		msgInfo.content =  ValuesUtil::Instance()->getString("CHT023");

		ChatMsgManager::Instance()->addMessage(&msgInfo);

		ChatPopContainer* getisPop = (ChatPopContainer*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chat);
		if (getisPop)
		{		
			systemTip(&msgInfo);
		}

		return;
	}


	//频繁发送客户端拦截提示 end
	//设置发送拦截 begin
	_canSend = false;
	//设置发送拦截 end

	TextFieldTTF* _inputTextField = (TextFieldTTF*)pParentLayer->getChildByTag(ChatPopContainerTAG_TextFieldTTF);
	if (!_inputTextField)
		return;

	CCTextFieldTTF * pccTextField = (CCTextFieldTTF*)_inputTextField->m_pTrackNode;
	std::string _inputTextField_text = pccTextField->getString();

	
	if(_inputTextField_text == "") return;


	// special handle for replaying story
	// LH 20121016
	std::string strContent = _inputTextField_text;
	int len = strContent.length();
	if (strContent.length() >= 3
		&&((strContent[0] == 'p')||(strContent[0] == 'P'))
		&&(strContent[1] == ' '))
	{
		std::string strsub = strContent.substr(2 , len-1);
		int lenth = strsub.length();
		bool isInt = true;
		for (int i = 0; i < lenth; i++)
		{
			if ((strsub[i] > '9')||(strsub[i] < '0'))
			{
				isInt = false;
				break;
			}
		}
		if (isInt)
		{
			// replay story
			int storyID = atoi(strsub.c_str());
			SceneStoryMediator * pMediator = (SceneStoryMediator *)g_pFacade->retrieveMediator(AppFacade_SCENESTORY_PROXY_CHANGE);
			if (pMediator)
			{
				clickCloseHandler(0);
				pMediator->tweenToTargetStartStory(storyID);
			}
			return;
		}
	}

	struct MSGOBJ
	{
		std::string name;
		int32 channel;
		std::string msg;
		std::string data;
	};

	int channel = ChannelType::stringToChannel(_channelBtnLabelType);

	MSGOBJ msgObj;
	msgObj.name = (_channelBtnLabelType == ChannelType::PRIVATE_STRING && _channelBtnLabel)?_channelBtnLabel->getString():"";//私聊：其他
	msgObj.channel = channel; if (msgObj.channel == 0) msgObj.channel = 1;//如果玩家用全部来说，就强制转为世界：1
	msgObj.msg = _inputTextField_text;
	msgObj.data = "";
    
    _inputTextField->setString("");
	dispatchEvent(SEND_CHAT_MESSAGE, (char*)&msgObj);








	//chatTextFieldVisible(true);	//先打开聊天信息面板
	//_inputTextField.text = _inputTextField.text.replace(/^\s*|\s*$/g, ""); //去掉前后空格
	//_inputTextField.text = _inputTextField.text.replace(ChatModel.HYPERLINK_REGEXP, "");
	//var content:String = _inputTextField.text;
	//if(content == "") return;
	//if (_wiatTime > 0)
	//{
	//	_inputTextField.text = "";
	//	stage.focus = _inputTextField;
	//	systemTip(LangManager.getText("CHT013"));
	//	return;
	//}
	//var info:AccountInfoVo = RoleManage.getInstance().accountInfo;
	//if (_channelBtnLabel.text == ChannelType.GUILD_STRING && info.guild == 0)
	//{
	//	_inputTextField.text = "";
	//	stage.focus = _inputTextField;
	//	systemTip(LangManager.getText("CHT023"));
	//	return;
	//}
	//_inputTextField.text = _inputTextField.text.replace(ChatModel.regExp1, "&lt;");
 //	_inputTextField.text = _inputTextField.text.replace(ChatModel.regExp2, "&gt;");
	//		
	////放入剧情测试
	//if(testStory(content)){
	//	return;
	//}
	//		
	//_wiatTime = setInterval(function():void
	//{
	//	clearInterval(_wiatTime);
	//	_wiatTime = 0;
	//}, _sendMesGap);
	//		
	//while(_inputTextField.text.indexOf("{") != -1){
	//	_inputTextField.text = _inputTextField.text.replace("{", ChatModel.REPLACE_MODEL);
	//}
	//		
	//var channel:int = ChannelType.stringToChannel(_channelBtnLabel.text);
	//var otherData:String = ChatLinker.matchAll();
	//var msgObj:Object = new Object();
	//msgObj.name = _channelBtnLabel.text;
	//msgObj.channel = channel;
	//msgObj.msg = _inputTextField.text;
	//msgObj.data = otherData;
	//dispatchEvent(new ParamEvent(SEND_CHAT_MESSAGE, msgObj));
	//		
	//ChatLinker.reset();
	//_inputTextField.text = "";
	//_inputTextField.maxChars = 60;
	//stage.focus = _inputTextField;
	//cacheHistroyData(content);
}

void ChatPopContainer::systemTip(ChatInfo* chatInfo)
{
	if (!chatInfo)
		return;

	ChatItem* newNode = ChatPopContainer::chatItemFactory(chatInfo);
	if (newNode)
	{
		_cacheNodes.push_back(newNode);	
		//newNode->release();
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void ChatPopContainer::onItemClickListener(LayerNode *itemCell, int position)
{
	if (!itemCell)
		return;


	ChatItem* itemc = (ChatItem*)itemCell;

	if (itemc->m_chatInfo.channel != 3)
	{//想世界说话 (军团GM先忽略)
		int32 selfId = RoleManage::Instance()->_accountInfo.accountId;

		if (selfId != itemc->m_chatInfo.fromId && itemc->m_chatInfo.fromId != 0)
		{//要和这个人私聊
			std::string useName = itemc->m_chatInfo.fromName;
			setPrivateChat(useName);	
		}
		else if (_channelBtnLabelType != ChannelType::WORLD_STRING)
		{
			_channelBtnLabelType = ChannelType::WORLD_STRING;
			//换字为：世界 和字体颜色
			if (this->getParent())
			{
				_channelBtnLabel->setString(ValuesUtil::Instance()->getString("CHT044").c_str());
				setChannelBtnLabelColor();	
			}		
		}
	}
	else
	{//想点人私聊
		int32 selfId = RoleManage::Instance()->_accountInfo.accountId;
		std::string useName = "none";
		if (selfId != itemc->m_chatInfo.fromId)
		{
			useName = itemc->m_chatInfo.fromName;
		}
		else if(selfId != itemc->m_chatInfo.toId)
		{
			useName = itemc->m_chatInfo.toName;
		}
		
		setPrivateChat(useName);	
	}

}