#ifndef _BANKMEDIATOR_H_
#define _BANKMEDIATOR_H_

#include "mvc/Mediator.h"
#include "socket/command/s16/SCMD163.h"

class BankProxy;
class BankView;
class GameDispatcher;
class BankMediator:public Mediator
{
public:
	enum 
	{
		CREATE_LIST = 0,
		BANK_ITEM_UPDATE,
		BANK_ITEM_TIP_UPDATE,
		BANK_CLOSE,
	};
public:
	BankMediator();
public:
	
	virtual void handleNotification(int M2Vcmd, char* data);
	void createList();
	void openBank();
	void bankPop();
	void initWorldBank(char* data);
	bool isBankViewPop();
	void bankUpdate(char* arr);
	void packChange(CCNode* n, void* data);
	void sockBankItemUpdate(std::list<SCMD161_163_165_167Node>*	param);
	void bankToBag(int32 sitGrid);
	void bankPopHandle(CCNode* n, void* data);
	void onAddGridHandler(CCNode* n, void* data);
	void startListener();
	void updateTip( char* data );
	/*

	void sockBagItemUpdate(std::list<SCMD161_163_165_167Node>*	param);
	void deleteGoodsHandle(int32 sit);
	*/
public:
	BankView* _bankView; 
	BankProxy* _bankProxy;

	GameDispatcher* _dispatcher;
};

#endif