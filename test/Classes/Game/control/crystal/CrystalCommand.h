#ifndef _CRYSTAL_H_
#define _CRYSTAL_H_
#include "mvc/SimpleCommand.h"
#include "model/crystal/vo/CrystalInfo.h"
#include "model/task/TaskProxy.h"

class CrystalManager;
class CrystalProxy;

class CrystalCommand : public SimpleCommand
{
public:

	enum 
	{
		INIT_CRYSTALS=0,
		INIT_ACCOUNT_INFO,
		UPDATE_CRYSTALS,
		LINK_ITEMS_TO_DICT,
		UPGRADE_CRYSTALS,
		UPGRADE_CDTIME,
		UPGRADE_CDLIST,
	};


	std::map<int, CrystalInfo*> idToVo;
	std::map<int, CrystalInfo*> itemToVo;

	CrystalManager * _crystalManager;
	CrystalProxy * _crystalProxy;
	TaskProxy *_taskProxy;
public:
	CrystalCommand();
	~CrystalCommand();
	virtual void execute(int32 command, char* data);

	void sendCDListRequest(int id);
	void initCrystals(char* data);
	void initData();
	void initAccountInfo(char* data);
	void updateCrystals(char* data);
	void upgradeCrystals( char* data);
	void linkItemsToDict(char* data);
	void updateCDTime(char * data);
	void updateCDList(char * data);
	std::map<int,CrystalInfo*>  getIdToVo();
	std::map<int,CrystalInfo*>  getItemToVo();
};



#endif