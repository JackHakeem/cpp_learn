#ifndef _EnterPanel_H_
#define _EnterPanel_H_

#include "BaseType.h"
#include "model/tower/vo/TowerPanel1Vo.h"
using namespace cocos2d;

class EnterPanel : public CCLayer
{
public:
	EnterPanel();
	~EnterPanel();

public:

	virtual bool init();
	void updateInfo(TowerPanel1Vo* vo);
	void updateMyArea();
	void openTowerRank(CCObject* ojb);
	void updateBox(int area);
	void enableBox(int floor, bool hightlight);
	void takeRankAward(CCObject* ojb);
public:
	CCLabelTTF* _txtMyRank;
	CCLabelTTF* _txtTopRank;
	CCLabelTTF* _txtFreeNum;
	CCLabelTTF* _txtLastFloor;
	CCLabelTTF* _txtLevArea;
	CCLabelTTF* _txtFloorArea;

	int m_iPreRolelv;
	TowerPanel1Vo* m_pPanel1vo;
};

#endif