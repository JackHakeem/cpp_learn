#include "FightEnd.h"
#include "BaseType.h"
#include "CCUIBackground.h"
#include "model/player/RoleManage.h"
#include "utils/ValuesUtil.h"
#include "../../layer/FightLayer.h"
#include "model/battle/FightProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/battle/SceneFightMediator.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/sound/SoundManager.h"

USING_NS_CC;
const int TAG_PARENT = 1001;

#define FLOAT_EXP_LABEL_SIZE POSX(18)
#define FLOAT_NAME_LABEL_SIZE POSX(24)
#define FLOAT_RESULT_LABEL_SIZE POSX(20)
#define FLOAT_PRACTICE_LABEL_SIZE POSX(20)
#define FLOAT_SCORE_LABEL_SIZE POSX(20)
#define FLOAT_START_WIDTH POSX(62)

#define CCSIZE_LAYER CCSizeMake(POSX(600), POSX(430))
#define CCSIZE_PANEL_1 CCSizeMake(POSX(600), POSX(390))
#define CCSIZE_PANEL_2 CCSizeMake(POSX(560), POSX(296))
#define CCSIZE_EXP_LAYER CCSizeMake(POSX(550), POSX(170))
#define CCSIZE_EXP_LAYER_CELL CCSizeMake(POSX(110), POSX(170))
#define CCSIZE_EXP_LAYER_CELL_NAME CCSizeMake(POSX(130), FLOAT_NAME_LABEL_SIZE)
#define CCSIZE_EXP_LAYER_CELL_EXP CCSizeMake(POSX(110), FLOAT_EXP_LABEL_SIZE)

#define CCPOINT_PANEL_1 CCPointZero
#define CCPOINT_PANEL_2 ccp(POSX(20), POSX(70))
#define CCPOINT_COPY_REPORT_BTN ccp(POSX(24), POSX(14))
#define CCPOINT_REPLAY_BTN ccp(POSX(90), POSX(14))
#define CCPOINT_OK_BTN ccp(POSX(250), POSX(14))
#define CCPOINT_OK_BTN_LABEL ccp(CCPOINT_OK_BTN.x + POSX(10), CCPOINT_OK_BTN.y + POSX(10))
#define CCPOINT_SCORE_LABEL ccp(POSX(30), POSX(120))
#define CCPOINT_START_1 ccp(POSX(120), POSX(100))
#define CCPOINT_PRACTICE_WORD ccp(POSX(310), POSX(120))
#define CCPOINT_PRACTICE_REWARD ccp(POSX(360), POSX(120))
#define CCPOINT_GOOD_REWARD ccp(POSX(472), POSX(80))
#define CCPOINT_EXP_LAYER ccp(POSX(30), POSX(188))
#define CCPOINT_EXP_LAYER_CELL_EXP CCPointZero
#define CCPOINT_EXP_LAYER_CELL_NAME ccp(-10, POSX(28))
#define CCPOINT_EXP_LAYER_CELL_ICON ccp(POSX(4), POSX(58))
#define CCPOINT_RESULT_LABEL ccp(POSX(310), POSX(408))

#define SCALE_BTN_SMALL 0.48

#define CHAR_FONT_NAME "Arial"

FightEnd::FightEnd( int result, SCMD13D *pReward, SCMD3B1 *pReport, int style )
{
	_pReward = 0;
	_pReport = 0;
	_goodId = 0;
	_goodNum = 0;
	_result = result;
	_style = style;
	_pReward = pReward;
	_pReport = pReport;

}

FightEnd::~FightEnd()
{
	//CC_SAFE_DELETE(_pReward);// LH0708LEAK
	//CC_SAFE_DELETE(_pReport);// LH0708LEAK
}

