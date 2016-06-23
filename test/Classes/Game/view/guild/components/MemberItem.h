#pragma once

#include "BaseType.h"
#include "model/guild/vo/MemberVo.h"
#include "MemberPanel.h"

class MemberItem:public LayerNode
{
public:
	enum
	{
		MemberItemZ_bg1,
		MemberItemZ_txtClass,
		MemberItemZ_txtCon,
		MemberItemZ_txtID,
		MemberItemZ_txtLevel,
		MemberItemZ_txtFame,
		MemberItemZ_txtLine,
		MemberItemZ_btn,
	};
	enum
	{
		MemberItemTAG_bg1,
		MemberItemTAG_txtClass,
		MemberItemTAG_txtCon,
		MemberItemTAG_txtID,
		MemberItemTAG_txtLevel,
		MemberItemTAG_txtFame,
		MemberItemTAG_txtLine,
		MemberItemTAG_btn,
	};
	MemberItem();
	~MemberItem();

	bool init(MemberVo memberVo, int tag);
	void initView(int tag);
	MemberPanel* getMemberPanel();

public:
	MemberVo _memberVo;		//公会成员信息对象;
};