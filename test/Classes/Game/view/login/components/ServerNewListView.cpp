#include "ServerNewListView.h"
#include "manager/TouchLayerEnum.h"
#include "UIListView/CCUIListView.h"
#include "LayerNode.h"
#include "SpriteNode.h"
#include "CCUIBackground.h"
#include "ServerListVo.h"
#include "LoginManage.h"
#include "LoginMain.h"
#include "LoginServer.h"
#include "LoginView.h"
#include "LHMenuItemLabel.h"

ServerNewListView::ServerNewListView()
{
	_pListView = 0;
	_CurLightIndex = -2;
	setPreSeclecedItem(0);
	setIsServSelected(false);
}

ServerNewListView::~ServerNewListView()
{
	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		pChildLayer->removeFromParentAndCleanup(true);
		pChildLayer->release();
	}

	//_pListView->release();
}

bool ServerNewListView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(CCPOINT_SERVER_LIST.x,
		CCPOINT_SERVER_LIST.y,
		CCSIZE_SERVER_LIST.width - POSX(100),
		CCSIZE_SERVER_LIST.height), 
		false);

	if(!_pListView) 
		return false;
	_pListView->setAnchorPoint(CCPointZero);
	//_pListView->setClipLayerRect(CCRECT_TASK_LIST_CLIP);
	_pListView->setSpacingVertical(POSX(14));
	_pListView->setAdapter(this);
	_pListView->setOnItemActionListener(this);
	this->setContentSize(_pListView->getContentSize());
	_pListView->setTag(TAG_LIST);
	this->addChild(_pListView);
    _pListView->release();
	return true;
}

int ServerNewListView::getCount()
{
	int nCount = 0;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->begin();
	for (iter ; iter != _servListVoDic->end() ; iter++)
	{
		nCount += iter->second.size();
	}

	return (nCount + 1)/2;
}

