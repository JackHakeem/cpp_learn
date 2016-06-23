#include "SkillView.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "FigureCreate.h"
#include "model/skill/SkillManager.h"
#include "utils/ValuesUtil.h"
#include "SkillLayer.h"

SkillView::SkillView()
{
	_skillLayer = 0;
	_nCurTouchSkill =0;
	_tipLayer = 0;
	_nameText = 0;
	_desText = 0;
	_desTextEx = 0;
	_skillPopLayer = 0;
	_stateSkill = 0;
	_nameTextEx = 0;
	_nLen = 0;
	memset(SkillID,0,sizeof(SkillID));
	init();
}

bool SkillView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->key = PopEventName::SKILL;
	this->setIsTouchEnabled(true);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	SpriteNode* _skillContainer = new SpriteNode();
	_skillContainer->initWithSpriteFrameName("figure/figureSkillContainer.png");
	_skillContainer->setIsRelativeAnchorPoint(true);
	_skillContainer->setAnchorPoint(ccp(0,0));
	this->setPosition(ccp(winSize.width / 2.0f, winSize.height / 2.0f));
	//this->addSkillCellAndItem();
	this->setContentSize(_skillContainer->getTexture()->getContentSize());
	this->addChild(_skillContainer, RENDERZ_SkillContainer);
	if (!_skillLayer)
	{
		_skillLayer = new LayerNode();
		_skillLayer->setAnchorPoint(CCPointZero);
		_skillLayer->setIsRelativeAnchorPoint(true);
	}
	this->addChild(_skillLayer,RENDERZ_SkillContainer+1);
	m_viewSize = _skillContainer->getTexture()->getContentSize();//With the size of the background picture decide this VIEW size
	_skillContainer->release();
    return true;
}

void SkillView::moveBy(CCPoint pos)
{
// 	CCAction* m_action = CCSequence::actions(	CCMoveBy::actionWithDuration(0.5, pos),NULL);
// 	this->runAction(m_action);
}


void SkillView::addSkillCellAndItem()
{
	this->_skillLayer->removeAllChildrenWithCleanup(true);
	if (!g_pFigureScrollView)
	{
		return;
	}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	//int page = g_pFigureScrollView->_currentPage;
	//CCLayer * c = g_pFigureScrollView->getLayerByTag(page);
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	while (nCurScreen-1)
	{
		++iter;
		--nCurScreen;
	}
	if (iter != list->end())
	{
		char path[64];
		// grid1
		SpriteNode * cell = new SpriteNode();
		cell->initWithSpriteFrameName("pack/unlock.png");
		cell->setAnchorPoint(CCPointZero);
		cell->setIsRelativeAnchorPoint(true);
		cell->setPosition(ccp(12,257));
		this->_skillLayer->addChild(cell,RENDERZ_SkillContainer+2,11);
		//skill1
		int skill;
		memset(path,0,sizeof(path));
		SpriteNode * item = new SpriteNode();
		sprintf(path,"skill/122.png");
		if (!item->initWithSpriteFrameName(path))
		{
			return;
			CCLog("skill icon is not exist!");
			assert("skill icon is not exist!");
		}
		item->initWithFile(path);
		item->setAnchorPoint(CCPointZero);
		item->setIsRelativeAnchorPoint(true);
		cell->addChild(item,RENDERZ_SkillContainer+3,1);
		cell->setContentSize(item->getTexture()->getContentSize());
		_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM1").c_str(),CCSizeMake(120,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
		_nameTextEx->setPosition(ccp(10,10));
		_nameTextEx->setColor(ccc3(255,200,25));
		_nameTextEx->setAnchorPoint(CCPointZero);
		_nameTextEx->setIsRelativeAnchorPoint(true);
		cell->addChild(_nameTextEx,RENDERZ_SkillContainer+4,2);
		//_nameTextEx->release();
		item->release();
		cell->release();


		// grid2
		cell = new SpriteNode();
		cell->initWithSpriteFrameName("pack/unlock.png");
		cell->setAnchorPoint(CCPointZero);
		cell->setIsRelativeAnchorPoint(true);
		cell->setPosition(ccp(12,142));
		this->_skillLayer->addChild(cell,RENDERZ_SkillContainer+2,21);
		//skill2
//		skill = iter->second.playerBaseInfo.skill2;
		memset(path,0,sizeof(path));
		item = new SpriteNode();
		sprintf(path,"skill/122.png");//,skill
		item->initWithSpriteFrameName(path);
		item->setAnchorPoint(CCPointZero);
		item->setIsRelativeAnchorPoint(true);
		cell->addChild(item,RENDERZ_SkillContainer+3,1);
		cell->setContentSize(item->getTexture()->getContentSize());
		_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM2").c_str(),CCSizeMake(120,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
		_nameTextEx->setPosition(ccp(10,10));
		_nameTextEx->setColor(ccc3(255,200,25));
		_nameTextEx->setAnchorPoint(CCPointZero);
		_nameTextEx->setIsRelativeAnchorPoint(true);
		cell->addChild(_nameTextEx,RENDERZ_SkillContainer+4,2);
		//_nameTextEx->release();
		item->release();
		cell->release();

		// grid3
		cell = new SpriteNode();
		cell->initWithSpriteFrameName("pack/unlock.png");
		cell->setAnchorPoint(CCPointZero);
		cell->setIsRelativeAnchorPoint(true);
		cell->setPosition(ccp(12,26));
		this->_skillLayer->addChild(cell,RENDERZ_SkillContainer+2,31);
		//skill3
		skill = iter->second.playerBaseInfo.skill3;
		if (skill)
		{
			memset(path,0,sizeof(path));
			item = new SpriteNode();
			sprintf(path,"skill/122.png");
			item->initWithSpriteFrameName(path);
			item->setAnchorPoint(CCPointZero);
			item->setIsRelativeAnchorPoint(true);
			cell->addChild(item,RENDERZ_SkillContainer+3,1);
			cell->setContentSize(item->getTexture()->getContentSize());
			item->release();
		}
		_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM3").c_str(),CCSizeMake(120,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
		_nameTextEx->setPosition(ccp(10,10));
		_nameTextEx->setColor(ccc3(255,200,25));
		_nameTextEx->setAnchorPoint(CCPointZero);
		_nameTextEx->setIsRelativeAnchorPoint(true);
		cell->addChild(_nameTextEx,RENDERZ_SkillContainer+4,2);
		//_nameTextEx->release();
		cell->release();

	}
}

