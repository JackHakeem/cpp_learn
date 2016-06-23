#pragma once

#include "BaseType.h"

class ArenaConst
{
public:
	ArenaConst() {}
	~ArenaConst() {}

	enum
	{
		REPORT_ARENA = 0, // �鿴ս��
		TAKE_AWARD,      // ��ȡ���ƽ���
		PK_ARENA,    // ���𾺼�����ս
		BUY_ARENA,  // ���򾺼��� 
		GIFT_PACKAGE,  // ��ȡ�������������
		RESET_OPPS,    //refresh the qualifying oppents
		CARD_FINISH, 
	};


	static int getIndexByRank(int rank);
	/*
			// ����������ȡ��ӦͼƬ������ֵ 
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
		
		// ��ȡ��������Vo�򵥵�tip
		public static function getRankingTip(cRankVo:CfgRankVo):String{
			var tip:String = "";
			tip = tip.concat("</font color='#ffff00'>����:</font>" + cRankVo.silver);
			tip = tip.concat("\n</font color='#ffff00'>����:</font>" + cRankVo.pop);
			return tip;
		}
		
		// ����card/��ʤstreak/���ǵȼ�roleLev/��ȡ��Ʒ���� card��0-3 
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
		
//////////////////////////////Ӣ�۰�/////////////////////////////////////////////////////////////////////
		
		public static const ADD_FRIEND:String = "ADD_FRIEND";  // ��Ӻ���
	*/
};