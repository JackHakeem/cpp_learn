#include "CCUIBackground.h"


CCUIBackground::CCUIBackground()
{
	setAlpha(255);
}

CCUIBackground::~CCUIBackground()
{

}

void CCUIBackground::setPosition(CCPoint var)
{
	CCLayer::setPosition(ccp(var.x-offsetX, var.y-offsetY));
}

void CCUIBackground::setAlpha(int value)
{
	alpha = value;
}

bool CCUIBackground::initWithFile(const char* filename, CCPoint pos, CCPoint offset, CCSize size, int alpha)
{
	if (!filename)
		return false;
	if (!CCLayer::init())
		return false;

	setAlpha(alpha);
	this->setContentSize(size);


	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(filename);
	CCSize ts = texture->getContentSize();
	srcsize = ts;	
	

	offsetX = offset.x;
	offsetY = offset.y;
    

	widthtinterval = size.width - srcsize.width + offsetX * 2;
	heightinterval = size.height - srcsize.height + offsetY * 2;

	if (widthtinterval<0) widthtinterval=0;
	if (heightinterval<0) heightinterval=0;



	x = 0;
	y = heightinterval + ts.height/2;

	this->setPosition(pos);


    // manually add frames to the frame cache
	CCSpriteFrame *frame0 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(0*0, 0*0, ts.width/2, ts.height/2));
    CCSpriteFrame *frame1 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(ts.width/2, 0, ts.width/2, ts.height/2));
	CCSpriteFrame *frame2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(0, ts.height/2, ts.width/2, ts.height/2));
    CCSpriteFrame *frame3 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(ts.width/2, ts.height/2, ts.width/2, ts.height/2));

	CCSpriteFrame *frameheng  = CCSpriteFrame::frameWithTexture(texture, CCRectMake(ts.width/2-1, 0, 2, ts.height/2));
	CCSpriteFrame *frameheng2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(ts.width/2-1, ts.height/2, 2, ts.height/2));

	CCSpriteFrame *frameshu  = CCSpriteFrame::frameWithTexture(texture, CCRectMake(0, ts.height/2-1, ts.width/2, 2));
	CCSpriteFrame *frameshu2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(ts.width/2, ts.height/2-1, ts.width/2, 2));
	
	CCSprite* ppp;
	//Upper left
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame0);
	this->addChild(ppp, 0, CCUIBackground_tl);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setPosition(ccp(x,y));
	ppp->setOpacity(alpha);
	ppp->release();
	//Upper right
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame1);
	this->addChild(ppp, 0, CCUIBackground_tr);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setOpacity(alpha);
	ppp->setPosition(ccp(x + ts.width/2 +widthtinterval,y));
	ppp->release();
	//Left lower
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame2);
	this->addChild(ppp, 0, CCUIBackground_bl);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setOpacity(alpha);
	ppp->setPosition(ccp(x + 0,y-ts.height/2-heightinterval));
	ppp->release();
	//Right lower
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame3);
	this->addChild(ppp, 0, CCUIBackground_br);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setOpacity(alpha);
	ppp->setPosition(ccp(x + ts.width/2 +widthtinterval,y-ts.height/2-heightinterval));
	ppp->release();
	/**/
	//up
	CCSprite* pheng = new CCSprite();
	pheng->initWithSpriteFrame(frameheng);
	pheng->setScaleX(widthtinterval/2);
	pheng->setAnchorPoint(ccp(0,0));
	pheng->setOpacity(alpha);
	this->addChild(pheng,0,CCUIBackground_t);
	pheng->setPosition(ccp(x + ts.width/2,y));
	pheng->release();

	//down
	CCSprite* pheng2 = new CCSprite();
	pheng2->initWithSpriteFrame(frameheng2);
	pheng2->setScaleX(widthtinterval/2);
	pheng2->setAnchorPoint(ccp(0,0));
	pheng2->setOpacity(alpha);
	this->addChild(pheng2,0,CCUIBackground_b);
	pheng2->setPosition(ccp(x + ts.width/2, y-ts.height/2-heightinterval));
	pheng2->release();
	//left
	CCSprite* pshu = new CCSprite();
	pshu->initWithSpriteFrame(frameshu);
	pshu->setScaleY(heightinterval/2);
	pshu->setAnchorPoint(ccp(0,0));
	pshu->setOpacity(alpha);
	this->addChild(pshu,0,CCUIBackground_l);
	pshu->setPosition(ccp(x,y-heightinterval));
	pshu->release();
	//right
	CCSprite* pshu2 = new CCSprite();
	pshu2->initWithSpriteFrame(frameshu2);
	pshu2->setScaleY(heightinterval/2);
	pshu2->setAnchorPoint(ccp(0,0));
	pshu2->setOpacity(alpha);
	this->addChild(pshu2,0,CCUIBackground_r);
	pshu2->setPosition(ccp(x+widthtinterval+ts.width/2,y-heightinterval));
	pshu2->release();


	//center
	CCSpriteFrame *framenei = CCSpriteFrame::frameWithTexture(texture, CCRectMake(ts.width/2-1, ts.height/2-1, 2, 2));
	CCSprite* nei = new CCSprite();
	nei->initWithSpriteFrame(framenei);
	nei->setScaleX(widthtinterval/2);
	nei->setScaleY(heightinterval/2);
	nei->setAnchorPoint(ccp(0,0));
	nei->setOpacity(alpha);
	this->addChild(nei,0,CCUIBackground_n);
	nei->setPosition(ccp(x+ts.width/2, y-heightinterval));
	nei->release();
