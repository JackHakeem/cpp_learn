//************************************************************************
// ListView component, supported vertical & horizontal scroll.
// By Yang Liangjie
//************************************************************************

#ifndef _CC_UI_LISTVIEW_H_
#define _CC_UI_LISTVIEW_H_
#include "CCUIListViewAdapter.h"
#include "CCUIListViewItemActionListener.h"
#include "LayerNode.h"

#define  CCPOINT_DEFAULT  ccp(-9999 , -9999)

USING_NS_CC;

class CCUIListView : public CCLayer
{
public:
	virtual bool init();
	virtual void visit();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

public:
	~CCUIListView();
	CCUIListView()
	{
		contentLayer = 0;
		_worldSpaceLeftBottomPoint = CCPointZero;
		m_pri =-1000;
		setTouchMoveContentLayerPosition(CCPOINT_DEFAULT);
		setIsCanTouchMove(true);
	}

	static CCUIListView* listViewWithCCRect(const CCRect& mRect, bool isHorizontal);
	virtual bool getIsTouchInContentLayer(CCTouch *pTouch);
	void setBackgroundWithFile(const char *pFileName);
	void onTouchEnd(CCTouch *pTouch, CCEvent *pEvent);
	//void setOnItemClickListener(CCUIListViewItemClickListener *listener);
	void setAdapter(CCUIListViewAdapter *adapter);
	//virtual void bindView(CCNode *itemCell, int position, CCPoint ccPosition);
	CCMutableArray<LayerNode *>* getChilds();
	void scrollToEnd(ccTime duration);
	void scrollToTop(ccTime duration);
	// LH
	void scrollToItemByIndex(int index , ccTime duration);

	void resetContentLayerSize(const CCSize& newSize);
	void resetContentLayerPosition(); //LH
	void moveContentLayerToPosition(CCPoint position);

	virtual void onItemTouch(int position);
	virtual void onItemClick(int position);
	virtual void onItemTouchCancel(int position);
	void setWorldSpaceLeftBottomPoint(CCPoint pos);
	CCPoint getWorldSpaceLeftBottomPoint();
	
protected:
	CC_SYNTHESIZE(CCUIListViewItemActionListener*, onItemActionListener, OnItemActionListener);
	// Stretch base on this background layer.
	CC_SYNTHESIZE(CCLayerColor*, contentLayer, ContentLayer);
	// Subviews' parent layer.
	CC_SYNTHESIZE(CCLayerColor*, listItemsLayer, ListItemsLayer);
	CC_SYNTHESIZE(CCRect, clipLayerRect, ClipLayerRect);
	CC_SYNTHESIZE(CCRect, rect, Rect);
	CC_SYNTHESIZE(CCSprite*, backgroundSprite, BackgroundSprite);
	CC_SYNTHESIZE(bool, isLockHorizontal, IsLockHorizontal);
	CC_SYNTHESIZE(bool, isLockVertical, IsLockVertical);
	CC_SYNTHESIZE(bool, isScrolling, IsScrolling);
	CC_SYNTHESIZE(float, paddingLeft, PaddingLeft);
	CC_SYNTHESIZE(float, paddingRight, PaddingRight);
	CC_SYNTHESIZE(float, paddingTop, PaddingTop);
	CC_SYNTHESIZE(float, paddingBottom, PaddingBottom);
	CC_SYNTHESIZE(float, headerSize, HeaderSize);
	CC_SYNTHESIZE(float, footerSize, FooterSize);

	CC_SYNTHESIZE(float, topEdgePosition, TopEdgePosition);
	CC_SYNTHESIZE(float, bottomEdgePosition, BottomEdgePosition);
	CC_SYNTHESIZE(float, leftEdgePosition, LeftEdgePosition);
	CC_SYNTHESIZE(float, rightEdgePosition, RightEdgePosition);
	CC_SYNTHESIZE(float, spacingVertical, SpacingVertical);
	CC_SYNTHESIZE(float, spacingHorizontal, SpacingHorizontal);
	CC_SYNTHESIZE(float, listHeight, ListHeight);
	CC_SYNTHESIZE(float, listWidth, ListWidth);

	CC_SYNTHESIZE(int, touchItemId, TouchItemId);
	CC_SYNTHESIZE(CCPoint, _touchMoveContentLayerPosition, TouchMoveContentLayerPosition); // LH
	CC_SYNTHESIZE(bool, _isCanTouchMove, IsCanTouchMove); // LH

private:
	//CCUIListViewItemClickListener *pItemClickListener;
	CCUIListViewAdapter *_pAdapter;
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
};
#endif