#include "SkillItem.h"
#include "model/player/RoleManage.h"
#include "utils/TipHelps.h"
#include "model/skill/SkillTipsTool.h"
#include "model/skill/SkillManager.h"

#include "SkillView.h"
#include "manager/ViewManager.h"
#include "control/figure/FigureCommand.h"
#include "model/skill/vo/SkillType.h"
#include "SkillItem.h"
#include "utils/TipHelps.h"
#include "manager/LayerManager.h"
#include "model/skill/SkillProxy.h"


SkillItem::SkillItem()
{
	_myInfo = NULL;
	_mySitNum = 0;
	myTip = 0;
	_posIndex = 0;
}

SkillItem::~SkillItem()
{
	CC_SAFE_DELETE( myTip );

	CC_SAFE_DELETE( _myInfo );
}

bool SkillItem::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
    return true;
}

SkillItem::SkillItem(int sitNum, UpGradeInfo* info, int style)
{
	init(); // LH0712
	myTip = 0;
	_posIndex = 0;


	bool isAOYI = false;
	SkillVo * _skillvo= 0;
	UpGradeInfo* upInfo = 0;
	//std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> > * _levskilldic = &SkillManager::Instance()->_levSkillDic;
	//std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> >::iterator iter = _levskilldic->find(info->id);
	std::map<int/*skillId*/, SkillVo > * _skilldic = &SkillManager::Instance()->_skillDic;
	std::map<int/*skillId*/, SkillVo >::iterator iter = _skilldic->find(info->id);
	if (iter == _skilldic->end())
	{
		SkillProxy* pSkillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
		if ( !pSkillProxy ) 	
			return;

		upInfo = pSkillProxy->getUpGradeInfo( info->id, info->rank );
		if (upInfo)
		{
			isAOYI = true;
		}
		//else
		//	return;	
	}
	else
	{
		_skillvo = &iter->second;
	}


	_mySitNum = sitNum;
	float width = 0.0f;
	float height = 0.0f;

	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);


	if(info->id != 0 )
	{
		// grid
		SpriteNode * cell = new SpriteNode();
		if (cell && cell->initWithSpriteFrameName("pack/unlock.png"))
		{
			cell->setAnchorPoint(CCPointZero);
			cell->setIsRelativeAnchorPoint(true);
			width = cell->getContentSize().width;
			height = cell->getContentSize().height;
			this->addChild(cell, RENDERZ_skill);
			//this->setContentSize(cell->getTexture()->getContentSize());
			cell->release();

			this->setContentSize(cell->getContentSize());
		}

		// skill icon
		char path[64];
		SpriteNode * skill = new SpriteNode();
		//sprintf(path,"skill/%d.png",info->id);
		//if (skill && skill->initWithSpriteFrameName(path))

		//LH20130110
		sprintf(path,"assets/icon/skill/%d.png",info->id);
		if (skill && skill->initWithFile(path))
		{
			skill->setAnchorPoint(ccp(0.5,0.5));
			skill->setIsRelativeAnchorPoint(true);
			skill->setPosition(ccp(width/2,height/2));
			width = skill->getContentSize().width;
//			height = skill->getTexture()->getContentSize().height;
			skill->setScale((float)cell->getContentSize().width/width-0.1);
			this->addChild(skill, RENDERZ_skill);
			skill->release();
		}
	}

	//ÉèÖÃTIPS

	_myInfo = new UpGradeInfo();

	*_myInfo = *info;

	std::string szName1("");
	if (upInfo)	{szName1 = upInfo->name;}
	std::string szName2("");
	if (SkillManager::Instance()->getSkill(info->id))	{szName2 = SkillManager::Instance()->getSkill(info->id)->name;}
	_myInfo->name = isAOYI?szName1:szName2;
	std::string szDes1("");
	if (upInfo)	{szDes1 = upInfo->desc;}	
	std::string szDes2 = _skillvo ? _skillvo->des : szDes1;
	_myInfo->desc = isAOYI?szDes1:szDes2;

	int nRank = SkillManager::Instance()->getSkill(info->id) ? SkillManager::Instance()->getSkill(info->id)->rank : 0;
	_myInfo->rank = isAOYI?info->rank:nRank;
	_myInfo->lev = info->lev;
	int nLev = _skillvo ? _skillvo->level : 0;
	_myInfo->needLevel = isAOYI?0:nLev;
	_myInfo->subTips = SkillTipsTool::getSkillTips(_myInfo, style, 0);

	if (!myTip)
	{
		myTip = new TipHelps();
	}
	myTip->init(false, 0, true/*TipConst::BACKPACK*/);
	myTip->setToolTips(this, this);
	//

	CC_SAFE_DELETE(upInfo); // ADD BY L.H. LEAK
}