/*
	enum
	{
		CCUIBackground_tl=0,
		CCUIBackground_tr,
		CCUIBackground_bl,
		CCUIBackground_br,
		CCUIBackground_t,
		CCUIBackground_b,
		CCUIBackground_l,
		CCUIBackground_r,
		CCUIBackground_n
	};
*/

	return true;
}

void CCUIBackground::changeSize(CCSize size)
{
//	CCSprite* ppp;
	

	widthtinterval = size.width - srcsize.width + offsetX * 2;
	heightinterval = size.height - srcsize.height + offsetY * 2;
	if (widthtinterval<0) widthtinterval=0;
	if (heightinterval<0) heightinterval=0;


	x = 0;
	y = heightinterval + srcsize.width/2;

	CCSprite* tl = (CCSprite*)this->getChildByTag(CCUIBackground_tl);
	tl->setPosition(ccp(x,y));

	CCSprite* tr = (CCSprite*)this->getChildByTag(CCUIBackground_tr);
	tr->setPosition(ccp(x + srcsize.width/2 +widthtinterval,y));

	CCSprite* bl = (CCSprite*)this->getChildByTag(CCUIBackground_bl);
	bl->setPosition(ccp(x + 0,y-srcsize.height/2-heightinterval));

	CCSprite* br = (CCSprite*)this->getChildByTag(CCUIBackground_br);
	br->setPosition(ccp(x + srcsize.width/2 +widthtinterval,y-srcsize.height/2-heightinterval));

	CCSprite* pheng = (CCSprite*)this->getChildByTag(CCUIBackground_t);
	pheng->setScaleX(widthtinterval/2);
	pheng->setPosition(ccp(x + srcsize.width/2,y));

	CCSprite* pheng2 = (CCSprite*)this->getChildByTag(CCUIBackground_b);
	pheng2->setScaleX(widthtinterval/2);
	pheng2->setPosition(ccp(x + srcsize.width/2, y-srcsize.height/2-heightinterval));

	CCSprite* pshu = (CCSprite*)this->getChildByTag(CCUIBackground_l);
	pshu->setScaleY(heightinterval/2);
	pshu->setPosition(ccp(x,y-heightinterval));

	CCSprite* pshu2 =(CCSprite*)this->getChildByTag(CCUIBackground_r);
	pshu2->setScaleY(heightinterval/2);
	pshu2->setPosition(ccp(x+widthtinterval+srcsize.width/2,y-heightinterval));

	CCSprite* nei = (CCSprite*)this->getChildByTag(CCUIBackground_n);
	nei->setScaleX(widthtinterval/2);
	nei->setScaleY(heightinterval/2);
	nei->setPosition(ccp(x+srcsize.width/2, y-heightinterval));
}

bool CCUIBackground::initWithSpriteFrame( const char* framename, CCPoint pos, CCPoint offset, CCSize size, int alpha /*= 255*/ )
{
	if (!framename)
		return false;
	if (!CCLayer::init())
		return false;

	setAlpha(alpha);
	this->setContentSize(size);
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);

	if (!pFrame)
	{
		return false;
	}	

	CCTexture2D *pTemp = pFrame->getTexture();
	CCSpriteFrame *pTempFrame = CCSpriteFrame::frameWithTexture(pTemp, pFrame->getRect());
	CCTexture2D *texture = pTempFrame->getTexture();
	//CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(filename);
	//CCSize ts = texture->getContentSize();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	CCSize original = pTempFrame->getOriginalSizeInPixels();
    CCSize ts = CCSizeMake(original.width / CCDirector::sharedDirector()->getContentScaleFactor(),
                           original.height / CCDirector::sharedDirector()->getContentScaleFactor());
	CCPoint originalPoint = pTempFrame->getRect().origin;
#else
	CCSize ts = pTempFrame->getOriginalSizeInPixels();
	CCPoint originalPoint = pTempFrame->getRectInPixels().origin;
