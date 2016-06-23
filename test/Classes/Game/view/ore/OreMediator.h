#pragma once

#include "BaseType.h"
#include "mvc/Mediator.h"

class OreView;
class OreMediator:public Mediator
{
public:
	OreMediator();
	~OreMediator();

public:
	void OpenView();
	void UpdateOre(uint32 stoneNum, uint32 oreNum, uint32 buyCount);
	void HandleResponse(uint32 flag);
	void UpdatePlantProgress(uint32 progress);
	int getOreNumber();
public:
	OreView* m_pOreView;
	int _oreNum;
};