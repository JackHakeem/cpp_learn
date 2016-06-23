#include "CCUIPrintLine.h"
#include "utils/ScaleUtil.h"

CCUIPrintLine::CCUIPrintLine()
{
	setVisitRect(CCRectMake(POSX(0),POSX(0),POSX(0),POSX(0)));
	setPrintRect(CCRectMake(POSX(0),POSX(0),POSX(0),POSX(0)));
	setIsLastLine(false);
	setLineX(0);
}

CCUIPrintLine::~CCUIPrintLine()
{
	cleanup();
}

CCUIPrintLine * CCUIPrintLine::initUIPrintLineWithCCRect(CCSize size,std::string strText,float fontsize)
{
	CCUIPrintLine * pPrintView = new CCUIPrintLine();
	if (pPrintView && pPrintView->init())
	{
		pPrintView->setPrintSize(size);
		pPrintView->setFontSize(fontsize);
		pPrintView->setPrintString(strText);
		pPrintView->loadItems();
		return pPrintView;
	}
	CC_SAFE_DELETE(pPrintView);
	return 0;
}

bool CCUIPrintLine::init()
{
	if (!CCLayerColor::init())
	{
		return false;
	}
	this->setColor(ccc3(255,0,0));
	return true;
}

void CCUIPrintLine::visit(CCSize size)
{
	CCRect oRect = getVisitRect();
	CCRect rect;
	rect.origin.x = oRect.origin.x;
	rect.origin.y = oRect.origin.y;
	rect.size.width = size.width;
	rect.size.height = size.height;
	setVisitRect(rect);

	visit();
}

void CCUIPrintLine::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	glEnable(GL_SCISSOR_TEST);
	CCPoint pos = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize sizeNow = getVisitRect().size;
	CCSize sizeMax = getPrintSize();
    
	float vx = pos.x * scale - scale *sizeMax.width/2;
	float vwidth = scale *sizeNow.width;
	glScissor(vx , (pos.y * scale - scale *sizeNow.height/2),
              vwidth, scale *sizeNow.height);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	glEnable(GL_SCISSOR_TEST);
	CCPoint pos = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize sizeNow = getVisitRect().size;
	CCSize sizeMax = getPrintSize();
    
	float vx = pos.x * scale - scale *sizeMax.width/2;
	float vwidth = scale *sizeNow.width;
	glScissor(vx , (pos.y * scale - scale *sizeNow.height/2),
              vwidth, scale *sizeNow.height);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#endif
}

void CCUIPrintLine::loadItems()
{
	this->setContentSize(getPrintRect().size);
	std::string strText = getPrintString();
	CCLabelTTF * pLabText = new CCLabelTTF();
	pLabText->initWithString(
		strText.c_str(),
		getPrintRect().size,
		CCTextAlignmentLeft,
		"Arial",
		getFontSize());
	pLabText->setAnchorPoint(ccp(0,0.5));

	CCSize size = getPrintSize();
	int len = strText.length();
	_deltaWidth = size.width - len * (getFontSize()/2.0f);

	//pLabText->setPosition(ccp((-1)*pLabText->getContentSize().width/2.0f,0));
	
	if (((strText.length() * getFontSize()/2.0f) >= getPrintSize().width))
	{
		pLabText->setPosition(ccp((-1)*pLabText->getContentSize().width/2.0f,0));
	}
	else
	{ 
		pLabText->setPosition(ccp((-1)*pLabText->getContentSize().width/2.0f,0));
		//pLabText->setPosition(ccp((-1) *_deltaWidth/2.0f , 0));
	}
	
	pLabText->setTag(TAG_Labtxt);
	this->addChild(pLabText);
	pLabText->release();
}

void CCUIPrintLine::setLineX(float vx)
{
	if (!_lineX)
	{
		_lineX = vx;
	}
}