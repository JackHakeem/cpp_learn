#include "UICheckButton.h"


UICheckButton * UICheckButton::menuWithItems(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	UICheckButton *pRet = new UICheckButton();
	if (pRet && pRet->initWithItems(item, args))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet)
		return NULL;
}

void UICheckButton::setIsCheck( bool isCheck )
{
	CCMenuItem *pChildren = (CCMenuItem *)m_pChildren->objectAtIndex(0);
	if(!pChildren)
	{
		return;
	}

	if(isCheck)
	{
		if(!pChildren->getIsSelected())
		{
			pChildren->selected();
		}
	}
	else
	{
		if(pChildren->getIsSelected())
		{
			pChildren->unselected();
		}
	}
}
