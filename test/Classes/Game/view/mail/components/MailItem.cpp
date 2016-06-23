#include "MailItem.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"

#define Mail_Scroll_Item_width (POSX(300))
#define Mail_Scroll_Item_Height (POSX(60))

#define Mail_FontSize (POSX(22))

MailItem::MailItem(MailHeadVo headVo)
{
	if (!CCLayer::init()) {return;	}
	_headVo = headVo;

	CCSize itemSize = CCSizeMake(Mail_Scroll_Item_width,Mail_Scroll_Item_Height);

	this->setContentSize(itemSize);
	this->setIsRelativeAnchorPoint(true);

 	CCUIBackground * pBack = new CCUIBackground();
 	pBack->initWithSpriteFrame("mail/input1.png",CCPointZero,CCPointZero,CCSizeMake(Mail_Scroll_Item_width,Mail_Scroll_Item_Height),225);
 	this->addChild(pBack);
 	pBack->release();

	std::string strPath = (headVo.mailStatus-1) ? ("mail/readed.png") : ("mail/unread.png");
	CCSprite * pIcon = new CCSprite();
	pIcon->initWithSpriteFrameName(strPath.c_str());
	pIcon->setPosition(ccp(pIcon->getContentSize().width/2+POSX(10),itemSize.height/2+POSX(11)));
	this->addChild(pIcon,0);
	pIcon->release();

	CCLabelTTF * pReadState = new CCLabelTTF();
	std::string readState = (headVo.mailStatus-1) ? ValuesUtil::Instance()->getString("MAIL006") : ValuesUtil::Instance()->getString("MAIL007");
	pReadState->initWithString(readState.c_str(),CCSizeMake(POSX(60),POSX(30)),CCTextAlignmentCenter,"Arial",Mail_FontSize);
	pReadState->setPosition(ccp(pIcon->getPosition().x,POSX(12)));
	pReadState->setColor((headVo.mailStatus-1) ? ccc3(12,233,25) : ccc3(220,12,25));
	this->addChild(pReadState,2);
	pReadState->release();

	CCLabelTTF * pTitleText = new CCLabelTTF();
	std::string strTitle = headVo.mailTitle;
	int len = strTitle.length();
	int cnt = 0;
	bool var = isLenOverflow(strTitle , 6 ,cnt);
	if (var)
	{
		strTitle = strTitle.substr(0,cnt);
		strTitle.append("...");
	}
	char path[64] = {0};
	sprintf(path,ValuesUtil::Instance()->getString("MAIL022").c_str() , strTitle.c_str());
	pTitleText->initWithString(path,CCSizeMake(POSX(250),POSX(28)),CCTextAlignmentLeft,"Arial",Mail_FontSize);
	pTitleText->setAnchorPoint(CCPointZero);
	pTitleText->setPosition(ccp(pIcon->getContentSize().width +POSX(30),itemSize.height/2-POSX(4)));
	this->addChild(pTitleText,1);
	pTitleText->release();

	CCLabelTTF * pSenderName = new CCLabelTTF();
	char path2[64] = {0};
	sprintf(path2,ValuesUtil::Instance()->getString("MAIL021").c_str(),headVo.senderName.c_str());
	pSenderName->initWithString(path2,CCSizeMake(POSX(260),POSX(30)),CCTextAlignmentLeft,"Arial",Mail_FontSize);
	pSenderName->setAnchorPoint(CCPointZero);
	pSenderName->setPosition(ccp(pIcon->getContentSize().width +POSX(30),0));
	pSenderName->setColor(ccc3(240,133,25));
	this->addChild(pSenderName,1);
	pSenderName->release();
}

MailItem::~MailItem()
{

}

bool MailItem::isLenOverflow(std::string str , const int CNwordnum , int &nbyteCnt)
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