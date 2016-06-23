#include "CrystalUIPartialScrollView.h"
#include "../CrystalMediator.h"
#include "control/AppFacade.h"
#include "CCGeometry.h"
#include "CrystalView.h"
#include "manager/ViewManager.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"
#include "manager/TouchLayerEnum.h"

CrystalUIPartialScrollView * g_pCrystalScrollView = 0;

CrystalUIPartialScrollView::CrystalUIPartialScrollView(const CCRect & ccRect):CCUIPartialScrollView(ccRect)
{
	_crystalMediator = 0;
	_crystalProxy = 0;
	_crystalProxy = (CrystalProxy *)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	_nPreFocusPos = 0;
    _nPosIndex = -1;
}

CrystalUIPartialScrollView::~CrystalUIPartialScrollView()
{

}

CrystalUIPartialScrollView * CrystalUIPartialScrollView::crystalScrollViewWithCCRect(const CCRect & ccRect)
{
	CrystalUIPartialScrollView *pScrollView = new CrystalUIPartialScrollView(ccRect);
	if(pScrollView && pScrollView->init())
	{
		//pScrollView->setIsTouchEnabled(false);
		pScrollView->autorelease();
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
	return NULL;
}


int CrystalUIPartialScrollView::getTouchPosIndex( CCPoint point )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	/*SpriteNode *_BgPanel = new SpriteNode();
	_BgPanel->initWithSpriteFrameName("crystal/bg_crystal.png");
	CCSize _BgSize = _BgPanel->getTexture()->getContentSize();
	_BgPanel->release();*/
	SpriteNode *_crystal = new SpriteNode();
	_crystal->initWithSpriteFrameName("crystal/32.png");
	CCSize _crystalSize = _crystal->getContentSize();
	cocos2d::CCLog("Crystal:crystal width and height is(%f,%f)",_crystalSize.width,_crystalSize.height);
	_crystal->release();

	int curPage = 0; 
	curPage = this->currentScreen-1;
	int posIndex = 0;
	for(int i=0; i<CRYSTAL_ROW_NUM*CRYSTAL_COLUMN_NUM; i++)
	{
		//CrystalView * pCryView = new CrystalView();
		//cocos2d::CCLog("Crystal:make crystal point(%f,%f)",(winSizePixels.width-_BgSize.width)/2+cv->ccpCrystalPos[i].x+11,(winSizePixels.height-_BgSize.height)/2+cv->ccpCrystalPos[i].y+25);
		
		CCPoint pos;
		CCNode * pNode = (CCNode *)g_pCrystalScrollView->getLayerByTag(i/(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM))->getChildByTag(CrystalView::TAG_CRYSTAL+i+curPage * CRYSTAL_ROW_NUM*CRYSTAL_COLUMN_NUM);
		if (pNode)
		{
			pos = getScreenPos(pNode);
		}

		CCRect _crystalRect = CCRect(pos.x-_crystalSize.width/2,pos.y-_crystalSize.height/2,_crystalSize.width,_crystalSize.height);
		//pCryView->autorelease();
		if(CCRect::CCRectContainsPoint(_crystalRect, point))
		{
			posIndex = i + curPage * CRYSTAL_ROW_NUM*CRYSTAL_COLUMN_NUM;
			
			addHightLightFocusImage(i);
			
			cocos2d::CCLog("Crystal:touch hit crystal index %d,id is %d",posIndex,CRYSTALS[posIndex]);
			return posIndex;
		}
	}
	return (-1);
}

void CrystalUIPartialScrollView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,TLE::WindowLayer_CrystalView, true);
}

void CrystalUIPartialScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (currentScreen == 0 || totalScreens == 0)
		return;

	if (getIsTouchingMoving())
	{
		this->CCUIPartialScrollView::ccTouchEnded(pTouch, pEvent);
		return;
	}	

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

//  	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//The current need windowLayer focus
//  	{
//  		return false;
//  	}
	cocos2d::CCLog("Crystal:touch pos(%f,%f):",preTouchPoint.x,preTouchPoint.y);
	if (getIsTouchInContentLayer(pTouch)) 
	{
		cocos2d::CCLog("Crystal:touch is in ScrollLayer");
		int nPosIndex = getTouchPosIndex(preTouchPoint);
		if (nPosIndex >= 0)
		{
			std::map<int,CrystalInfo *>::iterator iter = _crystalProxy->_idToVos.find(CRYSTALS[nPosIndex]);
 			if(iter == _crystalProxy->_idToVos.end())
 			{
 				return;
 			}
 			if (!_crystalMediator)
			{
 				_crystalMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
			}
			cocos2d::CCLog("Crystal:nPosIndex %d",nPosIndex);
			_crystalMediator->updateDetailInfo(CRYSTALS[nPosIndex]);
			_crystalMediator->reqUpgradeTime(CRYSTALS[nPosIndex]);

			CrystalView * pCrystalview = ViewManager::getInstance()->crystalView;
			if (pCrystalview)
			{
				if (iter->second->level >= RoleManage::Instance()->roleInfo()->playerBaseInfo._lev)
				{
					pCrystalview->EnableUpgradeButton(false);
				}
				else
				{
					pCrystalview->EnableUpgradeButton(true);
				}
			}
		}
		_nPosIndex = nPosIndex;
	}	
}

void CrystalUIPartialScrollView::addHightLightFocusImage(int index)
{
	if (index < 0)
	{
		return;
	}	

	SpriteNode * pBack = (SpriteNode *)g_pCrystalScrollView->getLayerByTag(index/(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM))->getChildByTag(CrystalView::TAG_BGCIRCLE+index);
	if (pBack)
	{
		SpriteNode * pBackPre = (SpriteNode *)g_pCrystalScrollView->getLayerByTag(_nPreFocusPos/(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM))->getChildByTag(CrystalView::TAG_BGCIRCLE+_nPreFocusPos);
		if (pBackPre)
		{
			if (pBackPre->getChildByTag(0))
			{
				pBackPre->removeChildByTag(0,true);
			}					
		}				

		SpriteNode * pFocus = new SpriteNode();
		pFocus->initWithSpriteFrameName("crystal/focus.png");
		pFocus->setAnchorPoint(CCPointZero);
		pFocus->setPosition(ccp(POSX(-15),POSX(-15)));
		pBack->addChild(pFocus,0,0);
		pFocus->release();
		_nPreFocusPos = index;
	}
}