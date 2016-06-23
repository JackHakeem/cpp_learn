#ifndef _CONFIRM_H_
#define _CONFIRM_H_

#include "BaseType.h"

USING_NS_CC;

class Alert;
class TextInputConfirm:public LayerNode
{
public:
	TextInputConfirm();
	~TextInputConfirm();
	bool initWithParam(std::string str, CCObject* target, SEL_MenuHandler selector, SEL_MenuHandler selector2);
	void handleCancel(CCObject* pSender);
	const char* getString();
public:
	Alert* m_alert;
};

#endif