#include "CrystalManager.h"
#include "utils/ValuesUtil.h"

CrystalManager::CrystalManager()
{
	_cv = ValuesUtil::Instance();
}

CrystalManager::~CrystalManager()
{

}

std::string CrystalManager::getUpgradeTip(int type,int lev)
{
	char s[16] = {0};
	sprintf(s,"%d_%d",type,lev);
	std::string key = s;
	if(_upgradePreTips.find(key) != _upgradePreTips.end())
	{
		return _upgradePreTips.find(key)->second;
	}
	else
	{
		return "";
	}
}