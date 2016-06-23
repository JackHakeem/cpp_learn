#include "Alert.h"
#include "CCUIBackground.h"
#include "TextFieldTTF.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "KKLabelTTF.h"
//const float rowheight = 32;

Alert::Alert()
{
	pMenu = 0;
	buttonCount = 0;
	rowMaxFontCount = 0;
	fontSize = 18.0f;
	rowHeight = 32;
//	m_str.clear();
}

Alert::~Alert()
{
	m_str.clear();
}

bool Alert::initWithParam(CCRect rect, bool toRight)
{
	if (!CCLayer::init())
		return false;

	//this->setIsRelativeAnchorPoint(true);

	if (toRight)
		this->setAnchorPoint(ccp(0, 1.0f));//×óÉÏ
	else
		this->setAnchorPoint(ccp(1.0f, 1.0f));//ÓÒÉÏ

	this->setPosition(rect.origin);
	this->isRight = toRight;
	return true;
}

bool Alert::addStr(std::string str, cocos2d::ccColor3B color)
{
	int len = str.size();
	if (len == 0)
		return false;

	if (len>10)
	{
		std::string newsub = str.substr();
	}
	
	strinfo info;
	info.str = str;
	info.color = color;

	m_str.push_back(info);

	if (len > rowMaxFontCount)
		rowMaxFontCount = len;

	if (rowMaxFontCount>100)
	{
		rowMaxFontCount = 100;
	}
	return true;
}

bool Alert::addButton(std::string buttonName, CCObject* target, SEL_MenuHandler selector)
{
	if (!pMenu)
	{
		pMenu = new CCMenu();//CCMenu::menuWithItems(pCloseItem, NULL);
		if (!pMenu) //|| !pMenu->init()
		{
			CCLog("error bool Alert::addButton(std::string buttonName, SelectorProtocol* target, SEL_MenuHandler selector)");
			return false;
		}
		pMenu->init();
		pMenu->setPosition( CCPointZero );
		pMenu->setTouchLayer(-9999/*TLE::PreTipsLayer_Alert*/);//TLE::TipsLayer_Alert
		this->addChild(pMenu, 2);
	}

	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return false;
	}
	CCMenuItemSprite *newButton = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		target,
		selector);

	if (!newButton)
	{
		CCLog("error bool Alert::addButton(std::string buttonName, SelectorProtocol* target, SEL_MenuHandler selector)");
		return false;
	}


	newButton->setPosition(ccp(POSX(buttonCount*121*0.7f+buttonCount*10), 0));
	newButton->setScaleX(0.7f);
	newButton->setScaleY(0.7f);
	pMenu->addChild(newButton, AlertZ_button0, buttonCount++);
	
	UTF8(buttonName);
	CCLabelTTF* pLable = CCLabelTTF::labelWithString(buttonName.c_str(),
		CCSizeMake(newButton->getContentSize().width, POSX(20)),
		CCTextAlignmentCenter, 
		"Arial", 
		POSX(20));
	pLable->setPosition(ccp(newButton->getContentSize().width/2, newButton->getContentSize().height/2));
	pLable->setScale(1.2f);
	newButton->addChild(pLable, 2);
	pLable->setColor(ccc3(254, 189, 0));

	return true;
}

