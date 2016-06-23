#ifndef HLQS_SkillCommand_H_
#define HLQS_SkillCommand_H_
#include "mvc/SimpleCommand.h"
#include "model/skill/SkillProxy.h"

class SkillCommand: public SimpleCommand
{
public:
	SkillCommand();
	virtual void execute(int32 command, char* data);
	void initSkillDic(char* data);
	void updateSkill(char* data);
	void updateFormation(char* cata);
	void addSkill(char* data);
	void addFormation(char* data);
	void addTalent(char* data);
	void updateTalent(char*data);
	void initTalentDic(char* data);

public:
	enum
	{
		INIT_SKILL_DIC= 0,
		UPGRADE_SKILL,
		UPGRADE_FORMATION,
		ADD_SKILL,
		ADD_FORMATION,
		ADD_TALENT,
		UPGRADE_TALENT,
		INIT_TALENT_DIC,
	};

	SkillProxy* _skillProxy;
};

#endif