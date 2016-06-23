#ifndef _FORMATIONMEDIATOR_H_
#define _FORMATIONMEDIATOR_H_
#include "mvc/Mediator.h"
#include "view/formation/components/FormationView.h"


class FormationMediator : public Mediator
{
public:
	enum 
	{
		MEMBER_CHANGE_SUCCESS,
		TEAM_MEMBER_INIT,
		TEAM_MEMBER_UPDATE,
		TEAM_MEMBER_CHANGE_SIT,
		UPDATE_FORMATION_LIST
	};

	FormationView* _formationView;
	bool _teamRequestView;
	


public:
	FormationMediator();
	virtual void handleNotification(int M2Vcmd, char* data);
	void openFormationView();  //Open formation panel
	void initFormationInfo(char* data);
	void popView();
	void createFormationList();
	void sockFormationActive(char * data);
	void sockMemberChange(char * data);
	void updateFormation(char * data);
	void formationActive( char * data );
	void popHandler(CCNode *pNode, void *data);
};

 

#endif