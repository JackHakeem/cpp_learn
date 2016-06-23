#pragma once

#include "BaseType.h"
class TextFieldTTF;
class GuildInfoVo;
class GuildEditView:public LayerNode
{
public:
	GuildEditView();
	~GuildEditView();

	bool init(GuildInfoVo* guildInfo);
	void clickOK(CCObject* pSender);
	void cancel(CCObject* pSender);
	void dispear(CCObject* pSender);
public:
	LayerNode* _container;
	TextFieldTTF* m_pTextField1;
	TextFieldTTF* m_pTextField2;
	TextFieldTTF* m_pTextField3;

};