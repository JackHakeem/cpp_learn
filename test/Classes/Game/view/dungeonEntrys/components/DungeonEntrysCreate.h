#ifndef HLQS_DungeonEntrysCreate_H_
#define HLQS_DungeonEntrysCreate_H_
#include "CCUIPartialScrollView.h"
#include "utils/flash/CCIEventDispatcher.h"

USING_NS_CC;

class DungeonEntrysCreate: public CCUIPartialScrollView, public CCIEventDispatcher
{
public:
	DungeonEntrysCreate();
	~DungeonEntrysCreate();
	DungeonEntrysCreate(const CCRect& mRect);
	void addDungeonEntries();
	void onClickStoryEnterBtn(CCObject* pSender);
	void onClickChallengeEnterBtn(CCObject* pSender);
	void onClickLairEnterBtn(CCObject* pSender);
	void onClickWorldBossEnterBtn(CCObject* pSender);
	void onClickSilverMineEnterBtn(CCObject* pSender);
	void onClickDragonTowerEnterBtn(CCObject* pSender);
    void onClickRankingEnterBtn(CCObject* pSender);
<<<<<<< .mine
	void onClickCampFightEnterBtn(CCObject* pSender);
=======
	void onClickCampFightEnterBtn(CCObject* pSender);
	void onClickGongEnterBtn(CCObject* pSender);
	virtual void moveToPreviousPage();
	virtual void moveToNextPage();

>>>>>>> .r5911
public:
	enum
	{
		TAG_WorldBossTime = 1021,
		TAG_SilverMineTime = 1021,
		TAG_GongTime = 1022,
	};

	CCMenuItemSprite * _btStoryEnter;
	CCMenuItemSprite * _btChallengeEnter;
	CCMenuItemSprite * btDragonTowerEnter;
	CCMenuItemSprite * btWorldBossEnter;
};

#endif
