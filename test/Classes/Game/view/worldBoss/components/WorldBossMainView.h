#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class WorldBossMainView : public CCLayer
{
public:
	WorldBossMainView();
	virtual ~WorldBossMainView();

	virtual bool init();

	void loadBoostView();
	void loadBossHPView();
	void loadDamageRankView();
	void loadDeathView();
	void loadQuitView();
	void loadShowRankListMenu();
	void loadChatMenu();
	void ShowRewordTips(bool bVar);

	void closeStep(ccTime dt);

	void onClickShowRankList(CCObject * pSender);
	void onClickChat(CCObject * pSender);
	void onClickCloseRewordTips(CCObject * pSender);

	enum VIEW_TAG
	{
		TAG_BoostView = 121,
		TAG_BossHPView,
		TAG_DamageView,
		TAG_DeathView,
		TAG_QuitView,
		TAG_ShowRank_Menu,
		TAG_Chat_Menu,
		TAG_RewordTips,
	};

	CCSize _winSize;
	int _timeCnt;

protected:
private:
};