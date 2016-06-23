#ifndef _DAILY_TASK_EX_PROXY_H_
#define _DAILY_TASK_EX_PROXY_H_
#include "mvc/Proxy.h"
#include "vo/DailyTaskExVo.h"
#include "socket/command/s42/SCMD421.h"
#include "socket/command/s42/SCMD423.h"
#include "socket/command/s42/SCMD425.h"
#include "socket/command/s42/SCMD427.h"
#include "socket/command/s42/SCMD42B.h"

class DailyTaskExProxy : public Proxy
{
public:
	DailyTaskExProxy();
	~DailyTaskExProxy(){};

	std::vector<DailyTaskExVo *> & getDailyTaskExList()
	{
		return _dailyTaskExList;
	}

	void onDailyTaskExChanged(SCMD421 *pPacket);
	void onDailyTaskExAccept(SCMD423 *pPacket);
	void onDailyTaskExSubmit(SCMD425 *pPacket);
	void onDailyTaskExProgress(SCMD427 *pPacket);
	void onDailyTaskExGiveup(SCMD42B *pPacket);
	int getRemainFreeRefreshCount() { return _remainFreeRefreshCount; };
	void setRemainFreeRefreshCount(int count) { _remainFreeRefreshCount = count;};
	int getRemainTaskCount() { return _remainTaskCount; };
	void setRemainTaskCount(int count) { _remainTaskCount = count;};
	bool getHasUnFinishTask() { return _hasUnFinishTask; }
private:
	bool _FinishTaskToast;
	bool _hasUnFinishTask;
	int _remainFreeRefreshCount;
	int _remainTaskCount;
	std::vector<DailyTaskExVo *> _dailyTaskExList;
};
#endif