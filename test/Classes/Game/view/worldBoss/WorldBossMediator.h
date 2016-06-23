#pragma  once
#include "../BaseMediator.h"

typedef long long Number;

class  SCMD2C9;
class  SCMD2C8;
class  SCMD2CE;
class  SCMD2CC;
class SCMD2C7;

class WorldBossMediator : public BaseMediator
{
public:
	WorldBossMediator();
	virtual ~WorldBossMediator();

	virtual void handleNotification( int M2Vcmd, char* data );

	enum
	{
		ENTER,
		QUIT,
		UPDATE_BOSS_INFO,
		UPDATE_PLAYER_INFO,
		UPDATE_OPEN_TIME,
		RELIVE,
		BOOST,
//		BATTLE_END,
	};

	void updateBossInfo(SCMD2C9 * data);
	void updatePlayerInfo(SCMD2C8 * data);
	void relive(SCMD2CE * data);
	void boost(SCMD2CC * data);
	void quit();

	void requestQuit();
	void requestRelive();
	void requestReborn();
	void requestGoldBoost();
	void requestPracBoost();

	void sockOpenTime(SCMD2C7 * data);
	void sockPlayerInfo(SCMD2C8 * data);
	void sockBossInfo(SCMD2C9 * data);
	void sockBoost(SCMD2CC * data);
	void sockRelive(SCMD2CE * data);

	void initView();
	void showWorldBossUI(bool var);
	void showDeathView(bool bVar);

	void updateOpenTime(SCMD2C7 *data);
	std::string getTimeStringByMili(Number time);

	void removeWorldBossScene();

public:
	/** 世界Boss活动剩余时间 0表示已结束 */
	int _restTime;
	/** 玩家复活剩余时间 0表示已复活*/
	int _reliveTime;
	/*
	QuitView * _quitView;
	BossHPView _bossHPView;
	DamageRankListView _dmgRKListView;
	DeathView _deathView;
	BoostView _boostView;
	*/
	bool _isLoaded;
	/** 初始化数据缓存 仅在第一次打开时有用*/
	//struct initinfo
	/** 战斗力加成 */
	int _powerUp;
	
	int _isInTime;

protected:
private:
};