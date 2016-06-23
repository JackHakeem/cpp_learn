#pragma once

#include "BaseType.h"

class FightAoyiTextField:public LayerNode
{
public:

	enum
	{
		FightAoyiTextFieldZ_label,
	};

	enum
	{
		FightAoyiTextFieldTAG_label,
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

	FightAoyiTextField();
	~FightAoyiTextField();

	bool init();

	bool createTxt(int skillId);
	void step(ccTime dt);//´¥¿Ø¼ÆÊ±keving
	void changeStepState(int stepState);//keving
	void doAction();
public:
	float m_fStepCounter;
	int m_iStepTotalCounter;
	int m_iStepState;
	float m_fTotalActionCount;

};