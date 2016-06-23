#include "XHView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "socket/network/GameServerSocket.h"
#include "manager/ViewManager.h"
#include "view/zx/ZXMediator.h"
#include "ZXView.h"
#include "socket/command/c46/CCMD463.h"
#include "socket/command/c46/CCMD469.h"
#include "socket/command/c46/CCMD46B.h"
#include "model/zx/XHConfManager.h"
#include "XH.h"
#include "XHCopy.h"
#include "XHFigure.h"

XHView::XHView()
{
	_pContainer = 0;
	
	for (int i = 0; i < 8; i++)
		m_pEquipSlot[i] = 0;
	for (int i = 0; i < 16; i++)
		m_pBag[i] = 0;
	m_fCtlInterval = 0.0f;
	m_iCtlState = XHViewCtl_NONE;
	m_iCopyPosType = 0;
	m_iCopyPos = 0;
	m_iReadySendPosType = 0;
	m_iReadySendPos = 0;

	m_iXHValue = 0;
}


XHView::~XHView()
{
	SCMD46ANode** tmp = 0;
	for (std::map<int, SCMD46ANode** >::iterator it = m_vXHRoleEquipList.begin(); it != m_vXHRoleEquipList.end(); it++)
	{
		tmp = it->second;
		for (int i = 0; i < 8; i++)
		{
			SCMD46ANode* sub = *(tmp+i);
			delete sub;
		}
	}
	if (tmp)
		delete [] tmp;
	m_vXHRoleEquipList.clear();
}


