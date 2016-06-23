#include "StuntsLayer.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "FigureCreate.h"
#include "model/player/FigureBaseManage.h"
#include "model/player/RoleManage.h"
#include "SkillItem.h"
#include "FigureView.h"
#include "utils/TipHelps.h"
#include "manager/TouchLayerEnum.h"

StuntsLayer::StuntsLayer()
{

}

bool StuntsLayer::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setIsTouchEnabled(true);

	LoadBackGround();

	LoadItems();

	return true;
}

void StuntsLayer::LoadBackGround()
{
	CCUIBackground * pStuntBack = new CCUIBackground();
	if (pStuntBack)
	{
		bool ret = pStuntBack->initWithSpriteFrame("ui.png",CCPointZero,CCPointZero,CCSizeMake(POSX(240),POSX(120)),128);
		if (ret)
		{
			pStuntBack->setTag(TAG_BACKGROUND);
			this->addChild(pStuntBack);
			_layerSize = pStuntBack->getContentSize();
			this->setContentSize(_layerSize);
		}
		pStuntBack->release();
	}
}

void StuntsLayer::LoadItems()
{
	if ( !g_pFigureScrollView ){ return; }

	int nCurPage = g_pFigureScrollView->currentScreen-1;

	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int ,PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	int count = 0;
	for(;iter != list->end();iter++)
	{
		if(count == nCurPage)
		{
			break;
		}
		++count;
	}

	int merID = iter->second.figureBaseInfo.mercId;
	FigureCfgBaseVo * pFigureCfgBaseVo = FigureBaseManage::Instance()->getMercBase(merID);
	if (!pFigureCfgBaseVo){return;}
	std::vector<int>::iterator it = pFigureCfgBaseVo->skill1.begin();
	int nNum = pFigureCfgBaseVo->skill1.size();
	int * stunts = new int[nNum];
	int i = 0;
	for (;it != pFigureCfgBaseVo->skill1.end();it++)
	{
		stunts[i] = *it;
		++i;
	}
	int maxN = nNum;
	int roleLev = RoleManage::Instance()->roleLev();
	if (roleLev < 30)
	{
		maxN = 1;
	}
	for(int sitnum = 0; sitnum < maxN; sitnum++)
	{
		UpGradeInfo info;
		info.active = false;
		info.id = stunts[sitnum];
		info.lev = 1;
		SkillItem * pItem = new SkillItem( sitnum , &info , 1 );
		CCSize size = pItem->getContentSize();
		pItem->setTag(TAG_STUNTS+sitnum);
		pItem->setAnchorPoint(ccp(0.5,0.5));
		pItem->setPosition(ccp((sitnum*2+1)*_layerSize.width/4, _layerSize.height/2));
		this->addChild(pItem,1);
		pItem->release();
	}

	delete []stunts;
}

void StuntsLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,TLE::TipsLayer_equipStunts,true);
}

bool StuntsLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	CCPoint pos = getScreenPos(this);
	CCSize size = _layerSize;
	if (!CCRect::CCRectContainsPoint(CCRectMake(pos.x,pos.y,size.width,size.height),preTouchPoint))
	{
		FigureView * pFigureView = (FigureView *)this->getParent();
		if (pFigureView)
		{
			pFigureView->show2Stunts(false);
			setHighLight(ccp(0,0) , false);
			return false;
		}
	}

	SkillItem * pItem1 = (SkillItem *)this->getChildByTag(TAG_STUNTS);
	if (pItem1)
	{
		CCPoint pos1 = getScreenPos(pItem1);
		CCSize sizeItem = pItem1->getContentSize();
		if (CCRect::CCRectContainsPoint(CCRectMake(pos1.x-sizeItem.width/2,pos1.y-sizeItem.height/2,sizeItem.width,sizeItem.height),preTouchPoint))
		{
			setHighLight(pItem1->getPosition() , true);

			TipHelps * pTipHelp = (TipHelps *)pItem1->myTip;
			if (pTipHelp)
			{
				pTipHelp->rollOverHander();
			}
		}
	}

	SkillItem * pItem2 = (SkillItem *)this->getChildByTag(TAG_STUNTS+1);
	if (pItem2)
	{
		CCPoint pos2 = getScreenPos(pItem2);
		CCSize sizeItem = pItem2->getContentSize();
		if (CCRect::CCRectContainsPoint(CCRectMake(pos2.x-sizeItem.width/2,pos2.y-sizeItem.height/2,sizeItem.width,sizeItem.height),preTouchPoint))
		{
			setHighLight(pItem2->getPosition() , true);

			TipHelps * pTipHelp = (TipHelps *)pItem2->myTip;
			if (pTipHelp)
			{
				pTipHelp->rollOverHander();
			}
		}
	}

	return true;
}

void StuntsLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void StuntsLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void StuntsLayer::setHighLight(CCPoint pos ,bool bVar)
{
	CCSprite * pHightLight = (CCSprite *)this->getChildByTag(TAG_Skill_HightLight);
	if (!pHightLight)
	{
		pHightLight = new CCSprite();
		bool var = pHightLight->initWithSpriteFrameName("formation/formation_activated.png");
		if (var)
		{
			CCSize size = pHightLight->getContentSize();
			pHightLight->setTag(TAG_Skill_HightLight);
			pHightLight->setPosition(ccp(pos.x, pos.y));
			pHightLight->setIsVisible(bVar);
			this->addChild(pHightLight , 1);
			pHightLight->release();
		}		
	}
	else
	{
		CCSize size = pHightLight->getContentSize();
		pHightLight->setPosition(ccp(pos.x , pos.y ));
		pHightLight->setIsVisible(bVar);
	}	
}
