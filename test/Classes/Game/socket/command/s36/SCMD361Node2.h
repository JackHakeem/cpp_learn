#pragma once

#include "BaseType.h"

struct SCMD361Node2
{
	SCMD361Node2()
	{
		a_time = 0;
		b_name = "";
		c_position = 0;
		d_result = 0;
		e_trend = 0;
		f_report1 = 0;
		g_report2 = 0;
	}
	uint32 a_time;
	std::string b_name;
	int8 c_position;
	int8 d_result;
	int8 e_trend;
	uint32 f_report1;
	uint32 g_report2;
};