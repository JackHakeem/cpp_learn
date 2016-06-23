#pragma once

#include "BaseType.h"

class FindPMLayer:public LayerNode
{
public:
	enum
	{
		FindPMLayerZ_bg1,
		FindPMLayerZ_insertBg,
	};

	enum
	{
		FindPMLayerTAG_bg1,
		FindPMLayerTAG_insertBg,
	};
	FindPMLayer();
	~FindPMLayer();

	bool init();
};