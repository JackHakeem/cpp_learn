#ifndef _RANKINGMEDIATOR_H_
#define _RANKINGMEDIATOR_H_

#include "view/BaseMediator.h"
#include "components/RankingView.h"
#include "socket/command/s25/SCMD25C.h"
#include "socket/command/s25/SCMD25E.h"

class RankingMediator : public BaseMediator
{
public:
	enum
	{
		UPDATE_RANK_LIST,
		UPDATE_EQUIPMENTS,
		UPDATE_MY_RANK,
		//UPDATE_FIGURE_DATA,
	};
    RankingMediator();
    ~RankingMediator();
public:
    virtual void handleNotification(int M2Vcmd, char* data);

    void popRankingView();

	/**=====处理服务器返回结果====**/
	void updateRankingList(SCMD25C* packet);
	void updateEuiqpments(SCMD25E* packet);

//	void updateEquipsInfo(SCMD25E* packet);
//
//	/**=====处理视图组件派发的事件=====**/
//private:
//	void onItemSelected(int position);
	//	void onTypeChange(int type);
	RankingView* _pRankingView;
private:
	void startViewListener();
	void stopViewListener();

	void onRequestRankingList(cocos2d::CCNode* target, void* data);
	void onRequestEquipInfo(cocos2d::CCNode* target, void* data);
private:

};

#endif
