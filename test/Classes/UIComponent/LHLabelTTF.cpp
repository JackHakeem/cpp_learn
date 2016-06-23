#include "LHLabelTTF.h"

LHLabelTTF::LHLabelTTF() : _str(0)
{

}

LHLabelTTF::~LHLabelTTF()
{

}

bool LHLabelTTF::initWithString(char * str , const CCSize & size , CCTextAlignment aliment ,  const char * fontName , 
	float fontSize , float strokeSize , ccColor3B strokecolor , CCAction * pStrokeAction , bool bLine , float lineSize )
{
	//CCLabelTTF * pLabel = new CCLabelTTF();
	bool var = this->CCLabelTTF::initWithString(str , size ,aliment , fontName , fontSize);
	_str = str;
	setLineSize(lineSize);
	setFontSize(fontSize);
	setStrokeSize(strokeSize);
	setStrokeColor(strokecolor);
	if (var)
	{
		CCRenderTexture * pStrokeTexture = createStroke((CCLabelTTF *)this ,  strokeSize , strokecolor);
		this->addChild(pStrokeTexture , -1);
		if (pStrokeAction)
		{
			pStrokeTexture->runAction(pStrokeAction);
		}
		
		//pStrokeTexture->release();

		if (bLine)
		{
			CCLayerColor * pLineLayer = new CCLayerColor();
			pLineLayer->initWithColorWidthHeight(ccc4(255,215,0,255) , getTextWidth() , getLineSize());
			pLineLayer->setPosition(ccp(this->getPositionX() , this->getPositionY() - 1));
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

CCRenderTexture * LHLabelTTF::createStroke(CCLabelTTF* label ,   float size , ccColor3B color)
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

void LHLabelTTF::setString(const char *str)
{
	this->CCLabelTTF::setString(str);
	//
}

float LHLabelTTF::getTextWidth()
{
	float width = 0;
	if (!_str)
	{
		return width;
	}	
	std::string str = _str;
	width = str.length() * getFontSize()/3;
	return width;
}