#ifndef _BANKPROXY_H_
#define _BANKPROXY_H_

#include "mvc/Proxy.h"
#include "socket/command/s16/SCMD161.h"
#include "socket/command/s16/SCMD165.h"

class GoodsInfo;
class BankProxy: public Proxy
{
public:
	BankProxy();
	~BankProxy();

	void createList(char* data);
	void updateGoods(char* data);
	
	void handleGoodList(std::list<SCMD161_163_165_167Node>* arr);
	void updateGoodList(SCMD161_163_165_167Node* goodInfo);
	GoodsInfo* goodsInfo(int32 sitNum);
	int32 getSpaceGridNum();
	void setDynamicInfo( uint grid );
public:
	std::map<int32, GoodsInfo*> _goodsList;
	int32 _goodsNumber;
	int32 _noEmpty;
	bool _isCreate;
	
};

#endif