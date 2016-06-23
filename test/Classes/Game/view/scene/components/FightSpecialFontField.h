#pragma once

#include "BaseType.h"

class FightSpecialFontField:public LayerNode
{
public:

	enum
	{
		FightSpecialFontFieldZ_label,
	};

	enum
	{
		FightSpecialFontFieldTAG_label,
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

	enum
	{
		BAOJI = 1,
		FANJI,
		NUQI,
		SHANBI, 
	};

	FightSpecialFontField();
	~FightSpecialFontField();

	bool init();


	bool createTxt(int style);
	void step(ccTime dt);//´¥¿Ø¼ÆÊ±keving
	void changeStepState(int stepState);//keving
	void doAction();
public:
    int m_iStyle;
public:
	float m_fStepCounter;
	int m_iStepTotalCounter;
	int m_iStepState;
    float m_fTotalActionCount;

};