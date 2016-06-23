#pragma once

#include "BaseType.h"
#include "model/silverMine/vo/SilverMineVo.h"
#include "socket/command/s36/SCMD367Node.h"

class MinePanel;
class MineBg;
class MineOpt;
class MineInfo;
class MineRank;

class MineView:public LayerNode
{
public:
	enum BGLAYEREZNUM
	{
		bglayerZ_bg=0,
		bglayerZ_mine,
	};

	enum BGLAYERETAGNUM
	{
		bglayerTAG_mine_0=0,
		bglayerTAG_mine_36=36,
	};

	enum
	{
		Z_bgLayer,
		Z_mineBg,
		Z_minePanel,	
		Z_mineItem,
		
		Z_mineOpt,
		Z_mineInfo,
		Z_title,
		Z_campMc,
	};

	enum
	{
		TAG_bgLayer,
		TAG_mineBg,
		TAG_minePanel,
		TAG_campMc,
		TAG_mineOpt,
		TAG_mineInfo,
	};

public:
	MineView();
	~MineView();
	bool init();

	void updatePracInsTips(int cost);
	void setMyCamp(int campID);
	void setMyMine(int mineID);
	int getcurMineID();
	int getcurCampID();
	int whichCampHome(int mineID);
	void setDigEnable(bool value);
	void updateMinePanel(std::list<SilverMineVo>& mines);
	void updateMineInfo(int mineId, int onMine);
	void updateMoveCD(uint moveCD, bool inCD);
	void updateDigCD(uint digCD, bool inCD);
	void updateSilver(int silver);
	void onClose(CCObject* pSender);
	int getMineIDByCamp(int campID);
	void updateRank(std::list<SCMD367Node>& arr);
	void updateAttPlus(int plus);
	void updateDefPlus(int plus);
	void loadChatMenu();
	void onClickChat(CCObject * pSender);
public:		
	MinePanel* _minePanel;
	LayerNode* _pContainer;
	LayerNode* _bgLayer;
	MineBg* _mineBg;
	MineOpt* _mineOpt;
	MineInfo* _mineInfo;
	CCMenuItemSprite* _btnReturn;
	std::list<SCMD367Node> m_arr;
	uint m_silver_forRank;
	
public:
	CC_PROPERTY(int, _tokenType, TokenType)
};