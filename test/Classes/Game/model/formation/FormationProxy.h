#ifndef _FORMATIONPROXY_H_
#define _FORMATIONPROXY_H_
 #include "mvc/Proxy.h"
#include "model/player/vo/PlayerInfoVo.h"
class FormationProxy : public Proxy
{
public:
	int _teamFormation;
	std::map <int, int> _teamMemberMap;
	bool isTeamCreate;

public:
	FormationProxy();
	~FormationProxy();

	void updateTeamMemberInfo(int formation , int sitGrid ,PlayerInfoVo* info);
	void changeTeamMemberSit(int formation ,int  grid1 , int grid2 );
};


#endif