#ifndef HLQS_FigureBaseManage_H_
#define HLQS_FigureBaseManage_H_
#include "utils/Singleton.h"
#include "model/player/vo/FigureCfgBaseVo.h"

class FigureBaseManage: public Singleton<FigureBaseManage>
{
public:
	std::map<int, FigureCfgBaseVo> _mercList;

public:
	FigureBaseManage();
	void setMercenaryDic(FigureCfgBaseVo* vo);
	FigureCfgBaseVo* getMercBase(int mercId);
	void resetCfgMercList();
	int getLevelExpVo(int exp);
	std::string getCareerStr(int careerId);
	std::map<int, FigureCfgBaseVo>* getCfgMercList();
	std::string getPopMercenary(int pop);
	FigureCfgBaseVo* getNextPopMerc(int pop);
};

#endif