LayerNode * ServerNewListView::getView(int position)
{
	LayerNode *pListLayer = new LayerNode();

	std::vector<ServerListVo> servList = g_pLoginManage->getServerList();

	CCUIBackground * pListItemBackLeft = new CCUIBackground();
	pListItemBackLeft->initWithSpriteFrame("ui2.png",CCPointZero,CCPointZero,CCSizeMake(POSX(320),POSX(70)));
	pListLayer->setAnchorPoint(CCPointZero);
	pListLayer->setContentSize(CCSizeMake(POSX(700),POSX(70)));
	pListLayer->setvisibleSize(pListLayer->getContentSize());
	pListLayer->setTag(position);
	pListLayer->addChild(pListItemBackLeft,0);
	pListItemBackLeft->release();

	CCPoint pos = pListItemBackLeft->getPosition();
	CCSize size = pListItemBackLeft->getContentSize();
	
	if (( position + 1 ) * 2 <= servList.size())
	{
		CCUIBackground * pListItemBackRight = new CCUIBackground();
		pListItemBackRight->initWithSpriteFrame("ui2.png",CCPointZero,CCPointZero,CCSizeMake(POSX(320),POSX(70)));
		pListItemBackRight->setPositionX(pos.x + POSX(378));
		pListLayer->addChild(pListItemBackRight,0);
		pListItemBackRight->release();	
	}
	
	
	
	// for new UI

	//CCMenuItemLabel * pMenuItemLeftFont = 0;
	//CCMenuItemLabel * pMenuItemRightFont = 0;
	LHMenuItemLabel * pMenuItemLeftFont = 0;
	LHMenuItemLabel * pMenuItemRightFont = 0;
	{// left item
		std::string szServLeftItemText("");
		ccColor3B color = ccc3(12,233,25);

		szServLeftItemText.append(servList[position * 2].areaName);
		szServLeftItemText.append(" - ");
		szServLeftItemText.append(servList[position * 2].servName);

		CCLabelTTF * pLabTextLeft = CCLabelTTF::labelWithString(szServLeftItemText.c_str(),CCSizeMake(POSX(310),POSX(34)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(24));
		pLabTextLeft->setColor(color);
		pLabTextLeft->setAnchorPoint(ccp( 0 , 0.5));
		pMenuItemLeftFont = new LHMenuItemLabel();
		pMenuItemLeftFont->initWithLabel(pLabTextLeft , this , menu_selector(ServerNewListView::onServerSelected) , POSX(24) , POSX(0.5));
		pMenuItemLeftFont->setPosition(ccp(pos.x + size.width/2 - POSX(30) , pos.y));
		pMenuItemLeftFont->setTag(position * 2);

		// left state
		char path[32] = {0};
		sprintf(path , "new_res/state%d.png" , servList[position * 2].state);
		CCSprite * pSpriteState = CCSprite::spriteWithSpriteFrameName(path);
		pSpriteState->setPosition(ccp(pos.x + size.width  - POSX(30) , pos.y+ size.height/2));
		pSpriteState->setOpacity(255);
		pListLayer->addChild(pSpriteState,3);
	}

	if (( position + 1 ) * 2 <= servList.size())
	{// right item
		std::string szServRightItemText("");
		ccColor3B color = ccc3(12,233,25);

		szServRightItemText.append(servList[position * 2 + 1].areaName);
		szServRightItemText.append(" - ");
		szServRightItemText.append(servList[position * 2 + 1].servName);

		CCLabelTTF * pLabTextRight = CCLabelTTF::labelWithString(szServRightItemText.c_str(),CCSizeMake(POSX(310),POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(24));
		pLabTextRight->setColor(color);
		pLabTextRight->setAnchorPoint(ccp( 0 , 0.5));
		pMenuItemRightFont = new LHMenuItemLabel();
		pMenuItemRightFont->initWithLabel(pLabTextRight , this , menu_selector(ServerNewListView::onServerSelected) , POSX(24) , POSX(0.5));
		pMenuItemRightFont->setPosition(ccp(pos.x + size.width/2  - POSX(30) + POSX(378) , pos.y));
		pMenuItemRightFont->setTag(position * 2 + 1);

		// right state
		char path[32] = {0};
		sprintf(path , "new_res/state%d.png" , servList[position * 2 + 1].state);
		CCSprite * pSpriteState = CCSprite::spriteWithSpriteFrameName(path);
		pSpriteState->setPosition(ccp(pos.x + size.width - POSX(30) + POSX(378) , pos.y + size.height/2));
		pSpriteState->setOpacity(255);
		pListLayer->addChild(pSpriteState,3);
	}
	
	CCMenu * pMenu = 0;
	if (pMenuItemRightFont)
	{
		pMenu = CCMenu::menuWithItems(pMenuItemLeftFont , pMenuItemRightFont , 0);
	}
	else
	{
		pMenu = CCMenu::menuWithItems(pMenuItemLeftFont ,  0);
	}	
	
	pMenu->setTouchLayer(_pListView->m_pri - 1);

	pMenu->setPosition(ccp(0 ,(pListLayer->getContentSize().height/2)));
	pListLayer->addChild(pMenu,2);

	if (pMenuItemLeftFont)
	{
		pMenuItemLeftFont->release();
	}
	if (pMenuItemRightFont)
	{
		pMenuItemRightFont->release();
	}

	return pListLayer;
}

void ServerNewListView::onServerSelected(CCObject * pSender)
{
	if (!pSender)
	{
		return;
	}
	CCMenuItemLabel  * pNode = (CCMenuItemLabel *) pSender;
	int tag = pNode->getTag();
	std::vector<ServerListVo> servList = g_pLoginManage->getServerList();
	if (tag >= 0 && tag < servList.size())
	{
		this->setSelectIP(servList[tag].ip);
		this->setSelectedPort(servList[tag].port);
		this->setServState(servList[tag].state);

		g_pLoginManage->setServIPAddr(servList[tag].ip);
		g_pLoginManage->setServIPPort(servList[tag].port);
		g_pLoginManage->setServState(servList[tag].state);
		g_pLoginManage->setExchargeServerId(servList[tag].exchargeServerId);

		g_pLoginManage->_CurServListVo = servList[tag];

		LoginServer * pLoginServer = (LoginServer *)this->getParent();
		if (pLoginServer)
		{
			//std::string str(servList[tag].areaName);
			//str.append("-");
			std::string str(servList[tag].servName);
			pLoginServer->setSelectedServer(str);
			pLoginServer->enableConfirmButton(true);
		}

		setIsServSelected(true);
	}

	//Light
	setItemLight((CCNode *)pSender);

	LoginServer * pLoginServer = (LoginServer *)this->getParent();
	if (pLoginServer)
	{
		/*
		LoginView * pLoginView = (LoginView *)pLoginServer->getParent();
		if (pLoginView)
		{
			pLoginView->runMyAction(pLoginServer , pLoginView->getMyAction(LoginView::ActType_Fade1));
		}
		*/
		pLoginServer->onNewServerConfirmMenuClick(0);
	}

}

void ServerNewListView::setItemLight(CCNode * pSender)
{
	if (!pSender)
	{
		return;
	}
	
	CCMenuItemLabel  * pNode = (CCMenuItemLabel *) pSender;
	int tag = pNode->getTag();
	LayerNode * pItemLayerPre = getItemLayerByIndex(_CurLightIndex);
	if (pItemLayerPre)
	{
		pItemLayerPre->removeChildByTag(TAG_LIGHT , true);
	}
	LayerNode * pItemLayerNow = getItemLayerByIndex(tag);
	if (pItemLayerNow)
	{
		pItemLayerNow->removeChildByTag(TAG_LIGHT , true);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_server.plist");
		CCSprite * pLightSprite = CCSprite::spriteWithSpriteFrameName("login/login_area.png");
		CCPoint pos = pNode->getPosition();
		CCSize size = pNode->getContentSize();
		pLightSprite->setAnchorPoint(ccp(0.5 , 0));
		pLightSprite->setPosition(ccp(pos.x , pos.y + size.height/2));
		pItemLayerNow->addChild(pLightSprite , 1 , TAG_LIGHT);
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_server.plist");
		_CurLightIndex = tag;
	}	
}

int ServerNewListView::getListTouchPri()
{
	if (_pListView)
	{
		return _pListView->m_pri;
	}	
	return 0;
}

void ServerNewListView::onItemClickListener( LayerNode *itemCell, int position )
{

}

void ServerNewListView::onItemTouchListener( LayerNode *itemCell, int position )
{

}

void ServerNewListView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{

}

void ServerNewListView::refresh()
{
    if (_pListView)
    {
        CCMutableArray<LayerNode *> * pListNode = _pListView->getChilds();
        CCMutableArray<LayerNode *>::CCMutableArrayIterator iter = pListNode->begin();
        for (;iter != pListNode->end(); iter++)
        {
            LayerNode * pLayer = (LayerNode *)(*iter);
            if (!pLayer)		{	continue;	}				
            pLayer->removeFromParentAndCleanup(true);
            pLayer->release();
        }
        
        _pListView->setAdapter(this);
    }
}

LayerNode * ServerNewListView::getItemLayerByIndex(int index)
{
	if ( index < 0 )
	{
		return 0;
	}

	if (_pListView)
	{
		CCMutableArray<LayerNode *> * pListNode = _pListView->getChilds();
		CCMutableArray<LayerNode *>::CCMutableArrayIterator iter = pListNode->begin();
		int position = index/2;
		int i = 0;
		for (iter ; iter != pListNode->end(); iter++)
		{
			if (i == position)
			{
				return (LayerNode *)(*iter);
			}
			++i;
		}
	}
	return 0;
}
