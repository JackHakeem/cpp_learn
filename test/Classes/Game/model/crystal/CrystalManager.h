#ifndef _CRYSTALMANAGER_H_
#define _CRYSTALMANAGER_H_

#include "utils/Singleton.h"
#include "BaseType.h"

class CrystalInfo;
class ValuesUtil;

class CrystalManager:public Singleton<CrystalManager>
{
public:
	CrystalManager();
	virtual ~CrystalManager();

public:
	ValuesUtil * _cv;

 	std::map<string,string> _upgradePreTips;	

	
	std::string getUpgradeTip(int type,int lev);
};

#endif