bool XHView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	key = 0;
	setNeedBg(NeedBg_NO);

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 1);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(16.0f), POSX(12.0f)), ccp(0,0), CCSizeMake(POSX(928.0f), POSX(562.0f)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(25.0f), POSX(32.0f)), ccp(0,0), CCSizeMake(POSX(470.0f-25.0f), POSX(608.0f-86.0f)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(476.0f), POSX(32.0f)), ccp(0,0), CCSizeMake(POSX(910.0f-476.0f), POSX(608.0f-86.0f)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();
	}

	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(XHView::clickClose) );
		_btnX->setPosition(ccp(screenSize.width-_btnX->getContentSize().width/2, 
			screenSize.height-_btnX->getContentSize().height/2));


		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btnX, 0, 0);
		buttonMenu->setPosition(ccp(0, 0));
		buttonMenu->setTouchLayer(TLE::WindowLayer_zx-1);
		this->addChild(buttonMenu, 5);
		buttonMenu->release();
	}
	//title
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/zx/title.png");
		_pContainer->addChild(sp, 3);
		sp->release();
		sp->setPosition(ccp(POSX(474), POSX(640-74)));
	}
	//xh_0
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/zx/xh_0.png");
		_pContainer->addChild(sp, 3);
		sp->release();
		sp->setPosition(ccp(POSX(246), POSX(640-348)));
	}
	//bag
	{
		for (int i = 0; i < 16; i++)
		{
			m_pBag[i] = new LayerNode();
			m_pBag[i]->init();
			m_pBag[i]->setPosition(POSX(540+100*(i%4)), POSX(640-142-106*(i/4)));
			_pContainer->addChild(m_pBag[i], 5, XHViewTAG_BAG+i);
			m_pBag[i]->release();

			{
				SpriteNode* sp = new SpriteNode();
				sp->initWithFile("assets/ui/zx/cellbg.png");
				m_pBag[i]->addChild(sp, 0, 1);
				sp->release();
				sp->setPosition(ccp(POSX(0), POSX(0)));
			}
		}
	}
	//EquipSlot
	{
		CCPoint equipslotpos[8] = {
		ccp(POSX(245), POSX(640-186)),
		ccp(POSX(372), POSX(640-233)),
		ccp(POSX(401), POSX(640-349)),
		ccp(POSX(361), POSX(640-458)),

		ccp(POSX(245), POSX(640-505)),
		ccp(POSX(124), POSX(640-458)),
		ccp(POSX(85), POSX(640-349)),
		ccp(POSX(124), POSX(640-233)),
		};

		//int lev = RoleManage::Instance()->roleLev();
		for (int i = 0; i < 8; i++)
		{
			m_pEquipSlot[i] = new LayerNode();
			m_pEquipSlot[i]->init();
			m_pEquipSlot[i]->setPosition(equipslotpos[i]);
			_pContainer->addChild(m_pEquipSlot[i], 6, XHViewTAG_SLOT+i);
			m_pEquipSlot[i]->release();
			
			{
				SpriteNode* sp = new SpriteNode();
				sp->initWithFile("assets/ui/zx/cellbg.png");
				m_pEquipSlot[i]->addChild(sp, 0, 1);
				sp->release();
				sp->setPosition(ccp(POSX(0), POSX(0)));
			}

			//if ((i >= 0 && i <=3 && lev<50) || (i == 4 && lev<60) || (i == 5 && lev<70) || (i == 6 && lev<80) || (i == 7 && lev<90))
			//{
			//	SpriteNode* sp = new SpriteNode();
			//	sp->initWithFile("assets/ui/zx/celllockbg.png");
			//	m_pEquipSlot[i]->addChild(sp, 1, XHViewEquipTAG_LOCKBG);
			//	sp->release();
			//	sp->setPosition(ccp(POSX(0), POSX(0)));				
			//}
		}
	}
	

	//
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX015" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(31), POSX(640-120)));
		_pContainer->addChild(pLabel, 5);
		pLabel->setColor(ccc3(239, 200, 0));
	}

	//一键合成
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_zx-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(XHView::clickOneKeyHeCheng) );
			_btn->setPosition(ccp(POSX(599), POSX(640-564)));


			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX001" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));
		}

		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(XHView::clickGoZX) );
			_btn->setPosition(ccp(POSX(817), POSX(640-564)));


			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX002" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));
		}
	}
	//figure
	{
		
		XHFigure* pXHFigure = XHFigure::figureScrollViewWithCCRect(
			CCRectMake(POSX(124), 
			POSX(640-505+74/2),
			POSX(401-124-74/2),
			POSX(505-186-74)));
		
		pXHFigure->setIsTouchEnabled(true);
		if (_pContainer->getChildByTag(XHViewTAG_FIGURE))
		{
			_pContainer->removeChildByTag(XHViewTAG_FIGURE, true);
		}
		_pContainer->addChild(pXHFigure, 5, XHViewTAG_FIGURE);
		pXHFigure->release();
	}
	//
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX024" ).c_str(), CCSizeMake(POSX(400), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		//pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(245), POSX(640-562)));
		_pContainer->addChild(pLabel, 5);
		pLabel->setColor(ccc3(251, 216, 0));
	}
	//
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX023" ).c_str(), CCSizeMake(POSX(400), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		//pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(245), POSX(640-590)));
		_pContainer->addChild(pLabel, 5);
		pLabel->setColor(ccc3(251, 216, 0));
	}
	return true;
}

void XHView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_zx-10, true);
	
}

void XHView::onEnter()
{
	setIsTouchEnabled(true);
	LayerNode::onEnter();
}

void XHView::onExit()
{
	setIsTouchEnabled(false);
	LayerNode::onExit();
}

