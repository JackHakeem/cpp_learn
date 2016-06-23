#pragma once

#include "BaseType.h"
#include "mvc/Mediator.h"

class ZXView;
class XHView;
class ZXMediator:public Mediator
{
public:
	ZXMediator();
	~ZXMediator();

public:
	void OpenXHView();
	void updateScore(uint32 score);
public:
	XHView* m_pXHView;
	int32 m_iScore;
};