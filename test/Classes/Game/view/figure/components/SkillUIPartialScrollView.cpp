#include "SkillUIPartialScrollView.h"
#include "SkillView.h"
#include "manager/ViewManager.h"
#include "control/figure/FigureCommand.h"
#include "model/skill/vo/SkillType.h"
#include "SkillItem.h"
#include "utils/TipHelps.h"
#include "manager/TouchLayerEnum.h"

SkillUIPartialScrollView * g_pSkillScrollView = 0;

SkillUIPartialScrollView::SkillUIPartialScrollView(const CCRect & ccRect):CCUIPartialScrollView(ccRect)
{
	_nState = 0;
	
}

SkillUIPartialScrollView::~SkillUIPartialScrollView()
{

}

SkillUIPartialScrollView * SkillUIPartialScrollView::skillScrollViewWithCCRect(const CCRect & ccRect)
{
	SkillUIPartialScrollView *pScrollView = new SkillUIPartialScrollView(ccRect);
	if(pScrollView && pScrollView->init())
	{
		//pScrollView->setIsTouchEnabled(false);
		
		pScrollView->autorelease();
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}

CCNode* SkillUIPartialScrollView::getTouchPosIndex( CCPoint point, int* posIndex )
{
	CCSprite * s = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
	CCSize sz = s->getTexture()->getContentSize();
	CCRect rect;
	for (int i = 0;i<SKILL_ROW*SKILL_COL;i++)
	{
		int page = this->currentScreen-1;
		CCNode * s = this->getLayerByTag(page);
		s = s->getChildByTag(page*9 + i);
		if (!s)
		{
			break;
		}
		CCPoint c = getScreenPos(s);
		CCLog("Skill2:pos change to screen :(%f,%f)",c.x,c.y);
		rect = CCRect(c.x/*-sz.width/2*/,c.y/*-sz.height/2*/,sz.width,sz.height);
		if (CCRect::CCRectContainsPoint(rect,point))
		{
			CCLog("Skill2:touch in the cell : %d",i);
			*posIndex =  page*9 + i;
			return s;
		}
	}
	return 0;
}

bool SkillUIPartialScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{    
	_nState = 0;
	if (currentScreen == 0 || totalScreens == 0)
		return false;//

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	_curTouchPos = this->getIsTouchInContentLayer(pTouch);
	if (this->getIsTouchInContentLayer(pTouch)) 
	{
		_nState = 1;
		isScrolling = true;
		startSwipe = preTouchPoint.x;
		printf("Began Scrolling\n");
	}
	else
	{
// 		SkillView * sv = ViewManager::getInstance()->_skillView;
// 		if (sv)
// 		{
// 			sv->showSkillSelectPanel(0);
// 		}
		if ((ViewManager::getInstance()->figureView)&&(ViewManager::getInstance()->figureView->_figureV))
		{
			ViewManager::getInstance()->figureView->_figureV->showSkillSelectPanel(0);
		}
		
		isScrolling = false;
		startSwipe = 0;
	}
	return isScrolling;
}

void SkillUIPartialScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

    if (abs(touchPoint.x - preTouchPoint.x) < 5)
    {
        return;
    }

    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	CCPoint deltaPoint = ccpSub(currentTouchPoint, preTouchPoint);
	deltaPoint.y=0; 
	contentLayer->setPosition(ccpAdd(contentLayer->getPosition(), deltaPoint));
	preTouchPoint = currentTouchPoint;

	contentLayer->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(currentTouchPoint.x-startSwipe),0));
	_nState = 2;

	// hide hightlight
	LayerNode * pSkillLayer = (LayerNode *)this->getParent();
	if (pSkillLayer)
	{
		SpriteNode * pHighLight = (SpriteNode *)pSkillLayer->getChildByTag(SkillLayer::TAG_HIGH_LIGHT);
		if (pHighLight)
		{
			pHighLight->setIsVisible(false);
		}
	}
}

void SkillUIPartialScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	if (_nState == 1)
	{
		//if (_curTouchPos == this->getIsTouchInContentLayer(pTouch))
		if (this->getIsTouchInContentLayer(pTouch))
		{
			cocos2d::CCLog("Skill2::touch is in ScrollLayer (%f,%f)",touchPoint.x,touchPoint.y);
			int nPosIndex = -1;
			SkillItem* pSkillItem = 0;
			pSkillItem = (SkillItem*)getTouchPosIndex(touchPoint, &nPosIndex);
			if (pSkillItem)
				pSkillItem->_posIndex = nPosIndex;

			//int len = ViewManager::getInstance()->_skillView->_nLen;
			if ((!ViewManager::getInstance()->figureView)||(!ViewManager::getInstance()->figureView->_figureV)||(!g_pFigureScrollView))
			{
				return;
			}
			if ((nPosIndex >= 0)&&(nPosIndex < sizeof(ViewManager::getInstance()->figureView->_figureV->SkillID)))
			{
				//
				FigureCommand * fc = (FigureCommand *)g_pFacade->retrieveController(AppFacade_FIGURE_COMMAND);
				if (fc)
				{
					//int merID = 0,skillID = 0,account = 0;
					
					if (pSkillItem)
					{
						if (pSkillItem->myTip)
						{
							pSkillItem->myTip->rollOverHander();
						}
					}

					LayerNode * pSkillLayer = (LayerNode *)this->getParent();
					if (pSkillLayer)
					{
						SpriteNode * pHighLight = (SpriteNode *)pSkillLayer->getChildByTag(SkillLayer::TAG_HIGH_LIGHT);
						if (pHighLight)
						{
							pHighLight->setIsVisible(true);
							CCPoint pos = pSkillItem->getPosition();
							pHighLight->setPosition(ccp(pos.x+POSX(12) , pos.y-POSX(6)));
						}
					}
					
					//KEVIN
					//merID = ViewManager::getInstance()->figureView->_figureV->RoleID[g_pFigureScrollView->currentScreen-1];
					//skillID = ViewManager::getInstance()->figureView->_figureV->SkillID[nPosIndex];

					//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
					//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
					//for (iter;iter != list->end();iter++)
					//{
					//	if (merID == iter->second.figureBaseInfo.mercId)
					//	{
					//		account = iter->first;
					//		break;
					//	}
					//}
					//if (iter->second.playerBaseInfo.skill3 != skillID)
					//{
					//	fc->sendChangeSkillRequest(account,SkillType::PASSVIE,skillID);
					//}
				}
				//ViewManager::getInstance()->figureView->_figureV->showSkillSelectPanel(0);
			}
		}
	}
	else if (_nState == 2)
	{
		SkillLayer * pSkillLayer = (SkillLayer *)this->getParent();
		if (pSkillLayer)
		{
			this->CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
			pSkillLayer->updateDirections();
		}
	}
}
