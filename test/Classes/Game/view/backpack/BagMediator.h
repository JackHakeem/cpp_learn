#ifndef _BAGMEDIATOR_H_
#define _BAGMEDIATOR_H_

#include "mvc/Mediator.h"
#include "./components/BagView.h"
#include "socket/command/s16/SCMD161.h"

class BagProxy;
class SCMD16D;
class GameDispatcher;
class BagMediator:public Mediator
{
public:
	enum 
	{
		CREATE_LIST = 0,
		BAG_ITEM_UPDATE,
		BAG_ITEM_TIP_UPDATE,
		OPEN_ID_GOOD,
	};
public:
	BagMediator();
public:

	virtual void handleNotification(int M2Vcmd, char* data);

	void initWorldBag(char* data);
	void createList();

	bool isBagViewPop();
	void bagUpdate(char* arr);
	void openBag();
	void bagPop();
	void packChange(CCNode* n, void* data);//int32 UseType, int32 oldGrid, int32 newGrid
	void sockBagItemUpdate(std::list<SCMD161_163_165_167Node>*	param);
	void deleteGoodsHandle(int32 sit);
	void bagToBank(int32 sitGrid);
	void onSpecialItemAdd(SCMD16D* param);
	void onAddGridHandler(CCNode* n, void* data);
	void onSortHandler(CCNode* n, void* data);
	void bagPopHandle(CCNode* n, void* data);
	void startListener();
	void confirmToDel(int32 sit);
	bool checkMerc(std::string name);
	void updateTip( char* data );
	void openGoodsById(char* datagoodId);
public:
	BagView* _bagView;
	BagProxy* _bagProxy;

	GameDispatcher* _dispatcher;
};

#endif