void SkillView::showSkillTips(int nCurTouchSkill)
{
	if (!_nCurTouchSkill)
	{
		return;
	}
	if (!g_pFigureScrollView)
	{
		return;
	}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	while (nCurScreen-1)
	{
		++iter;
		--nCurScreen;
	}
	if (!_tipLayer)
	{
		_tipLayer = new LayerNode();
		_tipLayer->setAnchorPoint(CCPointZero);
		_tipLayer->setIsRelativeAnchorPoint(true);
	}
	if (!this->_skillLayer->getChildByTag(44))
	{
		this->_skillLayer->addChild(_tipLayer,RENDERZ_SkillContainer+1,44);
	}
	_tipLayer->removeAllChildrenWithCleanup(true);
	if (iter != list->end())
	{
		std::string s("");
		switch (nCurTouchSkill)
		{
		case 1:
			s.clear();
			s = ValuesUtil::Instance()->getString("NAM11") + SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill1)->name;
			_nameText = CCLabelTTF::labelWithString(s.c_str(),CCSizeMake(160,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
			_desText = CCLabelTTF::labelWithString(SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill1)->des.c_str(),CCSizeMake(160,100),CCTextAlignmentLeft,g_sSimHeiFont,16);
			_desTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("DES1").c_str(),CCSizeMake(160,100),CCTextAlignmentLeft,g_sSimHeiFont,16);
			break;
		case 2:
			s.clear();
			s = ValuesUtil::Instance()->getString("NAM12") + SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill2)->name;
			_nameText = CCLabelTTF::labelWithString(s.c_str(),CCSizeMake(160,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
			_desText = CCLabelTTF::labelWithString(SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill2)->des.c_str(),CCSizeMake(160,100),CCTextAlignmentLeft,g_sSimHeiFont,16);
			break;
		case 3:
			if (!iter->second.playerBaseInfo.skill3)
			{
				return;
			}
			s.clear();
			s = ValuesUtil::Instance()->getString("NAM13") + SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill3)->name;
			_nameText = CCLabelTTF::labelWithString(s.c_str(),CCSizeMake(160,20),CCTextAlignmentCenter,g_sSimHeiFont,20);
			_desText = CCLabelTTF::labelWithString(SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill3)->des.c_str(),CCSizeMake(160,100),CCTextAlignmentLeft,g_sSimHeiFont,16);
			_desTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("DES2").c_str(),CCSizeMake(160,100),CCTextAlignmentLeft,g_sSimHeiFont,16);
			break;
		default:
			break;
		}
		_nameText->setColor(ccc3(240,240,240));
		_nameText->setAnchorPoint(CCPointZero);
		_nameText->setIsRelativeAnchorPoint(true);
		_nameText->setPosition(ccp(160,300));
		_tipLayer->addChild(_nameText,RENDERZ_SkillContainer+2,1);

		_desText->setColor(ccc3(12,233,25));
		_desText->setAnchorPoint(CCPointZero);
		_desText->setIsRelativeAnchorPoint(true);
		_desText->setPosition(ccp(140,200));
		_tipLayer->addChild(_desText,RENDERZ_SkillContainer+2,2);

		if (nCurTouchSkill!=2)
		{
			_desTextEx->setColor(ccc3(80,80,80));
			_desTextEx->setAnchorPoint(CCPointZero);
			_desTextEx->setIsRelativeAnchorPoint(true);
			_desTextEx->setPosition(ccp(160,30));
			_tipLayer->addChild(_desTextEx,RENDERZ_SkillContainer+2,3);
		}
		//_tipLayer->release();
	}
}

