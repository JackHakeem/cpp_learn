#pragma once

#include "BaseType.h"
#include "utils/ScaleUtil.h"

//const float w_bg1 = POSX(928.0f);
//const float h_bg1 = POSX(562.0f);
//
//const float w_bg2 = POSX(910.0f);
//const float h_bg2 = POSX(524.0f);

#define w_bg1 POSX(928.0f)
#define h_bg1 POSX(562.0f)

#define w_bg2 POSX(910.0f)
#define h_bg2 POSX(524.0f)

class PopUIBg:public LayerNode
{
public:
	enum
	{
		PopUIBgZ_bg0 = -1,
		PopUIBgZ_bg1 = 0,
		PopUIBgZ_bg2,
		PopUIBgZ_btn_1,
		PopUIBgZ_btn_X,
	};

	enum
	{
		PopUIBgTAG_bg0 = -1,
		PopUIBgTAG_bg1 = 0,
		PopUIBgTAG_bg2,
		PopUIBgTAG_btn_1,
		PopUIBgTAG_btn_X,
	};
public:
	PopUIBg();
	~PopUIBg();

	bool init();

	void clickBackHandler(CCObject* pSender);
	void clickCloseHandler(CCObject* pSender);
	void setBackBtnShow(bool show);
public:
};