void XHView::clickOneKeyHeCheng(CCObject* pSender)
{
	//弹出合成确认框
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		return;

	//计算预计合成到哪个星魂
	uint tarPos = 255;
	XH* pTarXH = 0;
	
	int hasCount = 0;
	for (int i = 0; i < 16; i++)
	{
		XH* pBagXH = (XH*)m_pBag[i]->getChildByTag(XHViewBagTAG_pic);
		if (pBagXH)
		{
			hasCount++;

			if (tarPos == 255)
			{
				tarPos = i;
				pTarXH = pBagXH;
			}
			else
			{
				XHConfVo* tarPosConfXH = XHConfManager::Instance()->getXHConf(pTarXH->m_iXHType);if (!tarPosConfXH)continue;
				XHConfVo* tmpPosConfXH = XHConfManager::Instance()->getXHConf(pBagXH->m_iXHType);if (!tmpPosConfXH)continue;
						

				if (tarPosConfXH->color == tmpPosConfXH->color)
				{//lv compare
					if (pTarXH->m_iCurExp >= pBagXH->m_iCurExp)
					{
						continue;
					}
					else
					{
						tarPos = i;
						pTarXH = pBagXH;						
					}
				}
				else if (tarPosConfXH->color > tmpPosConfXH->color)
				{
					continue;
				}
				else
				{
					tarPos = i;
					pTarXH = pBagXH;
				}
			}
		}
	}

	if (hasCount<2)
	{
		LangManager::msgShow("ZXMSG029");
		return;//星魂不足无法合成
	}
	//
	char strShow[50];
	XHConfVo* tarPosConfXH = XHConfManager::Instance()->getXHConf(pTarXH->m_iXHType);if (!tarPosConfXH)return;
	sprintf(strShow, ValuesUtil::Instance()->getString( "ZX022" ).c_str(), tarPosConfXH->name.c_str());
	//
	Confirm* pConfirm = new Confirm();
	pConfirm->initWithParam(strShow, this, menu_selector(XHView::handleOneKeyHeCheng), menu_selector(XHView::handleOneKeyHeChengCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();

}

void XHView::handleOneKeyHeCheng(CCObject* pSender)
{
	CCMD46B cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );

	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void XHView::handleOneKeyHeChengCancel(CCObject* pSender)
{
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void XHView::clickGoZX(CCObject* pSender)
{
	this->setIsVisible(false);

	//
	if (LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX))
	{
		return;
	}
	ZXView* _zx = new ZXView();
	_zx->init();
	_zx->setPosition(ccp(0, 0));
	LayerManager::intervalLayer->addChild(_zx, IntervalLayer::IntervalLayerZ_ZX, IntervalLayer::IntervalLayerTAG_ZX);
	_zx->release();

	//
	CCMD463 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}

void XHView::clickClose(CCObject* pSender)
{
	if (this->getParent())
	{
		ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
		if (pZXMediator)
		{
			//
			if (LayerManager::tipsLayer->getChildByTag( TipsLayer::TipsLayerTAG_ZXDuiView))
			{
				LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_ZXDuiView, true);
			}
			//
			if (LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX))
			{
				LayerManager::intervalLayer->removeChildByTag(IntervalLayer::IntervalLayerTAG_ZX, true);
			}
			//
			pZXMediator->m_pXHView = 0;
		}

		this->setisPop(false);
	}
}

void XHView::buildEquipXH(std::list<SCMD46ANode>& a_XHEquipList)
{
	for (std::list<SCMD46ANode>::iterator it = a_XHEquipList.begin(); it != a_XHEquipList.end(); it++)
	{
		SCMD46ANode& node = *it;
		if (node.b_sitGrid >= 8)
			continue;//error data

		std::map<int, SCMD46ANode** >::iterator it2 = m_vXHRoleEquipList.find(node.a_roldId);
		if (it2 == m_vXHRoleEquipList.end())
		{
			SCMD46ANode** tmpNew = new SCMD46ANode*[8];
			SCMD46ANode* tmpNew2;
			//tmpNew = &tmpNew2;
			for (int i = 0; i < 8; i++)
			{
				tmpNew[i] = 0;
			}
			tmpNew[node.b_sitGrid] = new SCMD46ANode();
			*tmpNew[node.b_sitGrid] = node;

			SCMD46ANode tmptmp = *tmpNew[node.b_sitGrid];

			m_vXHRoleEquipList.insert(std::make_pair(node.a_roldId, tmpNew));
		}
		else
		{
			SCMD46ANode** tmpNew;
			tmpNew = it2->second;
			if (!tmpNew[node.b_sitGrid])
			{
				tmpNew[node.b_sitGrid] = new SCMD46ANode();
			}
			*tmpNew[node.b_sitGrid] = node;
		}
	}
	//show first role equip XHs
	XHFigure* pXHFigure = (XHFigure*)_pContainer->getChildByTag(XHViewTAG_FIGURE);
	if (pXHFigure)
		showFigureXH(pXHFigure->getCurScreenFigureId());
}