void SkillView::showSkillSelectPanel(int _state)
{
	if (!_state)
	{
		if (this->getChildByTag(51))
		{
			this->removeChildByTag(51,true);
		}
		return;
	}
	SpriteNode* _skillbg = new SpriteNode();
	_skillbg->initWithSpriteFrameName("figure/figureSkillContainer.png");
	_skillbg->setIsRelativeAnchorPoint(true);
	_skillbg->setAnchorPoint(CCPointZero);
	CCSize sz = _skillbg->getTexture()->getContentSize();
	CCSize wsz = CCDirector::sharedDirector()->getWinSize();
	if (!_skillPopLayer)
	{
		_skillPopLayer = new SkillLayer();
		if (!_skillPopLayer)
		{
			return;
		}
		_skillPopLayer->setAnchorPoint(CCPointZero);
		_skillPopLayer->setIsRelativeAnchorPoint(true);
		_skillPopLayer->setContentSize(sz);
		_skillPopLayer->setPosition(120,-80);
		_skillPopLayer->setIsTouchEnabled(true);
	}
	if (!this->getChildByTag(51))
	{
		this->addChild(_skillPopLayer,7,51);
	}
	if (!_skillPopLayer->getChildByTag(1))
	{
		_skillPopLayer->addChild(_skillbg,0,1);
	}
	if (!_skillPopLayer->getChildByTag(2))
	{
		_skillPopLayer->addSkillScrollView();
	}
	_skillPopLayer->loadSkillItems();
}

void SkillView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,1,true);
}

bool SkillView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setIsTouchEnabled(true);
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	CCLog("Skill:touch point(%f,%f)",preTouchPoint.x,preTouchPoint.y);
	CCSprite * cell = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
	CCSprite * skillbg = CCSprite::spriteWithSpriteFrameName("figure/figureSkillContainer.png");
	CCSize sz = cell->getTexture()->getContentSize();
	CCSize ssz = skillbg->getTexture()->getContentSize();
	if (!_skillLayer)
	{
		return false;
	}

	CCNode * s1 = _skillLayer->getChildByTag(11);
	CCNode * s2 = _skillLayer->getChildByTag(21);
	CCNode * s3 = _skillLayer->getChildByTag(31);
	if ((!s1)||(!s2)||(!s3))
	{
		return false;
	}
	CCPoint c1 = getScreenPos(s1);
	CCPoint c2 = getScreenPos(s2);
	CCPoint c3 = getScreenPos(s3);
	CCRect rect1 = CCRect(c1.x,c1.y,sz.width,sz.height);
	CCRect rect2 = CCRect(c2.x,c2.y,sz.width,sz.height);
	CCRect rect3 = CCRect(c3.x,c3.y,sz.width,sz.height);
	//CCRect rect4 = CCRect(0,130,ssz.width,ssz.height);
	if (CCRect::CCRectContainsPoint(rect1,preTouchPoint))
	{
		_nCurTouchSkill = 1;
		return true;
	}
	else if (CCRect::CCRectContainsPoint(rect2,preTouchPoint))
	{
		_nCurTouchSkill = 2;
		return true;
	}
	else if (CCRect::CCRectContainsPoint(rect3,preTouchPoint))
	{
		_nCurTouchSkill = 3;
		return true;
	}
	// 	if (1 == _stateSkill)
	// 	{
	// 		if (!CCRect::CCRectContainsPoint(rect4,preTouchPoint))
	// 		{
	// 			_stateSkill = 0;
	// 			showSkillSelectPanel(_stateSkill);
	// 		}
	// 	}
	return false;	
}

void SkillView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!_nCurTouchSkill)
	{
		return;
	}
	showSkillTips(_nCurTouchSkill);
	if (3 == _nCurTouchSkill)
	{
		_stateSkill = (0 == _stateSkill) ? 1:0;
		showSkillSelectPanel(_stateSkill);
	}
}