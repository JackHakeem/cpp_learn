#include "NameUIPartialScrollView.h"
#include "FigureView.h"
#include "model/player/RoleManage.h"
#include "manager/ViewManager.h"

NameUIPartialScrollView * g_pNameScrollView = 0;

NameUIPartialScrollView::NameUIPartialScrollView(const CCRect & ccRect):CCUIPartialScrollView(ccRect)
{
	_nState = 0;
	_merchNum = RoleManage::Instance()->_mercList.size();
	rect = ccRect;
}

NameUIPartialScrollView::~NameUIPartialScrollView()
{

}

NameUIPartialScrollView * NameUIPartialScrollView::nameScrollViewWithCCRect(const CCRect & ccRect)
{
	NameUIPartialScrollView *pScrollView = new NameUIPartialScrollView(ccRect);
	if(pScrollView && pScrollView->init())
	{
		//pScrollView->setIsTouchEnabled(false);
		pScrollView->autorelease();
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}

bool NameUIPartialScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{    
	_nState = 0;
	if (currentScreen == 0 || totalScreens == 0)
		return false;//

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	_preTouchPos = preTouchPoint;
	_curTouchPos = preTouchPoint;
	this->setIsTouchingMoving(false);
	if (this->getIsTouchInContentLayer(pTouch)) 
	{
		_nState = 1;
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

void NameUIPartialScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setIsTouchingMoving(true);
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	_curTouchPos = currentTouchPoint;
	CCPoint deltaPoint = ccpSub(currentTouchPoint, preTouchPoint);
	deltaPoint.y=0; 
	contentLayer->setPosition(ccpAdd(contentLayer->getPosition(), deltaPoint));
	preTouchPoint = currentTouchPoint;

	//contentLayer->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(currentTouchPoint.x-startSwipe),0));
	_nState = 2;
}

void NameUIPartialScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	_curTouchPos = touchPoint; 
	if (_nState == 1)
	{
		//if (_curTouchPos == this->getIsTouchInContentLayer(pTouch))
		if (this->getIsTouchInContentLayer(pTouch))
		{
			cocos2d::CCLog("Role::touch is in ScrollLayer (%f,%f)",touchPoint.x,touchPoint.y);
			for (int i=0;i<this->_merchNum;i++)
			{
				CCNode * cn = g_pNameScrollView->getLayerByTag(0)->getChildByTag(i);
				if (!cn)
				{
					return;
				}
				CCPoint p = getScreenPos(cn);
				if (CCRect::CCRectContainsPoint(CCRectMake(p.x,p.y,120,30),touchPoint))
				{
					//this->moveToCenter(ccp(250-touchPoint.x+1024-,0));
					if (!g_pFigureScrollView)
					{
						return;
					}
					int curScrIndex = g_pFigureScrollView->currentScreen-1;
					if (curScrIndex<i)
					{
						while (i!=curScrIndex)
						{
							g_pFigureScrollView->moveToNextPage();
							SkillView * sv = ViewManager::getInstance()->_skillView;
							if (sv)
							{
								sv->addSkillCellAndItem();
							}
							PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
							if (pv)
							{
								pv->loadItems(false);
							}
							--i;
						}
					}
					else
					{
						while (i!=curScrIndex)
						{
							g_pFigureScrollView->moveToPreviousPage();
							SkillView * sv = ViewManager::getInstance()->_skillView;
							if (sv)
							{
								sv->addSkillCellAndItem();
							}
							PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
							if (pv)
							{
								pv->loadItems(false);
							}
							++i;
						}
					}
					break;
				}
			}			
		}
	}
	else	if (_nState == 2)
	{
		CCLayer * contentlayer = g_pNameScrollView->getContentLayer();
		CCLayer * layer = g_pNameScrollView->getLayerByTag(0);
		CCPoint rectPos = getScreenPos((CCNode *)contentlayer);
		CCPoint lPoint = contentlayer->getPosition();
		CCSize sz = layer->getContentSize();
		float deltaX = rect.size.width-sz.width;

		if ( lPoint.x > 0 )
		{
			this->moveToBoundary(ccp(-lPoint.x,0));
		}
		else if (( lPoint.x< deltaX))
		{
			this->moveToBoundary(ccp(deltaX-lPoint.x,0));
		}
		else
		{
			//int pre = (touchPoint.x > _preTouchPos.x) ? 1 :(-1);
			//this->moveToPos(ccp(pre * SCALEW(150),0));
		}
	}

	this->setIsTouchingMoving(false);
}

CCLayer* NameUIPartialScrollView::addLayerByTag(int tag)
{
	if (!contentLayer) 
		return 0;
	CCLayer* newlayer = CCLayerColor::layerWithColorWidthHeight(ccc4(0,(totalScreens%2==0)?100:0,100,totalScreens%2), 
		SCALEW(120)*_merchNum,
		scrollHeight);// new CCLayer();//?Y¨º¡À¨®D¨¦?
	if (!newlayer)
		return 0;

	contentLayer->addChild(newlayer, CCUIPARTIALSCROLLVIEW_LAYER_Z, tag);

	newlayer->setPosition(ccp(0, 0));
	totalScreens++;
	if (currentScreen == 0)
		currentScreen = 1;



	return newlayer;
}

void NameUIPartialScrollView::moveToCenter(CCPoint pos)
{
	CCAction* m_action = CCSequence::actions(	CCMoveBy::actionWithDuration(0.2, pos),NULL);
	contentLayer->runAction(m_action);
}

void NameUIPartialScrollView::moveToBoundary(CCPoint pos)
{
	CCAction* m_action = CCSequence::actions(	CCMoveBy::actionWithDuration(0.2, pos),NULL);
	contentLayer->runAction(m_action);
}

void NameUIPartialScrollView::moveToPos(CCPoint pos)
{
	CCAction* m_action = 0;
	float duration = 0.2;
	m_action = CCSequence::actions(	CCMoveBy::actionWithDuration(duration,ccp(pos.x,pos.y)),m_action,NULL); 
	contentLayer->runAction(m_action);
	pos.x = pos.x/2;
}
