#ifndef _TIPBASE_H_
#define _TIPBASE_H_

#include "BaseType.h"
#include "XHTipsInfoVo.h"

class GoodsInfo;
class UpGradeInfo;
class TipBase
{
public:
	TipBase();
	virtual ~TipBase();

	virtual CCSize getSrcContentSize();

public:
	GoodsInfo* myInfo;
	UpGradeInfo* _myInfo;
	XHTipsInfoVo* m_myXHInfo;
	
};

#endif