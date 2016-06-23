#pragma once

#include "BaseType.h"
#include "model/notice/NoticeManager.h"

struct NM_ELM_INFO;

class CenterView;
class NoticeItem:public LayerNode
{
public:
	enum
	{
		NoticeItemZ_bg,
		NoticeItemZ_icon,
	};

	enum
	{
		NoticeItemTAG_bg,
		NoticeItemTAG_icon,
	};

	NoticeItem();
	~NoticeItem();

	bool init(NM_ELM_INFO* info, int type);
	CenterView* view();
	void onLink_ADD_FRI(CCObject* pSender);
	void onLink_CLOSE_NOTE(CCObject* pSender);

	NM_ELM_INFO m_info;
};