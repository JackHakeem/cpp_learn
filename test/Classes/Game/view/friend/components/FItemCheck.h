#pragma once

#include "BaseType.h"


class FListItem;
class FItemCheck:public LayerNode
{
public:
	enum
	{
		FItemCheckZ_frame,
		FItemCheckZ_btn_0,
		FItemCheckZ_btn_1,
		FItemCheckZ_btn_2,
		FItemCheckZ_btn_3,
		FItemCheckZ_btn_X,
	};

	enum
	{
		FItemCheckTAG_frame,
		FItemCheckTAG_btn_0,
		FItemCheckTAG_btn_1,
		FItemCheckTAG_btn_2,
		FItemCheckTAG_btn_3,
		FItemCheckTAG_btn_X,
	};

	FItemCheck();
	~FItemCheck();
	bool initWithParam(FListItem* target, int32 btnCategory);
	void clickCloseHandler(CCObject* pSender);


};