#pragma once

#include "BaseType.h"
class TextFieldTTF;
class CreateGuild:public LayerNode
{
public:
	CreateGuild();
	~CreateGuild();

	bool init();
	void clickOK(CCObject* pSender);
	void cancel(CCObject* pSender);
	void dispear(CCObject* pSender);
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
public:
	LayerNode* _container;
	TextFieldTTF* m_pTextField1;
};