#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"
#include "model/zx/vo/XHConfVo.h"
#include "model/zx/vo/XHExpConfVo.h"

class XHConfManager: public Singleton<XHConfManager>
{
public:
	XHConfManager();
	virtual ~XHConfManager();

	void addXHConf(XHConfVo& vo);
	XHConfVo* getXHConf(int8 XHtype);

	void addXHExpConf(XHExpConfVo& vo);
	int getXHExpConf(int8 XHcolor, int8 lv);
public:
	std::map<int8, XHConfVo> _XHConfDic;
	std::map<int8, XHExpConfVo> _XHExpConfDic;
};
