#pragma once
#include "../../mvc/Proxy.h"
#include "socket/command/s1e/SCMD1ED.h"

class OnlineRewardProxy : public Proxy
{
public:
	OnlineRewardProxy();
	virtual ~OnlineRewardProxy();

public:
	void updateOLInfo(char * data);
	void updateADInfo(char * data);

public:
	struct Node 
	{
		int id;
		int num;
	};
	int _presentValue;
	int _addValue;
	std::vector<SCMD1ED::SCMD1EDNode> _goodsArray;
	
protected:
private:
};