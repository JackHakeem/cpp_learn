#pragma once

#include "mvc/Proxy.h"
#include "model/silverMine/vo/SilverMineVo.h"

class SilverMineProxy: public Proxy
{
public:
	SilverMineProxy();
	~SilverMineProxy();

	int getcampId()
	{
		return _campId;
	}
	void setcampId(int value)
	{
		_campId = value;
	}
	uint getmoveCD()
	{
		return _moveCD;
	}
	void setmoveCD(uint value)
	{
		_moveCD = value;
	}
	uint getdigCD()
	{
		return _digCD;
	}
	void setdigCD(uint value)
	{
		_digCD = value;
	}
	bool getinActionCD(){
		return _inActionCD;
	}
	void setinActionCD(bool value){
		_inActionCD = value;
	}
	bool getinDigCD(){
		return _inActionCD;
	}
	void setinDigCD(bool value){
		_inDigCD = value;
	}
	int getmineID(){
		return _mineID;
	}
	void setmineID(int value){
		_mineID = value;
	}
	int getonMine(){
		return _onMine;
	}
	void setonMine(int value){
		_onMine = value;
	}
	int getwinRow(){
		return _winRow;
	}
	void setwinRow(int value){
		_winRow = value;
	}
	std::list<SilverMineVo>& getmineArr(){
		return _mineArr;
	}
	int getattPlus(){
		return _attPlus;
	}
	void setattPlus(int value){
		_attPlus = value;
	}
	int getdefPlus(){
		return _defPlus;
	}
	void setdefPlus(int value){
		_defPlus = value;
	}
		
	int gettoken0(){
		return _token0;
	}
	int gettoken1(){
		return _token1;
	}
	void settoken0(int value){
		_token0 = value;
	}
	void settoken1(int value){
		_token1 = value;
	}

public:
		bool isInMine ;
		int _campId;  // 阵营ID 有效值 0，1, 2 
		uint32 _moveCD;	// 行动CD 单位秒
		bool _inActionCD;
		uint32 _digCD;	// 挖矿CD 单位秒
		bool _inDigCD;
		int _mineID;		// 当前所在矿ID
		int _onMine;		// 当前所在银矿人数
		int _winRow;		// 连胜次数
		int _attPlus;		// 鼓舞攻击加成
		int _defPlus;		// 鼓舞防御加成 
		std::list<SilverMineVo> _mineArr;  // 银矿数组
		int _token0;   // 令牌0
		int _token1;   // 令牌1 
};