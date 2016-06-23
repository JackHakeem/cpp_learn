#pragma once

#include "mvc/Mediator.h"
#include "utils/Timer.h"

class PoolView;
class ReserveDepot;
class WashPanel;
class NumSelectBox;
class SCMD401;
class SCMD403;
class SCMD405;
class SCMD407;
class SCMD409;
class SCMD40B;
class SCMD40D;
class GameDispatcher;
class RoleManage;
class EggProxy;

class EggMediator : public Mediator
{
public:
	enum
	{
		/** 许愿奖励历史记录 */
		REWARD_HISTORY=3500,
		/** 心愿宝箱里的蛋蛋信息*/
		DEPOT_INFO,
		
		/** 许愿 */
		PLEGE_EGG,
		/** 开蛋 */
		OPEN_EGG,
		/** 洗礼 */
		WASH_EGG,
		/** 拾取 */
		GET_EGG,
		/** 一键拾取 */
		GET_ALL,
	};

	EggMediator();
	~EggMediator();

public:
	void initEvent();
	virtual void handleNotification(int M2Vcmd, char* data);
	void cmdHistoryHandler(SCMD401* param);
	void cmdPlegeHandler(SCMD403* param);
	void cmdOpenHandler(SCMD405* param);
	void cmdPickHandler(SCMD407* param);
	void cmdWashHandler(SCMD409* param);
	void cmdDepotHandler(SCMD40B* param);
	void cmdPickAllHandler(SCMD40D* param);

	void uiLoadHandler();
	void openPoolView();
	void initDepotInfo();
	void initRewardInfo();
	void openDepot(CCNode* pSender, void* data);
	void plegeEggHandler(CCNode* pSender, void* data);
	void openWashPanel(int name, char* data);
	void openEggHandler(CCNode* pSender, void* data);
	void washEggHandler(CCNode* pSender, void* data);
	void getEggHandler(CCNode* pSender, void* data);
	void getAllHandler(CCNode* pSender, void* data);
	void changeGold(CCObject* pSender, void* data);
	void openNumSelectBox(CCNode* pSender, void* data);
public:
	/** 许愿池 */
	PoolView* _poolView;
	/** 心愿宝箱 */
	ReserveDepot* _depotView;
	/** 洗礼面板 */
	WashPanel* _washPanel;
	/** 拾取数量选择框 */
	NumSelectBox* _selectBox;
	
	GameDispatcher* _dispatcher;
	RoleManage* _roleManage;

	EggProxy* _eggProxy;
};
