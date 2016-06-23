#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include "utils/Singleton.h"
#include "vo/ResourceVo.h"
//using namespace util;

class ResourceManage : public Singleton<ResourceManage>
{
public:
	ResourceManage();
	~ResourceManage();

public:
	ResourceVo* allocVo() { return new ResourceVo(); };

	ResourceVo * getRes( int type, int iResID );
	void setRes( ResourceVo * pResourceVo );
	ResourceVo * getDefaultModel(int id);
	ResourceVo * getDefaultSkill(int id);
	std::string skillUrl();

private:
	std::map<int, ResourceVo *> _resDic;
	std::map<int, ResourceVo *> _resSkillDic;
};

typedef std::map<int, ResourceVo *>::iterator RESOURCEVOITER;

#endif