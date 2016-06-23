#include "SkillLayer.h"
#include "CCTouchDispatcher.h"
#include "manager/ViewManager.h"
#include "CCUIPartialScrollView.h"
#include "model/skill/SkillManager.h"
#include "model/skill/vo/SkillType.h"
#include "SkillItem.h"
#include "SkillUIPartialScrollView.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"

SkillLayer::SkillLayer()
{
	_sz = CCSIZE_SKILL_SCROLLVIEW;
	_skillView = 0;
}

bool SkillLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

    this->setIsTouchEnabled(true);

	addHighLight();

	return true;
}

SkillLayer::~SkillLayer()
{
	
	
}

void SkillLayer::addHighLight()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");
	SpriteNode * pHighlight = new SpriteNode();
	pHighlight->initWithSpriteFrameName("upskill/select.png");
	pHighlight->setTag(TAG_HIGH_LIGHT);
	pHighlight->setIsVisible(false);
	pHighlight->setAnchorPoint(CCPointZero);
	this->addChild(pHighlight,3);
	pHighlight->release();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
}

void SkillLayer::addSkillScrollView()
{
	if (!g_pSkillScrollView)
	{
		g_pSkillScrollView = new SkillUIPartialScrollView(CCRectMake(POSX(15),POSX(0),_sz.width-POSX(45),_sz.height-POSX(30)));
		g_pSkillScrollView->m_pri = TLE::WindowLayer_Figure;
		if (!g_pSkillScrollView)
		{
			return;
		}
		//g_pSkillScrollView->setAnchorPoint(CCPointZero);
		//g_pSkillScrollView->setIsRelativeAnchorPoint(true);
	}
		
	if (!this->getChildByTag(2))
	{
		this->addChild(g_pSkillScrollView,1,2);
		g_pSkillScrollView->release(); // LH0712LEAK
	}
}

void SkillLayer::loadDirections()
{
	SpriteNode * pDirectLeft = new SpriteNode();
	pDirectLeft->initWithSpriteFrameName("streng/direct.png");
	pDirectLeft->setPosition(ccp(_sz.width/2-POSX(45),_sz.height-POSX(25)));
	pDirectLeft->setScale(0.4);
	pDirectLeft->setTag(TAG_DIR_LEFT);
	if (this->getChildByTag(TAG_DIR_LEFT))
	{
		this->removeChildByTag(TAG_DIR_LEFT,true);
	}
	this->addChild(pDirectLeft,2);
	pDirectLeft->release();

	SpriteNode * pDirectRight = new SpriteNode();
	pDirectRight->initWithSpriteFrameName("streng/direct.png");
	pDirectRight->setFlipX(true); // x reverse
	pDirectRight->setScale(0.4);
	pDirectRight->setTag(TAG_DIR_RIGHT);
	pDirectRight->setPosition(ccp(_sz.width/2+POSX(45),_sz.height-POSX(25)));
	if (this->getChildByTag(TAG_DIR_RIGHT))
	{
		this->removeChildByTag(TAG_DIR_RIGHT,true);
	}
	this->addChild(pDirectRight,2);
	pDirectRight->release();

	if (!g_pSkillScrollView)	{ return;	}
	int nCurPage = g_pSkillScrollView->currentScreen;
	int totalPage = g_pSkillScrollView->totalScreens;
	char path[8];
	sprintf(path,ValuesUtil::Instance()->getString("US18").c_str(),nCurPage,totalPage);
	CCLabelTTF * pPageTxt = CCLabelTTF::labelWithString(path, g_sSimHeiFont, POSX(24));
	pPageTxt->setPosition(ccp(_sz.width/2,_sz.height-POSX(25)));
	pPageTxt->setTag(TAG_DIR_TXT);
	if (this->getChildByTag(TAG_DIR_TXT))
	{
		this->removeChildByTag(TAG_DIR_TXT,true);
	}
	this->addChild(pPageTxt,2);
}

