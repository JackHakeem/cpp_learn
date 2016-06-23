#include "MsgMediator.h"
#include "events/GameDispatcher.h"
#include "SpriteBtn.h"
#include "manager/LayerManager.h"
#include "model/notice/NoticeManager.h"
#include "view/noticeCenter/components/CenterView.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/ViewManager.h"
#include "control/friend/FriendProxyCommand.h"

MsgMediator::MsgMediator()
{
	_num = 0;
	_btnFriend = 0;
	//_wSocket = GameServerSocket.getInstance();
	//_gSocket = GateServerSocket.getInstance();
	_targetBtn = 0;
	_msgView = 0;
	_dispatcher = GameDispatcher::getInstance();
	//_noticeManage = g_pNoticeManager;

	//_noticeManage = NoticeManager.getInstance();
	//_globalManager = GlobalManage.getInstance();
	//_globalManager.addEventListener(GlobalManage.ENTIRELY_ENTER_GAME,sendCmd);
	//_taskProxy = facade.retrieveProxy(TaskProxy.NAME) as TaskProxy;
	//_farmProxy = facade.retrieveProxy(FarmProxy.NAME) as FarmProxy;
	//_traderProxy = facade.retrieveProxy(TraderProxy.NAME) as TraderProxy;
	//_crysProxy = facade.retrieveProxy(CrystalProxy.NAME) as CrystalProxy;
}

void MsgMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case NEW_FRIEND_MSG:
		{
			newFriendMsg();
		}break;
	default:
		break;
	}
}

void MsgMediator::newFriendMsg()
{
	//if(!GlobalManage.getInstance().isEnterGame) 
	//	return;

//	_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_NOTIFY_REQ); 

	CCMenu* buttonMenu = (CCMenu*)LayerManager::sceneUILayer->getChildByTag(SceneUILayer::SceneUILayerTAG_btnFriend);
	if (buttonMenu)
	{
		LayerManager::sceneUILayer->removeChildByTag(SceneUILayer::SceneUILayerTAG_btnFriend, true);
	}

	_btnFriend = 0;

	if(!_btnFriend/*||!LayerManager::sceneUILayer.contains(_btnFriend)*/)
	{
		CCSize winsize = CCDirector::sharedDirector()->getWinSize();

		_btnFriend = SpriteBtnFactory::make(ValuesUtil::Instance()->getString("NTC006").c_str(), 30, 30, this, menu_selector(MsgMediator::showMsg));
		
		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btnFriend, 0, SceneUILayer::SceneUILayerTAG_btnFriend);
		buttonMenu->setPosition(ccp(0, 0));
		LayerManager::sceneUILayer->addChild(buttonMenu, SceneUILayer::SceneUILayerZ_btnFriend, SceneUILayer::SceneUILayerTAG_btnFriend);
		buttonMenu->release();

		_num++;
		_noteArr.push_back(buttonMenu);
		_btnFriend->setPosition(ccp(winsize.width/2, POSX(100.0f)));
		/*
		tweenThatFucker(_btnFriend);
		*/
	}	
}

void MsgMediator::showMsg(CCObject* pSender)
{
	_targetBtn = _btnFriend;
	openNews();
	/*
	CCMenu* buttonMenu = (CCMenu*)LayerManager::sceneUILayer->getChildByTag(SceneUILayer::SceneUILayerTAG_btnFriend);
	if (buttonMenu)
	{
		LayerManager::sceneUILayer->removeChildByTag(SceneUILayer::SceneUILayerTAG_btnFriend, true);
		_btnFriend = 0;
	}
	*/
}

void MsgMediator::openNews()
{
	if (_msgView && _msgView->getisPop() == true)
	{
		return;
	}

	int _type = _targetBtn->getTag()-NOTICE_START;

	NoticeManager::NoteElmArr* arr = g_pNoticeManager->getArrByType(_type);
	if (!arr)
		return;

	if (!_msgView)
	{
		_msgView = new CenterView();
		_msgView->init(_type, arr);	
		addListener();
		ViewManager::getInstance()->_centerView = _msgView;
	}
	else
		_msgView->reLocate();

	_msgView->setisPop(!_msgView->getisPop());
	
}

void MsgMediator::addListener()
{
	_msgView->addEventListener(CenterView::ADD_FRIEND, this, callfuncND_selector(MsgMediator::addFriendHandler));
	//_msgView->addEventListener(CenterView::BLESS_FRIEND,callfuncND_selector(blessFriendHandler));
	//_msgView->addEventListener(CenterView::SEE_REPORT,callfuncND_selector(seeReportHandler));
	//_msgView->addEventListener(CenterView::GOTO_NPC,callfuncND_selector(toNpcHandler));

	//_msgView->addEventListener(PopContainer::CLOSE_CONTAINER,callfuncND_selector(closeHandler));
	//_msgView->addEventListener(CenterView::REMOVE_BTN,callfuncND_selector(removeBtnHandler));
}

void MsgMediator::addFriendHandler(CCNode* n, void* data)
{
	sendNotification(Facade_Command, AppFacade_Friend_PROXY_CHANGE, (char*)data, FriendProxyCommand::CHECK_REQUEST);
}