#pragma once

#include "BaseType.h"

class ArenaUI;

class StarRecord:public LayerNode
{
public:
	enum
	{
		StarRecordZ_s0,
		StarRecordZ_s1,
		StarRecordZ_s2,
		StarRecordZ_s3,
		StarRecordZ_s4,
		StarRecordZ_str_0,
		StarRecordZ_str_1,
	};

	enum
	{
		StarRecordTAG_s0,
		StarRecordTAG_s1,
		StarRecordTAG_s2,
		StarRecordTAG_s3,
		StarRecordTAG_s4,
		StarRecordTAG_str_0,
		StarRecordTAG_str_1,
	};

	StarRecord();
	~StarRecord();

	bool initWithParam(ArenaUI* pContainer);

	void update(std::vector<int>& arr);
public:

	ArenaUI* _pContainer;
};