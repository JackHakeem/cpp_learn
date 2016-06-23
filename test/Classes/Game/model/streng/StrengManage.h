#ifndef _STRENGMANAGER_H_
#define _STRENGMANAGER_H_

#include "utils/Singleton.h"
#include "vo/StrengRise.h"
#include "BaseType.h"

class StrengGoodsVo;
class StrengVo;
class GoodsInfo;

class StrengManage : public Singleton<StrengManage>
{
public:
	StrengManage();
	~StrengManage();

public:
	StrengRise* allocVo(){ return new StrengRise(); }
	void createStrengRise( StrengRise* info );
	StrengVo* getGoodsStrengInfo( int id,int levle,StrengVo* pStrengVo = 0 );
	int getGoodsUpStrengprice(int id,int levle);	// Expenses required to strengthen
	int getGoodDownStrengprice(int id,int levle);
	StrengGoodsVo* returnStrengGoodsVo( GoodsInfo* goodsInfo, int sitGrid, int roleID, int type = 1 );
	StrengGoodsVo* getStrengGoods( int id );
	int getGoodsUpStrengpriceToLv( int id, int level );
public:
	static const int _initialcosts = 100;  //Initial fee
	std::map<int, StrengGoodsVo*> _goodsStreng;
	std::map<std::string, StrengRise*> _goodsStrengRise;  //Improved growth value
};

#endif