void XHView::buildBagXH(std::list<SCMD464_465Node>& a_XHList)
{
	for (std::list<SCMD464_465Node>::iterator it = a_XHList.begin(); it != a_XHList.end(); it++)
	{
		SCMD464_465Node& node = *it;
		

		if (!m_pBag[node.a_sitGrid])
			continue;
		
		m_pBag[node.a_sitGrid]->removeChildByTag(XHViewBagTAG_pic, true);
		
		//pic
		if (node.b_id == 0)
			continue;//here no xh

		XH* pXH = new XH();
		if (pXH->init(node.c_goodId, node.d_lv, node.e_curexp))
		{
			m_pBag[node.a_sitGrid]->addChild(pXH, 1, XHViewBagTAG_pic);
			pXH->release();		
		}
		else
		{
			delete pXH;
		}	
	}
}

bool XHView::getXHByTouch(CCPoint touch, int& posType, int& pos)
{
	//XH::XH_POS_16
	for (int i = 0; i < 16; i++)
	{
		SpriteNode* pRoundBg = (SpriteNode*)m_pBag[i]->getChildByTag(1);

		CCPoint pPoint = getScreenPos(pRoundBg);

		CCRect rect = CCRectZero;
		rect.origin = ccpAdd(pPoint, ccp(-pRoundBg->getContentSize().width/2, -pRoundBg->getContentSize().height/2));
		rect.size = pRoundBg->getContentSize();

        bool sus = CCRect::CCRectContainsPoint(rect, touch);
		if (sus)
		{//碰撞成功
			posType = XH::XH_POS_16;
			pos = i;
			CCLog("posType:%d, pos:%d", posType, pos);
			return true;
		}
	}
	//XH::XH_POS_8
	for (int i = 0; i < 8; i++)
	{
		SpriteNode* pRoundBg = (SpriteNode*)m_pEquipSlot[i]->getChildByTag(1);

		CCPoint pPoint = getScreenPos(pRoundBg);

		CCRect rect = CCRectZero;
		rect.origin = ccpAdd(pPoint, ccp(-pRoundBg->getContentSize().width/2, -pRoundBg->getContentSize().height/2));
		rect.size = pRoundBg->getContentSize();

        bool sus = CCRect::CCRectContainsPoint(rect, touch);
		if (sus)
		{//碰撞成功
			posType = XH::XH_POS_8;
			pos = i;
			CCLog("posType:%d, pos:%d", posType, pos);
			return true;
		}	
	}
	return false;
}

void XHView::startSchedule()
{
	schedule(schedule_selector(XHView::step), 0.1f);

	m_fCtlInterval = 0.0f;

	setCtlState(XHViewCtl_NONE);
}


void XHView::stopSchedule()
{
	unschedule(schedule_selector(XHView::step));

	m_fCtlInterval = 0.0f;

	setCtlState(XHViewCtl_NONE);
}

bool XHView::createCopy(XH* pOrg)
{
	if (!pOrg)
		return false;

	XHCopy* pCopy = (XHCopy*)_pContainer->getChildByTag(XHViewTAG_COPY);
	if (pCopy)
		pCopy->removeFromParentAndCleanup(true);

	pCopy = new XHCopy();
	pCopy->init(pOrg);
	_pContainer->addChild(pCopy, 6, XHViewTAG_COPY);
	pCopy->release();//getScreenPos(pOrg)
	pCopy->setPosition(ccpAdd(m_vPreTouchPoint,ccp(-_pContainer->getPosition().x, -_pContainer->getPosition().y)));

	pOrg->setIsVisible(false);

	return true;
}

void XHView::cancelCopy()
{
	XHCopy* pCopy = (XHCopy*)_pContainer->getChildByTag(XHViewTAG_COPY);
	if (pCopy)
	{
		pCopy->m_pOrg->setIsVisible(true);
		pCopy->removeFromParentAndCleanup(true);
	}
}