#endif
	srcsize = ts;	
	

	offsetX = offset.x;
	offsetY = offset.y;
    

	widthtinterval = size.width - srcsize.width + offsetX * 2;
	heightinterval = size.height - srcsize.height + offsetY * 2;

	if (widthtinterval<0) widthtinterval=0;
	if (heightinterval<0) heightinterval=0;



	x = 0;
	y = heightinterval + ts.height/2;

	this->setPosition(pos);


    // manually add frames to the frame cache
	CCSpriteFrame *frame0 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x, originalPoint.y, ts.width/2, ts.height/2));
    CCSpriteFrame *frame1 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x + ts.width/2, originalPoint.y, ts.width/2, ts.height/2));
	CCSpriteFrame *frame2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x, originalPoint.y + ts.height/2, ts.width/2, ts.height/2));
    CCSpriteFrame *frame3 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x + ts.width/2, originalPoint.y + ts.height/2, ts.width/2, ts.height/2));

	CCSpriteFrame *frameheng  = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x + ts.width/2-1, originalPoint.y, 2, ts.height/2));
	CCSpriteFrame *frameheng2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x + ts.width/2-1, originalPoint.y + ts.height/2, 2, ts.height/2));

	CCSpriteFrame *frameshu  = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x, originalPoint.y + ts.height/2-1, ts.width/2, 2));
	CCSpriteFrame *frameshu2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x + ts.width/2, originalPoint.y + ts.height/2-1, ts.width/2, 2));
	
	CCSprite* ppp;
	//Upper left
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame0);
	this->addChild(ppp, 0, CCUIBackground_tl);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setPosition(ccp(x,y));
	ppp->setOpacity(alpha);
	ppp->release();
	//Upper right
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame1);
	this->addChild(ppp, 0, CCUIBackground_tr);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setOpacity(alpha);
	ppp->setPosition(ccp(x + ts.width/2 +widthtinterval,y));
	ppp->release();
	//Left lower
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame2);
	this->addChild(ppp, 0, CCUIBackground_bl);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setOpacity(alpha);
	ppp->setPosition(ccp(x + 0,y-ts.height/2-heightinterval));
	ppp->release();
	//Right lower
	ppp = new CCSprite();
	ppp->initWithSpriteFrame(frame3);
	this->addChild(ppp, 0, CCUIBackground_br);
	ppp->setAnchorPoint(ccp(0,0));
	ppp->setOpacity(alpha);
	ppp->setPosition(ccp(x + ts.width/2 +widthtinterval,y-ts.height/2-heightinterval));
	ppp->release();
	/**/
	//up
	CCSprite* pheng = new CCSprite();
	pheng->initWithSpriteFrame(frameheng);
	pheng->setScaleX(widthtinterval/2);
	pheng->setAnchorPoint(ccp(0,0));
	pheng->setOpacity(alpha);
	this->addChild(pheng,0,CCUIBackground_t);
	pheng->setPosition(ccp(x + ts.width/2,y));
	pheng->release();

	//down
	CCSprite* pheng2 = new CCSprite();
	pheng2->initWithSpriteFrame(frameheng2);
	pheng2->setScaleX(widthtinterval/2);
	pheng2->setAnchorPoint(ccp(0,0));
	pheng2->setOpacity(alpha);
	this->addChild(pheng2,0,CCUIBackground_b);
	pheng2->setPosition(ccp(x + ts.width/2, y-ts.height/2-heightinterval));
	pheng2->release();
	//left
	CCSprite* pshu = new CCSprite();
	pshu->initWithSpriteFrame(frameshu);
	pshu->setScaleY(heightinterval/2);
	pshu->setAnchorPoint(ccp(0,0));
	pshu->setOpacity(alpha);
	this->addChild(pshu,0,CCUIBackground_l);
	pshu->setPosition(ccp(x,y-heightinterval));
	pshu->release();
	//right
	CCSprite* pshu2 = new CCSprite();
	pshu2->initWithSpriteFrame(frameshu2);
	pshu2->setScaleY(heightinterval/2);
	pshu2->setAnchorPoint(ccp(0,0));
	pshu2->setOpacity(alpha);
	this->addChild(pshu2,0,CCUIBackground_r);
	pshu2->setPosition(ccp(x+widthtinterval+ts.width/2,y-heightinterval));
	pshu2->release();


	//center
	CCSpriteFrame *framenei = CCSpriteFrame::frameWithTexture(texture, CCRectMake(
		originalPoint.x + ts.width/2-1, originalPoint.y + ts.height/2-1, 2, 2));
	CCSprite* nei = new CCSprite();
	nei->initWithSpriteFrame(framenei);
	nei->setScaleX(widthtinterval/2);
	nei->setScaleY(heightinterval/2);
	nei->setAnchorPoint(ccp(0,0));
	nei->setOpacity(alpha);
	this->addChild(nei,0,CCUIBackground_n);
	nei->setPosition(ccp(x+ts.width/2, y-heightinterval));
	nei->release();
/*
	enum
	{
		CCUIBackground_tl=0,
		CCUIBackground_tr,
		CCUIBackground_bl,
		CCUIBackground_br,
		CCUIBackground_t,
		CCUIBackground_b,
		CCUIBackground_l,
		CCUIBackground_r,
		CCUIBackground_n
	};
*/

	return true;
}
