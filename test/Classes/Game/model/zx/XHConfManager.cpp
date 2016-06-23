#include "XHConfManager.h"

XHConfManager::XHConfManager()
{}

XHConfManager::~XHConfManager()
{}

void XHConfManager::addXHConf(XHConfVo& vo)
{
	_XHConfDic[vo.type] = vo;
}

XHConfVo* XHConfManager::getXHConf(int8 XHtype)
{
	std::map<int8, XHConfVo>::iterator it = _XHConfDic.find(XHtype);
	if (it == _XHConfDic.end())
		return 0;

	return &(it->second);
}

//std::map<int8, XHExpConfVo> _XHExpConfDic;
void XHConfManager::addXHExpConf(XHExpConfVo& vo)
{
	_XHExpConfDic[vo.color] = vo;
}

int XHConfManager::getXHExpConf(int8 XHcolor, int8 lv)
{
	std::map<int8, XHExpConfVo>::iterator it = _XHExpConfDic.find(XHcolor);
	if (it == _XHExpConfDic.end())
		return 0;

	XHExpConfVo& tmpConf= it->second;
	return tmpConf.lv[lv];
}