#include "LHMenuItemLabel.h"

LHMenuItemLabel::LHMenuItemLabel() : _pLabel(0) 
{

}

LHMenuItemLabel::~LHMenuItemLabel()
{

}

bool LHMenuItemLabel::initWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector , float fontSize ,
	float strokeSize , ccColor3B strokecolor , CCAction * pStrokeAction , bool bLine , float lineSize)
{
	_pLabel = (CCLabelTTF *)label;
	bool var =this->CCMenuItemLabel::initWithLabel(label,  target, selector);
	setLineSize(lineSize);
	setFontSize(fontSize);
	setStrokeSize(strokeSize);
	setStrokeColor(strokecolor);
	if (var)
	{
		CCRenderTexture * pStrokeTexture = createStroke((CCLabelTTF *)label ,  strokeSize , strokecolor);
		this->addChild(pStrokeTexture , -1);
		if (pStrokeAction)
		{
			pStrokeTexture->runAction(pStrokeAction);
		}		

		if (bLine)
		{
			CCLayerColor * pLineLayer = new CCLayerColor();
			pLineLayer->initWithColorWidthHeight(ccc4(255,215,0,255) , getTextWidth() , getLineSize());
			pLineLayer->setPosition(ccp(label->getPositionX() , label->getPositionY() - 1));
			this->addChild(pLineLayer , 1);
			pLineLayer->release();
		}
		
	}
	else
	{
		return false;
	}
	return true;
}

CCRenderTexture * LHMenuItemLabel::createStroke(CCLabelTTF* label ,   float size , ccColor3B color)
{
	CCRenderTexture* rt = CCRenderTexture::renderTextureWithWidthAndHeight(label->getContentSize().width+size*2 , label->getContentSize().height+size*2);
	CCPoint originalPos = label->getPosition();
	ccColor3B originalColor = label->getColor();
	bool originalVisibility = label->getIsVisible();
	label->setColor(color);
	label->setIsVisible(true);
	ccBlendFunc originalBlend = label->getBlendFunc();
	ccBlendFunc blend = {GL_ONE, GL_ONE}; // inScene will lay on background and will not be used with alpha
	label->setBlendFunc(blend);
	CCPoint bottomLeft = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x + size, 
		label->getTexture()->getContentSize().height * label->getAnchorPoint().y + size);
	//CCPoint positionOffset = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x- label->getTexture()->getContentSize().width/2,
	//	label->getTexture()->getContentSize().height * label->getAnchorPoint().y - label->getTexture()->getContentSize().height/2);

	CCPoint positionOffset= ccp(-label->getContentSize().width/2,-label->getContentSize().height/2);

	CCPoint position = ccpSub(originalPos, positionOffset);

	rt->begin();
	for (int i=0; i<360; i+=10) // you should optimize that for your needs
	{
		label->setPosition(ccp(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*size, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*size));
		label->visit();
	}
	rt->end();
	label->setPosition(originalPos);
	label->setColor(originalColor);
	label->setBlendFunc(originalBlend);
	label->setIsVisible(originalVisibility);
	rt->setPosition(position);
	return rt;
}

float LHMenuItemLabel::getTextWidth()
{
	float width = 0;
	if (!_pLabel)
	{
		return width;
	}
	
	std::string str = _pLabel->getString();
	width = str.length() * getFontSize()/3;
	return width;
}