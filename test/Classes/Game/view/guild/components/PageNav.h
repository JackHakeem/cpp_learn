#pragma once

#include "BaseType.h"

class PageNav:public LayerNode
{
public:
	enum
	{
		PAGE_CHANGE,
	};
	enum
	{
		PageNavTAG_page,
	};
	PageNav();
	~PageNav();

	bool init();
	void onPrevHandler(CCObject* pSender);
	void onNextHandler(CCObject* pSender);
	void setPage(int max=1, int index=1);
	void updateText();
public:
	int _maxPage;
	int _curPage;
};