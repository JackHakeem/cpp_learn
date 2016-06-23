//
//  CCUIPartialScrollView.h
//  cocos2dUI
//
//  Created by rorger on 12-3-7. contact me:jhcyd112@163.com
//  Copyright 2012Äê __MyCompanyName__. All rights reserved.
//

#ifndef cocos2dUI_CCUIPartialScrollView_h
#define cocos2dUI_CCUIPartialScrollView_h
#include "cocos2d.h"
USING_NS_CC;

#define CCUIPARTIALSCROLLVIEW_LAYER_Z (1)

class CCUIPartialScrollView:public CCLayer{
public:
    virtual ~CCUIPartialScrollView();
    CCUIPartialScrollView(const CCRect& mRect);
    static CCUIPartialScrollView* scrollViewWithCCRect(const CCRect& mRect);
	virtual bool init();
    
    //addTargetedDelegate
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //clip contentLayer
    virtual void visit();
    
    //add child to contentLayer
    virtual void addChildInContentLayer(CCNode * child){contentLayer->addChild(child); }
    virtual void addChildInContentLayer(CCNode * child, int zOrder){contentLayer->addChild(child, zOrder); }
    virtual void addChildInContentLayer(CCNode * child, int zOrder, int tag){contentLayer->addChild(child, zOrder, tag);}
	CCLayer* getObjByIndex(int pageIndex);
	//void getIdlePage();
	//void addPage(CCLayer* newpage);
	CCLayer* addLayerByTag(int tag);
	CCLayer* getLayerByTag(int tag);
	void removeAllLayer();
	
    //set method
 
	void setContentLayerSize(const CCSize& mSize){contentLayer->setContentSize(mSize);}

    //get method
    virtual bool getIsTouchInContentLayer(CCTouch *pTouch);

    const CCSize& getContentLayerSize(){return contentLayer->getContentSize();}

    CCLayerColor*  getScrollLayerCellAtIndex(int i);

	void moveToPage(int page);
	virtual void moveToNextPage();
	virtual void moveToPreviousPage();
	virtual void moveToPageImmediately(int page);
	virtual void onExit();

	virtual void handleTouchEndPagePre();
	virtual void handleTouchEndPageNext();
	virtual void handleTouchEnd2Page();

	void clean();
public:
    CC_SYNTHESIZE(CCLayerColor*, contentLayer, ContentLayer)//Color
  //  CC_SYNTHESIZE(bool, isLockHorizontal, IsLockHorizontal)
  //  CC_SYNTHESIZE(bool, isLockVertical, IsLockVertical)
  CC_SYNTHESIZE(bool, isScrolling, IsScrolling)
  CC_SYNTHESIZE(bool, isTouchingMoving, IsTouchingMoving)
  CC_SYNTHESIZE(CCSize, visitSize, VisitSize);
	// Holds the current height and width of the screen
	float scrollHeight;
	float scrollWidth;
	
	// Holds the current page being displayed
	int currentScreen;
	
	// A count of the total screens available
	int totalScreens;
	
	// The initial point the user starts their swipe
	float startSwipe;	

	int m_pri;
protected:
    //CCPoint based on world coordinates
    CCPoint preTouchPoint;
    CCPoint currentTouchPoint;

	//CCMutableArray<CCLayer*>* m_layers;
};


#endif//cocos2dUI_CCUIPartialScrollView_h