bool FightEnd::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/fight/res_fight.plist");

	CCLayer *pFightResultLayer = new CCLayer();
	if(!pFightResultLayer ||
		!pFightResultLayer->init())
	{ 
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	pFightResultLayer->setContentSize(CCSIZE_LAYER);
	pFightResultLayer->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	pFightResultLayer->setIsRelativeAnchorPoint(true);
	this->addChild(pFightResultLayer, 0, TAG_PARENT);
	pFightResultLayer->release();//jae 20130123

	// Panel 1 background.
	CCUIBackground *pPanel1 = new CCUIBackground();
	pPanel1->initWithSpriteFrame("ui.png", CCPointZero, ccp(POSX(6), POSX(7)), CCSIZE_PANEL_1);
	pPanel1->setAnchorPoint(CCPointZero);
	pPanel1->setPosition(CCPOINT_PANEL_1);
	pFightResultLayer->addChild(pPanel1);
	pPanel1->release();

	// Panel 2 background.
	CCUIBackground *pPanel2 = new CCUIBackground();
	pPanel2->initWithSpriteFrame("ui2.png", CCPointZero, CCPointZero, CCSIZE_PANEL_2);
	pPanel2->setAnchorPoint(CCPointZero);
	pPanel2->setPosition(CCPOINT_PANEL_2);
	pFightResultLayer->addChild(pPanel2);
	pPanel2->release();
	
	CCLayer *pExpLayer = this->createExpLayer();
	if(pExpLayer)
	{
		pFightResultLayer->addChild(pExpLayer);
		pExpLayer->release();//jae 20130123
	}

	// Add score
	CCLabelTTF *pScoreLabel = CCLabelTTF::labelWithString(
		pValueUtil->getString("fi_score").c_str(),
		CCSizeMake(FLOAT_SCORE_LABEL_SIZE * 4, FLOAT_SCORE_LABEL_SIZE), 
		CCTextAlignmentLeft, 
		CHAR_FONT_NAME,
		FLOAT_SCORE_LABEL_SIZE);
	if(pScoreLabel)
	{
		pScoreLabel->setPosition(CCPOINT_SCORE_LABEL);
		pScoreLabel->setAnchorPoint(CCPointZero);
		pFightResultLayer->addChild(pScoreLabel);
	}

	// Add stars and config result word.
	//char *pResultChar;
    std::string pResultChar;
	int startCount = 0;
	if(_result>=80)
	{
		pResultChar = "fight/win_1.png";
		startCount = 3;
	}
	else if(_result>=60)
	{
		pResultChar = "fight/win_2.png";
		startCount = 2;
	}
	else if(_result>=40)
	{
		pResultChar = "fight/win_3.png";
		startCount = 2;
	}
	else if(_result>=20)
	{
		pResultChar = "fight/win_4.png";
		startCount = 1;
	}
	else if(_result>=0)
	{
		pResultChar = "fight/win_5.png";
		startCount = 1;
	}
	else if(_result<=-80)
	{
		pResultChar = "fight/lose_5.png";
		startCount = 0;
	}
	else if(_result<=-60)
	{
		pResultChar = "fight/lose_4.png";
		startCount = 0;
	}
	else if(_result<=-40)
	{
		pResultChar = "fight/lose_3.png";
		startCount = 0;
	}
	else if(_result<=-20)
	{
		pResultChar = "fight/lose_2.png";
		startCount = 0;
	}
	else if(_result<0)
	{
		pResultChar = "fight/lose_1.png";
		startCount = 0;
	}
	
	// Add starts.
	CCPoint startPoint = CCPOINT_START_1;
	for(int i=0; i<3; ++i)
	{
        std::string pStartChar;
		if(i < startCount)
		{
			pStartChar = "fight/start_bright.png";
		}
		else
		{
			pStartChar = "fight/start_dark.png";
		}
		CCSprite *pStartSprite = CCSprite::spriteWithSpriteFrameName(pStartChar.c_str());
		if(pStartSprite)
		{
			pStartSprite->setAnchorPoint(CCPointZero);
			pStartSprite->setPosition(startPoint);
			pFightResultLayer->addChild(pStartSprite);
		}
		startPoint.x += FLOAT_START_WIDTH;
	}

	// Add fight result.
	CCSprite *pResultWordSprite = CCSprite::spriteWithSpriteFrameName(pResultChar.c_str());
	if(pResultWordSprite)
	{
		pResultWordSprite->setAnchorPoint(ccp(0.5, 0.5));
		pResultWordSprite->setPosition(CCPOINT_RESULT_LABEL);
		pFightResultLayer->addChild(pResultWordSprite);
	}

	// Add rewards.
	CCLabelTTF *pPraticeLabel = this->buildRewards();
	if(pPraticeLabel)
	{
		CCLabelTTF *pPracticeWordLabel = CCLabelTTF::labelWithString(
			pValueUtil->getString("get").c_str(),
			CCSizeMake(FLOAT_PRACTICE_LABEL_SIZE * 2, FLOAT_PRACTICE_LABEL_SIZE),
			CCTextAlignmentLeft,
			CHAR_FONT_NAME,
			FLOAT_PRACTICE_LABEL_SIZE);
		if(pPracticeWordLabel)
		{
			pPracticeWordLabel->setAnchorPoint(CCPointZero);
			pPracticeWordLabel->setPosition(CCPOINT_PRACTICE_WORD);
			pPracticeWordLabel->setColor(ccc3(255, 255, 255));
			pFightResultLayer->addChild(pPracticeWordLabel);
		}
		pFightResultLayer->addChild(pPraticeLabel);
	}
	else
	{
		// Nothing happend.
	}

	// Add rewards good.
	if(_goodId != 0)
	{
		CCSprite *pGoodSprite = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
		pGoodSprite->setAnchorPoint(CCPointZero);
		pGoodSprite->setPosition(CCPOINT_GOOD_REWARD);

		char pGoodIcon[30];
		sprintf(pGoodIcon, "assets/icon/goods/%d.png", _goodId);
		CCSprite *pGoodIconSprite = CCSprite::spriteWithFile(pGoodIcon);
		if(pGoodIconSprite)
		{
			pGoodIconSprite->setAnchorPoint(CCPointZero);
			pGoodIconSprite->setPosition(ccp(POSX(4), POSX(4)));
			pGoodSprite->addChild(pGoodIconSprite);
		}
		pFightResultLayer->addChild(pGoodSprite);
	}
	else
	{
		CCSprite *pGoodSprite = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
		pGoodSprite->setAnchorPoint(CCPointZero);
		pGoodSprite->setPosition(CCPOINT_GOOD_REWARD);
		pFightResultLayer->addChild(pGoodSprite);
	}

	// Add buttons.
	// Add report button.
	// Add close button.
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pCloseMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(FightEnd::closePanel));
			pCloseMenuItem->setAnchorPoint(CCPointZero);
			pCloseMenuItem->setPosition(CCPOINT_OK_BTN);
			CCLabelTTF *pOKLabel = CCLabelTTF::labelWithString(
				pValueUtil->getString("CF001").c_str(),
				pCloseMenuItem->getContentSize(),
				CCTextAlignmentCenter,
				CHAR_FONT_NAME,
				FLOAT_NAME_LABEL_SIZE);
			pOKLabel->setAnchorPoint(CCPointZero);
			pOKLabel->setPosition(CCPointZero);
			pCloseMenuItem->addChild(pOKLabel);
			CCMenu* pCloseMenu = CCMenu::menuWithItems(pCloseMenuItem, NULL);
			pCloseMenu->setPosition(CCPointZero);
			pCloseMenu->setTouchLayer(TLE::FightLayer-10);
			pFightResultLayer->addChild(pCloseMenu);
		}
		
	}

    
    //Doyang 20120811
    if(_result < 5)
    {
		std::string strContent("");
		int nLevel = RoleManage::Instance()->roleLev();
		if (_result < 5)
		{
			if (nLevel <= 15)
			{
				strContent = pValueUtil->getString("FT020");
			}
			else if (nLevel <= 20)
			{
				strContent = pValueUtil->getString("FT021");
			}
			else if (nLevel <= 25)
			{
				strContent = pValueUtil->getString("FT022");
			}
			else if(nLevel <= 30)
			{
				strContent = pValueUtil->getString("FT023");
			}
			else if(nLevel <= 35)
			{
				strContent = pValueUtil->getString("FT024");
			}
			else if(nLevel <= 39)
			{
				strContent = pValueUtil->getString("FT025");
			}
			else if(nLevel <= 44)
			{
				strContent = pValueUtil->getString("FT026");
			}
			else if(nLevel < 50)
			{
				strContent = pValueUtil->getString("FT027");
			}
			else
			{
				strContent = pValueUtil->getString("FT028");
			}
		}
		else
		{
			//strContent = pValueUtil->getString("FT028");
		}
		
		

		// 
        CCPoint labelPoint = ccpAdd(CCPOINT_EXP_LAYER, ccp(CCSIZE_EXP_LAYER.width / 2, CCSIZE_EXP_LAYER.height / 2));
        CCLabelTTF *pFailedLabel = CCLabelTTF::labelWithString(
                                                           strContent.c_str(),
                                                           CCSizeMake(FLOAT_NAME_LABEL_SIZE * 20, FLOAT_NAME_LABEL_SIZE*3),
                                                           CCTextAlignmentCenter,
                                                           CHAR_FONT_NAME,
                                                           FLOAT_NAME_LABEL_SIZE);
        pFailedLabel->setColor(ccc3(255, 255, 255));
        pFailedLabel->setPosition(ccp(labelPoint.x , labelPoint.y+POSX(20)));
        pFightResultLayer->addChild(pFailedLabel);

		// 
		/*
		CCLabelTTF *pSliverLabel = CCLabelTTF::labelWithString(
			pValueUtil->getString("FT010").c_str(),
			CCSizeMake(FLOAT_NAME_LABEL_SIZE * 20, FLOAT_NAME_LABEL_SIZE*2.2),
			CCTextAlignmentCenter,
			CHAR_FONT_NAME,
			FLOAT_NAME_LABEL_SIZE);
		pSliverLabel->setColor(ccc3(255, 255, 255));
		pSliverLabel->setPosition(ccp(labelPoint.x , labelPoint.y - POSX(30)));
		pFightResultLayer->addChild(pSliverLabel);
		*/
    }

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/fight/res_fight.plist");
	//if (CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/fight/res_fight.pvr.ccz"))//kevinshit
	//{
	//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/fight/res_fight.pvr.ccz");
	//}
	return true;
}

