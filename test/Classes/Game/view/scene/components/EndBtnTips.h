#pragma once

#include "BaseType.h"

class CCUIBackground;

class EndBtnTips:public LayerNode
{
public:

	EndBtnTips();
	~EndBtnTips();

	bool init();
	void confirm(CCObject* pSender);
	void cancel(CCObject* pSender);
	void close(CCObject* pSender);
public:

public:

};