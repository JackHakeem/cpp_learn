#ifndef _HonorGoodVo_H_
#define _HonorGoodVo_H_

struct AwardThing
{
	int type;
	int numbers;
	AwardThing()
	{
		type = 0;
		numbers = 0;
	}
};

class HonorGoodVo
{
public:
	HonorGoodVo()
	{
		honorsid = 0;
		goods.clear();
		m_map = 0;
		taskId = 0;
		//enabled = 0;
		//completed = false;
		//award = 1;
	}

public:
	//int bigtype;           //成就大类
	//int type;              //成就小类
	int honorsid;          //成就编号
	//string honorname;     //成就名
	//int reward;          //奖励点数
	//string title;        //称号
	//string reamark;      //成就达成条件说明
	//成就达成物品奖励  1:xx|2:xx|goodsId:xx, 1金币，2银币，goodsId是物品，如果都没有则0:0，
	vector<AwardThing> goods;
	int m_map;			//通关奖励地图id
	int taskId;		//通关奖励对应的任务id，用于寻路索引
	//int enabled;     //0未开始  1= 已开启
	//bool completed;
	//int award; //是否已领取 默认是领取  1= true 
};

#endif