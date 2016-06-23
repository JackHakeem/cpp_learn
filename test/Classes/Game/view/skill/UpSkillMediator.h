#ifndef HLQS_UpSkillMediator_H_
#define HLQS_UpSkillMediator_H_
#include "../BaseMediator.h"

class UpSkillView;

class UpSkillMediator : public BaseMediator
{
public:
	UpSkillMediator();
	void popUpSkillView();
	virtual void handleNotification(int M2Vcmd, char* data);
	void initUpSkill();
	void skillAdded(char *data);
	void skillUpgrade(char *data);
	void formationAdded(char *data);
	void formationUpgrade(char *data);
public:
	void UpSkillInfoListener(char *data);
	void skillAddedListener(char *data);
	void skillUpgradeListener(char *data);
	void formationInfoListener(char *data);
	void formationAddedListener(char *data);
	void formationUpgradeListener(char *data);
public:
	void sendUpgradePassiveSkillRequest(uint16 passiveID);
	void sendUpgradeFormationRequest(uint16 formationID);

	void viewPopHandler(CCNode *pNode, void *data);
public:
	enum
	{
		SKILL_INIT = 0,
		SKILL_UPGRADE,
		FORMATION_UPGRADE,
		SKILL_ADDED,
		FORMATION_ADDED,
		TALENT_ADDED,
		TALENT_UPGRADE,
	};
	UpSkillView * _upskillView;
};

#endif