bool XHView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	setCtlState(XHViewCtl_NONE);

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
    m_vPreTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if (!getXHByTouch(m_vPreTouchPoint, m_iCopyPosType, m_iCopyPos))
		return false;

	startSchedule();

	setCtlState(XHViewCtl_PRESSED);

	return true;
}

void XHView::step(float dt)
{
	switch (getCtlState())
	{
	case XHViewCtl_PRESSED:
		{
			m_fCtlInterval += dt;
			if (m_fCtlInterval >= 0.3f)
			{
				setCtlState(XHViewCtl_INTERVAL_PASS);
				//copy 原消失
				if (m_iCopyPosType == XH::XH_POS_16)
				{
					if (!createCopy((XH*)m_pBag[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic)))
					{
						stopSchedule();
						return;
					}
				}
				else if (m_iCopyPosType == XH::XH_POS_8)
				{
					if (!createCopy((XH*)m_pEquipSlot[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic)))
					{
						stopSchedule();
						return;
					}
				}
				else
				{
					stopSchedule();
					return;
				}
				//

			}
		}
		break;
	
	default:
		break;
	}
}

void XHView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
    m_vPreTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	switch (getCtlState())
	{
	case XHViewCtl_INTERVAL_PASS:
		{
			//copy 跟手指走
			XHCopy* pCopy = (XHCopy*)_pContainer->getChildByTag(XHViewTAG_COPY);
			if (pCopy)
			{
				pCopy->setPosition(ccpAdd(m_vPreTouchPoint,ccp(-_pContainer->getPosition().x, -_pContainer->getPosition().y)));
			}
		}
		break;
	default:
		break;
	}
}

