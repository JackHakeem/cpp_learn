#include "FigureMainView.h"
#include "manager/LayerManager.h"
#include "manager/PopEventName.h"
#include "manager/ViewManager.h"
#include "manager/GlobalManage.h"
#include "manager/ViewManager.h"
#include "view/backpack/components/BagView.h"
#include "manager/LayerManager.h"
#include "PopUIBg.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/PopManage.h"
#include "manager/LayerManager.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/ButtonIDConst.h"
#include "SkillUIPartialScrollView.h"

FigureMainView::FigureMainView()
{
	_currentId = 0;
	_figureV = NULL;
	_currentView = NULL;
	_viewType = 0;
	init();
}

FigureMainView::~FigureMainView() 
{
	if (g_pFigureScrollView)
	{
		g_pFigureScrollView->removeAllLayer();
		g_pFigureScrollView->removeFromParentAndCleanup(true);
		//g_pFigureScrollView->release();
		g_pFigureScrollView = 0;
	}


	//if(_figureV)
	//	delete _figureV;
	if(ViewManager::getInstance()->bagView
		&& ViewManager::getInstance()->bagView->getisPop())
	{
		
	}
	else
	{
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist"); 
		//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_skill_icon.pvr.ccz");

	ViewManager::getInstance()->figureView = 0;

	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}


bool FigureMainView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->key = PopEventName::FIGURE;
	this->setIsTouchEnabled(true);
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(CCPointZero);
	this->setPosition(CCPointZero);

	// Modify by Doyang.
	// init with 444 * 2 for popmanage's role.
	// change it 444 when AttributeLayer remove.
	m_viewSize = CCSizeMake(POSX(444 * 2), /*POSX(628)*/CCDirector::sharedDirector()->getWinSize().height);
	setPopContentSize(m_viewSize);
	setContentSize(m_viewSize);

	//changeStage(0);
	//this->setPosition(ccp(POSX(winSize.width / 2.0f-m_viewSize.width/2), POSX(winSize.height / 2.0f-m_viewSize.height/2)));

	// should be set in child page

	// 加入角色层 以便以后加入tab时使用
	_figureV = new FigureView(m_viewSize);
	this->addChild(_figureV,RENDERZ_figureview,TAG_FIGUREVIEW);
	_figureV->release();

    //return true;
	_figureV->currentId(_currentId);
	_figureV->_statPanel = FigureView::STAT_ROLE;

	// 添加滚动底层 和滑动页 显示角色装备信息
	_figureV->showEquipInfo();
	_currentView = _figureV; // 当前的角色信息页
	_figureV->setContentSize(m_viewSize);
	_figureV->setIsRelativeAnchorPoint(true);
	_figureV->setAnchorPoint(CCPointZero);
	_figureV->setPosition(POS(ccp(0,12), ScaleUtil::TOP_LEFT));
	return true;
}

void FigureMainView::registerWithTouchDispatcher()
{

	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Figure, true);
}

bool FigureMainView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//
	//setTouchState(TouchState_0);
	//
	//CCPoint locationInView = touch->locationInView(touch->view());
	//preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//
	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//当前需要windowLayer焦点
	{
		return false;
	}

	return _currentView->ccTouchBegan(touch, event);

}

void FigureMainView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	_currentView->ccTouchMoved(touch, event);
	//
	//CCPoint locationInView = touch->locationInView(touch->view());
	//currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	////
	//int diaotaX = abs(currentTouchPoint.x - preTouchPoint.x);




	//	else if (getTouchState() == TouchState_5)
	//	{
	//		CCPoint dstp = currentTouchPoint;
	//		dstp = ccp(currentTouchPoint.x, currentTouchPoint.y);

	//		if (m_pCurSelectedBagGoods)
	//		{
	//			CCPoint p = currentTouchPoint;
	//			//CCPoint __containerPosition = __container->getPosition();
	//			//p = ccp(p.x-__containerPosition.x, p.y-__containerPosition.y);
	//			m_pCurSelectedBagGoods->onMouseMoveHnadler(ccp(currentTouchPoint.x - preTouchPoint.x, currentTouchPoint.y - preTouchPoint.y));
	//		}
	//	}
	//}

	//
}