CCLayer * FightEnd::createExpLayer()
{
	CCLayer *pExpLayer = new CCLayer();
	if(!pExpLayer || !pExpLayer->init())
	{
		return NULL;
	}
	pExpLayer->setContentSize(CCSIZE_EXP_LAYER);
	pExpLayer->setAnchorPoint(CCPointZero);
	pExpLayer->setIsRelativeAnchorPoint(true);
	pExpLayer->setPosition(CCPOINT_EXP_LAYER);

	// Add cell layouts.
	CCPoint cellLayerPoint = CCPointZero;
	if(_pReward)
	{
		std::list<SCMD13D::SCMD13DNode2>::iterator expIt;
		std::list<SCMD13D::SCMD13DNode2> expList = _pReward->_exps;
		int i = 0;
		for(expIt = expList.begin(); expIt != expList.end(); ++ expIt)
		{
			SCMD13D::SCMD13DNode2 node = (SCMD13D::SCMD13DNode2) *expIt;
			CCLayer *cellLayer = this->createExpLayerCell(cellLayerPoint, node);
			if(cellLayer != NULL)
			{
				pExpLayer->addChild(cellLayer); 
				cellLayer->release();
			}
			cellLayerPoint.x += CCSIZE_EXP_LAYER_CELL.width;
			i ++;
		}
	}
	else
	{
		/*SCMD13D::SCMD13DNode2 node;
		node._id = -1;
		for(int i=0; i<5; ++i)
		{
			CCLayer *cellLayer = this->createExpLayerCell(cellLayerPoint, node);
			if(cellLayer != NULL)
			{
				pExpLayer->addChild(cellLayer); 
			}
			cellLayerPoint.x += CCSIZE_EXP_LAYER_CELL.width;
		}*/
	}

	return pExpLayer;
}

