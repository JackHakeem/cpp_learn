#pragma once

#include "BaseType.h"

class ChangeKey
{
public:
	static int getGoodsId(std::string key)
	{
		if (key == "1_1_0_3")
			return 3008;
		else if (key == "1_1_0_4")
			return 3007;
		else if (key == "1_1_0_5")
			return 3006;
		else if (key == "1_1_0_6")
			return 3005;
		else if (key == "2_1_0_3")
			return 3012;
		else if (key == "2_1_0_4")
			return 3011;
		else if (key == "2_1_0_5")
			return 3010;
		else if (key == "2_1_0_6")
			return 3009;
		else if (key == "1_2_0_101")
			return 3015;
		else if (key == "1_2_0_102")
			return 3016;
		else if (key == "2_2_0_101")
			return 3017;
		else if (key == "2_2_0_102")
			return 3018;
		else if (key == "2_3_1_101")
			return 3019;
		else if (key == "2_3_2_101")
			return 3020;
		else if (key == "2_3_3_101")
			return 3021;
		else if (key == "2_3_4_101")
			return 3022;
		else if (key == "2_3_5_101")
			return 3023;
		else if (key == "2_3_6_101")
			return 3024;
		else if (key == "2_3_1_102")
			return 3025;
		else if (key == "2_3_2_102")
			return 3026;
		else if (key == "2_3_3_102")
			return 3027;
		else if (key == "2_3_4_102")
			return 3028;
		else if (key == "2_3_5_102")
			return 3029;
		else if (key == "2_3_6_102")
			return 3030;
		else 
			return -1;

	}
};