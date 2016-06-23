#include "InfoPanel.h"
#include "events/GameDispatcher.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "ArenaUI.h"
#include "socket/command/s36/SCMD361.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

const float FontSize = 26.0f;
const float FontSize_2 = 20.0f;
const float FontSize_3 = 21.0f;
//ValuesUtil::Instance()->getString("BB005").c_str()
InfoPanel::InfoPanel()
{
	_roleManage = RoleManage::Instance();
	_dispatcher = GameDispatcher::getInstance();
	_pContainer = 0;
	_accountInfo = _roleManage->accountInfo();

}

InfoPanel::~InfoPanel()
{}

bool InfoPanel::initWithParam(ArenaUI* pContainer)
{
	if (!LayerNode::init())
		return false;
	_pContainer = pContainer;

	_accountInfo->addEventListener(AccountInfoVo::CHANGE_POPULARITY, this, 0);
	//ValuesUtil::Instance()->getString("BB010")

	//³ÆºÅ
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_title_title);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC001").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-200-40*0)));
			this->addChild(pLabel, InfoPanelZ_title_title, InfoPanelTAG_title_title);
			pLabel->setColor(ccc3(55, 21, 0));		
		}
	}
	//ÃûÉù
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_Renown_title);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC002").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-200-40*1)));
			this->addChild(pLabel, InfoPanelZ_Renown_title, InfoPanelTAG_Renown_title);
			pLabel->setColor(ccc3(55, 21, 0));
		}
	}
	//ÅÅÃû
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_rank_title);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC003").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-200-40*2)));
			this->addChild(pLabel, InfoPanelZ_rank_title, InfoPanelTAG_rank_title);
			pLabel->setColor(ccc3(55, 21, 0));
		}
	}
	//Á¬Ê¤
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_Straight_title);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC004").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-200-40*3)));
			this->addChild(pLabel, InfoPanelZ_Straight_title, InfoPanelTAG_Straight_title);
			pLabel->setColor(ccc3(55, 21, 0));
		}
	}

	//²é¿´Ó¢ÐÛ°ñ
	CCSprite *pHeroNormalSprite = CCSprite::spriteWithSpriteFrameName("arena/4.png");
	CCSprite *pHeroPressedSprite = CCSprite::spriteWithSpriteFrameName("arena/btn_rank_pressed.png");
	CCMenuItemSprite *_btnHeroRank = CCMenuItemSprite::itemFromNormalSprite(
		pHeroNormalSprite,
		pHeroPressedSprite,
		this, 
		menu_selector(InfoPanel::clickHeroRank) );
	_btnHeroRank->setPosition(ccp(POSX(175), POSX(640-375)));

	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnHeroRank, 0); 
    buttonMenu->setPosition( CCPointZero );
	buttonMenu->setTouchLayer(TLE::WindowLayer_Arena);
	this->addChild(buttonMenu, InfoPanelZ_HeroRankBtn, InfoPanelTAG_HeroRankBtn);

	CCLabelTTF* pHeroRankLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC005").c_str(), CCSizeMake(POSX(200), POSX(FontSize_2)), CCTextAlignmentCenter, "Arial", POSX(FontSize_2));
	pHeroRankLabel->setPosition(ccp(_btnHeroRank->getContentSize().width/2, _btnHeroRank->getContentSize().height/2));
	_btnHeroRank->addChild(pHeroRankLabel,0 ,1);
	pHeroRankLabel->setColor(ccc3(55, 21, 0));		

	return true;
}


void InfoPanel::update(SCMD361* data)
{
	//name
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_name);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(165), POSX(640-132)));
			this->addChild(pLabel, InfoPanelZ_name, InfoPanelTAG_name);
			pLabel->setColor(ccc3(55, 21, 0));		
		}
		pLabel->setString(_accountInfo->name.c_str());
	}
	//Rank13927283276
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_rank);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(160), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(250), POSX(640-200-40*2)));
			this->addChild(pLabel, InfoPanelZ_rank, InfoPanelTAG_rank);
			pLabel->setColor(ccc3(254, 189, 0));		
		}
		char dst[50];
		sprintf(dst, "%d", data->c_maxRank+1);
		pLabel->setString(dst);
	}
	// Á¬Ê¤¼ÇÂ¼
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_Straight);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(160), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(200), POSX(640-200-40*3)));
			this->addChild(pLabel, InfoPanelZ_Straight, InfoPanelTAG_Straight);
			pLabel->setColor(ccc3(254, 189, 0));		
		}
		char dst[50];
		sprintf(dst, "%d", data->d_winstreak);
		pLabel->setString(dst);
	}

	/*// ³ÆºÅ
	var honorTitle:String = HonorManage.getInstance().honorTitle(_accountInfo.honorTitleId);
 	var repvo:ReputationVo = ReputationManage.getInstance().getCurrentData(_accountInfo.popularity);
			
	if(repvo!=null){
		_txtTitle.htmlText = repvo.repName;
		_btnReputation.visible = true;
	}
	else{
//				_txtTitle.htmlText = "<font color='#ffffff'>Î´»ñµÃ³ÆºÅ</font>";	
		_txtTitle.htmlText = "<font color='#ffffff'>" + LangManager.getText("ARN059") +  "</font>";	
		_btnReputation.visible = false;
	}
	*/
	// ³ÆºÅ
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_title);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(160), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(200), POSX(640-200-40*0)));
			this->addChild(pLabel, InfoPanelZ_title, InfoPanelTAG_title);
			pLabel->setColor(ccc3(254, 189, 0));		
		}
		char dst[50];
		sprintf(dst, "%s", ValuesUtil::Instance()->getString("JJC006").c_str());
		pLabel->setString(dst);		
	}

	// ÃûÉù
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(InfoPanelTAG_Renown);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(160), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(200), POSX(640-200-40*1)));
			this->addChild(pLabel, InfoPanelZ_Renown, InfoPanelTAG_Renown);
			pLabel->setColor(ccc3(254, 189, 0));		
		}
		char dst[50];
		sprintf(dst, "%d", _accountInfo->popularity());
		pLabel->setString(dst);		
	}
}

void InfoPanel::clickHeroRank(CCObject* pSender)
{
	_dispatcher->dispatchEvent(GameDispatcher::SHOW_HERO_RANK, 0);
}