CCLayer * FightEnd::createExpLayerCell(CCPoint  point, SCMD13D::SCMD13DNode2 node )
{
	CCLayer *pCellLayer = new CCLayer();
	if(!pCellLayer || !pCellLayer->init())
	{
		return NULL;
	}
	pCellLayer->setPosition(point);
	pCellLayer->setAnchorPoint(CCPointZero);
	
	PlayerInfoVo *pPlayerInfo = RoleManage::Instance()->getMercenary(node._id);

	CCSprite *pIconSpriteFrame = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
	if(pIconSpriteFrame)
	{
		pIconSpriteFrame->setAnchorPoint(CCPointZero);
		pIconSpriteFrame->setPosition(CCPOINT_EXP_LAYER_CELL_ICON);
		pCellLayer->addChild(pIconSpriteFrame);
	}

	if(pPlayerInfo)
	{
		// Add head icon.
		char path[64];
		sprintf(path,"assets/icon/head/%d.png",pPlayerInfo->playerBaseInfo.cloth);		
		CCSprite *pIconSprite = CCSprite::spriteWithFile(path);
		if(pIconSprite)
		{
			//pIconSprite->setAnchorPoint(CCPointZero);
			pIconSprite->setScale((float)pIconSpriteFrame->getContentSize().width/pIconSprite->getContentSize().width);
			pIconSprite->setPosition(ccp(pIconSpriteFrame->getContentSize().width/2,
				pIconSpriteFrame->getContentSize().height/2));
			pIconSpriteFrame->addChild(pIconSprite);
		}

        std::string nameStr = pPlayerInfo->playerBaseInfo.name.c_str();
//        int cnt = 0;
//        if (isLenOverflow(nameStr, 5, cnt))
//        {
//            nameStr = nameStr.substr(0, cnt);
//            nameStr.append("...");
//        }
        int length = nameStr.length();
        int splitCount = 5;
        int cnt = 0;
        for(int i=0; i<length; ++i)
        {
            if(splitCount == 0 || cnt >= length)
            {
                break;
            }
            char c = nameStr[i];
            if(c >=0 && c <= 127)
            {
                cnt ++;
            }
            else
            {
                i ++;
                cnt += 2;
            }
            splitCount --;
        }
        /*nameStr = nameStr.substr(0, cnt);
        if( cnt < length)
        {
            nameStr.append("...");
        }*/
        
        
		// Add name.
		CCLabelTTF *pNameLabel = CCLabelTTF::labelWithString(
			nameStr.c_str(),
			CCSIZE_EXP_LAYER_CELL_NAME, 
			CCTextAlignmentCenter, 
			CHAR_FONT_NAME, 
			FLOAT_NAME_LABEL_SIZE);
		pNameLabel->setColor(ccc3(255, 255, 255));
		pNameLabel->setAnchorPoint(CCPointZero);
		pNameLabel->setPosition(CCPOINT_EXP_LAYER_CELL_NAME);
		pCellLayer->addChild(pNameLabel);

		// Add exp.
		char expChar[10];
		sprintf(expChar, "%s+%d", ValuesUtil::Instance()->getString("exp").c_str(), node._plusExp);
		CCLabelTTF *pExpLabel = CCLabelTTF::labelWithString(
			expChar, 
			CCSIZE_EXP_LAYER_CELL_NAME, 
			CCTextAlignmentCenter, 
			CHAR_FONT_NAME, 
			FLOAT_EXP_LABEL_SIZE);
		pExpLabel->setColor(ccc3(0, 255, 0));
		pExpLabel->setAnchorPoint(CCPointZero);
		pExpLabel->setPosition(CCPOINT_EXP_LAYER_CELL_EXP);
		pCellLayer->addChild(pExpLabel);
	}

	return pCellLayer;
}

