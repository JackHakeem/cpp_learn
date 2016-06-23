#include "AreaListView.h"
#include "manager/TouchLayerEnum.h"
#include "UIListView/CCUIListView.h"
#include "LayerNode.h"
#include "SpriteNode.h"
#include "LoginManage.h"
#include "ServerListVo.h"
#include "CCUIBackground.h"
#include "LoginServer.h"
#include "ServerListView.h"
#include "BaseType.h"
#include "LoginMain.h"
#include "LoginView.h"
AreaListView::AreaListView()
{
	_pListView = 0;
	setPreSeclecedItem(0);
	setIsAreaSelected(false);
}

AreaListView::~AreaListView()
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

	_pListView->release();
}

bool AreaListView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(CCPOINT_AREA_LIST.x,
		CCPOINT_AREA_LIST.y,
		CCSIZE_AREA_LIST.width,
		CCSIZE_AREA_LIST.height), 
		false);

	if(!_pListView)
		return false;
	_pListView->setAnchorPoint(CCPointZero);
	//_pListView->setClipLayerRect(CCRECT_TASK_LIST_CLIP);
	_pListView->setSpacingVertical(POSX(20));
	_pListView->setAdapter(this);
	_pListView->setOnItemActionListener(this);
	this->setContentSize(_pListView->getContentSize());
	_pListView->setTag(TAG_LIST);
	//_pListView->m_pri = TLE::LoginLayer;
	this->addChild(_pListView);
	_pListView->release(); //Kenfly 20130125

	return true;
}

int AreaListView::getCount()
{
	int nCount = 0;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->begin();
	while (iter != _servListVoDic->end())
	{
		nCount = iter->first;
		++iter;
	}
	++nCount;
	return nCount;
}

LayerNode * AreaListView::getView(int position)
{
	LayerNode *pListLayer = new LayerNode();

	CCUIBackground * pListItemBack = new CCUIBackground();
	pListItemBack->initWithSpriteFrame("ui2.png",CCPointZero,CCPointZero,CCSizeMake(POSX(230),POSX(60)));	
	pListLayer->setAnchorPoint(CCPointZero);
	pListLayer->setContentSize(pListItemBack->getContentSize());
	pListLayer->setvisibleSize(pListLayer->getContentSize());
	pListLayer->setTag(position);
	pListLayer->addChild(pListItemBack);
	//Doyang 20120712
	pListItemBack->release();
	
	std::string szServName("");
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->find(position);
	if (iter != _servListVoDic->end())
	{
		std::map<int/*servID*/,ServerListVo>::iterator it = iter->second.begin();
		if (it != iter->second.end())
		{
			ServerListVo * pSerListVo = &it->second;
			if (pSerListVo)
			{
				szServName = pSerListVo->areaName;
			}
		}
	}
	CCLabelTTF * pLabText = CCLabelTTF::labelWithString(szServName.c_str(),CCSizeMake(POSX(200),POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(28));
	pLabText->setColor(ccc3(12,233,25));
	pLabText->setPosition(ccp(pListLayer->getContentSize().width/2,pListLayer->getContentSize().height/2));
	pListLayer->addChild(pLabText,2);

	return pListLayer;
}

void AreaListView::onItemClickListener( LayerNode *itemCell, int position )
{
	LoginServer * pLoginServer = (LoginServer *)this->getParent();
	if (!pLoginServer){return;}
	ServerListView * pServListView = (ServerListView *)pLoginServer->getChildByTag(LoginServer::TAG_SERV_LIST);
	if (!pServListView){return;}
	CCUIListView * pListView = (CCUIListView *)pServListView->getChildByTag(TAG_LIST);
	if (!pListView){return;}

	CCSprite * pSpriteLight = CCSprite::spriteWithSpriteFrameName("login/login_area.png");
	pSpriteLight->setPosition(ccp(itemCell->getContentSize().width/2,itemCell->getContentSize().height/2));
	itemCell->addChild(pSpriteLight,1,TAG_LIGHT);
	LayerNode * pPreLayer = getPreSeclecedItem();
	if (pPreLayer&&pPreLayer->getChildByTag(TAG_LIGHT))
	{
		pPreLayer->removeChildByTag(TAG_LIGHT,true);
	}
	setPreSeclecedItem(itemCell);

	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->find(position);
	if (iter != _servListVoDic->end())
	{
		pServListView->setAreaID(iter->first);
		std::map<int/*servID*/,ServerListVo>::iterator it = iter->second.begin();
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
				g_pLoginManage->setServIPAddr(pSerListVo->ip);
				g_pLoginManage->setServIPPort(pSerListVo->port);
				g_pLoginManage->setServState(pSerListVo->state);

				setIsAreaSelected(true);
			}
		}
	}
	pListView->setAdapter((CCUIListViewAdapter *)pServListView);

	//pLoginServer->EnableConfirmButton(true);
}

void AreaListView::onItemTouchListener( LayerNode *itemCell, int position )
{

}

void AreaListView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{

}

void AreaListView::refresh()
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