#pragma once

#include "BaseType.h"
#include "model/guild/vo/ApplyVo.h"

class GuildDispatcher;
class VerifyItem:public LayerNode
{
public:
	enum
	{
		VerifyItemZ_bg1,
		VerifyItemZ_txtID,
		VerifyItemZ_txtLevel,
		VerifyItemZ_txtFame,
		VerifyItemZ_txtDate,
		VerifyItemZ_btnyes,
		VerifyItemZ_btnno,
	};
	enum
	{
		VerifyItemTAG_bg1,
		VerifyItemTAG_txtID,
		VerifyItemTAG_txtLevel,
		VerifyItemTAG_txtFame,
		VerifyItemTAG_txtDate,
		VerifyItemTAG_btnyes,
		VerifyItemTAG_btnno,
	};
	VerifyItem();
	~VerifyItem();

	bool init(ApplyVo memberVo);
	void initView();
	void onYesBtnClick(CCObject* pSender);
	void onNoBtnClick(CCObject* pSender);
public:
	ApplyVo _applyVo;		//公会成员信息对象;
	GuildDispatcher* _guildDispatch;
};