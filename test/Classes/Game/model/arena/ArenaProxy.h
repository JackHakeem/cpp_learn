
#ifndef _ARENAPROXY_H_
#define _ARENAPROXY_H_

#include "mvc/Proxy.h"
#include "socket/command/s36/SCMD361.h"
#include "socket/command/s39/SCMD39A.h"
#include "socket/command/s39/SCMD39B.h"
#include "socket/command/s39/SCMD39C.h"
#include "vo/ArenaDareVo.h"
#include "vo/RingVo.h"

class CCMD134;
class SCMD363;
class SCMD38C;
class SCMD287;
class SCMD285;
class SCMD36E;
class HeroRankView;
class ArenaUI;
class ArenaProxy: public Proxy
{
public:
	ArenaProxy();
	~ArenaProxy();

	//void PVPQualifying(SCMD361* data);
	void PVPQualifyingResult(SCMD39A* data);
	void PVPArenacontestResult(SCMD39B* data);
//	void PVPArenacontestList(SCMD39C* data);.
	void reqPVPWinStarList();
	void reqHeroRankList();
	void doArenaInfo(SCMD361* param);
	void setarenaUI(ArenaUI* ui);
	void startArenaEvent();
	void startArenaSocket();
	void onPkArena(CCNode* n, void* data);
	void onClickLinkReport(CCNode* n, void* data);
	void onTakeAward(CCNode* n, void* data);
	void onGiftPackage(CCNode* n, void* data);
	void onBuy(CCNode* n, void* data);
	void onCardFinish(CCNode* n, void* data);
	void reqArenaInfo();
	void reqHeroInfo();
	void doArenaPkRes(SCMD363* param);
	void doArenaBuyRes(SCMD38C* param);
	void doGiftPackage(SCMD287* param);
	void startHeroEvent();
	void onAddFriend();
	void doHeroInfo(SCMD285* param);
	void doArenaAwardRes(SCMD36E* param);
	void setheroUI(HeroRankView* ui);
	void onResetOpps(CCNode* n, void* data); //add by hwj 
public:
	int32 _Row_number;	//��ʤ��
	int32 _Arena_lev;	//��λ���ȼ�
	std::list<int32> _StartDic;	//��ʤ����  0 δ����  1ʤ��   2 ʧ��
	std::list<ArenaDareVo> _ArenaList;	//��������λ���б�  
	std::map<int32, RingVo> _RingList;	//����ս��̨��              ��̨����������
	std::map<int32, std::map<int32, RingVo> >  _RingAllList;	//��̨���б�                 ��̨����������
	int32 _meRange;	// ������������
	int32 _meRank;	// �������� 
	int32 _giftNum;	// �����
	bool isOpen;	// ������/��̨�Ƿ�� 
	ArenaUI* _arenaUI;
	HeroRankView* _heroRankView;  // Ӣ�۰�UI
	std::map<int, std::vector<int> > _pvpReportDic; 

};

#endif