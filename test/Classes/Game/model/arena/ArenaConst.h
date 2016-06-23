#pragma once

#include "BaseType.h"

class ArenaConst
{
public:
	ArenaConst() {}
	~ArenaConst() {}

	enum
	{
		REPORT_ARENA = 0, // 查看战报
		TAKE_AWARD,      // 领取翻牌奖励
		PK_ARENA,    // 发起竞技场挑战
		BUY_ARENA,  // 购买竞技令 
		GIFT_PACKAGE,  // 领取竞技场排名礼包
		RESET_OPPS,    //refresh the qualifying oppents
		CARD_FINISH, 
	};


	static int getIndexByRank(int rank);
	/*
			// 根据排名获取对应图片的索引值 
		public static function getIndexByRank(rank:int):int{
			var index:int = 1;
			if(rank==1){
				index = 12;				
			}
			else if(rank==2){
				index = 11;
			}
			else if(rank==3){
				index = 10;
			}
			else if(rank==4){
				index = 9;
			}
			else if(rank==5){
				index = 8;
			}
			else if(rank<=10){
				index = 7;
			}
			else if(rank<=25){
				index = 6;
			}
			else if(rank<=100){
				index = 5;
			}
			else if(rank<=200){
				index = 4;
			}
			else if(rank<=400){
				index = 3;
			}
			else if(rank<=600){
				index = 2;
			}
			else if(rank<=1000){
				index = 1;
			}
			return index;
		}
		
		// 获取竞技排名Vo简单的tip
		public static function getRankingTip(cRankVo:CfgRankVo):String{
			var tip:String = "";
			tip = tip.concat("</font color='#ffff00'>银币:</font>" + cRankVo.silver);
			tip = tip.concat("\n</font color='#ffff00'>名声:</font>" + cRankVo.pop);
			return tip;
		}
		
		// 根据card/连胜streak/主角等级roleLev/获取奖品描述 card从0-3 
		public static function getLuckyCard(card:int,streak:int,roleLev:int):Object{
			var desc:String = "";
			var silver:int;
			var prac:int;
			var gold:int;
			switch(card){
				case 0:
					silver = (100 + streak*10) * roleLev;
					prac = (20 + streak*2) * roleLev; 
					break;
				case 1:
					silver = (200 + streak*20) * roleLev;
					prac = (40 + streak*4) * roleLev;
					break;
				case 2:
					silver = (300 + streak*30) * roleLev;
					prac = (60 + streak*6) * roleLev;
					break;
				case 3:
					silver = (300 + streak*30) * roleLev;
					prac = (60 + streak*6) * roleLev; 
					gold = 5 + streak; 
					break;
  			}
			return {silver:silver, prac:prac, gold:gold};
		}
		
//////////////////////////////英雄榜/////////////////////////////////////////////////////////////////////
		
		public static const ADD_FRIEND:String = "ADD_FRIEND";  // 添加好友
	*/
};