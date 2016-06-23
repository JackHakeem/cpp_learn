#pragma once

#include "mvc/SimpleCommand.h"
class EggProxy;
class EggCommand:public SimpleCommand
{
public:
	enum
	{
		HISTORY_RESULT,
		DEPOT_RESULT,
	};

public:
	EggCommand();
	~EggCommand();

	virtual void execute(int32 command, char* data);

public:
	EggProxy* _eggProxy;
};