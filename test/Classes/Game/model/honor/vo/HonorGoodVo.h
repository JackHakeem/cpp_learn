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
	//int bigtype;           //�ɾʹ���
	//int type;              //�ɾ�С��
	int honorsid;          //�ɾͱ��
	//string honorname;     //�ɾ���
	//int reward;          //��������
	//string title;        //�ƺ�
	//string reamark;      //�ɾʹ������˵��
	//�ɾʹ����Ʒ����  1:xx|2:xx|goodsId:xx, 1��ң�2���ң�goodsId����Ʒ�������û����0:0��
	vector<AwardThing> goods;
	int m_map;			//ͨ�ؽ�����ͼid
	int taskId;		//ͨ�ؽ�����Ӧ������id������Ѱ·����
	//int enabled;     //0δ��ʼ  1= �ѿ���
	//bool completed;
	//int award; //�Ƿ�����ȡ Ĭ������ȡ  1= true 
};

#endif