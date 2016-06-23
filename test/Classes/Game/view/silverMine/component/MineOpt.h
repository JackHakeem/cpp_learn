#pragma once

#include "BaseType.h"
class MineView;
class MineOpt:public LayerNode
{
public:
	

	MineOpt();
	~MineOpt();

	bool init(MineView* pContainer);
	void updateMineInfo(int mineId, int onMine);
	int getCapacity(int level);
	void setDescription();
	std::string getFlourish(int online, int capacity);
	void digClick(CCObject* pSender);
	void digClick2(CCObject* pSender);
	void digClick3(CCObject* pSender);
	void searchClick(CCObject* pSender);
	void setDigBtnEnable(bool value);
	void setSearchBtnEnable(bool value);
public:
	int _capacity;  // 容量
	int _online;   // 当前人数 
	CCLabelTTF* _txtPercent;
	MineView* pContainer;
	CCMenuItemSprite* _btnDig;// 挖矿
	CCMenuItemSprite* _btnDig2;//// 黄金挖矿 aurum
	//CCMenuItemSprite* _btnDig3;  // 白金挖矿 platina 
	CCMenuItemSprite* _btnSearch;// 查 1一种特殊的令牌，一直存在 2,10金币可直接使用 3,不参与其他令牌的叠加 4,可查看一格范围内银矿上的玩家数量

};
