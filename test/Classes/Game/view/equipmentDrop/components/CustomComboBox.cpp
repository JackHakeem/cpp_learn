#include "CustomComboBox.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

CustomComboBox::CustomComboBox(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	m_pri = -20000;
	m_screen_last = -1;
	m_pSelectorTarget = 0; 
	m_pCallFuncND = 0; 
	m_data = 0;
}

void CustomComboBox::execute()
{
	if (m_pSelectorTarget && m_pCallFuncND) 
	{
		(m_pSelectorTarget->*m_pCallFuncND)(m_pSelectorTarget, m_data);
	}
}

bool CustomComboBox::initWithParam(CCNode* target, SEL_CallFuncND selector, void* data)
{
	m_pSelectorTarget = target;
	m_pCallFuncND = selector;
	m_data = data;
	return true;
}

CustomComboBox* CustomComboBox::customComboBoxWithCCRect(const CCRect& mRect)
{
    CustomComboBox *pScrollView = new CustomComboBox(mRect);
    if(pScrollView && pScrollView->init()){
        pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}

int CustomComboBox::dataProvider(int tag, const char* value)
{
	int realtag = m_realtag2tag.size();

	CCLayer* layer = getLayerByTag(realtag);//0KK
	if (!layer)
		addLayerByTag(realtag);
	else
		return -1;

	layer = getLayerByTag(realtag);
	if (!layer)
		return -1;//error

	if (layer)
	{
		CCSize size = CCSizeMake(POSX(this->getContentSize().width+20), POSX(this->getContentSize().height));
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, size, CCTextAlignmentCenter, "Arial", POSX(24));
		CCSize labelsize = pLabel->getContentSize();
		pLabel->setPosition(ccp(POSX(labelsize.width/2-10), POSX(labelsize.height/2)));
		layer->setAnchorPoint(ccp(0, 0));
		layer->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(157, 127, 77));
		m_realtag2tag.push_back(tag);
	}
	return tag;
}

int CustomComboBox::getTagByIndex(int index)
{
	for (int i = 0; i < (int)m_realtag2tag.size(); i++)
	{
		if (m_realtag2tag[i] == index)
			return i;
	}
	return -1;
}

void CustomComboBox::setselectedIndex(int index)
{
	int tag = getTagByIndex(index);
	_selectedIndex = tag;
	if (tag+1 >= 1)
	{
		this->moveToPage(tag+1);
		handleTouchEnd2Page();		
	}
	
}

int CustomComboBox::getselectedIndex()
{
	return _selectedIndex;
}


void CustomComboBox::visit()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
    CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
    glEnable(GL_SCISSOR_TEST);
    glScissor(convertedLocationLowerLeft.x * scale, convertedLocationLowerLeft.y * scale,
              this->getVisitSize().width * scale, this->getVisitSize().height * scale);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
    glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x * scale-this->getVisitSize().width, convertedLocationLowerLeft.y * scale,
              this->getVisitSize().width+this->getVisitSize().width*2, this->getVisitSize().height);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
#endif
}

bool CustomComboBox::getIsTouchInContentLayer( CCTouch *pTouch)
{
    CCPoint nodeSpaceLocation = this->convertTouchToNodeSpace(pTouch);

    CCRect contentLayerRect = CCRectZero;
    contentLayerRect.origin = CCPointZero;
	contentLayerRect.origin.x -= contentLayer->getContentSize().width;
    contentLayerRect.size = contentLayer->getContentSize();
	contentLayerRect.size.width += contentLayer->getContentSize().width*2;

    return CCRect::CCRectContainsPoint(contentLayerRect, nodeSpaceLocation);
}

void CustomComboBox::moveToNextPageClick(CCObject* pSender)
{	
	if ( (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
		handleTouchEndPageNext();
	}
}

void CustomComboBox::moveToPreviousPageClick(CCObject* pSender)
{
	if ( (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
		handleTouchEndPagePre();
	}
}

void CustomComboBox::refreshLvBoxLabel()
{
	
	if (m_screen_last > 0)
	{
		CCLayer* layer = getLayerByTag(m_screen_last-1);
		if (layer)
		{
			CCLabelTTF* pLabel = (CCLabelTTF*)layer->getChildByTag(0);
			pLabel->setColor(ccc3(157, 127, 77));
			pLabel->setScale(1.0f);
		}		
	}

	
	
	CCLayer* layer = getLayerByTag(currentScreen-1);
	if (!layer) return;
	CCLabelTTF* pLabel = (CCLabelTTF*)layer->getChildByTag(0);
	pLabel->setColor(ccc3(255,128,64));
	pLabel->setScale(1.2f);
	m_screen_last = currentScreen;
	//
	_selectedIndex = currentScreen-1;
	//
	execute();
}

void CustomComboBox::handleTouchEndPagePre()
{
	refreshLvBoxLabel();
}

void CustomComboBox::handleTouchEndPageNext()
{
	refreshLvBoxLabel();
}

void CustomComboBox::handleTouchEnd2Page()
{
	refreshLvBoxLabel();
}