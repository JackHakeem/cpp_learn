#include "VipScrollView.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"

const int PAGE_COUNT = 11;


void VipScrollView::scrollToPage( int pageId )
{
	this->moveToPage(pageId);
	if(_pScrollListener)
	{
		_pScrollListener->onScrollListener(currentScreen);
	}
}

VipScrollView::VipScrollView( CCRect rect ):CCUIPartialScrollView(rect)
{
	this->setContentSize(rect.size);
	this->setPosition(rect.origin);

	_pScrollListener = NULL;
}

VipScrollView::~VipScrollView()
{

}

VipScrollView * VipScrollView::scrollViewWithRect( CCRect rect )
{
	VipScrollView *pScrollView = new VipScrollView(rect);
	if(pScrollView && pScrollView->init()){
	//	pScrollView->setIsTouchEnabled(false);
		//pScrollView->autorelease();
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}

void VipScrollView::initData()
{
	for(int i=0; i<PAGE_COUNT; ++i)
	{
		CCLayer *pPageLayer = getLayerByTag(i);
		if(!pPageLayer)
		{
			addLayerByTag(i);

			pPageLayer = getLayerByTag(i);
			if (!pPageLayer)
				return;


			pPageLayer->addChild(buildPageLayer(i));
		}
	}
}

CCLayer * VipScrollView::buildPageLayer( int pageId )
{
	CCLayer *pPageLayer = CCLayer::node();
	pPageLayer->setPosition(CCPointZero);
	pPageLayer->setAnchorPoint(CCPointZero);
	

	CCUIBackground* pBgLayer = new CCUIBackground();
	pBgLayer->initWithSpriteFrame("popuibg/bg2.png", 
		ccp(POSX(8), POSX(2)), 
		ccp(0,0), 
		CCSizeMake(POSX(890), POSX(248)));
	pPageLayer->addChild(pBgLayer);
	pBgLayer->release();
	//return pPageLayer;
	// Title ccp(52, 152) ccp(0, 0)
	// Text ccp(52, 136) ccp(0, 1)
	ValuesUtil *pValueUtil = ValuesUtil::Instance();
	string titleStr;
	char pTitle[150];//change 100 to 150
	char pText[10000];

	int page = pageId - 1;
	int lineNum = 0;
	switch(page)
	{
	case -1:// vip1
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 1);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n7. %s",
				pValueUtil->getString("VIP103").c_str(),
				pValueUtil->getString("VIP104").c_str(),
				pValueUtil->getString("VIP105").c_str(),
				pValueUtil->getString("VIP106").c_str(),
				pValueUtil->getString("VIP107").c_str(),
				pValueUtil->getString("VIP108").c_str(),
				pValueUtil->getString("VIP109").c_str());
			lineNum = 10;
		}
		break;

	case 0:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 2);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s\n5. %s", 
				pValueUtil->getString("VIP110").c_str(),
				pValueUtil->getString("VIP111").c_str(),
                pValueUtil->getString("VIP112").c_str(),
                pValueUtil->getString("VIP113").c_str(),
				pValueUtil->getString("VIP114").c_str());
			lineNum = 9;
		}
		break;

	case 1:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 3);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s\n5. %s", 
				pValueUtil->getString("VIP116").c_str(),
				pValueUtil->getString("VIP117").c_str(),
                pValueUtil->getString("VIP118").c_str(),
                pValueUtil->getString("VIP119").c_str(),
				pValueUtil->getString("VIP120").c_str());
			lineNum = 9;
		}
		break;

	case 2:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 4);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s\n5. %s", 
				pValueUtil->getString("VIP122").c_str(),
				pValueUtil->getString("VIP123").c_str(),
				pValueUtil->getString("VIP124").c_str(),
				pValueUtil->getString("VIP125").c_str(),
				pValueUtil->getString("VIP127").c_str());
			lineNum = 9;
		}
		break;

	case 3:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 5);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s", 
				pValueUtil->getString("VIP128").c_str(),
				pValueUtil->getString("VIP129").c_str(),
				pValueUtil->getString("VIP130").c_str(),
				pValueUtil->getString("VIP131").c_str(),
				pValueUtil->getString("VIP132").c_str(),
				pValueUtil->getString("VIP133").c_str());
			lineNum = 9;
		}
		break;

	case 4:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 6);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s\n5. %s", 
				pValueUtil->getString("VIP134").c_str(),
				pValueUtil->getString("VIP135").c_str(),
				pValueUtil->getString("VIP136").c_str(),
				pValueUtil->getString("VIP137").c_str(),
				pValueUtil->getString("VIP138").c_str());
			lineNum = 8;
		}
		break;

	case 5:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 7);
			sprintf(pText, "1. %s\n2. %s\n3. %s\n4. %s", 
				pValueUtil->getString("VIP139").c_str(),
				pValueUtil->getString("VIP140").c_str(),
				pValueUtil->getString("VIP141").c_str(),
				pValueUtil->getString("VIP142").c_str());
			lineNum = 7;
		}
		break;

	case 6:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 8);
			sprintf(pText, "1. %s\n2. %s\n3. %s", 
				pValueUtil->getString("VIP143").c_str(),
				pValueUtil->getString("VIP144").c_str(),
				pValueUtil->getString("VIP145").c_str());
			lineNum = 6;
		}
		break;

	case 7:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 9);
			sprintf(pText, "1. %s\n2. %s\n3. %s", 
				pValueUtil->getString("VIP146").c_str(),
				pValueUtil->getString("VIP147").c_str(),
				pValueUtil->getString("VIP148").c_str());
			lineNum = 6;
		}
		break;

	case 8:
		{
			sprintf(pTitle, pValueUtil->getString("VIP014").c_str(), 10);
			sprintf(pText, "1. %s\n2. %s\n3. %s", 
				pValueUtil->getString("VIP149").c_str(),
				pValueUtil->getString("VIP150").c_str(),
				pValueUtil->getString("VIP151").c_str());
			lineNum = 6;
		}
		break;

	case 9:
		{
			sprintf(pTitle, "%s", pValueUtil->getString("VIP152").c_str());
            sprintf(pText, "");	
			lineNum = 4;
		}
		break;

	default:
		lineNum = 1;
		break;
	}//mao 2013.1.23

	// Title ccp(52, 152) ccp(0, 0)
	// Text ccp(52, 136) ccp(0, 1)
	CCLabelTTF *pTitleLabel = CCLabelTTF::labelWithString(pTitle, CCSizeMake(POSX(890), POSX(20)), 
		CCTextAlignmentLeft, "Arial", POSX(20));
	pTitleLabel->setAnchorPoint(CCPointZero);
	pTitleLabel->setPosition(ccp(POSX(52), POSX(224)));
	pPageLayer->addChild(pTitleLabel);

	CCLabelTTF *pTextLabel = CCLabelTTF::labelWithString(pText, CCSizeMake(POSX(890), POSX(24 * lineNum)), 
		CCTextAlignmentLeft, "Arial", POSX(20));
	pTextLabel->setAnchorPoint(ccp(0, 1));
	pTextLabel->setPosition(ccp(POSX(52), POSX(230)));
	pPageLayer->addChild(pTextLabel);


	if(page == -1){
		//_txtTimer.visible = true;
		//_txtTimer.htmlText = "<font color='#FFCC00' size='14'>"+ LangManager.getText("VIP070")+"</font>";
		//_txtTimer.x = _txtCaption.x +  _txtCaption.textWidth;
		//_txtTimer.y = _txtCaption.y + _txtCaption.textHeight - _txtTimer.textHeight;
	}
	else{
		//_txtTimer.visible = false;
	}
	return pPageLayer;
}

void VipScrollView::handleTouchEndPagePre()
{
	if(_pScrollListener)
	{
		_pScrollListener->onScrollListener(currentScreen);
	}
}

void VipScrollView::handleTouchEndPageNext()
{
	if(_pScrollListener)
	{
		_pScrollListener->onScrollListener(currentScreen);
	}
}

void VipScrollView::handleTouchEnd2Page()
{
	if(_pScrollListener)
	{
		_pScrollListener->onScrollListener(currentScreen);
	}
}
