#include "HotList.h"
#include "ActItem.h"

HotList* HotList::listViewWithCCRect(const CCRect& mRect, bool isHorizontal)
{
	HotList *pListView = new HotList();
	if(pListView)
	{
		pListView->setIsLockHorizontal(isHorizontal);
		pListView->setRect(mRect);
		pListView->init();
		//pListView->autorelease(); kevin modified
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

int HotList::getCount()
{
	return m_arr.size();
}

LayerNode * HotList::getView( int position )
{
	if (position == 0)
	{
		for ( std::vector<ActItem*>::iterator it = m_arrItem.begin();
			it != m_arrItem.end();
			it++ )
		{
			ActItem* item = *it;
			if (item)
			{
				if (item->getParent())
				{
					item->removeFromParentAndCleanup(true);
				}
				item->release();
			}
		}
		m_arrItem.clear();
	}
	
	int count = 0;
	SCMD38FNode node;
	std::list<SCMD38FNode>::iterator it = m_arr.begin();
	for (it ; it != m_arr.end() ; it++)
	{
		if (count == position)
		{
			node = *it;
			break;
		}
		++count;
	}

	ActItem * pItem = new ActItem();
	pItem->setIsExpand(false);
	if (_curClickIndex == position)
	{
		pItem->setIsExpand(!_isCurClickItemExpand);
	}
	pItem->init(node);
	m_arrItem.push_back(pItem);
	//pItem->release();

	return m_arrItem[position];
}

void HotList::onItemClickListener( LayerNode *itemCell, int position )
{
	_index = 0;
	_curClickIndex = position;
	_isCurClickItemExpand = m_arrItem[position]->getIsExpand();

	setAdapter(this);
}

HotList::~HotList()
{
}