CCLabelTTF * FightEnd::buildRewards()
{
	ValuesUtil *pValueUtil = ValuesUtil::Instance();
	char pPracticeChar[128];
	string praticeName;
	//char pLine[200] = "";
	int index = 0;
	if(_pReward)
	{
		std::list<SCMD13D::SCMD13DNode>::iterator rewardsIt;
		for(rewardsIt = _pReward->_rewards.begin(); rewardsIt != _pReward->_rewards.end(); ++ rewardsIt)
		{
			SCMD13D::SCMD13DNode node = *rewardsIt;
			if(node._goodsId < 6)
			{
				switch(node._goodsId)
				{
				case 1:
					praticeName = pValueUtil->getString("gold");
					break;
				case 2:
					{
						praticeName = pValueUtil->getString("silver");
						
					}
					break;
				case 3:
					praticeName = pValueUtil->getString("pat");
					break;
				case 4:
					{
						praticeName = pValueUtil->getString("rep");

						{
                            CCNode *pParent = this->getChildByTag(TAG_PARENT);
                            if(pParent)
                            {
                                CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC045").c_str(), CCSizeMake(POSX(450), POSX(22)),CCTextAlignmentLeft, "Arial", POSX(22));
                                pLabel->setPosition(ccp(POSX(28), POSX(74)));
                                pLabel->setAnchorPoint(CCPointZero);
                                pParent->addChild(pLabel, 3);
                                pLabel->setColor(ccc3(255, 255, 255));
                            }
						}
					}
					break; 
				case 5:
					praticeName = pValueUtil->getString("exp");
					break;
				default:
					praticeName = pValueUtil->getString("rep");
					break;
				}
				if(index == 0)
				{
					sprintf(pPracticeChar, "%d%s", node._goodsNum, praticeName.c_str());
				}
				else
				{
					char pTemp[128];
					strcpy(pTemp, pPracticeChar);
					sprintf(pPracticeChar, "%s\n%d%s", pTemp, node._goodsNum, praticeName.c_str());
				}
				++ index;
			}
			else
			{
				_goodId = node._goodsId;
				_goodNum = node._goodsNum;
			}
		}

		if(index == 0)
		{
			return NULL;
		}

		CCLabelTTF *pPraticeLabel = CCLabelTTF::labelWithString(
			pPracticeChar,
			CCSizeMake(FLOAT_PRACTICE_LABEL_SIZE * 10, FLOAT_PRACTICE_LABEL_SIZE * (index + 1)),
			CCTextAlignmentLeft,
			CHAR_FONT_NAME,
			FLOAT_PRACTICE_LABEL_SIZE);
		pPraticeLabel->setColor(ccc3(255, 255, 0));
		pPraticeLabel->setAnchorPoint(CCPointZero);
		pPraticeLabel->setPosition(ccp(CCPOINT_PRACTICE_REWARD.x, 
			CCPOINT_PRACTICE_REWARD.y - FLOAT_PRACTICE_LABEL_SIZE / 2 * (index - 1)));
		return pPraticeLabel;
	}
	else
	{
		return NULL;
	}
	
}

void FightEnd::copyReport( CCObject *pObject )
{

}

void FightEnd::replay( CCObject *pObject )
{

}

void FightEnd::closePanel( CCObject *pObject )
{
	SoundManager::Instance()->playButtonEffectSound();

	//FightLayer::getInstance()->outOfFight();
	SceneFightMediator* m = (SceneFightMediator*)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if(m)
	{
		m->fightOutHandler(0, 0);
	}
	FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(pFightProxy)
		pFightProxy->fightExit();
}

bool FightEnd::isLenOverflow(std::string str , const int CNwordnum , int &nbyteCnt)
{
	int length = str.length();
	int letterCount = 0;
	int wordCount = 0;
	int totalCount = 0;
	int pos = 0;
	int byteCnt = 0;
	while (pos < length)
	{
		if (str[pos] & 0x80)
		{
			pos += 3;
			++wordCount;
		}
		else
		{
			pos += 1;
			++letterCount;
		}
        
		nbyteCnt = pos;
		totalCount = wordCount + (letterCount+1)/2;
		if (totalCount >= CNwordnum)
		{
			return true;
		}
	}
	return false;
}
