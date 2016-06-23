#pragma once

#include "BaseType.h"

class TowerPageNav:public LayerNode
{
public:
	enum
	{
		PAGE_CHANGE,
	};
	enum
	{
		TowerPageNavTAG_page,
	};
	TowerPageNav();
	~TowerPageNav();

	bool init();
	void onPrevHandler(CCObject* pSender);
	void onNextHandler(CCObject* pSender);
	void setPage(int max=1, int index=1);
	void updateText();
public:
	int _maxPage;
	int _curPage;
};