void XHView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
    m_vPreTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	switch (getCtlState())
	{
	case XHViewCtl_PRESSED:
		{
			//显示tips
			if (m_iCopyPosType == XH::XH_POS_8)
			{
				XH* pXH = (XH*)m_pEquipSlot[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic);
				if (pXH)
				{
					pXH->myTip->rollOverHander();
				}
			}
			else if (m_iCopyPosType == XH::XH_POS_16)
			{
				XH* pXH = (XH*)m_pBag[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic);
				if (pXH)
				{
					pXH->myTip->rollOverHander();
				}		
			}
		}
		break;
	case XHViewCtl_INTERVAL_PASS:
		{
			if (getXHByTouch(m_vPreTouchPoint, m_iReadySendPosType, m_iReadySendPos))
			{
				if (m_iCopyPosType == m_iReadySendPosType && m_iCopyPos == m_iReadySendPos)
				{}
				else if (m_iCopyPosType == XH::XH_POS_8 && m_iReadySendPosType == XH::XH_POS_16)
				{//equip 2 bag
					XH* pBagXH = (XH*)m_pBag[m_iReadySendPos]->getChildByTag(XHViewBagTAG_pic);
					if (pBagXH)
					{
						//compare
						
						//color compare
						bool isBagFrom = false;
						XH* pEquipXH = (XH*)m_pEquipSlot[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic);
						XHConfVo* confBagXH = XHConfManager::Instance()->getXHConf(pBagXH->m_iXHType);if (!confBagXH)return;
						XHConfVo* confEquipXH = XHConfManager::Instance()->getXHConf(pEquipXH->m_iXHType);if (!confEquipXH)return;
						if (confBagXH->color == confEquipXH->color)
						{//lv compare
							if (pBagXH->m_iCurExp >= pEquipXH->m_iCurExp)
								isBagFrom = true;
							else
								isBagFrom = false;
						}
						else if (confBagXH->color > confEquipXH->color)
						{
							isBagFrom = true;
						}
						else
							isBagFrom = false;

							
						
						
						//弹出合成确认框
						if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
							return;


						Confirm* pConfirm = new Confirm();
						char strMove[90];
						sprintf(strMove, ValuesUtil::Instance()->getString("ZX016").c_str(), 
							isBagFrom?confBagXH->name.c_str():confEquipXH->name.c_str(), isBagFrom?confEquipXH->name.c_str():confBagXH->name.c_str());
						pConfirm->initWithParam(strMove, this, menu_selector(XHView::handleXHMove), menu_selector(XHView::handleXHMoveCancel));
						LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
						pConfirm->release();
					}
					else
					{//移动物品
						XHFigure* pXHFigure = (XHFigure*)_pContainer->getChildByTag(XHViewTAG_FIGURE);
						if (pXHFigure)
						{
							CCMD469 cmd;
							cmd.a_fromPosType = m_iCopyPosType;
							cmd.b_fromPos= m_iCopyPos;
							cmd.c_toPosType= m_iReadySendPosType;
							cmd.d_toPos= m_iReadySendPos;
							cmd.e_roldId= pXHFigure->getCurScreenFigureId();
							GameServerSocket::getInstance()->sendMessage( &cmd );
						}
					}
					
				}
				else if (m_iCopyPosType == XH::XH_POS_16 && m_iReadySendPosType == XH::XH_POS_8)
				{//bag 2 equip
					XH* pEquipXH = (XH*)m_pEquipSlot[m_iReadySendPos]->getChildByTag(XHViewBagTAG_pic);
					if (pEquipXH)
					{
						//color compare
						bool isBagFrom = false;
						XH* pBagXH = (XH*)m_pBag[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic);
						XHConfVo* confEquipXH = XHConfManager::Instance()->getXHConf(pEquipXH->m_iXHType);if (!confEquipXH)return;
						XHConfVo* confBagXH = XHConfManager::Instance()->getXHConf(pBagXH->m_iXHType);if (!confBagXH)return;
						if (confEquipXH->color == confBagXH->color)
						{//lv compare
							if (pEquipXH->m_iCurExp >= pBagXH->m_iCurExp)
								isBagFrom = true;
							else
								isBagFrom = false;
						}
						else if (confEquipXH->color > confBagXH->color)
						{
							isBagFrom = true;
						}
						else
							isBagFrom = false;

						//弹出合成确认框
						if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
							return;


						Confirm* pConfirm = new Confirm();
						char strMove[90];
						sprintf(strMove, ValuesUtil::Instance()->getString("ZX016").c_str(), 
							isBagFrom?confEquipXH->name.c_str():confBagXH->name.c_str(), isBagFrom?confBagXH->name.c_str():confEquipXH->name.c_str());
						
						pConfirm->initWithParam(strMove, this, menu_selector(XHView::handleXHMove), menu_selector(XHView::handleXHMoveCancel));
						LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
						pConfirm->release();					
					}
					else
					{//移动物品
						XHFigure* pXHFigure = (XHFigure*)_pContainer->getChildByTag(XHViewTAG_FIGURE);
						if (pXHFigure)
						{
							CCMD469 cmd;
							cmd.a_fromPosType = m_iCopyPosType;
							cmd.b_fromPos= m_iCopyPos;
							cmd.c_toPosType= m_iReadySendPosType;
							cmd.d_toPos= m_iReadySendPos;
							cmd.e_roldId= pXHFigure->getCurScreenFigureId();
							GameServerSocket::getInstance()->sendMessage( &cmd );
						}				
					}
				}
				else if (m_iCopyPosType == XH::XH_POS_16 && m_iReadySendPosType == XH::XH_POS_16)
				{//bag 2 bag
					XH* pBagXH = (XH*)m_pBag[m_iReadySendPos]->getChildByTag(XHViewBagTAG_pic);
					if (pBagXH)
					{
						//compare
						
						//color compare
						bool isBagFrom = false;
						XH* pBagXH2 = (XH*)m_pBag[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic);
						XHConfVo* confBagXH = XHConfManager::Instance()->getXHConf(pBagXH->m_iXHType);if (!confBagXH)return;
						XHConfVo* confBagXH2 = XHConfManager::Instance()->getXHConf(pBagXH2->m_iXHType);if (!confBagXH2)return;
						if (confBagXH->color == confBagXH2->color)
						{//lv compare
							if (pBagXH->m_iCurExp >= pBagXH2->m_iCurExp)
								isBagFrom = true;
							else
								isBagFrom = false;
						}
						else if (confBagXH->color > confBagXH2->color)
						{
							isBagFrom = true;
						}
						else
							isBagFrom = false;

							
						
						
						//弹出合成确认框
						if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
							return;


						Confirm* pConfirm = new Confirm();
						char strMove[90];
						sprintf(strMove, ValuesUtil::Instance()->getString("ZX016").c_str(), 
							isBagFrom?confBagXH->name.c_str():confBagXH2->name.c_str(), isBagFrom?confBagXH2->name.c_str():confBagXH->name.c_str());
						pConfirm->initWithParam(strMove, this, menu_selector(XHView::handleXHMove), menu_selector(XHView::handleXHMoveCancel));
						LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
						pConfirm->release();					
					}
					else
					{
						//移动物品
						XHFigure* pXHFigure = (XHFigure*)_pContainer->getChildByTag(XHViewTAG_FIGURE);
						if (pXHFigure)
						{
							CCMD469 cmd;
							cmd.a_fromPosType = m_iCopyPosType;
							cmd.b_fromPos= m_iCopyPos;
							cmd.c_toPosType= m_iReadySendPosType;
							cmd.d_toPos= m_iReadySendPos;
							cmd.e_roldId= pXHFigure->getCurScreenFigureId();
							GameServerSocket::getInstance()->sendMessage( &cmd );
						}	
					}
				}
				else if (m_iCopyPosType == XH::XH_POS_8 && m_iReadySendPosType == XH::XH_POS_8)
				{//equip 2 equip
					XH* pEquipXH = (XH*)m_pEquipSlot[m_iReadySendPos]->getChildByTag(XHViewBagTAG_pic);
					if (pEquipXH)
					{
						//compare
						
						//color compare
						bool isBagFrom = false;
						XH* pEquipXH2 = (XH*)m_pEquipSlot[m_iCopyPos]->getChildByTag(XHViewBagTAG_pic);
						XHConfVo* confEquipXH = XHConfManager::Instance()->getXHConf(pEquipXH->m_iXHType);if (!confEquipXH)return;
						XHConfVo* confEquipXH2 = XHConfManager::Instance()->getXHConf(pEquipXH2->m_iXHType);if (!confEquipXH2)return;
						if (confEquipXH->color == confEquipXH2->color)
						{//lv compare
							if (pEquipXH->m_iCurExp >= pEquipXH2->m_iCurExp)
								isBagFrom = true;
							else
								isBagFrom = false;
						}
						else if (confEquipXH->color > confEquipXH2->color)
						{
							isBagFrom = true;
						}
						else
							isBagFrom = false;

							
						
						
						//弹出合成确认框
						if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
							return;


						Confirm* pConfirm = new Confirm();
						char strMove[90];
						sprintf(strMove, ValuesUtil::Instance()->getString("ZX016").c_str(), 
							isBagFrom?confEquipXH->name.c_str():confEquipXH2->name.c_str(), isBagFrom?confEquipXH2->name.c_str():confEquipXH->name.c_str());
						pConfirm->initWithParam(strMove, this, menu_selector(XHView::handleXHMove), menu_selector(XHView::handleXHMoveCancel));
						LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
						pConfirm->release();					
					}
					else
					{
						//移动物品
						XHFigure* pXHFigure = (XHFigure*)_pContainer->getChildByTag(XHViewTAG_FIGURE);
						if (pXHFigure)
						{
							CCMD469 cmd;
							cmd.a_fromPosType = m_iCopyPosType;
							cmd.b_fromPos= m_iCopyPos;
							cmd.c_toPosType= m_iReadySendPosType;
							cmd.d_toPos= m_iReadySendPos;
							cmd.e_roldId= pXHFigure->getCurScreenFigureId();
							GameServerSocket::getInstance()->sendMessage( &cmd );
						}	
					}
				
				}
				//copy被remove 原重现
				cancelCopy();
			}
			else
			{
				//copy被remove 原重现
				cancelCopy();
				
			}
		}
		break;
	default:
		break;
	}

	stopSchedule();
}




