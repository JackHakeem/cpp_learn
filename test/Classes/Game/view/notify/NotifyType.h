#pragma once

class NotifyType
{
public:
	NotifyType(){};
	~NotifyType(){};

	enum
	{
		NType_Mail,
		NType_Strength,
		NType_WorldBoss,
		NType_Sliver,
		NType_Arena,
		NType_Levy,
		NType_Gift,
		NType_Train,
		NType_Appoint,
		NType_DailyTask,
		NType_Trader,
	};
protected:
private:
};