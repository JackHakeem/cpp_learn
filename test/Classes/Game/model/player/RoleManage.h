#ifndef HLQS_RoleManage_h
#define HLQS_RoleManage_h
#include "utils/Singleton.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/backpack/vo/GoodsInfo.h"

using namespace cocos2d;

class RoleManage: public Singleton<RoleManage>
{
public:
	struct MercKeyIndex
	{
		int index;
		int id;
		bool operator < (const MercKeyIndex & _M) const
		{
			if (index < _M.index)
			{
				return true;
			}
			if (index == _M.index)
			{
				return id < _M.id;
			}			
			return false;
		}
	};
	int _indexCount;

public:
	AccountInfoVo _accountInfo;           //The current account information
	std::map<int, PlayerInfoVo> _mercList;  //Mercenaries list
	std::map<MercKeyIndex, PlayerInfoVo> _mercListEx;
	std::map<int, PlayerInfoVo> _cfgMercList; // The same is mercenaries list ID as key prototype
	std::map<int, PlayerInfoVo> _playlist;   //Play list mercenaries Numbers
	int _currentId;
	 
public:
	RoleManage();
	~RoleManage();
	void addMercenary(int id, PlayerInfoVo* mercObj);
	void addMercenaryEx(int id, PlayerInfoVo* mercObj);
	void updateMercenaryEx(int id, PlayerInfoVo* mercObj);
	void updateEnergy(int present, int diffrence);
	AccountInfoVo* accountInfo();
	void accountInfo(AccountInfoVo value);
	PlayerInfoVo* getMercenary(int id);
	PlayerInfoVo* roleInfo();
	std::map<int, PlayerInfoVo>* mercList();
	std::map<MercKeyIndex, PlayerInfoVo>* mercListEx();
	std::map<int, PlayerInfoVo>* cfgMercList();
	void playlist(std::map<int, PlayerInfoVo> &value);
	std::map<int, PlayerInfoVo>* playlist();
	void currentId(int id);
	int currentId();
	//int currentFigureLev();
	int currentFigureCareer();
	bool isRole();
	GoodsInfo* getSitGridEquip(int sitGrid);
	bool roleOpe();
	int currentFigureLev();

	int roleLev();	
	int getAccountIdByMerhId(int merhId);

};
#endif
