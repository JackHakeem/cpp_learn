#ifndef _APPOINT_VO_H_
#define _APPOINT_VO_H_

class AppointVo
{
public:
	int id;					//���˵ı��0~7
	int type;				//�������� 0����ָ���ˣ� 1����������
	int level;				//���˵ȼ� 0~3
	std::string name;		//��������
	std::string info;		//������Ϣ
	int silver;				//ί����Ҫ������
	int gold;				//ί����Ҫ�Ľ��
	std::string icon;		//����ͷ��

	/** =========������Ϣ�������ļ���ȡ========== */

	bool isGoldAppoint;		//�Ƿ���ί��
	int freeNum;			//ʣ�����ί�ɴ���
	int bitNum;				//��bitλ��ʾ��������Ϣ

};
#endif