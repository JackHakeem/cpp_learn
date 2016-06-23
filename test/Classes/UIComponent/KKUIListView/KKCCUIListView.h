//************************************************************************
// ListView component, supported vertical & horizontal scroll.
// By Yang Liangjie
//************************************************************************

#ifndef _KKCC_UI_LISTVIEW_H_
#define _KKCC_UI_LISTVIEW_H_
#include "KKCCUIListViewAdapter.h"
#include "KKCCUIListViewItemActionListener.h"
#include "LayerNode.h"

USING_NS_CC;

class KKCCUIListView : public CCLayer
{
public:
	virtual bool init(int item_max);
	virtual void visit();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
public:
	~KKCCUIListView();
	KKCCUIListView()
	{		
		setVisitType(0);
		contentLayer = 0;
		_worldSpaceLeftBottomPoint = CCPointZero;
		m_pri =-1000;
	}

	static KKCCUIListView* listViewWithCCRect(const CCRect& mRect, int ITEM_MAX);
	virtual bool getIsTouchInContentLayer(CCTouch *pTouch);
	void onTouchEnd(CCTouch *pTouch, CCEvent *pEvent);
	//void setOnItemClickListener(KKCCUIListViewItemClickListener *listener);
	
	//virtual void bindView(CCNode *itemCell, int position, CCPoint ccPosition);
	CCMutableArray<LayerNode *>* getChilds();
	void scrollToEnd(ccTime duration);
	void scrollToTop(ccTime duration);

	void resetContentLayerSize(const CCSize& newSize);

	virtual void onItemTouch(int position);
	virtual void onItemClick(int position);
	virtual void onItemTouchCancel(int position);
	void setWorldSpaceLeftBottomPoint(CCPoint pos);
	CCPoint getWorldSpaceLeftBottomPoint();
	
	//void setAdapter(KKCCUIListViewAdapter *adapter);
	bool add(KKCCUIListViewAdapter *adapter);
	void cleanLayer();

protected:
	CC_SYNTHESIZE(KKCCUIListViewItemActionListener*, onItemActionListener, OnItemActionListener);
	// Stretch base on this background layer.
	CC_SYNTHESIZE(CCLayerColor*, contentLayer, ContentLayer);
	// Subviews' parent layer.
	//CC_SYNTHESIZE(CCLayerColor*, listItemsLayer, ListItemsLayer);
	CC_SYNTHESIZE(CCRect, clipLayerRect, ClipLayerRect);
	CC_SYNTHESIZE(CCRect, rect, Rect);
	CC_SYNTHESIZE(CCSprite*, backgroundSprite, BackgroundSprite);


	CC_SYNTHESIZE(bool, isScrolling, IsScrolling);
	

	CC_SYNTHESIZE(int, visitType, VisitType);
	CC_SYNTHESIZE(float, topEdgePosition, TopEdgePosition);
	CC_SYNTHESIZE(float, bottomEdgePosition, BottomEdgePosition);
	CC_SYNTHESIZE(float, leftEdgePosition, LeftEdgePosition);
	CC_SYNTHESIZE(float, rightEdgePosition, RightEdgePosition);
	CC_SYNTHESIZE(float, spacingVertical, SpacingVertical);
	CC_SYNTHESIZE(float, listHeight, ListHeight);
	CC_SYNTHESIZE(float, listWidth, ListWidth);

	CC_SYNTHESIZE(int, touchItemId, TouchItemId);
private:
	//KKCCUIListViewItemClickListener *pItemClickListener;
	KKCCUIListViewAdapter *_pAdapter;
	//float _topEdgePosition, _bottomEdgePosition, _leftEdgePosition, _rightEdgePosition;
	CCPoint _clickPosition;
	bool _isClick;
	//float _listHeight, _listWidth;
	/*std::vector<float> _listItemsHeight;
	std::vector<float> _listItemsWidth;*/
	CCPoint _preTouchPoint;
	CCPoint _currentTouchPoint;

	void resetEdgePosition();
	int getItemIdWithPosition(CCPoint& position);
	void setContentLayerPosition(CCPoint destPosition, ccTime duration);
	CCMutableArray<LayerNode *>* _childViewList;
	CCPoint _worldSpaceLeftBottomPoint;
public:
	int m_pri;//KEVIN
	int ITEM_MAX;
};
#endif