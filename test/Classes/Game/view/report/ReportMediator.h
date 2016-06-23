#ifndef _ReportMediator_H_
#define _ReportMediator_H_

#include "mvc/Mediator.h"
#include "../BaseMediator.h"
#include "socket/command/s14/SCMD140.h"
#include "socket/command/s13/SCMD137.h"
#include "components/MapAwardPanel.h"
#include "components/PassGiftSkin.h"

class ReportView;

class ReportMediator : public BaseMediator{
public:
	ReportMediator();

	enum 
	{
		PLAY_REPORT,
		TAKE_AWRAD,
		INIT_PROGRESS
	};
	
public:
	virtual void handleNotification(int M2Vcmd, char* data);
	//void dungeonAward( SCMD376& param );
	void dungeonAward( SCMD140& param );
	void updateHonorAwardComplete( int honorId );
	void takeAward( int honorId );
	void openAward( int awardId );
	void openAwardWithoutGift();

	//Begin chenjian 20121012
    void showReportView();
	void loadReportSource(CCNode *pNode, void *pData);
    void sendApplyReportData(const int16& mapId);
	void onApplyReportList(CCNode *pNode, void *pData);
	void initLayerTitleStar();
    void updateReportData();
	void sockReportList(SCMD137* pPacket);

	void onSelectReport(CCNode *pNode, void *pData);
	//End chenjian 20121012
public:
	MapAwardPanel* _arward;
	PassGiftSkin* _passGift;
	//Begin chenjian 20121012
    ReportView* _reportView;
private:
	void reportWaitTime();
	//End chenjian 20121012
};

extern ReportMediator* g_pReportMediator;

#endif
