#ifndef _CRYSTALPROXY_H_
#define _CRYSTALPROXY_H_

#include "mvc/Proxy.h"
#include "model/crystal/vo/CrystalInfo.h"

using namespace std;

class CrystalProxy: public Proxy
{
public:
	CrystalProxy();
	virtual ~CrystalProxy();

	void initData();
	void initCrystal( char* data);
	void upgradeCrystal( char* data);
	void updateCrystal( char* data);
	void updateDetailInfo( int id);
	void crystalCDTime(char *data);
	void crystalCDList(char *data);

public:
	std::map <int,CrystalInfo*> _idToVos;		//VO:key:id,value:CrystalInfo
	std::map <int,CrystalInfo*> _itemToVos;		//VO:key:clicked crystal object,value:CrystalInfo

	std::map <int,CrystalInfo*> getIdToVos();

	std::map <int,CrystalInfo*> getItemToVos();

	int getCrystalLev(int id);
	
	std::string getUpgradeTip(int type);

	static int getIndex(int id);
};

#endif