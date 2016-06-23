#include "StoryCityLists.h"
#include "TouchCityNode.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c3d/CCMD3DA.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"

StoryCityLists::StoryCityLists()
{
	_pListView = NULL;
	_currentTaskMapId = 0;
}

int StoryCityLists::getCount()
{
	return m_vMapList.size();
}

LayerNode * StoryCityLists::getView(int position)
{
	if ((uint32)position >= m_vMapList.size())
		return 0;
	else
	{
		//POSX edwardliu
		m_vMapList[position]->setvisibleSize(CCSizeMake(POSX(226), POSX(111)));
		m_vMapList[position]->setContentSize(CCSizeMake(POSX(226), POSX(111)));
		return m_vMapList[position];
	}
	
	//if(position >= _dataList.size())
	//	return NULL;
	//
	//int index = _dataList[position];
	//TouchCityNode* mapNode = new TouchCityNode(index);
	//if(mapNode)
	//{
	//	mapNode->setSpriteIcon(open);
	//}
}

void StoryCityLists::onItemClickListener(LayerNode *itemCell, int position)
{

	CCLog("click story map...position=%d", position);
	if(g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())
		return;

	if (!itemCell)
		return;

	this->sendMapRequest(indexToMapId(position + 1));
}

int StoryCityLists::indexToMapId(int index)
{
	return index + 1000;
}

void StoryCityLists::startListViewHandler()
{
	//¡¡Has connected a task list
	//POSX edwardliu
	if(!_pListView)
	{
		_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(2), POSX(2), POSX(240), POSX(518)), false);
	}
	if(_pListView)
	{
		_pListView->setIsRelativeAnchorPoint(true);
		_pListView->setAnchorPoint(ccp(0,0));
		//_pListView->setSpacingVertical(15);
		_pListView->setWorldSpaceLeftBottomPoint(ccp(_pListView->getPosition().x + this->getPosition().x + this->getParent()->getPosition().x,
			_pListView->getPosition().y + this->getPosition().y + this->getParent()->getPosition().y));
		_pListView->setOnItemActionListener(this);
		_pListView->m_pri = TLE::WindowLayer_Map;
		if(_pListView->getParent() == NULL)
		{
			this->addChild(_pListView);
			_pListView->release();
		}
	}
}

void StoryCityLists::initDataList(int index, bool open)
{
	bool i = true;
	std::vector<LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		if(*iter)
		{
			TouchCityNode* n = (TouchCityNode*)((*iter)->getChildByTag(0));
			if(n)
			{
				if(n->_nodeId == index)
					i = false;
			}
		}
	}

	if(i)
	{
		TouchCityNode* mapNode = new TouchCityNode(index);
		LayerNode* layerNode = new LayerNode();
		if(mapNode && layerNode)
		{
			mapNode->setSpriteIcon(open);
			layerNode->addChild(mapNode);
			//Doyang 20120712
			mapNode->release();
			m_vMapList.push_back(layerNode);
		}
	}

	// 20120625
	// Doyang
	// Add default opend map list.
	if(open)
	{
		if(index > _currentTaskMapId)
			_currentTaskMapId = index;
	}
}

void StoryCityLists::setViewAdapter()
{
	//Doyang 20120711
	/*CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
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
	}*/
	_pListView->setAdapter(this);

	// 20120625
	// Doyang
	// Add default opend map list.
	this->sendMapRequest(indexToMapId(_currentTaskMapId));
}

void StoryCityLists::clearDataList()
{
	std::vector<LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		if(*iter)
		{
			(*iter)->removeAllChildrenWithCleanup(true);
			(*iter)->release();
		}
	}
	m_vMapList.clear();
}

void StoryCityLists::sendMapRequest( int mapId )
{
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		CCMD3DA ccmd3da;
		ccmd3da._id = mapId;//indexToMapId(position + 1);
		pSocket->sendMessage(&ccmd3da);
	}
}
