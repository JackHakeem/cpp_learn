#pragma once

#include "BaseType.h"

class ArenaUI;
class SCMD36E;
class CardList:public LayerNode
{
public:
	enum
	{
		CardListZ_btn0,
	};

	enum
	{
		CardListTAG_btn0,
	};

	CardList();
	~CardList();

	bool initWithParam(ArenaUI* pContainer);
	void takeAward(CCObject* pSender);
	void update(SCMD36E* data);
public:
	ArenaUI* _pContainer;
};