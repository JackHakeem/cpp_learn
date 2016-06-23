#include "KKLabelTTF.h"
#include "utils/ScaleUtil.h"
#include "CCStrokeLabel/CCStrokeLabel.h"



KKLabelTTF::KKLabelTTF():
m_fFontSize(0.0f),m_fCurLabelPixelWidth(0.0f),m_fCurMAXLabelPixelWidth(0.0f),m_fCurTotleLabelPixelWidth(0.0f),m_iCurTag(0)
{
}

KKLabelTTF::~KKLabelTTF()
{}



// on "init" you need to initialize your instance
bool KKLabelTTF::init(float fontSize, float rowHeight, CCSize size)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

    m_fFontSize = POSX(fontSize);//POSX
    m_vFrameSize = CCSizeMake(POSX(size.width), POSX(size.height));// POSX
    m_fCurLabelPixelWidth = 0.0f;
	m_fCurTotleLabelPixelWidth = 0.0f;
    m_iCurTag = -1;
    m_iRow = 0;
    m_fFontRealHeight = POSX(rowHeight);//POSX
	return true;
}

void KKLabelTTF::add(std::string& value, cocos2d::ccColor3B color, bool isBtn)
{
    if (value.empty())
        return;
    int length = value.size();
    if (length <= 0)
        return;
    
    char tmpValue[400];
    strcpy(tmpValue, value.c_str());
    
    bool isEnd = false;
    int startValueIndex = 0;
    while(!isEnd)
    {
        //1 计算剩余像素位置
        float extraPixels = m_vFrameSize.width - m_fCurLabelPixelWidth;
        //2 计算能被分配到本行的字符串
        
        int valueIndex = 0;//startValueIndex;
        float sumPixels = 0;
        while (sumPixels < extraPixels- POSX(10))
        {
            if (valueIndex+startValueIndex >= length)
            {
                isEnd = true;
                break;
            }
            
            if (tmpValue[valueIndex+startValueIndex] & 0x80)
            {//中文
                valueIndex += 3;
                sumPixels+=m_fFontSize;
               // CCLog(".............%s",tmpValue[valueIndex+startValueIndex]);
            }
            else 
            {//半角
                valueIndex++;
                sumPixels+=m_fFontSize/2;
            }
        }
		int compareLength = valueIndex+startValueIndex;
        if (compareLength >= length)
        {//试过sumPixels < extraPixels-10没符合直接跳过但是也符合这个的 导致死循环
            isEnd = true;
        }
        
        std::string addStr = value.substr(startValueIndex, valueIndex);
        //
        startValueIndex += valueIndex;
       
        //
        //获取
        if (this->getChildByTag(m_iCurTag+1))
            return;
        //CCLabelTTF* label = CCLabelTTF::labelWithString(addStr.c_str(), CCSizeMake(0, 0), CCTextAlignmentLeft, "Arial", m_fFontSize);
		CCStrokeLabel *label = CCStrokeLabel::labelWithString(addStr.c_str(), "Arial", m_fFontSize );
        if (!label)return;
		label->setStroke(1.0f, ccc3(0, 0, 0));
        label->setColor(color);
        label->setAnchorPoint(ccp(0, 0));
       // m_fFontRealHeight = label->getTextureRect().size.height;
        float rectWidth = label->getTextureRect().size.width;
        float rectWidth2 = label->getContentSize().width;
       // m_fCurLabelPixelWidth += rectWidth;
        m_fCurTotleLabelPixelWidth += rectWidth;
        //if (m_fCurLabelPixelWidth+rectWidth >= m_vFrameSize.width)
        if (!(sumPixels < extraPixels- POSX(10)) && value.size() != startValueIndex)
        {//加一行
            
            //m_iRow++;
            label->setPosition(ccp(m_fCurLabelPixelWidth, -m_fFontRealHeight*m_iRow));
            m_fCurLabelPixelWidth = 0;
            m_iRow++;
        }
        else {
            label->setPosition(ccp(m_fCurLabelPixelWidth, -m_fFontRealHeight*m_iRow));
            m_fCurLabelPixelWidth+=rectWidth;
			if (m_fCurMAXLabelPixelWidth < m_fCurLabelPixelWidth)
				m_fCurMAXLabelPixelWidth = m_fCurLabelPixelWidth;//for gong_gao
        }
        //
        this->addChild(label, 0, ++m_iCurTag);
		label->release(); //davidjae 20130123
    }       
}