void SkillItem::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
}

bool SkillItem::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	AccountInfoVo* acc = RoleManage::Instance()->accountInfo();
	if(acc == NULL)
		return true;

	if(_mySitNum == 1&& acc->crystalLev()<30)
	{
		return true;
	}
	else
	{
		//SHOW_SKILL_PANEL, _mySitNum;
	}
	return true;
}

void SkillItem::updateInfo(UpGradeInfo* info)
{
	clear();

	if(info)
	{
		_myInfo = info;
	}
	else
	{
		_myInfo = new UpGradeInfo();
	}

	if(_myInfo->id != 0)
	{
		SpriteNode* skill = new SpriteNode();
		//char buf[] = "assets/icon/skills/%d.png";
		char buf[] = "pack/unlock.png";
		char path[64];
		//sprintf(path, buf, info->id);
		sprintf(path, buf, 622);
		skill->initWithSpriteFrameName(path);
		//float width = skill->getTexture()->getContentSize().width;
		//float height = skill->getTexture()->getContentSize().height;

		this->addChild(skill);
		this->setContentSize(skill->getTexture()->getContentSize());
		skill->release();
	}
}

void SkillItem::clear()
{
	removeAllChildrenWithCleanup(true);
	if(_myInfo)
		delete _myInfo;
}

void SkillItem::handleEquip(CCObject* pSender)
{
	FigureCommand * fc = (FigureCommand *)g_pFacade->retrieveController(AppFacade_FIGURE_COMMAND);
	if (fc)
	{
		int merID = 0,skillID = 0,account = 0;
					


		merID = ViewManager::getInstance()->figureView->_figureV->RoleID[g_pFigureScrollView->currentScreen-1];

		if (_myInfo->rank == SkillType::PASSVIE)
		{
			skillID = ViewManager::getInstance()->figureView->_figureV->SkillID[_posIndex];
		}
		else if (_myInfo->rank == SkillType::SKILL)
		{
			skillID = _myInfo->id;
		}

		//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
		//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
		std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
		std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
		bool bExist(false);
		for (;iter != list->end();iter++)
		{
			if (merID == iter->second.figureBaseInfo.mercId)
			{
				account = iter->first.id;
				bExist = true;
				break;
			}
		}
		if (!bExist)
		{
			return;
		}
		
		if ((_myInfo->rank == SkillType::PASSVIE) && (iter->second.playerBaseInfo.skill3 != skillID))
		{
			fc->sendChangeSkillRequest(account,SkillType::PASSVIE,skillID);
		}
		if ((_myInfo->rank == SkillType::SKILL) && (iter->second.playerBaseInfo.skill2 != skillID))
		{
			fc->sendChangeSkillRequest(account,SkillType::SKILL,skillID);
		}
	}
	if (ViewManager::getInstance()->figureView && ViewManager::getInstance()->figureView->_figureV)
	{
		ViewManager::getInstance()->figureView->_figureV->showSkillSelectPanel(0);
		ViewManager::getInstance()->figureView->_figureV->show2Stunts(false);
	}

	//
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}