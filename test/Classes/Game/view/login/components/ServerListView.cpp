#include "ServerListView.h"
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

ServerListView::ServerListView()
{
	_pListView = 0;
	setPreSeclecedItem(0);
	setIsServSelected(false);
}

ServerListView::~ServerListView()
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

bool ServerListView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(CCPOINT_SERVER_LIST.x,
		CCPOINT_SERVER_LIST.y,
		CCSIZE_SERVER_LIST.width,
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

int ServerListView::getCount()
{
	int nCount = 0;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->find(getAreaID());
	if (iter != _servListVoDic->end())
	{
		nCount = iter->second.size();
	}
	return nCount;
}

LayerNode * ServerListView::getView(int position)
{
	LayerNode *pListLayer = new LayerNode();

	CCUIBackground * pListItemBack = new CCUIBackground();
	pListItemBack->initWithSpriteFrame("ui2.png",CCPointZero,CCPointZero,CCSizeMake(POSX(230),POSX(70)));	
	pListLayer->setAnchorPoint(CCPointZero);
	pListLayer->setContentSize(pListItemBack->getContentSize());
	pListLayer->setvisibleSize(pListLayer->getContentSize());
	pListLayer->setTag(position);
	pListLayer->addChild(pListItemBack,0);
	pListItemBack->release();

	std::string szServName("");
	ccColor3B color = ccc3(12,233,25);
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->find(getAreaID());
	if (iter != _servListVoDic->end())
	{
		std::map<int/*servID*/,ServerListVo>::iterator it = iter->second.find(position);
		if (it != iter->second.end())
		{
			ServerListVo * pSerListVo = &it->second;
			if (pSerListVo)
			{
				szServName = pSerListVo->servName;
				switch (pSerListVo->state)
				{
				case 0:
					color = ccc3(12,233,25);
					break;
				case -1:
					color = ccc3(70,80,90);
					break;
				case 1:
					color = ccc3(255,233,12);
					break;
				case 2:
					break;
					color = ccc3(255,0,0);
				default:
					color = ccc3(12,233,25);
					break;
				}
			}
		}
	}
	CCLabelTTF * pLabText = CCLabelTTF::labelWithString(szServName.c_str(),CCSizeMake(POSX(200),POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(28));
	
	pLabText->setColor(color);
	pLabText->setPosition(ccp((pListLayer->getContentSize().width/2),(pListLayer->getContentSize().height/2)));
	pListLayer->addChild(pLabText,2);
	return pListLayer;
}

void ServerListView::onItemClickListener( LayerNode *itemCell, int position )
{
	CCSprite * pSpriteLight = CCSprite::spriteWithSpriteFrameName("login/login_area.png");
	pSpriteLight->setPosition(ccp((itemCell->getContentSize().width/2),(itemCell->getContentSize().height/2)));
	itemCell->addChild(pSpriteLight,1,TAG_LIGHT);
	LayerNode * pPreLayer = getPreSeclecedItem();
	if (pPreLayer&&pPreLayer->getChildByTag(TAG_LIGHT))
	{
		pPreLayer->removeChildByTag(TAG_LIGHT,true);
	}
	setPreSeclecedItem(itemCell);

	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->find(getAreaID());
	if (iter != _servListVoDic->end())
	{
		std::map<int/*servID*/,ServerListVo>::iterator it = iter->second.find(position);
		if (it != iter->second.end())
		{
			ServerListVo * pSerListVo = &it->second;
			if (pSerListVo)
			{
				LoginServer * pLoginServ = (LoginServer *)this->getParent();
				if (pLoginServ)
				{
					LoginView * pLoginView = (LoginView *)pLoginServ->getParent();
					if (pLoginView)
					{
						pLoginView->setSelectedArea(pSerListVo->areaName);
						pLoginView->setSelectedServ(pSerListVo->servName);
					}
				}

				this->setSelectIP(pSerListVo->ip);
				this->setSelectedPort(pSerListVo->port);
				this->setServState(pSerListVo->state);

				g_pLoginManage->setServIPAddr(pSerListVo->ip);
				g_pLoginManage->setServIPPort(pSerListVo->port);
				g_pLoginManage->setServState(pSerListVo->state);
				g_pLoginManage->setExchargeServerId(pSerListVo->exchargeServerId);

				setIsServSelected(true);
			}
		}
	}
}

void ServerListView::onItemTouchListener( LayerNode *itemCell, int position )
{

}

void ServerListView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{

}

void ServerListView::refresh()
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
