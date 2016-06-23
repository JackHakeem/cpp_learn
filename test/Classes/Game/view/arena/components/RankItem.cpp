#include "RankItem.h"
#include "model/player/FigureBaseManage.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "ArenaUI.h"
#include "manager/LangManager.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"
#include "model/newhand/vo/NewhandConst.h"

const float FontSize = 18.0f;
const float FontSize_1 = 20.0f;

RankItem::RankItem()
{
	_pContainer = 0;
	_figureBaseManage = 0;
}

RankItem::~RankItem()
{}

bool RankItem::initWithParam(ArenaUI* pContainer, SCMD361Node& data)
{
	_pContainer = pContainer;
	_data = data;
	_figureBaseManage = FigureBaseManage::Instance();
	/*
	this._cdManage = CDManage.getInstance();

	*/
	//haswin
	if (_data.f_win)
	{
		SpriteNode* pHaswin = new SpriteNode();
		pHaswin->initWithSpriteFrameName("arena/haswin_icon.png");
		this->addChild(pHaswin, RankItemZ_haswin, RankItemTAG_haswin);
		pHaswin->release();	
	}

	//head
	FigureCfgBaseVo* figureBaseVo = _figureBaseManage->getMercBase(_data.e_mercid);


	char headPath[100];
	//sprintf(headPath, "head/%d.png", figureBaseVo->cloth);
	sprintf(headPath, "assets/icon/head/%d.png", figureBaseVo->cloth);

	CCSprite* p1 = CCSprite::spriteWithFile(headPath);
	CCSprite* p2 = CCSprite::spriteWithFile(headPath);
	CCMenuItemSprite *_btnHead = CCMenuItemImage::itemFromNormalSprite(
		p1, p2, this, 
		menu_selector(RankItem::clickHandler) );
	_btnHead->setPosition(ccp(POSX(0), POSX(0)));

	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
    buttonMenu->setPosition( CCPointZero );
	buttonMenu->setTouchLayer(TLE::WindowLayer_Arena);
	buttonMenu->addChild(_btnHead, 0, 0);
	this->addChild(buttonMenu, RankItemZ_head, RankItemTAG_head);

	buttonMenu->release(); // LH0715

	//head_bg
	CCPoint head_bg_size = ccp(_btnHead->getContentSize().width+POSX(8), _btnHead->getContentSize().height+POSX(8));
	CCUIBackground* _head_bg = new CCUIBackground();
	_head_bg->initWithSpriteFrame("ui3.png", ccp(-head_bg_size.x/2, -head_bg_size.y/2), ccp(POSX(6),POSX(7)), CCSizeMake(head_bg_size.x, head_bg_size.y));
	this->addChild(_head_bg, RankItemZ_head_bg, RankItemTAG_head_bg);
	//Doyang 20120712
	_head_bg->release();

	//name
	CCLabelTTF* pLabelName = CCLabelTTF::labelWithString(_data.c_name.c_str(), CCSizeMake(POSX(200), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabelName->setPosition(ccp(0, POSX(-50)));
	this->addChild(pLabelName, RankItemZ_name, RankItemTAG_name);
	pLabelName->setColor(ccc3(255, 0, 0));	
	//lv
	char strLv[20];
	sprintf(strLv, "%s %d", ValuesUtil::Instance()->getString("JJC007").c_str(),_data.d_level);
	CCLabelTTF* pLabelLv = CCLabelTTF::labelWithString(strLv, CCSizeMake(POSX(200), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabelLv->setPosition(ccp(0, POSX(-70)));
	this->addChild(pLabelLv, RankItemZ_lv, RankItemTAG_lv);
	pLabelLv->setColor(ccc3(55, 21, 0));
	//rank_pic
	SpriteNode* rank_pic = new SpriteNode();
	rank_pic->initWithSpriteFrameName("arena/15.png");
	rank_pic->setPosition(ccp(0, _btnHead->getContentSize().height - POSX(16)));
	rank_pic->setScaleY(0.9f);
	this->addChild(rank_pic, RankItemZ_rank_pic, RankItemTAG_rank_pic);

	rank_pic->release(); // LH0715

	//rank
	char strRank[20];
	sprintf(strRank, "%d", _data.a_rank+1);
	CCLabelTTF* pLabelRank = CCLabelTTF::labelWithString(strRank, CCSizeMake(POSX(200), POSX(FontSize_1)),CCTextAlignmentCenter, "Arial", POSX(FontSize_1));
	pLabelRank->setPosition(ccp(0, _btnHead->getContentSize().height - POSX(15)));
	this->addChild(pLabelRank, RankItemZ_rank, RankItemTAG_rank);
	pLabelRank->setColor(ccc3(255, 255, 255));

	return true;
}

void RankItem::clickHandler(CCObject* pSender)
{
	// new hand
	//if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Arena) == NewhandManager::Flag_New)
	{
		//NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Arena , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(206);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_ARENA_OVER);
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Arena , NewhandManager::Flag_Close);
	}

	CCLog("RankItem::clickHandler....%d", ((CCNode*)pSender)->getTag());
	if (this->_data.f_win)
	{
		LangManager::msgShow("JJC047");
		return;
	}

	if (_pContainer->_meRank == _data.a_rank)
	{
		LangManager::msgShow("JJC039");
		return;
	}

	if (_pContainer->_cdlock == 1)
	{
		LangManager::msgShow("JJC040");
		return;
	}

	if (_pContainer->_quota <= 0)
	{
		LangManager::msgShow("JJC041");
		return;		
	}

	_pContainer->pkArena(_data.a_rank);

}

