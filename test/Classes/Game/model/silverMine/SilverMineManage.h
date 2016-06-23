#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"
#include "vo/BasicMineVo.h"
#include "utils/Timer.h"

class SilverMineManage : public Singleton<SilverMineManage>
{
public:
	typedef  std::map<int, BasicMineVo> Dictionary;
	Dictionary _basicDic;
	Number _mineStartTime;  // 银矿战开启时间
	Number _mineEndTime;	   // 银矿战结束时间 

	Number _gongStartTime;  // 银矿战开启时间
	Number _gongEndTime;	   // 银矿战结束时间 

	//String _mineStartTips; // 银矿战Tips

		
	BasicMineVo getBasicCfgByID(int mineId)
	{
		return _basicDic[mineId];
	}
		
	void addBasicCfgByID(BasicMineVo infonode);

	Dictionary getBasicDic()
	{
		return _basicDic;
	}
		
	void setmineStartTime(Number value)
	{
		_mineStartTime = value;
			
	/*	var date:Date = new Date();
		date.setTime(_mineStartTime * 1000);
		trace(date.toUTCString(), "",date.getMonth(), ":", date.getDate(),":", date.getHours());*/
	}

	Number getmineStartTime()
	{
		return _mineStartTime;
	}
		
	
	void setmineEndTime(Number value){
		_mineEndTime = value; 
	}
	Number getmineEndTime(){
		return _mineEndTime;
	}
		



	void setgongStartTime(Number value)
	{
		_gongStartTime = value;
			
	}

	Number getgongStartTime()
	{
		return _gongStartTime;
	}
	void setgongEndTime(Number value){
		_gongEndTime = value; 
	}
	Number getgongEndTime(){
		return _gongEndTime;
	}
		
		
	//public function getCloseTips():String{
	//	var str:String = null;
	//	var utime:Number = this._mineStartTime * 1000;
	//	var date:Date = new Date();
	//	date.setTime(utime);
	//	var month:int = date.getMonth()+1;
	//	var day:int = date.getDate();
	//	var hoursStr:String = LangManager.getText("SLM036");
	//	str = LangManager.getText("SLM037",month,day,hoursStr);
	//	str += LangManager.getText("SLM038");
	//	return str;
	//}
	//	
	//public function getOpenTips():String{
	//	var str:String = null;
	//	str = LangManager.getText("SLM039");
	//	return str;
	//}
};