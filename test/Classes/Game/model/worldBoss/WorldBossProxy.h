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
	/** ������������Boss�ذ� Player��Ϣ */
	void handleBossInfo(SCMD2C9 * data);
	/** ������������Boss�ذ� ����Boss���ʼʱ�� */
	void handlePlayerInfo(SCMD2C8 * data);
	/** ������������Boss�ذ� ������ */
	void handleOpenTime(SCMD2C7 * data);
	/** ������������Boss�ذ� ������ */
	void handleRelive(SCMD2CE * data);
	/** ������������Boss�ذ� ������ */
	void handleBoost(SCMD2CC * data);
	// ���õ�ǰ��ͼID
	void setCurMapID(int mapID);
	/** ��ǰ�Ƿ���Խ�������Boss��ͼ */
	bool canEnter();
	/** ��ȡ�ۼƽ��� */
	std::list<SCMD2C8::SCMD2C8Node> * getAwardList();
	/** ��ȡĬ�ϵ�ͼID */
	int getMapID();
	/** ��ȡ����Boss��ͼ����ʱ�� */
	int getTime();

	void handleQuit();

public:
	static const int _worldBossMapID = 1208;
	/** ����Boss�˺��� */
	std::list<SCMD2C9::SCMD2C9Node> _dmgRKList;
	/** ����Boss����ʱ�� */
	int _worldBossOpTime;
	/** �������:����CD,�������,�˺��� */
	WBPlayerInfoVo * _playerInfo;
	/** Boss����:��ǰѪ��,���Ѫ�� */
	BossInfoVo * _bossInfo;
	/** ��ǰ��ͼID 0��ʾδ��ʼ��(��һ�û��ת����ͼ)*/
	int _curMapID;
	/** �Ƿ��ڻ�� 0���� 1��*/
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