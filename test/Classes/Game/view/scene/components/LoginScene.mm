#include "LoginScene.h"
#include "view/login/components/LoginView.h"
#include "events/GameDispatcher.h"
#include "socket/network/GateServerSocket.h"
#include "socket/network/GameServerSocket.h"
#include "MainScene.h"
#include "MessageInfoBox.h"
#include "utils/ValuesUtil.h"
#include "LoginManage.h"
#include "Connect91Handler.h"
//#include "Connect4399Handler.h"

static LoginScene * m_pLoginSceneInstance;

LoginScene::LoginScene()
{
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::GATE_SERVER_CONNECT_FAILED,
		this,
		callfuncND_selector(LoginScene::onGateServerConnectFailed));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::GATE_SERVER_CONNECT_SUCCESS,
		this,
		callfuncND_selector(LoginScene::onGateServerConnectSuccess));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::GAME_SERVER_CONNECT_FAILED,
		this,
		callfuncND_selector(LoginScene::onGameServerConnectFailed));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::GAME_SERVER_CONNECT_SUCCESS,
		this,
		callfuncND_selector(LoginScene::onGameServerConnectSuccess));	


	GateServerSocket::getInstance();
	/*pGateSocket->setTag(GATE_SERVER_TAG);
	this->addChild(pGateSocket, 0);*/
	GameServerSocket::getInstance();
	/*pSocketGame->setTag(GATE_SERVER_TAG);
	this->addChild(pSocketGame, 0);*/
	m_pLoginSceneInstance = 0;

}

bool LoginScene::init()
{
	if(!CCScene::init())
	{
		return false;
	}

	g_pLoginManage->_pLoginView = new LoginView();
	if(g_pLoginManage->_pLoginView && g_pLoginManage->_pLoginView->init())
	{
		this->addChild(g_pLoginManage->_pLoginView);
		//g_pLoginManage->_pLoginView->release();
	}

//  	g_pLoginManage->_pLoginView->removeFromParentAndCleanup(true);
// 	g_pLoginManage->_pLoginView->release();
	
	[[Connect91Handler sharedTo91] versionUpdateCheck];
    // Doyang 20120927 
    // 4399sy.com
//    [[Connect4399Handler sharedTo4399] login];

	return true;
}

void LoginScene::onGateServerConnectFailed( CCNode *pNode, void *data )
{
	CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
	//MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("LG023"),ccc3(12,233,25));
	//CCMessageBox("onGateServerConnectFailed", "");
	clearChilds();
}

void LoginScene::onGateServerConnectSuccess( CCNode *pNode, void *data )
{
	//MessageInfoBox::Instance()->show("onGateServerConnectSuccess",ccc3(12,233,25));
	//CCMessageBox("onGateServerConnectSuccess", "");
	clearChilds();
}

void LoginScene::onGameServerConnectFailed( CCNode *pNode, void *data )
{
	CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
	//MessageInfoBox::Instance()->show("onGameServerConnectFailed",ccc3(12,233,25));
	//CCMessageBox("onGameServerConnectFailed", "");
	clearChilds();
}

void LoginScene::onGameServerConnectSuccess( CCNode *pNode, void *data )
{
	//MessageInfoBox::Instance()->show("onGameServerConnectSuccess",ccc3(12,233,25));
	//CCMessageBox("onGameServerConnectSuccess", "");
	clearChilds();
}

void LoginScene::onLoginFailed(CCNode *pNode, void *data)
{
	//MessageInfoBox::Instance()->show("Failed",ccc3(12,233,25));
	//CCMessageBox("onLoginFailed", "");
	clearChilds();
}

void LoginScene::clearChilds()
{
	/*this->removeChildByTag(GATE_SERVER_TAG, true);
	this->removeChildByTag(GAME_SERVER_TAG, true);*/
}

LoginScene * LoginScene::getInstance()
{
	if(m_pLoginSceneInstance == NULL)
	{
		//m_pMainSceneInstance = MainScene::node();
		m_pLoginSceneInstance = new LoginScene();
	}
	if(m_pLoginSceneInstance)
	{
		return m_pLoginSceneInstance;
	}
	return NULL;
}

LoginScene::~LoginScene()
{
	CCLog( "LoginScene release." );
}

