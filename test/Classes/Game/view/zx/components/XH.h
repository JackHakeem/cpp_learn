#pragma once

#include "LayerNode.h"
#include "utils/TipBase.h"

class TipHelps;
class XH:public LayerNode, public TipBase
{
public:
	enum
	{
		XH_POS_16=1,
		XH_POS_8=3,
	};
public:
	XH();
	~XH();

	bool init(int index, uint8 lv, uint32 curexp);
public:
	int m_iXHType;
	uint8 m_iLv;
	uint32 m_iCurExp;
	TipHelps* myTip;
};