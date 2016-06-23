#pragma once

#include "BaseType.h"
#include "CCUIPartialScrollView.h"
#include "TowerRankItem.h"
#include "model/tower/vo/TowerRankItemVo.h"
#include "CCUIBackground.h"

class ListContainer:public CCUIPartialScrollView
{
public:
	ListContainer(const CCRect& mRect);
	~ListContainer();

	static ListContainer* ListContainerScrollViewWithCCRect(const CCRect& mRect);

	void updateList(std::list<TowerRankItemVo*>& volist, int page);

public:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	int stateSscroll;
	void handleTouchEndPagePre();
	void handleTouchEndPageNext();
	void handleTouchEndAfter(bool same, int curlayertag);
public:
	CCPoint preTouchPoint;
	TowerRankItem* selectedItem;
	CCUIBackground* m_selectedSpriteImage;
};