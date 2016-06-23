#ifndef _FIGHT_END_H_
#define _FIGHT_END_H_

#include "cocos2d.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s3b/SCMD3B1.h"
#include "model/player/vo/PlayerInfoVo.h"

USING_NS_CC;

class FightEnd : public CCLayer
{
public:
	enum 
	{
		REPLAY = 0,
		COPY_REPORT,
		RESULT_CLICK
	};

	FightEnd(int result, SCMD13D *pReward, SCMD3B1 *pReport, int style);
	//FightEnd(int result, SCMD13D reward, SCMD3B1 report, int style);
	~FightEnd();

	bool virtual init();

	CCLayer *createExpLayer();
	CCLayer *createExpLayerCell(CCPoint point, SCMD13D::SCMD13DNode2 node);
	CCLabelTTF *buildRewards();

	void copyReport(CCObject *pObject);
	void replay(CCObject *pObject);
	void closePanel(CCObject *pObject);
    
    bool isLenOverflow(std::string str , const int CNwordnum , int &nbyteCnt);
public:
	int _result;
	int _style;
	SCMD13D *_pReward;
	SCMD3B1 *_pReport;

private:
	int _goodId;
	int _goodNum;
};
#endif