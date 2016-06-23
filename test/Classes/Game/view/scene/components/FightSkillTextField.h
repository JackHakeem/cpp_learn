#pragma once

#include "BaseType.h"

class FightSkillTextField:public LayerNode
{
public:

	enum
	{
		FightSkillTextFieldZ_label,
	};

	enum
	{
		FightSkillTextFieldTAG_label,
	};

	enum
	{
		StepState_idle,
		StepState_rising,
	};

	enum
	{
		BLOOD_UP,
		BLOOD_DOWN,
		MP_UP,
	};

	FightSkillTextField();
	~FightSkillTextField();

	bool init();


	bool createTxt(std::string skillName, int skillId);
	void step(ccTime dt);//´¥¿Ø¼ÆÊ±keving
	void changeStepState(int stepState);//keving
	void doAction();
public:
	float m_fStepCounter;
	int m_iStepTotalCounter;
	int m_iStepState;
	float m_fTotalActionCount;
};