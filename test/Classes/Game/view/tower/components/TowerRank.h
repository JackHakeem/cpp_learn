#ifndef _TowerRank_H_
#define _TowerRank_H_

#include "BaseType.h"
#include "model/tower/vo/TowerRankListVo.h"
#include "ListContainer.h"
#include "TowerPageNav.h"

class TowerRank : public LayerNode
{
public:
	enum
	{
		TowerRankZ_bg1,

	};
	enum
	{
		TowerRankTAG_bg1,
	};

	enum
	{
		OPEN_TOWER_RANK,
		PAGE_CHANGE,
		RANK_ME,
	};

public:
	TowerRank();
	~TowerRank(){};

public:

	bool init();
public:
	void initView();
	//void registerWithTouchDispatcher( void );
	virtual void onEnter();
	virtual void onExit();

	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void updateRanking( TowerRankListVo* vo );
	void dispear(CCObject* pSender);
	void rankMe(CCObject* obj);
	void rankConfirm(CCObject* boj);
	void rankConfirm2(CCObject* boj);
	void rankCancel(CCObject* boj);
	void checkClickSelf( TowerRankItemVo* itemVo );
	void resetTouchDispatcher();
	bool needFight();
public:
	LayerNode* _container;

	CCLabelTTF* _txtBest;
	CCLabelTTF* _txtLast;
	CCLabelTTF* _txtMyRecord;
	CCLabelTTF* _restCountLabel;

	CCMenuItemSprite *_pStrengUpItem;
	CCMenu* _btnStrengUp;

	TowerPageNav* _pageNav;
	ListContainer* _listContainer;
	TowerRankListVo* _rankVo;
	int _preRank;

	int m_rankParam;
	bool leaveNameFighting;
	bool m_bFirstOpen;
	bool m_bClickRank;
	bool m_bRnkNeedFight;
};

#endif