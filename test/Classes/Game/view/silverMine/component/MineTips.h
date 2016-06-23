#pragma once

#include "BaseType.h"

class CCUIBackground;
class MineView;
class MineTips:public LayerNode
{
public:
	enum
	{
		baijin,
		huangjin,
		guwu_gold,
		guwu_lilian,
	};
	MineTips();
	~MineTips();

	bool init(int type, MineView* pContainer);
	void confirm(CCObject* pSender);
	void cancel(CCObject* pSender);
	void close(CCObject* pSender);
public:
	int m_type;
	MineView* pContainer;

public:

};