#ifndef _RecruitProxy_H_
#define _RecruitProxy_H_

#include "mvc/Proxy.h"
#include "utils/Timer.h"
#include "model/recruit/vo/RecruitInfo.h"

class DismissVo;
class RookieVo;
class PlayerInfoVo;

class RecruitProxy: public Proxy
{
public:
	RecruitProxy();
	~RecruitProxy();

	void initRookieList( vector<RookieVo*> list );
	void initDismissList( vector<DismissVo*> list );
	void cleanRecruitList();
	void saveDismissedMerc( PlayerInfoVo* playerInfoVo );
	void dismissMerc( int mercId = 0 );
	DismissVo* getDismissVoByMercId( int mercId );
	void recruitMerc( int id );
	Number getRecruitSilver( int mercId );
	vector<RecruitInfo*> recruitList();
	vector<RecruitInfo> fameList();
	vector<RecruitInfo> storyList();
	bool hasData();
	bool hasFameDate();

public:
	map< int, DismissVo* >_dismissDic;
	vector<RecruitInfo*> _storyList;
	vector<RecruitInfo*> _fameList;

	//private var _rookieDic:Dictionary = new Dictionary;
};

#endif