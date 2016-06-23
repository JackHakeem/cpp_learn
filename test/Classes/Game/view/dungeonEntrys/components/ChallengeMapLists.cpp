#include "ChallengeMapLists.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"

ChallengeMapLists::ChallengeMapLists()
{
	_pListView = NULL;
	_mapCnt = 0;
}

int ChallengeMapLists::getCount()
{
	return m_vMapList.size();
}

ChallengeMapLists::~ChallengeMapLists()
{
	//if (!m_vMapList.empty())
	//{
	//	std::map<int, LayerNode*>::iterator listItemIt;
	//	for(listItemIt = m_vMapList.begin();
	//		listItemIt != m_vMapList.end();
	//		++listItemIt)
	//	{
	//		LayerNode *tmp = listItemIt->second;
	//		if(tmp && tmp->getParent())
	//		{
	//			tmp->removeFromParentAndCleanup(true);
	//			tmp->release();
	//		}
	//	}
	//	m_vMapList.clear();
	//}
}

LayerNode * ChallengeMapLists::getView(int position)
{
	if ((uint32)position >= m_vMapList.size())
		return 0;
	else
	{
		m_vMapList[position]->setvisibleSize(CCSizeMake(POSX(654), POSX(418/2)));
		m_vMapList[position]->setContentSize(CCSizeMake(POSX(654), POSX(418/2)));
		return m_vMapList[position];
	}
}

void ChallengeMapLists::startListViewHandler()
{
	//¡¡Has connected a task list
	if(!_pListView)
	{
		_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(250), POSX(2), POSX(665), POSX(518)), false);
	}
	if(_pListView)
	{
		_pListView->setIsRelativeAnchorPoint(true);
		_pListView->setAnchorPoint(ccp(0, 0));
		_pListView->setSpacingVertical(POSX(41));

		CCPoint pos1 = this->getPosition();
		CCPoint pos2;
		if(this->getParent())
		{
			pos2 = this->getParent()->getPosition();
		}
		CCPoint pos3 = _pListView->getPosition();

		//_pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + this->getParent()->getPosition().x + _pListView->getPosition().x,
		//	this->getPosition().y + this->getParent()->getPosition().y + _pListView->getPosition().y));

		_pListView->setHeaderSize(POSX(50));
		_pListView->setFooterSize(POSX(50));
		_pListView->setWorldSpaceLeftBottomPoint(ccp(pos1.x + pos2.x + pos3.x, pos1.y + pos2.y + pos3.y));
		_pListView->setOnItemActionListener(this);
		_pListView->m_pri = TLE::WindowLayer_CopyMap + 1;
		if(_pListView->getParent() == NULL)
		{
			this->addChild(_pListView);
		}
		_pListView->release();
	}
}

void ChallengeMapLists::initDataList(MapData node, bool open)
{
	int x = 0;
	int y = 0;
	//bool i = true;
	std::map<int, LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		if(iter->second)
		{
			bool brk = false;
			int size = iter->second->getChildrenCount();
			if(size < 4)
			{
				x = iter->first;
				y = size;
				brk = true;
			}
			else
			{
				x = iter->first + 1;
				y = 0;
			}

			CCArray * pArray = iter->second->getChildren();
			CCObject* pObject = NULL;
			TouchMapNode* child = NULL;
			CCARRAY_FOREACH(pArray, pObject)
			{
				if(pObject == NULL)
					break;
				child = (TouchMapNode*)pObject;
				if(child->_mapData._id == node._id)
				{
					return;
				}
			}

			if(brk)
				break;
		}
	}

	if(y == 0)
	{
		TouchMapNode* newMapNode = new TouchMapNode();
		LayerNode* layerNode = new LayerNode();
		if(newMapNode && layerNode)
		{
			layerNode->addChild(newMapNode, 0, y);
			newMapNode->release();
			newMapNode->_colId = y;
			newMapNode->_mapData = node;
			newMapNode->_copyType = 1;
			newMapNode->setPosition(POSX(44 + (122 + 29) * y), POSX(100));
			newMapNode->setSpriteIcon(true);
			//newMapNode->_nodeList.insert(make_pair(y, node));
			m_vMapList.insert(make_pair(x, layerNode));
		}
	}
	else
	{
		std::map<int, LayerNode*>::iterator iter = m_vMapList.find(x);
		if(iter != m_vMapList.end() && (iter->second))
		{
			LayerNode* n = (LayerNode*)iter->second;
			if(n)
			{
				TouchMapNode* newMapNode = new TouchMapNode();
				newMapNode->_colId = y;
				newMapNode->_copyType = 1;
				newMapNode->_mapData = node;
				newMapNode->setPosition(POSX(44 + (122 + 29) * y), POSX(100));
				newMapNode->setSpriteIcon(true);
				n->addChild(newMapNode, 0, y);
				newMapNode->release();
			}
		}
	}
}

void ChallengeMapLists::setViewAdapter()
{
	if(_pListView)
	{
		_pListView->setAdapter(this);
	}

	std::map<int, LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		iter->second->release();
	}
}

void ChallengeMapLists::deleteIcons()
{
	std::map<int, LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		if(iter->second)
		{
			CCArray * pArray = iter->second->getChildren();
			CCObject* pObject = NULL;
			CCARRAY_FOREACH(pArray, pObject)
			{
				if(pObject == NULL)
					break;
				iter->second->removeChild((CCNode*)pObject, true);
			}
			iter->second->release();
		}
	}
	m_vMapList.clear();
}