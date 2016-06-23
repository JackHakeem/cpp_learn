#include "StoryMapLists.h"
#include "TouchMapNode.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"

StoryMapLists::StoryMapLists()
{
	_pListView = NULL;
	_mapCnt = 0;
}

StoryMapLists::~StoryMapLists()
{
	if (!m_vMapList.empty())
	{
		std::map<int, LayerNode*>::iterator listItemIt;
		for(listItemIt = m_vMapList.begin();
			listItemIt != m_vMapList.end();
			++listItemIt)
		{
			LayerNode *tmp = listItemIt->second;
			if(tmp && tmp->getParent())
			{
				tmp->removeFromParentAndCleanup(true);
				tmp->release();
			}
		}
		m_vMapList.clear();
	}

	//CC_SAFE_DELETE(_pListView);
}

int StoryMapLists::getCount()
{
	return m_vMapList.size();
}

LayerNode * StoryMapLists::getView(int position)
{
	int size = m_vMapList.size();
	if ((uint32)position >= size)
	{
		return 0;
	}
	else
	{
		//POSX edwardliu
		if (!m_vMapList[position])
		{
			return 0;
		}
		m_vMapList[position]->setvisibleSize(CCSizeMake(POSX(654), POSX(418/2)));
		m_vMapList[position]->setContentSize(CCSizeMake(POSX(654), POSX(418/2)));

		return m_vMapList[position];
	}
}

//void StoryMapLists::onItemClickListener(LayerNode *itemCell, int position)
//{
//
//	CCLog("click story map...position=%d", position);
//
//	if (!itemCell)
//		return;
//}

void StoryMapLists::startListViewHandler()
{
	//¡¡Has connected a task list
	//POSX edwardliu
	if(!_pListView)
	{
		_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(2), POSX(2), POSX(665), POSX(518)), false);
	}
	if(_pListView)
	{
		_pListView->setIsRelativeAnchorPoint(true);
		_pListView->setAnchorPoint(ccp(0, 0));
		_pListView->setSpacingVertical(POSX(41));
		_pListView->setWorldSpaceLeftBottomPoint(ccp(_pListView->getPosition().x + this->getPosition().x + this->getParent()->getPosition().x,
			_pListView->getPosition().y + this->getPosition().y + this->getParent()->getPosition().y));
		_pListView->setOnItemActionListener(this);
		_pListView->m_pri = TLE::WindowLayer_CopyMap;
		_pListView->setHeaderSize(POSX(50));
		_pListView->setFooterSize(POSX(50));
		if(_pListView->getParent() == NULL)
		{
			this->addChild(_pListView);
			_pListView->release();
		}
	}
}

void StoryMapLists::initDataList(MapData node, bool open)
{
	/*
	int x = 0;
	int y = 0;
	std::map<int, LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		if(!(iter->second))
		{
			m_vMapList.erase(iter);
			continue;
		}

		TouchMapNode* node = (TouchMapNode*)iter->second;
		if(node)
		{
			if(node->_nodeList.size() < 4)
			{
				x = iter->first;
				y = node->_nodeList.size();
			}
			else
			{
				x = iter->first + 1;
				y = 0;
			}

			if(y > 0)
			{
				std::map<int, MapData>::iterator it = node->_nodeList.find(y);
				if(it != node->_nodeList.end())
					return;
			}
		}
	}

	if(y == 0)
	{
		TouchMapNode* newMapNode = new TouchMapNode();
		newMapNode->_nodeList.insert(make_pair(y, node));
		m_vMapList.insert(make_pair(x, newMapNode));
	}
	else
	{
		std::map<int, LayerNode*>::iterator iter = m_vMapList.find(x);
		if(iter != m_vMapList.end() && (iter->second))
		{
			TouchMapNode* n = (TouchMapNode*)iter->second;
			if(n)
			{
				n->_nodeList.insert(make_pair(y, node));
			}
		}
	}
	*/

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
					return;
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
			newMapNode->release();//kevinz
			newMapNode->_colId = y;
			newMapNode->_mapData = node;
			newMapNode->setPosition(ccp(POSX(44 + (122 + 29) * y), POSX(/*-61*/100)));
			newMapNode->setSpriteIcon(true);
			//newMapNode->_nodeList.insert(make_pair(y, node));
			m_vMapList.insert(make_pair(x, layerNode));

		}
		//CC_SAFE_DELETE(newMapNode);
		//CC_SAFE_DELETE(layerNode);
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
				newMapNode->_mapData = node;
				newMapNode->setPosition(ccp(POSX(44 + (122 + 29) * y), POSX(/*-61*/100)));
				newMapNode->setSpriteIcon(true);
				n->addChild(newMapNode, 0, y);
				newMapNode->release();//kevinz
				//CC_SAFE_DELETE(newMapNode);
			}
		}
	}
}

void StoryMapLists::setViewAdapter()
{
	if(_pListView)
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

		_pListView->scrollToItemByIndex(getNowMapIndex()/4 , 0.2f);
	}
}

void StoryMapLists::deleteIcons()
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

void StoryMapLists::setLastMapTip( int tipId )
{
	std::map<int, LayerNode*>::iterator iter = m_vMapList.begin();
	for(; iter != m_vMapList.end(); ++iter)
	{
		if(iter->second)
		{
			CCArray * pArray = iter->second->getChildren();
			CCObject* pObject = NULL;
			int i=0;
			CCARRAY_FOREACH(pArray, pObject)
			{
				if(pObject == NULL)
					break;
				
				TouchMapNode* pNode = (TouchMapNode *) pObject;

				if(pNode == NULL)
					break;

				if(pNode->_mapData._id == tipId)
				{
					pNode->_isNoTongGuan = true;
					pNode->setNoTongGuan();

					CCSprite *pTipSprite = NULL;
					if(i % 3 == 0 && i != 0)
					{
						// add right tip.
						pTipSprite = CCSprite::spriteWithSpriteFrameName("entrance/currentTaskMapRight.png");

						if(pTipSprite)
						{
							pTipSprite->setAnchorPoint(ccp(0.5, -1));
							pTipSprite->setPosition(pNode->getPosition());
							iter->second->addChild(pTipSprite, 9999);
						}	
					}
					else
					{
						// add left tip.
						pTipSprite = CCSprite::spriteWithSpriteFrameName("entrance/currentTaskMapLeft.png");

						if(pTipSprite)
						{
							pTipSprite->setAnchorPoint(ccp(-0.5, -1));
							pTipSprite->setPosition(pNode->getPosition());
							iter->second->addChild(pTipSprite, 9999);
						}
					}

					/*
					if (_pListView)
					{
						_pListView->scrollToItemByIndex(i/3,0);
					}
					*/
					break;
				}

				++i;
			}
		}
	}
}

int StoryMapLists::getNowMapIndex()
{
	if (getNowMapId() == 0)
	{
		return 0;
	}

	int index = 0;
	std::map<int /*index*/, LayerNode*>::iterator iter = m_vMapList.begin();
	for (iter ; iter != m_vMapList.end() ; iter++)
	{
		if (!iter->second)
		{
			continue;
		}
		CCArray * pArray = iter->second->getChildren();
		CCObject * pObj = 0;
		CCARRAY_FOREACH(pArray , pObj)
		{
			if(pObj == NULL)
				break;

			TouchMapNode* pNode = (TouchMapNode *) pObj;

			if(pNode == NULL)
				break;

			if(pNode->_mapData._id == getNowMapId())
			{
				return index;
			}
			++index;
		}
	}
	return index;
}