void Alert::centerShow()
{
	int32 rowcount = m_str.size();
	int32 currowcount = 0;

	std::list<strinfo>::iterator it;
	
	CCUIBackground* bg = 0;
	if (pMenu)
	{
		int hOffset = 20;
		int btnStartX = 30;
		int btnEndX = 464-60;

		for (it = m_str.begin(); it != m_str.end(); it++)
		{
			strinfo info = *it;
			CCLabelTTF* pLable = CCLabelTTF::labelWithString(info.str.c_str(), 
				CCSizeMake(POSX(400.f),POSX(fontSize*3)),
				CCTextAlignmentCenter, 
				"Arial", 
				POSX(fontSize));
			pLable->setPosition(ccp(POSX(-10), POSX((rowcount-currowcount)*rowHeight+hOffset)));
			this->addChild(pLable, 2);
			pLable->setColor(info.color);
			currowcount++;
		}

		int btncount = pMenu->getChildren()->count();
		for (int i = 0; i < btncount; i++)
		{
			pMenu->getChildByTag(i)->setScale(1.0f);//(btnEndX-btnStartX)/btncount * i + btnStartX -464/2 + pMenu->getChildByTag(i)->getContentSize().width/2
			pMenu->getChildByTag(i)->setPosition(ccp(
				i%2==0 ? (POSX(-464/2) + pMenu->getChildByTag(i)->getContentSize().width/2 + POSX(btnStartX)) : (POSX(-464/2) - pMenu->getChildByTag(i)->getContentSize().width/2 + POSX(btnEndX+20)), POSX(-130/2+40)));// + (464/(btncount+1))*(i+1)
		}

		this->setContentSize(CCSizeMake(POSX(rowMaxFontCount/2*fontSize), POSX(200)));
		bg = new CCUIBackground();
		bg->initWithSpriteFrame("ui.png", ccp(POSX(-464/2), POSX(-130/2)), ccp(POSX(6),POSX(7)), CCSizeMake(POSX(464), POSX(150)));//buttonCount*121 CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
		this->addChild(bg, 1);
		bg->release();		
	}
}

void Alert::centerShowTextInput()
{
	int32 rowcount = m_str.size();
	int32 currowcount = 0;

	std::list<strinfo>::iterator it;
	
	CCUIBackground* bg = 0;
	if (pMenu)
	{
		int hOffset = 10;
		int btnStartX = 30;
		int btnEndX = 464-60;

		for (it = m_str.begin(); it != m_str.end(); it++)
		{
			strinfo info = *it;
			CCLabelTTF* pLable = CCLabelTTF::labelWithString(info.str.c_str(), 
				CCSizeMake(POSX(1024.f),POSX(34.0f)),
				CCTextAlignmentCenter, 
				"Arial", 
				POSX(34.0f));
			pLable->setPosition(ccp(POSX(-130), POSX((rowcount-currowcount)*rowHeight+hOffset)));
			this->addChild(pLable, 2);
			pLable->setColor(info.color);
			currowcount++;
		}

				
		TextFieldTTF * pTextField = new TextFieldTTF();
        pTextField->m_pri = -1590;
		pTextField->setUp(this, POSX(50));
		this->addChild(pTextField, AlertZ_CCTextFieldTTF, AlertTAG_CCTextFieldTTF);
		pTextField->setPosition(ccp(POSX(rowMaxFontCount/2*fontSize / 2+210), POSX(40)));

		{//ÊäÈë¿ò
			CCUIBackground* _insertBG = new CCUIBackground();
			_insertBG->initWithSpriteFrame("chat/chat_2.png", ccp(POSX(-40), POSX(20)),ccp(0,0),
				CCSizeMake(POSX(250),POSX(10)));
			this->addChild(_insertBG, 2);
			_insertBG->release();		
		}

		int btncount = pMenu->getChildren()->count();
		for (int i = 0; i < btncount; i++)
		{
			pMenu->getChildByTag(i)->setScale(1.0f);//(btnEndX-btnStartX)/btncount * i + btnStartX -464/2 + pMenu->getChildByTag(i)->getContentSize().width/2
			pMenu->getChildByTag(i)->setPosition(ccp(
				i%2==0 ? (POSX(-464/2) + pMenu->getChildByTag(i)->getContentSize().width/2 + POSX(btnStartX)) : (POSX(-464/2) - pMenu->getChildByTag(i)->getContentSize().width/2 + POSX(btnEndX+20)), POSX(-130/2+40)));// + (464/(btncount+1))*(i+1)
		}

		this->setContentSize(CCSizeMake(POSX(rowMaxFontCount/2*fontSize), POSX(200)));
		bg = new CCUIBackground();
		bg->initWithSpriteFrame("ui.png", ccp(POSX(-464/2), POSX(-130/2)), ccp(POSX(6),POSX(7)), CCSizeMake(POSX(464), POSX(150)));//buttonCount*121 CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
		this->addChild(bg, 1);
		bg->release();		
	}
}

