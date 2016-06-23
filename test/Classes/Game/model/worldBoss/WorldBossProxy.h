#pragma once
#include "../../mvc/Proxy.h"
#include "../../socket/command/s2c/SCMD2C9.h"
#include "../../socket/command/s2c/SCMD2C8.h"

class SCMD2C7;
class SCMD2CC;
class SCMD2CE;
class WBPlayerInfoVo;
class BossInfoVo;

class WorldBossProxy : public Proxy
{
public:
	WorldBossProxy();
	virtual ~WorldBossProxy();

public:
	/** 处理服务端世界Boss回包 Player信息 */
	void handleBossInfo(SCMD2C9 * data);
	/** 处理服务端世界Boss回包 世界Boss活动开始时间 */
	void handlePlayerInfo(SCMD2C8 * data);
	/** 处理服务端世界Boss回包 复活结果 */
	void handleOpenTime(SCMD2C7 * data);
	/** 处理服务端世界Boss回包 复活结果 */
	void handleRelive(SCMD2CE * data);
	/** 处理服务端世界Boss回包 鼓舞结果 */
	void handleBoost(SCMD2CC * data);
	// 设置当前地图ID
	void setCurMapID(int mapID);
	/** 当前是否可以进入世界Boss地图 */
	bool canEnter();
	/** 获取累计奖励 */
	std::list<SCMD2C8::SCMD2C8Node> * getAwardList();
	/** 获取默认地图ID */
	int getMapID();
	/** 获取世界Boss地图开启时间 */
	int getTime();

	void handleQuit();

public:
	static const int _worldBossMapID = 1208;
	/** 世界Boss伤害榜 */
	std::list<SCMD2C9::SCMD2C9Node> _dmgRKList;
	/** 世界Boss开启时间 */
	int _worldBossOpTime;
	/** 玩家数据:死亡CD,鼓舞次数,伤害量 */
	WBPlayerInfoVo * _playerInfo;
	/** Boss数据:当前血量,最大血量 */
	BossInfoVo * _bossInfo;
	/** 当前地图ID 0表示未初始化(玩家还没跳转过地图)*/
	int _curMapID;
	/** 是否在活动中 0不是 1是*/
	uint8 _isInTime;

	struct INITInfo
	{
		SCMD2C8 cmd2c8;
		SCMD2C9 cmd2c9;
		int wbOpTime;
	};

protected:
private:
};