#pragma once

#include "BaseType.h"

struct SCMD38FNode
{
	SCMD38FNode()
	{
		a_id = 0;
		b_type = 0;
		c_title = "";
		d_content = "";
		e_startTime = 0;
		f_endTime = 0;
		g_isShowTime = 0;
	}

	uint32 a_id;
	uint8 b_type;
	std::string c_title;
	std::string d_content;
	uint32 e_startTime;
	uint32 f_endTime;
	uint8 g_isShowTime;
};