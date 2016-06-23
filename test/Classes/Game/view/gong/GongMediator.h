#pragma once


#include "BaseType.h"
#include "mvc/Mediator.h"

class SCMD446;
class SCMD44A;
class GongRankingView;
class GongMBView;
class GongMediator:public Mediator
{
public:
	GongMediator();
	~GongMediator(){}
	
	void openRankingView();
	void updateRankingView(SCMD446* packet);

	void openMBView();	
	void updateMBView(SCMD44A* packet);
public:
	GongRankingView* m_pRankingView;
	GongMBView* m_pMBView;
};
