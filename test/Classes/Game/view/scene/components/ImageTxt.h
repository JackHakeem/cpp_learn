#pragma once

#include "BaseType.h"

class ImageTxt:public LayerNode
{
public:

	enum
	{
		ImageTxtZ_labelValue,
	};

	enum
	{
		ImageTxtTAG_labelValue,
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

	ImageTxt();
	~ImageTxt();

	bool init();

	void createTxt(int type, int seat,  int value, bool iscrit = false);
	void step(ccTime dt);//´¥¿Ø¼ÆÊ±keving
	void changeStepState(int stepState);//keving
	void doAction();
public:
    bool m_bIscrit;
public:
	float m_fStepCounter;
	int m_iStepTotalCounter;
	int m_iStepState;
	float m_fTotalActionCount;
    int m_spSeat;

};