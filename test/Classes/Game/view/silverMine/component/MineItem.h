#pragma once

#include "BaseType.h"
#include "model/silverMine/vo/BasicMineVo.h"
#include "model/silverMine/vo/SilverMineVo.h"

class MineView;
class MineItem:public LayerNode
{
public:
	/*static const int NONADJACENT = -1;
	static const int ADJACENT_MOVE = 0;
	static const int ADJACENT_PK = 1;
				 
	static const int ILLEGAL_TYPE = -1;
	static const int MOVE_TYPE = 0;
	static const int PK_TYPE = 1;
 	static const int SPEED_TYPE = 2;
	static const int RAID_TYPE = 3;
 	static const int HARASS_TYPE = 4;
	static const int SEARCH_TYPE = 5;*/
	//int NONADJACENT;
	//int ADJACENT_MOVE;
	//int ADJACENT_PK;
	//
	//int ILLEGAL_TYPE;
	//int MOVE_TYPE;
	//int PK_TYPE;
 //	int SPEED_TYPE;
	//int RAID_TYPE;
 //	int HARASS_TYPE;
	//int SEARCH_TYPE;

	MineItem();
	~MineItem();

	bool init(MineView* pContainer, int mineID);
	void updateMineVo(SilverMineVo mineVo);
	int getFrameByCampId(int campId);
	void itemClick(CCObject* pSender);
	void setOperateType(int operateType);
	void setMoveEnable(bool value);
	void setPkEnable(bool value);
	void setMouseEnable(bool value);
	void useToken(int type);
	void tokenRaid();
	void tokenHarass();
	void tokenSpeed();
	void tokenSearch();
	int testNeighour(SilverMineVo testMineVo);
	bool isNeighbour(BasicMineVo mineVo1, BasicMineVo mineVo2);
	SilverMineVo getmineVo();

public:
	MineView* pContainer;
	int _mineID;
	BasicMineVo _basicMineVo;
	SilverMineVo _mineVo; // 动态信息
	SpriteNode* _doubleMc;
	SpriteNode* _pkMc;
	SpriteNode* _moveMc;
	SpriteNode* _frame;
	CCMenuItemSprite* _handleBtn;
	int _operateType;	// 操作类型 
};