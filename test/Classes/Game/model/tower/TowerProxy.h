#ifndef _TowerProxy_H_
#define _TowerProxy_H_

#include "mvc/Proxy.h"
#include "vo/TowerPanel1Vo.h"
#include "vo/TowerPanel2Vo.h"
#include "vo/TowerRankListVo.h"

class TowerProxy: public Proxy
{
public:
	TowerProxy();
	~TowerProxy();
	TowerPanel1Vo* getpanel1Vo();
	void setpanel1Vo(TowerPanel1Vo* value);
	TowerPanel2Vo* getpanel2Vo();
	void setpanel2Vo(TowerPanel2Vo* value);
	TowerRankListVo* getrankVo();
	void setrankVo(TowerRankListVo* value);

public:
	TowerPanel1Vo* _panel1Vo;
	TowerPanel2Vo* _panel2Vo;
	TowerRankListVo* _rankVo;
	int numFree;
	int numPay;
	bool waitFightEnd;
	bool showLottery;

};

#endif