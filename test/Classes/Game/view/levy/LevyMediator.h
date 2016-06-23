#ifndef _LevyMediator_H_
#define _LevyMediator_H_

#include "mvc/Mediator.h"
#include "model/player/vo/LevyInfoVo.h"

class LevyView;
class GoldLevyPanel;
class SCMD323;
class SCMD321;
class SCMD324;

class LevyMediator:public Mediator
{
public:
	enum
	{
		OPEN_GOLD_LEVY = 0,
	};
public:
	LevyMediator();
	~LevyMediator();
	void loadReportSource( CCNode* n, void* data );
	void showGoldLevy( CCNode* n, void* data );
	void goldPop();
	void initHandler();
	void doSomeMath( int uniteNum, int starNum );
	void levyRequestHandler( CCNode* n, void* data );
	void levyInitHandler( SCMD323* param );
	void levyResultHandler( SCMD321* param );
	string note( uint type );
	void guildImpose( SCMD324* param );

public:
	LevyView* _levyView;
	uint _reward;
	uint _levyNum;
	int _uniteNum;        //公会等级
	int _starNum;         //星星数
	bool firstOpen;
	int _crysEarthLev;
	int _roleLev;
	int _crysEfc;
	int _earthEfc;
	LevyInfoVo* _levyInfo;
	GoldLevyPanel* _goldPanel;
	int _tmpRest;

	int m_iPreRoleLev;
};

extern LevyMediator* g_pLevyMediator;
#endif