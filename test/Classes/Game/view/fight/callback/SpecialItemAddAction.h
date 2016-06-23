#pragma once

#include "BaseType.h"
#include "view/fight/interfaces/BaseAction.h"
#include "socket/command/s16/SCMD16D.h"
#include "utils/flash/CCIEventDispatcher.h"

class PlayerInfoVo;
class GoodsBasic;
class GameDispatcher;
class SpecialItemAddAction:public BaseAction, public CCIEventDispatcher
{
public:
	SpecialItemAddAction();
	~SpecialItemAddAction();

	bool init(SCMD16D* param);

	virtual void doAction();
	
	virtual	void addAction(IAction* action){};
		
	virtual	void delAction(IAction* action){};

	bool checkCanEquip(PlayerInfoVo* info, GoodsBasic* goodBasic);
	void autoPutOnEquipment(int mercId, int sitNum);
	void openGoodsById(CCObject* pSender);

	void equipOnCallback(CCObject * pSender);

public:
	GameDispatcher* _dispatcher;
//	SCMD16D* _param;


	int8 a_from;
	int16 b_goodsId;
	int8 c_num;
	int8 d_sitGrid;


	int _param_goodId;

};