void FigureMainView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	_currentView->ccTouchEnded(touch, event);
	//CCPoint locationInView = touch->locationInView(touch->view());
	//currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	//if (_pBagCreate)// && _pBagCreate->getIsScrolling()
	//{
	//	if (getTouchState() == TouchState_3)
	//	{
	//		_pBagCreate->ccTouchEnded(touch, event);
	//	}
	//	else if (getTouchState() == TouchState_5)
	//	{
	//		if (m_pCurSelectedBagGoods)
	//			m_pCurSelectedBagGoods->onMouseUpHnadler(currentTouchPoint);
	//	}
	//}
} 

void FigureMainView::closeView()
{
	//this->removeAllChildrenWithCleanup(true);

	_figureV->_statPanel = FigureView::STAT_ROLE;

	this->setisPop(false);

	SkillView * sv = ViewManager::getInstance()->_skillView;
	if (sv)
	{
		sv->setisPop(false);
	}
	PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
	if (pv)
	{
		pv->setisPop(false);
	}
}

void FigureMainView::clickCloseHandler(CCObject* pSender)
{
	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Peiyang) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Peiyang);
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Peiyang) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Peiyang , NewhandManager::Flag_Close);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_PEIYANG_OVER);
		NewhandManager::Instance()->doTaskFollow();
	}

	closeView();
	g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	return;
}

void FigureMainView::moveBy(CCPoint pos)
{
// 	CCAction* m_action = CCSequence::actions(	CCMoveBy::actionWithDuration(0.5, pos),NULL);
// 	this->runAction(m_action);
}


int FigureMainView::getType()
{
	return _viewType;
}

void FigureMainView::setType(int type)
{
	_viewType = type;
}

void FigureMainView::changeStage(int32 stage)
{
	switch (stage)
	{
	case 0:
		{
			this->setContentSize(m_viewSize);
			setPopContentSize(CCSizeMake(m_viewSize.width, m_viewSize.height));
			if (this->_figureV && this->_figureV->_attrLayer)
				this->_figureV->_attrLayer->setIsVisible(true);
		}
		break;
	case 1:
		{
			setPopContentSize(CCSizeMake(m_viewSize.width/2, m_viewSize.height));
			if (this->_figureV && this->_figureV->_attrLayer)
				this->_figureV->_attrLayer->setIsVisible(false);
		}
		break;
	default:
		break;
	}

	setUIStage(stage);
	g_pPopManage->adjustCordinate();
}

bool FigureMainView::handleBack()//bool isshow
{
	switch (getUIStage())
	{
	case 0:
		break;
	case 1://返回初态
		{
			//
			this->setContentSize(m_viewSize);
			setPopContentSize(CCSizeMake(m_viewSize.width, m_viewSize.height));
			if (this->_figureV && this->_figureV->_attrLayer)
				this->_figureV->_attrLayer->setIsVisible(true);
			//关闭背包
			//ViewManager::getInstance()->bagView->setisPop(false);
			BagView* bagview = (BagView*)LayerManager::windowLayer->getChildByTag(PopEventName::BAG);
			if (bagview)
				bagview->setisPop(false);

			//关掉返回按钮
			PopUIBg* _PopUIBg = (PopUIBg*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg);
			if (_PopUIBg)
			{
				_PopUIBg->setBackBtnShow(false);
			}

			setUIStage(0);
		}
		break;
	}
	return true;
}

void FigureMainView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->figureView)
	{
		ViewManager::getInstance()->figureView = 0;
	}
	FigureMediator  * pM = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	if (pM)
	{
		pM->_figureMainView = 0;
	}	
}