void SkillLayer::updateDirections()
{
	if (!g_pSkillScrollView){return;}	

	int nCurPage = g_pSkillScrollView->currentScreen;
	int totalPage = g_pSkillScrollView->totalScreens;

	char path[8];
	sprintf(path,ValuesUtil::Instance()->getString("US18").c_str(),nCurPage,totalPage);
	CCLabelTTF * pPageTxt = (CCLabelTTF *)this->getChildByTag(TAG_DIR_TXT);
	if (pPageTxt)
	{
		pPageTxt->setString(path);
	}
}

void SkillLayer::loadSkillItems()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");

	std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
	std::map<int, std::map<int, SkillNode> >::iterator iter = rankDic->find(SkillType::PASSVIE);

	if(iter != rankDic->end())
	{
		int sitNum = 0;
		UpGradeInfo info;
		std::map<int, SkillNode> * skillNode = &iter->second;
		std::map<int, SkillNode>::iterator it = skillNode->begin();	

		CCLayer * pLayer = 0;
		int page = 0;
		if (!g_pSkillScrollView)
		{
			return;
		}
		//SkillView * sv = ViewManager::getInstance()->_skillView;
		//if (sv)
		//{
		//	sv->_nLen = 0;
		//}
		//this->g_pSKillScrollView->removeAllChildrenWithCleanup(true);
		for (;it != skillNode->end();it++)
		{
			info.id = it->second.skillInfo.id;
			info.lev = it->second.skillInfo.lev;
			info.active = it->second.skillInfo.active;
			if (sitNum < MAX_SKILL_NUM)
			{
				ViewManager::getInstance()->figureView->_figureV->SkillID[sitNum] = info.id;
			}
			SkillItem * si = new SkillItem(sitNum,&info);
			if (sitNum%9 == 0)
			{
				page = (int)sitNum/9;
				if (!g_pSkillScrollView->getLayerByTag(page))
				{
					g_pSkillScrollView->addLayerByTag(page);
				}
				pLayer = g_pSkillScrollView->getLayerByTag(page);
			}
			if (pLayer->getChildByTag(sitNum))
			{
				pLayer->removeChildByTag(sitNum,true);
			}
			//si->setPosition(POSX(48 + sitNum%3 * 109), _sz.height - POSX((sitNum%9)/3 * 115 - 81));
			si->setPosition(POSX(5+sitNum%3 * 109), _sz.height - POSX((sitNum%9)/3 * 115 + 140));
			pLayer->addChild(si,0,sitNum);
			si->release(); // LH0713
			++sitNum;
		}
	}
	else
	{
		//
	}

	loadDirections();

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");
}

void SkillLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
}

bool SkillLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	this->setIsTouchEnabled(true);
	/*CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);*/
	CCLog("Skill2:touch point(%f,%f)",preTouchPoint.x,preTouchPoint.y);
	/*
	CCNode * s3 = this->getChildByTag(31);
	if (!s3)
	{
		return false;
	}
	CCPoint c3 = getScreenPos(s3);
	CCRect rect3 = CCRect(c3.x,c3.y,_sz.width,_sz.height);
	if (!_skillView)

	{

		_skillView = ViewManager::getInstance()->_skillView;

		if (!_skillView)

		{

			return false;

		}

	}
	*/
	CCPoint pot = getScreenPos(this);
	if (!CCRect::CCRectContainsPoint(CCRectMake(pot.x,pot.y,_sz.width,_sz.height),preTouchPoint))
	{		
		if (_skillView)
		{
			_skillView->_stateSkill = 0;
		}
		if (ViewManager::getInstance()->_skillView)
		{
			ViewManager::getInstance()->_skillView->showSkillSelectPanel(0);
		}
	}
	else
	{
		SpriteNode * pHighLight = (SpriteNode *)this->getChildByTag(SkillLayer::TAG_HIGH_LIGHT);
		if (pHighLight)
		{
			pHighLight->setIsVisible(false);
		}
	}
	return true;
}

void SkillLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

    if(abs(touchPoint.x - preTouchPoint.x) < 5)
    {
        return;
    }
	SpriteNode * pHighLight = (SpriteNode *)this->getChildByTag(TAG_HIGH_LIGHT);
	if (pHighLight)
	{
		pHighLight->setIsVisible(false);
	}

}

void SkillLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}
