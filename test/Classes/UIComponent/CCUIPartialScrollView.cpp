#include "CCUIPartialScrollView.h"
#include "utils/ScaleUtil.h"
USING_NS_CC;
#define contentViewFontColorRed  (GLubyte)(255 * 0.8) 
#define contentViewFontColorGreen  (GLubyte)(255 * 0.9) 
#define contentViewFontColorBlue  (GLubyte)(255 * 0.2) 
#define contentViewFontColorAlpha 1.0
#define kScrollLayerCellPositionY 25
#define myFontColor ccc3(contentViewFontColorRed, contentViewFontColorGreen, contentViewFontColorBlue)

/*
CCLayerColor*  CCUIPartialScrollView::getScrollLayerCellAtIndex(int i)
{
    CCLayerColor *scrollLayerCell = CCLayerColor::layerWithColorWidthHeight(ccc4(0, (i%2==0)?100:0, 0, i%2), 40, 400);(i%2==0)?0:100
    scrollLayerCell->setIsTouchEnabled(false);
    scrollLayerCell->setPosition(ccp(i*scrollWidth,0));

    return scrollLayerCell;
}
*/
CCUIPartialScrollView::CCUIPartialScrollView(const CCRect& mRect)
{
	m_pri = -1000;
    this->setPosition(mRect.origin);
    this->setContentSize(mRect.size);
    this->setIsTouchEnabled(true);//That can be touch
//    this->setIsLockHorizontal(true);
    this->setIsScrolling(false);
	this->setIsTouchingMoving(false);
	//contentLayer = new CCLayer();
	contentLayer = new CCLayerColor();
	contentLayer->initWithColorWidthHeight(ccc4( 120,255,120,0), mRect.size.width,mRect.size.height);// CCLayerColor::layerWithColorWidthHeight(ccc4( 120,255,120,100), mRect.size.width,mRect.size.height);
//	contentLayer->setContentSize(mRect.size);

    contentLayer->setIsRelativeAnchorPoint(true);
    contentLayer->setAnchorPoint(ccp(0,0));

	currentScreen = 0;
	scrollWidth  = mRect.size.width;
	scrollHeight = mRect.size.height;
	totalScreens = 0;

	this->setVisitSize(CCSizeMake(this->getContentSize().width * CCDirector::sharedDirector()->getContentScaleFactor(),
		this->getContentSize().height * CCDirector::sharedDirector()->getContentScaleFactor()));

    this->addChild(contentLayer);
	contentLayer->release();
}

void CCUIPartialScrollView::removeAllLayer()
{
	contentLayer->removeAllChildrenWithCleanup(true);
}

CCLayer* CCUIPartialScrollView::addLayerByTag(int tag)
{
	if (!contentLayer) 
		return 0;
	CCLayer* newlayer = CCLayerColor::layerWithColorWidthHeight(ccc4((totalScreens%2==0)?100:0,100,totalScreens%2,0), 
																scrollWidth, 
																scrollHeight);// new CCLayer();//?Y���(�D��?
	if (!newlayer)
		return 0;

	contentLayer->addChild(newlayer, CCUIPARTIALSCROLLVIEW_LAYER_Z, tag);
	
	//newlayer->release(); //LH20130111LEAK

	newlayer->setPosition(ccp(totalScreens*scrollWidth, 0));
	totalScreens++;
	if (currentScreen == 0)
		currentScreen = 1;


	
	return newlayer;
}

CCLayer* CCUIPartialScrollView::getLayerByTag(int tag)
{
    if(!contentLayer)
        return NULL;
	CCLayer* rnt = (CCLayer*)contentLayer->getChildByTag(tag);
	return rnt;
}

CCUIPartialScrollView* CCUIPartialScrollView::scrollViewWithCCRect(const CCRect& mRect)
{
    CCUIPartialScrollView *pScrollView = new CCUIPartialScrollView(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}


CCUIPartialScrollView::~CCUIPartialScrollView()
{
	removeAllLayer();  // LH20130115
	//if (m_pLayers)
	//	m_pLayers->release();
}

bool CCUIPartialScrollView::init(){
    return true;
}

void CCUIPartialScrollView::registerWithTouchDispatcher(){

    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_pri, true);
}

