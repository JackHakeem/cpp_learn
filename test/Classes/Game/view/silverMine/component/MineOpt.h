#pragma once

#include "BaseType.h"
class MineView;
class MineOpt:public LayerNode
{
public:
	

	MineOpt();
	~MineOpt();

	bool init(MineView* pContainer);
	void updateMineInfo(int mineId, int onMine);
	int getCapacity(int level);
	void setDescription();
	std::string getFlourish(int online, int capacity);
	void digClick(CCObject* pSender);
	void digClick2(CCObject* pSender);
	void digClick3(CCObject* pSender);
	void searchClick(CCObject* pSender);
	void setDigBtnEnable(bool value);
	void setSearchBtnEnable(bool value);
public:
	int _capacity;  // ����
	int _online;   // ��ǰ���� 
	CCLabelTTF* _txtPercent;
	MineView* pContainer;
	CCMenuItemSprite* _btnDig;// �ڿ�
	CCMenuItemSprite* _btnDig2;//// �ƽ��ڿ� aurum
	//CCMenuItemSprite* _btnDig3;  // �׽��ڿ� platina 
	CCMenuItemSprite* _btnSearch;// �� 1һ����������ƣ�һֱ���� 2,10��ҿ�ֱ��ʹ�� 3,�������������Ƶĵ��� 4,�ɲ鿴һ��Χ�������ϵ��������

};