void Alert::show()
{
	int32 rowcount = m_str.size();
	int32 currowcount = 0;
    float heightcount = 0;
    
	std::list<strinfo>::reverse_iterator it;
	
	CCUIBackground* bg = 0;
	if (pMenu)
	{
		float btnlen = buttonCount*121*0.7f+buttonCount*10+26;
		float hOffset = 0;
		for (it = m_str.rbegin(); it != m_str.rend(); it++)
		{
			strinfo info = *it;

            KKLabelTTF* pLabel = new KKLabelTTF();
            pLabel->init(fontSize, 26.0f, CCSizeMake(220, 200));
            pLabel->add(info.str, info.color);
            this->addChild(pLabel, 2);
            rowHeight = pLabel->m_fFontRealHeight;
            heightcount += (pLabel->m_iRow+1)*pLabel->m_fFontRealHeight;
            pLabel->setPosition(ccp(POSX(10), heightcount- POSX(20.0f)));
            currowcount+=1;//(pLabel->m_iRow+1);
			
		}


		pMenu->setIsRelativeAnchorPoint(true);
		pMenu->setAnchorPoint(ccp(0,0));
		pMenu->setPosition(ccp(POSX(60), POSX(-26.0f)));
		
		float csx = 240;//rowMaxFontCount/2*(fontSize-4);
		if (csx < 220) csx = 220;
		this->setContentSize(CCSizeMake(POSX(csx), heightcount+POSX(hOffset+26.0f*2)));//rowcount*rowHeight
		bg = new CCUIBackground();
		/*
        if (btnlen > this->getContentSize().width)
		{
			setBgSize(CCSizeMake(btnlen, this->getContentSize().height));
			bg->initWithSpriteFrame("ui.png", ccp(0,0), ccp(POSX(6), POSX(7)), getBgSize());
		}
		else
        */
		{
			setBgSize(this->getContentSize());
			bg->initWithSpriteFrame("ui.png", ccp(0, POSX(-26.0f*2)), ccp(POSX(6), POSX(7)), getBgSize());
		}

		this->addChild(bg, 1);
		bg->release();		
	}
	else
	{
		//float btnlen = 240;
		float hOffset = POSX(6);
      
		for (it = m_str.rbegin(); it != m_str.rend(); it++)
		{
            strinfo info = *it;
            
            KKLabelTTF* pLabel = new KKLabelTTF();
            pLabel->init(fontSize, 26.0f, CCSizeMake(220, 200));
            pLabel->add(info.str, info.color);
            this->addChild(pLabel, 2);
            rowHeight = pLabel->m_fFontRealHeight;
            heightcount += (pLabel->m_iRow+1)*pLabel->m_fFontRealHeight;
            pLabel->setPosition(ccp(POSX(10), heightcount + hOffset));
            currowcount+=1;//(pLabel->m_iRow+1);
			

		}

		
		float csx = 240;//rowMaxFontCount/2*(fontSize-4);
//		if (csx < 220) csx = 220;
		this->setContentSize(CCSizeMake(POSX(csx), heightcount));
		bg = new CCUIBackground();

		{
			setBgSize(this->getContentSize());
			bg->initWithSpriteFrame("ui.png", ccp(0,POSX(26)), ccp(POSX(6), POSX(7)), getBgSize());
		}

		this->addChild(bg, 1);
        //this->setPosition(ccp(0,0));//(ccpAdd(this->getPosition(), ccp(0, POSX(heightcount/2))));
		bg->release();			
	}
}

//CC_PROPERTY(int32, _BgSize, BgSize)	
CCSize Alert::getBgSize()
{
	return _BgSize;
}

void Alert::setBgSize(CCSize var)
{
	_BgSize = var;
}

const char* Alert::getString()
{
	TextFieldTTF* pTextField = (TextFieldTTF*)this->getChildByTag(AlertTAG_CCTextFieldTTF);
	if (pTextField)
	{
		 CCTextFieldTTF * pccTextField = (CCTextFieldTTF*)pTextField->m_pTrackNode;
		 if (pccTextField)
		 {
			return pccTextField->getString();
		 }
	}
	return 0;
	//	return pTextField->getString();
}