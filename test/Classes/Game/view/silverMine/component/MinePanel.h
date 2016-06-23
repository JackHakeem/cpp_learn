#pragma once

#include "BaseType.h"
#include "model/silverMine/vo/SilverMineVo.h"

class MineItem;
class MineView;
class MinePanel:public LayerNode
{
public:
	enum
	{
		Z_campMc,
	};

	enum
	{
		TAG_campMc,
	};

	enum
	{
		STATE_IDLE,
		STATE_MOVING,
	};

	MinePanel();
	~MinePanel();

	bool init(LayerNode* layer, MineView* pContainer);
	int getcurCampID();
	int getcurMineID();
	void setMyCamp(int campId);
	void setMyMine(int mineID);
	void move2mine(int mineId, bool imm = false);
	void step(ccTime dt);
	void useToken(int type);
	void updateMinePanel(std::list<SilverMineVo>& mines);
public:
	LayerNode* _campMc;
	int _curCampID;// 当前所在组
	int _curMineID; //当前所在矿ID
	float _timeCounter;
	int m_stateMC;
	bool m_actionImm;
	std::map<int, MineItem*> _itemDic;
	MineItem* _curItem;// 当前Item
	MineView* pContainer;
	LayerNode* m_parlayer;
};