void XHView::handleXHMove(CCObject* pSender)
{
	//移动物品
	XHFigure* pXHFigure = (XHFigure*)_pContainer->getChildByTag(XHViewTAG_FIGURE);
	if (pXHFigure)
	{
		CCMD469 cmd;
		cmd.a_fromPosType = m_iCopyPosType;
		cmd.b_fromPos= m_iCopyPos;
		cmd.c_toPosType= m_iReadySendPosType;
		cmd.d_toPos= m_iReadySendPos;
		cmd.e_roldId= pXHFigure->getCurScreenFigureId();
		GameServerSocket::getInstance()->sendMessage( &cmd );
	}

	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void XHView::handleXHMoveCancel(CCObject* pSender)
{
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void XHView::showFigureXH(int32 roleId)
{
	for (int i = 0; i < 8; i++)
	{
		m_pEquipSlot[i]->removeChildByTag(XHViewBagTAG_pic, true);
	}

	//更新lock
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* listEx = RoleManage::Instance()->mercListEx();
	for(std::map<RoleManage::MercKeyIndex, PlayerInfoVo>::iterator iterEx = listEx->begin();iterEx != listEx->end(); iterEx++)
	{
		int id = iterEx->first.id;
		int lev = iterEx->second.playerBaseInfo._lev;
		if (id == roleId)
		{
			for (int i = 0; i < 8; i++)
			{
				LayerNode* equipSlot = m_pEquipSlot[i];
				if (equipSlot && equipSlot->getChildByTag(XHViewEquipTAG_LOCKBG))
					equipSlot->removeChildByTag(XHViewEquipTAG_LOCKBG, true);

				if ((i >= 0 && i <=3 && lev<50) || (i == 4 && lev<60) || (i == 5 && lev<70) || (i == 6 && lev<80) || (i == 7 && lev<90))
				{
					SpriteNode* sp = new SpriteNode();
					sp->initWithFile("assets/ui/zx/celllockbg.png");
					m_pEquipSlot[i]->addChild(sp, 1, XHViewEquipTAG_LOCKBG);
					sp->release();
					sp->setPosition(ccp(POSX(0), POSX(0)));				
				}
			}
		}
	}


	std::map<int, SCMD46ANode** >::iterator it = m_vXHRoleEquipList.find(roleId);
	if (it == m_vXHRoleEquipList.end())
	{
		return;
	}

	SCMD46ANode** ppXHEquip = it->second;
	if (!ppXHEquip)
		return;

	m_iXHValue = 0;
	for (int i = 0; i < 8; i++)
	{
		m_pEquipSlot[i]->removeChildByTag(XHViewBagTAG_pic, true);
	}
	for (int i = 0; i < 8; i++)
	{
		SCMD46ANode* node = ppXHEquip[i];
		if (!node)
			continue;

		if (!m_pEquipSlot[node->b_sitGrid])
			continue;
		
		//m_pEquipSlot[node->b_sitGrid]->removeChildByTag(XHViewBagTAG_pic, true);
		//
		m_iXHValue += node->f_curexp;

		//pic
		if (node->c_id == 0)
			continue;//here no xh

		XH* pXH = new XH();
		if (pXH->init(node->d_goodId, node->e_lv, node->f_curexp))
		{
			m_pEquipSlot[node->b_sitGrid]->addChild(pXH, 1, XHViewBagTAG_pic);
			pXH->release();		
		}
		else
		{
			delete pXH;
		}	
	}	

	updateXHViewValue();



}

void XHView::updateXHViewValue()
{
	//
	CCLabelTTF* pLabel = (CCLabelTTF*)_pContainer->getChildByTag(XHViewTAG_XH_VALUE);
	if (!pLabel)
	{
		pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(116), POSX(640-120)));
		_pContainer->addChild(pLabel, 5, XHViewTAG_XH_VALUE);
		pLabel->setColor(ccc3(239, 255, 255));
	}
	char valstr[20];
	sprintf(valstr, "%d", m_iXHValue);
	pLabel->setString(valstr);

}