bool CCUIPartialScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{    
	if (currentScreen == 0 || totalScreens == 0)
		return false;//

    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	this->setIsTouchingMoving(false);
    if (this->getIsTouchInContentLayer(pTouch)) {
        isScrolling = true;
		startSwipe = preTouchPoint.x;
        printf("Began Scrolling\n");
    }
    else 
	{
        isScrolling = false;
		startSwipe = 0;
	}
    return isScrolling;
}

void CCUIPartialScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //Doyang 20120924
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    if(abs(movePoint.x - preTouchPoint.x) < 5)
    {
        return;
    }


	this->setIsTouchingMoving(true);

//    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	CCPoint deltaPoint = ccpSub(currentTouchPoint, preTouchPoint);
	//if (deltaPoint.x <= 2)
	//	return;//moving much slow

	deltaPoint.y=0; 
    contentLayer->setPosition(ccpAdd(contentLayer->getPosition(), deltaPoint));
    preTouchPoint = currentTouchPoint;

	contentLayer->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(currentTouchPoint.x-startSwipe),0));

}


void CCUIPartialScrollView::handleTouchEndPagePre()
{
	CCLog("void CCUIPartialScrollView::handleTouchEnd()  default");
}

void CCUIPartialScrollView::handleTouchEndPageNext()
{
	CCLog("void CCUIPartialScrollView::handleTouchEnd()  default");
}

void CCUIPartialScrollView::handleTouchEnd2Page()
{
	CCLog("void CCUIPartialScrollView::handleTouchEnd()  default");
}

void CCUIPartialScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	int newX = (int)touchPoint.x;
		
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
		handleTouchEndPageNext();
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
		handleTouchEndPagePre();
	}
	else
	{
		this->moveToPage(currentScreen);
		handleTouchEnd2Page();
	}	

	this->setIsTouchingMoving(false);
}

void CCUIPartialScrollView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

bool CCUIPartialScrollView::getIsTouchInContentLayer( CCTouch *pTouch){
    CCPoint nodeSpaceLocation = this->convertTouchToNodeSpace(pTouch);

    CCRect contentLayerRect = CCRectZero;
    contentLayerRect.origin = CCPointZero;
    contentLayerRect.size = contentLayer->getContentSize();

    return CCRect::CCRectContainsPoint(contentLayerRect, nodeSpaceLocation);
}

void CCUIPartialScrollView::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
    CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
    glEnable(GL_SCISSOR_TEST);
    glScissor(convertedLocationLowerLeft.x * scale, convertedLocationLowerLeft.y * scale,
              this->getVisitSize().width * scale, this->getVisitSize().height * scale);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
    glEnable(GL_SCISSOR_TEST);
    glScissor(convertedLocationLowerLeft.x * scale, convertedLocationLowerLeft.y * scale,
              this->getVisitSize().width, this->getVisitSize().height);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
#endif
}

void CCUIPartialScrollView::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void CCUIPartialScrollView::moveToPage(int page)
{	
	CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.3f, ccp(-((page-1)*scrollWidth),0)));
	contentLayer->runAction(changePage);
	currentScreen = page;	
}

void CCUIPartialScrollView::moveToPageImmediately(int page)
{	
	if (page < 1)
		page = 1;
	
	contentLayer->setPosition(ccp(-((page-1)*scrollWidth),0));
	currentScreen = page;	
}

void CCUIPartialScrollView::moveToNextPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.3f, ccp(-(((currentScreen+1)-1)*scrollWidth),0)));
	
	contentLayer->runAction(changePage);
	currentScreen = currentScreen+1;	
}

void CCUIPartialScrollView::moveToPreviousPage()
{	
	CCEaseBounce* changePage =CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.3f, ccp(-(((currentScreen-1)-1)*scrollWidth),0)));
	contentLayer->runAction(changePage);
	currentScreen = currentScreen-1;	
}

CCLayer* CCUIPartialScrollView::getObjByIndex(int pageIndex)
{
	CCArray* varray = contentLayer->getChildren();
	CCLayer* rnt = (CCLayer*)varray->objectAtIndex(pageIndex);


	return rnt;
}

